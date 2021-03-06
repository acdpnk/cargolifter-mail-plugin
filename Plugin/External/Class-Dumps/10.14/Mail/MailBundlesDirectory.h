//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


@class MailBundleController, NSArray, NSMutableArray, NSMutableDictionary, NSString, NSURL;

@interface MailBundlesDirectory : NSObject
{
    struct __FSEventStream *_eventStream;
    NSString *_deviceUUIDString;
    NSUInteger _lastEventID;
    MailBundleController *_controller;
    NSMutableArray *_loadedBundlesToUninstall;
    NSURL *_snapshotURL;
    NSMutableDictionary *_bundles;
    NSURL *_url;
}

+ (id)bundlesDirectoryWithURL:(id)arg1 controller:(id)arg2;
- (id)_initWithURL:(id)arg1 controller:(id)arg2;
- (id)_propertyListURL;
- (void)_uninstallLoadedBundle:(id)arg1;
- (void)_uninstallMismatchedBundles;
- (void)_uninstallUnloadedBundle:(id)arg1;
- (void)_writePropertyList;
@property(readonly, copy, nonatomic) NSArray *bundles;
- (void)dealloc;
- (id)description;
- (void)installBundle:(id)arg1;
- (void)uninstallBundle:(id)arg1;
@property(readonly, nonatomic) NSURL *url; // @synthesize url=_url;

@end

