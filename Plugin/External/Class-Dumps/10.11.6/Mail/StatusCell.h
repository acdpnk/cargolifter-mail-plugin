//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


@interface StatusCell : NSImageTextFieldCell
{
    long long _statusType;
}

- (id)accessibilityRoleDescription;
- (id)accessibilityValue;
@property(nonatomic) long long statusType; // @synthesize statusType=_statusType;

@end

