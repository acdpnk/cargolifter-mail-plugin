//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


@class NSData, NSNumber, NSString;

@interface NSFileWrapper (MailCoreAdditions)
- (BOOL)_writeFinderInfoToURL:(id)arg1 includeDirectoryContents:(BOOL)arg2;
- (id)createTemporaryFile;
@property(nonatomic) unsigned int creator;
@property(retain, nonatomic) NSNumber *filePermissions;
@property(nonatomic) unsigned short finderFlags;
@property(readonly, copy, nonatomic) NSString *preferredFilenameWithoutHiddenExtension;
@property(retain, nonatomic) NSData *resourceForkData;
@property(nonatomic) BOOL shouldHideExtension;
@property(nonatomic) unsigned int type;
@property(readonly, copy, nonatomic) NSString *stringForIndexing;
@end

