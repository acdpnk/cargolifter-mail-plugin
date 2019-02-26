//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header

#import <MFEWSRequestOperation.h>


@class NSArray, NSString;

@interface MFEWSDeleteItemsRequestOperation : MFEWSRequestOperation <NSSecureCoding>
{
    NSArray *_EWSItemIds;
    NSString *_folderIdString;
}

+ (BOOL)supportsSecureCoding;
@property(readonly, copy, nonatomic) NSArray *EWSItemIds; // @synthesize EWSItemIds=_EWSItemIds;
- (void)_ewsDeleteItemsRequestOperationCommonInitWithEWSItemIds:(id)arg1 folderIdString:(id)arg2;
- (id)activityString;
- (void)encodeWithCoder:(id)arg1;
@property(readonly, copy, nonatomic) NSString *folderIdString; // @synthesize folderIdString=_folderIdString;
- (id)initWithCoder:(id)arg1;
- (id)initWithEWSItemIds:(id)arg1 folderIdString:(id)arg2 gateway:(id)arg3;
- (id)initWithGateway:(id)arg1 errorHandler:(id)arg2;
- (id)prepareRequest;
- (void)setupOfflineResponse;

@end

