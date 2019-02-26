//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header



@class NSArray, NSArrayController, NSBox, NSLayoutConstraint, NSScrollView, NSStackView, NSString, NSTableView, NSTextField;

@interface MessageFilterSelectorViewController : NSViewController <NSTableViewDelegate>
{
    id <MessageFilterSelectorViewControllerDelegate> _delegate;
    NSArray *_selectedFilters;
    NSStackView *_filterStack;
    NSTextField *_mailboxHeader;
    NSScrollView *_mailboxScrollView;
    NSArrayController *_mailboxArrayController;
    NSTableView *_mailboxTableView;
    NSLayoutConstraint *_mailboxWidthConstraint;
    NSBox *_mailboxSeparator;
    NSArrayController *_stateArrayController;
    NSTableView *_stateTableView;
    NSLayoutConstraint *_stateWidthConstraint;
    NSArrayController *_addressArrayController;
    NSTableView *_addressTableView;
    NSLayoutConstraint *_addressWidthConstraint;
    NSArrayController *_optionArrayController;
    NSTableView *_optionTableView;
    NSLayoutConstraint *_optionWidthConstraint;
}

- (void)_disableScrollingForTableView:(id)arg1;
@property(retain, nonatomic) NSArrayController *addressArrayController; // @synthesize addressArrayController=_addressArrayController;
@property(copy, nonatomic) NSArray *addressFilters;
@property(retain, nonatomic) NSTableView *addressTableView; // @synthesize addressTableView=_addressTableView;
@property(retain, nonatomic) NSLayoutConstraint *addressWidthConstraint; // @synthesize addressWidthConstraint=_addressWidthConstraint;
@property(nonatomic) __weak id <MessageFilterSelectorViewControllerDelegate> delegate; // @synthesize delegate=_delegate;
@property(retain, nonatomic) NSStackView *filterStack; // @synthesize filterStack=_filterStack;
@property(retain, nonatomic) NSArrayController *mailboxArrayController; // @synthesize mailboxArrayController=_mailboxArrayController;
@property(copy, nonatomic) NSArray *mailboxFilters;
@property(retain, nonatomic) NSTextField *mailboxHeader; // @synthesize mailboxHeader=_mailboxHeader;
@property(retain, nonatomic) NSScrollView *mailboxScrollView; // @synthesize mailboxScrollView=_mailboxScrollView;
@property(retain, nonatomic) NSBox *mailboxSeparator; // @synthesize mailboxSeparator=_mailboxSeparator;
@property(retain, nonatomic) NSTableView *mailboxTableView; // @synthesize mailboxTableView=_mailboxTableView;
@property(retain, nonatomic) NSLayoutConstraint *mailboxWidthConstraint; // @synthesize mailboxWidthConstraint=_mailboxWidthConstraint;
@property(retain, nonatomic) NSArrayController *optionArrayController; // @synthesize optionArrayController=_optionArrayController;
@property(copy, nonatomic) NSArray *optionFilters;
@property(retain, nonatomic) NSTableView *optionTableView; // @synthesize optionTableView=_optionTableView;
@property(retain, nonatomic) NSLayoutConstraint *optionWidthConstraint; // @synthesize optionWidthConstraint=_optionWidthConstraint;
@property(copy, nonatomic) NSArray *selectedFilters; // @synthesize selectedFilters=_selectedFilters;
@property(retain, nonatomic) NSArrayController *stateArrayController; // @synthesize stateArrayController=_stateArrayController;
@property(copy, nonatomic) NSArray *stateFilters;
@property(retain, nonatomic) NSTableView *stateTableView; // @synthesize stateTableView=_stateTableView;
@property(retain, nonatomic) NSLayoutConstraint *stateWidthConstraint; // @synthesize stateWidthConstraint=_stateWidthConstraint;
- (id)tableView:(id)arg1 rowViewForRow:(long long)arg2;
- (void)tableViewSelectionDidChange:(id)arg1;
- (void)updateWidthConstraint:(id)arg1 forTableView:(id)arg2;
- (void)updateWithSelectedFilters:(id)arg1;
- (void)viewDidLayout;
- (void)viewDidLoad;

// Remaining properties
@property(readonly, copy) NSString *debugDescription;
@property(readonly, copy) NSString *description;
@property(readonly) NSUInteger hash;
@property(readonly) Class superclass;

@end

