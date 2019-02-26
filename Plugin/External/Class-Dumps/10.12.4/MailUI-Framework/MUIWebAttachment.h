//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header



@class MCFileWrapper, NSImage, NSString, NSURL;

@interface MUIWebAttachment : NSObject <NSPasteboardReading, NSPasteboardWriting, NSSecureCoding>
{
    NSString *_inlineTagName;
    NSString *_mimeType;
    NSString *_uti;
    NSURL *_fileURL;
    MCFileWrapper *_fileWrapper;
    NSURL *_cidURL;
    NSString *_contentID;
    NSURL *_remoteURL;
}

+ (id)readableTypesForPasteboard:(id)arg1;
+ (BOOL)supportsSecureCoding;
- (id)_fileURLIfAvailable;
@property(retain, nonatomic) NSURL *cidURL; // @synthesize cidURL=_cidURL;
@property(copy, nonatomic) NSString *contentID; // @synthesize contentID=_contentID;
@property(readonly, nonatomic) __weak NSURL *downloadDirectory;
- (void)encodeWithCoder:(id)arg1;
@property(readonly, nonatomic) NSUInteger fileSize;
@property(readonly, nonatomic) NSURL *fileURL;
@property(readonly, nonatomic) MCFileWrapper *fileWrapper; // @synthesize fileWrapper=_fileWrapper;
@property(readonly, nonatomic) NSString *filename;
@property(readonly, nonatomic) NSString *filenameForSaving;
@property(readonly, nonatomic) NSImage *iconImage;
- (id)init;
- (id)initWithCoder:(id)arg1;
- (id)initWithFileWrapper:(id)arg1;
- (id)initWithPasteboardPropertyList:(id)arg1 ofType:(id)arg2;
@property(readonly, copy, nonatomic) NSString *inlineTagName;
@property(readonly, nonatomic) BOOL isAutoArchiveAttachment;
@property(readonly, nonatomic) BOOL isDataDownloaded;
@property(readonly, copy, nonatomic) NSString *mimeType;
@property(readonly, copy, nonatomic) NSString *mimeTypeForAttachmentTag;
- (id)pasteboardPropertyListForType:(id)arg1;
@property(retain, nonatomic) NSURL *remoteURL; // @synthesize remoteURL=_remoteURL;
@property(readonly, nonatomic) BOOL shouldAlwaysAutomaticallyDownload;
@property(readonly, copy, nonatomic) NSString *uti;
- (id)writableTypesForPasteboard:(id)arg1;

// Remaining properties
@property(readonly, copy) NSString *debugDescription;
@property(readonly, copy) NSString *description;
@property(readonly) NSUInteger hash;
@property(readonly) Class superclass;

@end
