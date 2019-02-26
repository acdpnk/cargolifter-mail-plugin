//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


@class NSString;

@interface NSData (MailCoreAdditions)
@property(readonly, copy, nonatomic) NSData *MD5Digest;
@property(readonly, copy, nonatomic) NSString *hexString;
- (id)initWithDataConvertingLineEndingsFromNetworkToUnix:(id)arg1;
- (id)initWithDataConvertingLineEndingsFromUnixToNetwork:(id)arg1;
@property(readonly, copy, nonatomic) NSData *quotedFromSpaceDataForMessage;
- (struct _NSRange)rangeOfByteFromSet:(id)arg1;
- (struct _NSRange)rangeOfCString:(const char *)arg1;
- (struct _NSRange)rangeOfCString:(const char *)arg1 options:(NSUInteger)arg2;
- (struct _NSRange)rangeOfCString:(const char *)arg1 options:(NSUInteger)arg2 range:(struct _NSRange)arg3;
@property(readonly, nonatomic) struct _NSRange rangeOfRFC822HeaderData;
- (id)unquotedFromSpaceDataWithRange:(struct _NSRange)arg1;
@end

