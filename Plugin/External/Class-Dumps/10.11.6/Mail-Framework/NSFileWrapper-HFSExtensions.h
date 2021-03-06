//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


@class NSString;

@interface NSFileWrapper (HFSExtensions)
+ (id)_quarantinePropertiesQueue;
+ (void)loadMessageExtensions;
- (id)_Message_initWithURL:(id)arg1 options:(NSUInteger)arg2 error:(id *)arg3;
- (void)_Message_setPreferredFilename:(id)arg1;
- (BOOL)_Message_updateFromPath:(id)arg1 checkOnly:(BOOL)arg2 exists:(char *)arg3;
- (BOOL)_Message_writeToURL:(id)arg1 options:(NSUInteger)arg2 originalContentsURL:(id)arg3 error:(id *)arg4;
@property(readonly, nonatomic) BOOL couldConfuseWindowsClients;
@property(retain, nonatomic) NSString *savedPath;
@property(nonatomic) BOOL shouldBeViewedInline;
@end

