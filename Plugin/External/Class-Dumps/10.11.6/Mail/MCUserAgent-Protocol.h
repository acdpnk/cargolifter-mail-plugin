//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


@class MCStringRenderContext, NSData, NSString;

@protocol MCUserAgent <NSObject>
@property(nonatomic) BOOL isInTimeMachineMode;
@property(readonly, nonatomic) long long junkMailBehavior;
- (NSString *)junkStringFromHTMLData:(NSData *)arg1 textEncodingName:(NSString *)arg2 context:(MCStringRenderContext *)arg3;
@property(readonly, copy, nonatomic) NSString *localAttachmentFilesDirectory;
@end

