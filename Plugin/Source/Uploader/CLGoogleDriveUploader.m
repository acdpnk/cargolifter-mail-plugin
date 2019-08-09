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
//  CLGoogleDriveUploader.m
//
//  Created by Fabian Jäger on 09.04.13.
//  Copyright (c) 2013 Mailbutler. All rights reserved.
//

#import "CLGoogleDriveUploader.h"

#import <AFNetworking/AFNetworking.h>
#import "AFOAuth2Manager.h"

#import "NSString+CLAdditions.h"

#define CLGDriveFolderId        @"CLGDriveFolderId"

#define CLDriveBaseURL          @"https://www.googleapis.com"
#define CLDriveRedirectURL      @"https://cargolifter.mailbutler.io/googledrive"

@implementation CLGoogleDriveUploader

- (NSString*) clientID { return GDRIVE_CLIENT_ID; }
- (NSString*) clientSecret { return GDRIVE_CLIENT_SECRET; }
- (NSURL*) oauthStartURL { return [NSURL URLWithString:[NSString stringWithFormat:@"https://accounts.google.com/o/oauth2/v2/auth?client_id=%@&response_type=code&access_type=offline&redirect_uri=%@&scope=%@&prompt=consent", self.clientID, [CLDriveRedirectURL urlEncodedQueryString], [@"https://www.googleapis.com/auth/drive.file" urlEncodedQueryString]]]; }
- (NSURL*) authBaseURL { return [NSURL URLWithString:@"https://www.googleapis.com"]; }
- (NSURL*) redirectURL { return [NSURL URLWithString:CLDriveRedirectURL]; }
- (NSString*) getTokenPath { return @"/oauth2/v4/token"; }
- (NSString*) refreshTokenPath { return @"/oauth2/v4/token"; }
- (NSString*) revokeTokenPath { return @"/o/oauth2/revoke"; }

- (void) uploadFile:(NSString*)localFilePath createPublicLink:(BOOL)createPublicLink rawFileAccess:(BOOL)rawFile {
    if(!self.service.credentials[CLGDriveFolderId])
        return;
    
    if( self.busy )
        return;
    
    self.activeFile = localFilePath;
    self.busy = YES;
    self.canceled = NO;
    
    // upload files via Google Drive
    [self uploadFileAtPath:localFilePath createPublicLink:createPublicLink rawFileAccess:rawFile];
}

#pragma mark Google Drive Related Methods

