//
//  DAVSession.h
//  DAVKit
//
//  Copyright Matt Rajca 2010. All rights reserved.
//

@class DAVBaseRequest;
@protocol DAVSessionDelegate;

/* All paths are relative to the root of the server */


@interface DAVSession : NSObject {
  @private
	NSURL *_rootURL;
	BOOL _allowUntrustedCertificate;
    BOOL _send100ContinueRequests;
    
    id <DAVSessionDelegate> _delegate;
}

@property (readonly) NSURL *rootURL;
@property (assign) BOOL allowUntrustedCertificate;
@property (nonatomic) BOOL send100ContinueRequests;
@property (nonatomic, readonly, assign) id <DAVSessionDelegate> delegate;

/*
 The root URL should include a scheme and host, followed by any root paths
 **NOTE: omit the trailing slash (/)**
 Example: http://idisk.me.com/steve
*/
- (id)initWithRootURL:(NSURL *)url delegate:(id <DAVSessionDelegate>)delegate;

- (void)resetCredentialsCache;

// Convenience methods that call through to the delegate
- (void)appendFormatToReceivedTranscript:(NSString *)format, ...;
- (void)appendFormatToSentTranscript:(NSString *)format, ...;
- (void)appendFormatToTranscript:(NSString *)format arguments:(va_list)argList sent:(BOOL)sent;

@end


@protocol DAVSessionDelegate <NSObject>
@optional

- (void)webDAVSession:(DAVSession *)session didReceiveChallenge:(NSURLAuthenticationChallenge *)challenge completionHandler:(void (^)(NSInteger disposition, NSURLCredential *credential))completionHandler;

// The sent argument indicates whether the data was sent or received
- (void)webDAVSession:(DAVSession *)session appendStringToTranscript:(NSString *)string sent:(BOOL)sent;

@end
