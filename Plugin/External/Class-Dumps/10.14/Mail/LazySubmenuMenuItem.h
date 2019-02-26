//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


@class NSMenu;

@interface LazySubmenuMenuItem : NSMenuItem
{
    BOOL _enableLoadedSubmenu;
    id _lazySubmenuBlock;
    NSMenu *_loadedSubmenu;
}

- (id)copyWithZone:(struct _NSZone *)arg1;
@property(nonatomic) BOOL enableLoadedSubmenu; // @synthesize enableLoadedSubmenu=_enableLoadedSubmenu;
- (BOOL)hasSubmenu;
- (BOOL)isEnabled;
@property(copy, nonatomic) id lazySubmenuBlock; // @synthesize lazySubmenuBlock=_lazySubmenuBlock;
@property(retain, nonatomic) NSMenu *loadedSubmenu; // @synthesize loadedSubmenu=_loadedSubmenu;
- (void)setEnabled:(BOOL)arg1;
- (id)submenu;

@end

