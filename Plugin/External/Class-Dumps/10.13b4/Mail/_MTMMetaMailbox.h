//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header

#import "MTMSpecialMailbox.h"

@interface _MTMMetaMailbox : MTMSpecialMailbox
{
}

- (void)_loadMessages;
- (BOOL)_shouldSortMailboxes;
- (void)discardMailbox;
- (void)loadNextMessagesWithControllingMailbox:(id)arg1 andFetcher:(id)arg2;
- (BOOL)needsToLoadMessagesInBackground;
- (void)observeValueForKeyPath:(id)arg1 ofObject:(id)arg2 change:(id)arg3 context:(void *)arg4;
- (id)paths;
- (id)restoreString;
- (id)subRestoreString;

@end

