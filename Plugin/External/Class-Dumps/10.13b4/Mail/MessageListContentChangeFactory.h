//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


@interface MessageListContentChangeFactory : NSObject
{
}

+ (id)createChangeFromAddedIndexes:(id)arg1 withAnimationOptions:(NSUInteger)arg2;
+ (id)createChangeFromRemovedIndexes:(id)arg1 withAnimationOptions:(NSUInteger)arg2;
+ (id)createChangeMovingFromIndex:(NSUInteger)arg1 toIndex:(NSUInteger)arg2;

@end

