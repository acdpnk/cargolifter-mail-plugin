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
//  CLSendAttacthmentsUploadController.m
//  CargoLifter
//
//  Created by Fabian Jäger on 22/09/15.
//  Copyright © 2015 Mailbutler. All rights reserved.
//

#import "CLSendAttachmentsUploadController.h"

#import "CLServicesManager.h"

#import "MCAttachment.h"

#import "NSString+CLAdditions.h"
#import "CLGlobalFunctions.h"

@interface CLSendAttachmentsUploadController ()

@property (retain) CLUploader* uploader;
@property (retain) NSArray* fileStatsArray;
@property (retain) NSArray* attachmentIDs;
@property (assign) BOOL active;

@property (weak) NSWindow* mailWindow;
@property (strong) CLService* service;

- (void) prepareAndUploadAttachments:(NSArray*)attachments;
- (void) doUploadAttachmentsForIDs:(NSArray*)attachmentIDs;
@end

@implementation CLSendAttachmentsUploadController

#pragma mark General Methods

- (instancetype)init
{
    return [self initWithDelegate:nil forMailWindow:nil];
}

- (instancetype)initWithDelegate:(id<CLSendAttachmentsUploadControllerDelegate>)delegate forMailWindow:(NSWindow*)mailWindow
{
    if (self = [super init])
    {
        self.delegate = delegate;
        self.fileStatsArray = nil;
        self.active = NO;
        
        self.mailWindow = mailWindow;
        
        // load nib
        NSArray* topLevelObjects = nil;
        if([PLUGIN_BUNDLE loadNibNamed:@"SendAttachmentsUploadView" owner:self topLevelObjects:&topLevelObjects])
        {
            NSLog(@"📯 CARGOLIFTER: Successfully loaded SendAttachmentsUploadView.nib");
        }
        else
        {
            NSLog(@"💥 CARGOLIFTER: FATAL: Failed loading SendAttachmentsUploadView.nib");
        }
    }
    return self;
}

#pragma mark General Methods

- (void) uploadAttachments:(NSArray *)attachments
{
    if( attachments.count == 0 )
    {
        NSError* error = [NSError errorWithDomain:CLUploaderErrorDomain code:CLUploaderErrorNoAttachments userInfo:@{NSLocalizedDescriptionKey:NSLocalizedString(@"Could not find any attachments to upload.", nil)}];
        [self.delegate cl_failedUploadingAttachmentsWithError:error forAttachmentIDs:@[]];
        return;
    }
    
    // make sure that we have a service to upload with
    self.service = [self.delegate cl_uploadService];
    if(!self.service)
    {
        NSError* error = [NSError errorWithDomain:CLUploaderErrorDomain code:CLUploaderErrorInvalidService userInfo:@{NSLocalizedDescriptionKey:NSLocalizedString(@"No service configured to upload files to.", nil)}];
        [self.delegate cl_failedUploadingAttachmentsWithError:error forAttachmentIDs:@[]];
        return;
    }

    // start preparation for upload
    [self prepareAndUploadAttachments:attachments];
}

- (IBAction)cancelUpload:(id)sender
{
    self.active = NO;
    
    [self.uploader cancelUpload];
    
    // end originating sheet
    NSButton* senderButton = (NSButton*)sender;
    [self.mailWindow endSheet:senderButton.window returnCode:NSModalResponseCancel];
}

#pragma mark Upload Progress Sheet Methods

- (void) showUploadProgressSheet
{
    // update service icon
    self.serviceImageView.image = self.service.icon;
    
    [self.mailWindow beginSheet:self.progressPanel completionHandler:^(NSModalResponse returnCode) {
        // close the upload progress sheet
        [self.progressPanel orderOut:self];
        
        if( returnCode == NSModalResponseCancel )
        {
            // notify delegate
            [self.delegate cl_canceledUploadingAttachmentsWithIDs:self.attachmentIDs];
        }
    }];
}

#pragma mark Private Worker Methods

