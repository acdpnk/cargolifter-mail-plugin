//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


@class MFMailbox, NSOperationQueue;

@interface DockCountController : NSObject
{
    MFMailbox *_mailBadgeMailbox;
    long long _mailBadgeScope;
    NSOperationQueue *_workQueue;
}

+ (id)_log;
+ (id)allocWithZone:(struct _NSZone *)arg1;
+ (id)sharedInstance;
- (void)_mailboxWillBeInvalidated:(id)arg1;
- (void)_setDockBadgeForCount:(id)arg1;
- (void)_setMailBadgeMailbox:(id)arg1;
- (void)clearCountAndStopUpdating;
- (void)dealloc;
- (id)init;
@property(readonly, nonatomic) MFMailbox *mailBadgeMailbox;
@property(nonatomic) long long mailBadgeScope; // @synthesize mailBadgeScope=_mailBadgeScope;
- (void)setMailBadgeScope:(long long)arg1 mailbox:(id)arg2;
- (void)unreadCountChanged:(id)arg1;
@property(readonly, nonatomic) NSOperationQueue *workQueue; // @synthesize workQueue=_workQueue;

@end