- (void)uploadFileAtPath:(NSString *)path createPublicLink:(BOOL)createPublicLink rawFileAccess:(BOOL)rawFile {
    [self _refreshAccessTokenWithSuccess:^{
        // use new access token
        AFOAuthCredential* credentials = [AFOAuthCredential retrieveCredentialWithIdentifier:self.service.uniqueIdentifier];

        AFHTTPSessionManager *generalManager = [[AFHTTPSessionManager alloc] initWithBaseURL:self.authBaseURL];
        generalManager.responseSerializer = [AFJSONResponseSerializer serializer];
        generalManager.requestSerializer = [AFJSONRequestSerializer serializer];
        [generalManager.requestSerializer setAuthorizationHeaderFieldWithCredential:credentials];

        // upload files via Google Drive
        NSString* fileName = path.lastPathComponent;
        NSString *mimeType = [self MIMETypeFileName:fileName defaultMIMEType:@"binary/octet-stream"];
        NSData* fileData = [NSData dataWithContentsOfFile:path];

        [generalManager.requestSerializer setValue:mimeType forHTTPHeaderField:@"X-Upload-Content-Type"];
        [generalManager.requestSerializer setValue:[NSString stringWithFormat:@"%ld", fileData.length] forHTTPHeaderField:@"X-Upload-Content-Length"];

        // create file with metadata
        NSDictionary* metadata = @{@"name": fileName, @"parents": @[self.service.credentials[CLGDriveFolderId]]};
        [generalManager POST:@"/upload/drive/v3/files?uploadType=resumable" parameters:metadata progress:nil success:^(NSURLSessionDataTask * _Nonnull task, id  _Nullable responseObject) {
            NSHTTPURLResponse* response = ((NSHTTPURLResponse *)[task response]);
            NSDictionary* headers = [response allHeaderFields];
            NSString* uploadLocation = headers[@"Location"];

            NSMutableURLRequest* uploadRequest = [generalManager.requestSerializer requestWithMethod:@"PUT" URLString:uploadLocation parameters:nil error:nil];
            uploadRequest.HTTPBody = fileData;
            [uploadRequest setValue:mimeType forHTTPHeaderField:@"Content-Type"];

            // start actual upload of file
            [[generalManager dataTaskWithRequest:uploadRequest uploadProgress:^(NSProgress * _Nonnull uploadProgress) {
                if(self.canceled) {
                    [uploadProgress cancel];
                    self.busy = NO;
                    return;
                }

                dispatch_async(dispatch_get_main_queue(), ^{
                    if( [self.delegate respondsToSelector:@selector(uploadProgress:forFile:)] )
                        [self.delegate uploadProgress:uploadProgress.fractionCompleted forFile:path];
                });

            } downloadProgress:nil completionHandler:^(NSURLResponse * _Nonnull response, id  _Nullable responseObject, NSError * _Nullable error) {
                if(error) {
                    NSLog(@"💥 CARGOLIFTER: UPLOAD FAILURE: %@", error);

                    self.busy = NO;

                    if( [self.delegate respondsToSelector:@selector(uploadFailedWithStatus:withError:)] )
                        [self.delegate uploadFailedWithStatus:CLUploadError withError:error];
                } else {
                    NSLog(@"📯 CARGOLIFTER: UPLOAD SUCCESS:");

                    NSDictionary* fileInfo = (NSDictionary*)responseObject;

                    if (createPublicLink) {
                        NSString* fileID = fileInfo[@"id"];

                        NSString* apiPath = [NSString stringWithFormat:@"/drive/v3/files/%@/permissions", fileID];

                        NSDictionary* permissions = @{@"role": @"reader", @"type": @"anyone"};
                        [generalManager POST:apiPath parameters:permissions progress:nil success:^(NSURLSessionDataTask * _Nonnull task, id  _Nullable responseObject) {
                            // permission change - get share URL
                            NSLog(@"📯 CARGOLIFTER: PERMISSION SUCCESS: %@", path);

                            // get final share link
                            NSString* apiPath = [NSString stringWithFormat:@"/drive/v3/files/%@", fileID];
                            [generalManager GET:apiPath parameters:@{@"fields": @"webContentLink,iconLink"} progress:nil success:^(NSURLSessionDataTask * _Nonnull task, id  _Nullable responseObject) {
                                NSDictionary* fileInfo = (NSDictionary*)responseObject;
                                NSString* shareLink = fileInfo[@"webContentLink"];

                                self.busy = NO;

                                if( self.delegate && [self.delegate respondsToSelector:@selector(createdLink:forFile:withIconURL:)] )
                                    [self.delegate createdLink:[NSURL URLWithString:shareLink] forFile:path withIconURL:[NSURL URLWithString:fileInfo[@"iconLink"]]];
                            } failure:^(NSURLSessionDataTask * _Nullable task, NSError * _Nonnull error) {
                                NSLog(@"💥 CARGOLIFTER: GET FILE FAILURE: %@", error);

                                self.busy = NO;

                                if( [self.delegate respondsToSelector:@selector(uploadFailedWithStatus:withError:)] )
                                    [self.delegate uploadFailedWithStatus:CLUploadError withError:error];
                            }];
                        } failure:^(NSURLSessionDataTask * _Nullable task, NSError * _Nonnull error) {
                            NSLog(@"💥 CARGOLIFTER: PERMISSIONS FAILURE: %@", error);

                            self.busy = NO;

                            if( [self.delegate respondsToSelector:@selector(uploadFailedWithStatus:withError:)] )
                                [self.delegate uploadFailedWithStatus:CLUploadError withError:error];
                        }];
                    } else {
                        self.busy = NO;

                        if( [self.delegate respondsToSelector:@selector(createdLink:forFile:withIconURL:)] )
                            [self.delegate createdLink:[NSURL URLWithString:fileInfo[@"webContentLink"]] forFile:path withIconURL:[NSURL URLWithString:fileInfo[@"iconLink"]]];
                    }

                }

            }] resume];
        } failure:^(NSURLSessionDataTask * _Nullable task, NSError * _Nonnull error) {
            NSLog(@"💥 CARGOLIFTER: METADATA FAILURE: %@", error);

            self.busy = NO;

            if( [self.delegate respondsToSelector:@selector(uploadFailedWithStatus:withError:)] )
                [self.delegate uploadFailedWithStatus:CLUploadError withError:error];
        }];
    } failure:^(NSError *error) {

        self.busy = NO;

        if( [self.delegate respondsToSelector:@selector(uploadFailedWithStatus:withError:)] )
            [self.delegate uploadFailedWithStatus:CLUploadError withError:error];
    }];
}

