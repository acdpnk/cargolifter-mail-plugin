//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


@class NSArray, NSMutableArray, NSMutableDictionary, _StationeryThumbnailCreator;

@interface StationeryLoader : NSObject
{
    NSMutableDictionary *_categoriesByDisplayName;
    NSMutableArray *_orderedCategoryDisplayNames;
    NSMutableDictionary *_orderedStationeryByCategoryDisplayName;
    _StationeryThumbnailCreator *_thumbnailCreator;
}

+ (id)allocWithZone:(struct _NSZone *)arg1;
+ (id)pathForCustomCategory;
+ (id)pathForCustomCategoryResources;
+ (void)purgeDeletedCustomStationery;
+ (id)sharedInstance;
- (void)_addToFavoritesInPosition:(NSUInteger)arg1 stationeryWithPath:(id)arg2 inCategoryWithDisplayName:(id)arg3;
- (id)_bundlePathForCategoryWithFolderName:(id)arg1 company:(id)arg2 type:(long long)arg3;
- (id)_cacheNameForCompany:(id)arg1 categoryDisplayName:(id)arg2 type:(long long)arg3;
- (void)_cacheTOC:(id)arg1 withName:(id)arg2;
- (id)_cachedTOCWithName:(id)arg1;
- (id)_categoryTOCForCategoryFolderName:(id)arg1 company:(id)arg2 type:(long long)arg3 categoryDisplayName:(id)arg4;
- (void)_combinePartialTOCs:(id)arg1;
- (id)_companyTOCWithName:(id)arg1 type:(long long)arg2 isFromCache:(char *)arg3;
- (id)_dictionaryForCustomCategoryForCompany:(BOOL)arg1;
- (id)_dictionaryForStationeryWithPath:(id)arg1 inCategoryWithDisplayName:(id)arg2;
- (id)_dictionaryForStationeryWithPath:(id)arg1 inCategoryWithDisplayName:(id)arg2 position:(NSUInteger *)arg3;
- (id)_pathForStationeryNamed:(id)arg1 inCategoryWithDisplayName:(id)arg2;
- (BOOL)_recursivelyCreateDirectory:(id)arg1 error:(id *)arg2;
- (void)_reinsertStationeryWithInformation:(id)arg1;
- (BOOL)_saveCustomStationery:(id)arg1 byMovingFromPath:(id)arg2 error:(id *)arg3;
- (void)_synchronouslyPurgeDeletedCustomStationery:(id)arg1;
- (void)_updateCategories;
- (void)_updateStationeryInCategoryWithDisplayName:(id)arg1;
- (id)_validatedCompanyCategoryDictionary:(id)arg1 categoryFolderName:(id)arg2 companyBundle:(id)arg3 type:(long long)arg4;
- (id)_validatedStationeryDictionary:(id)arg1 withName:(id)arg2 categoryBundle:(id)arg3 needsThumbnail:(char *)arg4;
- (void)addToFavoritesStationeryWithPath:(id)arg1 inCategoryWithDisplayName:(id)arg2;
- (void)createAppleUserCompanyBundleIfNecessary;
- (BOOL)customStationeryWithNameExists:(id)arg1 index:(NSUInteger *)arg2;
- (void)dealloc;
- (void)deleteStationeryWithDictionary:(id)arg1 fromCategoryWithDisplayName:(id)arg2 undoManager:(id)arg3;
- (BOOL)installStationery:(id)arg1;
@property(readonly, copy, nonatomic) NSArray *orderedCategoryDictionaries;
@property(readonly, copy, nonatomic) NSArray *orderedCategoryDisplayNamesIncludingFavorites;
- (id)orderedStationeryDictionariesForCategoryWithDisplayName:(id)arg1;
- (id)pathForFavoritesList;
- (id)pathForStationeryWithID:(id)arg1;
- (void)purgeDeletedCustomStationery:(id)arg1;
- (BOOL)saveCustomStationery:(id)arg1 error:(id *)arg2;
@property(retain) _StationeryThumbnailCreator *thumbnailCreator; // @synthesize thumbnailCreator=_thumbnailCreator;
- (BOOL)stationery:(id)arg1 isInCategoryWithDisplayName:(id)arg2;
- (id)stationeryWithID:(id)arg1;
- (id)stationeryWithPath:(id)arg1;
- (void)thumbnailCreator:(id)arg1 didCreateThumbnail:(id)arg2 forCustomStationeryWithPath:(id)arg3;
- (void)thumbnailCreatorDidCompletelyFinish:(id)arg1;
- (void)thumbnailCreatorDidCreateThumbnailForCustomStationery:(id)arg1;
- (void)updateStationery;

@end
