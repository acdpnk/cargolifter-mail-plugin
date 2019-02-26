//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header



@class NSArray, NSAttributedString, NSDictionary, NSString, NSURL;

@interface MCParsedMessage : NSObject <NSXMLParserDelegate>
{
    BOOL _isPlainText;
    NSString *_html;
    NSString *_mimeType;
    NSURL *_baseURL;
    NSDictionary *_attachmentsByURL;
    NSArray *_stationeryBackgroundImageURLs;
}

+ (id)parsedMessageWithWebArchive:(id)arg1 archiveIsMailInternal:(BOOL)arg2;
- (void)_addWebArchiveDataToArray:(id)arg1;
- (void)_mcParsedMessageCommonInit;
- (void)addAttachment:(id)arg1 forURL:(id)arg2;
@property(copy, nonatomic) NSDictionary *attachmentsByURL; // @synthesize attachmentsByURL=_attachmentsByURL;
@property(readonly, copy, nonatomic) NSAttributedString *attributedString;
@property(retain, nonatomic) NSURL *baseURL; // @synthesize baseURL=_baseURL;
@property(readonly, copy) NSString *debugDescription;
@property(readonly, copy) NSString *description;
@property(copy, nonatomic) NSString *html; // @synthesize html=_html;
- (id)init;
- (id)initWithWebArchive:(id)arg1;
- (id)initWithWebArchive:(id)arg1 archiveIsMailInternal:(BOOL)arg2;
@property(nonatomic) BOOL isPlainText; // @synthesize isPlainText=_isPlainText;
@property(copy, nonatomic) NSString *mimeType; // @synthesize mimeType=_mimeType;
- (void)setBaseURLFromHtml;
@property(copy, nonatomic) NSArray *stationeryBackgroundImageURLs; // @synthesize stationeryBackgroundImageURLs=_stationeryBackgroundImageURLs;

// Remaining properties
@property(readonly) NSUInteger hash;
@property(readonly) Class superclass;

@end
