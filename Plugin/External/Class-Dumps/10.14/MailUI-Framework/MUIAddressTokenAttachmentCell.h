//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


@class NSColor;

@interface MUIAddressTokenAttachmentCell : NSTokenAttachmentCell
{
    BOOL _neverShowSeparator;
    BOOL _displayAsExternal;
    NSColor *_foregroundColor;
}

+ (id)colorForExternalDomain;
- (BOOL)_finalizeStyleTextOptions:(id)arg1;
- (id)_textAttributes;
@property(nonatomic) BOOL displayAsExternal; // @synthesize displayAsExternal=_displayAsExternal;
@property(retain, nonatomic) NSColor *foregroundColor; // @synthesize foregroundColor=_foregroundColor;
@property BOOL neverShowSeparator; // @synthesize neverShowSeparator=_neverShowSeparator;
- (id)tokenTintColor;

@end

