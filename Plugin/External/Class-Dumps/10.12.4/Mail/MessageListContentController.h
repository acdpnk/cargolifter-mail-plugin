//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


#import "MCMessageDataSource-Protocol.h"
#import "MessageListContentProviderDelegate-Protocol.h"

@class MFLibraryStore, MessageListContentProvider, NSArray, NSDictionary, NSPredicate, NSString;

@interface MessageListContentController : NSObject <MessageListContentProviderDelegate, MCMessageDataSource>
{
    BOOL _includeDeleted;
    BOOL _isInThreadedMode;
    BOOL _useLibraryIDNumbering;
    NSArray *_selectedMailboxes;
    NSArray *_expandedSelectedMailboxes;
    NSArray *_orderedObjects;
    NSDictionary *_originalMessageByMessageID;
    NSDictionary *_messageCopiesByMessageID;
    MFLibraryStore *_searchStore;
    BOOL _allMessagesLoaded;
    BOOL _inSearchMode;
    BOOL _wasPreviouslyOrderedAscending;
    BOOL _wasPreviouslyInThreadedMode;
    BOOL _wasPreviouslyIncludingDeleted;
    BOOL _isSortedAscending;
    BOOL _displayingToColumn;
    id <MessageListContentControllerDelegate> _delegate;
    MessageListContentProvider *_provider;
    MessageListContentProvider *_bufferedProvider;
    long long _activeSearchField;
    long long _activeSearchTarget;
    NSString *_lastQueryStringFragment;
    NSArray *_previouslySelectedMailboxes;
    NSString *_previousSortOrder;
    NSPredicate *_previousFilterPredicate;
    NSString *_sortOrder;
    NSString *_secondarySortOrder;
    NSPredicate *_primitiveFilterPredicate;
    NSUInteger _totalMessageCount;
}

