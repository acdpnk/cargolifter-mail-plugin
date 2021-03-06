//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


@class NSBackgroundActivityScheduler;

@interface MFEMLXUpgrader : NSObject
{
    NSBackgroundActivityScheduler *_mimeSnipActivityScheduler;
    id _mimeSnipActivityCompletionHandler;
    NSBackgroundActivityScheduler *_libraryCompressionActivityScheduler;
    id _libraryCompressionCompletionHandler;
}

- (id)_checkMIMEInEMLXFile:(id)arg1;
- (void)_cleanupMessageXAttrsInAccountDirectories:(id)arg1;
- (void)_cleanupSpotlightIndexForMailboxDirectory:(id)arg1;
- (void)_compressLibraryDirectories:(id)arg1;
- (BOOL)_compressionNeededForMailbox:(id)arg1;
- (BOOL)_libraryCompressionComplete;
- (BOOL)_mimeSnipUpgraderComplete;
- (void)_runLibraryCompressionIfNeeded;
- (void)_runMIMESnipUpradesIfNeeded;
- (void)_snipAttachmentMIMEInAccountDirectories:(id)arg1;
- (void)dealloc;
@property(retain, nonatomic) NSBackgroundActivityScheduler *libraryCompressionActivityScheduler; // @synthesize libraryCompressionActivityScheduler=_libraryCompressionActivityScheduler;
@property(copy, nonatomic) id libraryCompressionCompletionHandler; // @synthesize libraryCompressionCompletionHandler=_libraryCompressionCompletionHandler;
@property(copy, nonatomic) id mimeSnipActivityCompletionHandler; // @synthesize mimeSnipActivityCompletionHandler=_mimeSnipActivityCompletionHandler;
@property(retain, nonatomic) NSBackgroundActivityScheduler *mimeSnipActivityScheduler; // @synthesize mimeSnipActivityScheduler=_mimeSnipActivityScheduler;
- (void)runIfNeeded;

@end

