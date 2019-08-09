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
//  CLOneDriveUploader.m
//  CargoLifter
//
//  Created by Fabian Jäger on 01/09/16.
//  Copyright © 2016 Mailbutler. All rights reserved.
//

#import "CLOneDriveUploader.h"

#import "NSString+CLAdditions.h"

#import "AFOAuth2Manager.h"

#define CLOneDriveAuthBaseURL        @"https://login.microsoftonline.com"
#define CLOneDriveBaseURL            @"https://graph.microsoft.com"

#define CLOneDriveRedirectURL        @"https://cargolifter.mailbutler.io/onedrive"

#define CLOneDrivePartSize          (327680*4)

@implementation CLOneDriveUploader

- (NSString*) clientID { return ONEDRIVE_APP_ID; }
- (NSString*) clientSecret { return ONEDRIVE_PRIVATE_KEY; }
- (NSURL*) oauthStartURL { return [NSURL URLWithString:[NSString stringWithFormat:@"https://login.microsoftonline.com/common/oauth2/v2.0/authorize?client_id=%@&scope=%@&response_type=code&redirect_uri=%@", self.clientID, [@"offline_access files.readwrite" urlEncodedQueryString], [CLOneDriveRedirectURL urlEncodedQueryString]]]; }
- (NSURL*) redirectURL { return [NSURL URLWithString:CLOneDriveRedirectURL]; }
- (NSURL*) authBaseURL { return [NSURL URLWithString:CLOneDriveAuthBaseURL]; }
- (NSString*) getTokenPath { return @"/common/oauth2/v2.0/token"; }
- (NSString*) refreshTokenPath { return @"/common/oauth2/v2.0/token"; }

- (void) uploadFile:(NSString*)localFilePath createPublicLink:(BOOL)createPublicLink rawFileAccess:(BOOL)rawFile {
    if( self.busy )
        return;
    
    self.activeFile = localFilePath;
    self.busy = YES;
    self.canceled = NO;
    
    [self _refreshAccessTokenWithSuccess:^{
        [self checkForCargoLifterFolderWithCompletionBlock:^(NSError *error) {
            if(error) {
                NSLog(@"💥 CARGOLIFTER: UPLOAD FAILURE: %@", error);
                self.busy = NO;

                if( [self.delegate respondsToSelector:@selector(uploadFailedWithStatus:withError:)] )
                    [self.delegate uploadFailedWithStatus:CLUploadError withError:error];
            } else {
                // use new access token
                AFOAuthCredential* credentials = [AFOAuthCredential retrieveCredentialWithIdentifier:self.service.uniqueIdentifier];

                // upload files via OneDrive
                NSString* fileName = [@"CargoLifter" stringByAppendingPathComponent:localFilePath.lastPathComponent];
                NSString* apiPath = [NSString stringWithFormat:@"/v1.0/me/drive/root:/%@:/createUploadSession", [fileName urlEncodedPathString]];

                AFHTTPSessionManager *generalManager = [[AFHTTPSessionManager alloc] initWithBaseURL:[NSURL URLWithString:CLOneDriveBaseURL]];
                generalManager.requestSerializer = [AFJSONRequestSerializer serializer];
                AFJSONResponseSerializer* jsonSerializer = [AFJSONResponseSerializer serializer];
                [jsonSerializer setRemovesKeysWithNullValues:YES];
                generalManager.responseSerializer = jsonSerializer;
                [generalManager.requestSerializer setValue:@"application/json" forHTTPHeaderField:@"Accept"];
                [generalManager.requestSerializer setAuthorizationHeaderFieldWithCredential:credentials];

                NSDictionary* params = @{
                                         @"@microsoft.graph.conflictBehavior": @"rename",
                                         @"name": localFilePath.lastPathComponent
                                         };

                [generalManager POST:apiPath parameters:params progress:nil success:^(NSURLSessionDataTask * _Nonnull task, id  _Nullable responseObject) {
                    NSDictionary* responseDict = (NSDictionary*)responseObject;
                    NSString* uploadURLString = responseDict[@"uploadUrl"];

                    // start uploading parts
                    NSData* fileData = [NSData dataWithContentsOfFile:localFilePath];
                    [self uploadPart:0 ofData:fileData atPath:localFilePath toURL:uploadURLString withHandler:^(NSString *fileID, NSError *error) {
                        if(error) {
                            NSLog(@"💥 CARGOLIFTER: UPLOAD FAILURE: %@", error);
                            self.busy = NO;

                            if( [self.delegate respondsToSelector:@selector(uploadFailedWithStatus:withError:)] )
                                [self.delegate uploadFailedWithStatus:CLUploadError withError:error];
                        } else {
                            NSLog(@"📯 CARGOLIFTER: UPLOAD SUCCESS:");

                            // make file shareable and get link
                            NSString* apiPath = [NSString stringWithFormat:@"/v1.0/me/drive/items/%@/createLink", fileID];
                            [generalManager POST:apiPath parameters:@{@"type":@"view"} progress:nil success:^(NSURLSessionDataTask * _Nonnull task, id  _Nullable responseObject) {
                                NSDictionary* responseDict = (NSDictionary*)responseObject;

                                NSString* uploadURLString = responseDict[@"link"][@"webUrl"];

                                self.busy = NO;

                                if( [self.delegate respondsToSelector:@selector(createdLink:forFile:withIconURL:)] )
                                    [self.delegate createdLink:[NSURL URLWithString:uploadURLString] forFile:localFilePath withIconURL:nil];
                            } failure:^(NSURLSessionDataTask * _Nullable task, NSError * _Nonnull error) {
                                NSLog(@"💥 CARGOLIFTER: SHARING FAILURE: %@", error);

                                self.busy = NO;

                                if( [self.delegate respondsToSelector:@selector(uploadFailedWithStatus:withError:)] )
                                    [self.delegate uploadFailedWithStatus:CLUploadError withError:error];
                            }];
                        }
                    }];
                } failure:^(NSURLSessionDataTask * _Nullable task, NSError * _Nonnull error) {
                    NSLog(@"💥 CARGOLIFTER: UPLOAD FAILURE: %@", error);
                    self.busy = NO;

                    if( [self.delegate respondsToSelector:@selector(uploadFailedWithStatus:withError:)] )
                        [self.delegate uploadFailedWithStatus:CLUploadError withError:error];
                }];
            }
        }];
    } failure:^(NSError *error) {
        
        self.busy = NO;
        
        if( [self.delegate respondsToSelector:@selector(uploadFailedWithStatus:withError:)] )
            [self.delegate uploadFailedWithStatus:CLUploadError withError:error];
    }];
}

