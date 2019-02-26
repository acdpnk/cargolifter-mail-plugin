//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header

#import <MFRemoteStoreAccount.h>

#import "IMAPAccount-Protocol.h"

@class IMAPTaskManager, MCAuthScheme, MFIMAPOperationCache, MFLibraryIMAPStore, MFMailbox, NSArray, NSDictionary, NSError, NSLock, NSMutableDictionary, NSMutableSet, NSOperationQueue, NSString;

@interface MFIMAPAccount : MFRemoteStoreAccount <IMAPAccount>
{
    NSMutableDictionary *_syncEngineMap;
    NSArray *_lastKnownCapabilities;
    NSMutableSet *_namespacePrivatePrefixes;
    NSMutableSet *_namespacePublicPrefixes;
    NSMutableSet *_namespaceSharedPrefixes;
    NSString *_separatorChar;
    NSLock *_connectionPoolLock;
    MFIMAPOperationCache *_offlineCache;
    NSString *_serverPathPrefixWithFilesystemSeparator;
    NSString *_serverPathPrefixAsFilesystemPath;
    NSLock *_fsPrefixLock;
    NSLock *_mailboxListingLock;
    NSMutableSet *_mailboxURLsToSynchronize;
    NSMutableDictionary *_IMAPMailboxes;
    NSMutableDictionary *_IMAPQuotaRoots;
    id _allMailLock;
    MFMailbox *_allMailMailbox;
    MFMailbox *_serverDefinedArchiveMailbox;
    id _serverDefinedArchiveMailboxLock;
    MFMailbox *_serverDefinedDraftsMailbox;
    id _serverDefinedDraftsMailboxLock;
    MFMailbox *_serverDefinedJunkMailbox;
    id _serverDefinedJunkMailboxLock;
    MFMailbox *_serverDefinedSentMailbox;
    id _serverDefinedSentMailboxLock;
    MFMailbox *_serverDefinedTrashMailbox;
    id _serverDefinedTrashMailboxLock;
    id _propertyDiscoveryLock;
    BOOL _currentlySynchronizingMailboxList;
    id _synchronizeMailboxListingLock;
    NSMutableSet *_labelsBeingCleanedUp;
    BOOL _lastConnectionFailed;
    BOOL _shouldIncludePrefixInPath;
    BOOL _supportsQuickResynchronization;
    MFLibraryIMAPStore *_idleStore;
    double _lastMailboxListFetchTime;
    NSOperationQueue *_remoteTaskQueue;
    NSOperationQueue *_remoteFetchQueue;
    NSDictionary *_serverID;
}

