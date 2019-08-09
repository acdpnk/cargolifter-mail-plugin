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
//  CLBoxUploader.m
//
//  Created by Fabian Jäger on 09.04.13.
//  Copyright (c) 2013 Mailbutler. All rights reserved.
//

#import "CLBoxUploader.h"

#import "NSString+CLAdditions.h"
#import "NSData+CLAdditions.h"

#import <AFNetworking/AFNetworking.h>

#import "AFOAuth2Manager.h"

#define CLBoxRedirectURL        @"https://cargolifter.mailbutler.io/box"

#define CLBoxFolderId           @"CLBoxFolderId"

#define CLBoxAPIAuthBaseURL     @"https://api.box.com"
#define CLBoxAPIUploadBaseURL   @"https://upload.box.com"

@implementation CLBoxUploader

- (NSString*) clientID { return BOX_CLIENT_ID; }
- (NSString*) clientSecret { return BOX_CLIENT_SECRET; }
- (NSURL*) oauthStartURL { return [NSURL URLWithString:[NSString stringWithFormat:@"https://account.box.com/api/oauth2/authorize?response_type=code&client_id=%@&state=authenticated", self.clientID]]; }
- (NSURL*) authBaseURL { return [NSURL URLWithString:CLBoxAPIAuthBaseURL]; }
- (NSURL*) redirectURL { return [NSURL URLWithString:CLBoxRedirectURL]; }
- (NSString*) getTokenPath { return @"/oauth2/token"; }
- (NSString*) refreshTokenPath { return @"/oauth2/token"; }
- (NSString*) revokeTokenPath { return @"/oauth2/revoke"; }

