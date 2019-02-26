//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header

#import "MCConnection.h"

@class EWSExchangeServiceBinding, MFEWSAccount;

@interface MFEWSConnection : MCConnection
{
    EWSExchangeServiceBinding *_binding;
}

+ (id)log;
- (id)_connectAndAuthenticateDiscoveringBestSettings:(BOOL)arg1;
- (id)_fetchRootFolderId:(id *)arg1;
- (void)_handleServerBusyError:(id)arg1;
- (void)_setupConnectionErrorForMonitorWithPort:(long long)arg1 usingSSL:(BOOL)arg2 serverTrust:(struct __SecTrust *)arg3;
@property __weak MFEWSAccount *account;
- (BOOL)authenticate;
@property(retain) EWSExchangeServiceBinding *binding; // @synthesize binding=_binding;
- (BOOL)connectAndAuthenticate;
- (BOOL)connectDiscoveringBestSettings:(BOOL)arg1;
- (void)dealloc;
- (void)disconnect;
- (void)disconnectWithError:(id)arg1;
- (BOOL)isValidAllowNetworking:(BOOL)arg1;
- (void)quit;
- (id)sendMessage:(id)arg1 forRequest:(id)arg2;
- (id)sendMessage:(id)arg1 schemaVersion:(id)arg2 error:(id *)arg3;
- (BOOL)supportsSchema:(id)arg1;

@end