+ (void)_deleteQueuedMailboxes:(id)arg1;
+ (id)_mailboxNameForPathComponent:(id)arg1;
+ (id)_pathComponentForMailboxName:(id)arg1;
+ (id)accountTypeString;
+ (id)backgroundQueue;
+ (id)invocationQueue;
+ (id)standardPorts;
+ (id)standardSSLPorts;
- (id)IMAPMailboxForMailbox:(id)arg1 createIfNeeded:(BOOL)arg2;
- (id)IMAPMailboxForMailbox:(id)arg1 name:(id)arg2 createIfNeeded:(BOOL)arg3;
- (id)IMAPMailboxForMailboxName:(id)arg1 createIfNeeded:(BOOL)arg2;
- (id)URLPersistenceScheme;
- (id)_addIMAPMailboxForMailbox:(id)arg1 name:(id)arg2;
- (void)_allegedHighestModificationSequenceDidChangeForIMAPMailbox:(id)arg1;
- (BOOL)_askToChangePathPrefixToCreateMailbox:(id)arg1 displayName:(id)arg2 withSyncHandler:(id)arg3;
- (BOOL)_cleanUpMessagesInGmailLabel:(id)arg1;
- (void)_cleanUpMessagesInGmailLabels;
- (void)_clearAllPathBasedCachesAndDelete:(BOOL)arg1;
- (id)_colorByMessageFromColorByMessageDigest:(id)arg1;
- (id)_copyMailboxWithParent:(id)arg1 name:(id)arg2 pathComponent:(id)arg3 attributes:(NSUInteger)arg4 existingMailbox:(id)arg5;
- (BOOL)_createMailbox:(id)arg1 withSyncHandler:(id)arg2;
- (BOOL)_deleteMailbox:(id)arg1 reflectToServer:(BOOL)arg2;
- (id)_fileSystemServerPathPrefix:(BOOL)arg1;
- (id)_fullIMAPPathForPath:(id)arg1 relativeToMailbox:(id)arg2;
- (id)_hostnameFromParentAccount:(id)arg1;
- (id)_infoForMatchingURL:(id)arg1;
- (id)_listingForMailbox:(id)arg1 listAllChildren:(BOOL)arg2;
- (id)_listingForMailbox:(id)arg1 listAllChildren:(BOOL)arg2 onlySubscribed:(BOOL)arg3;
- (void)_loadEntriesFromFileSystemPath:(id)arg1 parent:(id)arg2;
- (void)_loadMailboxListingIntoCache:(id)arg1 parent:(id)arg2 addedMailboxes:(id)arg3 removedMailboxes:(id)arg4;
- (void)_loadMailboxListingIntoCache:(id)arg1 parent:(id)arg2 addedMailboxes:(id)arg3 removedMailboxes:(id)arg4 updatingSourceMailbox:(BOOL)arg5;
- (id)_mailboxNameForLabelName:(id)arg1;
- (id)_mailboxPathPrefix:(BOOL)arg1;
- (void)_mailboxesWereRemovedFromTree:(id)arg1 withFileSystemPaths:(id)arg2;
- (void)_migrateColorsForGmail;
- (id)_namespacePrefixesForPrivate:(BOOL)arg1 public:(BOOL)arg2 shared:(BOOL)arg3;
- (id)_newTaskManager;
- (BOOL)_parentSystemAccountDidUpdateProperties:(id)arg1 changedSystemAccount:(char *)arg2;
- (void)_performDiagnostics:(id)arg1;
- (void)_readCustomInfoFromMailboxCache:(id)arg1;
- (id)_recursivelyFilterMailboxList:(id)arg1 accordingToList:(id)arg2;
- (void)_recursivelyModifySubscriptions:(BOOL)arg1 forMailbox:(id)arg2 children:(id)arg3 withSyncHandler:(id)arg4;
- (void)_releaseAllConnectionsAndCallSuper:(BOOL)arg1 saveOfflineCache:(BOOL)arg2;
- (void)_removeIMAPMailboxWithName:(id)arg1;
- (void)_renameIMAPMailboxWithMailbox:(id)arg1 fromName:(id)arg2 toName:(id)arg3;
- (id)_serverDefinedMailboxWithAttribute:(NSUInteger)arg1;
- (BOOL)_setChildren:(id)arg1 forMailbox:(id)arg2;
- (void)_setFileSystemServerPathPrefix;
- (id)_shouldUseGmailLabelStoresNumber;
- (id)_specialMailboxWithType:(int)arg1 create:(BOOL)arg2 isLocal:(BOOL)arg3;
- (void)_startObserving:(BOOL)arg1 IMAPMailbox:(id)arg2;
- (BOOL)_synchronizeMailboxList;
- (void)_synchronizeMailboxListDuringMailCheck;
- (void)_synchronouslyLoadListingForParent:(id)arg1;
- (void)_unseenCount:(unsigned int)arg1 didChangeForIMAPMailbox:(id)arg2;
- (void)_updateIdleMailbox;
- (void)_updateSpecialMailboxes;
- (void)_validateConnections;
- (void)_waitForMailboxListingLoadToComplete;
- (void)_writeCustomInfoToMailboxCache:(id)arg1;
@property(readonly, copy, nonatomic) NSArray *allBackgroundMailboxNames;
- (id)allMailMailbox;
@property(readonly) BOOL allowsPartialDownloads;
- (id)authenticatedConnection;
- (BOOL)canMailboxBeDeleted:(id)arg1;
- (void)cleanUpMessagesInGmailLabel:(id)arg1;
- (void)clearQuotaRoots;
@property BOOL compactWhenClosingMailboxes;
- (void)completeDeferredInitialization;
- (BOOL)connectAndAuthenticate:(id)arg1;
- (id)createMailboxWithParent:(id)arg1 displayName:(id)arg2 localizedDisplayName:(id)arg3;
- (id)dataSourceForMailbox:(id)arg1 createIfNeeded:(BOOL)arg2;
- (id)dataSourceForMailboxName:(id)arg1 createIfNeeded:(BOOL)arg2;
- (void)dealloc;
- (long long)defaultPortNumber;
- (long long)defaultSecurePortNumber;
- (BOOL)deleteMailbox:(id)arg1 reflectToServer:(BOOL)arg2;
- (void)detectAllMailMailboxWithConnection:(id)arg1;
- (void)didConnectToServerWithServerInterface:(id)arg1;
- (void)didSynchronizeMailboxCachesAndFoundChanges:(BOOL)arg1;
- (BOOL)discoverSettings;
- (void)doCommandBlockForMailbox:(id)arg1 synchronously:(BOOL)arg2 priority:(long long)arg3 description:(id)arg4 block:(id)arg5;
- (void)doRoutineCleanup;
- (void)expungeMailboxWithName:(id)arg1 URLStringToCompact:(id)arg2;
- (void)fetchAsynchronouslyIsAuto:(BOOL)arg1;
- (id)gmailLabelWithName:(id)arg1;
- (void)handleAlertResponse:(id)arg1;
- (void)handleOpenMailboxError:(id)arg1;
- (BOOL)handleResponseCodeFromResponse:(id)arg1;
@property BOOL hasServerDefinedAllMailMailbox;
@property BOOL hasServerDefinedArchiveMailbox;
@property BOOL hasServerDefinedDraftsMailbox;
@property BOOL hasServerDefinedJunkMailbox;
@property BOOL hasServerDefinedSentMailbox;
@property BOOL hasServerDefinedTrashMailbox;
@property(retain) MFLibraryIMAPStore *idleStore; // @synthesize idleStore=_idleStore;
@property BOOL ignoreServerDefinedArchiveMailbox;
@property BOOL ignoreServerDefinedDraftsMailbox;
@property BOOL ignoreServerDefinedJunkMailbox;
@property BOOL ignoreServerDefinedSentMailbox;
@property BOOL ignoreServerDefinedTrashMailbox;
- (id)init;
- (id)initWithSystemAccount:(id)arg1;
- (void)insertInMailboxes:(id)arg1 atIndex:(NSUInteger)arg2;
- (void)invalidateMailboxWithName:(id)arg1 expunge:(BOOL)arg2 URLStringToCompact:(id)arg3;
@property(nonatomic) BOOL lastConnectionFailed; // @synthesize lastConnectionFailed=_lastConnectionFailed;
@property(readonly, copy) NSArray *lastKnownCapabilities;
@property double lastMailboxListFetchTime; // @synthesize lastMailboxListFetchTime=_lastMailboxListFetchTime;
- (id)mailboxForName:(id)arg1;
- (id)mailboxForRelativePath:(id)arg1 isFilesystemPath:(BOOL)arg2 create:(BOOL)arg3;
- (id)mailboxPathExtension;
- (id)messageActionsAfterActionID:(long long)arg1;
- (unsigned int)messageCaching;
- (void)messageDeliveryWillBegin:(id)arg1;
- (id)nameForMailbox:(id)arg1;
- (BOOL)needToSynchronizeMailboxCaches;
@property BOOL needsGmailLabelsCleanup;
- (BOOL)needsServerMessages;
- (BOOL)needsToDiscoverSettings;
- (id)newConnectedConnectionDiscoveringBestSettings:(BOOL)arg1 withConnectTimeout:(double)arg2 readWriteTimeout:(double)arg3;
- (void)observeValueForKeyPath:(id)arg1 ofObject:(id)arg2 change:(id)arg3 context:(void *)arg4;
- (id)portNumberObject;
- (id)primaryMailbox;
- (id)quotaRootForName:(id)arg1 createIfNeeded:(BOOL)arg2;
- (void)refreshMailboxListingRootedAtMailbox:(id)arg1;
- (void)releaseAllConnections;
@property(readonly, nonatomic) NSOperationQueue *remoteFetchQueue; // @synthesize remoteFetchQueue=_remoteFetchQueue;
@property(readonly, nonatomic) NSOperationQueue *remoteTaskQueue; // @synthesize remoteTaskQueue=_remoteTaskQueue;
- (BOOL)renameMailbox:(id)arg1 newDisplayName:(id)arg2 parent:(id)arg3;
@property(readonly, nonatomic) BOOL requiresAuthentication;
- (void)resetNeedToSynchronizeMailboxCaches;
- (BOOL)resetSpecialMailboxes;
@property(readonly, copy, nonatomic) NSString *saslProfileName;
- (id)separatorCharFetchIfNeeded:(BOOL)arg1;
@property(readonly) MFMailbox *serverDefinedArchiveMailbox;
@property(readonly) MFMailbox *serverDefinedDraftsMailbox;
@property(readonly) MFMailbox *serverDefinedJunkMailbox;
@property(readonly) MFMailbox *serverDefinedSentMailbox;
@property(readonly) MFMailbox *serverDefinedTrashMailbox;
@property(copy) NSDictionary *serverID; // @synthesize serverID=_serverID;
@property(copy) NSString *serverPathPrefix;
- (void)setIsOffline:(BOOL)arg1;
- (void)setMessageCaching:(unsigned int)arg1;
- (void)setSeparatorChar:(id)arg1;
@property(nonatomic) BOOL shouldIncludePrefixInPath; // @synthesize shouldIncludePrefixInPath=_shouldIncludePrefixInPath;
@property BOOL shouldUseGmailLabelStores;
- (void)setStoreDraftsOnServer:(BOOL)arg1;
- (void)setStoreJunkOnServer:(BOOL)arg1;
- (void)setStoreSentMessagesOnServer:(BOOL)arg1;
- (void)setStoreTrashOnServer:(BOOL)arg1;
- (void)setSupportsModificationSequences:(BOOL)arg1 forMailboxName:(id)arg2;
@property BOOL supportsQuickResynchronization; // @synthesize supportsQuickResynchronization=_supportsQuickResynchronization;
- (BOOL)shouldFetch;
@property(readonly) BOOL shouldUseGmailLabelStoresIsSet;
- (Class)storeClassForMailbox:(id)arg1;
- (id)storeForMailbox:(id)arg1;
- (BOOL)storesUnseenCount;
@property(readonly) BOOL supportsIDLE;
- (void)syncFileSystemWithServerPathPrefix;
- (void)unselectConnectionForMailbox:(id)arg1;
- (id)usesSSLObject;
- (id)validNameForMailbox:(id)arg1 fromDisplayName:(id)arg2 error:(id *)arg3;
- (void)validateConnections;

// Remaining properties
@property(readonly, copy) NSString *accountTypeString;
@property BOOL allowInsecureAuthentication;
@property(readonly, copy) NSString *appleAuthenticationToken;
@property(readonly, copy) NSString *applePersonID;
@property(copy) NSString *authenticationScheme;
@property long long cachePolicy;
@property(copy) NSString *canonicalEmailAddress;
@property BOOL configureDynamically;
@property(retain) NSError *connectionError;
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
@property long long securityLayerType;
@property(readonly) BOOL shouldMoveDeletedMessagesToTrash;
@property BOOL shouldUseAuthentication;
@property(readonly, copy, nonatomic) NSArray *standardPorts;
@property(readonly, copy, nonatomic) NSArray *standardSSLPorts;
@property(readonly) Class superclass;
@property(readonly, nonatomic) IMAPTaskManager *taskManager; // @dynamic taskManager;
@property(copy) NSString *username;
@property BOOL usesSSL;

@end

