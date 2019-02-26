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
//  CLUploader.h
//
//  Created by Fabian Jäger on 09.04.13.
//  Copyright (c) 2013 Mailbutler. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "CLService.h"
#import "CLServiceSlaveProtocol.h"

typedef enum _CSCLUploadStatus {
    CLUploadError,
    CLUploadSilent
} CLUploadStatus;

typedef NS_ENUM(NSUInteger, CLUploaderError) {
    CLUploaderErrorUnknownError,
    CLUploaderErrorCreateDirectory,
    CLUploaderErrorFileNotFound,
    CLUploaderErrorQuickKey,
    CLUploaderErrorGetDownloadLink,
    CLUploaderErrorLocalFileNotFound,
    CLUploaderErrorNoAttachments,
    CLUploaderErrorCompressionFailed,
    CLUploaderErrorInvalidService,
    CLUploaderErrorUploadTimeout,
    CLUploaderErrorNoRawFileSupport
};

typedef enum : NSUInteger {
    CLAttachmentLinkStyleURLFiles,
    CLAttachmentLinkStyleLinkList,
    CLAttachmentLinkStyleBoth,
} CLAttachmentLinkStyleType;

typedef enum : NSUInteger {
    CLAttachmentLinkListPositionBelowMessage,
    CLAttachmentLinkListPositionAboveMessage,
} CLAttachmentLinkListPositionType;

#define CLUploaderErrorDomain       @"com.mailbutler.CargoLifter.Uploader"

@protocol CLUploaderDelegate <NSObject>

@optional
- (void)uploadProgress:(CGFloat)progress forFile:(NSString*)filePath;

@required
- (void)uploadFailedWithStatus:(CLUploadStatus)status withError:(NSError*)error;
- (void)createdLink:(NSURL*)linkURL forFile:(NSString*)path withIconURL:(NSURL*)iconURL;

@end

@interface CLUploader : NSObject <CLServiceSlaveProtocol, CLUploadServiceSlaveProtocol>

@property (strong) CLService* service;
@property (retain) id<CLUploaderDelegate> delegate;
@property (weak) id<CLServiceSlaveAuthenticationDelegate> authDelegate;

@property (retain) NSString* activeFile;
@property (assign) BOOL busy;
@property (assign) BOOL canceled;

- (instancetype) initWithService:(CLService*)service NS_DESIGNATED_INITIALIZER;

- (void) uploadFile:(NSString*)localFilePath createPublicLink:(BOOL)createPublicLink rawFileAccess:(BOOL)rawFile;
- (void) cancelUpload;

- (void) authenticate;

+ (Class)classForServiceType:(CLServiceType)serviceType;

+ (NSString*)localizedErrorDescriptionForErrorCode:(CLServiceAuthError)errorCode;

- (NSString *)MIMETypeFileName:(NSString *)path defaultMIMEType:(NSString *)defaultType;

@end
