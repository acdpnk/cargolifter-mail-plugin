//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


@class NSBitmapImageRep, NSData;

@interface NSImage (MailCoreAdditions)
+ (id)imageDataForType:(id *)arg1 fromPasteboard:(id)arg2;
+ (id)imagePasteboardTypesWithPreferenceToPNG;
+ (id)rotateImage:(id)arg1 byDegrees:(double)arg2;
@property(readonly, copy, nonatomic) NSData *PNGData;
@property(readonly, nonatomic) NSBitmapImageRep *bitmapImageRep;
- (void)drawTransformedInRect:(struct CGRect)arg1 fromRect:(struct CGRect)arg2 operation:(NSUInteger)arg3 fraction:(double)arg4 flip:(BOOL)arg5;
@property(readonly, nonatomic) NSUInteger frameCount;
@property(readonly, nonatomic) BOOL isAnimated;
@property(readonly, nonatomic) NSImage *opaqueImage;
@property(readonly, nonatomic) double pixelsHigh;
@property(readonly, nonatomic) double pixelsWide;
@end
