//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header

#import <MCPowerLog.h>

#import "_MCBatchingTimerDelegate-Protocol.h"

@class NSLock, NSMutableDictionary, NSString, _MCBatchingTimer;

@interface MCAggregablePowerLog : MCPowerLog <_MCBatchingTimerDelegate>
{
    NSLock *_aggregationLock;
    NSMutableDictionary *_aggregatedEventDictionary;
    _MCBatchingTimer *_timer;
    id _aggregationBlock;
    double _aggregationPeriod;
}

@property(readonly, copy, nonatomic) id aggregationBlock; // @synthesize aggregationBlock=_aggregationBlock;
@property(readonly, nonatomic) double aggregationPeriod; // @synthesize aggregationPeriod=_aggregationPeriod;
- (void)batchingTimerDidFire:(id)arg1;
- (id)initWithEventName:(id)arg1 aggregationPeriod:(double)arg2 aggregationBlock:(id)arg3;
- (void)logEventWithDictionary:(id)arg1;

// Remaining properties
@property(readonly, copy) NSString *debugDescription;
@property(readonly, copy) NSString *description;
@property(readonly) NSUInteger hash;
@property(readonly) Class superclass;

@end
