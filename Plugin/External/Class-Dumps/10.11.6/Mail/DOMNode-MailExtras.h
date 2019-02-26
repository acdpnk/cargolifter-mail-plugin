//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header

//#import "DOMNode.h"

@class DOMElement, DOMHTMLElement, NSArray, NSDictionary, NSString;

@interface DOMNode (MailExtras)
- (id)XPathRelativeTo:(id)arg1;
- (BOOL)_hasNoSignificantContentsOrWhitespace:(BOOL)arg1 orAttachments:(BOOL)arg2;
- (BOOL)_isAppleStringAttachmentSpan;
@property(readonly, nonatomic) BOOL _mail_isAttached;
- (id)_mail_traverseNextNodeStayingWithin:(id)arg1;
- (id)_mail_traverseNextSiblingStayingWithin:(id)arg1;
- (id)_mail_traversePreviousNode;
- (void)_removeStrayLinefeedsAtBeginning;
- (void)_removeStrayLinefeedsAtEnd;
- (void)addInlineBackgroundImageURLToArray:(id)arg1;
- (id)appendBlockPlaceholder;
- (id)attributedStringWithDocument:(id)arg1;
@property(readonly, nonatomic) DOMNode *blockNodeAncestor;
- (id)commonAncestorWithNode:(id)arg1;
@property(readonly, nonatomic) DOMNode *containingBlockQuote;
@property(readonly, nonatomic) DOMHTMLElement *containingListElement;
@property(readonly, nonatomic) DOMNode *containingListItem;
@property(readonly, nonatomic) BOOL containsOnlySelectionMarkers;
- (BOOL)containsRichTextForMessageFont:(id)arg1;
- (void)convertBackgroundImageURLsUsingDictionary:(id)arg1;
- (BOOL)convertInlineStationeryBackgroundImageURL;
- (BOOL)convertInternalImagesToObjectsIsStationery:(BOOL)arg1;
- (id)descendantNamed:(id)arg1;
- (void)descendants:(id *)arg1 withClassName:(id)arg2;
- (id)descendantsWithClassName:(id)arg1;
@property(readonly, copy, nonatomic) NSDictionary *editableElements;
- (void)editableElements:(id *)arg1;
@property(readonly, nonatomic) DOMElement *elementAncestor;
- (id)findElementWithTag:(id)arg1 andClass:(id)arg2;
- (id)findElementWithTag:(id)arg1 className:(id)arg2 andIdName:(id)arg3;
- (id)firstContainingNodeWithNameInArray:(id)arg1;
@property(readonly, nonatomic) DOMNode *firstDescendantBlockQuote;
- (void)fixParagraphsAndQuotesFromMicrosoft;
- (void)fixParagraphsAndQuotesFromMicrosoftNodesToRemove:(id)arg1;
@property(readonly, nonatomic) BOOL hasNoContents;
@property(readonly, nonatomic) BOOL hasNoSignificantContents;
@property(readonly, nonatomic) BOOL hasNoSignificantContentsOrWhitespace;
@property(readonly, nonatomic) BOOL hasNoSignificantContentsOtherThanAttachments;
@property(readonly, nonatomic) DOMNode *highestContainingBlockQuote;
- (void)insertAsSiblingAfterNode:(id)arg1;
- (void)insertAsSiblingBeforeNode:(id)arg1;
- (BOOL)isAtBeginningOfContainerNode:(id)arg1;
- (BOOL)isAtEndOfContainerNode:(id)arg1;
@property(readonly, nonatomic) BOOL isBlockLevelElement;
@property(readonly, nonatomic) BOOL isBody;
- (BOOL)isDescendantOfNode:(id)arg1;
@property(readonly, nonatomic) BOOL isInEditableRegion;
@property(readonly, nonatomic) BOOL isListElement;
@property(readonly, nonatomic) BOOL isNodeThatAffectsTyping;
@property(readonly, nonatomic) BOOL isTemporaryCursorMarker;
@property(readonly, nonatomic) DOMNode *lastEditableElement;
@property(readonly, nonatomic) DOMElement *nestedListElement;
@property(readonly, nonatomic) DOMNode *nextNode;
@property(readonly, nonatomic) DOMNode *nextSiblingOrAunt;
@property(readonly, copy, nonatomic) NSArray *objectElementChildNodes;
- (void)objectElementChildNodes:(id *)arg1;
- (unsigned int)offsetOfChild:(id)arg1;
@property(readonly, nonatomic) long long outlineNestingLevel;
@property(readonly, nonatomic) DOMNode *precedingListItem;
@property(readonly, nonatomic) DOMNode *previousNode;
@property(readonly, nonatomic) long long quoteLevel;
@property(readonly, nonatomic) long long quoteLevelDelta;
- (void)recursivelyFixParagraphs;
- (void)recursivelyRemoveMailAttributes;
- (void)recursivelyRemoveMailAttributes:(BOOL)arg1 convertObjectsToImages:(BOOL)arg2 convertEditableElements:(BOOL)arg3 removeDefaultColorStyle:(BOOL)arg4;
- (void)removeStrayLinefeeds;
- (void)restoreEditableElementsEdited:(id *)arg1 unedited:(id *)arg2;
@property(readonly, copy, nonatomic) NSArray *stationeryAttachmentPlaceholderNodes;
- (void)stationeryAttachmentPlaceholderNodes:(id *)arg1;
@property(readonly, copy, nonatomic) NSArray *stationeryDynamicElementNodes;
- (void)stationeryDynamicElementNodes:(id *)arg1;
@property(readonly, copy, nonatomic) NSString *stringValue;
@property(readonly, nonatomic) DOMHTMLElement *tilingDiv;
@property(readonly, copy, nonatomic) NSArray *tilingElements;
- (id)topmostContainingNodeWithNameInArray:(id)arg1;
@property(readonly, nonatomic) DOMNode *topmostEditableAncestor;
@end
