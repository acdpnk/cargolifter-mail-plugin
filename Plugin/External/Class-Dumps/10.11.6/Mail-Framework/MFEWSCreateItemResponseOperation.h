//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header

#import <MFEWSResponseOperation.h>

@class EWSCreateItemResponseType, NSString;

@interface MFEWSCreateItemResponseOperation : MFEWSResponseOperation
{
    NSString *_itemId;
}

- (void)executeOperation;
@property(copy) NSString *itemId; // @synthesize itemId=_itemId;
- (void)prepareToExecuteWithResponse:(id)arg1 forRequestOperation:(id)arg2;
@property(retain) EWSCreateItemResponseType *response;

@end

