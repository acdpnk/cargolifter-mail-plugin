/*
 *     Generated by class-dump 3.3.3 (64 bit).
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2010 by Steve Nygard.
 */

@class NSBox, NSButtonCell, NSMatrix, NSMutableArray, NSMutableDictionary, NSWindow;

@interface NSPreferences : NSObject
{
    NSWindow *_preferencesPanel;
    NSBox *_preferenceBox;
    NSMatrix *_moduleMatrix;
    NSButtonCell *_okButton;
    NSButtonCell *_cancelButton;
    NSButtonCell *_applyButton;
    NSMutableArray *_preferenceTitles;
    NSMutableArray *_preferenceModules;
    NSMutableDictionary *_masterPreferenceViews;
    NSMutableDictionary *_currentSessionPreferenceViews;
    NSBox *_originalContentView;
    BOOL _isModal;
    double _constrainedWidth;
    id _currentModule;
    void *_reserved;
}

+ (id)sharedPreferences;
+ (void)setDefaultPreferencesClass:(Class)arg1;
+ (Class)defaultPreferencesClass;
+ (void)restoreWindowWithIdentifier:(id)arg1 state:(id)arg2 completionHandler:(id)arg3;
- (id)init;
- (void)dealloc;
- (void)addPreferenceNamed:(id)arg1 owner:(id)arg2;
- (void)_setupToolbar;
- (void)_setupUI;
- (struct CGSize)preferencesContentSize;
- (void)showPreferencesPanel;
- (id)_setupPreferencesPanelForOwner:(id)arg1;
- (id)_setupPreferencesPanelForOwnerAtIndex:(long long)arg1;
- (void)showPreferencesPanelForOwner:(id)arg1;
- (void)window:(id)arg1 willEncodeRestorableState:(id)arg2;
- (long long)showModalPreferencesPanelForOwner:(id)arg1;
- (long long)showModalPreferencesPanel;
- (void)ok:(id)arg1;
- (void)cancel:(id)arg1;
- (void)apply:(id)arg1;
- (void)_selectModuleOwner:(id)arg1;
- (id)windowTitle;
- (void)confirmCloseSheetIsDone:(id)arg1 returnCode:(long long)arg2 contextInfo:(void *)arg3;
- (BOOL)windowShouldClose:(id)arg1;
- (void)windowDidResize:(id)arg1;
- (struct CGSize)windowWillResize:(id)arg1 toSize:(struct CGSize)arg2;
- (BOOL)usesButtons;
- (id)_itemIdentifierForModule:(id)arg1;
- (void)toolbarItemClicked:(id)arg1;
- (id)toolbar:(id)arg1 itemForItemIdentifier:(id)arg2 willBeInsertedIntoToolbar:(BOOL)arg3;
- (id)toolbarDefaultItemIdentifiers:(id)arg1;
- (id)toolbarAllowedItemIdentifiers:(id)arg1;
- (id)toolbarSelectableItemIdentifiers:(id)arg1;

@end
