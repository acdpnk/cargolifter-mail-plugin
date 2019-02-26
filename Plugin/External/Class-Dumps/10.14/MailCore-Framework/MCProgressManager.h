//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


#import "MCProgressEntryDelegate-Protocol.h"

@class MCProgressEntry, NSArray, NSMutableArray, NSMutableDictionary, NSString;

@interface MCProgressManager : NSObject <MCProgressEntryDelegate>
{
    NSMutableDictionary *_entriesBySlice;
    NSMutableArray *_orderedEntries;
    MCProgressEntry *_activeEntry;
    NSArray *_trackedAccountNames;
}

+ (id)allocWithZone:(struct _NSZone *)arg1;
+ (id)sharedInstance;
- (void)_addEntry:(id)arg1;
- (void)_diagnosticsNotificationReceived:(id)arg1;
- (id)_entryComparator;
- (void)_refreshActiveEntry;
- (void)_removeEntry:(id)arg1;
@property(retain, nonatomic) MCProgressEntry *activeEntry; // @synthesize activeEntry=_activeEntry;
- (void)addProgress:(id)arg1 forSlice:(long long)arg2;
- (NSUInteger)countOfOrderedEntries;
- (void)dealloc;
- (id)init;
- (void)insertObject:(id)arg1 inOrderedEntriesAtIndex:(NSUInteger)arg2;
- (id)objectInOrderedEntriesAtIndex:(NSUInteger)arg1;
- (void)observeValueForKeyPath:(id)arg1 ofObject:(id)arg2 change:(id)arg3 context:(void *)arg4;
@property(readonly, copy, nonatomic) NSArray *orderedEntries;
- (void)progressEntryDidFinish:(id)arg1;
- (void)removeObjectFromOrderedEntriesAtIndex:(NSUInteger)arg1;
@property(copy, nonatomic) NSArray *trackedAccountNames; // @synthesize trackedAccountNames=_trackedAccountNames;

// Remaining properties
@property(readonly, copy) NSString *debugDescription;
@property(readonly, copy) NSString *description;
@property(readonly) NSUInteger hash;
@property(readonly) Class superclass;

@end

