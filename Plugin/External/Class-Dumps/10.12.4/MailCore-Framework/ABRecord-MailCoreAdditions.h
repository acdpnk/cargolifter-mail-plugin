//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header

#import "ABRecord.h"

@class NSArray, NSString;

@interface ABRecord (MailCoreAdditions)
- (id)_fullName;
@property(readonly, copy, nonatomic) NSArray *allEmailAddresses;
@property(readonly, copy, nonatomic) NSString *compoundName;
@property(readonly, copy, nonatomic) NSString *compoundNameAndEmail;
- (id)compoundNameAndEmailForEmail:(id)arg1;
@property(readonly, copy, nonatomic) NSString *email;
@property(readonly, copy, nonatomic) NSString *extension;
@property(readonly, copy, nonatomic) NSString *firstName;
- (long long)fullNameCompare:(id)arg1;
@property(readonly, nonatomic) BOOL isGroup;
@property(readonly, copy, nonatomic) NSString *lastName;
@property(readonly, copy, nonatomic) NSString *middleName;
@property(readonly, copy, nonatomic) NSString *nickname;
@end

