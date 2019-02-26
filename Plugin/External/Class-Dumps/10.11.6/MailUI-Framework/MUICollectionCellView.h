//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


@class NSLayoutConstraint;

@interface MUICollectionCellView : NSView
{
    BOOL _emphasized;
    BOOL _focused;
    BOOL _selected;
    NSUInteger _cellIndex;
    NSLayoutConstraint *_widthConstraint;
    NSLayoutConstraint *_heightConstraint;
    NSLayoutConstraint *_midXConstraint;
    NSLayoutConstraint *_minYConstraint;
}

- (id)_enclosingConversationView;
- (void)_muiCollectionCellViewCommonInit;
@property(nonatomic) NSUInteger cellIndex; // @synthesize cellIndex=_cellIndex;
- (void)collectionView:(id)arg1 didBeginScrollInScrollView:(id)arg2;
- (void)collectionView:(id)arg1 didEndScrollInScrollView:(id)arg2;
- (void)collectionView:(id)arg1 didScrollInScrollView:(id)arg2;
@property(nonatomic) BOOL emphasized; // @synthesize emphasized=_emphasized;
@property(nonatomic) BOOL focused; // @synthesize focused=_focused;
@property(retain, nonatomic) NSLayoutConstraint *heightConstraint; // @synthesize heightConstraint=_heightConstraint;
- (id)initWithCoder:(id)arg1;
- (id)initWithFrame:(struct CGRect)arg1;
- (BOOL)isFlipped;
@property(retain, nonatomic) NSLayoutConstraint *midXConstraint; // @synthesize midXConstraint=_midXConstraint;
@property(retain, nonatomic) NSLayoutConstraint *minYConstraint; // @synthesize minYConstraint=_minYConstraint;
- (void)prepareContentInRect:(struct CGRect)arg1;
- (void)prepareForReuse;
@property(nonatomic) BOOL selected; // @synthesize selected=_selected;
- (void)setFrameSize:(struct CGSize)arg1;
@property(retain, nonatomic) NSLayoutConstraint *widthConstraint; // @synthesize widthConstraint=_widthConstraint;
@property(readonly, nonatomic) id viewController;

@end

