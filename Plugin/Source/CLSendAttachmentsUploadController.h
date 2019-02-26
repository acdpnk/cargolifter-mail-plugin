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
//  CLSendAttacthmentsUploadController.h
//  CargoLifter
//
//  Created by Fabian Jäger on 22/09/15.
//  Copyright © 2015 Mailbutler. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "CLUploader.h"

#define CLAttachmentOrigFileName    @"CLAttachmentOrigFileName"
#define CLAttachmentFilePath        @"CLAttachmentFilePath"
#define CLAttachmentContentID       @"CLAttachmentContentID"
#define CLAttachmentFileLinkURL     @"CLAttachmentFileLinkURL"
#define CLAttachmentFileIconURL     @"CLAttachmentFileIconURL"
#define CLAttachmentFileSize        @"CLAttachmentFileSize"
#define CLAttachmentFileSizePart    @"CLAttachmentFileSizePart"

typedef NS_ENUM(NSUInteger, CLAttachmentUploaderResponse) {
    CLUploaderResponseUploaded,
    CLUploaderResponseCanceled,
    CLUploaderResponseError
};

@protocol CLSendAttachmentsUploadControllerDelegate
@required
- (void) cl_willStartUploadingAttachmentsWithIDs:(NSArray*)attachmentIDs;
- (void) cl_receivedPublicLinks:(NSArray<NSDictionary*>*)shareLinkArray;
- (void) cl_canceledUploadingAttachmentsWithIDs:(NSArray*)attachmentIDs;
- (void) cl_failedUploadingAttachmentsWithError:(NSError*)error forAttachmentIDs:(NSArray*)attachmentIDs;
- (CLService*) cl_uploadService;
@end

@interface CLSendAttachmentsUploadController : NSObject <CLUploaderDelegate>

@property (retain) id<CLSendAttachmentsUploadControllerDelegate> delegate;

@property (retain) IBOutlet NSWindow *progressPanel;
@property (retain) IBOutlet NSProgressIndicator *progressIndicator;
@property (retain) IBOutlet NSImageView *serviceImageView;

@property (nonatomic, copy) void (^completionBlock)(CLSendProcessAction);

// designated initializer
- (instancetype)initWithDelegate:(id<CLSendAttachmentsUploadControllerDelegate>)delegate forMailWindow:(NSWindow*)mailWindow NS_DESIGNATED_INITIALIZER;

// action methods
- (void) uploadAttachments:(NSArray *)attachments;

- (IBAction)cancelUpload:(id)sender;

@end