- (void) postAuthenticationHookWithHandler:(void (^)(NSError *error))completionBlock {
    [self _refreshAccessTokenWithSuccess:^{
        // use new access token
        AFOAuthCredential* credentials = [AFOAuthCredential retrieveCredentialWithIdentifier:self.service.uniqueIdentifier];

        AFHTTPSessionManager *generalManager = [[AFHTTPSessionManager alloc] initWithBaseURL:self.authBaseURL];
        generalManager.responseSerializer = [AFJSONResponseSerializer serializer];
        generalManager.requestSerializer = [AFJSONRequestSerializer serializer];
        [generalManager.requestSerializer setAuthorizationHeaderFieldWithCredential:credentials];

        NSString* bundleName = PLUGIN_BUNDLE.infoDictionary[@"CFBundleName"];
        NSDictionary* query = @{@"q": [NSString stringWithFormat:@"name = '%@'", bundleName]};
        [generalManager GET:@"/drive/v3/files" parameters:query progress:nil success:^(NSURLSessionDataTask * _Nonnull task, id  _Nullable responseObject) {

            NSDictionary* listInfo = (NSDictionary*)responseObject;
            NSArray* files = listInfo[@"files"];

            if( files.count > 0 ) {
                NSString* folderId = nil;

                for( NSDictionary* aFile in files ) {
                    if( [aFile[@"name"] isEqualToString:bundleName] && [aFile[@"parents"] count] == 0 ) {
                        folderId = aFile[@"id"];
                        break;
                    }
                }

                if(folderId) {
                    // store folder id
                    self.service.credentials[CLGDriveFolderId] = folderId;
                    completionBlock(nil);
                    return;
                }
            }

            // no directory found, create one
            NSDictionary* directoryParams = @{@"name": bundleName, @"mimeType": @"application/vnd.google-apps.folder"};
            [generalManager POST:@"/drive/v3/files" parameters:directoryParams progress:nil success:^(NSURLSessionDataTask * _Nonnull task, id  _Nullable responseObject) {
                NSDictionary* dirInfo = (NSDictionary*)responseObject;

                NSLog(@"📯 CARGOLIFTER: New Directory: %@", dirInfo);
                NSString* folderId = dirInfo[@"id"];

                self.service.credentials[CLGDriveFolderId] = folderId;
                completionBlock(nil);
            } failure:^(NSURLSessionDataTask * _Nullable task, NSError * _Nonnull error) {
                NSLog(@"💥 CARGOLIFTER: Failed to create directory: %@", error);
                completionBlock(error);
            }];

        } failure:^(NSURLSessionDataTask * _Nullable task, NSError * _Nonnull error) {
            NSLog(@"💥 CARGOLIFTER: An error occurred: %@", error);
            completionBlock(error);
        }];
    } failure:^(NSError *error) {
        completionBlock(error);
    }];
}

@end
