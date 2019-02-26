//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


@class MCMessage, MessageListObjectProxy, NSButton, NSColor;

@interface RichMessageCellBase : NSTableCellView
{
    NSColor *_textColor;
    NSButton *_replyButton;
}

+ (double)heightWithNumberOfSnippetLines:(NSUInteger)arg1;
+ (id)keyPathsForValuesAffectingIsSelected;
+ (id)keyPathsForValuesAffectingMessage;
+ (id)keyPathsForValuesAffectingTextColor;
@property(readonly, nonatomic) BOOL isSelected;
@property(readonly, nonatomic) MCMessage *message;
@property(retain) MessageListObjectProxy *objectValue;
@property(retain, nonatomic) NSButton *replyButton; // @synthesize replyButton=_replyButton;
- (void)setBackgroundStyle:(long long)arg1;
- (void)setFrameSize:(struct CGSize)arg1;
- (void)setReplyAction:(SEL)arg1;
- (void)setReplyTarget:(id)arg1;
@property(retain, nonatomic) NSColor *textColor; // @synthesize textColor=_textColor;

@end

