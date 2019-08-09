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
//  CLDropboxUploader.m
//
//  Created by Fabian Jäger on 09.04.13.
//  Copyright (c) 2013 Mailbutler. All rights reserved.
//

#import "CLDropboxUploader.h"

#import "NSString+CLAdditions.h"

#import <ObjectiveDropboxOfficial/ObjectiveDropboxOfficial.h>
#import <AFNetworking/AFNetworking.h>
#import "AFOAuthCredential.h"
#import "AFHTTPRequestSerializer+OAuth2.h"

#define CLDropboxRedirectURL    @"https://cargolifter.mailbutler.io/dropbox"

@implementation CLDropboxUploader

- (NSString*) clientID { return DROPBOX_APP_KEY; }
- (NSString*) clientSecret { return DROPBOX_APP_SECRET; }
- (NSURL*) oauthStartURL { return [NSURL URLWithString:[NSString stringWithFormat:@"https://www.dropbox.com/oauth2/authorize?response_type=code&client_id=%@&redirect_uri=%@&state=%@", self.clientID, [CLDropboxRedirectURL urlEncodedQueryString], [NSUUID UUID]]]; }
- (NSURL*) authBaseURL { return [NSURL URLWithString:@"https://api.dropbox.com"]; }
- (NSURL*) redirectURL { return [NSURL URLWithString:CLDropboxRedirectURL]; }
- (NSString*) getTokenPath { return @"/oauth2/token"; }
- (NSString*) refreshTokenPath { return @"/oauth2/token"; }

- (void) uploadFile:(NSString*)localFilePath createPublicLink:(BOOL)createPublicLink rawFileAccess:(BOOL)rawFile
{
    if( self.busy )
        return;
    
    self.activeFile = localFilePath;
    self.busy = YES;

    AFOAuthCredential* credentials = [AFOAuthCredential retrieveCredentialWithIdentifier:self.service.uniqueIdentifier];
    DBUserClient* client = [[DBUserClient alloc] initWithAccessToken:credentials.accessToken];
    
    // For overriding on upload
    DBFILESWriteMode *mode = [[DBFILESWriteMode alloc] initWithOverwrite];
    
    // upload file via dropbox
    NSData* dataToUpload = [NSData dataWithContentsOfFile:localFilePath];
    NSUInteger fileSize = dataToUpload.length;
    [[[client.filesRoutes uploadData:[@"/" stringByAppendingPathComponent:localFilePath.lastPathComponent]
                                mode:mode
                          autorename:@(YES)
                      clientModified:nil
                                mute:@(NO)
                           inputData:dataToUpload]
      setResponseBlock:^(DBFILESFileMetadata *result, DBFILESUploadError *routeError, DBRequestError *networkError) {
          if (result) {
              NSLog(@"📯 CARGOLIFTER: File uploaded successfully to path: %@", result.pathLower);
              
              // use dropbox to get share link
              [[client.sharingRoutes createSharedLinkWithSettings:result.pathLower] setResponseBlock:^(DBSHARINGSharedLinkMetadata * _Nullable result, DBSHARINGCreateSharedLinkWithSettingsError * _Nullable routeError, DBRequestError * _Nullable networkError) {
                  
                  self.busy = NO;
                  
                  if(result) {
                      NSString* shareLink = result.url;
                      if(rawFile) {
                          if([shareLink containsString:@"?"])
                              shareLink = [shareLink stringByAppendingString:@"&raw=1"];
                          else
                              shareLink = [shareLink stringByAppendingString:@"?raw=1"];
                      } else {
                          shareLink = [shareLink stringByReplacingOccurrencesOfString:@"dl=0" withString:@"dl=1"];
                      }
                      
                      if( [self.delegate respondsToSelector:@selector(createdLink:forFile:withIconURL:)] )
                          [self.delegate createdLink:[NSURL URLWithString:shareLink] forFile:self.activeFile withIconURL:nil];
                  } else if(routeError) {
                      if(routeError.tag == DBSHARINGCreateSharedLinkWithSettingsErrorSharedLinkAlreadyExists) {
                          // try to get the existing share link for this upload
                          [[client.sharingRoutes listSharedLinks:result.pathLower cursor:nil directOnly:@(YES)] setResponseBlock:^(DBSHARINGListSharedLinksResult * _Nullable result, DBSHARINGListSharedLinksError * _Nullable routeError, DBRequestError * _Nullable networkError) {
                              if(result) {
                                  NSString* shareLink = result.links.firstObject.url;
                                  if(rawFile) {
                                      if([shareLink containsString:@"?"])
                                          shareLink = [shareLink stringByAppendingString:@"&raw=1"];
                                      else
                                          shareLink = [shareLink stringByAppendingString:@"?raw=1"];
                                  } else {
                                      shareLink = [shareLink stringByReplacingOccurrencesOfString:@"dl=0" withString:@"dl=1"];
                                  }
                                  
                                  if( [self.delegate respondsToSelector:@selector(createdLink:forFile:withIconURL:)] )
                                      [self.delegate createdLink:[NSURL URLWithString:shareLink] forFile:self.activeFile withIconURL:nil];
                              } else {
                                  if( self.delegate && [self.delegate respondsToSelector:@selector(uploadFailedWithStatus:withError:)] )
                                      [self.delegate uploadFailedWithStatus:CLUploadError withError:[NSError errorWithDomain:CLCargoLifterErrorDomain code:1234567 userInfo:@{NSLocalizedDescriptionKey:@"Could not find share link for existing file."}]];
                              }
                          }];
                      } else {
                          if( self.delegate && [self.delegate respondsToSelector:@selector(uploadFailedWithStatus:withError:)] )
                              [self.delegate uploadFailedWithStatus:CLUploadError withError:[NSError errorWithDomain:CLCargoLifterErrorDomain code:12345671 userInfo:@{NSLocalizedDescriptionKey:@"Failed to upload file."}]];
                      }
                  }
              }];
          } else {
              NSLog(@"💥 CARGOLIFTER: %@\n%@\n", routeError, networkError);
              
              self.busy = NO;
              
              if( [self.delegate respondsToSelector:@selector(uploadFailedWithStatus:withError:)] )
                  [self.delegate uploadFailedWithStatus:CLUploadError withError:networkError.nsError];
          }
      }] setProgressBlock:^(int64_t bytesUploaded, int64_t totalBytesUploaded, int64_t totalBytesExpectedToUploaded) {
          dispatch_async(dispatch_get_main_queue(), ^{
              CGFloat totalProgress = (CGFloat)totalBytesUploaded/(CGFloat)fileSize;
              if( [self.delegate respondsToSelector:@selector(uploadProgress:forFile:)] )
                  [self.delegate uploadProgress:totalProgress forFile:localFilePath];
          });
      }];
}

- (void) cancelUpload { [super cancelUpload]; }

- (void) deauthenticate {
    [DBClientsManager unlinkAndResetClients];
}

+ (void) load {
    [DBClientsManager setupWithAppKeyDesktop:DROPBOX_APP_KEY];
}

@end
