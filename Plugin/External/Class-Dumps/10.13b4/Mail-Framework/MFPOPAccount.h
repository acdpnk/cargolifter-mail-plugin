//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header

#import <MFMailAccount.h>

#import "MFPOPAccount.h"

@class MCActivityMonitor, MCAuthScheme, MFPOPStore, NSArray, NSLock, NSOperationQueue, NSString;

@interface MFPOPAccount : MFMailAccount <MFPOPAccount>
{
    NSLock *_connectionActivityLock;
    id _seenMessagesManagerLock;
    id _backgroundActivityFlagsLock;
    BOOL _backgroundFetchInProgress;
    BOOL _deletingMessages;
    BOOL _fetcherNeedsReset;
    BOOL _hasDoneBackgroundSynchronization;
    MFPOPStore *_fetcher;
    MCActivityMonitor *_fetchMonitor;
}

+ (id)accountTypeString;
+ (id)standardPorts;
+ (id)standardSSLPorts;
- (id)URLPersistenceScheme;
- (void)_addAccountAndSeenMessagesToMessageManager;
- (void)_backgroundFetchCompleted;
- (BOOL)_configureFetcherObject;
- (void)_readCustomInfoFromMailboxCache:(id)arg1;
- (void)_sendMailboxDidEndSyncTaskNotification;
- (void)_sendMailboxDidStartSyncTaskNotification;
- (void)acquireConnectionActivityLock;
- (id)archiveMailboxCreateIfNeeded:(BOOL)arg1;
- (id)authenticatedConnection;
@property long long bigMessageWarningSize;
- (BOOL)canAuthenticateWithScheme:(id)arg1;
- (BOOL)canCreateNewMailboxes;
- (BOOL)canGoOffline;
- (BOOL)canMailboxBeRenamed:(id)arg1;
- (BOOL)connectAndAuthenticate:(id)arg1;
- (BOOL)containsMailboxes;
- (long long)defaultPortNumber;
- (long long)defaultSecurePortNumber;
@property long long delayedMessageDeletionInterval;
- (void)deleteMessagesNow:(id)arg1;
- (BOOL)deleteMessagesOnServer;
- (BOOL)deleteMessagesWhenMovedFromInbox;
- (void)deleteSeenMessagesNow;
@property(nonatomic) BOOL deletingMessages; // @synthesize deletingMessages=_deletingMessages;
- (void)fetchAsynchronouslyIsAuto:(BOOL)arg1;
@property(retain, nonatomic) MCActivityMonitor *fetchMonitor; // @synthesize fetchMonitor=_fetchMonitor;
@property(retain, nonatomic) MFPOPStore *fetcher; // @synthesize fetcher=_fetcher;
@property(nonatomic) BOOL fetcherNeedsReset; // @synthesize fetcherNeedsReset=_fetcherNeedsReset;
@property(nonatomic) BOOL hasDoneBackgroundSynchronization; // @synthesize hasDoneBackgroundSynchronization=_hasDoneBackgroundSynchronization;
- (id)init;
- (id)initWithSystemAccount:(id)arg1;
- (void)insertInMailboxes:(id)arg1 atIndex:(NSUInteger)arg2;
- (BOOL)isFetching;
@property BOOL isFirstTimeSync;
- (id)mailboxPathExtension;
- (id)mailboxes;
@property long long messageDeletionPolicy;
- (id)newConnectedConnectionDiscoveringBestSettings:(BOOL)arg1 withConnectTimeout:(double)arg2 readWriteTimeout:(double)arg3;
- (id)newSeenMessagesManager;
- (id)objectSpecifierForMailbox:(id)arg1;
- (id)primaryMailbox;
- (void)releaseAllConnections;
- (void)relinquishConnectionActivityLock;
@property(readonly, nonatomic) BOOL requiresAuthentication;
- (void)resetFetcher;
@property(readonly, copy, nonatomic) NSString *saslProfileName;
- (void)setDeleteMessagesOnServer:(BOOL)arg1;
- (void)setDeleteMessagesWhenMovedFromInbox:(BOOL)arg1;
- (void)setIsOffline:(BOOL)arg1;
- (BOOL)shouldFetchIsAuto:(BOOL)arg1;
- (Class)storeClassForMailbox:(id)arg1;
- (id)storeForMailbox:(id)arg1 createIfNeeded:(BOOL)arg2;
- (id)valueInMailboxesWithName:(id)arg1;

// Remaining properties
@property(readonly, copy) NSString *accountTypeString;
@property BOOL allowInsecureAuthentication;
@property(readonly, copy) NSString *appleAuthenticationToken;
@property(readonly, copy) NSString *applePersonID;
@property(copy) NSString *authenticationScheme;
@property(copy) NSString *canonicalEmailAddress;
@property BOOL configureDynamically;
@property(readonly, copy) NSString *debugDescription;
@property(readonly, copy) NSString *description;
@property(copy) NSString *displayName;
@property(copy) NSString *externalHostname;
@property(readonly) NSUInteger hash;
@property(copy) NSString *hostname;
@property(readonly, copy) NSString *identifier;
@property(readonly, nonatomic) BOOL isGmailAccount;
@property(readonly) BOOL isYahooAccount;
@property(readonly, copy) NSString *oauthToken;
@property(copy) NSString *password;
@property long long portNumber;
@property(retain) MCAuthScheme *preferredAuthScheme;
@property(readonly, nonatomic) NSOperationQueue *remoteFetchQueue;
@property(readonly, nonatomic) NSOperationQueue *remoteTaskQueue;
@property long long securityLayerType;
@property BOOL shouldUseAuthentication;
@property(readonly, copy, nonatomic) NSArray *standardPorts;
@property(readonly, copy, nonatomic) NSArray *standardSSLPorts;
@property(readonly) Class superclass;
@property(copy) NSString *username;
@property BOOL usesSSL;

@end

