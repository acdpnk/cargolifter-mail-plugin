//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


@class NSColor, NSMenu, NSPopUpButton, NSString, NSTextField;

@interface ComposeStatusView : NSStackView
{
    NSTextField *_messageSizeLabel;
    NSTextField *_messageSizeTextField;
    NSTextField *_imageSizePickerLabel;
    NSPopUpButton *_imageSizePickerPopup;
    NSTextField *_URLPickerLabel;
    NSPopUpButton *_URLPickerButton;
}

+ (id)keyPathsForValuesAffectingMessageSizeColor;
+ (id)keyPathsForValuesAffectingMessageSizeValue;
+ (id)keyPathsForValuesAffectingSelectedImageSize;
+ (id)keyPathsForValuesAffectingSelectedSharingDisplayType;
@property(retain, nonatomic) NSPopUpButton *URLPickerButton; // @synthesize URLPickerButton=_URLPickerButton;
@property(retain, nonatomic) NSTextField *URLPickerLabel; // @synthesize URLPickerLabel=_URLPickerLabel;
@property(readonly, nonatomic) __weak NSMenu *URLPickerMenu;
- (void)awakeFromNib;
@property(readonly, nonatomic) BOOL canHideStatusBar;
@property(readonly, nonatomic) __weak NSMenu *imageSizeMenu;
@property(retain, nonatomic) NSTextField *imageSizePickerLabel; // @synthesize imageSizePickerLabel=_imageSizePickerLabel;
@property(retain, nonatomic) NSPopUpButton *imageSizePickerPopup; // @synthesize imageSizePickerPopup=_imageSizePickerPopup;
@property(retain, nonatomic) NSColor *messageSizeColor;
@property(retain, nonatomic) NSTextField *messageSizeLabel; // @synthesize messageSizeLabel=_messageSizeLabel;
@property(retain, nonatomic) NSTextField *messageSizeTextField; // @synthesize messageSizeTextField=_messageSizeTextField;
@property(copy, nonatomic) NSString *messageSizeValue;
@property(nonatomic) long long selectedImageSize;
@property(nonatomic) long long selectedSharingDisplayType;
@property(nonatomic) BOOL showsImageSizePicker;
@property(nonatomic) BOOL showsMessageSizeLabel;
@property(nonatomic) BOOL showsURLPicker;

@end
