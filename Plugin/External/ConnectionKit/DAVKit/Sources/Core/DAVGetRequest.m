//
//  DAVRequests.m
//  DAVKit
//
//  Copyright Matt Rajca 2010. All rights reserved.
//

#import "DAVGetRequest.h"
#import "DAVRequest+Private.h"

@implementation DAVGetRequest

- (NSURLRequest *)request {
	return [[self newRequestWithPath:self.path method:@"GET"] autorelease];
}

- (id)resultForData:(NSData *)data {
	return data;
}

@end
