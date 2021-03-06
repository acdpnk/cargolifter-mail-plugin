//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


#import "ECMessage-Protocol.h"
#import "MCMessageSortingInterface-Protocol.h"
#import "MCMessageDataSource-Protocol.h"

@class MCDisplayNameInfo, MCMimePart, NSArray, NSColor, NSData, NSDate, NSMutableSet, NSSet, NSString, NSUUID;

@interface MCMessage : NSObject <MCMessageSortingInterface, ECMessage>
{
    NSString *_subject;
    NSArray *_toRecipients;
    NSArray *_ccRecipients;
    NSString *_sender;
    NSData *_messageIDHeaderDigest;
    NSData *_inReplyToHeaderDigest;
    NSUUID *_documentID;
    BOOL _type;
    double _dateSentInterval;
    double _dateReceivedInterval;
    double _dateLastViewedInterval;
    id <MCMessageDataSource> _dataSource;
    // Error parsing type: Aq, name: _messageFlags
    unsigned char _subjectPrefixLength;
    NSMutableSet *_gmailLabels;
    BOOL _markedForOverwrite;
    BOOL _recipientType;
    BOOL _primitiveMessageType;
    long long _conversationID;
    double _primitiveDateSentInterval;
    double _primitiveDateReceivedInterval;
    double _primitiveDateLastViewedInterval;
}

