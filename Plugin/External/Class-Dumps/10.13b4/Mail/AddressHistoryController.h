//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header



@class NSButton, NSImage, NSMutableArray, NSMutableDictionary, NSOperationQueue, NSSearchField, NSString, NSTableView, NSWindow;

@interface AddressHistoryController : NSObject <NSTableViewDataSource, NSTableViewDelegate>
{
    NSMutableArray *_historyRecords;
    BOOL _sortIsAscending;
    NSTableView *_historyTableView;
    NSButton *_addToContactsButton;
    NSWindow *_window;
    NSSearchField *_searchField;
    NSMutableDictionary *_abRecordMap;
    NSOperationQueue *_fetchQueue;
    NSString *_sortColumn;
    NSImage *_addressBookPersonImage;
}

+ (id)allocWithZone:(struct _NSZone *)arg1;
+ (id)sharedInstance;
- (void)_addressBookDidChange:(id)arg1;
- (void)_cancelSearch:(id)arg1;
- (void)_fetchRecentsDataWithCompletionBlock:(id)arg1;
- (id)_recordForAddress:(id)arg1;
- (void)_showColumnSortIndicator;
- (void)_sortHistoryData;
@property(retain, nonatomic) NSMutableDictionary *abRecordMap; // @synthesize abRecordMap=_abRecordMap;
- (void)addToContacts:(id)arg1;
@property(nonatomic) __weak NSButton *addToContactsButton; // @synthesize addToContactsButton=_addToContactsButton;
@property(readonly, nonatomic) NSImage *addressBookPersonImage; // @synthesize addressBookPersonImage=_addressBookPersonImage;
- (void)dealloc;
- (void)deleteFromHistory:(id)arg1;
@property(readonly, nonatomic) NSOperationQueue *fetchQueue; // @synthesize fetchQueue=_fetchQueue;
@property(nonatomic) __weak NSTableView *historyTableView; // @synthesize historyTableView=_historyTableView;
- (id)init;
- (long long)numberOfRowsInTableView:(id)arg1;
- (void)openContacts:(id)arg1;
- (void)search:(id)arg1;
@property(nonatomic) __weak NSSearchField *searchField; // @synthesize searchField=_searchField;
- (void)searchIndex:(id)arg1;
@property(nonatomic) __weak NSString *sortColumn; // @synthesize sortColumn=_sortColumn;
@property(nonatomic) BOOL sortIsAscending; // @synthesize sortIsAscending=_sortIsAscending;
@property(retain, nonatomic) NSWindow *window; // @synthesize window=_window;
- (void)showAddressHistory;
- (void)tableView:(id)arg1 didClickTableColumn:(id)arg2;
- (id)tableView:(id)arg1 objectValueForTableColumn:(id)arg2 row:(long long)arg3;
- (id)tableView:(id)arg1 toolTipForCell:(id)arg2 rect:(struct CGRect *)arg3 tableColumn:(id)arg4 row:(long long)arg5 mouseLocation:(struct CGPoint)arg6;
- (void)tableView:(id)arg1 willDisplayCell:(id)arg2 forTableColumn:(id)arg3 row:(long long)arg4;
- (void)tableViewSelectionDidChange:(id)arg1;
- (void)windowWillClose:(id)arg1;

// Remaining properties
@property(readonly, copy) NSString *debugDescription;
@property(readonly, copy) NSString *description;
@property(readonly) NSUInteger hash;
@property(readonly) Class superclass;

@end
