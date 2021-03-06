//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header

#import "MTMMailbox.h"

@class NSString;

@interface MTMSpecialMailbox : MTMMailbox
{
    BOOL _isObserving;
}

+ (Class)rootMailboxClass;
+ (Class)specialMailboxClassForMailboxType:(long long)arg1;
- (id)identifier;
@property(nonatomic) BOOL isObserving; // @synthesize isObserving=_isObserving;
@property(readonly, copy, nonatomic) NSString *recoverDisplayName;

@end

