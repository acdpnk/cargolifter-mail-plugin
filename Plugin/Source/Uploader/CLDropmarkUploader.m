// Copyright (C) 2019 Mailbutler GmbH
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
//  CLDropmarkUploader.m
//
//  Created by Fabian Jäger on 09.04.13.
//  Copyright (c) 2013 Mailbutler. All rights reserved.
//

#import "CLDropmarkUploader.h"

#import "NSString+CLAdditions.h"
#import <AFNetworking/AFNetworking.h>

#define CLDropmarkAPIKey        @"***REMOVED***"
#define CLDropmarkUserID        @"CLDropmarkUserID"
#define CLDropmarkToken         @"CLDropmarkToken"
#define CLDropmarkCollectionID  @"CLDropmarkCollectionID"

@interface CLDropmarkUploader ()

- (NSError*) errorFromError:(NSError*)origError;

@end

@implementation CLDropmarkUploader

- (void) uploadFile:(NSString*)localFilePath createPublicLink:(BOOL)createPublicLink rawFileAccess:(BOOL)rawFile
{
    if( self.busy )
        return;
    
    NSString* collectionID = self.service.credentials[CLDropmarkCollectionID];
    NSString* userID = self.service.credentials[CLDropmarkUserID];
    NSString* token = self.service.credentials[CLDropmarkToken];
    
    if( !(collectionID && userID && token) )
        return;
    
    self.activeFile = localFilePath;
    self.busy = YES;
    self.canceled = NO;
    
    NSURL* baseURL = [NSURL URLWithString:@"https://api.dropmark.com"];
    
    // make sure we are authorized correctly
    AFHTTPSessionManager *manager = [[AFHTTPSessionManager alloc] initWithBaseURL:baseURL];
    [manager.requestSerializer setValue:CLDropmarkAPIKey forHTTPHeaderField:@"X-API-Key"];
    [manager.requestSerializer setValue:@"application/json" forHTTPHeaderField:@"Accept"];
    [manager.requestSerializer setAuthorizationHeaderFieldWithUsername:userID password:token];
    AFJSONResponseSerializer* jsonSerializer = [AFJSONResponseSerializer serializer];
    [jsonSerializer setRemovesKeysWithNullValues:YES];
    manager.responseSerializer = jsonSerializer;
    
    NSString* apiPath = [NSString stringWithFormat:@"/v1/collections/%@/items", collectionID];
    
    // upload files via Dropmark
    NSString *filename = localFilePath.lastPathComponent;
    NSData* fileData = [NSData dataWithContentsOfFile:localFilePath];
    NSString *mimeType = [self MIMETypeFileName:filename defaultMIMEType:@"binary/octet-stream"];
    
    NSString* shareable = createPublicLink?@"true":@"false";
    
    [manager POST:apiPath parameters:@{@"name":filename, @"shareable":shareable} constructingBodyWithBlock:^(id<AFMultipartFormData>  _Nonnull formData) {
        [formData appendPartWithFileData:fileData name:@"content" fileName:filename mimeType:mimeType];
    } progress:^(NSProgress * _Nonnull uploadProgress) {
    
        if(self.canceled)
        {
            self.busy = NO;
            
            [uploadProgress cancel];
            return;
        }
        
        dispatch_async(dispatch_get_main_queue(), ^{
            if( [self.delegate respondsToSelector:@selector(uploadProgress:forFile:)] )
                [self.delegate uploadProgress:uploadProgress.fractionCompleted forFile:localFilePath];
        });
        
    } success:^(NSURLSessionDataTask * _Nonnull task, id  _Nullable responseObject) {
        NSLog(@"📯 CARGOLIFTER: UPLOAD SUCCESS: ");
        
        NSDictionary* uploadDict = (NSDictionary*)responseObject;
        NSString* uploadURLString = uploadDict[@"short_url"];
        NSString* thumbURLString = nil;
        
        if( uploadDict[@"thumbnail"] )
            thumbURLString = uploadDict[@"thumbnail"];
        
        if(rawFile)
            uploadURLString = uploadDict[@"content"];
        
        self.busy = NO;
        
        if( [self.delegate respondsToSelector:@selector(createdLink:forFile:withIconURL:)] )
            [self.delegate createdLink:[NSURL URLWithString:uploadURLString] forFile:localFilePath withIconURL:[NSURL URLWithString:thumbURLString]];
    } failure:^(NSURLSessionDataTask * _Nullable task, NSError * _Nonnull error) {
        
        NSLog(@"💥 CARGOLIFTER: UPLOAD FAILURE: ");
        self.busy = NO;
        
        if( [self.delegate respondsToSelector:@selector(uploadFailedWithStatus:withError:)] )
            [self.delegate uploadFailedWithStatus:CLUploadError withError:error];
    
    }];
}

