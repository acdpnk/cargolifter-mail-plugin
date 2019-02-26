//
//  DAVRequests.m
//  DAVKit
//
//  Copyright Matt Rajca 2010. All rights reserved.
//

#import "DAVCopyRequest.h"
#import "DAVRequest+Private.h"

@implementation DAVCopyRequest

@synthesize destinationPath = _destinationPath;
@synthesize overwrite = _overwrite;

- (NSString *)method {
	return @"COPY";
}

- (NSURLRequest *)request {
	NSParameterAssert(_destinationPath != nil);
	
	NSURL *dp = [self concatenatedURLWithPath:_destinationPath];
	
	NSMutableURLRequest *req = [self newRequestWithPath:self.path
												 method:[self method]];
	
	[req setValue:[dp absoluteString] forHTTPHeaderField:@"Destination"];
	
	if (_overwrite)
		[req setValue:@"T" forHTTPHeaderField:@"Overwrite"];
	else
		[req setValue:@"F" forHTTPHeaderField:@"Overwrite"];
	
	return [req autorelease];
}

- (void)dealloc {
	[_destinationPath release];
	[super dealloc];
}

@end

