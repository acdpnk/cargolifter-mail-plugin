//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


@class FontPreferenceContainerView, NSArray, NSFont, NSMutableDictionary, NSPopUpButton, NSTextView;

@interface FontsAndColorsPreferences : NSPreferencesModule
{
    NSMutableDictionary *_midYDict;
    BOOL _isQuotedTextColored;
    BOOL _isPlainTextOfFixedWidth;
    NSFont *_messageListFont;
    NSFont *_messageFont;
    NSFont *_fixedWidthFont;
    NSArray *_colorList;
    FontPreferenceContainerView *_messageListContainerView;
    FontPreferenceContainerView *_messageTextContainerView;
    FontPreferenceContainerView *_fixedWidthContainerView;
    NSPopUpButton *_colorPopupOne;
    NSPopUpButton *_colorPopupTwo;
    NSPopUpButton *_colorPopupThree;
    NSTextView *_exampleTextView;
    NSArray *_fontPrefContainerViews;
    double _containerSuperViewSpacingY;
    double _containerContainerSpacingY;
    long long _changingFontPreference;
    NSPopUpButton *_lastColorPopupSelected;
}

+ (id)keyPathsForValuesAffectingFixedWidthSampleFont;
+ (id)keyPathsForValuesAffectingMessageListSampleFont;
+ (id)keyPathsForValuesAffectingMessageSampleFont;
- (void)_colorPicked:(id)arg1;
- (id)_containerViewForFontPreference:(long long)arg1;
- (id)_getFontForPreferenceContainer:(id)arg1;
- (void)_growWindowVertically:(double)arg1 animate:(BOOL)arg2;
- (void)_layoutFromFontPreference:(long long)arg1;
- (void)_populateFontPrefContainers;
- (void)_replaceExampleTextView;
- (id)_sampleFontForFont:(id)arg1;
- (void)_setColor:(id)arg1 forPopup:(id)arg2;
- (void)_setFont:(id)arg1 forPreferenceContainer:(id)arg2;
- (void)_setOtherColor:(id)arg1 forPopup:(id)arg2;
- (double)_sizeContainerView:(id)arg1;
- (void)_updateAutoresizeFlags:(long long)arg1;
- (void)_updateColorList;
- (void)_updateExampleTextView;
- (void)awakeFromNib;
- (void)changeFont:(id)arg1;
@property(nonatomic) long long changingFontPreference; // @synthesize changingFontPreference=_changingFontPreference;
@property(retain, nonatomic) NSArray *colorList; // @synthesize colorList=_colorList;
- (void)colorPopupChanged:(id)arg1;
@property(nonatomic) __weak NSPopUpButton *colorPopupOne; // @synthesize colorPopupOne=_colorPopupOne;
@property(nonatomic) __weak NSPopUpButton *colorPopupThree; // @synthesize colorPopupThree=_colorPopupThree;
@property(nonatomic) __weak NSPopUpButton *colorPopupTwo; // @synthesize colorPopupTwo=_colorPopupTwo;
- (void)colorQuotesButtonClicked:(id)arg1;
@property(nonatomic) double containerContainerSpacingY; // @synthesize containerContainerSpacingY=_containerContainerSpacingY;
@property(nonatomic) double containerSuperViewSpacingY; // @synthesize containerSuperViewSpacingY=_containerSuperViewSpacingY;
@property(retain, nonatomic) NSTextView *exampleTextView; // @synthesize exampleTextView=_exampleTextView;
@property(nonatomic) __weak FontPreferenceContainerView *fixedWidthContainerView; // @synthesize fixedWidthContainerView=_fixedWidthContainerView;
@property(retain, nonatomic) NSFont *fixedWidthFont; // @synthesize fixedWidthFont=_fixedWidthFont;
@property(readonly, nonatomic) NSFont *fixedWidthSampleFont;
@property(copy, nonatomic) NSArray *fontPrefContainerViews; // @synthesize fontPrefContainerViews=_fontPrefContainerViews;
- (id)imageForPreferenceNamed:(id)arg1;
- (void)initializeFromDefaults;
@property(nonatomic) BOOL isPlainTextOfFixedWidth; // @synthesize isPlainTextOfFixedWidth=_isPlainTextOfFixedWidth;
@property(nonatomic) BOOL isQuotedTextColored; // @synthesize isQuotedTextColored=_isQuotedTextColored;
- (BOOL)isResizable;
@property(nonatomic) __weak NSPopUpButton *lastColorPopupSelected; // @synthesize lastColorPopupSelected=_lastColorPopupSelected;
@property(retain, nonatomic) NSFont *messageFont; // @synthesize messageFont=_messageFont;
@property(nonatomic) __weak FontPreferenceContainerView *messageListContainerView; // @synthesize messageListContainerView=_messageListContainerView;
@property(retain, nonatomic) NSFont *messageListFont; // @synthesize messageListFont=_messageListFont;
@property(readonly, nonatomic) NSFont *messageListSampleFont;
@property(readonly, nonatomic) NSFont *messageSampleFont;
@property(nonatomic) __weak FontPreferenceContainerView *messageTextContainerView; // @synthesize messageTextContainerView=_messageTextContainerView;
- (void)moduleWillBeRemoved;
- (void)selectFont:(id)arg1;
- (id)titleForIdentifier:(id)arg1;
- (void)toggleColorQuotedText:(id)arg1;
- (void)toggleUseFixedWidthFont:(id)arg1;
- (NSUInteger)validModesForFontPanel:(id)arg1;

@end

