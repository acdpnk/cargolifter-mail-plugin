//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header

#import "LoadRemoteContentBannerViewController.h"

@class NSButton, NSImageView, NSTextField;

@interface CertificateBannerViewController : LoadRemoteContentBannerViewController
{
    NSImageView *_certificateImage;
    NSTextField *_messageField;
    NSButton *_helpButton;
}

@property(nonatomic) __weak NSImageView *certificateImage; // @synthesize certificateImage=_certificateImage;
- (void)dealloc;
@property(nonatomic) __weak NSButton *helpButton; // @synthesize helpButton=_helpButton;
@property(nonatomic) __weak NSTextField *messageField; // @synthesize messageField=_messageField;
- (void)observeValueForKeyPath:(id)arg1 ofObject:(id)arg2 change:(id)arg3 context:(void *)arg4;
- (void)setRepresentedObject:(id)arg1;
- (BOOL)shouldDisplayToLoadRemoteContent;
- (void)showDetails:(id)arg1;
- (void)updateBannerContents;
- (void)updateWantsDisplay;

@end

