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
//  CLOwnCloudUploader.m
//
//  Created by Fabian Jäger on 09.04.13.
//  Copyright (c) 2013 Mailbutler. All rights reserved.
//

#import "CLOwnCloudUploader.h"

#import "NSString+CLAdditions.h"
#import "NSData+CLAdditions.h"

#import <AFNetworking/AFNetworking.h>

#define CLOwnCloudURL               @"CLOwnCloudURL"
#define CLOwnCloudDirectoryName     @"CLOwnCloudDirectoryName"
#define CLOwnCloudDownloadSuffix    @"CLOwnCloudDownloadSuffix"

@interface CLOwnCloudUploader ()
- (BOOL) isValidURL:(NSURL*)testURL;
@end

@implementation CLOwnCloudUploader

- (BOOL) isValidURL:(NSURL *)testURL
{
    NSURLRequest* request = [NSURLRequest requestWithURL:testURL];
    NSURLResponse* response;
    NSError* error;
    
    [NSURLConnection sendSynchronousRequest:request returningResponse:&response error:&error];
    
    // you can use retVal, ignore if you don't need.
    NSInteger httpStatus = [response isKindOfClass:[NSHTTPURLResponse class]]?[((NSHTTPURLResponse *)response) statusCode]:400;
    
    return (httpStatus == 200);
}

