//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


@interface MailSearchCriteriaHelper : NSObject
{
}

+ (id)_mailboxSearchCriterionForMailboxes:(id)arg1;
+ (id)compoundCriterionWithCriterion:(id)arg1 andAnyDateMatchingQuery:(id)arg2;
+ (id)criterionForAttachmentNameContainsString:(id)arg1;
+ (id)criterionForAttachmentNameContainsSuggestion:(id)arg1 forSavedSearch:(BOOL)arg2;
+ (id)criterionForDateSuggestion:(id)arg1;
+ (id)criterionForDateWithin:(id)arg1 and:(id)arg2 withType:(long long)arg3;
+ (id)criterionForMailFlagColorSuggestion:(id)arg1;
+ (id)criterionForMailStatusSuggestion:(id)arg1;
+ (id)criterionForMailboxSuggestion:(id)arg1 forSavedSearch:(BOOL)arg2;
+ (id)criterionForMessageHasAttachment;
+ (id)criterionForPrioritySuggestion:(id)arg1;
+ (id)criterionForSuggestion:(id)arg1 forSavedSearch:(BOOL)arg2;
+ (id)criterionForSuggestions:(id)arg1 scope:(long long)arg2 inMessageMall:(id)arg3 shouldShowRecipient:(char *)arg4;
+ (id)mailboxSearchCriterionForScope:(long long)arg1 inMessageMall:(id)arg2 shouldShowRecipient:(char *)arg3;
+ (id)textSearchCriterionForSearchField:(long long)arg1 queryString:(id)arg2 includeDateTextualRepresentations:(BOOL)arg3 exactMatch:(BOOL)arg4;

@end

