//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


#import "IMAPUserAgent-Protocol.h"
#import "MCActivityTarget-Protocol.h"
#import "MCUserAgent-Protocol.h"
#import "MFUserAgent-Protocol.h"
#import "TerminationHandler-Protocol.h"
#import "SelectionOwner-Protocol.h"

@class ActivityWindowController, DeliveryQueue, DifferentialPrivacyReporter_macOS, DockCountController, DynamicErrorWindowController, FlagIconFactory, FlagsMenuItemView, MFAccountFactory_macOS, MailActivityNotifier, MailBundleController, MailboxesController, NSArray, NSMenu, NSMutableArray, NSMutableSet, NSOperationQueue, NSString, NSTimer, NSTouchBar, NSURL, NSUserDefaults, NSWindow, NSWindowController, SortByMenuDelegate, UserActivityHandler;

@interface MailApp : NSApplication <IMAPUserAgent, MCUserAgent, MFUserAgent, NSTouchBarDelegate, NSTouchBarProvider, MCActivityTarget, NSApplicationDelegate, NSMenuDelegate, NSTabViewDelegate, TerminationHandler>
{
    NSMenu *_mailboxesContextMenu;
    NSMenu *_addButtonMenu;
    NSMenu *_messageViewerContextMenu;
    NSMenu *_viewAttachmentContextMenu;
    NSMenu *_composeAttachmentContextMenu;
    NSMutableArray *_stationeryBundlesToInstall;
    DeliveryQueue *_deliveryQueue;
    id _terminationHandlersLock;
    NSMutableArray *_terminationHandlers;
    NSMutableArray *_currentTerminationHandlers;
    NSUInteger _terminateReply;
    NSTimer *_terminationTimer;
    BOOL _groupingByThreadDefaultsToOn;
    NSMutableSet *_accountsCurrentlySynchronizing;
    NSMutableArray *_appleEventDescriptorQueue;
    NSMutableArray *_accountsEmptyingTrash;
    BOOL _paused;
    BOOL _isExitingFullscreen;
    BOOL _hasPerformedDelayedInitialization;
    BOOL _isCurrentlyTerminating;
    BOOL _accountsAreNew;
    BOOL _accountsHaveBeenConfigured;
    BOOL _autoLaunchHidden;
    BOOL _synchronizingAllAccounts;
    BOOL _shouldUpdateEmailAliasesOnNextActivation;
    BOOL _hasUpdatedEmailAliases;
    BOOL _runningEmptyTrashSheet;
    BOOL _appHasFinishedLaunching;
    MailboxesController *_mailboxesController;
    FlagsMenuItemView *_flagsMenuItemView;
    NSWindow *_errorDiagnosisWindow;
    DynamicErrorWindowController *_errorDiagnosisWindowController;
    long long *_errorDiagnosisResult;
    MailBundleController *_mailBundleController;
    NSArray *_loadedBundles;
    id <SelectionOwner> _selectionOwner;
    SortByMenuDelegate *_sortByMenuDelegate;
    FlagIconFactory *_flagIconFactory;
    NSOperationQueue *_initializationQueue;
    DockCountController *_dockCountController;
    NSWindowController *_preferencesController;
    double _appDidFinishLaunchingTime;
    UserActivityHandler *_userActivityHandler;
    ActivityWindowController *_activityWindowController;
    MailActivityNotifier *_activityNotifier;
    NSOperationQueue *_workQueue;
    NSTouchBar *_touchBar;
    MFAccountFactory_macOS *_accountFactory;
    DifferentialPrivacyReporter_macOS *_differentialPrivacyReporter;
}

