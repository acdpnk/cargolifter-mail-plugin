//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


@class NSView;

@protocol NSTextFinderBarContainer <NSObject>
@property(retain) NSView *findBarView;
- (void)findBarViewDidChangeHeight;
@property(getter=isFindBarVisible) BOOL findBarVisible;

@optional
- (NSView *)contentView;
@end

