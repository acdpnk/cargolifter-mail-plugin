//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


@interface MFFileSystemPersistenceManager : NSObject
{
}

+ (id)_emlxPListInFile:(id)arg1 url:(id)arg2 plistOffset:(NSUInteger *)arg3;
+ (void)removeAlternateFileForEmlxFile:(id)arg1;
+ (BOOL)updatePropertyListAtURL:(id)arg1 propertyListBlock:(id)arg2 outError:(id *)arg3;
+ (BOOL)writeAttachment:(id)arg1 toDirectory:(id)arg2 originalContentsURL:(id)arg3 outError:(id *)arg4;
+ (BOOL)writeMimeData:(id)arg1 toURL:(id)arg2 isPart:(BOOL)arg3 propertyList:(id)arg4 outError:(id *)arg5;

@end

