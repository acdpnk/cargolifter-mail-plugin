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
//  CLMediaFireUploader.m
//
//  Created by Fabian Jäger on 09.04.13.
//  Copyright (c) 2013 Mailbutler. All rights reserved.
//

#import "CLMediaFireUploader.h"

#import "NSString+CLAdditions.h"
#import "NSData+CLAdditions.h"

#import <AFNetworking/AFNetworking.h>

#define CLMediaFireFolderKey    @"CLMediafireFolderKey"

@interface CLMediaFireUploader (PRIVATE)
- (NSString*)_hashStringForEmail:(NSString*)email password:(NSString*)password;
- (void)_getTokenWithSuccess:(void (^)(NSString* sessionToken))successHandler withFailure:(void (^)(NSError* error))failureHandler;
@end

@implementation CLMediaFireUploader

- (NSString*)_hashStringForEmail:(NSString *)email password:(NSString *)password
{
    NSString* toBeHashed = [NSString stringWithFormat:@"%@%@%@%@", email, password, MEDIAFIRE_APP_ID, MEDIAFIRE_API_KEY];
    
    return [toBeHashed sha1_digest];
}

- (void)_getTokenWithSuccess:(void (^)(NSString* sessionToken))successHandler withFailure:(void (^)(NSError* error))failureHandler
{
    NSString* aLogin = self.service.login;
    NSString* aPassword = self.service.password;
    
    // first, get session token
    NSString* hashString = [self _hashStringForEmail:aLogin password:aPassword];
    NSDictionary* params = @{@"email":aLogin, @"password":aPassword, @"signature":hashString, @"application_id":MEDIAFIRE_APP_ID, @"response_format":@"json"};
    
    AFHTTPSessionManager *manager = [[AFHTTPSessionManager alloc] initWithBaseURL:[NSURL URLWithString:@"https://www.mediafire.com"]];
    manager.requestSerializer = [AFJSONRequestSerializer serializer];
    AFJSONResponseSerializer* jsonSerializer = [AFJSONResponseSerializer serializer];
    [jsonSerializer setRemovesKeysWithNullValues:YES];
    manager.responseSerializer = jsonSerializer;
    [manager.requestSerializer setValue:@"application/json" forHTTPHeaderField:@"Accept"];
    
    [manager GET:@"/api/user/get_session_token.php" parameters:params progress:nil success:^(NSURLSessionDataTask * _Nonnull task, id  _Nullable responseObject) {
        // we received our session token, use it in handler
        NSDictionary* responseDict = (NSDictionary*)responseObject;
        NSString* sessionToken = responseDict[@"response"][@"session_token"];
        
        if(successHandler)
            successHandler(sessionToken);
    } failure:^(NSURLSessionDataTask * _Nullable task, NSError * _Nonnull error) {
        // we failed!
        if( failureHandler )
            failureHandler(error);
    }];
}