- (void) prepareAndUploadAttachments:(NSArray*)attachments
{
    NSMutableArray* fileStatsArray  = [NSMutableArray arrayWithCapacity:attachments.count];
    NSMutableArray* attachmentIDs   = [NSMutableArray arrayWithCapacity:attachments.count];
    
    // this is already part of the process, show progress...
    [self showUploadProgressSheet];
    
    for( MCAttachment* attachment in attachments )
    {
        NSFileWrapper* fileWrapper = [attachment fileWrapperForAccessLevel:0];
        
        // save attachments in temporary directory
        NSString *attachmentFileName    = attachment.filename;
        NSString* attachmentID          = [attachment.contentID trimmedContentID];
        NSString *attachmentPath        = [NSTemporaryDirectory() stringByAppendingPathComponent:attachmentFileName];
        
        // make sure that we have unique file names
        attachmentPath                  = CLNextAvailableFilePath(attachmentPath);
        
        // write data to temporary file
        NSError* error;
        BOOL success = [fileWrapper writeToURL:[NSURL fileURLWithPath:attachmentPath] options:(NSFileWrapperWritingAtomic|NSFileWrapperWritingWithNameUpdating) originalContentsURL:nil error:&error];
        
        if(!success) {
            NSLog(@"💥 CARGOLIFTER: Could not write attachment to temporary file: %@", error);
        }
        
        // get filesize from file
        NSDictionary *attrs = [[NSFileManager defaultManager] attributesOfItemAtPath:attachmentPath error:nil];
        NSUInteger fileSize = [attrs fileSize];

        NSMutableDictionary* aDict = [NSMutableDictionary dictionaryWithObjectsAndKeys:
                                      attachmentFileName, CLAttachmentOrigFileName,
                                      attachmentPath, CLAttachmentFilePath,
                                      @(fileSize), CLAttachmentFileSize,
                                      @(0U), CLAttachmentFileSizePart,
                                      attachmentID, CLAttachmentContentID,
                                      nil];
        
        [fileStatsArray addObject:aDict];
        [attachmentIDs addObject:attachmentID];
    }
    
    // second round of processing in background thread
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^(void) {
        
        for( NSMutableDictionary* fileStats in fileStatsArray )
        {
            NSString* filePath = fileStats[CLAttachmentFilePath];
            NSString* fileName = filePath.lastPathComponent;
            
            // only compress directories
            BOOL isDir = NO;
            [[NSFileManager defaultManager] fileExistsAtPath:filePath isDirectory:&isDir];
            if( !isDir )
            {
                continue;
            }
            
            NSString *zipName   = [fileName stringByAppendingPathExtension:@"zip"];
            NSString* zipFilePath = [NSTemporaryDirectory() stringByAppendingPathComponent:zipName];
            NSMutableArray *argumentArray = [NSMutableArray arrayWithCapacity:3];
            
            [argumentArray addObject:@"-c"];
            [argumentArray addObject:@"-k"];
            [argumentArray addObject:@"--sequesterRsrc"];
            if(isDir)
                [argumentArray addObject:@"--keepParent"];
            [argumentArray addObject:filePath];
            [argumentArray addObject:zipFilePath];
            
            NSTask* compressTask = [[NSTask alloc] init];
            compressTask.arguments = argumentArray;
            compressTask.launchPath = @"/usr/bin/ditto";
            
            [compressTask launch];
            [compressTask waitUntilExit];
            NSInteger status = compressTask.terminationStatus;
            
            // check termination status and show error (main thread), if it failed
            if( status != 0 )
            {
                dispatch_async(dispatch_get_main_queue(), ^(void){
                    
                    NSWindow* messageWindow = self.mailWindow;
                    [messageWindow endSheet:self.progressPanel returnCode:NSModalResponseStop];
                    
                    NSString* errorString = [NSString stringWithFormat:NSLocalizedString(@"Failed to compress file '%@'. Please check the file type and try again.", nil), fileName];
                    NSError* error = [NSError errorWithDomain:CLUploaderErrorDomain code:CLUploaderErrorCompressionFailed userInfo:@{NSLocalizedDescriptionKey:errorString}];
                    [self.delegate cl_failedUploadingAttachmentsWithError:error forAttachmentIDs:attachmentIDs];
                });
                return;
            }
            
            // delete uncompressed file
            [[NSFileManager defaultManager] removeItemAtPath:filePath error:nil];
            
            // save new local file name
            fileStats[CLAttachmentFilePath] = zipFilePath;
        }
        
        // store locally
        self.fileStatsArray = fileStatsArray;
        self.attachmentIDs = attachmentIDs;
        
        // done with processing, upload now (back on main thread)
        dispatch_async(dispatch_get_main_queue(), ^(void){
            
            // start uploading
            [self doUploadAttachmentsForIDs:self.attachmentIDs];
        });
    });
    
    
}

