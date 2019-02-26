//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


@class NSDate, NSString;

@protocol IMAPMessage <NSObject>
@property(readonly) NSDate *dateReceived;
@property(readonly, nonatomic) BOOL hasAttachments;
@property BOOL hasTemporaryUid;
@property BOOL isPartial;
@property(readonly, copy, nonatomic) NSString *mailboxName;
@property(readonly, copy, nonatomic) NSString *messageID;
@property(readonly) NSUInteger messageSize;
@property BOOL partsHaveBeenCached;
@property(nonatomic) unsigned int uid;
@property(readonly, nonatomic) BOOL shouldDeferBodyDownload;
@property(readonly, copy) NSString *subject;
@end