- (void) uploadFile:(NSString*)localFilePath createPublicLink:(BOOL)createPublicLink rawFileAccess:(BOOL)rawFile
{
    if( self.busy )
        return;
    
    self.activeFile = localFilePath;
    self.busy = YES;
    self.canceled = NO;
    
    [self _refreshAccessTokenWithSuccess:^{
        // use new access token
        AFOAuthCredential* credentials = [AFOAuthCredential retrieveCredentialWithIdentifier:self.service.uniqueIdentifier];
        
        // upload files via Box.net
        NSString* folderId = self.service.credentials[CLBoxFolderId];
        NSString* apiPath = [NSString stringWithFormat:@"/2.0/folders/%@/items", folderId];
        
        AFHTTPSessionManager *generalManager = [[AFHTTPSessionManager alloc] initWithBaseURL:[NSURL URLWithString:CLBoxAPIAuthBaseURL]];
        generalManager.requestSerializer = [AFJSONRequestSerializer serializer];
        AFJSONResponseSerializer* jsonSerializer = [AFJSONResponseSerializer serializer];
        [jsonSerializer setRemovesKeysWithNullValues:YES];
        generalManager.responseSerializer = jsonSerializer;
        [generalManager.requestSerializer setValue:@"application/json" forHTTPHeaderField:@"Accept"];
        [generalManager.requestSerializer setAuthorizationHeaderFieldWithCredential:credentials];
        
        // first check whether file of same name already exists
        [generalManager GET:apiPath parameters:nil progress:nil success:^(NSURLSessionDataTask * _Nonnull task, id  _Nullable responseObject) {
            NSURL* baseUploadURL = [NSURL URLWithString:CLBoxAPIUploadBaseURL];
            
            AFHTTPSessionManager *uploadManager = [[AFHTTPSessionManager alloc] initWithBaseURL:baseUploadURL];
            uploadManager.requestSerializer = [AFJSONRequestSerializer serializer];
            AFJSONResponseSerializer* jsonSerializer = [AFJSONResponseSerializer serializer];
            [jsonSerializer setRemovesKeysWithNullValues:YES];
            uploadManager.responseSerializer = jsonSerializer;
            [uploadManager.requestSerializer setValue:@"application/json" forHTTPHeaderField:@"Accept"];
            [uploadManager.requestSerializer setAuthorizationHeaderFieldWithCredential:credentials];
            
            NSDictionary* responseDict = (NSDictionary*)responseObject;
            NSArray* items = responseDict[@"entries"];
            
            NSMutableArray* filesArray = [NSMutableArray arrayWithCapacity:items.count];
            
            for( NSDictionary* anItemDict in items )
            {
                if([anItemDict[@"type"] isEqualToString:@"file"])
                    [filesArray addObject:anItemDict[@"name"]];
            }
            
            NSString* fileName = localFilePath.lastPathComponent;
            NSString* fileNameExt = fileName.pathExtension;
            NSString* fileNameBase = fileName.stringByDeletingPathExtension;
            NSInteger idx = 1;
            while( [filesArray containsObject:fileName] )
            {
                fileName = [NSString stringWithFormat:@"%@_%ld.%@", fileNameBase, idx++, fileNameExt];
            }
            
            // now use the final file name for the actual uploading
            NSString *filename = localFilePath.lastPathComponent;
            NSData* fileData = [NSData dataWithContentsOfFile:localFilePath];
            NSString *mimeType = [self MIMETypeFileName:filename defaultMIMEType:@"binary/octet-stream"];
            
            NSDictionary* params = @{@"parent_id":folderId};
            
            [uploadManager POST:@"/api/2.0/files/content" parameters:params constructingBodyWithBlock:^(id<AFMultipartFormData>  _Nonnull formData) {
                [formData appendPartWithFileData:fileData name:@"filename" fileName:fileName mimeType:mimeType];
            } progress:^(NSProgress * _Nonnull uploadProgress) {
                
                if(self.canceled)
                {
                    [uploadProgress cancel];
                    self.busy = NO;
                    return;
                }
                
                dispatch_async(dispatch_get_main_queue(), ^{
                    if( [self.delegate respondsToSelector:@selector(uploadProgress:forFile:)] )
                        [self.delegate uploadProgress:uploadProgress.fractionCompleted forFile:localFilePath];
                });
                
            } success:^(NSURLSessionDataTask * _Nonnull task, id  _Nullable responseObject) {
                
                NSLog(@"📯 CARGOLIFTER: UPLOAD SUCCESS: ");
                
                NSDictionary* fileDict = (NSDictionary*)responseObject;
                NSArray* files = fileDict[@"entries"];
                
                if( !(files && files.count==1) )
                {
                    NSError *error = [NSError errorWithDomain:CLUploaderErrorDomain code:CLUploaderErrorUnknownError userInfo:@{ NSLocalizedDescriptionKey:NSLocalizedString(@"Unknown problem during upload.", nil)}];
                    
                    self.busy = NO;
                    
                    if( [self.delegate respondsToSelector:@selector(uploadFailedWithStatus:withError:)] )
                        [self.delegate uploadFailedWithStatus:CLUploadError withError:error];
                    
                    return;
                }
                
                NSString* fileId = files[0][@"id"];
                
                // make file shareable and get link
                NSString* access = createPublicLink?@"open":@"{}";
                NSDictionary* params = @{@"shared_link":@{@"access":access}};
                
                [generalManager PUT:[NSString stringWithFormat:@"/2.0/files/%@", fileId] parameters:params success:^(NSURLSessionDataTask * _Nonnull task, id  _Nullable responseObject) {
                    NSDictionary* responseDict = (NSDictionary*)responseObject;
                    
                    NSString* uploadURLString = responseDict[@"shared_link"][@"url"];
                    
                    self.busy = NO;
                    
                    if( [self.delegate respondsToSelector:@selector(createdLink:forFile:withIconURL:)] )
                        [self.delegate createdLink:[NSURL URLWithString:uploadURLString] forFile:localFilePath withIconURL:nil];
                } failure:^(NSURLSessionDataTask * _Nullable task, NSError * _Nonnull error) {
                    NSLog(@"💥 CARGOLIFTER: SHARING FAILURE: %@", error);
                    
                    self.busy = NO;
                    
                    if( [self.delegate respondsToSelector:@selector(uploadFailedWithStatus:withError:)] )
                        [self.delegate uploadFailedWithStatus:CLUploadError withError:error];

                }];
                
            } failure:^(NSURLSessionDataTask * _Nullable task, NSError * _Nonnull error) {
                
                NSLog(@"💥 CARGOLIFTER: UPLOAD FAILURE: %@", error);
                
                self.busy = NO;
                
                if( [self.delegate respondsToSelector:@selector(uploadFailedWithStatus:withError:)] )
                    [self.delegate uploadFailedWithStatus:CLUploadError withError:error];
                
            }];
            
        } failure:nil];
        
    } failure:^(NSError *error) {
        
        self.busy = NO;
        
        if( [self.delegate respondsToSelector:@selector(uploadFailedWithStatus:withError:)] )
            [self.delegate uploadFailedWithStatus:CLUploadError withError:error];
    }];
}

