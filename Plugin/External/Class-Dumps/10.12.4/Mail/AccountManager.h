//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


@class NSDate, NSMutableArray, NSOperationQueue, NSTimer, NSUserDefaults;

@interface AccountManager : NSObject
{
    NSMutableArray *_accountsBeingObserved;
    BOOL _automaticFetchingShouldBeDisabled;
    BOOL _dailyCleanupDisabled;
    BOOL _missedDailyCleanup;
    NSOperationQueue *_automaticFetchQueue;
    NSTimer *_fetchTimer;
    NSDate *_lastAutomaticFetchDate;
    NSDate *_lastAutomaticUserInteractionFetchDate;
    NSOperationQueue *_accountChangedQueue;
}

+ (id)allocWithZone:(struct _NSZone *)arg1;
+ (id)keyPathsForValuesAffectingFetchFrequency;
+ (id)log;
+ (id)sharedInstance;
- (void)_accountStoreDidChange:(id)arg1;
- (void)_adjustFetchActivityAndReset:(BOOL)arg1;
- (void)_applicationDidBecomeActive:(id)arg1;
- (void)_connectionError:(id)arg1 didChangeForAccount:(id)arg2;
- (void)_credentialsDidChange:(id)arg1;
- (void)_deliveryAccountConnectionOrAuthenticationPropertiesDidChange:(id)arg1;
- (void)_fetchForAllAccountsWithType:(long long)arg1;
- (void)_fetchTimerFired:(id)arg1;
- (void)_mailAccountConnectionOrAuthenticationPropertiesDidChange:(id)arg1;
- (void)_mailAccountNeedsChecking:(id)arg1;
- (void)_mailAccountsChanged:(id)arg1;
- (void)_performAutomaticFetch:(long long)arg1;
- (void)_performDailyCleanup:(id)arg1;
- (void)_startSynchronizationForNewAccount:(id)arg1;
@property(readonly, nonatomic) NSOperationQueue *accountChangedQueue; // @synthesize accountChangedQueue=_accountChangedQueue;
@property(readonly, nonatomic) NSOperationQueue *automaticFetchQueue; // @synthesize automaticFetchQueue=_automaticFetchQueue;
@property(nonatomic) BOOL automaticFetchingShouldBeDisabled; // @synthesize automaticFetchingShouldBeDisabled=_automaticFetchingShouldBeDisabled;
@property(nonatomic) BOOL dailyCleanupDisabled; // @synthesize dailyCleanupDisabled=_dailyCleanupDisabled;
- (void)dealloc;
- (void)disableAutomaticFetching;
- (void)disableDailyCleanup;
- (void)enableAutomaticFetchingAndFetchIfNecessary;
- (void)enableDailyCleanupAndCleanupIfNecessary;
- (void)fetchForAccount:(id)arg1 isAutomatic:(BOOL)arg2;
@property(nonatomic) long long fetchFrequency;
@property(retain, nonatomic) NSTimer *fetchTimer; // @synthesize fetchTimer=_fetchTimer;
- (id)init;
- (void)initializeAutomaticFetchingAndPerformInitialFetch;
@property(retain, nonatomic) NSDate *lastAutomaticFetchDate; // @synthesize lastAutomaticFetchDate=_lastAutomaticFetchDate;
@property(retain, nonatomic) NSDate *lastAutomaticUserInteractionFetchDate; // @synthesize lastAutomaticUserInteractionFetchDate=_lastAutomaticUserInteractionFetchDate;
@property(nonatomic) BOOL missedDailyCleanup; // @synthesize missedDailyCleanup=_missedDailyCleanup;
- (void)observeValueForKeyPath:(id)arg1 ofObject:(id)arg2 change:(id)arg3 context:(void *)arg4;
- (void)performInitialAccountSynchronization;
@property(readonly, nonatomic) NSUserDefaults *userDefaults;

@end

