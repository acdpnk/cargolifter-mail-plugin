//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


@interface NSSound (MailAdditions)
+ (void)_addSoundOrPathToPlayList:(id)arg1 playImmediately:(BOOL)arg2;
+ (void)_playNextSound;
+ (void)_playSound;
+ (void)_setupPlayList;
+ (void)addSoundPathToPlayList:(id)arg1 playImmediately:(BOOL)arg2;
+ (void)addSoundToPlayList:(id)arg1 playImmediately:(BOOL)arg2;
+ (id)appendSoundsToPaths:(id)arg1;
+ (id)containerLibrarySoundsDirs;
+ (id)librarySoundsDirs;
+ (id)networkLibrarySoundsDirs;
+ (id)soundsAtPaths:(id)arg1;
+ (id)systemLibrarySoundsDirs;
+ (id)tildeLibrarySoundsDirs;
+ (id)validPathToSound:(id)arg1;
@end

