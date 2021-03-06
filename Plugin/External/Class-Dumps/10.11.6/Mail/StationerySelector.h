//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header



@class ColorBackgroundView, ComposeViewController, FlatTableView, NSArray, NSMutableArray, NSMutableDictionary, NSScrollView, NSString, NSTextField, NSView, StationeryLoader, ThumbnailMatrix;

@interface StationerySelector : NSObject <NSDraggingSource, NSTableViewDataSource, NSTableViewDelegate>
{
    NSArray *_stationeryDictionaries;
    NSMutableArray *_deletedStationery;
    NSMutableDictionary *_scrollPositionByCategory;
    BOOL _isFirstShowOfCategoriesForFavorites;
    BOOL _isFirstShowOfCategoriesForExistingStationery;
    BOOL _hasRegisteredForNewThumbnailImageNotifications;
    FlatTableView *_categoriesTableView;
    ThumbnailMatrix *_thumbnailMatrix;
    ComposeViewController *_composeViewController;
    ColorBackgroundView *_selectorPane;
    NSTextField *_emptyFavoritesMessageView;
    NSScrollView *_thumbnailsScrollView;
    ColorBackgroundView *_bottomDivider;
    NSView *_verticalDivider;
    StationeryLoader *_stationeryLoader;
    NSArray *_categoryDictionaries;
}

- (void)_displayStationery:(id)arg1 showDeleteButtons:(BOOL)arg2 beginningAtIndex:(long long)arg3;
- (BOOL)_draggingPasteboardContainsStationery;
- (void)_ensureValidSelection;
- (id)_mainContentConstraintsForView:(id)arg1;
- (void)_moveThumbnailsToScrollView;
- (void)_refreshStationery;
- (void)_restoreThumbnailScrollPosition;
- (void)_saveThumbnailScrollPosition;
- (void)_setStationeryDictionaries:(id)arg1;
- (void)_stationeryDidChange:(id)arg1;
- (void)_thumbnailImageIsAvailable:(id)arg1;
- (void)awakeFromNib;
@property(nonatomic) __weak ColorBackgroundView *bottomDivider; // @synthesize bottomDivider=_bottomDivider;
@property(nonatomic) __weak FlatTableView *categoriesTableView; // @synthesize categoriesTableView=_categoriesTableView;
@property(copy, nonatomic) NSArray *categoryDictionaries; // @synthesize categoryDictionaries=_categoryDictionaries;
- (void)clearStationerySelection;
@property(nonatomic) __weak ComposeViewController *composeViewController; // @synthesize composeViewController=_composeViewController;
- (void)dealloc;
- (void)deleteStationery:(id)arg1;
- (NSUInteger)draggingSession:(id)arg1 sourceOperationMaskForDraggingContext:(long long)arg2;
@property(nonatomic) __weak NSTextField *emptyFavoritesMessageView; // @synthesize emptyFavoritesMessageView=_emptyFavoritesMessageView;
@property(nonatomic) BOOL hasRegisteredForNewThumbnailImageNotifications; // @synthesize hasRegisteredForNewThumbnailImageNotifications=_hasRegisteredForNewThumbnailImageNotifications;
- (id)init;
@property(nonatomic) BOOL isFirstShowOfCategoriesForExistingStationery; // @synthesize isFirstShowOfCategoriesForExistingStationery=_isFirstShowOfCategoriesForExistingStationery;
@property(nonatomic) BOOL isFirstShowOfCategoriesForFavorites; // @synthesize isFirstShowOfCategoriesForFavorites=_isFirstShowOfCategoriesForFavorites;
- (long long)numberOfRowsInTableView:(id)arg1;
- (void)selectCategory:(id)arg1;
- (void)selectStationery:(id)arg1;
- (BOOL)selectionShouldChangeInTableView:(id)arg1;
@property(nonatomic) __weak ColorBackgroundView *selectorPane; // @synthesize selectorPane=_selectorPane;
@property(nonatomic) __weak ThumbnailMatrix *thumbnailMatrix; // @synthesize thumbnailMatrix=_thumbnailMatrix;
@property(nonatomic) __weak NSScrollView *thumbnailsScrollView; // @synthesize thumbnailsScrollView=_thumbnailsScrollView;
@property(nonatomic) __weak NSView *verticalDivider; // @synthesize verticalDivider=_verticalDivider;
- (void)showStationery;
- (void)startDragSessionFromIndex:(long long)arg1 withImage:(id)arg2 event:(id)arg3;
@property(readonly, nonatomic) __weak StationeryLoader *stationeryLoader; // @synthesize stationeryLoader=_stationeryLoader;
- (BOOL)tableView:(id)arg1 acceptDrop:(id)arg2 row:(long long)arg3 dropOperation:(NSUInteger)arg4;
- (id)tableView:(id)arg1 objectValueForTableColumn:(id)arg2 row:(long long)arg3;
- (NSUInteger)tableView:(id)arg1 validateDrop:(id)arg2 proposedRow:(long long)arg3 proposedDropOperation:(NSUInteger)arg4;
- (void)tableViewSelectionDidChange:(id)arg1;

// Remaining properties
@property(readonly, copy) NSString *debugDescription;
@property(readonly, copy) NSString *description;
@property(readonly) NSUInteger hash;
@property(readonly) Class superclass;

@end

