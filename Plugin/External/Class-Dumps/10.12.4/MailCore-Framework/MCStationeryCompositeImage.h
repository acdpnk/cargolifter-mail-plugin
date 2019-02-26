//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


@class MCFileWrapper, NSArray, NSData, NSImage, NSMutableArray, NSString, NSView<MCStationeryCompositeImageView>;

@interface MCStationeryCompositeImage : NSObject
{
    NSData *_baseImageData;
    NSData *_overlayImageData;
    NSMutableArray *_userImages;
    BOOL _isReadOnly;
    NSArray *_masks;
    NSView<MCStationeryCompositeImageView> *_view;
    NSString *_contentID;
    NSString *_preferredFilename;
    NSUInteger _index;
}

- (void)addUserImage:(id)arg1;
@property(readonly, nonatomic) long long approximateSize;
@property(readonly, copy, nonatomic) NSImage *baseImage;
@property(copy, nonatomic) NSString *contentID; // @synthesize contentID=_contentID;
@property(readonly, copy, nonatomic) NSData *data;
@property(readonly, copy, nonatomic) NSData *dataForCompositedImage;
@property(readonly, nonatomic) MCFileWrapper *fileWrapper;
@property(readonly, copy, nonatomic) NSString *filenameForCompositedImage;
@property(nonatomic) NSUInteger index; // @synthesize index=_index;
- (id)init;
- (id)initWithData:(id)arg1;
@property(readonly, nonatomic) BOOL isPlaceholder;
@property(nonatomic) BOOL isReadOnly; // @synthesize isReadOnly=_isReadOnly;
@property(readonly, nonatomic) BOOL isValid;
@property(copy, nonatomic) NSArray *masks; // @synthesize masks=_masks;
@property(readonly, copy, nonatomic) NSString *mimeTypeForCompositedImage;
@property(readonly, nonatomic) NSUInteger numberOfDropZones;
@property(readonly, copy, nonatomic) NSImage *overlayImage;
@property(copy, nonatomic) NSString *preferredFilename; // @synthesize preferredFilename=_preferredFilename;
- (void)setBaseImageData:(id)arg1;
- (void)setOverlayImageData:(id)arg1;
@property(nonatomic) __weak NSView<MCStationeryCompositeImageView> *view; // @synthesize view=_view;
@property(readonly, copy, nonatomic) NSArray *userImages;
@property(readonly, copy, nonatomic) NSArray *userImagesToSave;

@end
