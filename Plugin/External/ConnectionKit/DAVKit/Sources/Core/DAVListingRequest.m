//
//  DAVRequests.m
//  DAVKit
//
//  Copyright Matt Rajca 2010. All rights reserved.
//

#import "DAVListingRequest.h"
#import "DAVListingParser.h"
#import "DAVRequest+Private.h"

@implementation DAVListingRequest

@synthesize depth = _depth;

- (id)initWithPath:(NSString *)aPath session:(DAVSession *)session delegate:(id <DAVRequestDelegate>)delegate;
{
	self = [super initWithPath:aPath session:session delegate:delegate];
	if (self) {
		_depth = 1;
	}
	return self;
}

- (NSURLRequest *)request {
	NSMutableURLRequest *req = [self newRequestWithPath:self.path method:@"PROPFIND"];
	
	if (_depth > 1) {
		[req setValue:@"infinity" forHTTPHeaderField:@"Depth"];
	}
	else {
		[req setValue:[NSString stringWithFormat:@"%ld", (unsigned long) _depth] forHTTPHeaderField:@"Depth"];
	}
	
	[req setValue:@"text/xml" forHTTPHeaderField:@"Content-Type"];
	
	NSString *xml = @"<?xml version=\"1.0\" encoding=\"utf-8\" ?>\n"
					@"<D:propfind xmlns:D=\"DAV:\"><D:allprop/></D:propfind>";

    [req setValue:[NSString stringWithFormat:@"%ld", (unsigned long)xml.length] forHTTPHeaderField:@"Content-Length"];

	[req setHTTPBody:[xml dataUsingEncoding:NSUTF8StringEncoding]];
	
	return [req autorelease];
}

- (id)resultForData:(NSData *)data {
    NSArray *items = nil;
    NSLog(@"%@", [[[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding] autorelease]);
    if ([data length] > 0) {
        DAVListingParser *p = [[DAVListingParser alloc] initWithData:data];

        NSError *error = nil;
        items = [p parse:&error];

        if (error) {
#ifdef DEBUG
			NSLog(@"XML Parse error: %@", error);
#endif
        }
        
        [p release];
    }
    else {
#ifdef DEBUG
        NSLog(@"Got back nil/empty data");
#endif
    }

	return items;
}

@end

