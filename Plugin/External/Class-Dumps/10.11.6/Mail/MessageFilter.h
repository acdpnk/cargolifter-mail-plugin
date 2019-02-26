//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


#import "ThreadedMessageListDelegate-Protocol.h"

@class MCInvocationQueue, MCMessage, MFMessageThread, NSMutableArray, NSMutableDictionary, NSMutableSet, NSNumber, NSString;

@interface MessageFilter : NSObject <ThreadedMessageListDelegate>
{
    int _taskCounter;
    NSMutableArray *_allStores;
    NSMutableSet *_storesWaitingToLoad;
    NSMutableSet *_primaryMessages;
    NSMutableSet *_secondaryMessages;
    NSMutableSet *_nonDeletedMessages;
    NSMutableSet *_hiddenMessages;
    NSMutableSet *_shownMessages;
    NSMutableSet *_storesBeingOpened;
    NSMutableDictionary *_conversationIDByMessage;
    NSMutableDictionary *_threadsByConversationID;
    NSMutableDictionary *_originalMessageByMessageID;
    NSMutableDictionary *_messageCopiesByMessageID;
    NSMutableSet *_pendingSelectedMessageIdentifiers;
    NSMutableSet *_pendingSelectedThreadIdentifiers;
    NSMutableSet *_pendingOpenThreadIdentifiers;
    NSMutableDictionary *_foundSelectedMessagesByIdentifier;
    NSMutableDictionary *_foundSelectedThreadsByIdentifier;
    MFMessageThread *_foundPinnedThread;
    MCMessage *_foundPinnedMessage;
    NSMutableSet *_changedMessages;
    NSMutableSet *_changedThreads;
    BOOL _includeDeleted;
    BOOL _isInThreadedMode;
    BOOL _primarySortOrderIsSortedAscending;
    BOOL _secondarySortOrderIsSortedAscending;
    BOOL _awaitingInitialMessages;
    id <MessageFilterDelegate> _delegate;
    id <MessageList> _messageList;
    MCInvocationQueue *_filterTasks;
    NSString *_primarySortOrder;
    NSString *_secondarySortOrder;
    NSUInteger _totalMessageCount;
    NSNumber *_pendingScrollStyle;
    id _pendingPinnedMessageIdentifier;
    NSNumber *_pendingPinnedThreadIdentifier;
    double _pendingPinningOffset;
}