- (void) authenticate
{
    NSString* aLogin = self.service.login;
    NSString* aPassword = self.service.password;
    
    if(!(aLogin && aPassword))
    {
        NSError* error = [NSError errorWithDomain:CLServiceAuthErrorDomain code:CLServiceAuthErrorInvalidCredentials userInfo:@{NSLocalizedDescriptionKey:[CLUploader localizedErrorDescriptionForErrorCode:CLServiceAuthErrorInvalidCredentials]}];
        
        if( [self.authDelegate respondsToSelector:@selector(didFinishAuthenticationWithError:)] )
            [self.authDelegate didFinishAuthenticationWithError:error];
        
        [self.service markAsLinked:NO];
        
        return;
    }
    
    NSString* collectionName = @"CargoLifter";
    
    // make sure we are authorized correctly
    AFHTTPSessionManager *manager = [[AFHTTPSessionManager alloc] initWithBaseURL:[NSURL URLWithString:@"https://api.dropmark.com"]];
    AFJSONResponseSerializer* jsonSerializer = [AFJSONResponseSerializer serializer];
    [jsonSerializer setRemovesKeysWithNullValues:YES];
    manager.responseSerializer = jsonSerializer;
    [manager.requestSerializer setValue:CLDropmarkAPIKey forHTTPHeaderField:@"X-API-Key"];
    [manager.requestSerializer setValue:@"application/json" forHTTPHeaderField:@"Accept"];
    
    self.service.linking = YES;
    
    [manager POST:@"/v1/auth" parameters:@{@"email":aLogin, @"password":aPassword} progress:nil success:^(NSURLSessionDataTask * _Nonnull task, id  _Nullable responseObject) {
        
        NSLog(@"📯 CARGOLIFTER: SUCCESS: %@", responseObject);
        
        NSDictionary* responseDict = (NSDictionary*)responseObject;
        
        NSString* userID = responseDict[@"id"];
        NSString* token  = responseDict[@"token"];
        
        self.service.credentials[CLDropmarkUserID] = userID;
        self.service.credentials[CLDropmarkToken] = token;
        
        if( userID && token )
            [manager.requestSerializer setAuthorizationHeaderFieldWithUsername:userID password:token];
        
        // make sure that we have our private collection and its ID
        [manager GET:@"/v1/collections" parameters:@{@"count":@500} progress:nil success:^(NSURLSessionDataTask * _Nonnull task, id  _Nullable responseObject) {
            
            NSArray* collectionList = (NSArray*)responseObject;
            
            NSString* collectionID = nil;
            
            for(NSDictionary* aCollection in collectionList)
            {
                if( [aCollection[@"name"] isEqualToString:collectionName] )
                {
                    collectionID = aCollection[@"id"];
                    break;
                }
            }
            
            if( collectionID )
            {
                if( [self.authDelegate respondsToSelector:@selector(didFinishAuthenticationWithError:)] )
                    [self.authDelegate didFinishAuthenticationWithError:nil];
                
                self.service.credentials[CLDropmarkCollectionID] = collectionID;
                [self.service markAsLinked:YES];
            }
            else
            {
                // create collection
                [manager POST:@"/v1/collections" parameters:@{@"name":collectionName} progress:nil success:^(NSURLSessionDataTask * _Nonnull task, id  _Nullable responseObject) {
                    
                    NSLog(@"📯 CARGOLIFTER: SUCCESS: %@", responseObject);
                    
                    NSDictionary* responseDict = (NSDictionary*)responseObject;
                    NSString* collectionID = responseDict[@"id"];
                    
                    if( [self.authDelegate respondsToSelector:@selector(didFinishAuthenticationWithError:)] )
                        [self.authDelegate didFinishAuthenticationWithError:nil];
                    
                    self.service.credentials[CLDropmarkCollectionID] = collectionID;
                    [self.service markAsLinked:YES];
                    
                } failure:^(NSURLSessionDataTask * _Nullable task, NSError * _Nonnull error) {
                
                    NSLog(@"💥 CARGOLIFTER: ERROR: %@", [self errorFromError:error]);
                    
                    if( [self.authDelegate respondsToSelector:@selector(didFinishAuthenticationWithError:)] )
                        [self.authDelegate didFinishAuthenticationWithError:[self errorFromError:error]];
                    
                    [self.service.credentials removeAllObjects];
                    [self.service markAsLinked:NO];
                    
                }];
            }
            
        } failure:^(NSURLSessionDataTask * _Nullable task, NSError * _Nonnull error) {
            
            NSLog(@"💥 CARGOLIFTER: ERROR: %@", [self errorFromError:error]);
            
            if( [self.authDelegate respondsToSelector:@selector(didFinishAuthenticationWithError:)] )
                [self.authDelegate didFinishAuthenticationWithError:[self errorFromError:error]];
            
            [self.service.credentials removeAllObjects];
            [self.service markAsLinked:NO];
            
        }];
        
    } failure:^(NSURLSessionDataTask * _Nullable task, NSError * _Nonnull error) {
       
        NSLog(@"💥 CARGOLIFTER: ERROR: %@", [self errorFromError:error]);
        
        if( [self.authDelegate respondsToSelector:@selector(didFinishAuthenticationWithError:)] )
            [self.authDelegate didFinishAuthenticationWithError:[self errorFromError:error]];
        
        [self.service.credentials removeAllObjects];
        [self.service markAsLinked:NO];
        
    }];
}

