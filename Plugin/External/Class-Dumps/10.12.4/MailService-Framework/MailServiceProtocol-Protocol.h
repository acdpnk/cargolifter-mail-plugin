//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


@class MSEmailModel;

@protocol MailServiceProtocol <NSObject>
- (void)sendMessageWithModel:(MSEmailModel *)arg1 options:(NSUInteger)arg2 reply:(void (^)(NSError *))arg3;
@end