- (id)_addMessages:(id)arg1 secondaryMessages:(id)arg2;
- (id)_addStore:(id)arg1;
- (void)_addTaskToFilterQueue:(id)arg1;
- (void)_checkForPendingMessages:(id)arg1;
- (void)_clearAllMessageInfo;
- (void)_clearTaskSpecificInfo;
- (id)_closeAllThreads;
- (id)_closeThreads:(id)arg1 selectingThread:(id)arg2;
- (void)_componentStoreDidOpen:(id)arg1;
- (void)_componentStoreFinishedLoading:(id)arg1;
- (void)_componentStoreMessagesWereAdded:(id)arg1;
- (void)_componentStoreStructureChanged:(id)arg1;
- (void)_dumpDiagnosticInfo;
- (id)_filterInMessages:(id)arg1 secondaryMessages:(id)arg2;
- (id)_filterOutMessages:(id)arg1;
- (void)_filterTaskCompleted:(id)arg1 taskID:(int)arg2;
- (id)_filterTaskInfoByMergingTaskInfos:(id)arg1;
- (void)_findPendingObjectsInList;
- (id)_fullTaskInfoFromChangeDictionary:(id)arg1;
- (id)_getIndexesOfMessages:(id)arg1 completionBlock:(id)arg2;
- (id)_groupMessages;
- (id)_handleComponentStoreDidOpen:(id)arg1;
- (id)_handleComponentStoreStructureChanged:(id)arg1;
- (id)_handleLibraryConversationsWereChanged:(id)arg1;
- (id)_handleLibraryMessagesFlagsChanged:(id)arg1;
- (id)_handleLibraryMessagesGmailLabelsChanged:(id)arg1;
- (id)_handleLibraryMessagesUpdated:(id)arg1;
- (id)_handleMessagesAdded:(id)arg1;
- (id)_hideDeletedMessages;
- (id)_hideMessages:(id)arg1 selectingNextMessage:(id)arg2 withAnimationOptions:(id)arg3;
- (id)_invertFilteredListWithViewingState:(id)arg1;
- (BOOL)_isKnownMessage:(id)arg1;
- (id)_knownAndUnknownMessages:(id)arg1 fromMessages:(id)arg2;
- (void)_libraryConversationsWereChanged:(id)arg1;
- (void)_libraryMessagesCompacted:(id)arg1;
- (void)_libraryMessagesFlagsChanged:(id)arg1;
- (void)_libraryMessagesGmailLabelsChanged:(id)arg1;
- (void)_libraryMessagesUpdated:(id)arg1;
- (unsigned int)_loadOptions;
- (id)_messagesIncludingHiddenCopies:(id)arg1;
- (id)_newMessageList;
- (id)_openAllThreads;
- (id)_openThreads:(id)arg1;
- (id)_originalForMessage:(id)arg1;
- (void)_performFilterTask:(id)arg1 taskID:(int)arg2;
- (id)_refilter;
- (id)_removeMessages:(id)arg1;
- (id)_removeMessages:(id)arg1 reason:(id)arg2;
- (void)_removeMessagesInStores:(id)arg1 fromCopiesInfoWithStoreCache:(id)arg2;
- (void)_removeMessagesInStores:(id)arg1 fromMessages:(id)arg2 storeCache:(id)arg3;
- (id)_resortWithPrimarySortOrder:(id)arg1 isOrderedAscending:(BOOL)arg2 viewingState:(id)arg3;
- (id)_setStores:(id)arg1 sortOrder:(id)arg2 isSortedAscending:(BOOL)arg3 isInThreadedMode:(BOOL)arg4 includeDeleted:(BOOL)arg5 viewingState:(id)arg6;
- (BOOL)_shouldAlwaysShowDuplicates;
- (BOOL)_shouldDisplayMessage:(id)arg1;
- (BOOL)_shouldShowCopy:(id)arg1;
- (id)_showDeletedMessages;
- (id)_storeFinishedLoading:(id)arg1;
- (id)_storeForMailbox:(id)arg1 cache:(id)arg2;
- (id)_ungroupMessages;
- (id)_unhideMessages:(id)arg1;
- (void)_unrollViewingState:(id)arg1;
- (id)_updateCopiesInfoForMessages:(id)arg1;
- (id)arrayOfSortOrders;
@property(nonatomic) BOOL awaitingInitialMessages; // @synthesize awaitingInitialMessages=_awaitingInitialMessages;
- (void)closeAllThreads;
- (void)closeThreads:(id)arg1 selectingThread:(id)arg2;
- (id)conversationIDForMessage:(id)arg1;
@property __weak id <MessageFilterDelegate> delegate; // @synthesize delegate=_delegate;
@property(readonly, nonatomic) MCInvocationQueue *filterTasks; // @synthesize filterTasks=_filterTasks;
- (void)getIndexesOfMessages:(id)arg1 completionBlock:(id)arg2;
- (void)groupMessages;
- (void)hideDeletedMessages;
- (void)hideMessages:(id)arg1 selectingNextMessage:(id)arg2 withAnimationOptions:(NSUInteger)arg3;
- (id)init;
- (void)invertFilteredListWithViewingState:(id)arg1;
@property(nonatomic) BOOL isInThreadedMode; // @synthesize isInThreadedMode=_isInThreadedMode;
- (unsigned int)messageFlagsForMessage:(id)arg1 size:(NSUInteger *)arg2 appliedFlagColors:(id *)arg3;
@property(retain, nonatomic) id <MessageList> messageList; // @synthesize messageList=_messageList;
- (void)openAllThreads;
- (void)openThreads:(id)arg1;
@property(copy, nonatomic) id pendingPinnedMessageIdentifier; // @synthesize pendingPinnedMessageIdentifier=_pendingPinnedMessageIdentifier;
@property(retain, nonatomic) NSNumber *pendingPinnedThreadIdentifier; // @synthesize pendingPinnedThreadIdentifier=_pendingPinnedThreadIdentifier;
@property(nonatomic) double pendingPinningOffset; // @synthesize pendingPinningOffset=_pendingPinningOffset;
@property(retain, nonatomic) NSNumber *pendingScrollStyle; // @synthesize pendingScrollStyle=_pendingScrollStyle;
@property(copy, nonatomic) NSString *primarySortOrder; // @synthesize primarySortOrder=_primarySortOrder;
@property(nonatomic) BOOL primarySortOrderIsSortedAscending; // @synthesize primarySortOrderIsSortedAscending=_primarySortOrderIsSortedAscending;
- (void)resortWithSortOrder:(id)arg1 isOrderedAscending:(BOOL)arg2 viewingState:(id)arg3;
@property(copy, nonatomic) NSString *secondarySortOrder; // @synthesize secondarySortOrder=_secondarySortOrder;
@property(nonatomic) BOOL secondarySortOrderIsSortedAscending; // @synthesize secondarySortOrderIsSortedAscending=_secondarySortOrderIsSortedAscending;
- (void)setStores:(id)arg1 sortOrder:(id)arg2 isSortedAscending:(BOOL)arg3 isInThreadedMode:(BOOL)arg4 includeDeleted:(BOOL)arg5 viewingState:(id)arg6;
@property(nonatomic) NSUInteger totalMessageCount; // @synthesize totalMessageCount=_totalMessageCount;
- (BOOL)shouldSortAscendingForSortOrder:(id)arg1;
- (void)showDeletedMessages;
- (NSUInteger)sizeForMessage:(id)arg1;
- (unsigned int)sortingMessageFlagsForMessage:(id)arg1 appliedFlagColors:(id *)arg2;
- (NSUInteger)sortingSizeForMessage:(id)arg1;
- (long long)sortingUniqueIdentifierForMessageThread:(id)arg1;
- (id)threadForConversationID:(id)arg1;
- (id)threadForMessage:(id)arg1;
- (void)threadedMessageList:(id)arg1 messageWillChange:(id)arg2;
- (void)threadedMessageList:(id)arg1 willAddMessage:(id)arg2 withConversationID:(id)arg3;
- (void)threadedMessageList:(id)arg1 willAddThread:(id)arg2 withConversationID:(id)arg3;
- (void)threadedMessageList:(id)arg1 willRemoveMessage:(id)arg2;
- (void)threadedMessageList:(id)arg1 willRemoveThread:(id)arg2 withConversationID:(id)arg3;
- (void)ungroupMessages;
- (void)unhideMessages:(id)arg1;
- (void)unregisterForNotifications;

@end