+ (id)keyPathsForValuesAffectingNewMessagesSoundName;
+ (id)keyPathsForValuesAffectingShouldPlayOtherMailSounds;
+ (id)mailUpgraderLog;
+ (id)sharedApplication;
+ (id)terminationHandlingLog;
- (id)_accountBeingViewed;
- (void)_accountInfoDidChange:(id)arg1;
- (void)_accountsChanged:(id)arg1;
- (id)_accountsToEmptyTrashIn:(id)arg1;
- (void)_activityWindowWillClose:(id)arg1;
- (void)_addAosSmtpChildAccounts;
- (void)_addToAccountsCurrentlySynchronizing:(id)arg1;
- (void)_addressManagerLoaded:(id)arg1;
- (void)_adoptNewToolbarDefaultConfigurations;
- (void)_approveQuitIfFinished:(id)arg1;
- (void)_backfillDateLastViewedAttribute;
- (void)_checkNewMailInAccountRepresentedByMailbox:(id)arg1;
- (void)_cleanUpAccount:(id)arg1;
- (void)_cleanupFinishedForAccount:(id)arg1;
- (void)_clearAccountsCurrentlySynchronizing;
- (id)_convertSnowLeopardToLionKey:(id)arg1;
- (id)_currentTerminationHandler;
- (void)_delayedUpgradeSteps;
- (void)_downloadBigMessage:(id)arg1;
- (void)_emailAddressesApproved:(id)arg1;
- (void)_emailsRejected:(id)arg1;
- (void)_emptyTrashInAccounts:(id)arg1 storeToCompact:(id)arg2;
- (void)_emptyTrashPromptingUserInAccounts:(id)arg1 storeToCompact:(id)arg2;
- (void)_exitIfInUpgradeOnlyMode;
- (void)_getActiveAccountsThatCanGoOffline:(id)arg1 fetch:(id)arg2 sync:(id)arg3 deleteToTrash:(id)arg4 doesNotDeleteToTrash:(id)arg5;
- (id)_getMenuItemInMessageMenuWithTag:(long long)arg1;
- (void)_handleNetworkConfigurationChange;
- (BOOL)_handleOpenMessage:(id)arg1;
- (void)_handleScreenCaptureParameterInCurrentAppleEvent;
- (void)_handleStationeryBundles;
- (void)_handleSyncNotification:(id)arg1;
- (void)_informUserOfDatabaseError:(id)arg1;
- (void)_insertAccount:(id)arg1 atIndex:(NSUInteger)arg2 withScriptingAccounts:(id)arg3;
- (BOOL)_isAccountCurrentlySynchronizing:(id)arg1;
- (BOOL)_isMailboxBeingViewedSpecial;
- (void)_loadBundles;
- (void)_mailAttachments:(id)arg1;
- (void)_mailDocuments:(id)arg1;
- (void)_mailImagesAsData:(id)arg1;
- (id)_mailboxBeingViewed;
- (id)_mailboxMenu;
- (void)_migrateDefaultsToSharedDomain;
- (void)_migrateDisableRemoteContentToSharedDomain;
- (void)_migrateExternalUpdates;
- (void)_migrateRecentsToCoreRecents;
- (void)_migrateVIPPlist;
- (void)_modifyAccountsWithTypeIdentifiers:(id)arg1 modifier:(id)arg2;
- (BOOL)_moreThanOneAccountCanGoOffline;
- (BOOL)_needToCreateLibraryUpgradingIfNecessary;
- (void)_networkConfigurationChanged:(id)arg1;
- (void)_nowWouldBeAGoodTimeForHandler:(id)arg1 toTerminateFromSelector:(SEL)arg2;
- (void)_performDelayedInitialization;
- (void)_performPostAccountSetupWithDidFinishLaunchingNotification:(id)arg1;
- (void)_preserveSignatureAboveQuotedTextPreference;
- (void)_provisionAndEnableSMTPAccounts;
- (void)_registerAppleEventHandlers;
- (void)_registerAppleEventQueue;
- (void)_removeAllItemsInAccountMenuWithTag:(long long)arg1;
- (void)_removeContainerLogs;
- (void)_removeExtraSeparatorsInMailboxMenu;
- (void)_removeFromAccountsCurrentlySynchronizing:(id)arg1;
- (void)_removeRedundantAliases;
- (void)_removeSpotlightValidationDefaults;
- (void)_removeV3Backup;
- (void)_removeViewRelatedMessagesToolbarButtonByDefault;
- (void)_resetMailboxListVisibleSections;
- (void)_resetMenuItemWithTag:(long long)arg1;
- (void)_restoreMessagesFromDefaults;
- (void)_rulesChanged:(id)arg1;
- (void)_setAutoFetchFrequencyToAutomatic;
- (void)_setSourceOnGmailLabels;
- (void)_setupAccountMenuItems;
- (void)_setupCheckSpellingSubMenu;
- (void)_setupInitialState;
- (void)_setupQuitMenu;
- (void)_showDatabaseAlert:(BOOL)arg1 databaseFile:(id)arg2;
- (void)_showReadOnlyFolderAlert:(id)arg1;
- (void)_showUnresolvedFolderAlert:(id)arg1;
- (BOOL)_showViewerWindow:(id)arg1;
- (void)_switchToolbarsToIconOnly;
- (void)_synchronizeAccountListMenuWithTagIfNeeded:(long long)arg1;
- (void)_terminateNoConfirm;
- (void)_terminationTimerFired:(id)arg1;
- (void)_timeMachineSendEvent:(id)arg1;
- (void)_tryToPerformDelayedInitialization;
- (void)_turnOnConversationView;
- (void)_unregisterAppleEventHandlers;
- (void)_updateDefaultCachePolicy;
- (void)_updateEmailAliases;
- (void)_upgradeComposeWindowReplyOrForwardToolbar;
- (void)_upgradeExpandedMailboxesPreference;
- (void)_upgradeFlagToolbarItems;
@property(retain, nonatomic) MFAccountFactory_macOS *accountFactory; // @synthesize accountFactory=_accountFactory;
- (id)accounts;
@property(nonatomic) BOOL accountsAreNew; // @synthesize accountsAreNew=_accountsAreNew;
@property BOOL accountsHaveBeenConfigured; // @synthesize accountsHaveBeenConfigured=_accountsHaveBeenConfigured;
@property(readonly, nonatomic) MailActivityNotifier *activityNotifier; // @synthesize activityNotifier=_activityNotifier;
@property(readonly, nonatomic) ActivityWindowController *activityWindowController; // @synthesize activityWindowController=_activityWindowController;
- (void)addAccount:(id)arg1;
@property(retain, nonatomic) NSMenu *addButtonMenu;
- (void)addFontTrait:(id)arg1;
@property(readonly, nonatomic) BOOL addInvitationsToCalendarAutomatically;
- (void)addInvitationsToCalendarFromMessages:(id)arg1;
- (void)addTerminationHandler:(id)arg1;
- (void)alwaysAttachFilesAtEnd:(id)arg1;
- (BOOL)alwaysBCCMyself;
@property(nonatomic) BOOL alwaysCCMyself;
- (void)alwaysSendWindowsFriendlyAttachments:(id)arg1;
- (id)aosImapAccounts;
@property(nonatomic) double appDidFinishLaunchingTime; // @synthesize appDidFinishLaunchingTime=_appDidFinishLaunchingTime;
@property(nonatomic) BOOL appHasFinishedLaunching; // @synthesize appHasFinishedLaunching=_appHasFinishedLaunching;
- (id)applescriptSelection;
- (BOOL)application:(id)arg1 continueUserActivity:(id)arg2 restorationHandler:(id)arg3;
- (void)application:(id)arg1 didFailToContinueUserActivityWithType:(id)arg2 error:(id)arg3;
- (BOOL)application:(id)arg1 openFile:(id)arg2;
- (void)application:(id)arg1 openFiles:(id)arg2;
- (BOOL)application:(id)arg1 willContinueUserActivityWithType:(id)arg2;
- (void)applicationDidBecomeActive:(id)arg1;
- (void)applicationDidFinishLaunching:(id)arg1;
- (void)applicationDidUnhide:(id)arg1;
@property(readonly, nonatomic) BOOL applicationIsInBackgroundMode;
- (BOOL)applicationOpenUntitledFile:(id)arg1;
- (BOOL)applicationShouldHandleReopen:(id)arg1 hasVisibleWindows:(BOOL)arg2;
- (NSUInteger)applicationShouldTerminate:(id)arg1;
- (id)applicationVersion;
@property(readonly, nonatomic) BOOL applicationWillBeRestoredByTAL;
- (void)applicationWillFinishLaunching:(id)arg1;
- (void)applicationWillTerminate:(id)arg1;
- (void)attachFilesAtEnd:(id)arg1;
- (long long)autoFetchFrequency;
@property(nonatomic) BOOL autoLaunchHidden; // @synthesize autoLaunchHidden=_autoLaunchHidden;
@property(nonatomic) BOOL autosaveComposeWindows;
- (void)bringUpEmptyTrashMenu:(id)arg1;
- (void)bringUpGetNewMailMenu:(id)arg1;
- (void)bringUpOnlineOfflineMenu:(id)arg1;
- (void)bringUpSynchronizeAccountMenu:(id)arg1;
@property(nonatomic) BOOL checkGrammarWithSpelling;
- (void)checkNewMail:(id)arg1;
- (void)checkNewMailInSelectedAccounts:(id)arg1;
- (BOOL)chooseSignatureWhenComposing;
- (void)closeAll:(id)arg1;
- (BOOL)colorQuotedText;
- (void)compactSelectedMailboxes:(id)arg1;
@property(retain, nonatomic) NSMenu *composeAttachmentContextMenu;
- (id)composeMessages;
- (void)connectAllAccounts:(id)arg1;
- (void)connectAllAccountsFromContextMenu:(id)arg1;
- (void)connectThisAccount:(id)arg1;
- (void)connectThisAccountFromContextMenu:(id)arg1;
- (void)dealloc;
@property(nonatomic) unsigned int defaultMessageFormat;
- (id)deliveryAccounts;
@property(readonly, nonatomic) DeliveryQueue *deliveryQueue;
@property(retain, nonatomic) DifferentialPrivacyReporter_macOS *differentialPrivacyReporter; // @synthesize differentialPrivacyReporter=_differentialPrivacyReporter;
- (void)disconnectAllAccounts:(id)arg1;
- (void)disconnectAllAccountsFromContextMenu:(id)arg1;
- (void)disconnectThisAccount:(id)arg1;
- (void)disconnectThisAccountFromContextMenu:(id)arg1;
- (BOOL)doParentalControlProcessingForMessage:(id)arg1;
@property(nonatomic) __weak DockCountController *dockCountController; // @synthesize dockCountController=_dockCountController;
@property(nonatomic) BOOL downloadHTMLAttachments;
- (id)draftsMailbox;
- (void)editAccount:(id)arg1;
- (void)emptyTrashInAccount:(id)arg1;
@property(nonatomic) BOOL encryptOutgoingMessages;
- (void)eraseJunkMail:(id)arg1;
@property(nonatomic) long long *errorDiagnosisResult; // @synthesize errorDiagnosisResult=_errorDiagnosisResult;
@property(retain, nonatomic) NSWindow *errorDiagnosisWindow; // @synthesize errorDiagnosisWindow=_errorDiagnosisWindow;
@property(retain, nonatomic) DynamicErrorWindowController *errorDiagnosisWindowController; // @synthesize errorDiagnosisWindowController=_errorDiagnosisWindowController;
@property(nonatomic) BOOL expandGroupAddresses;
- (id)fixedWidthFont;
- (double)fixedWidthFontSize;
@property(retain, nonatomic) FlagIconFactory *flagIconFactory; // @synthesize flagIconFactory=_flagIconFactory;
@property(retain, nonatomic) FlagsMenuItemView *flagsMenuItemView; // @synthesize flagsMenuItemView=_flagsMenuItemView;
- (void)fontsAndColorsPreferencesDidChange;
- (void)fontsAndColorsPreferencesDidChange:(BOOL)arg1;
- (id)frameworkVersion;
@property(nonatomic) BOOL groupingByThreadDefaultsToOn;
- (id)handleCheckMailCommand:(id)arg1;
- (BOOL)handleClickOnURL:(id)arg1 visibleText:(id)arg2 window:(id)arg3 dontSwitch:(BOOL)arg4;
- (void)handleDiagnosticsEvent:(id)arg1 replyEvent:(id)arg2;
- (void)handleGURLAppleEvent:(id)arg1 replyEvent:(id)arg2;
- (id)handleImportMboxCommand:(id)arg1;
- (BOOL)handleMailToURL:(id)arg1;
- (void)handleMailWebLinkEvent:(id)arg1 replyEvent:(id)arg2;
- (void)handleMailWebPageEvent:(id)arg1 replyEvent:(id)arg2;
- (BOOL)handleMessageURL:(id)arg1;
- (void)handleSafariPDFEvent:(id)arg1 replyEvent:(id)arg2;
- (void)handleSafariPageArchiveEvent:(id)arg1 replyEvent:(id)arg2;
- (void)handleSafariReaderArchiveEvent:(id)arg1 replyEvent:(id)arg2;
- (void)handleShowAccountPreferencesEvent:(id)arg1 replyEvent:(id)arg2;
- (id)handleSynchronizeAccountCommand:(id)arg1;
- (void)handler:(id)arg1 approvedQuit:(BOOL)arg2;
@property BOOL hasPerformedDelayedInitialization; // @synthesize hasPerformedDelayedInitialization=_hasPerformedDelayedInitialization;
@property(nonatomic) BOOL hasUpdatedEmailAliases; // @synthesize hasUpdatedEmailAliases=_hasUpdatedEmailAliases;
- (unsigned int)headerDetail;
@property(readonly, copy, nonatomic) NSArray *headersRequiredForParentalControl;
@property(readonly, copy, nonatomic) NSArray *headersRequiredForRouting;
- (id)imapAccounts;
- (void)importMailboxes:(id)arg1;
- (id)inbox;
@property(nonatomic) BOOL includeAllOfOriginalMessage;
@property(nonatomic) BOOL includeOriginalMessage;
- (id)indicesOfObjectsByEvaluatingObjectSpecifier:(id)arg1;
- (void)informUserOfBusyDatabaseWithRecoverer:(id)arg1 diagnosis:(long long *)arg2;
- (void)informUserOfIOErrorWithStateIn:(long long *)arg1;
- (id)init;
@property(readonly, nonatomic) NSOperationQueue *initializationQueue; // @synthesize initializationQueue=_initializationQueue;
@property(nonatomic) BOOL inlineSpellCheckingEnabled;
- (void)insertInMailboxes:(id)arg1;
- (void)insertInMailboxes:(id)arg1 atIndex:(NSUInteger)arg2;
- (void)insertInMessageViewers:(id)arg1;
- (void)insertInMessageViewers:(id)arg1 atIndex:(NSUInteger)arg2;
- (void)insertInRules:(id)arg1;
- (void)insertInRules:(id)arg1 atIndex:(NSUInteger)arg2;
- (void)insertInSignatures:(id)arg1;
- (void)insertInSignatures:(id)arg1 atIndex:(NSUInteger)arg2;
- (void)insertObject:(id)arg1 inAccountsAtIndex:(NSUInteger)arg2;
- (void)insertObject:(id)arg1 inAosImapAccountsAtIndex:(NSUInteger)arg2;
- (void)insertObject:(id)arg1 inComposeMessagesAtIndex:(NSUInteger)arg2;
- (void)insertObject:(id)arg1 inDeliveryAccountsAtIndex:(NSUInteger)arg2;
- (void)insertObject:(id)arg1 inImapAccountsAtIndex:(NSUInteger)arg2;
- (void)insertObject:(id)arg1 inMessageEditorsAtIndex:(NSUInteger)arg2;
- (void)insertObject:(id)arg1 inPopAccountsAtIndex:(NSUInteger)arg2;
- (void)insertOriginalAttachments:(id)arg1;
@property BOOL isCurrentlyTerminating; // @synthesize isCurrentlyTerminating=_isCurrentlyTerminating;
@property BOOL isExitingFullscreen; // @synthesize isExitingFullscreen=_isExitingFullscreen;
@property(nonatomic) BOOL isInTimeMachineMode;
@property(readonly, nonatomic) BOOL isTerminating;
@property(readonly, nonatomic) long long junkMailBehavior;
- (id)junkMailbox;
- (unsigned int)levelOneQuotingColor;
- (unsigned int)levelThreeQuotingColor;
- (unsigned int)levelTwoQuotingColor;
- (void)loadMailboxesContextMenuNib;
@property(readonly, copy, nonatomic) NSArray *loadedBundles; // @synthesize loadedBundles=_loadedBundles;
@property(readonly, nonatomic) NSURL *localAttachmentFilesDirectory;
- (id)logActivityOnHosts;
- (id)logActivityOnPorts;
- (BOOL)logAllSocketActivity;
@property(readonly, nonatomic) MailBundleController *mailBundleController; // @synthesize mailBundleController=_mailBundleController;
- (void)mailSelection:(id)arg1 userData:(id)arg2 error:(id *)arg3;
- (void)mailTo:(id)arg1 userData:(id)arg2 error:(id *)arg3;
- (id)mailboxes;
@property(retain, nonatomic) NSMenu *mailboxesContextMenu;
@property(retain, nonatomic) MailboxesController *mailboxesController; // @synthesize mailboxesController=_mailboxesController;
- (id)makeTouchBar;
- (void)menuWillOpen:(id)arg1;
- (id)messageEditor;
- (id)messageEditors;
- (id)messageFont;
- (double)messageFontSize;
- (id)messageListFont;
- (double)messageListFontSize;
@property(retain, nonatomic) NSMenu *messageViewerContextMenu;
- (id)messageViewers;
- (id)newMailSound;
@property(copy, nonatomic) NSString *newMessagesSoundName;
- (id)newScriptingObjectOfClass:(Class)arg1 forValueForKey:(id)arg2 withContentsValue:(id)arg3 properties:(id)arg4;
- (void)newViewerWindow:(id)arg1;
- (void)nowWouldBeAGoodTimeToTerminate:(id)arg1;
- (void)openHelpTopic:(id)arg1;
- (id)openMessageEditorWithMessageBody:(id)arg1 headers:(id)arg2 activatingApp:(BOOL)arg3;
- (id)openStoreWithMailbox:(id)arg1;
- (id)openStoreWithMailbox:(id)arg1 andMakeKey:(BOOL)arg2;
- (void)openSystemAccountPreferences:(id)arg1;
- (BOOL)openTemporaryAttachments:(id)arg1 applicationBundle:(id)arg2;
- (void)orderFrontStylesPanel:(id)arg1;
- (id)outbox;
@property(nonatomic) BOOL paused; // @synthesize paused=_paused;
- (void)performPostPersistenceUpgrades;
- (void)performPrePersistenceUpgrades;
- (void)performSynchronizationForAccounts:(id)arg1;
- (id)popAccounts;
@property(retain, nonatomic) NSWindowController *preferencesController; // @synthesize preferencesController=_preferencesController;
- (long long)queryUserForBigMessageAction:(id)arg1;
- (BOOL)queryUserWithMessageText:(id)arg1 informativeText:(id)arg2 defaultButton:(id)arg3 alternateButton:(id)arg4;
- (void)queueAppleEvent:(id)arg1 replyEvent:(id)arg2;
- (void)quitAndRelaunchWithAdditionalArguments:(id)arg1;
- (void)quitNoMatterWhat;
- (unsigned int)quotingColorForLevel:(NSUInteger)arg1;
- (unsigned int)quotingColorValue:(id)arg1;
- (void)removeFromMessageViewersAtIndex:(NSUInteger)arg1;
- (void)removeFromRulesAtIndex:(NSUInteger)arg1;
- (void)removeFromSignaturesAtIndex:(NSUInteger)arg1;
- (void)removeObjectFromAccountsAtIndex:(NSUInteger)arg1;
- (void)removeObjectFromAosImapAccountsAtIndex:(NSUInteger)arg1;
- (void)removeObjectFromComposeMessagesAtIndex:(NSUInteger)arg1;
- (void)removeObjectFromDeliveryAccountsAtIndex:(NSUInteger)arg1;
- (void)removeObjectFromImapAccountsAtIndex:(NSUInteger)arg1;
- (void)removeObjectFromMessageEditorsAtIndex:(NSUInteger)arg1;
- (void)removeObjectFromPopAccountsAtIndex:(NSUInteger)arg1;
- (void)removeTerminationHandler:(id)arg1;
- (void)replaceInMailboxes:(id)arg1 atIndex:(NSUInteger)arg2;
@property(nonatomic) BOOL replyInSameFormat;
- (void)replyToApplicationShouldTerminate:(BOOL)arg1;
- (void)resignSelectionFor:(id)arg1;
- (id)rules;
- (long long)runAlertPanelWithTitle:(id)arg1 firstButtonTitle:(id)arg2 secondButtonTitle:(id)arg3 thirdButtonTitle:(id)arg4 message:(id)arg5;
- (void)runPageLayout:(id)arg1;
@property(nonatomic) BOOL runningEmptyTrashSheet; // @synthesize runningEmptyTrashSheet=_runningEmptyTrashSheet;
- (void)selectMailbox:(id)arg1;
- (id)selectedSignature;
@property(readonly, copy, nonatomic) NSArray *selection;
- (id)selectionExpandingThreadsAndHiddenCopies:(BOOL)arg1;
@property(nonatomic) __weak id <SelectionOwner> selectionOwner; // @synthesize selectionOwner=_selectionOwner;
- (void)sendEvent:(id)arg1;
- (void)sendWindowsFriendlyAttachments:(id)arg1;
- (id)sentMailbox;
- (void)setAlwaysBCCMyself:(BOOL)arg1;
- (void)setAutoFetchFrequency:(long long)arg1;
- (void)setChooseSignatureWhenComposing:(BOOL)arg1;
- (void)setColorQuotedText:(BOOL)arg1;
- (void)setFixedPitchFont:(id)arg1 size:(double)arg2;
- (void)setFixedWidthFont:(id)arg1;
- (void)setFixedWidthFontSize:(double)arg1;
- (void)setHeaderDetail:(unsigned int)arg1;
- (void)setLevelOneQuotingColor:(unsigned int)arg1;
- (void)setLevelThreeQuotingColor:(unsigned int)arg1;
- (void)setLevelTwoQuotingColor:(unsigned int)arg1;
- (void)setLogActivityOnHosts:(id)arg1;
- (void)setLogActivityOnPorts:(id)arg1;
- (void)setLogAllSocketActivity:(BOOL)arg1;
- (void)setMessageFont:(id)arg1;
- (void)setMessageFont:(id)arg1 size:(double)arg2;
- (void)setMessageFontSize:(double)arg1;
- (void)setMessageListFont:(id)arg1;
- (void)setMessageListFontSize:(double)arg1;
- (void)setNewMailSound:(id)arg1;
- (void)setQuotingColor:(unsigned int)arg1 forLevel:(NSUInteger)arg2;
- (void)setSelectedSignature:(id)arg1;
- (void)setSelectionFrom:(id)arg1;
- (void)setShouldCheckIntranetDomains:(BOOL)arg1 withString:(id)arg2;
@property(nonatomic) BOOL shouldHighlightThreads;
@property(nonatomic) BOOL shouldPlayOtherMailSounds;
@property(nonatomic) BOOL shouldShowUnreadMessagesInBold;
@property(nonatomic) BOOL shouldUpdateEmailAliasesOnNextActivation; // @synthesize shouldUpdateEmailAliasesOnNextActivation=_shouldUpdateEmailAliasesOnNextActivation;
@property(nonatomic) BOOL signOutgoingMessages;
@property(retain, nonatomic) SortByMenuDelegate *sortByMenuDelegate; // @synthesize sortByMenuDelegate=_sortByMenuDelegate;
@property(nonatomic) long long spellCheckingBehavior;
@property BOOL synchronizingAllAccounts; // @synthesize synchronizingAllAccounts=_synchronizingAllAccounts;
@property(retain, nonatomic) NSTouchBar *touchBar; // @synthesize touchBar=_touchBar;
@property(nonatomic) BOOL useAddressCompletion;
- (void)setUseFixedWidthFont:(BOOL)arg1;
- (void)setUseKeychain:(BOOL)arg1;
@property(retain, nonatomic) NSMenu *viewAttachmentContextMenu;
- (void)shareInMailEvent:(id)arg1 replyEvent:(id)arg2;
- (id)sharedAttachmentContextMenu;
- (BOOL)shouldRestoreStateOnNextLaunch;
- (void)showAccountInPreferences:(id)arg1;
- (void)showAccountInfo:(id)arg1;
- (void)showActivityViewer:(id)arg1;
- (void)showAddressHistoryPanel:(id)arg1;
- (void)showComposeWindow:(id)arg1;
- (void)showConnectionDoctor:(id)arg1;
- (void)showMediaBrowser:(id)arg1;
- (void)showPreferencesPanel:(id)arg1;
- (void)showReleaseNotes:(id)arg1;
- (void)showSMTPServerListWithSelectedAccount:(id)arg1;
- (void)showSignaturesPreferences;
- (void)showViewerWindow:(id)arg1;
- (id)signatures;
- (void)storeBeingInvalidated:(id)arg1;
- (void)synchronizeAccount:(id)arg1;
- (void)tabView:(id)arg1 didSelectTabViewItem:(id)arg2;
- (void)timeMachineDismiss:(id)arg1;
- (void)toggleAccountOnlineStatus:(id)arg1;
- (void)toggleThreadedMode:(id)arg1;
@property(readonly, nonatomic) NSMenu *toolbarItemCopyMenu;
@property(readonly, nonatomic) NSMenu *toolbarItemMoveMenu;
- (id)touchBar:(id)arg1 makeItemForIdentifier:(id)arg2;
- (void)transformToBackground;
- (void)transformToForeground;
- (id)trashMailbox;
- (void)updateEmailAliasesIfNeeded;
- (void)updateEmailAliasesOnNextActivation;
- (BOOL)useFixedWidthFont;
- (BOOL)useKeychain;
@property(readonly, nonatomic) UserActivityHandler *userActivityHandler; // @synthesize userActivityHandler=_userActivityHandler;
@property(readonly, nonatomic) NSUserDefaults *userDefaults;
- (BOOL)validateMenuItem:(id)arg1;
- (BOOL)validateToolbarItem:(id)arg1;
- (id)valueInComposeMessagesWithUniqueID:(id)arg1;
- (id)valueInMailboxesWithName:(id)arg1;
- (id)valueInMessageViewersWithUniqueID:(id)arg1;
@property(readonly, nonatomic) BOOL visibleMessageViewerExists;
- (void)willPresentContextualMenu:(id)arg1;
@property(readonly, nonatomic) NSOperationQueue *workQueue; // @synthesize workQueue=_workQueue;

// Remaining properties
@property(readonly, copy) NSString *debugDescription;
@property(readonly, copy) NSString *description;
@property(readonly, copy, nonatomic) NSString *displayName;
@property(readonly) NSUInteger hash;
@property(readonly) Class superclass;

@end