- (void) _uploadLocalFile:(NSString*)localFilePath createPublicLink:(BOOL)createPublicLink rawFileAccess:(BOOL)rawFile fileIdx:( NSUInteger)fileIdx
{
    NSString* remoteFileName = localFilePath.lastPathComponent;
    
    if( fileIdx > 0 )
    {
        NSString* fileExtension = remoteFileName.pathExtension;
        NSString* fileNameWithoutExtension = remoteFileName.stringByDeletingPathExtension;
        remoteFileName = [NSString stringWithFormat:@"%@-%ld.%@", fileNameWithoutExtension, fileIdx, fileExtension];
    }
    
    // upload files via ownCloud
    NSString* aLogin = self.service.login;
    NSString* aPassword = self.service.password;
    
    NSString* directoryName = self.service.credentials[CLOwnCloudDirectoryName];
    if ( directoryName.length == 0)
    {
        NSString* bundleName = PLUGIN_BUNDLE.infoDictionary[@"CFBundleName"];
        directoryName = bundleName;
    }
    
    NSString* remoteURLString = self.service.credentials[CLOwnCloudURL];
    remoteURLString = [remoteURLString stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]];
    
    NSURL* remoteURL = [NSURL URLWithString:remoteURLString];
    
    NSString* remotePath = [remoteURL.path copy];
    while( remoteURL.path.length > 1 )
        remoteURL = [remoteURL URLByDeletingLastPathComponent];
    
    AFHTTPSessionManager *uploadManager = [[AFHTTPSessionManager alloc] initWithBaseURL:remoteURL];
    uploadManager.responseSerializer = [AFHTTPResponseSerializer serializer];
    [uploadManager.requestSerializer setAuthorizationHeaderFieldWithUsername:aLogin password:aPassword];
    [uploadManager.requestSerializer setValue:@"true" forHTTPHeaderField:@"OCS-APIRequest"];
    
    // important as ownCloud does not allow multiple connections
    [uploadManager.requestSerializer setHTTPShouldHandleCookies:NO];
    [[uploadManager operationQueue] setMaxConcurrentOperationCount:1];
    
    // check if remote file with this name exists already
    NSString* filePath = [directoryName stringByAppendingPathComponent:[remoteFileName urlEncodedPathString]];
    NSString* uploadFilePath = [[remotePath stringByAppendingPathComponent:@"remote.php/webdav"] stringByAppendingPathComponent:filePath];
    
    [uploadManager GET:uploadFilePath parameters:nil progress:nil success:^(NSURLSessionDataTask * _Nonnull task, id  _Nullable responseObject) {
        // try again with another fileIdx
        [self _uploadLocalFile:localFilePath createPublicLink:createPublicLink rawFileAccess:rawFile fileIdx:(fileIdx+1)];
    } failure:^(NSURLSessionDataTask * _Nullable task, NSError * _Nonnull error) {
        
        NSHTTPURLResponse* urlResponse = error.userInfo[AFNetworkingOperationFailingURLResponseErrorKey];
        // check error and react accordingly
        if( urlResponse.statusCode == 404 ) // not found, good! :-)
        {
            NSString *filename = localFilePath.lastPathComponent;
            NSString *mimeType = [self MIMETypeFileName:filename defaultMIMEType:@"binary/octet-stream"];
            
            // let's start the actual upload
            NSString* uploadURLString = [remoteURL.absoluteString stringByAppendingPathComponent:uploadFilePath];
            NSMutableURLRequest* uploadRequest = [uploadManager.requestSerializer requestWithMethod:@"PUT" URLString:uploadURLString parameters:nil error:nil];
            
            [uploadRequest setCachePolicy:NSURLRequestReloadIgnoringLocalCacheData];
            uploadRequest.HTTPBody = [NSData dataWithContentsOfFile:localFilePath];
            [uploadRequest setValue:mimeType forHTTPHeaderField:@"Content-Type"];
            
            [[uploadManager dataTaskWithRequest:uploadRequest uploadProgress:^(NSProgress * _Nonnull uploadProgress) {
                
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
                
                if(error == nil)
                {
                    //NSLog(@"📯 CARGOLIFTER: Upload Response: %@", responseObject);
                    
                    if( createPublicLink )
                    {
                        // create share link
                        NSString* shareFilePath = [directoryName stringByAppendingPathComponent:remoteFileName];
                        NSDictionary* shareParams = @{@"path":shareFilePath, @"shareType":@3};
                        NSString* shareAPI = [remotePath stringByAppendingPathComponent:@"ocs/v1.php/apps/files_sharing/api/v1/shares"];
                        
                        [uploadManager POST:shareAPI parameters:shareParams progress:nil success:^(NSURLSessionDataTask * _Nonnull task, id  _Nullable responseObject) {
                            
                            //NSLog(@"📯 CARGOLIFTER: Share Response: %@", responseObject);
                            NSXMLDocument* aDoc = [[NSXMLDocument alloc] initWithData:responseObject options:0 error:nil];
                            NSArray* urlNodes = [aDoc nodesForXPath:@"//url" error:nil];
                            if( urlNodes.count == 1 )
                            {
                                NSXMLNode* urlNode = urlNodes[0];
                                NSString* shareLink = urlNode.stringValue;
                                
                                if(rawFile)
                                {
                                    // allow direct download
                                    NSString* downloadSuffix = self.service.credentials[CLOwnCloudDownloadSuffix];
                                    if(downloadSuffix)
                                        shareLink = [shareLink stringByAppendingString:downloadSuffix];
                                }
                                
                                self.busy = NO;
                                if( [self.delegate respondsToSelector:@selector(createdLink:forFile:withIconURL:)] )
                                    [self.delegate createdLink:[NSURL URLWithString:shareLink] forFile:localFilePath withIconURL:nil];
                            }
                            else
                            {
                                // unknown error occured
                                NSDictionary *errorDictionary = @{ NSLocalizedDescriptionKey : NSLocalizedString(@"Unknown problem during share creation.", nil) };
                                NSError *error = [NSError errorWithDomain:CLUploaderErrorDomain code:CLUploaderErrorUnknownError userInfo:errorDictionary];
                                self.busy = NO;
                                if( [self.delegate respondsToSelector:@selector(uploadFailedWithStatus:withError:)] )
                                    [self.delegate uploadFailedWithStatus:CLUploadError withError:error];
                            }
                            
                        } failure:^(NSURLSessionDataTask * _Nullable task, NSError * _Nonnull error) {
                            
                            NSLog(@"💥 CARGOLIFTER: Share ERROR: %@", error);
                            
                            // unknown error occured
                            self.busy = NO;
                            if( [self.delegate respondsToSelector:@selector(uploadFailedWithStatus:withError:)] )
                                [self.delegate uploadFailedWithStatus:CLUploadError withError:error];
                            
                        }];
                    }
                    else
                    {
                        NSString* finalURL = [remoteURLString stringByAppendingPathComponent:directoryName];
                        finalURL = [finalURL stringByAppendingPathComponent:[remoteFileName urlEncodedPathString]];
                        
                        self.busy = NO;
                        if( [self.delegate respondsToSelector:@selector(createdLink:forFile:withIconURL:)] )
                            [self.delegate createdLink:[NSURL URLWithString:finalURL] forFile:localFilePath withIconURL:nil];
                    }
                }
                else
                {
                    NSLog(@"💥 CARGOLIFTER: Upload ERROR: %@", error);
                    
                    // unknown error occured
                    self.busy = NO;
                    if( [self.delegate respondsToSelector:@selector(uploadFailedWithStatus:withError:)] )
                        [self.delegate uploadFailedWithStatus:CLUploadError withError:error];
                }
                
            }] resume];
        }
        else
        {
            // unknown error occured
            self.busy = NO;
            if( [self.delegate respondsToSelector:@selector(uploadFailedWithStatus:withError:)] )
                [self.delegate uploadFailedWithStatus:CLUploadError withError:error];
        }
    }];
}