- (void) postAuthenticationHookWithHandler:(void (^)(NSError *error))completionBlock {
    [self _refreshAccessTokenWithSuccess:^{
        AFOAuthCredential* credentials = [AFOAuthCredential retrieveCredentialWithIdentifier:self.service.uniqueIdentifier];

        AFHTTPSessionManager *generalManager = [[AFHTTPSessionManager alloc] initWithBaseURL:self.authBaseURL];
        generalManager.requestSerializer = [AFJSONRequestSerializer serializer];
        AFJSONResponseSerializer* jsonSerializer = [AFJSONResponseSerializer serializer];
        [jsonSerializer setRemovesKeysWithNullValues:YES];
        generalManager.responseSerializer = jsonSerializer;
        [generalManager.requestSerializer setValue:@"application/json" forHTTPHeaderField:@"Accept"];
        [generalManager.requestSerializer setAuthorizationHeaderFieldWithCredential:credentials];

        [generalManager GET:@"/2.0/folders/0/items" parameters:nil progress:nil success:^(NSURLSessionDataTask * _Nonnull task, id  _Nullable responseObject) {

            NSDictionary* responseDict = (NSDictionary*)responseObject;

            NSArray* items = responseDict[@"entries"];

            NSString* folderId = nil;
            for(NSDictionary* anItemDict in items) {
                if( [anItemDict[@"type"] isEqualToString:@"folder"] && [anItemDict[@"name"] isEqualToString:@"CargoLifter"] ) {
                    folderId = anItemDict[@"id"];
                    break;
                }
            }

            if( folderId ) {
                self.service.credentials[CLBoxFolderId] = folderId;
                completionBlock(nil);
            } else {
                // create folder
                NSDictionary* params = @{@"name":@"CargoLifter", @"parent":@{@"id":@"0"}};

                [generalManager POST:@"/2.0/folders" parameters:params progress:nil success:^(NSURLSessionDataTask * _Nonnull task, id  _Nullable responseObject) {
                    NSDictionary* responseDict = (NSDictionary*)responseObject;

                    NSString* folderId = responseDict[@"id"];

                    if( folderId ) {
                        self.service.credentials[CLBoxFolderId] = folderId;
                        completionBlock(nil);
                    } else {
                        NSError *error = [NSError errorWithDomain:CLUploaderErrorDomain code:CLUploaderErrorCreateDirectory userInfo:@{NSLocalizedDescriptionKey:NSLocalizedString(@"Could not create directory.", nil)}];

                        completionBlock(error);
                    }
                } failure:^(NSURLSessionDataTask * _Nullable task, NSError * _Nonnull error) {
                    completionBlock(error);
                }];
            }

        } failure:^(NSURLSessionDataTask * _Nullable task, NSError * _Nonnull error) {
            completionBlock(error);
        }];
    } failure:^(NSError *error) {
        completionBlock(error);
    }];
}

@end