- (void) uploadFile:(NSString*)localFilePath createPublicLink:(BOOL)createPublicLink rawFileAccess:(BOOL)rawFile
{
    if( self.busy )
        return;
    
    self.activeFile = localFilePath;
    self.busy = YES;
    self.canceled = NO;
    
    [self _getTokenWithSuccess:^(NSString *sessionToken) {
        
        NSURL* baseURL = [NSURL URLWithString:@"https://www.mediafire.com"];
        
        AFHTTPSessionManager *manager = [[AFHTTPSessionManager alloc] initWithBaseURL:baseURL];
        manager.requestSerializer = [AFJSONRequestSerializer serializer];
        manager.responseSerializer = [AFHTTPResponseSerializer serializer];
        [manager.requestSerializer setValue:@"application/json" forHTTPHeaderField:@"Accept"];
        
        // upload files via MediaFire
        NSString* fileName = localFilePath.lastPathComponent;
        
        // get mime type for file
        NSString *filename = localFilePath.lastPathComponent;
        NSData* fileData = [NSData dataWithContentsOfFile:localFilePath];
        NSString *mimeType = [self MIMETypeFileName:filename defaultMIMEType:@"binary/octet-stream"];
        
        // prepare upload
        NSString* folderKey = self.service.credentials[CLMediaFireFolderKey];
        
        NSString* requestpath = [NSString stringWithFormat:@"/api/upload/simple.php?session_token=%@&uploadkey=%@&action_on_duplicate=keep", sessionToken, folderKey];
        
        [manager POST:requestpath parameters:nil constructingBodyWithBlock:^(id<AFMultipartFormData>  _Nonnull formData) {
            [formData appendPartWithFileData:fileData name:@"Filedata" fileName:fileName mimeType:mimeType];
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
            
            NSString* xmlString = [[NSString alloc] initWithData:(NSData *)responseObject encoding:NSUTF8StringEncoding];
            
            NSXMLDocument* document = [[NSXMLDocument alloc] initWithXMLString:xmlString options:0 error:nil];
            NSLog(@"📯 CARGOLIFTER: UPLOAD SUCCESS: %@", [document rootElement].XMLString);
            
            NSArray* resultResponseArray = [document.rootElement nodesForXPath:@"/response/result" error:nil];
            NSString* resultResponse = (resultResponseArray.count)?[resultResponseArray[0] stringValue ]:nil;
            
            NSArray* resultValueArray = [document.rootElement nodesForXPath:@"/response/doupload/result" error:nil];
            NSString* resultValue = (resultValueArray.count)?[resultValueArray[0] stringValue ]:nil;
            
            NSArray* resultKeyArray = [document.rootElement nodesForXPath:@"/response/doupload/key" error:nil];
            NSString* resultKey = (resultKeyArray.count)?[resultKeyArray[0] stringValue ]:nil;
            
            // TODO: handle private upload
            if( [resultResponse isEqualToString:@"Success"] && resultKey.length )
            {
                // delay by 1 seconds to assure availability
                dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(1 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
                    NSInteger attempt = 0;
                    NSDictionary* quickKeyDict = nil;
                    NSString* quickKey = nil;
                    NSInteger uploadStatus = -1;
                    
                    do {
                        sleep(2);
                        
                        quickKeyDict = nil;
                        quickKey = nil;
                        
                        NSData* quickKeyData = [NSData dataWithContentsOfURL:[NSURL URLWithString:[NSString stringWithFormat:@"https://www.mediafire.com/api/upload/poll_upload.php?session_token=%@&key=%@&response_format=json", sessionToken, resultKey]]];
                        
                        quickKeyDict = [NSJSONSerialization JSONObjectWithData:quickKeyData options:kNilOptions error:nil];
                        quickKey = quickKeyDict[@"response"][@"doupload"][@"quickkey"];
                        
                        uploadStatus = [quickKeyDict[@"response"][@"doupload"][@"status"] integerValue];
                        
                    } while ( attempt < 3 && !(uploadStatus == 99 && quickKey.length) );
                    
                    
                    if( !(quickKey.length) )
                    {
                        NSLog(@"💥 CARGOLIFTER: QuickKey Error: %@", quickKeyDict);
                        
                        NSDictionary *errorDictionary = @{ NSLocalizedDescriptionKey :[NSString stringWithFormat:@"Failed to acquire quickKey with error: %@", quickKeyDict[@"response"][@"doupload"][@"result"]] };
                        NSError *error = [NSError errorWithDomain:CLUploaderErrorDomain code:CLUploaderErrorQuickKey userInfo:errorDictionary];
                        
                        self.busy = NO;
                        
                        if( [self.delegate respondsToSelector:@selector(uploadFailedWithStatus:withError:)] )
                            [self.delegate uploadFailedWithStatus:CLUploadError withError:error];
                        
                        return;
                    }
                    
                    NSData* downloadLinkData = [NSData dataWithContentsOfURL:[NSURL URLWithString:[NSString stringWithFormat:@"https://www.mediafire.com/api/file/get_links.php?link_type=direct_download&session_token=%@&quick_key=%@&response_format=json", sessionToken, quickKey]]];
                    NSDictionary* linkDict = [NSJSONSerialization JSONObjectWithData:downloadLinkData options:kNilOptions error:nil];
                    
                    NSArray* links = linkDict[@"response"][@"links"];
                    NSString* downloadLink = links.count?links[0][@"direct_download"]:nil;
                    
                    if(!downloadLink.length)
                    {
                        NSLog(@"💥 CARGOLIFTER: Download Link Error: %@", linkDict);
                        
                        self.busy = NO;
                        
                        NSDictionary *errorDictionary = @{ NSLocalizedDescriptionKey :[NSString stringWithFormat:@"Failed to acquire download link: %@", linkDict] };
                        NSError *error = [NSError errorWithDomain:CLUploaderErrorDomain code:CLUploaderErrorGetDownloadLink userInfo:errorDictionary];
                        
                        if( [self.delegate respondsToSelector:@selector(uploadFailedWithStatus:withError:)] )
                            [self.delegate uploadFailedWithStatus:CLUploadError withError:error];
                        
                        return;
                    }
                    
                    self.busy = NO;
                    
                    if( [self.delegate respondsToSelector:@selector(createdLink:forFile:withIconURL:)] )
                        [self.delegate createdLink:[NSURL URLWithString:downloadLink] forFile:localFilePath withIconURL:nil];
                });
            }
            else
            {
                NSDictionary *errorDictionary = @{ NSLocalizedDescriptionKey :[NSString stringWithFormat:@"Upload failed with Error: %@", resultValue] };
                NSError *error = [NSError errorWithDomain:CLUploaderErrorDomain code:CLUploaderErrorUnknownError userInfo:errorDictionary];
                
                self.busy = NO;
                
                if( [self.delegate respondsToSelector:@selector(uploadFailedWithStatus:withError:)] )
                    [self.delegate uploadFailedWithStatus:CLUploadError withError:error];
            }
        } failure:^(NSURLSessionDataTask * _Nullable task, NSError * _Nonnull error) {
            NSLog(@"💥 CARGOLIFTER: UPLOAD FAILURE: ");
            
            self.busy = NO;
            
            if( [self.delegate respondsToSelector:@selector(uploadFailedWithStatus:withError:)] )
                [self.delegate uploadFailedWithStatus:CLUploadError withError:error];
        }];
        
    } withFailure:^(NSError *error) {
        NSLog(@"💥 CARGOLIFTER: Error: %@", [error localizedDescription]);
        
        self.busy = NO;
        
        if( self.delegate && [self.delegate respondsToSelector:@selector(uploadFailedWithStatus:withError:)] )
            [self.delegate uploadFailedWithStatus:CLUploadError withError:error];
    }];
}

