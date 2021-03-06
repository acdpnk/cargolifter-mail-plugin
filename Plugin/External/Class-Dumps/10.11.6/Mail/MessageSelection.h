//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


@class MCMessage, NSArray, NSDictionary;

@interface MessageSelection : NSObject
{
    MCMessage *_initialMessage;
    NSArray *_conversations;
    NSDictionary *_focusedMessagesByConversation;
    NSDictionary *_selectedMessagesForConversation;
    NSArray *_messages;
}

- (void)_messageSelectionCommonInitWithInitialMessage:(id)arg1 conversations:(id)arg2 focusedMessagesByConversation:(id)arg3 selectedMessagesByConversation:(id)arg4 messages:(id)arg5;
@property(readonly, copy, nonatomic) NSArray *conversations; // @synthesize conversations=_conversations;
- (id)description;
@property(readonly, copy, nonatomic) NSDictionary *focusedMessagesByConversation; // @synthesize focusedMessagesByConversation=_focusedMessagesByConversation;
- (NSUInteger)hash;
- (id)init;
- (id)initWithInitialMessage:(id)arg1 conversations:(id)arg2 focusedMessagesByConversation:(id)arg3 messages:(id)arg4;
- (id)initWithInitialMessage:(id)arg1 conversations:(id)arg2 selectedMessagesByConversation:(id)arg3 messages:(id)arg4;
@property(readonly, nonatomic) MCMessage *initialMessage; // @synthesize initialMessage=_initialMessage;
- (BOOL)isEqual:(id)arg1;
@property(readonly, copy, nonatomic) NSArray *messages; // @synthesize messages=_messages;
@property(readonly, copy, nonatomic) NSDictionary *selectedMessagesByConversation; // @synthesize selectedMessagesByConversation=_selectedMessagesForConversation;

@end