- (void) uploadPart:(NSUInteger)partNumber ofData:(NSData*)fileData atPath:(NSString*)localFilePath toURL:(NSString*)uploadURLString withHandler:(void (^)(NSString* fileID, NSError *error))completionBlock {
    NSURL* baseURL = [[NSURL URLWithString:uploadURLString] baseURL];
    AFHTTPSessionManager *partUploadManager = [[AFHTTPSessionManager alloc] initWithBaseURL:baseURL];
    AFJSONResponseSerializer* jsonSerializer = [AFJSONResponseSerializer serializer];
    [jsonSerializer setRemovesKeysWithNullValues:YES];
    partUploadManager.responseSerializer = jsonSerializer;
    [partUploadManager.requestSerializer setValue:@"application/json" forHTTPHeaderField:@"Accept"];

    NSUInteger fileSize = fileData.length;
    NSUInteger uploadedSize = partNumber > 0 ? MIN(partNumber*CLOneDrivePartSize, fileSize) : 0;
    NSUInteger remainingSize = MAX(0, fileSize - uploadedSize);
    NSUInteger partSize = MIN(remainingSize, CLOneDrivePartSize);

    NSUInteger fileOffset = partNumber*CLOneDrivePartSize;
    NSString* contentRange = [NSString stringWithFormat:@"bytes %lu-%lu/%lu", (unsigned long)fileOffset, fileOffset+partSize-1, (unsigned long)fileSize];

    [partUploadManager.requestSerializer setValue:contentRange forHTTPHeaderField:@"Content-Range"];
    [partUploadManager.requestSerializer setValue:[NSString stringWithFormat:@"%lu", partSize] forHTTPHeaderField:@"Content-Length"];

    NSMutableURLRequest* uploadRequest = [partUploadManager.requestSerializer requestWithMethod:@"PUT" URLString:uploadURLString parameters:nil error:nil];
    uploadRequest.HTTPBody = [fileData subdataWithRange:NSMakeRange(fileOffset, partSize)];

    [[partUploadManager dataTaskWithRequest:uploadRequest uploadProgress:^(NSProgress * _Nonnull uploadProgress) {
        if(self.canceled) {
            [uploadProgress cancel];
            self.busy = NO;
            return;
        }

        CGFloat totalFraction = ((CGFloat)uploadedSize + uploadProgress.fractionCompleted * (CGFloat)partSize) / (CGFloat)fileSize;
        dispatch_async(dispatch_get_main_queue(), ^{
            if( [self.delegate respondsToSelector:@selector(uploadProgress:forFile:)] )
                [self.delegate uploadProgress:totalFraction forFile:localFilePath];
        });
    } downloadProgress:nil completionHandler:^(NSURLResponse * _Nonnull response, id  _Nullable responseObject, NSError * _Nullable error) {
        if(error) {
            completionBlock(nil, error);
        } else if([(NSHTTPURLResponse*)response statusCode] == 202) {
            // next part
            [self uploadPart:partNumber+1 ofData:fileData atPath:localFilePath toURL:uploadURLString withHandler:completionBlock];
        } else if([(NSHTTPURLResponse*)response statusCode] == 201) {
            NSDictionary* responseDict = (NSDictionary*)responseObject;
            completionBlock(responseDict[@"id"], nil);
        }
    }] resume];
}

