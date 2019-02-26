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
//  CLCloudAppUploader.m
//
//  Created by Fabian Jäger on 09.04.13.
//  Copyright (c) 2013 Mailbutler. All rights reserved.
//

#import "CLCloudAppUploader.h"

#import "NSString+CLAdditions.h"
#import "NSData+CLAdditions.h"

#import <AFNetworking/AFNetworking.h>

@implementation CLCloudAppUploader

- (void) uploadFile:(NSString*)localFilePath createPublicLink:(BOOL)createPublicLink rawFileAccess:(BOOL)rawFile
{
    if( self.busy )
        return;
    
    self.activeFile = localFilePath;
    self.busy = YES;
    self.canceled = NO;
    
    // upload files via cloudapp (REST API)
    AFHTTPSessionManager *manager = [[AFHTTPSessionManager alloc] initWithBaseURL:[NSURL URLWithString:@"https://my.cl.ly"]];
    manager.requestSerializer = [AFHTTPRequestSerializer serializer];
    AFJSONResponseSerializer* jsonSerializer = [AFJSONResponseSerializer serializer];
    [jsonSerializer setRemovesKeysWithNullValues:YES];
    manager.responseSerializer = jsonSerializer;
    
    NSURLCredential* credentials = [[NSURLCredential alloc] initWithUser:self.service.login password:self.service.password persistence:NSURLCredentialPersistenceForSession];
    
    [manager setTaskDidReceiveAuthenticationChallengeBlock:^NSURLSessionAuthChallengeDisposition(NSURLSession * _Nonnull session, NSURLSessionTask * _Nonnull task, NSURLAuthenticationChallenge * _Nonnull challenge, NSURLCredential *__autoreleasing  _Nullable * _Nullable credential) {
        
        if (challenge.previousFailureCount == 0) {
            *credential = credentials;
            return NSURLSessionAuthChallengeUseCredential;
        } else {
            return NSURLSessionAuthChallengePerformDefaultHandling;
        }
        
    }];
    
    [manager POST:@"/v3/items/" parameters:@{@"name":localFilePath.lastPathComponent} progress:nil success:^(NSURLSessionDataTask * _Nonnull task, id  _Nullable responseObject) {
        
        NSDictionary* uploadDict = responseObject;
        
        if(!(uploadDict[@"s3"] && uploadDict[@"url"]))
        {
            self.busy = NO;
            
            NSError* error = [NSError errorWithDomain:CLUploaderErrorDomain code:CLUploaderErrorUnknownError userInfo:@{NSLocalizedDescriptionKey:NSLocalizedString(@"Could not fetch required parameters for file upload", nil)}];
            
            if( [self.delegate respondsToSelector:@selector(uploadFailedWithStatus:withError:)] )
                [self.delegate uploadFailedWithStatus:CLUploadError withError:error];
            
            return;
        }
        
        NSString* uploadURLString = uploadDict[@"url"];
        
        AFHTTPSessionManager *s3Manager = [[AFHTTPSessionManager alloc] initWithBaseURL:[[NSURL URLWithString:uploadURLString] baseURL]];
        s3Manager.requestSerializer = [AFHTTPRequestSerializer serializer];
        s3Manager.responseSerializer = jsonSerializer;
        
        NSMutableDictionary* uploadParams = [uploadDict[@"s3"] mutableCopy];
        NSMutableURLRequest* uploadRequest = [s3Manager.requestSerializer multipartFormRequestWithMethod:@"POST" URLString:uploadURLString parameters:uploadParams constructingBodyWithBlock:^(id<AFMultipartFormData>  _Nonnull formData) {
            NSString *filename = localFilePath.lastPathComponent;
            NSData* fileData = [NSData dataWithContentsOfFile:localFilePath];
            NSString *mimeType = [self MIMETypeFileName:filename defaultMIMEType:@"binary/octet-stream"];
            
            [formData appendPartWithFileData:fileData name:@"file" fileName:filename mimeType:mimeType];
        } error:nil];
        
        [[s3Manager dataTaskWithRequest:uploadRequest uploadProgress:^(NSProgress * _Nonnull uploadProgress) {
            
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
            
        } downloadProgress:nil completionHandler:^(NSURLResponse * _Nonnull response, id  _Nullable responseObject, NSError * _Nullable error) {
            
            if(error)
            {
                self.busy = NO;
                
                if( [self.delegate respondsToSelector:@selector(uploadFailedWithStatus:withError:)] )
                    [self.delegate uploadFailedWithStatus:CLUploadError withError:error];
            }
            else
            {
                // get information of newly uploaded file
                NSDictionary* fileDict = responseObject;
                
                if(!fileDict[@"content_url"])
                {
                    self.busy = NO;
                    
                    error = [NSError errorWithDomain:CLUploaderErrorDomain code:CLUploaderErrorUnknownError userInfo:@{NSLocalizedDescriptionKey:NSLocalizedString(@"Could not fetch required parameters for file upload", nil)}];
                    
                    if( [self.delegate respondsToSelector:@selector(uploadFailedWithStatus:withError:)] )
                        [self.delegate uploadFailedWithStatus:CLUploadError withError:error];
                    
                    return;
                }
                
                NSString* shareURLString = fileDict[@"content_url"];
                if(rawFile && fileDict[@"remote_url"])
                    shareURLString = fileDict[@"remote_url"];
                
                self.busy = NO;
                
                if( self.delegate && [self.delegate respondsToSelector:@selector(createdLink:forFile:withIconURL:)] )
                    [self.delegate createdLink:[NSURL URLWithString:shareURLString] forFile:localFilePath withIconURL:nil];
            }
            
        }] resume];
        
    } failure:^(NSURLSessionDataTask * _Nullable task, NSError * _Nonnull error) {
        
        self.busy = NO;
        
        if( [self.delegate respondsToSelector:@selector(uploadFailedWithStatus:withError:)] )
            [self.delegate uploadFailedWithStatus:CLUploadError withError:error];
        
    }];
}

