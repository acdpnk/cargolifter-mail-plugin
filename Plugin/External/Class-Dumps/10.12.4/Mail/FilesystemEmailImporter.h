//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header

#import "EmailImporter.h"

@class NSSet;

@interface FilesystemEmailImporter : EmailImporter
{
}

@property(readonly, nonatomic) char *fromString;
- (BOOL)isValidMailbox:(id)arg1;
@property(readonly, copy, nonatomic) NSSet *pathExtensions;
- (void)prepareForImport;
- (void)processUserSelection;
- (void)readMailbox:(id)arg1 intoMailbox:(id)arg2;
- (void)sniffLineDelimiterFromData:(id)arg1;
- (void)verifyFromSpaceHeaderForScanner:(id)arg1 dataLength:(NSUInteger)arg2;

@end