#pragma mark Private Methods

- (NSError*) errorFromError:(NSError*)origError
{
    // construct readable error
    NSData *responseErrorData = origError.userInfo[AFNetworkingOperationFailingURLResponseDataErrorKey];
    NSDictionary* errorDict = [NSJSONSerialization JSONObjectWithData:responseErrorData options:0 error:nil];
    
    if( errorDict[@"code"] && errorDict[@"message"] )
    {
        CLServiceAuthError errorCode = CLServiceAuthErrorUnknownError;
        
        NSString* errorCodeString = errorDict[@"code"];
        
        if([errorCodeString isEqualToString:@"user_invalid"])
            errorCode = CLServiceAuthErrorUserInvalid;
        else if([errorCodeString isEqualToString:@"password_incorrect"])
            errorCode = CLServiceAuthErrorPasswordIncorrect;
        else if([errorCodeString isEqualToString:@"user_inactive"])
            errorCode = CLServiceAuthErrorUserInactive;
        else if([errorCodeString isEqualToString:@"user_guest"])
            errorCode = CLServiceAuthErrorUserIsGuest;
        
        NSString* errorMsg = [CLUploader localizedErrorDescriptionForErrorCode:errorCode];
        
        return [NSError errorWithDomain:CLServiceAuthErrorDomain code:errorCode userInfo:@{NSLocalizedDescriptionKey:errorMsg}];
    }
    else
    {
        return origError;
    }
}

@end
