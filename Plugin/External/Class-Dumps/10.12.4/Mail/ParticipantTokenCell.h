//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header

#import "MUIAddressTokenAttachmentCell.h"

@class NSSet, NSString;

@interface ParticipantTokenCell : MUIAddressTokenAttachmentCell
{
    BOOL _isVipCell;
    NSString *_displayName;
    NSUInteger _count;
}

- (BOOL)_canBeSelected;
- (id)_defaultAttributes;
- (id)_displayAttributedStringIsSelected:(BOOL)arg1;
- (void)_updateStringValue;
- (void)_updateVipStatus;
@property(nonatomic) NSUInteger count; // @synthesize count=_count;
@property(copy, nonatomic) NSString *displayName; // @synthesize displayName=_displayName;
- (void)drawInteriorWithFrame:(struct CGRect)arg1 inView:(id)arg2;
- (id)initTextCell:(id)arg1;
- (id)initWithCoder:(id)arg1;
- (id)initWithDisplayName:(id)arg1 count:(NSUInteger)arg2;
@property(nonatomic) BOOL isVipCell; // @synthesize isVipCell=_isVipCell;
@property(retain) NSSet *representedObject;
- (BOOL)shouldDrawTokenBackground;
- (id)tokenTintColor;
- (BOOL)trackMouse:(id)arg1 inRect:(struct CGRect)arg2 ofView:(id)arg3 atCharacterIndex:(NSUInteger)arg4 untilMouseUp:(BOOL)arg5;

@end

