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
//  CLGenericUploader.m
//
//  Created by Fabian Jäger on 09.04.13.
//  Copyright (c) 2013 Mailbutler. All rights reserved.
//

#import "CLGenericUploader.h"

#import "NSString+CLAdditions.h"
#import "NSData+CLAdditions.h"

#import "CLGlobalFunctions.h"

@interface CLGenericUploader ()
{
    CK2FileManager* _fileManager;
}

@property (readonly) CK2FileManager* fileManager;
@end

@implementation CLGenericUploader

- (void) uploadFile:(NSString*)localFilePath createPublicLink:(BOOL)createPublicLink rawFileAccess:(BOOL)rawFile
{
    if( self.busy )
        return;
    
    self.service.linking = NO;
    
    self.activeFile = localFilePath;
    self.busy = YES;
    self.canceled = NO;
    
    NSString* serverFullURLString = self.service.credentials[CLGenericServer];
    serverFullURLString = [serverFullURLString stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]];
    
    NSURL* serverURL = [NSURL URLWithString:serverFullURLString];
    
    NSString* serverPath = serverURL.path?:@"";
    
    if( serverPath && serverPath.length > 1 )
        serverURL = [NSURL URLWithString:[serverFullURLString stringByReplacingOccurrencesOfString:serverPath withString:@""]];
    
    // first get directory listing at our server path
    NSURL* serverRootURL = [CK2FileManager URLWithPath:serverPath relativeToURL:serverURL];
    
    [self.fileManager contentsOfDirectoryAtURL:serverRootURL includingPropertiesForKeys:nil options:NSDirectoryEnumerationSkipsHiddenFiles completionHandler:^(NSArray *contents, NSError *error)
    {
        if(self.canceled)
        {
            self.busy = NO;
            
            return;
        }
        
        if( error == nil )
        {
            // reformat list of files to only contain names (without path)
            NSMutableArray* fileList = [NSMutableArray arrayWithCapacity:contents.count];
            for(NSURL* anURL in contents)
                [fileList addObject:anURL.lastPathComponent];
            
            // upload files
            // check if file with the same name already exists
            NSString* fileName = [localFilePath.lastPathComponent asciiString];
            NSString* fileExtension = fileName.pathExtension;
            NSString* fileNameWithoutExtension = fileName.stringByDeletingPathExtension;
            NSInteger numDuplicates = 1;
            while( [fileList containsObject:fileName] )
            {
                fileName = [NSString stringWithFormat:@"%@-%ld.%@", fileNameWithoutExtension, numDuplicates++, fileExtension];
            }
            
            NSString* finalPath = [serverPath stringByAppendingPathComponent:fileName];
            
            NSURL *finalURL = [CK2FileManager URLWithPath:finalPath relativeToURL:serverURL];
            [self.fileManager createFileAtURL:finalURL contents:[NSData dataWithContentsOfFile:localFilePath] withIntermediateDirectories:YES openingAttributes:nil progressBlock:^(int64_t bytesWritten, int64_t totalBytesWritten, int64_t totalBytesExpectedToSend)
             {
                 // get total filesize from file
                 NSDictionary *attrs = [[NSFileManager defaultManager] attributesOfItemAtPath:localFilePath error:nil];
                 NSUInteger totalBytes = [attrs fileSize];
                 
                 if( [self.delegate respondsToSelector:@selector(uploadProgress:forFile:)] )
                 {
                     dispatch_async(dispatch_get_main_queue(), ^{
                         if([self.delegate respondsToSelector:@selector(uploadProgress:forFile:)])
                             [self.delegate uploadProgress:((CGFloat)totalBytesWritten/(CGFloat)totalBytes) forFile:localFilePath];
                     });
                 }
             } completionHandler:^(NSError *error)
             {
                 if(self.canceled)
                 {
                     self.busy = NO;
                     
                     return;
                 }
                 
                 if( error == nil )
                 {
                     NSURL* shareLink = finalURL;
                     
                     if( createPublicLink )
                     {
                         NSString* publicFullPath = self.service.credentials[CLGenericPublicURL];
                         publicFullPath = [publicFullPath stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]];
                         
                         if( publicFullPath != nil )
                         {
                             NSURL* publicFullURL = [NSURL URLWithString:publicFullPath];
                             shareLink = [publicFullURL URLByAppendingPathComponent:shareLink.lastPathComponent];
                         }
                     }
                     
                     self.busy = NO;
                     if( [self.delegate respondsToSelector:@selector(createdLink:forFile:withIconURL:)] )
                     {
                         dispatch_async(dispatch_get_main_queue(), ^{
                             [self.delegate createdLink:shareLink forFile:localFilePath withIconURL:nil];
                         });
                     }
                 }
                 else
                 {
                     self.busy = NO;
                     if( [self.delegate respondsToSelector:@selector(uploadFailedWithStatus:withError:)] )
                     {
                         dispatch_async(dispatch_get_main_queue(), ^{
                             [self.delegate uploadFailedWithStatus:CLUploadError withError:error];
                         });
                     }
                 }
             }];
        }
        else
        {
            self.busy = NO;
            if( [self.delegate respondsToSelector:@selector(uploadFailedWithStatus:withError:)] )
            {
                dispatch_async(dispatch_get_main_queue(), ^{
                    [self.delegate uploadFailedWithStatus:CLUploadError withError:error];
                });
            }
        }
    }];
}

