//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header

#import <MFEWSRequestOperation.h>

@class EWSSearchExpressionType, MFEWSFindItemsResponseOperation, NSArray;

@interface MFEWSFindItemsRequestOperation : MFEWSRequestOperation
{
    NSArray *_additionalProperties;
    NSArray *_EWSFolderIdStrings;
    EWSSearchExpressionType *_searchExpression;
}

@property(readonly, copy, nonatomic) NSArray *EWSFolderIdStrings; // @synthesize EWSFolderIdStrings=_EWSFolderIdStrings;
- (id)activityString;
@property(readonly, copy, nonatomic) NSArray *additionalProperties; // @synthesize additionalProperties=_additionalProperties;
- (id)initWithGateway:(id)arg1 errorHandler:(id)arg2;
- (id)initWithSearchExpression:(id)arg1 EWSFolderIdStrings:(id)arg2 additionalProperties:(id)arg3 gateway:(id)arg4;
- (id)newResponseOperationWithGateway:(id)arg1 errorHandler:(id)arg2;
- (id)prepareRequest;
@property(retain, nonatomic) MFEWSFindItemsResponseOperation *responseOperation;
@property(readonly, nonatomic) EWSSearchExpressionType *searchExpression; // @synthesize searchExpression=_searchExpression;

@end

