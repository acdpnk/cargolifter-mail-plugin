//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header

#import <MFIMAPOperation.h>

@class NSArray, NSDate;

@interface MFIMAPAppendMessageOperation : MFIMAPOperation
{
    unsigned int _uid;
    int _internalDateAsInt;
    NSArray *_flags;
}

- (void)_deserializeOpSpecificValuesFromData:(id)arg1 cursor:(NSUInteger *)arg2;
- (id)description;
@property(copy, nonatomic) NSArray *flags; // @synthesize flags=_flags;
- (id)initWithAppendedUid:(unsigned int)arg1 flags:(id)arg2 internalDate:(id)arg3 mailbox:(id)arg4;
@property(readonly, nonatomic) NSDate *internalDate;
@property(nonatomic) int internalDateAsInt; // @synthesize internalDateAsInt=_internalDateAsInt;
- (unsigned char)operationType;
- (void)serializeIntoData:(id)arg1;
@property(nonatomic) unsigned int uid; // @synthesize uid=_uid;

// Remaining properties
@property(nonatomic) BOOL usesRealUids; // @dynamic usesRealUids;

@end

