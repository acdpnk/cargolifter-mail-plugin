//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header

@class MUIWKWebViewController, MUIWebDocument;

@interface MUIWebDocumentView : NSView
{
    NSUInteger _loadedState;
    struct CGSize _contentSize;
    double _preferredMinLayoutWidth;
    BOOL _preparingToLayoutSynchronously;
    BOOL _supportsAttachments;
    NSView *_snapshotView;
    MUIWKWebViewController *_wkWebViewController;
    id _prepareToLayoutSynchronouslyCompletionHandler;
    id _delegate;
}

+ (id)keyPathsForValuesAffectingEditable;
+ (id)keyPathsForValuesAffectingPageZoom;
+ (id)keyPathsForValuesAffectingWebDocument;
+ (BOOL)requiresConstraintBasedLayout;
- (id)_attachmentControllersForAttachments:(id)arg1;
- (void)_muiWebDocumentViewCommonInit;
- (void)_readyToLayoutSynchronously;
- (void)_updatePreferredMinLayoutWidth;
- (void)appendAttachment:(id)arg1 completionHandler:(id)arg2;
- (void)appendAttributedString:(id)arg1 completionHandler:(id)arg2;
- (void)appendString:(id)arg1 completionHandler:(id)arg2;
- (BOOL)canExportAttachmentsToApplication:(id)arg1;
- (BOOL)commitEditing;
- (BOOL)commitEditingAndReturnError:(id *)arg1;
- (void)commitEditingWithDelegate:(id)arg1 didCommitSelector:(SEL)arg2 contextInfo:(void *)arg3;
@property(nonatomic) struct CGSize contentSize;
@property(readonly, nonatomic) __weak NSView *contentView;
@property(nonatomic) __weak id delegate; // @synthesize delegate=_delegate;
- (id)description;
- (void)discardEditing;
@property(nonatomic) BOOL drawsBackground;
@property(nonatomic) BOOL editable;
- (void)evaluateJavaScript:(id)arg1 completionHandler:(id)arg2;
- (id)evaluateJavaScriptSynchronously:(id)arg1;
- (void)exportAttachmentsToApplication:(id)arg1;
- (void)findMatchesForString:(id)arg1 relativeToMatch:(id)arg2 findOptions:(NSUInteger)arg3 maxResults:(NSUInteger)arg4 resultCollector:(id)arg5;
- (void)generateSelectionWebDocument:(id)arg1;
- (void)generateStyleInlinedWebDocument:(id)arg1;
- (void)getSelectedText:(id)arg1;
- (id)initWithCoder:(id)arg1;
- (id)initWithFrame:(struct CGRect)arg1;
- (struct CGSize)intrinsicContentSize;
- (BOOL)isFlipped;
- (void)layoutSublayersOfLayer:(id)arg1;
@property(nonatomic) NSUInteger loadedState;
- (void)mui_cancelAnimation;
- (void)mui_cancelSynchronousLayout;
- (void)mui_didCacheDisplayInRect;
- (void)mui_performAnimation;
- (void)mui_performLayoutSynchronously;
- (void)mui_prepareToAnimate:(id)arg1;
- (void)mui_prepareToCacheDisplayInRect:(struct CGRect)arg1 completionHandler:(id)arg2;
- (void)mui_prepareToLayoutSynchronously:(id)arg1;
@property(nonatomic) double pageZoom;
@property(nonatomic) double preferredMinLayoutWidth;
- (void)prepareTilesInRect:(struct CGRect)arg1;
@property(copy, nonatomic) id prepareToLayoutSynchronouslyCompletionHandler; // @synthesize prepareToLayoutSynchronouslyCompletionHandler=_prepareToLayoutSynchronouslyCompletionHandler;
@property(nonatomic) BOOL preparingToLayoutSynchronously; // @synthesize preparingToLayoutSynchronously=_preparingToLayoutSynchronously;
- (id)printOperationWithPrintInfo:(id)arg1;
- (void)quickLookAttachments:(id)arg1;
- (void)reloadDocument;
- (void)removeAttachment:(id)arg1 completionHandler:(id)arg2;
- (void)resizeWithOldSuperviewSize:(struct CGSize)arg1;
- (void)saveAttachments:(id)arg1 toDirectory:(id)arg2 makePathsUnique:(BOOL)arg3;
- (void)saveAttachmentsWithPanel:(id)arg1;
- (void)selectFindMatch:(id)arg1 completionHandler:(id)arg2;
- (void)setAttachments:(id)arg1 asHidden:(BOOL)arg2 completionHandler:(id)arg3;
@property(nonatomic) BOOL shouldPaintToBounds;
@property(nonatomic) BOOL supportsAttachments; // @synthesize supportsAttachments=_supportsAttachments;
@property(retain, nonatomic) MUIWebDocument *webDocument;
@property(retain, nonatomic) MUIWKWebViewController *wkWebViewController; // @synthesize wkWebViewController=_wkWebViewController;
- (BOOL)shouldHandleClickForURL:(id)arg1;
@property(readonly, nonatomic) NSView *snapshotView; // @synthesize snapshotView=_snapshotView;
- (id)supplementalTargetForAction:(SEL)arg1 sender:(id)arg2;
- (void)tearDown;
- (void)toggleAutomaticListInsertion:(id)arg1;
- (id)view:(id)arg1 stringForToolTip:(long long)arg2 point:(struct CGPoint)arg3 userData:(void *)arg4;
- (void)viewDidMoveToSuperview;

@end

