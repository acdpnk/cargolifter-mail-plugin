//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header

#import <MFEWSResponseOperation.h>

@class EWSSyncFolderHierarchyResponseType;

@interface MFEWSSyncFolderHierarchyResponseOperation : MFEWSResponseOperation
{
    id _createBlock;
    id _updateBlock;
    id _deleteBlock;
}

@property(copy, nonatomic) id createBlock; // @synthesize createBlock=_createBlock;
@property(copy, nonatomic) id deleteBlock; // @synthesize deleteBlock=_deleteBlock;
- (void)executeOperation;
- (void)prepareToExecuteWithResponse:(id)arg1 forRequestOperation:(id)arg2;
@property(retain) EWSSyncFolderHierarchyResponseType *response;
@property(copy, nonatomic) id updateBlock; // @synthesize updateBlock=_updateBlock;

@end

