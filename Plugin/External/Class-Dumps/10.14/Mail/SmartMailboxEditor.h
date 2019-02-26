//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


@class CriteriaUIHelper, MFMailbox, NSTextField, NSTextView, NSView, NSWindow;

@interface SmartMailboxEditor : NSObject
{
    BOOL _editedMailboxIsNew;
    CriteriaUIHelper *_criteriaUIHelper;
    NSWindow *_makeNewMailboxWindow;
    NSTextField *_nameField;
    NSWindow *_makeNewFolderWindow;
    NSTextField *_groupNameField;
    NSWindow *_notEditableWindow;
    NSTextField *_searchStringField;
    NSTextView *_mailboxesTextView;
    NSView *_criteriaView;
    SmartMailboxEditor *_me;
    MFMailbox *_mailboxBeingEdited;
    MFMailbox *_mailboxBeingValidated;
}

+ (BOOL)isEditingInProgress;
+ (BOOL)mailboxIsEditable:(id)arg1;
- (void)_saveEditedMailbox;
- (void)_sheetDidEnd:(id)arg1 returnCode:(long long)arg2;
- (void)cancelClicked:(id)arg1;
- (void)createNewMailboxGroup;
@property(retain, nonatomic) CriteriaUIHelper *criteriaUIHelper; // @synthesize criteriaUIHelper=_criteriaUIHelper;
@property(nonatomic) __weak NSView *criteriaView; // @synthesize criteriaView=_criteriaView;
- (void)editSmartMailbox:(id)arg1 suggestedName:(id)arg2 isNew:(BOOL)arg3;
@property(nonatomic) BOOL editedMailboxIsNew; // @synthesize editedMailboxIsNew=_editedMailboxIsNew;
@property(nonatomic) __weak NSTextField *groupNameField; // @synthesize groupNameField=_groupNameField;
@property(retain, nonatomic) MFMailbox *mailboxBeingEdited; // @synthesize mailboxBeingEdited=_mailboxBeingEdited;
@property(retain, nonatomic) MFMailbox *mailboxBeingValidated; // @synthesize mailboxBeingValidated=_mailboxBeingValidated;
@property(nonatomic) __weak NSTextView *mailboxesTextView; // @synthesize mailboxesTextView=_mailboxesTextView;
@property(retain, nonatomic) NSWindow *makeNewFolderWindow; // @synthesize makeNewFolderWindow=_makeNewFolderWindow;
@property(retain, nonatomic) NSWindow *makeNewMailboxWindow; // @synthesize makeNewMailboxWindow=_makeNewMailboxWindow;
@property(retain, nonatomic) SmartMailboxEditor *me; // @synthesize me=_me;
@property(nonatomic) __weak NSTextField *nameField; // @synthesize nameField=_nameField;
@property(retain, nonatomic) NSWindow *notEditableWindow; // @synthesize notEditableWindow=_notEditableWindow;
- (void)okClicked:(id)arg1;
@property(nonatomic) __weak NSTextField *searchStringField; // @synthesize searchStringField=_searchStringField;

@end

