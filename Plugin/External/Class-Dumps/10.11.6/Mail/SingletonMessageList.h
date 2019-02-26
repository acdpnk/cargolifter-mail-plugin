//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


#import "MessageList.h"

@class NSMutableArray, NSMutableDictionary, NSString;

@interface SingletonMessageList : NSObject <MessageList>
{
    NSMutableArray *_filteredMessages;
    NSMutableDictionary *_messageSortValues;
    id <MessageListDelegate> _delegate;
    id _comparator;
}

- (NSUInteger)_insertObjectIfAbsent:(id)arg1 intoArray:(id)arg2 inSortedRange:(struct _NSRange)arg3 usingComparator:(id)arg4 didInsert:(char *)arg5;
- (id)_newSortComparator;
- (id)_refreshedMessageSortValues;
- (NSUInteger)_removeMessage:(id)arg1 inSortedRange:(struct _NSRange)arg2 didRemove:(char *)arg3;
- (NSUInteger)_removeObjectIfPresent:(id)arg1 fromArray:(id)arg2 inSortedRange:(struct _NSRange)arg3 usingComparator:(id)arg4 didRemove:(char *)arg5;
- (NSUInteger)adjustedIndexOfMessage:(id)arg1;
@property(copy, nonatomic) id comparator; // @synthesize comparator=_comparator;
- (id)copyOfFilteredMessages;
@property(readonly, nonatomic) __weak id <MessageListDelegate> delegate; // @synthesize delegate=_delegate;
- (void)enumerateFilteredMessagesUsingBlock:(id)arg1;
- (id)filterInMessages:(id)arg1 secondaryMessages:(id)arg2;
- (id)filterOutMessages:(id)arg1 andReplaceMessages:(id)arg2;
- (id)filteredMessageAtIndex:(NSUInteger)arg1;
- (id)filteredMessagesAtIndexes:(id)arg1;
- (NSUInteger)filteredMessagesCount;
- (NSUInteger)indexOfFilteredMessage:(id)arg1;
- (id)init;
- (id)initWithDelegate:(id)arg1;
- (void)invert;
- (NSUInteger)mergeMessage:(id)arg1;
- (id)mergeMessages:(id)arg1;
- (id)mutableCopyOfFilteredMessages;
- (NSUInteger)removeMessage:(id)arg1;
- (id)removeMessages:(id)arg1;
- (void)resort;
- (void)updateMessages:(id)arg1;

// Remaining properties
@property(readonly, copy) NSString *debugDescription;
@property(readonly, copy) NSString *description;
@property(readonly) NSUInteger hash;
@property(readonly) Class superclass;

@end
