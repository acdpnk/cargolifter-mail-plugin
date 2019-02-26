//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


#import "AccountStatusDataSourceDelegate-Protocol.h"
#import "MUIAddressFieldContextProvider-Protocol.h"

@class AccountStatusDataSource, ComposeHeaderRowView, ComposeViewController, MFDeliveryAccount, MUIAddressField, NSArray, NSButtonCell, NSMenu, NSMutableArray, NSPopUpButton, NSSegmentedControl, NSStackView, NSString, NSTextField, NSView;

@interface HeadersEditor : NSObject <MUIAddressFieldContextProvider, AccountStatusDataSourceDelegate, NSStackViewDelegate, NSUserInterfaceValidations>
{
    NSMutableArray *_accessoryViewOwners;
    BOOL _hasChanges;
    BOOL _messageIsToBeSigned;
    BOOL _messageIsToBeEncrypted;
    BOOL _canSign;
    BOOL _canEncrypt;
    ComposeViewController *_composeViewController;
    MUIAddressField *_toField;
    MUIAddressField *_ccField;
    MUIAddressField *_bccField;
    MUIAddressField *_replyToField;
    NSTextField *_subjectField;
    NSTextField *_toTitle;
    NSTextField *_ccTitle;
    NSTextField *_bccTitle;
    NSTextField *_replyToTitle;
    NSTextField *_subjectTitle;
    NSTextField *_fromLabel;
    NSPopUpButton *_fromPopup;
    NSTextField *_signatureLabel;
    NSPopUpButton *_signaturePopup;
    NSPopUpButton *_priorityPopup;
    NSView *_signBlock;
    NSSegmentedControl *_signButton;
    NSSegmentedControl *_encryptButton;
    NSStackView *_contentStack;
    ComposeHeaderRowView *_ccRow;
    ComposeHeaderRowView *_bccRow;
    ComposeHeaderRowView *_replyToRow;
    NSStackView *_subjectStack;
    ComposeHeaderRowView *_fromRow;
    NSStackView *_fromStack;
    ComposeHeaderRowView *_statusRow;
    NSMenu *_disclosureMenu;
    AccountStatusDataSource *_deliveryASDS;
    NSButtonCell *_encryptCell;
    NSButtonCell *_signCell;
}

