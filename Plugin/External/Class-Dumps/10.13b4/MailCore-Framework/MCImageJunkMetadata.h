//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


@interface MCImageJunkMetadata : NSObject
{
    NSUInteger _pixelCount;
    NSUInteger _byteCount;
    BOOL _isAnimated;
    long long _type;
    NSUInteger _frameCount;
    double _density;
    struct CGSize _size;
}

+ (id)lsmMarkerForImageDensityCategory:(long long)arg1;
+ (id)lsmMarkerForImageSizeCategory:(long long)arg1;
+ (id)stringForImageType:(long long)arg1;
- (void)_computeDensity;
@property(nonatomic) NSUInteger byteCount;
@property(nonatomic) double density; // @synthesize density=_density;
@property(readonly, nonatomic) long long densityCategory;
- (id)description;
@property(nonatomic) NSUInteger frameCount; // @synthesize frameCount=_frameCount;
- (id)init;
- (id)initWithImage:(id)arg1 name:(id)arg2 type:(long long)arg3;
@property(nonatomic) BOOL isAnimated; // @synthesize isAnimated=_isAnimated;
@property(nonatomic) NSUInteger pixelCount;
@property(nonatomic) struct CGSize size; // @synthesize size=_size;
@property(nonatomic) long long type; // @synthesize type=_type;
@property(readonly, nonatomic) long long sizeCategory;

@end

