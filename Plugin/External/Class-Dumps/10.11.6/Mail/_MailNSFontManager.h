//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


@interface _MailNSFontManager : NSFontManager
{
    BOOL _isMultiple;
    double _fontSize;
}

- (void)_postSelectedFontChangeNotification;
- (id)convertFont:(id)arg1;
- (NSUInteger)currentFontAction;
@property(nonatomic) double fontSize; // @synthesize fontSize=_fontSize;
@property(nonatomic) BOOL isMultiple; // @synthesize isMultiple=_isMultiple;
- (void)modifyFontSize:(double)arg1;
- (void)setSelectedFont:(id)arg1 isMultiple:(BOOL)arg2;

@end

