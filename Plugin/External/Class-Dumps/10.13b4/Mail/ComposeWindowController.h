//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


#import "ComposeViewControllerDelegate-Protocol.h"
#import "PopoutAnimationContentProvider-Protocol.h"

@class ComposeViewController, ComposeWindow, MailInspectorBar, NSDictionary, NSMenu, NSString;

@interface ComposeWindowController : NSWindowController <NSWindowDelegate, ComposeViewControllerDelegate, NSAnimationDelegate, NSToolbarDelegate, NSWindowRestoration, PopoutAnimationContentProvider>
{
    MailInspectorBar *_inspectorBar;
    BOOL _shouldCloseWindowWhenAnimationCompletes;
    BOOL _inspectorBarDisplayed;
    id _loadCompletionHandler;
    NSDictionary *_toolbarItems;
    NSMenu *_disclosureMenu;
    struct CGPoint _animationStartFrameOrigin;
}

+ (id)keyPathsForValuesAffectingTitle;
+ (void)restoreWindowWithIdentifier:(id)arg1 state:(id)arg2 completionHandler:(id)arg3;
- (id)_menuForListsItem;
- (void)_performSendAnimationWithCompletion:(id)arg1;
- (void)_setupToolbar;
- (void)_synchronizeChangeReplyItem:(id)arg1 messageType:(long long)arg2;
- (struct CGRect)_toolbarRect;
- (void)_updateInspectorBar:(BOOL)arg1;
- (void)addComposeViewController:(id)arg1;
- (id)animationContentProvider:(id)arg1;
@property(nonatomic) struct CGPoint animationStartFrameOrigin; // @synthesize animationStartFrameOrigin=_animationStartFrameOrigin;
- (void)beginRecordingKeystrokes;
- (void)closeAll:(id)arg1;
- (void)composeViewControllerDidFinishLoading:(id)arg1;
- (void)composeViewControllerDidSend:(id)arg1;
- (void)composeViewControllerShouldClose:(id)arg1;
- (void)composeViewControllerShouldShow:(id)arg1;
- (void)configureSegmentedItem:(id)arg1 withDictionary:(id)arg2 forSegment:(long long)arg3;
@property(retain) ComposeViewController *contentViewController;
@property(retain, nonatomic) NSMenu *disclosureMenu; // @synthesize disclosureMenu=_disclosureMenu;
- (void)flushRecordedKeystrokes;
- (id)getContentGeometryData;
- (void)getSnapshotParts:(id)arg1;
- (id)init;
- (id)initWithCoder:(id)arg1;
- (id)initWithWindow:(id)arg1;
@property(readonly, nonatomic) MailInspectorBar *inspectorBar;
@property(nonatomic) BOOL inspectorBarDisplayed; // @synthesize inspectorBarDisplayed=_inspectorBarDisplayed;
@property(copy, nonatomic) id loadCompletionHandler; // @synthesize loadCompletionHandler=_loadCompletionHandler;
- (void)performClose:(id)arg1;
- (void)prepareComposeViewController:(id)arg1 forSendingWithCompletionHandler:(id)arg2;
- (void)restoreFrame;
@property(nonatomic) BOOL shouldCloseWindowWhenAnimationCompletes; // @synthesize shouldCloseWindowWhenAnimationCompletes=_shouldCloseWindowWhenAnimationCompletes;
@property(nonatomic) BOOL shouldDisplayInspectorBar;
@property(retain, nonatomic) NSDictionary *toolbarItems; // @synthesize toolbarItems=_toolbarItems;
@property(retain) ComposeWindow *window;
- (id)supplementalTargetForAction:(SEL)arg1 sender:(id)arg2;
- (void)synchronizeIncludeAttachmentsToolbarItem:(id)arg1;
- (void)synchronizeToolbarReplyWithType:(long long)arg1;
@property(readonly, copy, nonatomic) NSString *title;
- (void)toggleComposeFormatInspectorBar:(id)arg1;
- (id)toolbar:(id)arg1 itemForItemIdentifier:(id)arg2 willBeInsertedIntoToolbar:(BOOL)arg3;
- (id)toolbarAllowedItemIdentifiers:(id)arg1;
- (id)toolbarDefaultItemIdentifiers:(id)arg1;
- (id)toolbarIdentifier;
- (void)toolbarWillAddItem:(id)arg1;
- (void)updateInspectorBar;
- (void)updateSendButtonStateInToolbar;
- (BOOL)validateUserInterfaceItem:(id)arg1;
- (void)window:(id)arg1 willEncodeRestorableState:(id)arg2;
- (void)windowDidLoad;
- (void)windowDidMove:(id)arg1;
- (void)windowDidResignKey:(id)arg1;
- (void)windowDidResize:(id)arg1;
- (id)windowNibName;
- (BOOL)windowShouldClose:(id)arg1;
- (void)windowWillClose:(id)arg1;

// Remaining properties
@property(readonly, copy) NSString *debugDescription;
@property(readonly, copy) NSString *description;
@property(readonly) NSUInteger hash;
@property(readonly) Class superclass;

@end