+ (id)keyPathsForValuesAffectingDeliveryAccount;
- (void)_accountInfoDidChange:(id)arg1;
- (void)_accountStatusDidChange:(id)arg1;
- (BOOL)_alwaysBCCMyself;
- (BOOL)_alwaysCCMyself;
- (void)_animateHeaderRow:(id)arg1 toVisible:(BOOL)arg2;
- (void)_changeHeaderField:(id)arg1;
- (void)_clearField:(id)arg1;
- (void)_composePreferencesChanged:(id)arg1;
- (void)_emailAliasesDidChange:(id)arg1;
- (id)_fromDisplayAddressFromFullAddress:(id)arg1;
- (BOOL)_headerFieldIsEmpty:(id)arg1;
- (id)_headerKeyForView:(id)arg1;
- (void)_mailAccountsDidChange:(id)arg1;
- (id)_newContentsForClearedField:(id)arg1;
- (BOOL)_populateField:(id)arg1 withAddressesForKey:(id)arg2;
- (double)_rowAnimationDuration;
- (void)_setDynamicDeliveryAccountForAccount:(id)arg1;
- (void)_setHeaderRow:(id)arg1 toVisible:(BOOL)arg2 animate:(BOOL)arg3;
- (void)_setVisibilityForEncryptionAndSigning:(BOOL)arg1;
- (void)_setVisibilityForFromView:(BOOL)arg1;
- (void)_setVisibilityForPriorityControl:(BOOL)arg1;
- (void)_setVisibilityForSignatureView:(BOOL)arg1;
- (void)_setupAddressField:(id)arg1;
- (BOOL)_shouldShowFromView;
- (void)_signaturePreferencesChanged:(id)arg1;
- (void)_subjectChanged;
- (void)_toggleEncryption;
- (void)_updateCcOrBccMyselfFieldWithSender:(id)arg1 oldSender:(id)arg2;
- (void)_updateEncryptButton;
- (void)_updateFromControl;
- (void)_updateFullWidthSeparatorState;
- (void)_updatePriorityPopUp;
- (void)_updateSecurityControls;
- (void)_updateSecurityStateInBackgroundForRecipients:(id)arg1 sender:(id)arg2;
- (void)_updateSenderDomainAndAddressWithSender:(id)arg1 accountIdentifier:(id)arg2;
- (void)_updateSignButton;
- (void)_updateSignatureControl;
- (void)_updateSignatureControlOverridingExistingSignature:(id)arg1;
- (void)_webViewDidLoadStationery:(id)arg1;
@property(readonly, nonatomic) NSArray *allHeaderAddresses;
- (void)appendAddressesForToHeader:(id)arg1;
- (void)awakeFromNib;
@property(retain, nonatomic) MUIAddressField *bccField; // @synthesize bccField=_bccField;
@property(nonatomic) __weak ComposeHeaderRowView *bccRow; // @synthesize bccRow=_bccRow;
@property(nonatomic) __weak NSTextField *bccTitle; // @synthesize bccTitle=_bccTitle;
@property(nonatomic) BOOL canEncrypt; // @synthesize canEncrypt=_canEncrypt;
@property(nonatomic) BOOL canSign; // @synthesize canSign=_canSign;
- (BOOL)canSignFromAnyAccount;
@property(retain, nonatomic) MUIAddressField *ccField; // @synthesize ccField=_ccField;
@property(nonatomic) __weak ComposeHeaderRowView *ccRow; // @synthesize ccRow=_ccRow;
@property(nonatomic) __weak NSTextField *ccTitle; // @synthesize ccTitle=_ccTitle;
- (void)changeFromHeader:(id)arg1;
- (void)changeSignature:(id)arg1;
- (void)changeSignatureFrom:(id)arg1 to:(id)arg2;
@property(nonatomic) __weak ComposeViewController *composeViewController; // @synthesize composeViewController=_composeViewController;
- (void)configureButtonsAndPopUps;
@property(nonatomic) __weak NSStackView *contentStack; // @synthesize contentStack=_contentStack;
- (void)controlTextDidBeginEditing:(id)arg1;
- (void)controlTextDidChange:(id)arg1;
- (void)controlTextDidEndEditing:(id)arg1;
- (void)dealloc;
@property(retain, nonatomic) AccountStatusDataSource *deliveryASDS; // @synthesize deliveryASDS=_deliveryASDS;
@property(retain, nonatomic) MFDeliveryAccount *deliveryAccount;
@property(retain, nonatomic) NSMenu *disclosureMenu; // @synthesize disclosureMenu=_disclosureMenu;
- (void)editServerList:(id)arg1 selectedAccount:(id)arg2;
- (void)editSignatures:(id)arg1;
@property(nonatomic) __weak NSSegmentedControl *encryptButton; // @synthesize encryptButton=_encryptButton;
@property(nonatomic) __weak NSButtonCell *encryptCell; // @synthesize encryptCell=_encryptCell;
@property(nonatomic) __weak NSTextField *fromLabel; // @synthesize fromLabel=_fromLabel;
@property(nonatomic) __weak NSPopUpButton *fromPopup; // @synthesize fromPopup=_fromPopup;
@property(nonatomic) __weak ComposeHeaderRowView *fromRow; // @synthesize fromRow=_fromRow;
@property(nonatomic) __weak NSStackView *fromStack; // @synthesize fromStack=_fromStack;
@property(nonatomic) BOOL hasChanges; // @synthesize hasChanges=_hasChanges;
- (BOOL)isOkayToSaveMessage:(id)arg1;
- (void)loadHeadersFromBackEnd:(id)arg1;
- (id)mailAccount;
@property(readonly, nonatomic) BOOL messageHasRecipients;
@property(nonatomic) BOOL messageIsToBeEncrypted; // @synthesize messageIsToBeEncrypted=_messageIsToBeEncrypted;
@property(nonatomic) BOOL messageIsToBeSigned; // @synthesize messageIsToBeSigned=_messageIsToBeSigned;
- (void)observeValueForKeyPath:(id)arg1 ofObject:(id)arg2 change:(id)arg3 context:(void *)arg4;
- (void)prepareToCloseWindow;
@property(nonatomic) __weak NSPopUpButton *priorityPopup; // @synthesize priorityPopup=_priorityPopup;
@property(retain, nonatomic) MUIAddressField *replyToField; // @synthesize replyToField=_replyToField;
@property(nonatomic) __weak ComposeHeaderRowView *replyToRow; // @synthesize replyToRow=_replyToRow;
@property(nonatomic) __weak NSTextField *replyToTitle; // @synthesize replyToTitle=_replyToTitle;
- (void)securityControlChanged:(id)arg1;
- (void)setAllHeaderFieldsToEnabled:(BOOL)arg1;
- (void)setCheckGrammarWithSpelling:(BOOL)arg1;
- (void)setHeaders:(id)arg1;
- (void)setInitialFirstResponder;
- (void)setInlineSpellCheckingEnabled:(BOOL)arg1;
- (void)setMessagePriority:(id)arg1;
- (void)setSelectedAccount:(id)arg1;
@property(nonatomic) __weak NSView *signBlock; // @synthesize signBlock=_signBlock;
@property(nonatomic) __weak NSSegmentedControl *signButton; // @synthesize signButton=_signButton;
@property(nonatomic) __weak NSButtonCell *signCell; // @synthesize signCell=_signCell;
@property(nonatomic) __weak NSTextField *signatureLabel; // @synthesize signatureLabel=_signatureLabel;
@property(nonatomic) __weak NSPopUpButton *signaturePopup; // @synthesize signaturePopup=_signaturePopup;
@property(nonatomic) __weak ComposeHeaderRowView *statusRow; // @synthesize statusRow=_statusRow;
@property(nonatomic) __weak NSTextField *subjectField; // @synthesize subjectField=_subjectField;
@property(nonatomic) __weak NSStackView *subjectStack; // @synthesize subjectStack=_subjectStack;
@property(nonatomic) __weak NSTextField *subjectTitle; // @synthesize subjectTitle=_subjectTitle;
@property(retain, nonatomic) MUIAddressField *toField; // @synthesize toField=_toField;
@property(nonatomic) __weak NSTextField *toTitle; // @synthesize toTitle=_toTitle;
- (void)stackView:(id)arg1 didReattachViews:(id)arg2;
- (void)stackView:(id)arg1 willDetachViews:(id)arg2;
- (void)toggleAccountLock:(id)arg1;
- (void)updateDeliveryAccountControl:(id)arg1;
- (BOOL)validateMenuItem:(id)arg1;
- (BOOL)validateUserInterfaceItem:(id)arg1;

// Remaining properties
@property(readonly, copy) NSString *debugDescription;
@property(readonly, copy) NSString *description;
@property(readonly) NSUInteger hash;
@property(readonly) Class superclass;

@end
