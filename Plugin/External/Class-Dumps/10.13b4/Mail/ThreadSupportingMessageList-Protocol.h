//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header

#import "MessageList.h"

@class NSArray;

@protocol ThreadSupportingMessageList <MessageList>
- (void)closeAllThreads;
- (void)closeThreads:(NSArray *)arg1;
@property(readonly, nonatomic) __weak id <ThreadedMessageListDelegate> delegate;
- (void)openAllThreads;
- (void)openThreads:(NSArray *)arg1;
@end