- (void) authenticate
{
    NSString* bundleName = PLUGIN_BUNDLE.infoDictionary[@"CFBundleName"];
    
    [self _getTokenWithSuccess:^(NSString *sessionToken) {
        
        AFHTTPSessionManager *manager = [[AFHTTPSessionManager alloc] initWithBaseURL:[NSURL URLWithString:@"https://www.mediafire.com"]];
        manager.requestSerializer = [AFJSONRequestSerializer serializer];
        AFJSONResponseSerializer* jsonSerializer = [AFJSONResponseSerializer serializer];
        [jsonSerializer setRemovesKeysWithNullValues:YES];
        manager.responseSerializer = jsonSerializer;
        [manager.requestSerializer setValue:@"application/json" forHTTPHeaderField:@"Accept"];
        
        self.service.linking = YES;
        
        // make sure that we have a directory
        NSDictionary* params = @{@"session_token":sessionToken, @"response_format":@"json", @"content_type":@"folders"};
        
        [manager GET:@"/api/folder/get_content.php" parameters:params progress:nil success:^(NSURLSessionDataTask * _Nonnull task, id  _Nullable responseObject) {
            
            NSDictionary* responseDict = (NSDictionary*)responseObject;
            
            NSArray* folders = responseDict[@"response"][@"folder_content"][@"folders"];
            
            NSString* folderKey = nil;
            for(NSDictionary* aFolderDict in folders)
            {
                if( [aFolderDict[@"name"] isEqualToString:bundleName] )
                {
                    folderKey = aFolderDict[@"folderkey"];
                    break;
                }
            }
            
            if( folderKey )
            {
                if( [self.authDelegate respondsToSelector:@selector(didFinishAuthenticationWithError:)] )
                    [self.authDelegate didFinishAuthenticationWithError:nil];
                
                self.service.credentials[CLMediaFireFolderKey] = folderKey;
                [self.service markAsLinked:YES];
            }
            else
            {
                // create folder
                NSDictionary* params = @{@"session_token":sessionToken, @"foldername":bundleName, @"response_format":@"json"};
                
                [manager GET:@"/api/folder/create.php" parameters:params progress:nil success:^(NSURLSessionDataTask * _Nonnull task, id  _Nullable responseObject) {
                    NSDictionary* responseDict = (NSDictionary*)responseObject;
                    
                    NSString* folderKey = responseDict[@"response"][@"folder_key"];
                    
                    if( folderKey )
                    {
                        if( [self.authDelegate respondsToSelector:@selector(didFinishAuthenticationWithError:)] )
                            [self.authDelegate didFinishAuthenticationWithError:nil];
                        
                        self.service.credentials[CLMediaFireFolderKey] = folderKey;
                        [self.service markAsLinked:YES];
                    }
                    else
                    {
                        NSDictionary *errorDictionary = @{ NSLocalizedDescriptionKey : NSLocalizedString(@"Could not create directory.", nil) };
                        NSError *error = [NSError errorWithDomain:CLServiceAuthErrorDomain code:CLServiceAuthErrorCreateDirectory userInfo:errorDictionary];
                        
                        if( [self.authDelegate respondsToSelector:@selector(didFinishAuthenticationWithError:)] )
                            [self.authDelegate didFinishAuthenticationWithError:error];
                        
                        [self.service markAsLinked:NO];
                    }
                } failure:^(NSURLSessionDataTask * _Nullable task, NSError * _Nonnull error) {
                    NSLog(@"💥 CARGOLIFTER: ERROR: %@", error);
                    
                    if( [self.authDelegate respondsToSelector:@selector(didFinishAuthenticationWithError:)] )
                        [self.authDelegate didFinishAuthenticationWithError:error];
                    
                    [self.service markAsLinked:NO];
                }];
            }
            
        } failure:^(NSURLSessionDataTask * _Nullable task, NSError * _Nonnull error) {
            NSLog(@"💥 CARGOLIFTER: ERROR: %@", error);
            
            if( [self.authDelegate respondsToSelector:@selector(didFinishAuthenticationWithError:)] )
                [self.authDelegate didFinishAuthenticationWithError:error];
            
            [self.service markAsLinked:NO];
        }];
        
    } withFailure:^(NSError *error) {
        
        if( [self.authDelegate respondsToSelector:@selector(didFinishAuthenticationWithError:)] )
            [self.authDelegate didFinishAuthenticationWithError:error];
        
        [self.service markAsLinked:NO];        
    }];   
}

@end
