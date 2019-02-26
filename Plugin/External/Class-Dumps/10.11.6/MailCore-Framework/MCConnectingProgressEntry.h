//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header

#import <MCProgressEntry.h>

@class NSArray;

@interface MCConnectingProgressEntry : MCProgressEntry
{
    NSArray *_connectingAccountNames;
}

+ (id)keyPathsForValuesAffectingStatusText;
@property(copy, nonatomic) NSArray *connectingAccountNames; // @synthesize connectingAccountNames=_connectingAccountNames;
- (BOOL)indeterminate;
- (id)observedProgressKeypaths;
- (id)progressName;
- (id)progressSlice;
- (void)refreshValues;
- (id)statusText;

@end

