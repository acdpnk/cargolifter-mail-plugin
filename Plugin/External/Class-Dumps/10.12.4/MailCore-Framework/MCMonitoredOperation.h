//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


@class MCActivityMonitor, NSString;

@interface MCMonitoredOperation : NSOperation
{
    MCActivityMonitor *_parentMonitor;
    MCActivityMonitor *_monitor;
}

@property(readonly, copy, nonatomic) NSString *activityString;
- (void)dealloc;
- (void)executeOperation;
- (id)init;
- (void)main;
@property(retain, nonatomic) MCActivityMonitor *monitor; // @synthesize monitor=_monitor;
@property(retain, nonatomic) MCActivityMonitor *parentMonitor; // @synthesize parentMonitor=_parentMonitor;

@end

