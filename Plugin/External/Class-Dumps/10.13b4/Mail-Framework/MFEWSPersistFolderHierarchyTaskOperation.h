//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header

#import <MFEWSPersistenceTaskOperation.h>

@class MFEWSSyncFolderHierarchyBatch;

@interface MFEWSPersistFolderHierarchyTaskOperation : MFEWSPersistenceTaskOperation
{
    id <MFEWSPersistFolderHierarchyTaskOperationDelegate> _delegate;
    MFEWSSyncFolderHierarchyBatch *_batch;
}

@property(readonly, nonatomic) MFEWSSyncFolderHierarchyBatch *batch; // @synthesize batch=_batch;
@property __weak id <MFEWSPersistFolderHierarchyTaskOperationDelegate> delegate; // @synthesize delegate=_delegate;
- (id)init;
- (id)initWithBatch:(id)arg1;
- (void)main;

@end

