//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


@class NSArray, NSError, WKBackForwardListItem, WKBrowsingContextController;

@protocol WKBrowsingContextLoadDelegate <NSObject>

@optional
- (void)browsingContextController:(WKBrowsingContextController *)arg1 didFailLoadWithError:(NSError *)arg2;
- (void)browsingContextController:(WKBrowsingContextController *)arg1 didFailProvisionalLoadWithError:(NSError *)arg2;
- (void)browsingContextController:(WKBrowsingContextController *)arg1 estimatedProgressChangedTo:(double)arg2;
- (void)browsingContextControllerDidChangeBackForwardList:(WKBrowsingContextController *)arg1 addedItem:(WKBackForwardListItem *)arg2 removedItems:(NSArray *)arg3;
- (void)browsingContextControllerDidCommitLoad:(WKBrowsingContextController *)arg1;
- (void)browsingContextControllerDidFinishLoad:(WKBrowsingContextController *)arg1;
- (void)browsingContextControllerDidFinishProgress:(WKBrowsingContextController *)arg1;
- (void)browsingContextControllerDidReceiveServerRedirectForProvisionalLoad:(WKBrowsingContextController *)arg1;
- (void)browsingContextControllerDidStartProgress:(WKBrowsingContextController *)arg1;
- (void)browsingContextControllerDidStartProvisionalLoad:(WKBrowsingContextController *)arg1;
@end
