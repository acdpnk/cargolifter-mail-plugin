//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


@class NSArrayController, NSDate, NSString;

@interface MCActivityAggregate : NSObject
{
    NSArrayController *_monitorController;
    NSUInteger _baseItemsDone;
    NSUInteger _baseItemsTotal;
    double _baseUnifiedDone;
    BOOL _canCancel;
    NSUInteger _itemsDone;
    NSUInteger _itemsTotal;
    double _unifiedDone;
    double _progress;
    BOOL _isProgressing;
    double _estimatedTimeRemaining;
    BOOL _isResetting;
    long long _activityType;
    NSString *_nameSingular;
    NSString *_namePlural;
    NSString *_status;
    NSString *_bkItemDescription;
    NSDate *_lastUpdateTimestamp;
    double _startTime;
}

+ (BOOL)automaticallyNotifiesObserversOfCanCancel;
+ (BOOL)automaticallyNotifiesObserversOfEstimatedTimeRemaining;
+ (BOOL)automaticallyNotifiesObserversOfIsProgressing;
+ (BOOL)automaticallyNotifiesObserversOfProgress;
+ (id)keyPathsForValuesAffectingIsProgressIndeterminate;
+ (double)updateDelay;
- (void)_processMonitorUpdate;
- (void)_update;
- (void)_updateAggregateIsProgressing;
- (void)_updateAggregateValues;
- (void)_updateStatus;
- (void)_updateTimeBasedValues;
@property long long activityType; // @synthesize activityType=_activityType;
- (void)addActivityMonitor:(id)arg1;
@property(copy) NSString *bkItemDescription; // @synthesize bkItemDescription=_bkItemDescription;
@property(nonatomic) BOOL canCancel;
- (NSUInteger)currentItem;
- (void)dealloc;
- (id)description;
@property(nonatomic) double estimatedTimeRemaining;
- (id)init;
@property(readonly, nonatomic) BOOL isProgressIndeterminate;
@property(nonatomic) BOOL isProgressing;
@property BOOL isResetting; // @synthesize isResetting=_isResetting;
@property NSUInteger itemsDone;
@property NSUInteger itemsTotal;
@property(retain) NSDate *lastUpdateTimestamp; // @synthesize lastUpdateTimestamp=_lastUpdateTimestamp;
@property(readonly, nonatomic) NSArrayController *monitorController;
@property(copy) NSString *namePlural; // @synthesize namePlural=_namePlural;
@property(copy) NSString *nameSingular; // @synthesize nameSingular=_nameSingular;
- (void)observeValueForKeyPath:(id)arg1 ofObject:(id)arg2 change:(id)arg3 context:(void *)arg4;
@property(nonatomic) double progress;
- (void)removeActivityMonitor:(id)arg1;
- (void)reset;
@property(nonatomic) double startTime; // @synthesize startTime=_startTime;
@property(copy) NSString *status; // @synthesize status=_status;
@property double unifiedDone;
- (void)signalCancel:(id)arg1;
- (void)updateUnitBasedValues;

@end

