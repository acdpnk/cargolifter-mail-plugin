//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


@class NSArray, NSDictionary;

@interface MCTaskList : NSObject
{
    id <MCTaskListDelegate> _delegate;
    NSArray *_sortingKeys;
    NSDictionary *_listsByKey;
    NSDictionary *_comparatorsByKey;
}

+ (id)_newComparatorForKey:(id)arg1;
- (void)_extractTask:(id)arg1 fromListWithKey:(id)arg2;
- (void)_insertTask:(id)arg1 intoListWithKey:(id)arg2;
- (void)addTask:(id)arg1;
@property(readonly, copy, nonatomic) NSDictionary *comparatorsByKey; // @synthesize comparatorsByKey=_comparatorsByKey;
- (id)copyOfListForKey:(id)arg1;
- (void)dealloc;
@property(nonatomic) __weak id <MCTaskListDelegate> delegate; // @synthesize delegate=_delegate;
- (id)description;
- (void)enumerateTasksForKey:(id)arg1 usingBlock:(id)arg2;
- (id)highestPriorityTaskForKey:(id)arg1;
- (id)init;
- (id)initWithSortingKeys:(id)arg1;
@property(readonly, copy, nonatomic) NSDictionary *listsByKey; // @synthesize listsByKey=_listsByKey;
- (void)observeValueForKeyPath:(id)arg1 ofObject:(id)arg2 change:(id)arg3 context:(void *)arg4;
- (void)removeTask:(id)arg1;
@property(readonly, copy, nonatomic) NSArray *sortingKeys; // @synthesize sortingKeys=_sortingKeys;
@property(readonly, nonatomic) NSUInteger taskCount;

@end

