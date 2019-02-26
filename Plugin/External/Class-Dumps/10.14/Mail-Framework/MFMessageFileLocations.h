//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


@class NSDictionary, NSURL;

@interface MFMessageFileLocations : NSObject
{
    BOOL _isPartial;
    NSURL *_primaryEmlxURL;
    NSURL *_attachmentDirectory;
    long long _libraryID;
}

- (BOOL)_transferToNewFileLocation:(id)arg1 renameOrCopyBlock:(id)arg2 error:(id *)arg3;
@property(retain, nonatomic) NSURL *attachmentDirectory; // @synthesize attachmentDirectory=_attachmentDirectory;
@property(readonly, copy, nonatomic) NSDictionary *attachmentURLsByPartNumber;
- (BOOL)copyToNewFileLocation:(id)arg1 replaceIfExists:(BOOL)arg2 error:(id *)arg3;
- (id)description;
@property(readonly, copy, nonatomic) NSDictionary *emlxPartURLsByPartNumber;
- (id)init;
- (id)initWithPrimaryEmlxURL:(id)arg1;
@property(readonly, nonatomic) BOOL isPartial; // @synthesize isPartial=_isPartial;
@property(readonly, nonatomic) long long libraryID; // @synthesize libraryID=_libraryID;
- (BOOL)moveToNewFileLocation:(id)arg1 error:(id *)arg2;
@property(readonly, nonatomic) NSURL *primaryEmlxURL; // @synthesize primaryEmlxURL=_primaryEmlxURL;

@end
