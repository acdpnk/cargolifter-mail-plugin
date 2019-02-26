//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


@class MCAuthScheme, NSString;

@interface AuthSchemeBindingProxy : NSObject
{
    BOOL _isSeparator;
    MCAuthScheme *_authScheme;
}

+ (id)noneProxy;
+ (id)separatorProxy;
@property(retain, nonatomic) MCAuthScheme *authScheme; // @synthesize authScheme=_authScheme;
- (NSUInteger)hash;
@property(readonly, copy, nonatomic) NSString *humanReadableName;
- (id)init;
- (id)initWithAuthScheme:(id)arg1;
- (BOOL)isEqual:(id)arg1;
@property(nonatomic) BOOL isSeparator; // @synthesize isSeparator=_isSeparator;
@property(readonly, copy, nonatomic) NSString *name;

@end