- (void) postAuthenticationHookWithHandler:(void (^)(NSError *error))completionBlock {
    [self checkForCargoLifterFolderWithCompletionBlock:completionBlock];
}

#pragma mark Private Methods

- (void) checkForCargoLifterFolderWithCompletionBlock:(void (^)(NSError *error))completionBlock {
    [self _refreshAccessTokenWithSuccess:^{
        AFOAuthCredential* credentials = [AFOAuthCredential retrieveCredentialWithIdentifier:self.service.uniqueIdentifier];

        AFHTTPSessionManager *generalManager = [[AFHTTPSessionManager alloc] initWithBaseURL:[NSURL URLWithString:CLOneDriveBaseURL]];
        generalManager.requestSerializer = [AFJSONRequestSerializer serializer];
        AFJSONResponseSerializer* jsonSerializer = [AFJSONResponseSerializer serializer];
        [jsonSerializer setRemovesKeysWithNullValues:YES];
        generalManager.responseSerializer = jsonSerializer;
        [generalManager.requestSerializer setValue:@"application/json" forHTTPHeaderField:@"Accept"];
        [generalManager.requestSerializer setAuthorizationHeaderFieldWithCredential:credentials];

        [generalManager GET:@"/v1.0/me/drive/root:/CargoLifter" parameters:nil progress:nil success:^(NSURLSessionDataTask * _Nonnull task, id  _Nullable responseObject) {
            completionBlock(nil);
        } failure:^(NSURLSessionDataTask * _Nullable task, NSError * _Nonnull error) {
            // create folder
            NSDictionary* params = @{@"name":@"CargoLifter", @"folder": @{}};

            [generalManager POST:@"/v1.0/me/drive/root/children" parameters:params progress:nil success:^(NSURLSessionDataTask * _Nonnull task, id  _Nullable responseObject) {
                completionBlock(nil);
            } failure:^(NSURLSessionDataTask * _Nullable task, NSError * _Nonnull error) {
                completionBlock(error);
            }];
        }];
    } failure:^(NSError *error) {
        completionBlock(error);
    }];
}

- (NSString *)MIMETypeFileName:(NSString *)path defaultMIMEType:(NSString *)defaultType {
    NSString *result = defaultType;
    NSString *extension = path.pathExtension;
    CFStringRef uti = UTTypeCreatePreferredIdentifierForTag(kUTTagClassFilenameExtension, (__bridge CFStringRef)extension, NULL);
    if (uti) {
        CFStringRef cfMIMEType = UTTypeCopyPreferredTagWithClass(uti, kUTTagClassMIMEType);
        if (cfMIMEType) {
            result = CFBridgingRelease(cfMIMEType);
        }
        CFRelease(uti);
    }
    return result;
}

@end
