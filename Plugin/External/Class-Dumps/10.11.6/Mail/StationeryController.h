//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


#import "WebFrameLoadDelegate-Protocol.h"
#import "WebResourceLoadDelegate-Protocol.h"

@class ComposeBackEnd, EditableWebMessageDocument, EditingMessageWebView, NSMutableArray, NSMutableDictionary, NSString, NSTimer, Stationery;

@interface StationeryController : NSObject <WebFrameLoadDelegate, WebResourceLoadDelegate>
{
    Stationery *_stationery;
    BOOL _stationeryLoaded;
    NSString *_currentColor;
    ComposeBackEnd *_composeBackEnd;
    NSMutableDictionary *_fontElementsWithColors;
    NSMutableArray *_colorsThatHaveBeenDisplayed;
    BOOL _isLoadingStationery;
    BOOL _isChangingStationeryColor;
    BOOL _isLoadingResources;
    BOOL _shouldAnimateTransitions;
    EditingMessageWebView *_webView;
    double _letterTopMargin;
    double _letterWidth;
    id _savedResourceLoadDelegate;
    id _savedFrameLoadDelegate;
    long long _numberOfResourcesNotYetLoaded;
    EditableWebMessageDocument *_messageDocument;
    NSTimer *_flushWindowTimer;
}

- (void)_finishLoadingStationery;
- (void)_timerDidFire:(id)arg1;
- (void)_webViewDidFinishLoadingAllResources;
- (void)changeStationeryColor:(id)arg1;
@property(copy, nonatomic) NSString *color;
@property(nonatomic) __weak ComposeBackEnd *composeBackEnd;
@property(retain, nonatomic) NSTimer *flushWindowTimer; // @synthesize flushWindowTimer=_flushWindowTimer;
@property(nonatomic) BOOL isChangingStationeryColor; // @synthesize isChangingStationeryColor=_isChangingStationeryColor;
@property(nonatomic) BOOL isLoadingResources; // @synthesize isLoadingResources=_isLoadingResources;
@property(nonatomic) BOOL isLoadingStationery; // @synthesize isLoadingStationery=_isLoadingStationery;
@property(readonly, nonatomic) BOOL isUpdatingWebView;
@property(nonatomic) double letterTopMargin; // @synthesize letterTopMargin=_letterTopMargin;
@property(nonatomic) double letterWidth; // @synthesize letterWidth=_letterWidth;
- (void)loadStationery:(id)arg1;
@property(retain, nonatomic) EditableWebMessageDocument *messageDocument; // @synthesize messageDocument=_messageDocument;
@property(nonatomic) long long numberOfResourcesNotYetLoaded; // @synthesize numberOfResourcesNotYetLoaded=_numberOfResourcesNotYetLoaded;
@property(retain, nonatomic) id savedFrameLoadDelegate; // @synthesize savedFrameLoadDelegate=_savedFrameLoadDelegate;
@property(retain, nonatomic) id savedResourceLoadDelegate; // @synthesize savedResourceLoadDelegate=_savedResourceLoadDelegate;
@property(nonatomic) BOOL shouldAnimateTransitions; // @synthesize shouldAnimateTransitions=_shouldAnimateTransitions;
@property(retain, nonatomic) Stationery *stationery;
@property(nonatomic) BOOL stationeryLoaded;
@property(retain, nonatomic) EditingMessageWebView *webView; // @synthesize webView=_webView;
- (void)showColorOptions;
- (id)stationeryFromCurrentMessageError:(id *)arg1;
- (void)userClickedOnStationeryBackground:(id)arg1;
- (void)webView:(id)arg1 didFailLoadWithError:(id)arg2 forFrame:(id)arg3;
- (void)webView:(id)arg1 didFinishLoadForFrame:(id)arg2;
- (void)webView:(id)arg1 didLoadResourceFromMemoryCache:(id)arg2 response:(id)arg3 length:(long long)arg4 fromDataSource:(id)arg5;
- (id)webView:(id)arg1 identifierForInitialRequest:(id)arg2 fromDataSource:(id)arg3;
- (void)webView:(id)arg1 resource:(id)arg2 didFinishLoadingFromDataSource:(id)arg3;

// Remaining properties
@property(readonly, copy) NSString *debugDescription;
@property(readonly, copy) NSString *description;
@property(readonly) NSUInteger hash;
@property(readonly) Class superclass;

@end
