//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header

#import <MFLibraryUpgradeStep.h>

@interface MFRemoveCategoryColumnUpgradeStep : MFLibraryUpgradeStep
{
}

+ (BOOL)needToPerformFromMinorVersion:(NSUInteger)arg1 initialLastWriteMinorVersion:(NSUInteger)arg2 fromBackBooting:(char *)arg3;
+ (NSUInteger)targetVersion;
- (void)runWithRowIDsNeedingConversationRecalculation:(id)arg1;

@end

