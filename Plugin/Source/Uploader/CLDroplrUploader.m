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
//  CLDroplrUploader.m
//
//  Created by Fabian Jäger on 09.04.13.
//  Copyright (c) 2013 Mailbutler. All rights reserved.
//

#import "CLDroplrUploader.h"

#import "NSString+CLAdditions.h"
#import "NSData+CLAdditions.h"

#import <AFNetworking/AFNetworking.h>
#import <sys/time.h>

long long DKCurrentTimeMillis()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    
    return (((int64_t) t.tv_sec) * 1000) + (((int64_t) t.tv_usec) / 1000);
}

@interface CLDroplrUploader ()

@end

@implementation CLDroplrUploader

- (void) uploadFile:(NSString*)localFilePath createPublicLink:(BOOL)createPublicLink rawFileAccess:(BOOL)rawFile
{
    if( self.busy )
        return;
    
    // upload files via Droplr
    self.activeFile = localFilePath;
    self.busy = YES;
    self.canceled = NO;
    
    // prepare file upload
    NSString *filename = localFilePath.lastPathComponent;
    NSData* fileData = [NSData dataWithContentsOfFile:localFilePath];
    NSString *mimeType = [self MIMETypeFileName:filename defaultMIMEType:@"binary/octet-stream"];
    
    NSString* uploadURI = @"/files";
    long long timeSince1970 = DKCurrentTimeMillis();
    
    // Create the user agent identifier
    NSString* bundleName = PLUGIN_BUNDLE.infoDictionary[@"CFBundleName"];
    NSString* version = PLUGIN_BUNDLE.infoDictionary[@"CFBundleVersion"];
    NSString* userAgent = [NSString stringWithFormat:@"%@/%@", bundleName, version];
    
    // create signature
    NSString* accessKey = [NSString stringByEncodingBase64:[NSString stringWithFormat:@"%@:%@", DROPLR_PUBLIC_KEY, self.service.login] withCharacterEncoding:NSUTF8StringEncoding];
    NSString* accessSecret = [NSString stringWithFormat:@"%@:%@", DROPLR_PRIVATE_KEY, self.service.password.sha1_digest];
    NSString* stringToSign = [NSString stringWithFormat:@"%@ %@ HTTP/1.1\n%@\n%lld", @"POST", uploadURI, mimeType, timeSince1970];
    NSString* signature = [[NSData HMACSHA1DigestOfString:stringToSign withKey:accessSecret] base64EncodedString];
    
    NSString* authorizationHeader = [NSString stringWithFormat:@"droplr %@:%@", accessKey, signature];
    
    AFHTTPSessionManager *manager = [[AFHTTPSessionManager alloc] initWithBaseURL:[NSURL URLWithString:@"https://api.droplr.com"]];
    manager.requestSerializer = [AFHTTPRequestSerializer serializer];
    [manager.requestSerializer setValue:[NSString stringWithFormat:@"%lld", timeSince1970] forHTTPHeaderField:@"Date"];
    [manager.requestSerializer setValue:authorizationHeader forHTTPHeaderField:@"Authorization"];
    [manager.requestSerializer setValue:userAgent forHTTPHeaderField:@"User-Agent"];
    manager.responseSerializer = [AFHTTPResponseSerializer serializer];
    
    NSMutableURLRequest *request = [manager.requestSerializer requestWithMethod:@"POST" URLString:@"https://api.droplr.com/files" parameters:nil error:nil];
    [request setValue:mimeType forHTTPHeaderField:@"Content-Type"];
    [request setValue:filename forHTTPHeaderField:@"x-droplr-filename"];
    [request setHTTPBody:fileData];
    
    NSError *attributesError;
    NSDictionary *fileAttributes = [[NSFileManager defaultManager] attributesOfItemAtPath:localFilePath error:&attributesError];
    
    [request setValue:[NSString stringWithFormat:@"%llu", [fileAttributes fileSize]] forHTTPHeaderField:@"Content-Length"];
    
    [[manager dataTaskWithRequest:request uploadProgress:^(NSProgress * _Nonnull uploadProgress) {
        
        if(self.canceled)
        {
            self.busy = NO;
            
            [uploadProgress cancel];
            return;
        }
        
        NSLog(@"📯 CARGOLIFTER: Transferred %lld of %lld", uploadProgress.completedUnitCount, uploadProgress.totalUnitCount);
        
        dispatch_async(dispatch_get_main_queue(), ^{
            if( [self.delegate respondsToSelector:@selector(uploadProgress:forFile:)] )
                [self.delegate uploadProgress:uploadProgress.fractionCompleted forFile:localFilePath];
        });
        
    } downloadProgress:nil completionHandler:^(NSURLResponse * _Nonnull response, id  _Nullable responseObject, NSError * _Nullable error) {
        
        NSHTTPURLResponse* httpResponse = (NSHTTPURLResponse*)response;
        
        if(error == nil)
        {
            NSLog(@"📯 CARGOLIFTER: Drop created: %@", httpResponse.allHeaderFields);
            
            self.busy = NO;
            
            NSString* shareLink = httpResponse.allHeaderFields[@"x-droplr-shortlink"];
            if(rawFile)
                shareLink = [shareLink stringByAppendingString:@"+"];
            
            if( [self.delegate respondsToSelector:@selector(createdLink:forFile:withIconURL:)] )
                [self.delegate createdLink:[NSURL URLWithString:shareLink] forFile:localFilePath withIconURL:nil];
        }
        else
        {
            NSLog(@"💥 CARGOLIFTER: Error: %@", [error localizedDescription]);
            
            self.busy = NO;
            
            if( [self.delegate respondsToSelector:@selector(uploadFailedWithStatus:withError:)] )
                [self.delegate uploadFailedWithStatus:CLUploadError withError:error];
        }
        
    }] resume];
}