- (void) uploadFile:(NSString*)localFilePath createPublicLink:(BOOL)createPublicLink rawFileAccess:(BOOL)rawFile
{
    if( self.busy )
        return;
    
    self.activeFile = localFilePath;
    self.busy = YES;
    self.canceled = NO;
    
    [self _uploadLocalFile:localFilePath createPublicLink:createPublicLink rawFileAccess:rawFile fileIdx:0];
}

- (void) authenticate
{
    NSString* aLogin = self.service.login;
    NSString* aPassword = self.service.password;
    
    NSString* directoryName = self.service.credentials[CLOwnCloudDirectoryName];
    if ( directoryName.length == 0)
    {
        NSString* bundleName = PLUGIN_BUNDLE.infoDictionary[@"CFBundleName"];
        directoryName = bundleName;
    }
    
    // check if base dir for file upload exists
    NSString* remoteURLString = self.service.credentials[CLOwnCloudURL];
    remoteURLString = [remoteURLString stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]];
    
    NSURL* remoteURL = [NSURL URLWithString:remoteURLString];
    
    NSString* remotePath = [remoteURL.path copy];
    while( remoteURL.path.length > 1 )
        remoteURL = [remoteURL URLByDeletingLastPathComponent];
    
    // TODO: handle self-signed certificates correctly
    AFHTTPSessionManager *authManager = [[AFHTTPSessionManager alloc] initWithBaseURL:remoteURL];
    authManager.responseSerializer = [AFHTTPResponseSerializer serializer];
    [authManager.requestSerializer setAuthorizationHeaderFieldWithUsername:aLogin password:aPassword];
    [authManager.requestSerializer setValue:@"true" forHTTPHeaderField:@"OCS-APIRequest"];
    
    // important as ownCloud does not allow multiple connections
    [authManager.requestSerializer setHTTPShouldHandleCookies:NO];
    [[authManager operationQueue] setMaxConcurrentOperationCount:1];
    
    NSString* getPath = [remotePath stringByAppendingPathComponent:[NSString stringWithFormat:@"remote.php/webdav/%@", directoryName]];
    
    self.service.linking = YES;
    
    // check for directory first
    [authManager GET:getPath parameters:nil progress:nil success:^(NSURLSessionDataTask * _Nonnull task, id  _Nullable responseObject) {
        
        NSLog(@"📯 CARGOLIFTER: GET Response: %@", responseObject);
        
        // upload dummy file to the directory
        NSData* dummyData = [NSData randomDataWithBytes:4];
        NSString* dummyPath = [getPath stringByAppendingPathComponent:@"CargoLifter.dat"];
        NSString* uploadURLString = [remoteURL.absoluteString stringByAppendingPathComponent:dummyPath];
        NSMutableURLRequest* uploadRequest = [authManager.requestSerializer requestWithMethod:@"PUT" URLString:uploadURLString parameters:nil error:nil];
        
        [uploadRequest setValue:@"4" forHTTPHeaderField:@"Content-Length"];
        [uploadRequest setCachePolicy:NSURLRequestReloadIgnoringLocalCacheData];
        
        [[authManager uploadTaskWithRequest:uploadRequest fromData:dummyData progress:nil completionHandler:^(NSURLResponse * _Nonnull response, id  _Nullable responseObject, NSError * _Nullable error) {
            
            if(error.userInfo[AFNetworkingOperationFailingURLResponseDataErrorKey]) {
                NSString* errorResponse = [[NSString alloc] initWithData:(NSData *)error.userInfo[AFNetworkingOperationFailingURLResponseDataErrorKey] encoding:NSUTF8StringEncoding];
                
                error = [NSError errorWithDomain:CLCargoLifterErrorDomain code:error.code userInfo:@{NSLocalizedDescriptionKey:errorResponse}];
            }
            
            if(error == nil)
            {
                NSLog(@"📯 CARGOLIFTER: Upload Response: %@", responseObject);
                
                // create share link
                NSString* shareFilePath = [directoryName stringByAppendingPathComponent:@"CargoLifter.dat"];
                NSDictionary* shareParams = @{@"path":shareFilePath, @"shareType":@3};
                NSString* shareAPI = [remotePath stringByAppendingPathComponent:@"ocs/v1.php/apps/files_sharing/api/v1/shares"];
                
                [authManager POST:shareAPI parameters:shareParams progress:nil success:^(NSURLSessionDataTask * _Nonnull task, id  _Nullable responseObject) {
                    
                    NSLog(@"📯 CARGOLIFTER: Share Response: %@", responseObject);
                    NSXMLDocument* aDoc = [[NSXMLDocument alloc] initWithData:responseObject options:0 error:nil];
                    NSArray* urlNodes = [aDoc nodesForXPath:@"//url" error:nil];
                    if( urlNodes.count == 1 )
                    {
                        NSXMLNode* urlNode = urlNodes[0];
                        NSString* shareLink = urlNode.stringValue;
                        
                        // try with download link for version 8
                        if([self isValidURL:[NSURL URLWithString:[shareLink stringByAppendingString:@"/download"]]])
                            self.service.credentials[CLOwnCloudDownloadSuffix] = @"/download";
                        else if([self isValidURL:[NSURL URLWithString:[shareLink stringByAppendingString:@"&download"]]])
                            self.service.credentials[CLOwnCloudDownloadSuffix] = @"&download";
                        
                        // delete file now
                        [authManager DELETE:dummyPath parameters:nil success:^(NSURLSessionDataTask * _Nonnull task, id  _Nullable responseObject) {
                            
                            // everything successful
                            if( [self.authDelegate respondsToSelector:@selector(didFinishAuthenticationWithError:)] )
                                [self.authDelegate didFinishAuthenticationWithError:nil];
                            
                            [self.service markAsLinked:YES];
                            
                        } failure:^(NSURLSessionDataTask * _Nullable task, NSError * _Nonnull error) {
                            
                            NSLog(@"💥 CARGOLIFTER: ERROR: %@", error);
                            // unknown error occured
                            if( [self.authDelegate respondsToSelector:@selector(didFinishAuthenticationWithError:)] )
                                [self.authDelegate didFinishAuthenticationWithError:error];
                            
                            [self.service markAsLinked:NO];
                            
                        }];
                    }
                    else
                    {
                        NSDictionary *errorDictionary;
                        
                        NSString* status = [[[aDoc nodesForXPath:@"//status" error:nil] firstObject] stringValue];
                        NSString* message = [[[aDoc nodesForXPath:@"//message" error:nil] firstObject] stringValue];
                        
                        if([status isEqualToString:@"failure"] && message) {
                            errorDictionary = @{ NSLocalizedDescriptionKey : message };
                        } else {
                            // unknown error occured
                            errorDictionary = @{ NSLocalizedDescriptionKey : NSLocalizedString(@"Unknown problem during share creation.", nil) };
                        }
                        
                        NSError *error = [NSError errorWithDomain:CLUploaderErrorDomain code:CLUploaderErrorUnknownError userInfo:errorDictionary];
                        
                        // unknown error occured
                        if( [self.authDelegate respondsToSelector:@selector(didFinishAuthenticationWithError:)] )
                            [self.authDelegate didFinishAuthenticationWithError:error];
                        
                        [self.service markAsLinked:NO];
                    }
                    
                } failure:^(NSURLSessionDataTask * _Nullable task, NSError * _Nonnull error) {
                    
                    NSLog(@"💥 CARGOLIFTER: Share ERROR: %@", error);
                    
                    // unknown error occured
                    if( [self.authDelegate respondsToSelector:@selector(didFinishAuthenticationWithError:)] )
                        [self.authDelegate didFinishAuthenticationWithError:error];
                    
                    [self.service markAsLinked:NO];
                    
                }];
            }
            else
            {
                NSLog(@"💥 CARGOLIFTER: ERROR: %@", error);
                // unknown error occured
                if( [self.authDelegate respondsToSelector:@selector(didFinishAuthenticationWithError:)] )
                    [self.authDelegate didFinishAuthenticationWithError:error];
                
                [self.service markAsLinked:NO];
            }
            
        }] resume];
        
    } failure:^(NSURLSessionDataTask * _Nullable task, NSError * _Nonnull error) {
        
        NSLog(@"💥 CARGOLIFTER: ERROR: %@", error);
        
        // check error and react accordingly
        NSHTTPURLResponse* urlResponse = error.userInfo[AFNetworkingOperationFailingURLResponseErrorKey];
        if( urlResponse.statusCode == 404 ) // not found, good!
        {
            // we need to create our folder first
            NSString* newDirURLString = [remoteURL.absoluteString stringByAppendingPathComponent:getPath];
            NSMutableURLRequest *createRequest = [authManager.requestSerializer requestWithMethod:@"MKCOL" URLString:newDirURLString parameters:nil error:nil];
            
            [[authManager dataTaskWithRequest:createRequest completionHandler:^(NSURLResponse * _Nonnull response, id  _Nullable responseObject, NSError * _Nullable error) {
                
                if(error == nil)
                {
                    NSLog(@"📯 CARGOLIFTER: Create Directory Response: %@", responseObject);
                    
                    // directory should be available now ... let's try to authenticate again
                    [self authenticate];
                }
                else
                {
                    NSLog(@"💥 CARGOLIFTER: ERROR: %@", error);
                    // unknown error occured
                    if( [self.authDelegate respondsToSelector:@selector(didFinishAuthenticationWithError:)] )
                        [self.authDelegate didFinishAuthenticationWithError:error];
                    
                    [self.service markAsLinked:NO];
                }
                
            }] resume];
        }
        else
        {
            // unknown error occured
            if( [self.authDelegate respondsToSelector:@selector(didFinishAuthenticationWithError:)] )
                [self.authDelegate didFinishAuthenticationWithError:error];
            
            [self.service markAsLinked:NO];
        }
        
    }];
}

@end
