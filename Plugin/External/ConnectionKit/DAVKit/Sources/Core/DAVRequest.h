//
//  DAVRequest.h
//  DAVKit
//
//  Copyright Matt Rajca 2010. All rights reserved.
//

#import "DAVBaseRequest.h"

@protocol DAVRequestDelegate;

/* codes returned are HTTP status codes */
extern NSString *const DAVClientErrorDomain;

@interface DAVRequest : DAVBaseRequest {
  @private
	NSString *_path;
	NSURLConnection *_connection;
    NSMutableDictionary *_pendingCredentials;
	NSMutableData *_data;
	BOOL _done;
	BOOL _executing;
    NSIndexSet* _expectedStatuses;
    id <DAVRequestDelegate> _delegate;
}

/**
 Delegate is held onto until the request finishes
 */
- (id)initWithPath:(NSString *)aPath session:(DAVSession *)session delegate:(id <DAVRequestDelegate>)delegate;

@property(readonly) NSString *path;
@property(nonatomic, strong) NSIndexSet* expectedStatuses;
@property(nonatomic, strong, readonly) id <DAVRequestDelegate> delegate;

- (NSURL *)concatenatedURLWithPath:(NSString *)aPath;

/* must be overriden by subclasses */
- (NSURLRequest *)request;

/* optional override */
- (id)resultForData:(NSData *)data;

@end


@protocol DAVRequestDelegate < NSObject >

// The error can be a NSURLConnection error or a WebDAV error
- (void)request:(DAVRequest *)aRequest didFailWithError:(NSError *)error;

// The resulting object varies depending on the request type
- (void)request:(DAVRequest *)aRequest didSucceedWithResult:(id)result;

@optional

- (void)requestDidBegin:(DAVRequest *)aRequest;

- (NSURLRequest *)request:(DAVRequest *)aRequest willSendRequest:(NSURLRequest *)request redirectResponse:(NSURLResponse *)redirectResponse;

@end
