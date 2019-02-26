//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header

#import "MCAggregateActivity.h"

#import "MFEWSMailboxDataCache.h"

@class MFEWSAccount, MFEWSBackgroundBodyFetchTask, MFEWSFolderHierarchyReconcileTask, MFEWSRetrievePersistedFolderDataTask, NSMutableDictionary, NSObject<OS_dispatch_queue>, NSString;

@interface MFEWSAccountSyncActivity : MCAggregateActivity <MFEWSMailboxDataCache>
{
    NSMutableDictionary *_mailboxSyncTasksByMailboxURLString;
    BOOL _userInitiated;
    id <MFEWSMailboxDataCache> _mailboxDataCache;
    MFEWSFolderHierarchyReconcileTask *_folderHierarchyReconcileTask;
    MFEWSRetrievePersistedFolderDataTask *_retrievePersistedFolderDataTask;
    MFEWSBackgroundBodyFetchTask *_backgroundBodyFetchTask;
    NSObject<OS_dispatch_queue> *_queue;
    MFEWSAccount *_account;
}

- (BOOL)_currentlySynchronizingMailboxContents;
- (void)_setUserInitiated:(BOOL)arg1;
@property(readonly, nonatomic) __weak MFEWSAccount *account; // @synthesize account=_account;
- (void)addMailboxesToReconcile:(id)arg1;
@property(retain, nonatomic) MFEWSBackgroundBodyFetchTask *backgroundBodyFetchTask; // @synthesize backgroundBodyFetchTask=_backgroundBodyFetchTask;
- (id)cachedFolderIDForMailboxURL:(id)arg1;
- (id)cachedSyncStateForMailboxURL:(id)arg1;
- (void)childActivityFinished:(id)arg1;
@property(readonly, nonatomic) BOOL currentlySynchronizingMailboxContents;
- (void)dataNotFoundForURL:(id)arg1;
@property(retain, nonatomic) MFEWSFolderHierarchyReconcileTask *folderHierarchyReconcileTask; // @synthesize folderHierarchyReconcileTask=_folderHierarchyReconcileTask;
- (id)init;
- (id)initWithAccount:(id)arg1;
@property(nonatomic) __weak id <MFEWSMailboxDataCache> mailboxDataCache; // @synthesize mailboxDataCache=_mailboxDataCache;
@property(readonly, nonatomic) NSObject<OS_dispatch_queue> *queue; // @synthesize queue=_queue;
- (void)recalculatePriorityForMailboxURLString:(id)arg1;
- (void)reconcileFolderHierarchyWithSyncState:(id)arg1;
@property(retain, nonatomic) MFEWSRetrievePersistedFolderDataTask *retrievePersistedFolderDataTask; // @synthesize retrievePersistedFolderDataTask=_retrievePersistedFolderDataTask;
@property(nonatomic) BOOL userInitiated;
- (id)syncTasksForMailboxURLString:(id)arg1;
- (void)updateCachedFolderID:(id)arg1 andSyncState:(id)arg2 forMailboxURL:(id)arg3;

// Remaining properties
@property(readonly, copy) NSString *debugDescription;
@property(readonly, copy) NSString *description;
@property(readonly) NSUInteger hash;
@property(readonly) Class superclass;

@end

