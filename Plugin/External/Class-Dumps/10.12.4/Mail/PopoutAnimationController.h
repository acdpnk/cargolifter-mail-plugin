//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


@class CALayer, MailWindowShadowLayer, NSDictionary, NSWindow;

@interface PopoutAnimationController : NSObject
{
    CALayer *_contentLayer;
    CALayer *_clipLayer;
    CALayer *_backgroundLayer;
    NSWindow *_animationWindow;
    MailWindowShadowLayer *_shadowLayer;
    CALayer *_sourceBodyLayer;
    CALayer *_sourceHeaderLayer;
    CALayer *_destinationBodyLayer;
    CALayer *_destinationHeaderLayer;
    CALayer *_destinationToolbarLayer;
    NSDictionary *_sourceSnapshots;
    NSDictionary *_destinationSnapshots;
}

- (id)_backgroundAnimation;
- (struct CGRect)_commonScreenRectForSource:(struct CGRect)arg1 destination:(struct CGRect)arg2;
- (id)_createAnimationWindow:(struct CGRect)arg1;
- (id)_createBackgroundLayer;
- (id)_createContentLayerWithFrame:(struct CGRect)arg1 scale:(double)arg2;
- (id)_frameAnimationWithStart:(struct CGRect)arg1 destination:(struct CGRect)arg2;
- (BOOL)_initializeAnimationWindowComponentsWithSource:(id)arg1 destination:(id)arg2;
- (id)_internalTransitionAnimationWithDestination:(struct CGRect)arg1 fadeOut:(BOOL)arg2;
- (void)_performAnimationWithSourceGeometry:(id)arg1 destionationGeometry:(id)arg2 completion:(id)arg3;
- (id)_positionAnimationWithStartPosition:(struct CGPoint)arg1 endPosition:(struct CGPoint)arg2 percentFromStart:(double)arg3;
- (void)_setupLayer:(id)arg1 withGeometry:(id)arg2;
- (id)_sizeAnimationWithStartSize:(struct CGSize)arg1 endSize:(struct CGSize)arg2;
- (id)_toolbarAnimationWithFinalSize:(struct CGSize)arg1;
- (void)_updateDestinationSnapshots:(id)arg1;
- (void)_updateSourceSnapshots:(id)arg1;
- (void)animateFrom:(id)arg1 to:(id)arg2 withCompletion:(id)arg3;
@property(retain, nonatomic) NSWindow *animationWindow; // @synthesize animationWindow=_animationWindow;
@property(nonatomic) __weak CALayer *backgroundLayer; // @synthesize backgroundLayer=_backgroundLayer;
@property(nonatomic) __weak CALayer *clipLayer; // @synthesize clipLayer=_clipLayer;
@property(nonatomic) __weak CALayer *contentLayer; // @synthesize contentLayer=_contentLayer;
@property(nonatomic) __weak CALayer *destinationBodyLayer; // @synthesize destinationBodyLayer=_destinationBodyLayer;
@property(nonatomic) __weak CALayer *destinationHeaderLayer; // @synthesize destinationHeaderLayer=_destinationHeaderLayer;
@property(retain, nonatomic) NSDictionary *destinationSnapshots; // @synthesize destinationSnapshots=_destinationSnapshots;
@property(nonatomic) __weak CALayer *destinationToolbarLayer; // @synthesize destinationToolbarLayer=_destinationToolbarLayer;
@property(nonatomic) __weak MailWindowShadowLayer *shadowLayer; // @synthesize shadowLayer=_shadowLayer;
@property(nonatomic) __weak CALayer *sourceBodyLayer; // @synthesize sourceBodyLayer=_sourceBodyLayer;
@property(nonatomic) __weak CALayer *sourceHeaderLayer; // @synthesize sourceHeaderLayer=_sourceHeaderLayer;
@property(retain, nonatomic) NSDictionary *sourceSnapshots; // @synthesize sourceSnapshots=_sourceSnapshots;

@end
