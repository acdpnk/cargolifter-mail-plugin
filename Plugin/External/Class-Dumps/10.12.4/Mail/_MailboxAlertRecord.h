//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


@class MFMailbox;

@interface _MailboxAlertRecord : NSObject
{
    BOOL _userInitiated;
    MFMailbox *_mailbox;
}

- (id)description;
- (id)init;
- (id)initWithMailbox:(id)arg1 userInitiated:(BOOL)arg2;
@property(readonly, nonatomic) MFMailbox *mailbox; // @synthesize mailbox=_mailbox;
@property(readonly, nonatomic) BOOL userInitiated; // @synthesize userInitiated=_userInitiated;

@end

