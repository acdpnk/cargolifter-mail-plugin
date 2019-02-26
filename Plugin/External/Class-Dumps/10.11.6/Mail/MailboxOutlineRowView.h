//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


@class NSTrackingArea;

@interface MailboxOutlineRowView : NSTableRowView
{
    NSTrackingArea *_trackingArea;
}

- (void)_mailboxOutlineRowViewCommonInit;
- (void)didAddSubview:(id)arg1;
- (id)initWithCoder:(id)arg1;
- (id)initWithFrame:(struct CGRect)arg1;
- (void)mouseEntered:(id)arg1;
- (void)mouseExited:(id)arg1;
@property(nonatomic) BOOL trackCursor;
@property(retain, nonatomic) NSTrackingArea *trackingArea; // @synthesize trackingArea=_trackingArea;
- (BOOL)shouldSetFontSmoothingBackgroundColor;

@end