- (void) authenticate
{
    self.service.linking = YES;
    
    NSString* accountURI = @"/account";
    long long timeSince1970 = DKCurrentTimeMillis();
    
    // create signature
    NSString* accessKey = [NSString stringByEncodingBase64:[NSString stringWithFormat:@"%@:%@", DROPLR_PUBLIC_KEY, self.service.login] withCharacterEncoding:NSUTF8StringEncoding];
    NSString* accessSecret = [NSString stringWithFormat:@"%@:%@", DROPLR_PRIVATE_KEY, self.service.password.sha1_digest];
    NSString* stringToSign = [NSString stringWithFormat:@"%@ %@ HTTP/1.1\n\n%lld", @"GET", accountURI, timeSince1970];
    NSString* signature = [[NSData HMACSHA1DigestOfString:stringToSign withKey:accessSecret] base64EncodedString];
    
    NSString* authorizationHeader = [NSString stringWithFormat:@"droplr %@:%@", accessKey, signature];
    
    AFHTTPSessionManager *manager = [[AFHTTPSessionManager alloc] initWithBaseURL:[NSURL URLWithString:@"https://api.droplr.com"]];
    [manager.requestSerializer setValue:[NSString stringWithFormat:@"%lld", timeSince1970] forHTTPHeaderField:@"Date"];
    [manager.requestSerializer setValue:authorizationHeader forHTTPHeaderField:@"Authorization"];
    AFJSONResponseSerializer* jsonSerializer = [AFJSONResponseSerializer serializer];
    [jsonSerializer setRemovesKeysWithNullValues:YES];
    manager.responseSerializer = jsonSerializer;
    
    [manager GET:accountURI parameters:nil progress:nil success:^(NSURLSessionDataTask * _Nonnull task, NSDictionary* _Nullable responseObject) {
        NSLog(@"📯 CARGOLIFTER: User credentials are valid: %@", responseObject);
        if( [self.authDelegate respondsToSelector:@selector(didFinishAuthenticationWithError:)] )
            [self.authDelegate didFinishAuthenticationWithError:nil];
        
        [self.service markAsLinked:YES];
    } failure:^(NSURLSessionDataTask * _Nullable task, NSError * _Nonnull error) {
        NSLog(@"💥 CARGOLIFTER: Error: %@", [error localizedDescription]);
        if( [self.authDelegate respondsToSelector:@selector(didFinishAuthenticationWithError:)] )
            [self.authDelegate didFinishAuthenticationWithError:error];
        
        [self.service markAsLinked:NO];
    }];
}

@end
