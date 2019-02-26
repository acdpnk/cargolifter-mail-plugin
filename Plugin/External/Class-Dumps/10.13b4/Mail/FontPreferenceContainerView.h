//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


@class NSButton, NSTextField;

@interface FontPreferenceContainerView : NSView
{
    long long _fontPreference;
    NSButton *_selectButton;
    NSTextField *_labelTextField;
    NSTextField *_sampleTextField;
    double _buttonOffset;
    double _labelOffset;
    double _sampleOffset;
    struct CGRect _myOriginalFrame;
    struct CGRect _sampleTextFieldOriginalFrame;
}

- (void)awakeFromNib;
@property(nonatomic) double buttonOffset; // @synthesize buttonOffset=_buttonOffset;
@property(nonatomic) long long fontPreference; // @synthesize fontPreference=_fontPreference;
@property(nonatomic) double labelOffset; // @synthesize labelOffset=_labelOffset;
@property(retain, nonatomic) NSTextField *labelTextField; // @synthesize labelTextField=_labelTextField;
@property(nonatomic) struct CGRect myOriginalFrame; // @synthesize myOriginalFrame=_myOriginalFrame;
@property(nonatomic) double sampleOffset; // @synthesize sampleOffset=_sampleOffset;
@property(retain, nonatomic) NSTextField *sampleTextField; // @synthesize sampleTextField=_sampleTextField;
@property(nonatomic) struct CGRect sampleTextFieldOriginalFrame; // @synthesize sampleTextFieldOriginalFrame=_sampleTextFieldOriginalFrame;
@property(retain, nonatomic) NSButton *selectButton; // @synthesize selectButton=_selectButton;

@end

