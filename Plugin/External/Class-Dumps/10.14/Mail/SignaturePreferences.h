//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


#import "EditingMessageWebViewDelegate-Protocol.h"
#import "TerminationHandler-Protocol.h"

@class ColorBackgroundView, DeletingTableView, EditingMessageWebView, EditingWebMessageController, HyperlinkEditor, MFMailAccount, NSArray, NSButton, NSPopUpButton, NSSegmentedControl, NSString, NSTableView, NSTextField, WebArchive;

@interface SignaturePreferences : NSViewController <EditingMessageWebViewDelegate, NSUserInterfaceValidations, TerminationHandler>
{
    BOOL _addingNewSignature;
    BOOL _appIsTerminating;
    BOOL _loadedInitialHTML;
    BOOL _currentSignatureHasChanges;
    DeletingTableView *_signaturesTable;
    NSTableView *_accountsTable;
    NSPopUpButton *_selectPopup;
    ColorBackgroundView *_webViewBackground;
    EditingMessageWebView *_webView;
    NSButton *_textRichnessButton;
    NSTextField *_textRichnessMessageField;
    NSSegmentedControl *_createOrRemoveButton;
    NSButton *_placeSignatureAboveQuote;
    EditingWebMessageController *_controller;
    MFMailAccount *_selectedAccount;
    MFMailAccount *_allSignaturesAccount;
    NSString *_defaultFontName;
    WebArchive *_savedWebArchive;
    HyperlinkEditor *_hyperlinkEditor;
}

