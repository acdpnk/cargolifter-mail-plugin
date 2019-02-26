//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header

#import "ECMailbox-Protocol.h"

@class NSArray, NSDate, NSString;

@protocol ECMessage <NSCopying, NSObject>
@property(readonly) BOOL answered;
@property(readonly, copy) NSArray *cc;
@property(readonly) long long conversationID;
@property(readonly) BOOL conversationMuted;
@property(readonly) BOOL conversationVIP;
@property(readonly) NSDate *dateReceived;
@property(readonly) BOOL flagged;
@property(readonly, copy) NSArray *from;
@property(readonly) BOOL junk;
@property(readonly, copy) NSArray *listUnsubscribe;
@property(readonly, nonatomic) id <ECMailbox> mailbox;
@property(readonly, nonatomic) id messageBody;
@property(readonly, copy, nonatomic) NSString *persistentID;
@property(readonly, copy) NSString *remoteID;
@property(readonly) BOOL senderVIP;
@property(readonly, copy) NSString *subject;
@property(readonly, copy) NSArray *to;
@end