- (void) authenticate
{
    self.service.linking = YES;
    
    AFHTTPSessionManager *manager = [[AFHTTPSessionManager alloc] initWithBaseURL:[NSURL URLWithString:@"https://my.cl.ly"]];
    manager.requestSerializer = [AFHTTPRequestSerializer serializer];
    AFJSONResponseSerializer* jsonSerializer = [AFJSONResponseSerializer serializer];
    [jsonSerializer setRemovesKeysWithNullValues:YES];
    manager.responseSerializer = jsonSerializer;
    
    NSURLCredential* credentials = [[NSURLCredential alloc] initWithUser:self.service.login password:self.service.password persistence:NSURLCredentialPersistenceForSession];
    
    [manager setTaskDidReceiveAuthenticationChallengeBlock:^NSURLSessionAuthChallengeDisposition(NSURLSession * _Nonnull session, NSURLSessionTask * _Nonnull task, NSURLAuthenticationChallenge * _Nonnull challenge, NSURLCredential *__autoreleasing  _Nullable * _Nullable credential) {
        
        if (challenge.previousFailureCount == 0) {
            *credential = credentials;
            return NSURLSessionAuthChallengeUseCredential;
        } else {
            return NSURLSessionAuthChallengePerformDefaultHandling;
        }
        
    }];
    
    [manager GET:@"/v3/items" parameters:nil progress:nil success:^(NSURLSessionDataTask * _Nonnull task, id  _Nullable responseObject) {
        
        if( [self.authDelegate respondsToSelector:@selector(didFinishAuthenticationWithError:)] )
            [self.authDelegate didFinishAuthenticationWithError:nil];
        
        [self.service markAsLinked:YES];
        
    } failure:^(NSURLSessionDataTask * _Nullable task, NSError * _Nonnull error) {
        
        if( [self.authDelegate respondsToSelector:@selector(didFinishAuthenticationWithError:)] )
            [self.authDelegate didFinishAuthenticationWithError:error];
        
        [self.service markAsLinked:NO];
        
    }];
}

@end
