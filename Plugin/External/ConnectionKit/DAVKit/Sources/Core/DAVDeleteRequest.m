//
//  DAVRequests.m
//  DAVKit
//
//  Copyright Matt Rajca 2010. All rights reserved.
//

#import "DAVDeleteRequest.h"

#import "DAVRequest+Private.h"

@implementation DAVDeleteRequest

- (id)initWithPath:(NSString *)aPath session:(DAVSession *)session delegate:(id<DAVRequestDelegate>)delegate
{
    if ((self = [super initWithPath:aPath session:session delegate:delegate]) != nil)
    {
        NSMutableIndexSet *statuses = [NSMutableIndexSet indexSetWithIndex:204];
        [statuses addIndex:200];    // Have found Microsoft servers return this after a successful deletion https://karelia.fogbugz.com/f/cases/252461
        self.expectedStatuses = statuses;
    }

    return self;
}

- (NSURLRequest *)request {
	return [[self newRequestWithPath:self.path method:@"DELETE"] autorelease];
}

@end
