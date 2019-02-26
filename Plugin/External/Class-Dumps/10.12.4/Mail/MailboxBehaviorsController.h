//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


@class ACAccount, NSNumber;

@interface MailboxBehaviorsController : NSViewController
{
    BOOL _accountNeedsSaving;
}

+ (id)keyPathsForValuesAffectingAccountDeletesMessagesInPlace;
+ (id)keyPathsForValuesAffectingAccountNumberOfDaysToKeepJunk;
+ (id)keyPathsForValuesAffectingAccountNumberOfDaysToKeepTrash;
+ (id)keyPathsForValuesAffectingAccountStoresDraftsOnServer;
+ (id)keyPathsForValuesAffectingAccountStoresJunkOnServer;
+ (id)keyPathsForValuesAffectingAccountStoresSentMessagesOnServer;
+ (id)keyPathsForValuesAffectingAccountStoresTrashOnServer;
@property(retain, nonatomic) NSNumber *accountDeletesMessagesInPlace;
@property(nonatomic) BOOL accountNeedsSaving; // @synthesize accountNeedsSaving=_accountNeedsSaving;
@property(nonatomic) long long accountNumberOfDaysToKeepJunk;
@property(nonatomic) long long accountNumberOfDaysToKeepTrash;
@property(nonatomic) BOOL accountStoresDraftsOnServer;
@property(nonatomic) BOOL accountStoresJunkOnServer;
@property(nonatomic) BOOL accountStoresSentMessagesOnServer;
@property(nonatomic) BOOL accountStoresTrashOnServer;
@property(retain) ACAccount *representedObject;
- (id)title;

@end
