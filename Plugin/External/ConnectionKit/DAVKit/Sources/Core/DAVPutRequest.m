//
//  DAVRequests.m
//  DAVKit
//
//  Copyright Matt Rajca 2010. All rights reserved.
//

#import "DAVPutRequest.h"
#import "DAVRequest+Private.h"

#import "DAVSession.h"


@implementation DAVPutRequest

+ (NSString*)MIMETypeForExtension:(NSString*)extension
{
    CFStringRef type = UTTypeCreatePreferredIdentifierForTag(kUTTagClassFilenameExtension, (CFStringRef)extension, NULL);
    NSString* mimeType = nil;
    if (type)
    {
        mimeType = (NSString*)UTTypeCopyPreferredTagWithClass(type, kUTTagClassMIMEType);
        CFRelease(type);
        [mimeType autorelease];
        CFMakeCollectable(mimeType);
    }
    if (!mimeType)
    {
        mimeType = @"application/octet-stream";
    }

    return mimeType;
}


- (id)initWithPath:(NSString*)path originalRequest:(NSURLRequest*)originalRequest session:(DAVSession *)session delegate:(id<DAVRequestDelegate>)delegate
{
    if ((self = [super initWithPath:path session:session delegate:delegate]))
    {

        _request = [originalRequest mutableCopy];

        if(![_request valueForHTTPHeaderField:@"Content-Length"])
        {
            NSData* data = [_request HTTPBody];
            NSAssert(data != nil, @"should have data if no length set");
            NSUInteger length = [data length];
            [_request setValue:[NSString stringWithFormat:@"%lu", (unsigned long)length] forHTTPHeaderField:@"Content-Length"];
        }

        NSString* MIMEType = [DAVPutRequest MIMETypeForExtension:[path pathExtension]];
        [_request setValue:MIMEType forHTTPHeaderField:@"Content-Type"];
        if (session.send100ContinueRequests) [_request setValue:@"100-Continue" forHTTPHeaderField:@"Expect"];

        [_request setHTTPMethod:@"PUT"];
        [_request setCachePolicy:NSURLRequestReloadIgnoringLocalCacheData];
        [_request setURL:[self concatenatedURLWithPath:path]];

        NSMutableIndexSet* indexes = [[NSMutableIndexSet alloc] init];
        [indexes addIndex:200]; // Microsoft-IIS/6.0 returns this when overwriting an existing file
        [indexes addIndex:201]; // The resource was created successfully
        [indexes addIndex:202]; // The resource will be created or deleted, but this has not happened yet
        [indexes addIndex:204]; // The server has fulfilled the request but does not need to return an entity body, and might return updated metadata.
        self.expectedStatuses = indexes;
        [indexes release];
    }

    return self;
}

@dynamic delegate;

- (NSURLRequest *)request {
    return _request;
}

- (NSUInteger)expectedLength
{
    return [[_request valueForHTTPHeaderField:@"Content-Length"] integerValue];
}

- (void)dealloc
{
	[_request release];

	[super dealloc];
}

- (void)connection:(NSURLConnection *)connection didSendBodyData:(NSInteger)bytesWritten totalBytesWritten:(NSInteger)totalBytesWritten totalBytesExpectedToWrite:(NSInteger)totalBytesExpectedToWrite
{
    if ([[self delegate] respondsToSelector:@selector(webDAVRequest:didSendDataOfLength:totalBytesWritten:totalBytesExpectedToWrite:)])
    {
        [[self delegate] webDAVRequest:self didSendDataOfLength:bytesWritten totalBytesWritten:totalBytesWritten totalBytesExpectedToWrite:totalBytesExpectedToWrite];
    }
}

- (NSInputStream *)connection:(NSURLConnection *)connection needNewBodyStream:(NSURLRequest *)request
{
    NSInputStream* result = nil;

    if ([[self delegate] respondsToSelector:@selector(webDAVRequest:needNewBodyStream:)])
    {
        result = [[self delegate] webDAVRequest:self needNewBodyStream:request];
    }

    return result;
}

@end
