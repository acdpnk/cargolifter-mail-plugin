//
//  DAVRequests.h
//  DAVKit
//
//  Copyright Matt Rajca 2010. All rights reserved.
//

#import "DAVRequest.h"


@protocol DAVPutRequestDelegate <DAVRequestDelegate>
@optional
- (void)webDAVRequest:(DAVRequest *)request didSendDataOfLength:(NSInteger)bytesWritten totalBytesWritten:(NSInteger)totalBytesWritten totalBytesExpectedToWrite:(NSInteger)totalBytesExpectedToWrite;
- (NSInputStream *)webDAVRequest:(DAVRequest *)request needNewBodyStream:(NSURLRequest *)request;
@end

@interface DAVPutRequest : DAVRequest {
  @private
    NSMutableURLRequest* _request;
}

+ (NSString*)MIMETypeForExtension:(NSString*)extension;

- (id)initWithPath:(NSString*)path originalRequest:(NSURLRequest*)request session:(DAVSession *)session delegate:(id <DAVRequestDelegate>)delegate;

- (NSUInteger)expectedLength;

@property(nonatomic, assign, readonly) id <DAVPutRequestDelegate> delegate;

@end
