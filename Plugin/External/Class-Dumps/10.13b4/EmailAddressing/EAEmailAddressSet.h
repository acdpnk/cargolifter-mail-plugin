//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


@interface EAEmailAddressSet : NSMutableSet
{
    NSMutableSet *_internalSet;
}

+ (id)set;
+ (id)setWithCapacity:(NSUInteger)arg1;
- (void)addObject:(id)arg1;
- (id)allObjects;
- (id)copyWithZone:(struct _NSZone *)arg1;
- (NSUInteger)count;
- (id)init;
- (id)initWithCapacity:(NSUInteger)arg1;
@property(retain, nonatomic) NSMutableSet *internalSet; // @synthesize internalSet=_internalSet;
- (void)intersectSet:(id)arg1;
- (BOOL)intersectsSet:(id)arg1;
- (BOOL)isEqualToSet:(id)arg1;
- (BOOL)isSubsetOfSet:(id)arg1;
- (id)member:(id)arg1;
- (void)minusSet:(id)arg1;
- (id)mutableCopyWithZone:(struct _NSZone *)arg1;
- (id)objectEnumerator;
- (void)removeAllObjects;
- (void)removeObject:(id)arg1;
- (void)setSet:(id)arg1;
- (void)unionSet:(id)arg1;

@end