- (void) authenticate
{
    self.service.linking = YES;
    
    // testing authentication by uploading test data
    NSData* dummyData = [NSData randomDataWithBytes:4];
    
    NSString* serverFullURLString = self.service.credentials[CLGenericServer];
    serverFullURLString = [serverFullURLString stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]];
    
    NSURL* serverURL = [NSURL URLWithString:serverFullURLString];
    
    NSString* serverPath = serverURL.path?:@"";
    
    if( serverPath && serverPath.length > 1 )
        serverURL = [NSURL URLWithString:[serverFullURLString stringByReplacingOccurrencesOfString:serverPath withString:@""]];
        
    NSString* finalPath = [serverPath stringByAppendingPathComponent:@"CargoLifter.dat"];
    NSURL *finalURL = [CK2FileManager URLWithPath:finalPath relativeToURL:serverURL];
    [self.fileManager createFileAtURL:finalURL contents:dummyData withIntermediateDirectories:YES openingAttributes:nil progressBlock:nil completionHandler:^(NSError *error)
     {
         if( error == nil )
         {
             NSURL* shareLink = finalURL;
             
             NSString* publicFullPath = self.service.credentials[CLGenericPublicURL];
             publicFullPath = [publicFullPath stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]];
             
             if( publicFullPath != nil )
             {
                 NSURL* publicFullURL = [NSURL URLWithString:publicFullPath];
                 shareLink = [publicFullURL URLByAppendingPathComponent:@"CargoLifter.dat"];
             }
             
             NSURLRequest* request = [NSURLRequest requestWithURL:shareLink];
             
             [[[NSURLSession sharedSession] dataTaskWithRequest:request completionHandler:^(NSData * _Nullable dataAtShareLink, NSURLResponse * _Nullable response, NSError * _Nullable error) {
                 
                 if( [dataAtShareLink isEqualToData:dummyData] )
                 {
                     // remove dummy file
                     [self.fileManager removeItemAtURL:finalURL completionHandler:^(NSError *error)
                      {
                          if( [self.authDelegate respondsToSelector:@selector(didFinishAuthenticationWithError:)] )
                          {
                              dispatch_async(dispatch_get_main_queue(), ^{
                                  [self.authDelegate didFinishAuthenticationWithError:error];
                                  
                                  [self.service markAsLinked:(error==nil)];
                              });
                          }
                      }];
                 }
                 else
                 {
                     dispatch_async(dispatch_get_main_queue(), ^{
                         // if file cannot be reached, ask user whether to ignore this problem and still authenticate...
                         NSInteger response = CLRunAlertPanel(NSLocalizedString(@"Authentication Warning", nil), NSLocalizedString(@"Could not download test file 'CargoLifter.dat' from %@.\nPlease make sure that uploaded files are reachable through the given public URL.", nil), @[NSLocalizedString(@"Cancel", nil), NSLocalizedString(@"Ignore", nil)], [shareLink absoluteString]);
                         
                         if(response == NSAlertSecondButtonReturn)
                         {
                             // remove dummy file
                             [self.fileManager removeItemAtURL:finalURL completionHandler:^(NSError *error)
                              {
                                  if( [self.authDelegate respondsToSelector:@selector(didFinishAuthenticationWithError:)] )
                                  {
                                      dispatch_async(dispatch_get_main_queue(), ^{
                                          [self.authDelegate didFinishAuthenticationWithError:error];
                                          
                                          [self.service markAsLinked:(error==nil)];
                                      });
                                  }
                              }];
                         }
                         else if( [self.authDelegate respondsToSelector:@selector(didFinishAuthenticationWithError:)] )
                         {
                             [self.fileManager removeItemAtURL:finalURL completionHandler:nil];
                             
                             dispatch_async(dispatch_get_main_queue(), ^{
                                 NSString* errorFormatString = NSLocalizedString(@"Remote File could not be found at '%@'.", nil);
                                 NSError* error2 = error;
                                 if( error2 == nil )
                                 {
                                     error2 = [NSError errorWithDomain:CLServiceAuthErrorDomain code:CLUploaderErrorFileNotFound userInfo:@{NSLocalizedDescriptionKey:[NSString stringWithFormat:errorFormatString, shareLink]}];
                                 }
                                 [self.authDelegate didFinishAuthenticationWithError:error2];
                                 
                                 [self.service markAsLinked:NO];
                             });
                         }
                     });
                 }
                 
             }] resume];
         }
         else
         {
             if( [self.authDelegate respondsToSelector:@selector(didFinishAuthenticationWithError:)] )
             {
                 NSLog(@"💥 CARGOLIFTER: Authentication Error: %@", [error localizedDescription]);
                 dispatch_async(dispatch_get_main_queue(), ^{
                     [self.authDelegate didFinishAuthenticationWithError:error];
                     
                     [self.service markAsLinked:NO];
                 });
             }
         }
     }];
}

