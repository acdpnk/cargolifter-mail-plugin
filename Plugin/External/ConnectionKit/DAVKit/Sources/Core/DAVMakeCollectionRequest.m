//
//  DAVRequests.m
//  DAVKit
//
//  Copyright Matt Rajca 2010. All rights reserved.
//

#import "DAVMakeCollectionRequest.h"
#import "DAVRequest+Private.h"

@implementation DAVMakeCollectionRequest

- (id)initWithPath:(NSString *)aPath session:(DAVSession *)session delegate:(id<DAVRequestDelegate>)delegate
{
    if ((self = [super initWithPath:aPath session:session delegate:delegate]) != nil)
    {
        self.expectedStatuses = [NSIndexSet indexSetWithIndex:201];
    }

    return self;
}

- (NSURLRequest *)request {
	return [[self newRequestWithPath:self.path method:@"MKCOL"] autorelease];
}

@end
