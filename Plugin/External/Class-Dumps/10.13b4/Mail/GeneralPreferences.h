//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


@class AccountManager, DefaultApplicationPopUpButton, MailApp, MailboxesChooser, NSPopUpButton, NSUserDefaults, SoundPopUpButtonController;

@interface GeneralPreferences : NSViewController
{
    BOOL _settingNewMessagesSoundName;
    DefaultApplicationPopUpButton *_defaultMailClientPopUp;
    SoundPopUpButtonController *_theNewMessagesSoundController;
    NSPopUpButton *_theNewMessagesSoundPopUp;
    MailboxesChooser *_dockBadgeMailboxesChooser;
    MailboxesChooser *_userNotificationMailboxesChooser;
    NSPopUpButton *_downloadFolderPopup;
}

+ (id)keyPathsForValuesAffectingShouldIndexJunk;
+ (id)keyPathsForValuesAffectingShouldIndexTrash;
- (void)_chooseNewDownloadFolder:(id)arg1;
- (void)_dockBadgePopupChanged:(id)arg1;
- (void)_newMessagesSoundDidChange:(id)arg1;
- (void)_selectedNewMessagesSoundDidChange:(id)arg1;
- (void)_setupDockCountPopup;
- (void)_setupUserNotificationPopup;
- (void)_updateDownloadFolderPopUp:(id)arg1;
- (void)_userNotificationPopupChanged:(id)arg1;
@property(readonly, nonatomic) AccountManager *accountManager;
@property(nonatomic) BOOL addInvitationsToCalendarAutomatically;
@property(readonly, nonatomic) MailApp *application;
@property(nonatomic) long long attachmentDeletionTag;
- (void)dealloc;
@property(nonatomic) __weak DefaultApplicationPopUpButton *defaultMailClientPopUp; // @synthesize defaultMailClientPopUp=_defaultMailClientPopUp;
@property(retain, nonatomic) MailboxesChooser *dockBadgeMailboxesChooser; // @synthesize dockBadgeMailboxesChooser=_dockBadgeMailboxesChooser;
@property(nonatomic) __weak NSPopUpButton *downloadFolderPopup; // @synthesize downloadFolderPopup=_downloadFolderPopup;
- (void)observeValueForKeyPath:(id)arg1 ofObject:(id)arg2 change:(id)arg3 context:(void *)arg4;
@property(nonatomic) BOOL settingNewMessagesSoundName; // @synthesize settingNewMessagesSoundName=_settingNewMessagesSoundName;
@property(nonatomic) BOOL shouldIndexJunk;
@property(nonatomic) BOOL shouldIndexTrash;
@property(retain, nonatomic) SoundPopUpButtonController *theNewMessagesSoundController; // @synthesize theNewMessagesSoundController=_theNewMessagesSoundController;
@property(nonatomic) __weak NSPopUpButton *theNewMessagesSoundPopUp; // @synthesize theNewMessagesSoundPopUp=_theNewMessagesSoundPopUp;
@property(retain, nonatomic) MailboxesChooser *userNotificationMailboxesChooser; // @synthesize userNotificationMailboxesChooser=_userNotificationMailboxesChooser;
@property(readonly, nonatomic) NSUserDefaults *userDefaults;
- (void)viewDidLoad;

@end
