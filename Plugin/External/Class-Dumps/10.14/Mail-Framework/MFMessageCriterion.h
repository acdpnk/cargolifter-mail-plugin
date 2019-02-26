//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header

#import <MFCriterion.h>

@class NSArray, NSString;

@interface MFMessageCriterion : MFCriterion
{
    NSString *_originalGroupUniqueID;
    long long _specialMailboxTypeCode;
    NSString *_groupUniqueID;
}

+ (void)_updateAddressDisplayNames:(id)arg1;
+ (long long)criterionTypeForString:(id)arg1;
+ (void)initialize;
+ (id)messagesInConversationCriterionWithConversationIDs:(id)arg1;
+ (id)stringForCriterionType:(long long)arg1;
- (BOOL)_containsCriterion:(long long)arg1;
- (BOOL)_doesGroup:(id)arg1 containSender:(id)arg2;
- (BOOL)_evaluateAccountCriterion:(id)arg1;
- (BOOL)_evaluateAddressBookCriterion:(id)arg1;
- (BOOL)_evaluateAddressHistoryCriterion:(id)arg1 successfullyEvaluated:(char *)arg2;
- (BOOL)_evaluateAttachmentCriterion:(id)arg1 fetchBody:(BOOL)arg2 needsBody:(char *)arg3;
- (BOOL)_evaluateAttachmentTypeCriterion:(id)arg1 fetchBody:(BOOL)arg2 needsBody:(char *)arg3;
- (BOOL)_evaluateBodyCriterion:(id)arg1 fetchBody:(BOOL)arg2 needsBody:(char *)arg3;
- (BOOL)_evaluateCompoundCriterion:(id)arg1;
- (BOOL)_evaluateDateCriterion:(id)arg1;
- (BOOL)_evaluateFlagCriterion:(id)arg1;
- (BOOL)_evaluateFlaggedStatusCriterion:(id)arg1;
- (BOOL)_evaluateFullNameCriterion:(id)arg1;
- (BOOL)_evaluateGmailLabelCriterion:(id)arg1;
- (BOOL)_evaluateHeaderCriterion:(id)arg1;
- (BOOL)_evaluateIsDigitallySignedCriterion:(id)arg1;
- (BOOL)_evaluateIsEncryptedCriterion:(id)arg1;
- (BOOL)_evaluateJunkMailCriterion:(id)arg1 fetchBody:(BOOL)arg2 needsBody:(char *)arg3;
- (BOOL)_evaluateJunkMailHeaders:(id)arg1;
- (BOOL)_evaluateMailboxCriterion:(id)arg1;
- (BOOL)_evaluateMemberOfGroupCriterion:(id)arg1;
- (BOOL)_evaluateMemberOfVIPSendersCriterion:(id)arg1;
- (BOOL)_evaluateMessage:(id)arg1 fetchBody:(BOOL)arg2 needsBody:(char *)arg3 successfullyEvaluated:(char *)arg4;
- (BOOL)_evaluateMessageTypeCriterion:(id)arg1;
- (BOOL)_evaluatePriorityIsHighCriterion:(id)arg1;
- (BOOL)_evaluatePriorityIsLowCriterion:(id)arg1;
- (BOOL)_evaluatePriorityIsNormalCriterion:(id)arg1;
- (BOOL)_evaluateSizeCriterion:(id)arg1;
- (BOOL)_evaluateSpecialMailboxCriterion:(id)arg1;
- (id)_headersRequiredForEvaluation;
- (BOOL)_mailboxURLString:(id)arg1 satisfiesQualifier:(long long)arg2 forExpression:(id)arg3;
- (BOOL)_messageHasPassBookAttachment:(id)arg1;
- (BOOL)_messageIsSignedByMe:(id)arg1;
- (void)addHeadersRequiredForRoutingToArray:(id)arg1;
- (BOOL)allowsEmptyExpression;
@property(readonly, nonatomic) BOOL containsAddressBookCriteria;
@property(readonly, nonatomic) BOOL containsIncludeConversationsCriterion;
@property(readonly, nonatomic) BOOL containsLastViewedDateCriterion;
@property(readonly, nonatomic) BOOL containsMessageIsNotInATrashMailboxCriterion;
@property(readonly, nonatomic) BOOL containsRelativeDateCriteria;
- (BOOL)containsSpotlightCriterion;
- (id)criterionByExpandingGroup;
@property(readonly, nonatomic) MFMessageCriterion *criterionByExpandingSpecialMailboxCriterion;
- (id)criterionByMergingSpotlightCriteria;
- (id)dictionaryRepresentationIncludePII:(BOOL)arg1;
- (BOOL)doesMessageSatisfyRuleEvaluationCriterion:(id)arg1 fetchBody:(BOOL)arg2 needsBody:(char *)arg3 successfullyEvaluated:(char *)arg4;
@property(readonly, copy, nonatomic) NSArray *emailAddressesForGroupCriterion;
@property(readonly, copy, nonatomic) NSArray *emailAddressesForVIPCriterion;
- (BOOL)evaluateMessage:(id)arg1;
- (id)fixOnceWithExpandedSmartMailboxes:(id)arg1 forSpotlight:(BOOL)arg2;
@property(copy) NSString *groupUniqueID; // @synthesize groupUniqueID=_groupUniqueID;
- (BOOL)hasExpression;
- (BOOL)hasNumberCriterion;
@property(readonly, nonatomic) BOOL hasQualifier;
- (NSUInteger)hash;
- (id)initWithDictionary:(id)arg1 andRemoveRecognizedKeysIfMutable:(BOOL)arg2;
- (BOOL)isEqual:(id)arg1;
- (BOOL)isEquivalent:(id)arg1;
- (BOOL)isExpressibleInTigerSchema;
- (BOOL)isSatisfiedByMailboxURL:(id)arg1;
- (BOOL)isValid:(id *)arg1 options:(unsigned int)arg2;
@property(readonly, copy) NSString *originalGroupUniqueID;
@property(readonly, copy, nonatomic) NSArray *recursiveGroupUniqueIDs;
- (id)ruleExpression;
- (id)ruleHeader;
- (unsigned int)ruleQualifier;
@property(nonatomic) unsigned int ruleType;
- (void)setCriterionIdentifier:(id)arg1;
- (void)setRuleExpression:(id)arg1;
- (void)setRuleHeader:(id)arg1;
- (void)setRuleQualifier:(unsigned int)arg1;
@property long long specialMailboxTypeCode; // @synthesize specialMailboxTypeCode=_specialMailboxTypeCode;

@end

