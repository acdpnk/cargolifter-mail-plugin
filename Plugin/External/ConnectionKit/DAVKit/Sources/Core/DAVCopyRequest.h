//
//  DAVRequests.h
//  DAVKit
//
//  Copyright Matt Rajca 2010. All rights reserved.
//

#import "DAVRequest.h"

@interface DAVCopyRequest : DAVRequest {
  @private
	NSString *_destinationPath;
	BOOL _overwrite;
}

@property (copy) NSString *destinationPath;
@property (assign) BOOL overwrite;

@end
