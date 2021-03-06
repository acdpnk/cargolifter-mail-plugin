//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


#import "ComposeViewControllerDelegate-Protocol.h"
#import "MailFullScreenWindowDelegate-Protocol.h"
#import "PopoutAnimationContentProvider-Protocol.h"
#import "TabBarViewDelegate-Protocol.h"

@class ComposeViewController, FullScreenModalCapableWindow, MailInspectorBar, NSArray, NSDictionary, NSMenu, NSString, NSTitlebarAccessoryViewController, TabBarView, TabBarViewController;

@interface ComposeWindowController : NSWindowController <TabBarViewDelegate, ComposeViewControllerDelegate, NSAnimationDelegate, NSToolbarDelegate, NSWindowRestoration, MailFullScreenWindowDelegate, PopoutAnimationContentProvider>
{
    MailInspectorBar *_inspectorBar;
    BOOL _sendAnimationCancelled;
    BOOL _sendAnimationIsInProgress;
    BOOL _shouldCloseWindowWhenAnimationCompletes;
    BOOL _inspectorBarDisplayed;
    TabBarView *_tabBarView;
    TabBarViewController *_tabBarViewController;
    NSTitlebarAccessoryViewController *_toolbarNewTabButtonViewController;
    NSDictionary *_toolbarItems;
    NSMenu *_disclosureMenu;
    id _loadCompletionHandler;
    struct CGPoint _animationStartFrameOrigin;
}

