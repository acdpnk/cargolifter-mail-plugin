//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


@interface FlaggedStatusToolbarItem : NSToolbarItem
{
    id <FlaggedStatusToolbarItemDelegate> _delegate;
}

- (void)dealloc;
@property(nonatomic) __weak id <FlaggedStatusToolbarItemDelegate> delegate; // @synthesize delegate=_delegate;
- (id)initWithItemIdentifier:(id)arg1;
- (void)validate;

@end