- (void)_accountsDidChange:(id)arg1;
- (void)_createSignature:(id)arg1;
- (void)_defaultFontMayHaveChanged:(id)arg1;
- (id)_defaultSignatureContentForSelectedAccount;
- (void)_determineDefaultFontName;
- (void)_displaySelectedSignatureDetails;
- (BOOL)_endEditingOfSignatureOkayToReload:(BOOL)arg1 needsToReload:(char *)arg2;
- (void)_registerForNotifications;
- (void)_removeSignature:(id)arg1;
- (void)_unregisterForNotifications;
- (void)_updatePopup;
- (void)_updateWebView;
- (void)_validateButtonState;
- (BOOL)_validateValuesInUI;
- (id)_webArchiveForEditedSignature;
@property(nonatomic) __weak NSTableView *accountsTable; // @synthesize accountsTable=_accountsTable;
@property(nonatomic) BOOL addingNewSignature; // @synthesize addingNewSignature=_addingNewSignature;
@property(nonatomic) __weak MFMailAccount *allSignaturesAccount; // @synthesize allSignaturesAccount=_allSignaturesAccount;
@property(readonly, nonatomic) BOOL allowQuoting;
@property(nonatomic) BOOL allowsRichText;
@property(nonatomic) BOOL appIsTerminating; // @synthesize appIsTerminating=_appIsTerminating;
- (void)awakeFromNib;
- (void)changeSignatureRichness:(id)arg1;
- (BOOL)control:(id)arg1 textView:(id)arg2 doCommandBySelector:(SEL)arg3;
@property(retain, nonatomic) EditingWebMessageController *controller; // @synthesize controller=_controller;
- (void)convertToBulletedList:(id)arg1;
- (void)convertToNumberedList:(id)arg1;
@property(nonatomic) __weak NSSegmentedControl *createOrRemoveButton; // @synthesize createOrRemoveButton=_createOrRemoveButton;
- (void)createOrRemoveSignature:(id)arg1;
@property(nonatomic) BOOL currentSignatureHasChanges; // @synthesize currentSignatureHasChanges=_currentSignatureHasChanges;
- (void)dealloc;
- (void)decreaseListNestingLevel:(id)arg1;
@property(retain, nonatomic) NSString *defaultFontName; // @synthesize defaultFontName=_defaultFontName;
- (void)defaultSignatureChanged:(id)arg1;
- (void)deleteKey:(id)arg1;
- (void)editLink;
@property(retain, nonatomic) HyperlinkEditor *hyperlinkEditor; // @synthesize hyperlinkEditor=_hyperlinkEditor;
- (void)increaseListNestingLevel:(id)arg1;
- (void)initializeFromDefaults;
- (void)insertBulletedList:(id)arg1;
- (void)insertNumberedList:(id)arg1;
@property(nonatomic) BOOL loadedInitialHTML; // @synthesize loadedInitialHTML=_loadedInitialHTML;
- (void)nowWouldBeAGoodTimeToTerminate:(id)arg1;
- (long long)numberOfRowsInTableView:(id)arg1;
@property(nonatomic) __weak NSButton *placeSignatureAboveQuote; // @synthesize placeSignatureAboveQuote=_placeSignatureAboveQuote;
- (void)placeSignatureAboveQuotedText:(id)arg1;
- (BOOL)preferencesWindowShouldClose;
- (void)removeSelectedLink;
- (void)saveChanges;
@property(retain, nonatomic) WebArchive *savedWebArchive; // @synthesize savedWebArchive=_savedWebArchive;
@property(nonatomic) __weak NSPopUpButton *selectPopup; // @synthesize selectPopup=_selectPopup;
@property(retain, nonatomic) MFMailAccount *selectedAccount; // @synthesize selectedAccount=_selectedAccount;
@property(readonly, nonatomic) BOOL selectionIsInList;
- (BOOL)selectionShouldChangeInTableView:(id)arg1;
@property(nonatomic) __weak DeletingTableView *signaturesTable; // @synthesize signaturesTable=_signaturesTable;
@property(nonatomic) __weak NSButton *textRichnessButton; // @synthesize textRichnessButton=_textRichnessButton;
@property(nonatomic) __weak NSTextField *textRichnessMessageField; // @synthesize textRichnessMessageField=_textRichnessMessageField;
@property(nonatomic) __weak EditingMessageWebView *webView; // @synthesize webView=_webView;
@property(nonatomic) __weak ColorBackgroundView *webViewBackground; // @synthesize webViewBackground=_webViewBackground;
- (BOOL)tableView:(id)arg1 acceptDrop:(id)arg2 row:(long long)arg3 dropOperation:(NSUInteger)arg4;
- (id)tableView:(id)arg1 objectValueForTableColumn:(id)arg2 row:(long long)arg3;
- (void)tableView:(id)arg1 setObjectValue:(id)arg2 forTableColumn:(id)arg3 row:(long long)arg4;
- (NSUInteger)tableView:(id)arg1 validateDrop:(id)arg2 proposedRow:(long long)arg3 proposedDropOperation:(NSUInteger)arg4;
- (void)tableView:(id)arg1 willDisplayCell:(id)arg2 forTableColumn:(id)arg3 row:(long long)arg4;
- (BOOL)tableView:(id)arg1 writeRowsWithIndexes:(id)arg2 toPasteboard:(id)arg3;
- (void)tableViewSelectionDidChange:(id)arg1;
- (id)truncatingAttributes;
- (BOOL)validateMenuItem:(id)arg1;
- (BOOL)validateUserInterfaceItem:(id)arg1;
- (void)viewWillAppear;
- (void)viewWillDisappear;
- (void)webView:(id)arg1 didAddMailAttachment:(id)arg2;
- (void)webView:(id)arg1 didFailLoadWithError:(id)arg2 forFrame:(id)arg3;
- (void)webView:(id)arg1 didFailProvisionalLoadWithError:(id)arg2 forFrame:(id)arg3;
- (void)webView:(id)arg1 didFinishLoadForFrame:(id)arg2;
- (BOOL)webView:(id)arg1 shouldInsertNode:(id)arg2 replacingDOMRange:(id)arg3 givenAction:(long long)arg4;
- (id)webView:(id)arg1 shouldReplaceSelectionWithWebArchive:(id)arg2 givenAction:(long long)arg3;
- (void)webViewDidChange:(id)arg1;
- (void)webViewDidChangeTypingStyle:(id)arg1;

// Remaining properties
@property(readonly, copy) NSString *debugDescription;
@property(readonly, copy) NSString *description;
@property(readonly, copy, nonatomic) NSArray *editedEditableElements;
@property(readonly) NSUInteger hash;
@property(nonatomic) BOOL shouldAttachFilesAtEnd;
@property(readonly) Class superclass;

@end

