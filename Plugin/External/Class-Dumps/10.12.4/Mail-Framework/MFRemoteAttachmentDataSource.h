//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


#import "MCRemoteAttachmentDataSource.h"

@class MFLibraryMessage, NSConditionLock, NSMutableDictionary, NSOperationQueue, NSProgress, NSString;

@interface MFRemoteAttachmentDataSource : NSObject <MCRemoteAttachmentDataSource>
{
    NSConditionLock *_attachmentFetchLock;
    NSMutableDictionary *_completionBlocksByMimePartNumber;
    id _completionBlocksByMimePartNumberLock;
    MFLibraryMessage *_message;
    NSOperationQueue *_attachmentFetchCompletionQueue;
    NSProgress *_downloadProgress;
}

+ (id)remoteAttachmentDataSourceForMessage:(id)arg1;
- (void)_attachmentBecameAvailable:(id)arg1;
@property(readonly, nonatomic) NSOperationQueue *attachmentFetchCompletionQueue; // @synthesize attachmentFetchCompletionQueue=_attachmentFetchCompletionQueue;
- (void)dealloc;
@property(readonly, copy) NSString *description;
@property(readonly, nonatomic) NSProgress *downloadProgress; // @synthesize downloadProgress=_downloadProgress;
- (void)fetchAttachmentForAccessLevel:(long long)arg1 mimePartNumber:(id)arg2 withCompletionBlock:(id)arg3;
- (id)init;
- (id)initWithMessage:(id)arg1;
@property(readonly, nonatomic) MFLibraryMessage *message; // @synthesize message=_message;

// Remaining properties
@property(readonly, copy) NSString *debugDescription;
@property(readonly) NSUInteger hash;
@property(readonly) Class superclass;

@end
