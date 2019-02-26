//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


@class NSMutableArray, NSMutableIndexSet, NSPredicate;

@interface ManagedList : NSObject
{
    NSMutableArray *_orderedObjects;
    NSMutableIndexSet *_unfilteredIndexes;
    id _comparator;
    NSPredicate *_filterPredicate;
    id <ManagedListSortInfo> _sortInfo;
}

- (NSUInteger)_insertObjectIfAbsent:(id)arg1 intoArray:(id)arg2 inSortedRange:(struct _NSRange)arg3 usingComparator:(id)arg4 didInsert:(char *)arg5;
- (NSUInteger)_removeObject:(id)arg1 inSortedRange:(struct _NSRange)arg2 didRemove:(char *)arg3;
- (NSUInteger)_removeObjectIfPresent:(id)arg1 fromArray:(id)arg2 inSortedRange:(struct _NSRange)arg3 usingComparator:(id)arg4 didRemove:(char *)arg5;
- (NSUInteger)_unadjustedIndexForAdjustedIndex:(NSUInteger)arg1;
- (void)applyFilterReturningAddedIndexes:(id *)arg1 removedIndexes:(id *)arg2;
@property(copy, nonatomic) id comparator; // @synthesize comparator=_comparator;
- (id)copyOfOrderedObjects;
- (void)enumerateOrderedObjectsUsingBlock:(id)arg1;
@property(retain, nonatomic) NSPredicate *filterPredicate; // @synthesize filterPredicate=_filterPredicate;
- (NSUInteger)indexOfOrderedObject:(id)arg1;
- (id)init;
- (void)invert;
- (NSUInteger)mergeObject:(id)arg1;
- (id)mergeObjects:(id)arg1;
- (id)mutableCopyOfOrderedObjects;
- (id)orderedObjectAtIndex:(NSUInteger)arg1;
- (id)orderedObjectsAtIndexes:(id)arg1;
@property(readonly, nonatomic) NSUInteger orderedObjectsCount;
- (NSUInteger)removeObject:(id)arg1;
- (id)removeObjects:(id)arg1;
- (void)resort;
- (void)setOrderedObject:(id)arg1 atIndex:(NSUInteger)arg2;
@property(retain, nonatomic) id <ManagedListSortInfo> sortInfo; // @synthesize sortInfo=_sortInfo;

@end
