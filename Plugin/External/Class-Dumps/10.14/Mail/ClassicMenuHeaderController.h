//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


@class NSMenu, NSMenuItem;

@interface ClassicMenuHeaderController : NSObject
{
    NSMenu *_tableHeaderMenu;
    NSMenu *_sortByMenu;
    NSMenuItem *_dateReceivedMenuItem;
    NSMenuItem *_dateSentMenuItem;
}

@property(nonatomic) __weak NSMenuItem *dateReceivedMenuItem; // @synthesize dateReceivedMenuItem=_dateReceivedMenuItem;
@property(nonatomic) __weak NSMenuItem *dateSentMenuItem; // @synthesize dateSentMenuItem=_dateSentMenuItem;
- (id)init;
@property(nonatomic) __weak NSMenu *sortByMenu; // @synthesize sortByMenu=_sortByMenu;
@property(retain, nonatomic) NSMenu *tableHeaderMenu; // @synthesize tableHeaderMenu=_tableHeaderMenu;
- (void)updateMenuWithSelectedMailboxes:(id)arg1;

@end
