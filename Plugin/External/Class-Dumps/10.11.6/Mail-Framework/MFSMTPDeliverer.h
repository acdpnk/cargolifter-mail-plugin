//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header

#import <MFMessageDeliverer.h>

@class MFSMTPAccount;

@interface MFSMTPDeliverer : MFMessageDeliverer
{
}

@property(retain, nonatomic) MFSMTPAccount *account;
- (long long)deliverMessageHeaderData:(id)arg1 bodyData:(id)arg2 toRecipients:(id)arg3;

@end

