//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


#import "FlaggedStatusToolbarItemDelegate-Protocol.h"
//#import "MCActivityTarget-Protocol.h"
#import "MailTableViewDelegateDelegate-Protocol.h"
#import "MailboxSelectionOwner-Protocol.h"
#import "MailboxesOutlineViewControllerDelegate-Protocol.h"
#import "MessageListControllerDelegate-Protocol.h"
#import "MessageTransferDelegate-Protocol.h"
#import "MessageViewerSearchFieldFocusDelegate-Protocol.h"
#import "SGTSearchFieldQueryScopeDelegate-Protocol.h"
#import "TerminationHandler-Protocol.h"

@class ActivityViewController, FavoritesBarView, FavoritesBarViewController, FlaggedStatusToolbarItem, FullScreenModalCapableWindow, FullScreenWindowController, MCMessage, MFBehaviorTracker, MFMailbox, MailBarContainerView, MailToolbar, MailboxesOutlineViewController, MailboxesViewController, MessageListController, MessageMall, MessageSelection, MessageViewerFullScreenMinimizeTray, MessageViewerSearchField, NSArray, NSDictionary, NSIndexSet, NSLayoutConstraint, NSMenu, NSMenuItem, NSMutableArray, NSNumber, NSSet, NSSplitViewController, NSString, NSTextField, NSTimer, NSToolbarItem, NSView, NSWindow, SGTMailQueryGenius, ViewingPaneViewController;

@interface MessageViewer : NSResponder <FlaggedStatusToolbarItemDelegate, MessageViewerSearchFieldFocusDelegate, NSToolbarDelegate, MessageListControllerDelegate, MailboxesOutlineViewControllerDelegate, MailboxSelectionOwner, MailTableViewDelegateDelegate, MCActivityTarget, MessageTransferDelegate, NSAnimationDelegate, NSSpeechSynthesizerDelegate, NSUserInterfaceValidations, NSWindowDelegate, NSWindowRestoration, SGTSearchFieldQueryScopeDelegate, TerminationHandler>
{
    MessageMall *_messageMall;
    NSString *_searchPhrase;
    NSSet *_initiallySelectedMessages;
    NSMutableArray *_transferOperations;
    FullScreenWindowController *_fullScreenWindowController;
    struct __MDQuery *_lowPriorityQuery;
    struct __MDQuery *_highPriorityQuery;
    NSMutableArray *_mailboxesNeedingAlerts;
    BOOL _isShowingMailboxAlert;
    BOOL _ignoreSearchBarUpdates;
    BOOL _previouslyHadSentScope;
    BOOL _allowShowingDeletedMessages;
    BOOL _suppressWindowTitleUpdates;
    BOOL _didSetupUI;
    BOOL _shouldCascadeWhenShowing;
    BOOL _atLeastOneSelectedMessageIsInOutbox;
    BOOL _atLeastOneSelectedMessageIsInOutboxIsValid;
    BOOL _atLeastOneSelectedMessageIsInDrafts;
    BOOL _atLeastOneSelectedMessageIsInDraftsIsValid;
    BOOL _changingSplitViewOrientation;
    BOOL _timeMachineRestoreIsInProgress;
    BOOL _performedEarlyDealloc;
    ViewingPaneViewController *_viewingPaneViewController;
    MessageListController *_messageListController;
    FullScreenModalCapableWindow *_window;
    MessageViewerFullScreenMinimizeTray *_fullScreenMinimizeTray;
    NSView *_contentView;
    NSSplitViewController *_mailboxesSplitViewController;
    MailboxesViewController *_mailboxesViewController;
    ActivityViewController *_activityViewController;
    MessageViewerSearchField *_searchField;
    NSToolbarItem *_searchViewItem;
    FlaggedStatusToolbarItem *_flaggedStatusToolbarItem;
    NSToolbarItem *_fullScreenFlagMenuToolbarItem;
    MailToolbar *_toolbar;
    NSDictionary *_toolbarItems;
    NSMenu *_tableHeaderMenu;
    NSMenu *_sortByTableHeaderMenu;
    NSDictionary *_savedAttributes;
    NSWindow *_timeMachineRestoreMessagesWindow;
    NSTextField *_timeMachineRestoreMessagesField;
    NSWindow *_timeMachineRestoreMailboxWindow;
    NSTextField *_timeMachineRestoreMailboxField;
    FavoritesBarViewController *_favoritesBarViewController;
    NSString *_searchQuery;
    long long _currentSearchField;
    long long _searchTarget;
    long long _selectedTag;
    NSMenu *_messageColumnsMenu;
    NSMenu *_messageSortByMenu;
    NSMenuItem *_columnsMenuItem;
    NSMenuItem *_sortByMenuItem;
    NSMenuItem *_dateReceivedMenuItem;
    NSMenuItem *_dateSentMenuItem;
    NSMenuItem *_dateReceivedTableHeaderMenuItem;
    NSMenuItem *_dateSentTableHeaderMenuItem;
    NSArray *_mailboxesToDisplayWhenVisible;
    NSDictionary *_initialWindowState;
    NSNumber *_uniqueID;
    NSTimer *_timeMachineRestoreSheetTimer;
    NSSplitViewController *_contentSplitViewController;
    MFBehaviorTracker *_behaviorTracker;
    NSLayoutConstraint *_minimizeTrayHeight;
    NSLayoutConstraint *_minimizeTrayTabBarWidth;
}

