//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


@class CALayer, MinimizeTrayTabBarView;

@interface MessageViewerFullScreenMinimizeTray : NSView
{
    CALayer *_dividerLayer;
    MinimizeTrayTabBarView *_tabBarView;
}

- (void)awakeFromNib;
@property(nonatomic) __weak CALayer *dividerLayer; // @synthesize dividerLayer=_dividerLayer;
- (NSUInteger)draggingEntered:(id)arg1;
- (void)hideTabs;
- (id)makeBackingLayer;
- (void)restoreMinimizedModalWindows;
@property(nonatomic) __weak MinimizeTrayTabBarView *tabBarView; // @synthesize tabBarView=_tabBarView;
- (void)showTabsWithNames:(id)arg1 tabBarWidth:(double)arg2;
- (BOOL)wantsUpdateLayer;

@end

