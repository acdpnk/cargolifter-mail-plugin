//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header

#import "MCTask.h"

#import "MFEWSFetchMessageMetadataOperationDelegate-Protocol.h"
#import "MFEWSMailboxReconcileTaskOperationDelegate-Protocol.h"
#import "MFEWSPersistMessageMetadataOperationDelegate-Protocol.h"
#import "MFEWSMailboxDataCache-Protocol.h"

@class MFEWSDeleteMailboxTaskOperation, MFEWSMailboxReconcileTaskOperation, MFEWSPersistMessageMetadataOperation, NSMutableArray, NSMutableDictionary, NSMutableSet, NSProgress, NSString;

@interface MFEWSMailboxSyncTask : MCTask <MFEWSMailboxReconcileTaskOperationDelegate, MFEWSFetchMessageMetadataOperationDelegate, MFEWSPersistMessageMetadataOperationDelegate>
{
    MFEWSMailboxReconcileTaskOperation *_reconcileOperation;
    MFEWSPersistMessageMetadataOperation *_persistMetadataOperation;
    NSMutableArray *_batchesNeedingFetch;
    NSMutableSet *_currentFetchOperations;
    NSMutableDictionary *_batchesToPersistByInitialSyncState;
    BOOL _userInitiated;
    BOOL _needsDelete;
    BOOL _isPrimaryMailbox;
    BOOL _foundNewUnreadInboxMessage;
    NSString *_folderIDString;
    NSString *_mailboxURL;
    id <MFEWSMailboxDataCache> _mailboxDataCache;
    NSString *_syncStateToReconcile;
    NSString *_syncStateToPersist;
    MFEWSDeleteMailboxTaskOperation *_deleteMailboxOperation;
    NSProgress *_checkProgress;
}

- (void)_addFetchOperation:(id)arg1;
- (void)_finishCheckingForMailProgress;
- (void)_incrementFoundMessages:(NSUInteger)arg1;
- (void)_removeFetchOperation:(id)arg1;
- (void)_setFoundNewUnreadMessageInInbox;
@property(readonly, nonatomic) NSProgress *checkProgress; // @synthesize checkProgress=_checkProgress;
@property(retain, nonatomic) MFEWSDeleteMailboxTaskOperation *deleteMailboxOperation; // @synthesize deleteMailboxOperation=_deleteMailboxOperation;
- (void)end;
- (void)fetchMessageMetadataOperation:(id)arg1 didPopulateBatch:(id)arg2;
@property(copy, nonatomic) NSString *folderIDString; // @synthesize folderIDString=_folderIDString;
@property(nonatomic) BOOL foundNewUnreadInboxMessage; // @synthesize foundNewUnreadInboxMessage=_foundNewUnreadInboxMessage;
- (id)init;
- (id)initWithMailboxURL:(id)arg1;
@property(nonatomic) BOOL isPrimaryMailbox; // @synthesize isPrimaryMailbox=_isPrimaryMailbox;
@property(nonatomic) __weak id <MFEWSMailboxDataCache> mailboxDataCache; // @synthesize mailboxDataCache=_mailboxDataCache;
- (void)mailboxReconcileTaskOperation:(id)arg1 receivedBatch:(id)arg2;
- (void)mailboxReconcileTaskOperationFolderIsInvalid:(id)arg1;
@property(readonly, copy, nonatomic) NSString *mailboxURL; // @synthesize mailboxURL=_mailboxURL;
@property(nonatomic) BOOL needsDelete; // @synthesize needsDelete=_needsDelete;
- (id)nextNetworkOperation;
- (id)nextPersistenceOperation;
- (void)operationFinished:(id)arg1;
- (void)persistMessageMetadataOperation:(id)arg1 didPersistBatch:(id)arg2;
@property(retain, nonatomic) MFEWSPersistMessageMetadataOperation *persistMetadataOperation;
- (void)recalculatePriorities;
- (void)reconcileMailboxWithSyncState:(id)arg1;
@property(retain, nonatomic) MFEWSMailboxReconcileTaskOperation *reconcileOperation;
@property(copy, nonatomic) NSString *syncStateToPersist; // @synthesize syncStateToPersist=_syncStateToPersist;
@property(copy, nonatomic) NSString *syncStateToReconcile; // @synthesize syncStateToReconcile=_syncStateToReconcile;
@property(nonatomic) BOOL userInitiated;

// Remaining properties
@property(readonly, copy) NSString *debugDescription;
@property(readonly, copy) NSString *description;
@property(readonly) NSUInteger hash;
@property(readonly) Class superclass;

@end