+ (BOOL)_isMessageViewer:(id)arg1 includeSingleMessageViewer:(BOOL)arg2;
+ (void)_mailApplicationDidFinishLaunching:(id)arg1;
+ (id)_mailboxesForPaths:(id)arg1;
+ (id)_messageViewersByUniqueID;
+ (void)_registerNewViewer:(id)arg1;
+ (id)allMessageViewers;
+ (id)allSingleMessageViewers;
+ (BOOL)automaticallyNotifiesObserversOfSearchPhrase;
+ (void)clearDelayedWindowRestorations;
+ (long long)deleteOperationForEvent:(id)arg1 isKeyPressed:(BOOL)arg2;
+ (void)deregisterViewer:(id)arg1;
+ (id)existingViewerForMailbox:(id)arg1;
+ (id)existingViewerShowingMessage:(id)arg1;
+ (id)frontmostMessageViewerWithOptions:(NSUInteger)arg1;
+ (void)initialize;
+ (id)keyPathsForValuesAffectingFavoritesBarView;
+ (id)keyPathsForValuesAffectingMailBarContainerView;
+ (id)mailboxesBeingViewed;
+ (id)messageViewerForUniqueID:(id)arg1;
+ (id)newDefaultMessageViewer;
+ (void)restoreAllViewersFromDefaults;
+ (void)restoreWindowWithIdentifier:(id)arg1 state:(id)arg2 completionHandler:(id)arg3;
+ (void)searchForString:(id)arg1;
+ (void)showAllViewers;
+ (id)toolbarIdentifier;
+ (id)viewerForMailboxWithTag:(long long)arg1;
- (void)_animateMessageSelectionToFavoriteButtonAtPosition:(NSUInteger)arg1 withCount:(NSUInteger)arg2 image:(id)arg3 fromPosition:(struct CGPoint)arg4;
- (void)_asyncUpdateSuggestionsFlagNames:(id)arg1;
- (void)_asyncUpdateSuggestionsMailboxesListAndFlagNames:(id)arg1;
- (BOOL)_atLeastOneSelectedMessageIsInDrafts;
- (BOOL)_atLeastOneSelectedMessageIsInOutbox;
- (void)_beginTimeMachineRestoreSheetIsForMailbox:(id)arg1;
- (BOOL)_canSaveSearchWithTarget:(long long)arg1;
- (BOOL)_canSearchSelectedMailboxes;
- (void)_cantFindFollowupToMessage:(id)arg1;
- (void)_changeFlag:(id)arg1 state:(BOOL)arg2 forMessages:(id)arg3 undoActionName:(id)arg4;
- (void)_clearSearchByAnimating:(BOOL)arg1;
- (id)_columnOrDetailMenuItemTitle;
- (id)_countStringForType:(BOOL)arg1 isDrafts:(BOOL)arg2 omitUnread:(BOOL)arg3 totalCount:(NSUInteger *)arg4;
- (void)_createUniqueID;
- (id)_criterionForMailbox:(id)arg1;
- (id)_defaultWindowStateDictionary;
- (void)_deleteJunkedMessages:(id)arg1 inStores:(id)arg2 moveToTrash:(BOOL)arg3;
- (void)_diagnosticsNotificationReceived:(id)arg1;
- (void)_disableSplitViewAutosaving;
- (void)_displayFollowup:(id)arg1;
- (void)_displaySelectedMessageInSeparateWindow;
- (void)_displayTimeMachineRestoreSheet:(id)arg1;
- (id)_documentsToDisplaySelectedMessagesInSeperateWindow;
- (void)_earlyDealloc;
- (long long)_editedMessageTypeForAction:(SEL)arg1;
- (void)_enableSplitViewAutosaving;
- (void)_ensureItemVisibilityInToolbar:(long long)arg1 identifier:(id)arg2;
- (void)_findSomeDefaultsIfNecessary;
- (void)_firstResponderIsViewingPane:(char *)arg1 isMessageList:(char *)arg2;
- (id)_flaggedStatusForMessages:(id)arg1;
- (void)_handleAttachmentsRemovedFromMessages:(id)arg1 newMessages:(id)arg2;
- (BOOL)_hasSentScope;
- (void)_hideSearchResultsInSearchView;
- (BOOL)_isShowingMessage:(id)arg1;
- (BOOL)_isViewingMailbox:(id)arg1;
- (void)_mailboxDisplayCountChanged:(id)arg1;
- (void)_mailboxWasRenamed:(id)arg1;
- (void)_mailboxesDidChange:(id)arg1;
- (id)_mailboxesFromAttributes:(id)arg1;
- (BOOL)_mailboxesPaneIsOpenWideEnoughToUse;
- (void)_markMessagesAsJunkMail:(id)arg1 stores:(id)arg2;
- (void)_markMessagesAsNotJunkMail:(id)arg1 stores:(id)arg2;
- (void)_messageViewerCommonInit;
- (BOOL)_messages:(id)arg1 containMessagesWithFlaggedStatusEqualTo:(BOOL)arg2;
- (BOOL)_messages:(id)arg1 containMessagesWithJunkMailLevelEqualTo:(long long)arg2;
- (BOOL)_messages:(id)arg1 containMessagesWithReadStatusEqualTo:(BOOL)arg2;
- (long long)_messages:(id)arg1 stateForFlagColor:(BOOL)arg2;
- (BOOL)_messagesContainMessagesWithAttachments:(id)arg1;
- (id)_messagesWithoutFlagColor:(BOOL)arg1 fromMessages:(id)arg2;
- (void)_moveMessagesToFavoriteWithMailbox:(id)arg1 andPosition:(NSUInteger)arg2;
- (void)_moveOrCopyMessagesToMailbox:(id)arg1 deleteOriginals:(BOOL)arg2;
- (void)_reallyUpdateWindowTitle:(id)arg1;
- (void)_registerForApplicationNotifications;
- (void)_removeAttachmentsFromMessages:(id)arg1 fromStores:(id)arg2;
- (void)_reportError:(id)arg1;
- (void)_restoreFromDefaultWindowStateDictionary:(id)arg1;
- (void)_routeMessages:(id)arg1 fromMailboxes:(id)arg2;
- (void)_routeMessages:(id)arg1 fromStores:(id)arg2 fetchingBodies:(id)arg3 messagesNeedingBodies:(id)arg4;
- (double)_searchDelay;
- (void)_searchForSuggestions:(id)arg1;
- (NSUInteger)_searchResultCount;
- (id)_searchScopeMailboxes;
- (id)_selectedLabels;
- (BOOL)_selectedMailboxesAreOutgoing:(char *)arg1;
- (id)_selectedMessagesWhoseFlag:(unsigned int)arg1 isEqualToState:(BOOL)arg2 action:(SEL)arg3;
- (void)_sendMessages:(id)arg1 forDraft:(BOOL)arg2;
- (void)_setFlaggedStatus:(id)arg1 withUndoActionName:(id)arg2;
- (void)_setMailboxes:(id)arg1;
- (void)_setPrioritySuggestionsWithHighPriority:(BOOL)arg1 withLowPriority:(BOOL)arg2;
- (void)_setUpMenus;
- (void)_setupFromAttributes;
- (void)_setupMailboxOutlineView;
- (void)_setupPrioritySuggestions:(id)arg1;
- (void)_setupSearchParametersForTag:(long long)arg1;
- (void)_setupUIAndOrderFront:(BOOL)arg1 andMakeKey:(BOOL)arg2;
- (BOOL)_shouldUseLayoutContraintsForWindow:(id)arg1;
- (void)_showAlertForNextMailboxNeedingAlert;
- (void)_showEditorForAction:(SEL)arg1;
- (void)_showSearchResultsInSearchView;
- (void)_synchronizeFullScreenFlagToolbarItem:(id)arg1;
- (void)_synchronouslyMarkAsJunkMail:(id)arg1 inStores:(id)arg2 delete:(BOOL)arg3;
- (void)_synchronouslyMarkAsNotJunkMail:(id)arg1;
- (void)_timeMachineRestoreFinished:(id)arg1;
- (void)_undoMarkMessagesAsJunkMail:(id)arg1 stores:(id)arg2;
- (void)_unregisterForApplicationNotifications;
- (void)_updateMailboxNameVisibility;
- (void)_updateMallboxes:(id)arg1;
- (void)_updateSearchItemLabel;
- (void)_updateSearchStatus;
- (void)_updateSearchStatusWithDelay;
- (void)_updateSearchUIForSender:(id)arg1;
- (void)_updateSuggestionsFlagNames;
- (void)_updateSuggestionsMailboxesListAndFlagNames;
- (void)_updateUnreadCountQueries:(id)arg1;
- (void)_viewerLayoutPreferenceChanged;
- (void)_windowDidExitFullScreen:(id)arg1;
- (void)_windowDidResize:(id)arg1;
- (void)_windowWillEnterFullScreen:(id)arg1;
- (void)_windowWillExitFullScreen:(id)arg1;
- (BOOL)acceptsPreviewPanelControl:(id)arg1;
@property(retain, nonatomic) ActivityViewController *activityViewController; // @synthesize activityViewController=_activityViewController;
- (void)addSenderToContacts:(id)arg1;
- (id)allMessages;
@property(nonatomic) BOOL allowShowingDeletedMessages; // @synthesize allowShowingDeletedMessages=_allowShowingDeletedMessages;
- (BOOL)allowViewerToClose;
@property(nonatomic) unsigned int appleScriptSortColumn;
@property(readonly, copy, nonatomic) NSIndexSet *appliedFlagColorsForActionMessages;
- (void)archiveMessages:(id)arg1;
- (BOOL)archiveMessages:(id)arg1 allowUndo:(BOOL)arg2 withAnimationOptions:(NSUInteger)arg3;
@property(nonatomic) BOOL atLeastOneSelectedMessageIsInDrafts; // @synthesize atLeastOneSelectedMessageIsInDrafts=_atLeastOneSelectedMessageIsInDrafts;
@property(nonatomic) BOOL atLeastOneSelectedMessageIsInDraftsIsValid; // @synthesize atLeastOneSelectedMessageIsInDraftsIsValid=_atLeastOneSelectedMessageIsInDraftsIsValid;
@property(nonatomic) BOOL atLeastOneSelectedMessageIsInOutbox; // @synthesize atLeastOneSelectedMessageIsInOutbox=_atLeastOneSelectedMessageIsInOutbox;
@property(nonatomic) BOOL atLeastOneSelectedMessageIsInOutboxIsValid; // @synthesize atLeastOneSelectedMessageIsInOutboxIsValid=_atLeastOneSelectedMessageIsInOutboxIsValid;
- (void)awakeFromNib;
- (void)beginPreviewPanelControl:(id)arg1;
@property(readonly, nonatomic) MFBehaviorTracker *behaviorTracker; // @synthesize behaviorTracker=_behaviorTracker;
- (void)changeColor:(id)arg1;
@property(nonatomic) BOOL changingSplitViewOrientation; // @synthesize changingSplitViewOrientation=_changingSplitViewOrientation;
- (void)checkNewMail:(id)arg1;
- (void)clearFlaggedStatus;
- (void)clearFlaggedStatus:(id)arg1;
- (void)clearSearch:(id)arg1;
- (void)clearToolbarItemsTarget;
- (void)clearUndoRedoStacksUnconditionally:(BOOL)arg1;
- (void)closeAllThreads:(id)arg1;
- (void)closeModalWindow:(id)arg1 forcibly:(BOOL)arg2 animate:(BOOL)arg3;
- (void)closeModalWindow:(id)arg1 forcibly:(BOOL)arg2 animate:(BOOL)arg3 animationType:(long long)arg4;
@property(retain, nonatomic) NSMenuItem *columnsMenuItem; // @synthesize columnsMenuItem=_columnsMenuItem;
- (void)configureSegmentedItem:(id)arg1 withDictionary:(id)arg2 forSegment:(long long)arg3;
@property(retain, nonatomic) NSSplitViewController *contentSplitViewController; // @synthesize contentSplitViewController=_contentSplitViewController;
@property(nonatomic) __weak NSView *contentView; // @synthesize contentView=_contentView;
- (struct __MDQuery *)copyHighPriorityQuery;
- (struct __MDQuery *)copyLowPriorityQuery;
- (void)copyMessagesToMailbox:(id)arg1;
@property(readonly, copy, nonatomic) MCMessage *currentDisplayedMessage;
@property(nonatomic) long long currentSearchField; // @synthesize currentSearchField=_currentSearchField;
- (id)customWindowsToExitFullScreenForWindow:(id)arg1;
@property(nonatomic) __weak NSMenuItem *dateReceivedMenuItem; // @synthesize dateReceivedMenuItem=_dateReceivedMenuItem;
@property(nonatomic) __weak NSMenuItem *dateReceivedTableHeaderMenuItem; // @synthesize dateReceivedTableHeaderMenuItem=_dateReceivedTableHeaderMenuItem;
@property(nonatomic) __weak NSMenuItem *dateSentMenuItem; // @synthesize dateSentMenuItem=_dateSentMenuItem;
@property(nonatomic) __weak NSMenuItem *dateSentTableHeaderMenuItem; // @synthesize dateSentTableHeaderMenuItem=_dateSentTableHeaderMenuItem;
- (void)dealloc;
- (void)deleteMessages:(id)arg1;
- (BOOL)deleteMessages:(id)arg1 allowMoveToTrash:(BOOL)arg2 allowUndo:(BOOL)arg3 withAnimationOptions:(NSUInteger)arg4;
- (void)deleteMessages:(id)arg1 allowingMoveToTrash:(BOOL)arg2 withAnimation:(NSUInteger)arg3;
- (id)dictionaryRepresentation;
- (void)didCloseContextMenu:(id)arg1;
@property(nonatomic) BOOL didSetupUI; // @synthesize didSetupUI=_didSetupUI;
- (id)draftsMailbox;
- (void)endPreviewPanelControl:(id)arg1;
- (void)ensureSearchFieldVisibilityInToolbar;
@property(readonly, copy, nonatomic) NSArray *expandedItems;
@property(readonly, copy, nonatomic) NSArray *expandedSelectedMailboxes;
@property(readonly, copy, nonatomic) NSArray *expandedSelectedMailboxesAllowingSearch;
- (void)exportAsPDF:(id)arg1;
@property(readonly, nonatomic) FavoritesBarView *favoritesBarView;
@property(retain, nonatomic) FavoritesBarViewController *favoritesBarViewController; // @synthesize favoritesBarViewController=_favoritesBarViewController;
- (void)filterMessagesToMoveOrDelete:(id)arg1;
- (void)finishedSettingFlaggedStatus;
@property(retain, nonatomic) FlaggedStatusToolbarItem *flaggedStatusToolbarItem; // @synthesize flaggedStatusToolbarItem=_flaggedStatusToolbarItem;
- (void)focusMailboxes;
- (void)focusMessage;
- (void)focusMessages;
- (void)forwardAsAttachment:(id)arg1;
- (void)forwardMessage:(id)arg1;
- (void)forwardWithParentAsAttachment:(id)arg1;
@property(retain, nonatomic) NSToolbarItem *fullScreenFlagMenuToolbarItem; // @synthesize fullScreenFlagMenuToolbarItem=_fullScreenFlagMenuToolbarItem;
@property(nonatomic) __weak MessageViewerFullScreenMinimizeTray *fullScreenMinimizeTray; // @synthesize fullScreenMinimizeTray=_fullScreenMinimizeTray;
@property(readonly, nonatomic) FullScreenWindowController *fullScreenWindowController;
@property(readonly, nonatomic) BOOL hasModalWindow;
- (void)hideDeletions:(id)arg1;
- (void)hideMessagesForMessageTransfer:(id)arg1 selectingNextMessage:(BOOL)arg2;
- (void)hideMessagesForMessageTransfer:(id)arg1 selectingNextMessage:(BOOL)arg2 withAnimationOptions:(NSUInteger)arg3;
@property(nonatomic) BOOL ignoreSearchBarUpdates; // @synthesize ignoreSearchBarUpdates=_ignoreSearchBarUpdates;
- (id)inbox;
- (id)init;
- (void)initFullScreenController;
- (id)initPlainWithAttributes:(id)arg1;
- (id)initWithAttributes:(id)arg1;
- (id)initWithCoder:(id)arg1;
- (id)initWithMailboxes:(id)arg1;
@property(copy, nonatomic) NSDictionary *initialWindowState; // @synthesize initialWindowState=_initialWindowState;
@property(copy, nonatomic) NSSet *initiallySelectedMessages;
@property(readonly, nonatomic) BOOL isFullScreen;
@property(readonly, nonatomic) BOOL isModal;
@property(readonly, nonatomic) BOOL isSelectedMailboxSpecial;
@property(nonatomic) BOOL isShowingMailboxAlert; // @synthesize isShowingMailboxAlert=_isShowingMailboxAlert;
@property(readonly, nonatomic) BOOL isShowingSearchResults;
@property(nonatomic) BOOL isSortedAscending;
- (void)jumpToSelection:(id)arg1;
- (id)junkMailbox;
- (void)keyDown:(id)arg1;
@property(readonly, nonatomic) MailBarContainerView *mailBarContainerView;
- (BOOL)mailboxIsExpanded:(id)arg1;
- (id)mailboxSearchCriterionForScope:(long long)arg1 containsSentMailbox:(char *)arg2 containsTrashMailbox:(char *)arg3 shouldExcludeJunk:(char *)arg4;
- (void)mailboxSelectionChanged:(id)arg1;
@property(readonly, nonatomic) NSWindow *mailboxSelectionWindow;
@property(readonly, nonatomic) BOOL mailboxesPaneIsOpen;
@property(readonly, nonatomic) double mailboxesPaneWidth;
@property(retain, nonatomic) NSSplitViewController *mailboxesSplitViewController; // @synthesize mailboxesSplitViewController=_mailboxesSplitViewController;
@property(copy, nonatomic) NSArray *mailboxesToDisplayWhenVisible; // @synthesize mailboxesToDisplayWhenVisible=_mailboxesToDisplayWhenVisible;
@property(retain, nonatomic) MailboxesViewController *mailboxesViewController; // @synthesize mailboxesViewController=_mailboxesViewController;
- (void)markAsJunkMail:(id)arg1;
- (void)markAsNotJunkMail:(id)arg1;
- (void)markAsRead:(id)arg1;
- (void)markAsReadFromToolbar:(id)arg1;
- (void)markAsUnread:(id)arg1;
- (void)markAsUnreadFromToolbar:(id)arg1;
- (void)markMessageAsViewed:(id)arg1;
- (void)markMessagesAsRead:(id)arg1;
- (void)markMessagesAsUnread:(id)arg1;
- (void)markMessagesAsViewed:(id)arg1;
@property(retain, nonatomic) NSMenu *messageColumnsMenu; // @synthesize messageColumnsMenu=_messageColumnsMenu;
@property(retain, nonatomic) MessageListController *messageListController; // @synthesize messageListController=_messageListController;
- (void)messageListControllerDidOpenMessageMall:(id)arg1;
- (id)messageMall;
@property(readonly, nonatomic) MessageSelection *messageSelection;
- (id)messageSelectionForPrinting;
@property(retain, nonatomic) NSMenu *messageSortByMenu; // @synthesize messageSortByMenu=_messageSortByMenu;
@property(readonly, copy, nonatomic) MCMessage *messageThatUserIsProbablyReading;
- (void)messageTransferDidTransferMessages:(id)arg1;
- (void)messageTransferDidTransferMessages:(id)arg1 withAnimationOptions:(NSUInteger)arg2;
- (void)messageTransferDidUndoTransferOfMessages:(id)arg1;
@property(readonly, nonatomic) BOOL messageViewerIsFinishedLoadingMessages;
- (id)messagesIncludingHiddenCopies:(id)arg1;
- (id)messagesTargetedByAction:(SEL)arg1;
- (void)minimizeModalWindows;
@property(nonatomic) __weak NSLayoutConstraint *minimizeTrayHeight; // @synthesize minimizeTrayHeight=_minimizeTrayHeight;
@property(nonatomic) __weak NSLayoutConstraint *minimizeTrayTabBarWidth; // @synthesize minimizeTrayTabBarWidth=_minimizeTrayTabBarWidth;
@property(readonly, nonatomic) NSArray *modalChildWindows;
- (void)modifyFlaggedStatus:(id)arg1;
- (void)moveMessagesToMailbox:(id)arg1;
- (struct CGImage *)newMessageViewerSnapshotForceNonFullScreen:(BOOL)arg1;
- (void)nowWouldBeAGoodTimeToTerminate:(id)arg1;
- (id)objectSpecifier;
- (void)observeValueForKeyPath:(id)arg1 ofObject:(id)arg2 change:(id)arg3 context:(void *)arg4;
- (void)openAllThreads:(id)arg1;
- (void)openMessages:(id)arg1;
- (id)outbox;
@property(readonly, nonatomic) BOOL outgoingMailboxSelected;
@property(readonly, nonatomic) MailboxesOutlineViewController *outlineViewController;
- (void)outlineViewDoubleClick:(id)arg1;
- (void)performSearch:(id)arg1;
- (void)performTextFinderAction:(id)arg1;
@property(nonatomic) BOOL performedEarlyDealloc; // @synthesize performedEarlyDealloc=_performedEarlyDealloc;
- (void)prepareForTimeMachineRestore;
- (void)presentModalWindow:(id)arg1;
@property(readonly, nonatomic) BOOL previewPaneVisible;
@property(readonly, nonatomic) double previewSplitPercentage;
@property(nonatomic) BOOL previouslyHadSentScope; // @synthesize previouslyHadSentScope=_previouslyHadSentScope;
- (void)quickLookSelectedAttachments:(id)arg1;
- (void)reapplySortingRules:(id)arg1;
- (void)rebuildTableOfContents:(id)arg1;
- (void)redirectMessage:(id)arg1;
- (void)refreshViewingPaneSelection;
- (oneway void)release;
- (void)removeAttachments:(id)arg1;
- (void)renameMailbox:(id)arg1;
- (void)replyAllMessage:(id)arg1;
- (void)replyMessage:(id)arg1;
- (void)replyToOriginalSender:(id)arg1;
- (void)resignAsSelectionOwner;
- (void)resizeModalWindowForFullScreenSplit;
- (void)restoreMinimizedModalWindows;
- (void)revealMailbox:(id)arg1;
- (void)revealMessage:(id)arg1 inMailbox:(id)arg2 forceMailboxSelection:(BOOL)arg3;
- (void)saveAllAttachments:(id)arg1;
- (void)saveAs:(id)arg1;
- (void)saveDefaultViewerState;
- (void)saveDefaultWindowState;
- (void)saveSearch:(id)arg1;
@property(copy, nonatomic) NSDictionary *savedAttributes; // @synthesize savedAttributes=_savedAttributes;
- (void)searchDidFinish;
- (void)searchDidUpdate;
@property(retain, nonatomic) MessageViewerSearchField *searchField; // @synthesize searchField=_searchField;
- (BOOL)searchField:(id)arg1 hasResultsForQuery:(id)arg2;
- (void)searchFieldDidEndSearching:(id)arg1;
- (BOOL)searchFieldUsesRestrictedQueryScope:(id)arg1;
- (void)searchFieldWidenQueryScope:(id)arg1;
- (id)searchFieldWidenScopeMenuItemTitleString:(id)arg1;
- (id)searchFieldWidenScopeMenuSpinnerTitleString:(id)arg1;
- (id)searchFieldWidenScopeMenuTitleString:(id)arg1;
- (void)searchIndex:(id)arg1;
@property(copy, nonatomic) NSString *searchPhrase;
@property(copy, nonatomic) NSString *searchQuery; // @synthesize searchQuery=_searchQuery;
- (void)searchScopeChanged:(id)arg1;
- (void)searchScopeWillChange;
@property(nonatomic) long long searchTarget; // @synthesize searchTarget=_searchTarget;
@property(retain, nonatomic) NSToolbarItem *searchViewItem; // @synthesize searchViewItem=_searchViewItem;
- (void)searchWillStart;
- (BOOL)sectionIsExpanded:(id)arg1;
- (void)selectAllMessages;
- (void)selectMailbox:(id)arg1;
- (void)selectMessages:(id)arg1;
- (void)selectPathsToMailboxes:(id)arg1;
@property(readonly, nonatomic) MFMailbox *selectedMailbox;
- (id)selectedMailbox:(BOOL)arg1;
@property(copy, nonatomic) NSArray *selectedMailboxes;
- (id)selectedMessages;
- (void)selectedMessagesDidChangeInMessageList;
@property(nonatomic) long long selectedTag; // @synthesize selectedTag=_selectedTag;
- (void)send:(id)arg1;
- (void)send:(id)arg1 forDraft:(BOOL)arg2 actualMessage:(id)arg3;
- (id)sentMailbox;
- (void)setFullScreenWindowController:(FullScreenWindowController*)arg1;
- (void)setHighPriorityQuery:(struct __MDQuery *)arg1;
- (void)setLowPriorityQuery:(struct __MDQuery *)arg1;
- (void)setMailboxesPaneIsOpen:(BOOL)arg1;
- (void)setScriptingProperties:(id)arg1;
- (void)setSelectedMailboxes:(id)arg1 scrollToVisible:(BOOL)arg2;
- (void)setSelectedMessages:(id)arg1;
@property(nonatomic) BOOL shouldCascadeWhenShowing; // @synthesize shouldCascadeWhenShowing=_shouldCascadeWhenShowing;
@property(retain, nonatomic) NSMenuItem *sortByMenuItem; // @synthesize sortByMenuItem=_sortByMenuItem;
@property(nonatomic) __weak NSMenu *sortByTableHeaderMenu; // @synthesize sortByTableHeaderMenu=_sortByTableHeaderMenu;
@property(nonatomic) BOOL suppressWindowTitleUpdates; // @synthesize suppressWindowTitleUpdates=_suppressWindowTitleUpdates;
@property(retain, nonatomic) NSMenu *tableHeaderMenu; // @synthesize tableHeaderMenu=_tableHeaderMenu;
@property(nonatomic) BOOL timeMachineRestoreIsInProgress; // @synthesize timeMachineRestoreIsInProgress=_timeMachineRestoreIsInProgress;
@property(nonatomic) __weak NSTextField *timeMachineRestoreMailboxField; // @synthesize timeMachineRestoreMailboxField=_timeMachineRestoreMailboxField;
@property(retain, nonatomic) NSWindow *timeMachineRestoreMailboxWindow; // @synthesize timeMachineRestoreMailboxWindow=_timeMachineRestoreMailboxWindow;
@property(nonatomic) __weak NSTextField *timeMachineRestoreMessagesField; // @synthesize timeMachineRestoreMessagesField=_timeMachineRestoreMessagesField;
@property(retain, nonatomic) NSWindow *timeMachineRestoreMessagesWindow; // @synthesize timeMachineRestoreMessagesWindow=_timeMachineRestoreMessagesWindow;
@property(retain, nonatomic) NSTimer *timeMachineRestoreSheetTimer; // @synthesize timeMachineRestoreSheetTimer=_timeMachineRestoreSheetTimer;
@property(retain, nonatomic) MailToolbar *toolbar; // @synthesize toolbar=_toolbar;
@property(copy, nonatomic) NSDictionary *toolbarItems; // @synthesize toolbarItems=_toolbarItems;
@property(retain, nonatomic) NSNumber *uniqueID; // @synthesize uniqueID=_uniqueID;
@property(retain, nonatomic) ViewingPaneViewController *viewingPaneViewController; // @synthesize viewingPaneViewController=_viewingPaneViewController;
- (void)setVisibleColumns:(id)arg1;
@property(retain, nonatomic) FullScreenModalCapableWindow *window; // @synthesize window=_window;
- (void)setWithoutAnimationBarContainerVisibility:(BOOL)arg1;
- (void)setupSuggestionsSearchField;
- (void)setupSuggestionsSearchFieldForSentMailboxIfNecessary;
- (void)setupToolbar;
@property(readonly, nonatomic) BOOL shouldDeleteMessagesGivenCurrentState;
- (void)show;
- (void)showAccountInfo:(id)arg1;
- (void)showAlertForMailbox:(id)arg1;
- (void)showAndMakeKey:(BOOL)arg1;
- (void)showComposeWindow:(id)arg1;
- (void)showDeletions:(id)arg1;
- (void)showFollowupsToMessage:(id)arg1;
- (void)showPrintPanel:(id)arg1;
- (void)smartMailboxCriteriaChanged:(id)arg1;
- (void)sortByTagOfSender:(id)arg1;
@property(readonly, copy, nonatomic) NSArray *sortedSectionItemsForTimeMachine;
- (void)speechSynthesizer:(id)arg1 didFinishSpeaking:(BOOL)arg2;
- (void)startSearchForSuggestions:(id)arg1;
- (void)startSpeaking:(id)arg1;
- (void)stopSpeaking:(id)arg1;
- (void)storeBeingInvalidated:(id)arg1;
- (void)submenuAction:(id)arg1;
@property(readonly, nonatomic) SGTMailQueryGenius *suggestionsGenius;
- (id)supplementalTargetForAction:(SEL)arg1 sender:(id)arg2;
- (void)swipeWithEvent:(id)arg1;
- (id)tableHeaderViewGetDefaultMenu:(id)arg1;
- (id)tableManager;
- (void)takeOverAsSelectionOwner;
- (void)toggleAscendingSort:(id)arg1;
- (void)toggleAuthorColumn:(id)arg1;
- (void)toggleContentsColumn:(id)arg1;
- (void)toggleDateReceivedColumn:(id)arg1;
- (void)toggleDateSentColumn:(id)arg1;
- (void)toggleFlag:(id)arg1;
- (void)toggleFlaggedStatus:(BOOL)arg1;
- (void)toggleFlaggedStatusInFullScreen:(id)arg1;
- (void)toggleFromColumn:(id)arg1;
- (void)toggleInboxOnly:(id)arg1;
- (void)toggleLocationColumn:(id)arg1;
- (void)toggleMailboxesPane:(id)arg1;
- (void)toggleMessageFlagsColumn:(id)arg1;
- (void)toggleShowBarContainer:(id)arg1;
- (void)toggleSizeColumn:(id)arg1;
- (void)toggleThreadedMode:(id)arg1;
- (void)toggleToColumn:(id)arg1;
- (void)toggleViewRelatedMessages:(id)arg1;
- (id)toolbar:(id)arg1 itemForItemIdentifier:(id)arg2 willBeInsertedIntoToolbar:(BOOL)arg3;
- (id)toolbarAllowedItemIdentifiers:(id)arg1;
@property(readonly, copy, nonatomic) NSDictionary *toolbarConfigurationDict;
- (id)toolbarDefaultItemIdentifiers:(id)arg1;
- (void)toolbarDidRemoveItem:(id)arg1;
- (void)toolbarDidReorderItem:(id)arg1;
- (void)toolbarWillAddItem:(id)arg1;
- (void)transfer:(id)arg1 didCompleteWithError:(id)arg2;
- (BOOL)transferMessages:(id)arg1 toMailbox:(id)arg2 deleteOriginals:(BOOL)arg3 allowUndo:(BOOL)arg4 isDeleteOperation:(BOOL)arg5 isArchiveOperation:(BOOL)arg6;
- (BOOL)transferMessages:(id)arg1 toMailbox:(id)arg2 deleteOriginals:(BOOL)arg3 allowUndo:(BOOL)arg4 isDeleteOperation:(BOOL)arg5 isArchiveOperation:(BOOL)arg6 withAnimationOptions:(NSUInteger)arg7;
- (BOOL)transferSelectedMessagesToMailbox:(id)arg1 deleteOriginals:(BOOL)arg2;
- (id)trashMailbox;
- (void)undeleteMessages:(id)arg1;
- (id)undoManagerForMessageTransfer:(id)arg1;
- (void)unhideMessagesForMessageTransfer:(id)arg1;
- (void)updateToolbar;
- (void)updateWindowTitle:(id)arg1;
@property(readonly, nonatomic) BOOL usesCustomFullScreenAnimation;
- (BOOL)validateFlaggedStatusToolbarItem:(id)arg1;
- (BOOL)validateMenuItem:(id)arg1;
- (BOOL)validateToolbarItem:(id)arg1;
- (BOOL)validateUserInterfaceItem:(id)arg1;
@property(readonly, nonatomic) long long viewerNumber;
- (id)visibleColumns;
- (void)willShowContextMenu:(id)arg1;
- (void)window:(id)arg1 startCustomAnimationToExitFullScreenWithDuration:(double)arg2;
- (void)window:(id)arg1 willEncodeRestorableState:(id)arg2;
- (struct CGRect)window:(id)arg1 willPositionSheet:(id)arg2 usingRect:(struct CGRect)arg3;
- (void)windowDidBecomeMain:(id)arg1;
- (void)windowDidFailToEnterFullScreen:(id)arg1;
- (BOOL)windowShouldClose:(id)arg1;
- (void)windowWillClose:(id)arg1;
- (void)windowWillMiniaturize:(id)arg1;

// Remaining properties
@property(readonly, copy) NSString *debugDescription;
@property(readonly, copy) NSString *description;
@property(readonly, copy, nonatomic) NSString *displayName;
@property(readonly) NSUInteger hash;
@property(readonly, nonatomic) BOOL isSmartMailbox;
@property(readonly) Class superclass;

@end

