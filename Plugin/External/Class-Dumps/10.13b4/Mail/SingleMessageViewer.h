//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header

#import "MessageViewer.h"

#import "SelectionOwner-Protocol.h"

@class LoadingOverlay, MCMessage, NSArray, NSOperation, NSSet, NSString;

@interface SingleMessageViewer : MessageViewer <NSDraggingSource, NSToolbarDelegate, NSWindowRestoration, SelectionOwner>
{
    BOOL _nibLoaded;
    BOOL _nextDeleteShouldMoveToTrash;
    NSArray *_selectedMailboxes;
    NSOperation *_proxyIconOperation;
    NSOperation *_subjectLoadOperation;
    MCMessage *_initialMessage;
    NSSet *_hiddenCopies;
    NSArray *_messagesToDelete;
    LoadingOverlay *_loadingOverlay;
}

+ (id)_createWithMessage:(id)arg1 hiddenCopies:(id)arg2 showRelatedMessages:(BOOL)arg3 expandedSelectedMailboxes:(id)arg4 andAttributes:(id)arg5;
+ (id)_createWithSavedAttributes:(id)arg1;
+ (void)_mailApplicationDidFinishLaunching:(id)arg1;
+ (id)_messagesFromDictionary:(id)arg1;
+ (id)existingSingleMessageViewerForMessage:(id)arg1;
+ (id)newDefaultMessageViewer;
+ (void)restoreAllViewersFromDefaults;
+ (void)restoreWindowWithIdentifier:(id)arg1 state:(id)arg2 completionHandler:(id)arg3;
+ (id)toolbarIdentifier;
+ (id)viewerForMessage:(id)arg1 hiddenCopies:(id)arg2 showRelatedMessages:(BOOL)arg3 expandedSelectedMailboxes:(id)arg4;
+ (id)viewerForPendingMessage;
- (void)_addMessageIDsFrom:(id)arg1 toDictionary:(id)arg2;
- (void)_adjustNewSingleViewerWindowFrame;
- (BOOL)_displayingSingletonMessage;
- (BOOL)_isViewingMessage:(id)arg1;
- (void)_messageFlagsDidChange:(id)arg1;
- (id)_messageIDDictionaryRepresentationOf:(id)arg1;
- (void)_messagesCompacted:(id)arg1;
- (void)_messagesWereRemoved:(id)arg1;
- (void)_noMessagesLeftToDisplay;
- (void)_openEnclosingMailbox:(id)arg1;
- (void)_reallyDeleteMessages:(id)arg1 allowingMoveToTrash:(BOOL)arg2;
- (void)_reallyUpdateWindowTitle:(id)arg1;
- (BOOL)_replaceWithEditorForType:(long long)arg1 action:(SEL)arg2;
- (BOOL)_replaceWithEditorForType:(long long)arg1 messages:(id)arg2;
- (void)_restoreViewer;
- (void)_setUpForMessage:(id)arg1 showRelatedMessages:(BOOL)arg2;
- (void)_setWindowFrameFromDefaults;
- (void)_setupFromAttributes;
- (void)_updateWindowProxy:(id)arg1;
- (void)archiveMessages:(id)arg1;
@property(readonly, nonatomic) MCMessage *currentDisplayedMessage;
- (void)dealloc;
- (void)deleteMessages:(id)arg1;
- (void)deleteMessages:(id)arg1 allowMoveToTrash:(BOOL)arg2 allowUndo:(BOOL)arg3 selectingNextMessage:(BOOL)arg4 withAnimationOptions:(NSUInteger)arg5;
- (id)dictionaryRepresentation;
- (NSUInteger)draggingSession:(id)arg1 sourceOperationMaskForDraggingContext:(long long)arg2;
- (id)expandedSelectedMailboxes;
- (id)expandedSelectedMailboxesAllowingSearch;
- (id)filenameToDrag:(id)arg1;
- (void)forwardMessage:(id)arg1;
- (void)forwardMessage:(id)arg1 messageViewController:(id)arg2;
- (void)fullScreenCloseAnimationFinished;
@property(readonly, nonatomic) NSSet *hiddenCopies; // @synthesize hiddenCopies=_hiddenCopies;
- (id)initForViewingMessage:(id)arg1 hiddenCopies:(id)arg2 showRelatedMessages:(BOOL)arg3 expandedSelectedMailboxes:(id)arg4 withAttributes:(id)arg5;
- (void)initFullScreenController;
- (id)initPlainWithAttributes:(id)arg1;
- (id)initWithMailboxes:(id)arg1;
@property(retain, nonatomic) MCMessage *initialMessage; // @synthesize initialMessage=_initialMessage;
- (void)keyDown:(id)arg1;
- (void)loadMessageWindowNib;
@property(retain, nonatomic) LoadingOverlay *loadingOverlay; // @synthesize loadingOverlay=_loadingOverlay;
@property(readonly, nonatomic) id <MCMessageDataSource> messageStore;
@property(readonly, nonatomic) MCMessage *messageThatUserIsProbablyReading;
- (id)messagesIncludingHiddenCopies:(id)arg1;
@property(retain, nonatomic) NSArray *messagesToDelete; // @synthesize messagesToDelete=_messagesToDelete;
@property(nonatomic) BOOL nextDeleteShouldMoveToTrash; // @synthesize nextDeleteShouldMoveToTrash=_nextDeleteShouldMoveToTrash;
@property(nonatomic) BOOL nibLoaded; // @synthesize nibLoaded=_nibLoaded;
@property(retain, nonatomic) NSOperation *proxyIconOperation; // @synthesize proxyIconOperation=_proxyIconOperation;
- (void)redirectMessage:(id)arg1;
- (void)replyAllMessage:(id)arg1;
- (void)replyAllToMessage:(id)arg1 messageViewController:(id)arg2;
- (void)replyMessage:(id)arg1;
- (void)replyToMessage:(id)arg1 messageViewController:(id)arg2;
- (void)replyToOriginalSender:(id)arg1;
- (void)resignAsSelectionOwner;
- (void)restoreFrame;
- (void)revealMessage:(id)arg1;
- (void)saveDefaultWindowState;
- (void)selectMailbox:(id)arg1;
- (void)selectMessages:(id)arg1;
- (id)selectedMailboxes;
- (id)selectedMessages;
@property(readonly, copy, nonatomic) NSArray *selection;
- (id)selectionExpandingThreadsAndHiddenCopies:(BOOL)arg1;
- (void)send:(id)arg1;
- (void)setMessageToView:(id)arg1;
- (void)setSelectedMailboxes:(id)arg1;
- (void)setShouldDisplayShowInMailboxLink:(BOOL)arg1;
@property(retain, nonatomic) NSOperation *subjectLoadOperation; // @synthesize subjectLoadOperation=_subjectLoadOperation;
- (void)setupToolbar;
- (BOOL)shouldDeleteMessageGivenCurrentState;
- (BOOL)shouldDeleteMessagesGivenCurrentState;
- (void)showAndMakeKey:(BOOL)arg1;
- (void)takeOverAsSelectionOwner;
- (void)undeleteMessages:(id)arg1;
- (void)undeleteMessagesAllowUndo:(BOOL)arg1;
- (void)updateToolbar;
- (void)updateWindowTitle:(id)arg1;
- (BOOL)validateUserInterfaceItem:(id)arg1;
- (BOOL)window:(id)arg1 shouldDragDocumentWithEvent:(id)arg2 from:(struct CGPoint)arg3 withPasteboard:(id)arg4;
- (BOOL)window:(id)arg1 shouldPopUpDocumentPathMenu:(id)arg2;
- (void)windowDidMove:(id)arg1;
- (void)windowDidResize:(id)arg1;
- (void)windowWillClose:(id)arg1;

// Remaining properties
@property(readonly, copy) NSString *debugDescription;
@property(readonly, copy) NSString *description;
@property(readonly) NSUInteger hash;
@property(readonly, nonatomic) BOOL isInThreadedMode;
@property(readonly) Class superclass;

@end

