//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header

#import "CALayer.h"

@interface MailWindowShadowLayer : CALayer
{
    CALayer *_topShadow;
    CALayer *_bottomShadow;
    CALayer *_leftShadow;
    CALayer *_rightShadow;
    CALayer *_topRightShadow;
    CALayer *_topLeftShadow;
    CALayer *_bottomRightShadow;
    CALayer *_bottomLeftShadow;
    long long _shadowType;
    struct CGSize _animationStartSize;
    struct CGSize _animationEndSize;
}

- (double)_bottomMargin;
- (double)_leftMargin;
- (double)_rightMargin;
- (id)_shadowImageForShadowPart:(long long)arg1;
- (double)_topMargin;
- (void)animateShadowByGrowing:(BOOL)arg1;
@property(readonly, nonatomic) struct CGSize animationEndSize; // @synthesize animationEndSize=_animationEndSize;
@property(readonly, nonatomic) struct CGSize animationStartSize; // @synthesize animationStartSize=_animationStartSize;
@property(readonly, nonatomic) CALayer *bottomLeftShadow; // @synthesize bottomLeftShadow=_bottomLeftShadow;
@property(readonly, nonatomic) CALayer *bottomRightShadow; // @synthesize bottomRightShadow=_bottomRightShadow;
@property(readonly, nonatomic) CALayer *bottomShadow; // @synthesize bottomShadow=_bottomShadow;
- (id)init;
- (id)initWithStartSize:(struct CGSize)arg1 endSize:(struct CGSize)arg2 shadowType:(long long)arg3;
@property(readonly, nonatomic) CALayer *leftShadow; // @synthesize leftShadow=_leftShadow;
@property(readonly, nonatomic) CALayer *rightShadow; // @synthesize rightShadow=_rightShadow;
@property(readonly, nonatomic) long long shadowType; // @synthesize shadowType=_shadowType;
@property(readonly, nonatomic) CALayer *topLeftShadow; // @synthesize topLeftShadow=_topLeftShadow;
@property(readonly, nonatomic) CALayer *topRightShadow; // @synthesize topRightShadow=_topRightShadow;
@property(readonly, nonatomic) CALayer *topShadow; // @synthesize topShadow=_topShadow;

@end

