//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header

#import "AdvancedServerSettingsController.h"

@class NSString;

@interface IMAPAdvancedServerSettingsController : AdvancedServerSettingsController
{
    BOOL _accountNeedsSaving;
}

+ (id)keyPathsForValuesAffectingServerPath;
@property(nonatomic) BOOL accountNeedsSaving; // @synthesize accountNeedsSaving=_accountNeedsSaving;
@property(copy, nonatomic) NSString *serverPath;

@end