- (void) doUploadAttachmentsForIDs:(NSArray*)attachmentIDs
{    
    NSLog(@"📯 CARGOLIFTER: Uploading files...");
    
    // let delegate know that we start with uploading
    [self.delegate cl_willStartUploadingAttachmentsWithIDs:attachmentIDs];
    
    // reset progress indicator
    self.progressIndicator.doubleValue = 0.0;
    [self.progressIndicator setIndeterminate:NO];
    
    // make sure we have the correct uploader
    self.uploader = (CLUploader*)self.service.slave;
    
    // start uploading
    self.uploader.delegate = self;
    self.active = YES;
    NSString* firstFilePath = (self.fileStatsArray).firstObject[CLAttachmentFilePath];
    
    [self.uploader uploadFile:firstFilePath createPublicLink:YES rawFileAccess:NO];
}

#pragma mark Uploader Delegate Methods

- (void)uploadFailedWithStatus:(CLUploadStatus)status withError:(NSError *)error
{
    if(!self.active) return;
    
    NSWindow* messageWindow = self.mailWindow;
    [messageWindow endSheet:self.progressPanel returnCode:NSModalResponseStop];
    
    NSLog(@"💥 CARGOLIFTER: File upload failed with error - %@", [error localizedDescription]);
    [self.delegate cl_failedUploadingAttachmentsWithError:error forAttachmentIDs:self.attachmentIDs];
}

- (void)uploadProgress:(CGFloat)progress forFile:(NSString*)filePath
{
    if(!self.active) return;
    
    // get number of finished files
    NSString* fileName = filePath.lastPathComponent;
    float numTotalBytes = 0;
    float numUploadedBytes = 0;
    for( NSMutableDictionary* aFileDict in self.fileStatsArray )
    {
        // find this file in our list
        if( [[aFileDict[CLAttachmentFilePath] lastPathComponent] isEqualToString:fileName] )
        {
            // upate uploaded part of file size
            aFileDict[CLAttachmentFileSizePart] = [NSNumber numberWithUnsignedInteger:( [aFileDict[CLAttachmentFileSize] floatValue]*progress )];
        }
        
        numTotalBytes += [aFileDict[CLAttachmentFileSize] floatValue];
        numUploadedBytes += [aFileDict[CLAttachmentFileSizePart] floatValue];
    }
    
    self.progressIndicator.doubleValue = MAX(self.progressIndicator.doubleValue, (100.0/numTotalBytes)*numUploadedBytes);
}

- (void)createdLink:(NSURL*)linkURL forFile:(NSString*)path withIconURL:(NSURL *)iconURL
{
    if(!self.active) return;
    
    NSLog(@"📯 CARGOLIFTER: Created sharable link for file %@ successful: %@", [path lastPathComponent], linkURL);
    
    // add sharable link to file array
    NSString* fileName = path.lastPathComponent;
    NSUInteger numFinished = 0;
    CGFloat numTotalBytes = 0;
    CGFloat numUploadedBytes = 0;
    
    for( NSMutableDictionary* aFileDict in self.fileStatsArray )
    {
        if( [[aFileDict[CLAttachmentFilePath] lastPathComponent] isEqualToString:fileName] )
        {
            aFileDict[CLAttachmentFileLinkURL] = linkURL;
            if(iconURL)
                aFileDict[CLAttachmentFileIconURL] = iconURL;
        }
        
        if( aFileDict[CLAttachmentFileLinkURL] )
        {
            numFinished++;
            
            // if file is uploaded, set partial file size to total file size
            aFileDict[CLAttachmentFileSizePart] = aFileDict[CLAttachmentFileSize];
        }
        
        numTotalBytes += [aFileDict[CLAttachmentFileSize] floatValue];
        numUploadedBytes += [aFileDict[CLAttachmentFileSizePart] floatValue];
    }
    
    // update progress indicator
    self.progressIndicator.doubleValue = MAX(self.progressIndicator.doubleValue, (100.0/numTotalBytes)*numUploadedBytes);
    
    // next step: check if we have links for all files
    if( numFinished == self.fileStatsArray.count )
    {
        [self.delegate cl_receivedPublicLinks:self.fileStatsArray];
        
        if(self.completionBlock)
            self.completionBlock(CLProcessContinue);
        
        // end progress sheet
        [self.progressIndicator stopAnimation:self];
        NSWindow* messageWindow = self.mailWindow;
        [messageWindow endSheet:self.progressPanel returnCode:NSModalResponseOK];
    }
    else
    {
        // continue with next unfinished file
        for( NSMutableDictionary* aFileDict in self.fileStatsArray )
        {
            if( !aFileDict[CLAttachmentFileLinkURL] )
            {
                [self.uploader uploadFile:aFileDict[CLAttachmentFilePath] createPublicLink:YES rawFileAccess:NO];
                break;
            }
        }
    }
}

@end