+ (BOOL)_messageTypeForMessageTypeKey:(id)arg1;
+ (id)_subjectTruncatedToMaximumAllowableSize:(id)arg1 prefixLength:(unsigned char)arg2;
+ (BOOL)allMessages:(id)arg1 areSameType:(BOOL)arg2;
+ (long long)displayablePriorityForPriority:(long long)arg1;
+ (id)forwardedMessagePrefixWithSpacer:(BOOL)arg1;
+ (void)initialize;
+ (BOOL)isMessageURLString:(id)arg1;
+ (id)messageTypeKeyForMessageType:(BOOL)arg1;
+ (id)messageWithRFC822Data:(id)arg1 sanitizeData:(BOOL)arg2;
+ (id)replyPrefixWithSpacer:(BOOL)arg1;
+ (unsigned char)subjectPrefixLengthUnknown;
+ (id)subjectTruncatedToMaximumAllowableSize:(id)arg1;
+ (id)unreadMessagesFromMessages:(id)arg1;
+ (long long)validatePriority:(long long)arg1;
@property(readonly, copy, nonatomic) NSString *URLString;
@property(readonly, copy, nonatomic) NSString *URLStringIfAvailable;
- (id)URLStringWithHeaders:(id)arg1;
- (id)_URLStringWithHeaders:(id)arg1 fetchIfNotAvailable:(BOOL)arg2;
- (BOOL)_calculateAttachmentInfoFromTopLevelMimePart:(id)arg1 numberOfAttachments:(unsigned int *)arg2 isSigned:(char *)arg3 isEncrypted:(char *)arg4 force:(BOOL)arg5;
- (id)_searchableItemWithHTML:(id)arg1 messageBody:(id)arg2 updatableAttributesOnly:(BOOL)arg3 outOrderedAttachments:(id *)arg4;
- (void)_setDateReceivedFromHeaders:(id)arg1;
- (void)_setDateSentFromHeaders:(id)arg1;
- (void)_setSubject:(id)arg1 prefixLength:(unsigned char)arg2;
- (id)_uniqueIdentifierForSearchableItemUsingIdentifier:(id)arg1 useHeadersIfNecessary:(BOOL)arg2;
- (void)_updateAttributeSet:(id)arg1 includingHTML:(BOOL)arg2 withMessageBody:(id)arg3 orderedAttachments:(id *)arg4;
@property(readonly, nonatomic) id account;
- (void)addGmailLabels:(id)arg1;
@property(readonly) BOOL answered;
- (id)bodyDataFetchIfNotAvailable:(BOOL)arg1 allowPartial:(BOOL)arg2;
- (id)bodyFetchIfNotAvailable:(BOOL)arg1 updateFlags:(BOOL)arg2 allowPartial:(BOOL)arg3;
- (BOOL)calculateAttachmentInfoFromTopLevelMimePart:(id)arg1 numberOfAttachments:(unsigned int *)arg2 isSigned:(char *)arg3 isEncrypted:(char *)arg4;
@property(copy) NSArray *cc;
@property(copy) NSColor *color;
@property(readonly, nonatomic) int colorForSort;
@property BOOL colorHasBeenEvaluated;
@property(readonly, nonatomic) int colorIntValue;
@property(readonly) long long conversationID; // @synthesize conversationID=_conversationID;
@property(readonly) BOOL conversationMuted;
@property(readonly) BOOL conversationVIP;
- (id)copyWithZone:(struct _NSZone *)arg1;
- (id)dataSource;
@property(readonly, nonatomic) BOOL dataSourceShouldBeSet;
@property(readonly) NSDate *dateLastViewed;
@property double dateLastViewedAsTimeIntervalSince1970;
@property(readonly) NSDate *dateReceived;
@property double dateReceivedAsTimeIntervalSince1970;
@property(readonly) NSDate *dateSent;
@property double dateSentAsTimeIntervalSince1970;
@property(readonly, copy) NSString *debugDescription;
@property(readonly, copy) NSString *description;
@property(copy) NSUUID *documentID;
@property(readonly, nonatomic) unsigned char flagColorSet;
@property(readonly) BOOL flagged;
@property(readonly, copy) NSArray *from;
@property(retain) NSSet *gmailLabels;
@property(readonly, nonatomic) BOOL hasAttachments;
@property(readonly, nonatomic) BOOL hasCalculatedNumberOfAttachments;
- (id)headerDataFetchIfNotAvailable:(BOOL)arg1 allowPartial:(BOOL)arg2;
- (id)headersFetchIfNotAvailable:(BOOL)arg1;
- (id)imageArchiveURL;
@property(copy) NSData *inReplyToHeaderDigest;
- (id)init;
@property(readonly, nonatomic) BOOL isEditable;
@property(readonly, nonatomic) BOOL isMessageContentLocallyAvailable;
@property(readonly, nonatomic) BOOL isMessageMeeting;
@property(readonly, nonatomic) BOOL isPartialMessageBodyAvailable;
@property(readonly, nonatomic) BOOL isReply;
@property(readonly) BOOL junk;
@property(readonly, nonatomic) long long junkMailLevel;
@property(readonly, copy) NSArray *listUnsubscribe;
- (void)loadCachedHeaderValuesFromHeaders:(id)arg1 type:(BOOL)arg2;
@property(readonly, nonatomic) id mailbox;
@property BOOL markedForOverwrite; // @synthesize markedForOverwrite=_markedForOverwrite;
@property(readonly, nonatomic) id messageBody;
- (id)messageDataFetchIfNotAvailable:(BOOL)arg1 newDocumentID:(id)arg2;
@property(readonly, nonatomic) long long messageFlags;
@property(readonly, copy, nonatomic) NSString *messageID;
@property(readonly, copy) NSData *messageIDHeaderDigest;
@property(readonly, nonatomic) NSUInteger messageSize;
@property(readonly, nonatomic) NSUInteger numberOfAttachments;
@property(readonly, copy, nonatomic) NSString *path;
@property(readonly, copy, nonatomic) NSString *persistentID;
@property(readonly, nonatomic) __weak id <MCMessageDataSource> primitiveDataSource;
@property double primitiveDateLastViewedInterval; // @synthesize primitiveDateLastViewedInterval=_primitiveDateLastViewedInterval;
@property double primitiveDateReceivedInterval; // @synthesize primitiveDateReceivedInterval=_primitiveDateReceivedInterval;
@property double primitiveDateSentInterval; // @synthesize primitiveDateSentInterval=_primitiveDateSentInterval;
@property(readonly, nonatomic) long long primitiveMessageFlags;
@property BOOL primitiveMessageType; // @synthesize primitiveMessageType=_primitiveMessageType;
@property(readonly, nonatomic) long long priority;
@property(readonly, copy) NSData *rawInReplyToHeaderDigest;
@property(readonly, copy) NSData *rawMessageIDHeaderDigest;
- (id)rawSourceFromHeaders:(id)arg1 body:(id)arg2;
@property BOOL recipientType; // @synthesize recipientType=_recipientType;
@property(readonly, copy) NSArray *references;
@property(readonly, copy) NSString *remoteID;
@property(readonly, copy, nonatomic) NSString *remoteMailboxURLString;
- (void)removeGmailLabels:(id)arg1;
- (id)searchableItemWithHTML:(id)arg1 messageBody:(id)arg2 updatableAttributesOnly:(BOOL)arg3;
@property(copy) NSString *sender;
@property(readonly, copy, nonatomic) NSString *senderDisplayName;
@property(readonly, nonatomic) MCDisplayNameInfo *senderDisplayNameInfo;
@property(readonly, copy) NSString *senderIfAvailable;
@property(readonly) BOOL senderVIP;
- (void)setAttachmentFilenames:(id)arg1;
- (void)setAttachmentInfoFromTopLevelMimePart:(id)arg1;
- (void)setColor:(id)arg1 hasBeenEvaluated:(BOOL)arg2 flags:(long long)arg3 mask:(long long)arg4;
- (void)setDataSource:(id)arg1;
- (void)setMessageFlags:(long long)arg1 mask:(long long)arg2;
- (void)setMessageIDHeaderDigest:(id)arg1;
- (void)setMessageInfo:(id)arg1 subjectPrefixLength:(unsigned char)arg2 to:(id)arg3 cc:(id)arg4 sender:(id)arg5 type:(BOOL)arg6 dateReceivedTimeIntervalSince1970:(double)arg7 dateSentTimeIntervalSince1970:(double)arg8 messageIDHeaderDigest:(id)arg9 inReplyToHeaderDigest:(id)arg10 dateLastViewedTimeIntervalSince1970:(double)arg11;
- (void)setNumberOfAttachments:(unsigned int)arg1 isSigned:(BOOL)arg2 isEncrypted:(BOOL)arg3;
- (void)setPrimitiveColor:(id)arg1;
- (void)setPrimitiveColor:(id)arg1 hasBeenEvaluated:(BOOL)arg2 flags:(long long)arg3 mask:(long long)arg4;
- (void)setPrimitiveColorHasBeenEvaluated:(BOOL)arg1;
- (void)setPrimitiveColorIntValue:(int)arg1;
- (void)setPrimitiveMessageFlags:(long long)arg1 mask:(long long)arg2;
- (void)setPriorityFromHeaders:(id)arg1;
@property(copy) NSString *subject;
- (void)setSubject:(id)arg1 prefixLength:(NSUInteger)arg2;
@property(copy) NSArray *to;
@property BOOL type;
@property(readonly, nonatomic) BOOL shouldDeferBodyDownload;
@property(readonly, copy) NSString *subjectIfAvailable;
@property(readonly, copy, nonatomic) NSString *subjectNotIncludingReAndFwdPrefix;
@property(readonly) NSUInteger subjectPrefixLength;
@property(readonly, nonatomic) MCMimePart *topLevelMimePart;
@property(readonly, nonatomic) unsigned int uid;
@property(readonly, nonatomic) NSString *uniqueIdentifierForSearchableItem;
- (void)unlockedSetInReplyToHeaderDigest:(id)arg1;
- (void)unlockedSetMessageIDHeaderDigest:(id)arg1;

// Remaining properties
@property(readonly) NSUInteger hash;
@property(readonly) Class superclass;

@end