+ (id)expandedMailboxes:(id)arg1;
+ (void)initialize;
- (void)_searchForCriterion:(id)arg1 isInThreadedMode:(BOOL)arg2 viewingState:(id)arg3 filterPredicate:(id)arg4;
- (id)_storesToRebuild;
@property(readonly, nonatomic) id <MCMailAccount> account;
@property(nonatomic) long long activeSearchField; // @synthesize activeSearchField=_activeSearchField;
@property(nonatomic) long long activeSearchTarget; // @synthesize activeSearchTarget=_activeSearchTarget;
@property(readonly, copy, nonatomic) NSArray *allMailboxes;
@property(nonatomic) BOOL allMessagesLoaded; // @synthesize allMessagesLoaded=_allMessagesLoaded;
- (void)async_setFlagWithKey:(id)arg1 state:(BOOL)arg2 forMessages:(id)arg3;
- (void)async_setFlagsFromDictionary:(id)arg1 forMessages:(id)arg2;
- (id)attachmentsDirectoryForMessage:(id)arg1;
- (id)attachmentsDirectoryForMessage:(id)arg1 partNumber:(id)arg2;
- (id)bodyDataForMessage:(id)arg1 fetchIfNotAvailable:(BOOL)arg2 allowPartial:(BOOL)arg3;
- (id)bodyForMessage:(id)arg1 fetchIfNotAvailable:(BOOL)arg2 updateFlags:(BOOL)arg3 allowPartial:(BOOL)arg4;
@property(retain, nonatomic) MessageListContentProvider *bufferedProvider; // @synthesize bufferedProvider=_bufferedProvider;
@property(readonly, nonatomic) BOOL canCompact;
@property(readonly, nonatomic) BOOL canRebuild;
- (void)clearPreviousQueryString;
- (void)clearSearchWithViewingState:(id)arg1;
- (void)closeAllThreads;
- (void)closeThread:(id)arg1 selectThread:(BOOL)arg2;
- (id)copyWithZone:(struct _NSZone *)arg1;
@property(readonly, nonatomic) NSUInteger countOfOrderedObjects;
- (id)criterionForAttachmentType:(id)arg1;
@property(nonatomic) __weak id <MessageListContentControllerDelegate> delegate; // @synthesize delegate=_delegate;
- (void)deleteMessages:(id)arg1 moveToTrash:(BOOL)arg2;
@property(nonatomic) BOOL displayingToColumn; // @synthesize displayingToColumn=_displayingToColumn;
- (void)doCompact;
@property(readonly, copy, nonatomic) NSArray *expandedSelectedMailboxes;
@property(readonly, copy, nonatomic) NSArray *expandedSelectedMailboxesAllowingSearch;
@property(retain, nonatomic) NSPredicate *filterPredicate;
- (void)flushAllCaches;
- (id)fullBodyDataForMessage:(id)arg1 andHeaderDataIfReadilyAvailable:(id *)arg2 fetchIfNotAvailable:(BOOL)arg3;
- (void)getIndexesOfMessages:(id)arg1 completionBlock:(id)arg2;
- (id)headerDataForMessage:(id)arg1 fetchIfNotAvailable:(BOOL)arg2 allowPartial:(BOOL)arg3;
- (id)headersForMessage:(id)arg1 fetchIfNotAvailable:(BOOL)arg2;
- (void)hideMessages:(id)arg1 selectingNextMessage:(id)arg2 withAnimationOptions:(NSUInteger)arg3 completionHandler:(id)arg4;
@property(nonatomic) BOOL inSearchMode; // @synthesize inSearchMode=_inSearchMode;
@property(nonatomic) BOOL includeDeleted;
- (id)init;
- (void)invalidateMessage:(id)arg1;
@property(nonatomic) BOOL isInThreadedMode;
@property(readonly, nonatomic) BOOL isInThreadedModeExcludingSearch;
@property(readonly) BOOL isReadOnly;
@property(nonatomic) BOOL isSortedAscending; // @synthesize isSortedAscending=_isSortedAscending;
- (BOOL)isSortedByDateReceived;
@property(readonly, nonatomic) BOOL isStillSearching;
@property(copy, nonatomic) NSString *lastQueryStringFragment; // @synthesize lastQueryStringFragment=_lastQueryStringFragment;
@property(readonly, nonatomic) id <MCMailbox> mailbox;
- (void)messageFlagsDidChange:(id)arg1 flags:(id)arg2;
- (long long)messageFlagsForMessage:(id)arg1 size:(NSUInteger *)arg2 appliedFlagColors:(id *)arg3;
- (id)messageForMessageID:(id)arg1;
- (BOOL)messageIsPartOfAThread:(id)arg1;
- (void)messageListContentProvider:(id)arg1 didFinishTaskWithInfo:(id)arg2 taskID:(id)arg3;
- (void)messageListContentProviderConversationsUpdated:(id)arg1;
- (void)messageListContentProviderDidFinishLoading:(id)arg1;
- (id)messagesIncludingHiddenCopies:(id)arg1;
- (BOOL)needTo;
- (id)objectInOrderedObjectsAtIndex:(NSUInteger)arg1;
- (void)openAllThreads;
- (void)openThread:(id)arg1;
@property(readonly, copy, nonatomic) NSArray *openThreads;
@property(readonly, copy, nonatomic) NSArray *orderedObjects;
- (id)orderedObjectsAtIndexes:(id)arg1;
- (id)orderedObjectsInRange:(struct _NSRange)arg1;
- (id)originalOfMessage:(id)arg1;
- (id)parentOfMessage:(id)arg1;
@property(retain, nonatomic) NSPredicate *previousFilterPredicate; // @synthesize previousFilterPredicate=_previousFilterPredicate;
@property(copy, nonatomic) NSString *previousSortOrder; // @synthesize previousSortOrder=_previousSortOrder;
@property(retain, nonatomic) NSArray *previouslySelectedMailboxes; // @synthesize previouslySelectedMailboxes=_previouslySelectedMailboxes;
@property(retain, nonatomic) NSPredicate *primitiveFilterPredicate; // @synthesize primitiveFilterPredicate=_primitiveFilterPredicate;
@property(retain, nonatomic) MessageListContentProvider *provider; // @synthesize provider=_provider;
- (id)queryStringFragmentFromSuggestions:(id)arg1;
- (void)rebuildTableOfContentsAsynchronously;
- (id)repliesToMessage:(id)arg1;
- (id)routeMessages:(id)arg1 fetchingBodies:(BOOL)arg2 messagesNeedingBodies:(id)arg3;
- (void)saveSnippetsForMessages:(id)arg1;
- (void)searchForSuggestions:(id)arg1 in:(long long)arg2 withOptions:(long long)arg3 fromSuggestionsSearchField:(id)arg4 isInThreadedMode:(BOOL)arg5 viewingState:(id)arg6 filterPredicate:(id)arg7;
@property(readonly, copy, nonatomic) NSArray *searchScopeMailboxes;
@property(readonly, nonatomic) MFLibraryStore *searchStore;
@property(copy, nonatomic) NSString *secondarySortOrder; // @synthesize secondarySortOrder=_secondarySortOrder;
@property(readonly, copy, nonatomic) NSArray *selectedMailboxes;
@property(readonly, nonatomic) BOOL selectionIncludesSmartMailbox;
- (void)sendResponseType:(BOOL)arg1 forMeetingMessage:(id)arg2 completionHandler:(id)arg3;
- (void)setColor:(id)arg1 highlightTextOnly:(BOOL)arg2 forMessages:(id)arg3;
- (void)setFlagWithKey:(id)arg1 state:(BOOL)arg2 forMessages:(id)arg3;
- (id)setFlagsFromDictionary:(id)arg1 forMessages:(id)arg2;
- (id)setJunkMailLevel:(long long)arg1 forMessages:(id)arg2 trainJunkMailDatabase:(BOOL)arg3 userRecorded:(BOOL)arg4;
- (void)setMailboxes:(id)arg1 sortOrder:(id)arg2 isSortedAscending:(BOOL)arg3 isInThreadedMode:(BOOL)arg4 includeDeleted:(BOOL)arg5 initialViewingState:(id)arg6 filterPredicate:(id)arg7;
- (void)setNumberOfAttachments:(unsigned int)arg1 isSigned:(BOOL)arg2 isEncrypted:(BOOL)arg3 forMessage:(id)arg4;
@property(copy, nonatomic) NSString *sortOrder; // @synthesize sortOrder=_sortOrder;
- (void)setSortOrder:(id)arg1 ascending:(BOOL)arg2 viewingState:(id)arg3;
@property(nonatomic) NSUInteger totalMessageCount; // @synthesize totalMessageCount=_totalMessageCount;
@property(nonatomic) BOOL wasPreviouslyInThreadedMode; // @synthesize wasPreviouslyInThreadedMode=_wasPreviouslyInThreadedMode;
@property(nonatomic) BOOL wasPreviouslyIncludingDeleted; // @synthesize wasPreviouslyIncludingDeleted=_wasPreviouslyIncludingDeleted;
@property(nonatomic) BOOL wasPreviouslyOrderedAscending; // @synthesize wasPreviouslyOrderedAscending=_wasPreviouslyOrderedAscending;
- (BOOL)shouldShowRecipientForMailboxes:(id)arg1;
- (NSUInteger)sizeForMessage:(id)arg1;
- (id)snippetsForMessages:(id)arg1;
@property(readonly, copy, nonatomic) NSArray *stores;
- (BOOL)supportsSearching;
@property(readonly, nonatomic) BOOL supportsSnippets;
- (id)threadForMessage:(id)arg1;
- (void)toggleThreadedMode;
- (BOOL)undeleteMessages:(id)arg1;
- (id)undeleteMessages:(id)arg1 movedToStore:(id)arg2 newMessageIDs:(id)arg3;
- (void)unhideMessages:(id)arg1;
- (id)uniquedString:(id)arg1;
@property(readonly, nonatomic) NSUInteger unreadCount;
- (void)unregisterForNotifications;

// Remaining properties
@property(readonly, copy) NSString *debugDescription;
@property(readonly, copy) NSString *description;
@property(readonly, copy, nonatomic) NSString *displayName;
@property(readonly) NSUInteger hash;
@property(readonly, nonatomic) BOOL isSmartMailbox;
@property(readonly) Class superclass;

@end
