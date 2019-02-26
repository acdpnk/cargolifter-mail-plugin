//
//  DAVRequests.h
//  DAVKit
//
//  Copyright Matt Rajca 2010. All rights reserved.
//

#import "DAVRequest.h"

@interface DAVListingRequest : DAVRequest {
  @private
	NSUInteger _depth;
}

@property (assign) NSUInteger depth; /* default is 1 */

@end
