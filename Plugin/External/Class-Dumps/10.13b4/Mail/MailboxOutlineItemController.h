//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header

#import "MailboxOutlineItemControllerDelegate-Protocol.h"
#import "MailboxOutlineItemViewDelegate-Protocol.h"
#import "MailboxTextFieldDelegate-Protocol.h"

@class MailboxOutlineItemView, NSString;

@interface MailboxOutlineItemController : NSObject <MailboxTextFieldDelegate, MailboxOutlineItemViewDelegate>
{
    MailboxOutlineItemView *_view;
    id _item;
    NSObject<MailboxOutlineItemControllerDelegate> *_delegate;
}

- (id)_account;
- (long long)_alertState;
- (void)_connectView:(id)arg1;
- (void)_disconnectView:(id)arg1;
- (long long)_iconSize;
- (NSUInteger)_iconStyle;
- (BOOL)_isEditing;
- (id)_mailbox;
- (id)_sectionDisplayName;
- (BOOL)_shouldShowBadge;
- (void)_updateBadgeAnimated:(BOOL)arg1;
- (void)_updateImage;
- (void)_updateValuesForAccount;
- (void)_updateValuesForBasicSection;
- (void)_updateValuesForMailbox;
- (void)dealloc;
@property(readonly, copy) NSString *debugDescription;
@property __weak NSObject<MailboxOutlineItemControllerDelegate> *delegate; // @synthesize delegate=_delegate;
@property __weak id item;
- (id)mailboxOutlineItemViewShouldDisplayImage:(id)arg1;
- (void)mailboxTextFieldBeganEditingSession;
- (void)mailboxTextFieldEndedEditingSession;
@property __weak MailboxOutlineItemView *view;
- (void)updateAlertState;
- (void)updateAllValues;
- (void)updateBadgeCountAnimated:(BOOL)arg1;

// Remaining properties
@property(readonly, copy) NSString *description;
@property(readonly) NSUInteger hash;
@property(readonly) Class superclass;

@end

