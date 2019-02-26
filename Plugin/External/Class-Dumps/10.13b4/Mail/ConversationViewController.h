//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


#import "MUICollectionViewDelegate-Protocol.h"

@class ConversationMember, ConversationMemberArrayController, ConversationViewFindController, MUICollectionView, MessageSelection, MessageViewController, NSArray, NSHashTable, NSMutableDictionary, NSMutableIndexSet, NSMutableOrderedSet, NSMutableSet, NSScrollView, NSString, NSUUID;

@interface ConversationViewController : NSViewController <MUICollectionViewDelegate, NSUserInterfaceValidations>
{
    NSMutableOrderedSet *_conversationMembers;
    NSMutableSet *_viewControllers;
    NSMutableIndexSet *_loadIndexes;
    NSMutableIndexSet *_primaryIndexes;
    NSMutableIndexSet *_unreadIndexes;
    NSMutableIndexSet *_visibleIndexes;
    NSMutableDictionary *_defaultMessageViewingState;
    NSMutableDictionary *_messageViewingStateByLibraryID;
    ConversationMember *_conversationMemberObservedForActivity;
    NSHashTable *_observedConversations;
    BOOL _scrollViewIsInLiveScroll;
    BOOL _loaded;
    BOOL _needsBackdrop;
    BOOL _hiddenBehindSnapshot;
    MUICollectionView *_conversationView;
    ConversationMemberArrayController *_arrayController;
    ConversationViewFindController *_findController;
    double _pageZoom;
    NSUUID *_updateUUID;
    NSScrollView *_scrollView;
    NSString *_urlStringToContinue;
    NSString *_persistentIdToContinue;
}

+ (BOOL)automaticallyNotifiesObserversOfRepresentedObject;
- (id)_actionConversationMemberIndices;
- (void)_cellViewFrameDidChange:(id)arg1;
- (void)_conversationViewControllerCommonInit;
- (BOOL)_isSingleton;
- (void)_loadCellAtNextIndex;
- (void)_markViewControllerLoaded;
- (void)_performDiagnostics:(id)arg1;
- (void)_performInitialPinning;
- (void)_prepareToUpdateLastViewedDateAndMarkReadIfNeeded:(id)arg1 index:(NSUInteger)arg2;
- (void)_resetConversationDisplayState;
- (void)_resetConversationState;
- (void)_restoreMessageViewingState:(id)arg1;
- (void)_saveMessageViewingState:(id)arg1;
- (void)_scrollViewDidEndLiveScroll:(id)arg1;
- (void)_scrollViewWillStartLiveScroll:(id)arg1;
- (void)_updateActivityFromConversationMember:(id)arg1;
- (void)_updateContent;
- (void)_updateConversationMembers:(id)arg1;
- (void)_updateFirstResponderIfNeeded;
- (void)_updateLastViewedDateAndMarkRead:(id)arg1;
- (void)_updateNeedsBackdrop;
- (void)_viewControllerDidFinishLoading:(id)arg1;
@property(readonly, copy, nonatomic) NSArray *actionConversationMembers;
- (id)actionMessagesIncludingDuplicates:(BOOL)arg1;
@property(readonly, nonatomic) MessageViewController *actionViewController;
@property(readonly, nonatomic) ConversationMemberArrayController *arrayController; // @synthesize arrayController=_arrayController;
- (void)collectionView:(id)arg1 didBeginDisplayingCellView:(id)arg2 forItemAtIndex:(NSUInteger)arg3;
- (void)collectionView:(id)arg1 didEndDisplayingCellView:(id)arg2 forItemAtIndex:(NSUInteger)arg3;
- (void)collectionView:(id)arg1 didEndScrollInScrollView:(id)arg2;
- (void)collectionView:(id)arg1 didScrollInScrollView:(id)arg2;
- (void)collectionView:(id)arg1 didSelectIndex:(NSUInteger)arg2;
- (double)collectionView:(id)arg1 initialHeightOfCellAtIndex:(NSUInteger)arg2;
- (id)collectionView:(id)arg1 makeCellViewForItemAtIndex:(NSUInteger)arg2;
- (void)collectionView:(id)arg1 willEvictCellView:(id)arg2;
@property(readonly, nonatomic) BOOL conversationMemberHasRelatedMessages;
@property(retain, nonatomic) ConversationMember *conversationMemberObservedForActivity;
@property(readonly, nonatomic) MUICollectionView *conversationView; // @synthesize conversationView=_conversationView;
- (void)dealloc;
@property(readonly, copy) NSString *description;
@property(readonly, nonatomic) ConversationViewFindController *findController; // @synthesize findController=_findController;
@property(nonatomic) BOOL hiddenBehindSnapshot; // @synthesize hiddenBehindSnapshot=_hiddenBehindSnapshot;
- (id)initWithCoder:(id)arg1;
- (id)initWithNibName:(id)arg1 bundle:(id)arg2;
@property(nonatomic) BOOL loaded; // @synthesize loaded=_loaded;
- (void)makeFontBigger:(id)arg1;
- (void)makeFontSmaller:(id)arg1;
@property(nonatomic) BOOL needsBackdrop; // @synthesize needsBackdrop=_needsBackdrop;
- (void)observeValueForKeyPath:(id)arg1 ofObject:(id)arg2 change:(id)arg3 context:(void *)arg4;
@property(nonatomic) double pageZoom; // @synthesize pageZoom=_pageZoom;
- (void)performTextFinderAction:(id)arg1;
@property(copy, nonatomic) NSString *persistentIdToContinue; // @synthesize persistentIdToContinue=_persistentIdToContinue;
@property(retain) MessageSelection *representedObject;
@property(nonatomic) __weak NSScrollView *scrollView; // @synthesize scrollView=_scrollView;
@property(copy, nonatomic) NSUUID *updateUUID; // @synthesize updateUUID=_updateUUID;
@property(copy, nonatomic) NSString *urlStringToContinue; // @synthesize urlStringToContinue=_urlStringToContinue;
- (void)tearDown;
@property(readonly, nonatomic) __weak id <NSTextFinderBarContainer> textFinderBarContainer;
- (void)toggleViewRelatedMessages:(id)arg1;
- (void)updateUserActivityState:(id)arg1;
- (BOOL)validateMenuItem:(id)arg1;
- (BOOL)validateToolbarItem:(id)arg1;
- (BOOL)validateUserInterfaceItem:(id)arg1;
- (void)viewDidLoad;

// Remaining properties
@property(readonly, copy) NSString *debugDescription;
@property(readonly) NSUInteger hash;
@property(readonly) Class superclass;

@end
