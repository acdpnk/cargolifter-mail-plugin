//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


@class MFEWSAccount;

@interface _MFEWSAutodiscoveryTimerTarget : NSObject
{
    MFEWSAccount *_account;
}

@property(nonatomic) __weak MFEWSAccount *account; // @synthesize account=_account;
- (void)kickOffReautodiscovery:(id)arg1;

@end

