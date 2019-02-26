//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


@class ACAccount, NSString;

@protocol EMAccount <NSObject>
- (BOOL)canAuthenticateWithCurrentCredentials;
- (BOOL)hasPasswordCredential;
@property(copy, nonatomic) NSString *hostname;
@property(copy, nonatomic) NSString *password;
- (void)savePersistentAccount;
- (ACAccount *)systemAccount;
@end

