//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header

#import <MFMessageSortingValue.h>

@class NSString;

@interface _MFMessageSortingValueSubject : MFMessageSortingValue
{
    unsigned char _subjectPrefixLength;
    NSString *_subject;
}

- (void)dealloc;
- (id)description;
@property(copy, nonatomic) NSString *subject; // @synthesize subject=_subject;
@property(nonatomic) unsigned char subjectPrefixLength; // @synthesize subjectPrefixLength=_subjectPrefixLength;

@end

