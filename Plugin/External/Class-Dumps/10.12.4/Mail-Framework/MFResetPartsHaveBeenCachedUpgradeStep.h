//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header

#import <MFLibraryUpgradeStep.h>

@class NSArray;

@interface MFResetPartsHaveBeenCachedUpgradeStep : MFLibraryUpgradeStep
{
    NSArray *_accounts;
}

+ (BOOL)requiredAfterBackbooting;
+ (NSUInteger)targetVersion;
@property(readonly, copy, nonatomic) NSArray *accounts; // @synthesize accounts=_accounts;
- (id)initWithSQLHandle:(id)arg1;
- (id)initWithSQLHandle:(id)arg1 accounts:(id)arg2;
- (void)runWithRowIDsNeedingConversationRecalculation:(id)arg1;

@end

