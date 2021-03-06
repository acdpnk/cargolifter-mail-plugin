//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header

#import "MCMessage.h"

@class MFMailbox, MFPOPAccount, NSData, NSString;

@interface MFPOPMessage : MCMessage
{
    NSString *_messageID;
    NSUInteger _messageNumber;
    NSData *_messageData;
}

@property(readonly, nonatomic) MFPOPAccount *account;
- (id)dataSource;
- (id)initWithPOP3FetchStore:(id)arg1;
@property(readonly, nonatomic) MFMailbox *mailbox;
@property(copy, nonatomic) NSData *messageData; // @synthesize messageData=_messageData;
- (id)messageDataFetchIfNotAvailable:(BOOL)arg1 newDocumentID:(id)arg2;
@property(copy, nonatomic) NSString *messageID; // @synthesize messageID=_messageID;
@property(nonatomic) NSUInteger messageNumber; // @synthesize messageNumber=_messageNumber;
- (NSUInteger)messageSize;
- (id)remoteMailboxURLString;
- (void)setDataSource:(id)arg1;

@end

