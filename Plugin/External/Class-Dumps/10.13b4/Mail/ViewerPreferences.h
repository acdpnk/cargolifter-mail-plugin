//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header



@class NSButton, NSColorWell, NSMutableArray, NSPanel, NSPopUpButton, NSSegmentedControl, NSString, NSTableView;

@interface ViewerPreferences : NSViewController <NSTableViewDataSource>
{
    NSMutableArray *_filteredHeaders;
    BOOL _isEditingHeader;
    NSButton *_highlightThreadCheckbox;
    NSColorWell *_threadHighlightColorWell;
    NSButton *_loadURLsSwitch;
    NSButton *_showUnreadMessagesInBoldSwitch;
    NSButton *_useSmartAddressesSwitch;
    NSTableView *_customHeaderTable;
    NSSegmentedControl *_addRemoveHeaderControl;
    NSPanel *_customHeaderPanel;
    NSPopUpButton *_headerDetailPopup;
    NSPopUpButton *_snippetLinesPopup;
    NSButton *_toCcButton;
    NSButton *_contactPhotosButton;
    NSButton *_viewRelatedMessagesButton;
}

+ (void)_postToCcPreferenceChanged;
+ (void)postContactPhotoPreferenceChanged;
+ (void)postSnippetLinesPreferenceChanged;
+ (void)postViewingPreferencesChanged;
- (void)_editCustomHeadersClicked;
- (void)_endEditingHeader;
- (void)_headerTableBeganEditing:(id)arg1;
- (void)_headerTableEndedEditing:(id)arg1;
- (void)_removeInvalidHeaders;
- (void)_updateCustomHeaderUI;
- (void)addRemoveHeaderClicked:(id)arg1;
@property(nonatomic) __weak NSSegmentedControl *addRemoveHeaderControl; // @synthesize addRemoveHeaderControl=_addRemoveHeaderControl;
- (void)awakeFromNib;
- (void)cancelClicked:(id)arg1;
@property(nonatomic) __weak NSButton *contactPhotosButton; // @synthesize contactPhotosButton=_contactPhotosButton;
- (void)contactPhotosClicked:(id)arg1;
@property(retain, nonatomic) NSPanel *customHeaderPanel; // @synthesize customHeaderPanel=_customHeaderPanel;
@property(nonatomic) __weak NSTableView *customHeaderTable; // @synthesize customHeaderTable=_customHeaderTable;
- (void)dealloc;
- (void)headerDetailLevelChanged:(id)arg1;
@property(nonatomic) __weak NSPopUpButton *headerDetailPopup; // @synthesize headerDetailPopup=_headerDetailPopup;
@property(nonatomic) __weak NSButton *highlightThreadCheckbox; // @synthesize highlightThreadCheckbox=_highlightThreadCheckbox;
- (void)highlightThreadClicked:(id)arg1;
- (void)initializeFromDefaults;
@property(nonatomic) BOOL isEditingHeader; // @synthesize isEditingHeader=_isEditingHeader;
- (void)loadURLsClicked:(id)arg1;
@property(nonatomic) __weak NSButton *loadURLsSwitch; // @synthesize loadURLsSwitch=_loadURLsSwitch;
- (long long)numberOfRowsInTableView:(id)arg1;
- (void)okClicked:(id)arg1;
@property(nonatomic) __weak NSButton *showUnreadMessagesInBoldSwitch; // @synthesize showUnreadMessagesInBoldSwitch=_showUnreadMessagesInBoldSwitch;
@property(nonatomic) __weak NSPopUpButton *snippetLinesPopup; // @synthesize snippetLinesPopup=_snippetLinesPopup;
@property(nonatomic) __weak NSColorWell *threadHighlightColorWell; // @synthesize threadHighlightColorWell=_threadHighlightColorWell;
@property(nonatomic) __weak NSButton *toCcButton; // @synthesize toCcButton=_toCcButton;
@property(nonatomic) __weak NSButton *useSmartAddressesSwitch; // @synthesize useSmartAddressesSwitch=_useSmartAddressesSwitch;
@property(nonatomic) __weak NSButton *viewRelatedMessagesButton; // @synthesize viewRelatedMessagesButton=_viewRelatedMessagesButton;
- (void)showUnreadMessagesInBoldChanged:(id)arg1;
- (void)snippetLinesChanged:(id)arg1;
- (id)tableView:(id)arg1 objectValueForTableColumn:(id)arg2 row:(long long)arg3;
- (void)tableView:(id)arg1 setObjectValue:(id)arg2 forTableColumn:(id)arg3 row:(long long)arg4;
- (void)threadHighlightColorChanged:(id)arg1;
- (void)toCcClicked:(id)arg1;
- (void)useSmartAddressesClicked:(id)arg1;
- (void)viewRelatedMessagesClicked:(id)arg1;

// Remaining properties
@property(readonly, copy) NSString *debugDescription;
@property(readonly, copy) NSString *description;
@property(readonly) NSUInteger hash;
@property(readonly) Class superclass;

@end

