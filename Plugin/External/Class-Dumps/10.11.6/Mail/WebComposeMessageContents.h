//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


@class NSAttributedString, NSDictionary, NSMutableArray, NSString, NSURL;

@interface WebComposeMessageContents : NSObject
{
    BOOL _isMailDropPlaceholderMessage;
    long long _composeMode;
    NSAttributedString *_plainText;
    NSString *_topLevelHtmlString;
    NSMutableArray *_attachmentsAndHtmlStrings;
    NSMutableArray *_urlsForAttachmentsAndHtmlStrings;
    NSDictionary *_remoteAttachments;
    NSURL *_imageArchiveURL;
}

- (void)addAttachmentOrHtmlString:(id)arg1 withURL:(id)arg2;
@property(retain, nonatomic) NSMutableArray *attachmentsAndHtmlStrings; // @synthesize attachmentsAndHtmlStrings=_attachmentsAndHtmlStrings;
@property(nonatomic) long long composeMode; // @synthesize composeMode=_composeMode;
- (id)debugDescription;
@property(retain, nonatomic) NSURL *imageArchiveURL; // @synthesize imageArchiveURL=_imageArchiveURL;
@property(nonatomic) BOOL isMailDropPlaceholderMessage; // @synthesize isMailDropPlaceholderMessage=_isMailDropPlaceholderMessage;
@property(retain, nonatomic) NSAttributedString *plainText; // @synthesize plainText=_plainText;
@property(copy, nonatomic) NSDictionary *remoteAttachments; // @synthesize remoteAttachments=_remoteAttachments;
@property(retain, nonatomic) NSString *topLevelHtmlString; // @synthesize topLevelHtmlString=_topLevelHtmlString;
@property(retain, nonatomic) NSMutableArray *urlsForAttachmentsAndHtmlStrings; // @synthesize urlsForAttachmentsAndHtmlStrings=_urlsForAttachmentsAndHtmlStrings;

@end