+ (id)keyPathsForValuesAffectingTitle;
+ (void)restoreWindowWithIdentifier:(id)arg1 state:(id)arg2 completionHandler:(id)arg3;
- (void)_addOrRemoveNewTabButtonInToolbarIfNecessary;
- (void)_closeTabViewItems:(id)arg1;
- (id)_createComposeWindowForTabBarViewItem:(id)arg1;
- (id)_dictionaryRepresentation;
- (id)_menuForListsItem;
- (void)_performSendAnimationWithCompletion:(id)arg1;
- (id)_removeTabBarViewItem:(id)arg1;
- (void)_resetCloseMenus;
- (id)_selectedTabBarViewItemAfterClosingItem:(id)arg1 inTabBarView:(id)arg2;
- (void)_sendAnimationCompleted;
- (void)_setupToolbar;
- (void)_synchronizeChangeReplyItem:(id)arg1 messageType:(long long)arg2;
- (void)_tabBarView:(id)arg1 didSendTabBarViewItem:(id)arg2;
- (void)_tabBarView:(id)arg1 forceCloseTabBarViewItem:(id)arg2;
- (void)_tabBarView:(id)arg1 performSendAnimationOfTabBarViewItem:(id)arg2 completion:(id)arg3;
- (struct CGRect)_toolbarRect;
- (void)_updateCloseMenus;
- (void)_updateInspectorBar:(BOOL)arg1;
- (void)_windowDidExitFullScreen:(id)arg1;
- (id)_windowImageInRect:(struct CGRect)arg1;
- (void)_windowWillEnterFullScreen:(id)arg1;
- (void)addComposeViewController:(id)arg1;
- (id)animationContentProvider:(id)arg1;
- (void)animationDidEnd:(id)arg1;
@property(nonatomic) struct CGPoint animationStartFrameOrigin; // @synthesize animationStartFrameOrigin=_animationStartFrameOrigin;
- (void)beginRecordingKeystrokes;
- (void)cancelSendAnimation;
- (void)closeAll:(id)arg1;
- (void)closeOtherTabsFromMenu:(id)arg1;
- (void)closeTab:(id)arg1;
- (void)closeTabFromMenu:(id)arg1;
- (void)composeViewControllerDidFinishLoading:(id)arg1;
- (void)composeViewControllerDidSend:(id)arg1;
- (void)composeViewControllerShouldClose:(id)arg1;
- (void)composeViewControllerShouldShow:(id)arg1;
- (void)configureSegmentedItem:(id)arg1 withDictionary:(id)arg2 forSegment:(long long)arg3;
@property(retain) ComposeViewController *contentViewController;
- (void)createNewTabInTabBarView:(id)arg1;
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
- (void)mergeAllWindows:(id)arg1;
- (void)moveComposeViewControllersTo:(id)arg1;
- (void)moveTabToNewWindowFromMenu:(id)arg1;
- (void)newTabWithinWindow:(id)arg1;
- (void)performClose:(id)arg1;
- (void)prepareComposeViewController:(id)arg1 forSendingWithCompletionHandler:(id)arg2;
- (void)restoreFrame;
- (void)selectNextTab:(id)arg1;
- (void)selectPreviousTab:(id)arg1;
- (id)selectedTabBarViewItemAfterClosingCurrentTabInTabBarView:(id)arg1;
@property(nonatomic) BOOL sendAnimationCancelled; // @synthesize sendAnimationCancelled=_sendAnimationCancelled;
@property(nonatomic) BOOL sendAnimationIsInProgress; // @synthesize sendAnimationIsInProgress=_sendAnimationIsInProgress;
@property(nonatomic) BOOL shouldCloseWindowWhenAnimationCompletes; // @synthesize shouldCloseWindowWhenAnimationCompletes=_shouldCloseWindowWhenAnimationCompletes;
@property(nonatomic) BOOL shouldDisplayInspectorBar;
@property(retain, nonatomic) TabBarView *tabBarView; // @synthesize tabBarView=_tabBarView;
@property(retain, nonatomic) TabBarViewController *tabBarViewController; // @synthesize tabBarViewController=_tabBarViewController;
@property(retain, nonatomic) NSDictionary *toolbarItems; // @synthesize toolbarItems=_toolbarItems;
@property(retain, nonatomic) NSTitlebarAccessoryViewController *toolbarNewTabButtonViewController; // @synthesize toolbarNewTabButtonViewController=_toolbarNewTabButtonViewController;
@property(retain) FullScreenModalCapableWindow *window;
- (id)supplementalTargetForAction:(SEL)arg1 sender:(id)arg2;
- (void)synchronizeIncludeAttachmentsToolbarItem:(id)arg1;
- (void)synchronizeToolbarReplyWithType:(long long)arg1;
- (BOOL)tabBarView:(id)arg1 acceptDrop:(id)arg2 index:(NSUInteger)arg3;
- (BOOL)tabBarView:(id)arg1 acceptTabDrop:(id)arg2 index:(NSUInteger)arg3;
- (void)tabBarView:(id)arg1 closeOtherTabsExceptTabBarViewItem:(id)arg2;
- (void)tabBarView:(id)arg1 closeTabBarViewItem:(id)arg2;
- (id)tabBarView:(id)arg1 destinationWindowForDetachedTabBarViewItem:(id)arg2;
- (id)tabBarView:(id)arg1 detachedWindowImageForDraggedTabBarViewItem:(id)arg2;
- (void)tabBarView:(id)arg1 didFinishTransitionAnimationForWindow:(id)arg2;
- (void)tabBarView:(id)arg1 didMoveTabBarViewItem:(id)arg2 toIndex:(NSUInteger)arg3;
- (id)tabBarView:(id)arg1 menuForTabBarViewItem:(id)arg2 event:(id)arg3;
- (void)tabBarView:(id)arg1 selectTabBarViewItem:(id)arg2;
- (NSUInteger)tabBarView:(id)arg1 validateDrop:(id)arg2;
- (NSUInteger)tabBarView:(id)arg1 validateTabDrop:(id)arg2;
- (void)tabBarViewDidZoomIn:(id)arg1;
@property(readonly, copy, nonatomic) NSArray *tabNames;
@property(readonly, copy, nonatomic) NSString *title;
- (void)toggleComposeFormatInspectorBar:(id)arg1;
- (id)toolbar:(id)arg1 itemForItemIdentifier:(id)arg2 willBeInsertedIntoToolbar:(BOOL)arg3;
- (id)toolbarAllowedItemIdentifiers:(id)arg1;
- (id)toolbarDefaultItemIdentifiers:(id)arg1;
- (id)toolbarIdentifier;
- (void)toolbarWillAddItem:(id)arg1;
- (void)updateInspectorBar;
- (void)updateSendButtonStateInToolbar;
- (BOOL)validateMenuItem:(id)arg1;
- (BOOL)validateUserInterfaceItem:(id)arg1;
- (void)window:(id)arg1 willEncodeRestorableState:(id)arg2;
- (void)windowDidBecomeKey:(id)arg1;
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

