//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


@interface MCDateParser : NSObject
{
}

+ (id)_commonDateFormatters;
+ (id)_dateFromString:(id)arg1 imapFirst:(BOOL)arg2;
+ (id)_dateStringByStrippingCommentsFromString:(id)arg1;
+ (id)_fallbackDateFormaters;
+ (id)_imapDateFormatter;
+ (id)dateFromIMAPDateString:(id)arg1;
+ (id)dateFromInternetMessageDateString:(id)arg1;

@end