- (CK2FileManager *)fileManager
{
    if (!_fileManager)
    {
        _fileManager = [[CK2FileManager alloc] init];
        _fileManager.delegate = self;
    }
    return _fileManager;
}

#pragma mark Connection Delegate Methods

- (void)fileManager:(CK2FileManager *)manager operation:(id)operation didReceiveChallenge:(NSURLAuthenticationChallenge *)challenge completionHandler:(void (^)(CK2AuthChallengeDisposition, NSURLCredential *))completionHandler
{
    NSLog(@"📯 CARGOLIFTER: received authentication challenge");
    
    if( challenge.error ) {
        NSLog(@"💥 CARGOLIFTER: Authentication error: %@", [challenge error]);
    }
    
    if (challenge.previousFailureCount > 1) {
        NSError* error = challenge.error;
        if(!error) {
            error = [NSError errorWithDomain:CLServiceAuthErrorDomain code:CLServiceAuthErrorSecurityChallenge userInfo:@{NSLocalizedDescriptionKey:NSLocalizedString(@"Could not authenticate with remote server.", nil)}];
        }
        
        if( self.service.linking ) {
            if( [self.authDelegate respondsToSelector:@selector(didFinishAuthenticationWithError:)] ) {
                dispatch_async(dispatch_get_main_queue(), ^{
                    [self.authDelegate didFinishAuthenticationWithError:error];
                });
            }
        } else {
            if( [self.delegate respondsToSelector:@selector(uploadFailedWithStatus:withError:)] ) {
                dispatch_async(dispatch_get_main_queue(), ^{
                    [self.delegate uploadFailedWithStatus:CLUploadError withError:error];
                });
            }
        }
        
        completionHandler(CK2AuthChallengeCancelAuthenticationChallenge, nil);
        NSLog(@"💥 CARGOLIFTER: authentication failure");
        
        // we are done here!
        return;
    }
    
    // let's start the authentication part
    NSString* aLogin = self.service.login;
    NSString* aPassword = self.service.password;
    NSString* aPrivateKeyFilePath = self.service.credentials[CLGenericPrivateKey];
    
    if( [challenge.protectionSpace.authenticationMethod isEqualToString:NSURLAuthenticationMethodHTTPBasic] || [challenge.protectionSpace.authenticationMethod isEqualToString:NSURLAuthenticationMethodHTTPDigest] || [challenge.protectionSpace.authenticationMethod isEqualToString:NSURLAuthenticationMethodDefault] ) {
        if( aPrivateKeyFilePath.length && [[NSFileManager defaultManager] fileExistsAtPath:aPrivateKeyFilePath] ) {
            NSURLCredential* newCredential = [NSURLCredential ck2_credentialWithUser:aLogin publicKeyURL:nil privateKeyURL:[NSURL fileURLWithPath:aPrivateKeyFilePath] password:nil persistence:NSURLCredentialPersistenceNone];
            
            NSLog(@"📯 CARGOLIFTER: private key credential created");
            completionHandler(CK2AuthChallengeUseCredential, newCredential);
        } else {
            NSURLCredential *newCredential = [NSURLCredential credentialWithUser:aLogin password:aPassword persistence:NSURLCredentialPersistenceNone];
            
            NSLog(@"📯 CARGOLIFTER: try with username/password login");
            completionHandler(CK2AuthChallengeUseCredential, newCredential);
        }
    } else if( [challenge.protectionSpace.authenticationMethod isEqualToString:NSURLAuthenticationMethodClientCertificate] || [challenge.protectionSpace.authenticationMethod isEqualToString:NSURLAuthenticationMethodServerTrust] ) {
        NSLog(@"📯 CARGOLIFTER: automatically accepted authentication type: %@", challenge.protectionSpace.authenticationMethod);
        completionHandler(CK2AuthChallengePerformDefaultHandling, nil);
    } else {
        NSLog(@"📯 CARGOLIFTER: unknown authentication type: %@", challenge.protectionSpace.authenticationMethod);
        completionHandler(CK2AuthChallengePerformDefaultHandling, nil);
    }
    
    NSLog(@"📯 CARGOLIFTER: responded to authentication challenge");
}

#pragma mark Private Methods

@end
