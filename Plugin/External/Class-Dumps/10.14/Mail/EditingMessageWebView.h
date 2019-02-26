//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header

#import "TilingWebView.h"

#import "NSInspectorBarClient-Protocol.h"
#import "EditingMessageWebViewDelegate-Protocol.h"

@class DOMHTMLAnchorElement, DOMHTMLElement, DOMNode, NSArray, NSOperationQueue, NSSet, NSString, NSURL, NSWindow;

@interface EditingMessageWebView : TilingWebView <NSFilePresenter, NSInspectorBarClient, NSTextInputClient>
{
    DOMHTMLElement *_contentElement;
    NSUInteger _fileCount;
    BOOL _delegateRespondsToCanInsertFromPasteboard;
    DOMNode *_cursorPositionNode;
    NSOperationQueue *_filePromiseOperationQueue;
}

+ (void)addEditingHistoryScriptsToGroupIfNecessary;
+ (id)insertablePasteboardTypes;
- (void)_changeIndentationIfAllowed:(long long)arg1;
- (void)_clearExistingHTML;
- (id)_createAttachmentsForResources:(id)arg1 inFragment:(id)arg2;
- (void)_editingMessageWebViewCommonInit;
- (void)_insertNode:(id)arg1 parent:(id)arg2 offset:(unsigned int)arg3;
- (BOOL)_isContentEditable;
- (BOOL)_removeAllFormatting:(long long)arg1;
- (BOOL)_removeAllQuotingFromTree:(id)arg1;
- (void)_removeBlockQuoteFromTree:(id)arg1;
- (void)_removeFragmentBlockQuote:(id)arg1;
- (BOOL)_replaceSelectionWithContentsOfWebpage:(id)arg1;
- (BOOL)_replaceSelectionWithFragment:(id)arg1 attachments:(id)arg2 pasteboard:(id)arg3 types:(id)arg4 action:(long long)arg5 options:(NSUInteger)arg6 isPlainText:(BOOL)arg7;
- (BOOL)_replaceSelectionWithPasteboardContentsDraggingInfo:(id)arg1 pasteboard:(id)arg2 pasteboardType:(id)arg3 action:(long long)arg4 options:(NSUInteger)arg5;
- (void)_restoreSelectionFromTemporaryMarkers:(BOOL)arg1;
- (void)_splitUpBlockQuotesOverlappingEndOfRange:(id)arg1;
- (void)_splitUpBlockQuotesOverlappingStartOfRange:(id)arg1;
- (void)addHorizontalRule:(id)arg1;
- (id)attributedSubstringForProposedRange:(struct _NSRange)arg1 actualRange:(struct _NSRange *)arg2;
- (BOOL)becomeFirstResponder;
- (id)beginDraggingSessionWithItems:(id)arg1 event:(id)arg2 source:(id)arg3;
- (void)changeDocumentBackgroundColorToColor:(id)arg1;
- (void)changeIndentation:(long long)arg1;
- (void)changeQuoteLevel:(id)arg1;
- (NSUInteger)characterIndexForPoint:(struct CGPoint)arg1;
- (void)concludeDragOperation:(id)arg1;
@property(copy, nonatomic) DOMHTMLElement *contentElement;
- (void)convertListFromType:(id)arg1 toType:(id)arg2 undoTitle:(id)arg3;
- (void)convertToBulletedList:(id)arg1;
- (void)convertToNumberedList:(id)arg1;
@property(retain, nonatomic) DOMNode *cursorPositionNode; // @synthesize cursorPositionNode=_cursorPositionNode;
- (void)decreaseIndentation:(id)arg1;
- (void)decreaseListNestingLevel:(id)arg1;
@property(nonatomic) BOOL delegateRespondsToCanInsertFromPasteboard; // @synthesize delegateRespondsToCanInsertFromPasteboard=_delegateRespondsToCanInsertFromPasteboard;
- (void)deleteNode:(id)arg1;
- (void)deleteRange:(id)arg1;
- (void)deleteTemporarySelectionMarkersFromDocument:(id)arg1;
- (void)doCommandBySelector:(SEL)arg1;
- (NSUInteger)draggingEntered:(id)arg1;
- (void)draggingExited:(id)arg1;
- (NSUInteger)draggingUpdated:(id)arg1;
- (void)editLink:(id)arg1;
@property(retain, nonatomic) id <EditingMessageWebViewDelegate> editingDelegate;
@property(readonly, nonatomic) NSOperationQueue *filePromiseOperationQueue; // @synthesize filePromiseOperationQueue=_filePromiseOperationQueue;
- (struct CGRect)firstRectForCharacterRange:(struct _NSRange)arg1 actualRange:(struct _NSRange *)arg2;
- (BOOL)hasMarkedText;
- (void)increaseIndentation:(id)arg1;
- (void)increaseListNestingLevel:(id)arg1;
- (id)initWithCoder:(id)arg1;
- (id)initWithFrame:(struct CGRect)arg1 frameName:(id)arg2 groupName:(id)arg3;
- (BOOL)insertImageURL:(id)arg1 forAction:(long long)arg2;
- (void)insertListWithNumbers:(BOOL)arg1 undoTitle:(id)arg2;
- (void)insertNode:(id)arg1 atRange:(id)arg2;
- (void)insertNode:(id)arg1 parent:(id)arg2 nextSibling:(id)arg3;
- (void)insertTemporarySelectionMarkersForRange:(id)arg1;
- (void)insertText:(id)arg1 replacementRange:(struct _NSRange)arg2;
@property(readonly) NSArray *inspectorBarItemIdentifiers;
- (BOOL)isActive;
- (BOOL)isAutomaticLinkDetectionEnabled;
@property(readonly, nonatomic) BOOL isSelectionInContentElement;
- (void)layoutResizingAttachmentViews;
- (void)loadHTMLString:(id)arg1 baseURL:(id)arg2 resourcesToAttach:(id)arg3;
- (id)mailPreferredPboardTypeFromTypes:(id)arg1 pasteboard:(id)arg2 isForDrag:(BOOL)arg3 preferHTML:(BOOL)arg4;
- (BOOL)maintainsInactiveSelection;
- (void)makeFontBigger:(id)arg1;
- (void)makeFontSmaller:(id)arg1;
- (struct _NSRange)markedRange;
- (void)paste:(id)arg1;
- (void)pasteAsQuotation:(id)arg1;
- (void)pasteWithCurrentStyle:(id)arg1;
- (NSUInteger)pastedContactCounter;
- (NSUInteger)pastedGraphicCounter;
- (BOOL)performDragOperation:(id)arg1;
- (BOOL)prepareForDragOperation:(id)arg1;
@property(readonly, retain) NSOperationQueue *presentedItemOperationQueue;
@property(readonly, copy) NSURL *presentedItemURL;
- (void)redo:(id)arg1;
- (void)registerForDraggedTypes:(id)arg1;
- (void)removeAllFormatting;
- (BOOL)removeFormattingFromTree:(id)arg1 forDocument:(id)arg2 hasDocumentContext:(BOOL)arg3 imageStrippingMode:(long long)arg4;
- (BOOL)removeHeadFromDocument:(id)arg1;
- (void)removeLink:(id)arg1;
- (BOOL)removeNonBodyChildrenAndAttributesFromMainDocumentElement;
- (void)removeStyle:(id)arg1;
- (void)replaceNode:(id)arg1 oldNode:(id)arg2;
- (BOOL)replaceSelectionUsingContext:(id)arg1;
- (BOOL)replaceSelectionWithPasteboardContentsDraggingInfo:(id)arg1 pasteboardType:(id)arg2 action:(long long)arg3 options:(NSUInteger)arg4;
- (BOOL)replaceSelectionWithPasteboardContentsPasteboard:(id)arg1 pasteboardType:(id)arg2 action:(long long)arg3 options:(NSUInteger)arg4;
- (BOOL)resetMainDocumentBodyAttributes;
- (void)restoreSelectionFromTemporaryMarkers;
- (void)saveMessageToDrafts:(id)arg1;
- (void)saveSelectionForUndo;
@property(readonly, copy, nonatomic) DOMHTMLAnchorElement *selectedAnchor;
- (id)selectedContainerWithNameInArray:(id)arg1;
- (struct _NSRange)selectedRange;
- (BOOL)selectionCouldBeMadeIntoALink;
@property(readonly, nonatomic) BOOL selectionIsInEmptyListItem;
@property(readonly, nonatomic) BOOL selectionIsInList;
- (BOOL)selectionIsInListType:(id)arg1;
- (BOOL)selectionIsInListTypes:(id)arg1;
- (void)setMainDocumentURI:(id)arg1;
- (void)setMarkedText:(id)arg1 selectedRange:(struct _NSRange)arg2 replacementRange:(struct _NSRange)arg3;
- (void)setSelectionStart:(id)arg1 offset:(int)arg2 end:(id)arg3 offset:(int)arg4 affinity:(NSUInteger)arg5;
- (void)setStyleProperty:(id)arg1 value:(id)arg2 priority:(id)arg3 ofElement:(id)arg4;
- (void)setValue:(id)arg1 forAttribute:(id)arg2 ofElement:(id)arg3;
@property(readonly, copy, nonatomic) DOMNode *temporaryEndingSelectionMarker;
@property(readonly, copy, nonatomic) DOMNode *temporaryStartingSelectionMarker;
- (id)textInput;
- (void)undo:(id)arg1;
- (void)unmarkText;
- (void)updateLayer;
- (id)validAttributesForMarkedText;
- (BOOL)validateMenuItem:(id)arg1 fallThrough:(char *)arg2;
- (BOOL)validateUserInterfaceItem:(id)arg1;
- (BOOL)validateUserInterfaceItem:(id)arg1 fallThrough:(char *)arg2;
- (void)viewDidChangeEffectiveAppearance;
- (BOOL)wantsPeriodicDraggingUpdates;

// Remaining properties
@property(readonly, copy) NSString *debugDescription;
@property(readonly, copy) NSString *description;
@property(readonly) NSUInteger hash;
@property(readonly) NSSet *observedPresentedItemUbiquityAttributes;
@property(readonly, copy) NSURL *primaryPresentedItemURL;
@property(readonly) Class superclass;
@property(readonly) NSWindow *window;

@end

