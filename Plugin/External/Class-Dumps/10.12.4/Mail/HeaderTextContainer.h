//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


@class NSMutableSet;

@interface HeaderTextContainer : NSTextContainer
{
    NSMutableSet *_views;
}

- (void)_headerTextContainerCommonInit;
- (void)addView:(id)arg1;
- (id)initWithCoder:(id)arg1;
- (id)initWithSize:(struct CGSize)arg1;
- (BOOL)isSimpleRectangularTextContainer;
- (struct CGRect)lineFragmentRectForProposedRect:(struct CGRect)arg1 sweepDirection:(NSUInteger)arg2 movementDirection:(NSUInteger)arg3 remainingRect:(struct CGRect *)arg4;
@property(readonly, nonatomic) double lineWidth;
- (void)removeView:(id)arg1;

@end

