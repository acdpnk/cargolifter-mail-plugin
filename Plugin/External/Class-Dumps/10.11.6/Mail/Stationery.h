//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


@class MCParsedMessage, NSArray, NSBundle, NSDictionary, NSImage, NSMutableDictionary, NSString;

@interface Stationery : NSObject
{
    NSString *_html;
    NSMutableDictionary *_imageData;
    NSImage *_thumbnailImage;
    NSArray *_colors;
    NSString *_defaultColor;
    BOOL _isCustom;
    NSString *_uniqueIDForBaseURL;
    NSDictionary *_descriptionDictionary;
    NSDictionary *_localizedDescriptionDictionary;
    NSBundle *_bundle;
}

- (void)_addValueToDescription:(id)arg1 forKey:(id)arg2;
- (id)_attachmentsForImages:(id)arg1 typeIsBackground:(BOOL)arg2;
- (id)_html;
- (void)_loadColorsIfNeeded;
- (id)_localizeHtml:(id)arg1 withTable:(id)arg2;
- (id)addImageWithData:(id)arg1 name:(id)arg2;
- (id)backgroundImagePathsForColor:(id)arg1 previousColor:(id)arg2;
@property(readonly, copy, nonatomic) NSImage *backgroundTile;
@property(retain, nonatomic) NSBundle *bundle; // @synthesize bundle=_bundle;
@property(copy, nonatomic) NSString *bundlePath;
- (void)changeFolderAndDisplayNameTo:(id)arg1;
@property(readonly, copy, nonatomic) NSArray *colors;
@property(readonly, copy, nonatomic) NSString *defaultColor;
- (id)description;
@property(copy, nonatomic) NSDictionary *descriptionDictionary; // @synthesize descriptionDictionary=_descriptionDictionary;
@property(readonly, copy, nonatomic) NSString *displayName;
@property(readonly, copy, nonatomic) NSString *folderName;
- (id)fontsForColor:(id)arg1;
@property(readonly, nonatomic) BOOL hasImages;
- (NSUInteger)hash;
@property(readonly, copy, nonatomic) NSDictionary *headers;
- (id)imagePathsForColor:(id)arg1;
- (id)imagesInCompositeImagesForColor:(id)arg1;
- (id)init;
- (id)initWithPath:(id)arg1;
@property(readonly, nonatomic) BOOL isCustom; // @synthesize isCustom=_isCustom;
- (BOOL)isEqual:(id)arg1;
@property(readonly, nonatomic) double letterTopMargin;
@property(readonly, nonatomic) double letterWidth;
@property(readonly, copy, nonatomic) NSDictionary *localizedDescriptionDictionary; // @synthesize localizedDescriptionDictionary=_localizedDescriptionDictionary;
- (id)nextColorAfterColor:(id)arg1;
@property(readonly, nonatomic) MCParsedMessage *parsedMessage;
@property(readonly, copy, nonatomic) NSString *pathToBackgroundTile;
- (BOOL)saveToPath:(id)arg1 error:(id *)arg2;
- (void)setHTML:(id)arg1;
- (void)setMinimumWidth:(double)arg1;
- (void)setStationeryName:(id)arg1;
- (id)setThumbnailImage:(id)arg1;
@property(copy, nonatomic) NSString *uniqueIDForBaseURL; // @synthesize uniqueIDForBaseURL=_uniqueIDForBaseURL;
@property(nonatomic) BOOL userCreatedCustomStationery;
- (void)setValue:(id)arg1 forHeader:(id)arg2;
@property(readonly, copy, nonatomic) NSString *stationeryID;
- (id)thumbnailImage;
@property(readonly, copy, nonatomic) NSString *thumbnailImagePath;

@end

