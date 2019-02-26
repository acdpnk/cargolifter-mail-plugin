//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


@class MFMailbox, MFMessageStore, NSArray, NSDictionary, NSMutableArray, NSMutableDictionary, NSSet;

@interface _TransferOperation : NSObject
{
    NSMutableArray *_sourceMessages;
    NSMutableArray *_documentIDs;
    id _messagesForGmailLabelsToRemoveLock;
    NSMutableDictionary *_messagesForGmailLabelsToRemove;
    BOOL _editableDocuments;
    MFMessageStore *_sourceStore;
    MFMailbox *_destinationMailbox;
    NSArray *_unreadSourceMessages;
    NSSet *_destinationLibraryIDs;
}

- (void)addMessage:(id)arg1 forLabelsToRemove:(id)arg2;
- (void)addSourceMessage:(id)arg1;
@property(retain) NSSet *destinationLibraryIDs; // @synthesize destinationLibraryIDs=_destinationLibraryIDs;
@property(readonly, nonatomic) MFMailbox *destinationMailbox; // @synthesize destinationMailbox=_destinationMailbox;
@property(readonly, nonatomic) NSArray *documentIDs; // @synthesize documentIDs=_documentIDs;
@property(readonly, nonatomic) BOOL editableDocuments; // @synthesize editableDocuments=_editableDocuments;
- (id)init;
- (id)initWithSourceStore:(id)arg1 destinationMailbox:(id)arg2 editableDocuments:(BOOL)arg3;
@property(readonly, copy) NSDictionary *messagesForGmailLabelsToRemove;
@property(readonly, copy) NSDictionary *popMessagesForGmailLabelsToRemove;
- (void)removeSourceMessages:(id)arg1;
@property(retain, nonatomic) NSArray *sourceMessages;
@property(retain) NSArray *unreadSourceMessages; // @synthesize unreadSourceMessages=_unreadSourceMessages;
@property(readonly) id <MCMessageDataSource> sourceLibraryStore;
@property(readonly, nonatomic) MFMessageStore *sourceStore; // @synthesize sourceStore=_sourceStore;

@end

