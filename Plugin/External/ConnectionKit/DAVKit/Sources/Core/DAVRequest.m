//
//  DAVRequest.m
//  DAVKit
//
//  Copyright Matt Rajca 2010. All rights reserved.
//

#import "DAVRequest.h"

#import "DAVSession.h"

@interface DAVRequest ()

- (void)_didFail:(NSError *)error;
- (void)_didFinish;

@end


@implementation DAVRequest


NSString *const DAVClientErrorDomain = @"org.w3.http";

#define DEFAULT_TIMEOUT 60

- (id)initWithPath:(NSString *)aPath session:(DAVSession *)session delegate:(id <DAVRequestDelegate>)delegate;
{
	NSParameterAssert(aPath != nil);
	
	self = [self initWithSession:session];
	if (self) {
		_path = [aPath copy];
        _delegate = [delegate retain];  // retained till finish running/cancelled
        _pendingCredentials = [[NSMutableDictionary alloc] init];
	}
	return self;
}

@synthesize expectedStatuses = _expectedStatuses;
@synthesize path = _path;
@synthesize delegate = _delegate;

- (NSURL *)concatenatedURLWithPath:(NSString *)aPath {
	NSParameterAssert(aPath != nil);
    
    // According to the WebDAV spec http://www.webdav.org/specs/rfc4918.html#url-handling (as best I understand it)
    // resource "href"s received from servers should be ready to be resolved by NSURL as-is,
    // relative to the server URL.
    // Previously we had code here which distinguished between relative and absolute paths, and
    // handled them differently
    // In both cases, we're going to some trouble to escape any odd characters in the ref
    // I _think_ that's unecessary for things received from the server, but don't have any hard data
    // on the subject, sorry
    // Plus, it seems we use this method for some request URL generation. Perhaps the two should be
    // handled separately. I don't know. Going with this one fairly generic implementation for now.
	
        CFStringRef escaped = CFURLCreateStringByAddingPercentEscapes(NULL,
                                                                      (CFStringRef)aPath,
                                                                      NULL,
                                                                      CFSTR(";?#"), // otherwise e.g. ? character would be misinterpreted as query
                                                                      kCFStringEncodingUTF8);
        
        NSURL *result = [NSURL URLWithString:(NSString *)escaped relativeToURL:self.session.rootURL];
        CFRelease(escaped);
        return result;
}

- (BOOL)isConcurrent {
	return YES;
}

- (BOOL)isExecuting {
	return _executing;
}

- (BOOL)isFinished {
	return _done;
}

- (void)cancel;
{
    [super cancel];
    [_connection cancel];
    [_delegate release]; _delegate = nil;
}

- (void)start {
	if (![NSURLConnection instancesRespondToSelector:@selector(setDelegateQueue:)] &&
        ![NSThread isMainThread])
    {
		[self performSelectorOnMainThread:@selector(start) 
							   withObject:nil waitUntilDone:NO];
		
		return;
	}
	
	[self willChangeValueForKey:@"isExecuting"];
	
	_executing = YES;
	_connection = [[NSURLConnection alloc] initWithRequest:[self request]
                                                  delegate:self
                                          startImmediately:NO];
    
    if ([_connection respondsToSelector:@selector(setDelegateQueue:)])
    {
        static NSOperationQueue *delegateQueue;
        static dispatch_once_t onceToken;
        dispatch_once(&onceToken, ^{
            delegateQueue = [[NSOperationQueue alloc] init];
            delegateQueue.maxConcurrentOperationCount = 1;
        });
        
        [_connection setDelegateQueue:delegateQueue];
    }
    else
    {
        [_connection scheduleInRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
    }
    
    [_connection start];
	
	if ([_delegate respondsToSelector:@selector(requestDidBegin:)])
		[_delegate requestDidBegin:self];
	
	[self didChangeValueForKey:@"isExecuting"];
}

- (NSURLRequest *)request {
	@throw [NSException exceptionWithName:NSInternalInconsistencyException
								   reason:@"Subclasses of DAVRequest must override 'request'"
								 userInfo:nil];
	
	return nil;
}

- (id)resultForData:(NSData *)data {
	return nil;
}

- (void)appendResponseToTranscript:(NSURLResponse *)response;
{
    if ([response isKindOfClass:[NSHTTPURLResponse class]])
    {
        NSHTTPURLResponse *httpResponse = (NSHTTPURLResponse *)response;
        NSInteger code = httpResponse.statusCode;
        [self.session appendFormatToReceivedTranscript:@"%i %@", code, [response.class localizedStringForStatusCode:code]];
    }
}

- (NSURLRequest *)connection:(NSURLConnection *)connection willSendRequest:(NSURLRequest *)request redirectResponse:(NSURLResponse *)redirectResponse;
{
    NSString* redirectString;
    if (redirectResponse)
    {
        // NSURLConnection has helpfully stripped out all the useful stuff from the request,
        // so we make a copy of the original one, and replace just the URL with the redirected one
        NSMutableURLRequest* newRequest = [connection.originalRequest mutableCopy];
        newRequest.URL = request.URL;
        redirectString = [NSString stringWithFormat:@" (redirected to %@)", [request URL]];
        request = [newRequest autorelease];
    }
    else
    {
        redirectString = @"";
    }
    
    // Let delegate have a say too
    if ([self.delegate respondsToSelector:@selector(request:willSendRequest:redirectResponse:)])
    {
        request = [self.delegate request:self willSendRequest:request redirectResponse:redirectResponse];
    }

    [[self session] appendFormatToSentTranscript:@"%@ %@%@", [request HTTPMethod], [[request URL] path], redirectString];     // TODO: Include HTTP version

    return request;
}

- (void)connection:(NSURLConnection *)connection didReceiveData:(NSData *)data {
	[_data appendData:data];
}

- (void)connection:(NSURLConnection *)connection didFailWithError:(NSError *)error {
	[self _didFail:error];
}

- (void)connection:(NSURLConnection *)connection didReceiveResponse:(NSURLResponse *)response
{
	if (_data)
	{
		[_data setLength:0];
	}
	else
	{
		_data = [[NSMutableData alloc] init];
	}
	
	NSHTTPURLResponse *resp = (NSHTTPURLResponse *)response;
	NSInteger code = [resp statusCode];
    NSString *description = [resp.class localizedStringForStatusCode:code];
    
    // Store any pending credentials
    if (code != 401)
    {
        [_pendingCredentials enumerateKeysAndObjectsUsingBlock:^(NSURLProtectionSpace *aSpace, NSURLCredential *aCredential, BOOL *stop) {
            [[NSURLCredentialStorage sharedCredentialStorage] setCredential:aCredential forProtectionSpace:aSpace];
        }];
        
        [_pendingCredentials removeAllObjects];
    }
    
    // Report to transcript
    [self appendResponseToTranscript:response];
	
	if ((code >= 400) || (self.expectedStatuses && ![self.expectedStatuses containsIndex:code])) {
		[_connection cancel];
		
        // TODO: Formalize inclusion of response
		NSError *error = [NSError errorWithDomain:DAVClientErrorDomain
											 code:code
										 userInfo:@{ NSLocalizedFailureReasonErrorKey : description,
                                                     @"response" : response }];
		
		[self _didFail:error];
	}
}

- (BOOL)connectionShouldUseCredentialStorage:(NSURLConnection *)connection;
{
    // Insist we receive all auth challenges so can include them in the transcript
    return NO;
}

- (BOOL)connection:(NSURLConnection *)connection canAuthenticateAgainstProtectionSpace:(NSURLProtectionSpace *)protectionSpace {
	BOOL result = [protectionSpace.authenticationMethod isEqualToString:NSURLAuthenticationMethodDefault] ||
	[protectionSpace.authenticationMethod isEqualToString:NSURLAuthenticationMethodHTTPBasic] ||
	[protectionSpace.authenticationMethod isEqualToString:NSURLAuthenticationMethodHTTPDigest] ||
	[protectionSpace.authenticationMethod isEqualToString:NSURLAuthenticationMethodServerTrust];
	
	return result;
}

- (void)connection:(NSURLConnection *)connection didReceiveAuthenticationChallenge:(NSURLAuthenticationChallenge *)challenge
{
    // Log the challenge's response object
    NSURLResponse *response = challenge.failureResponse;
    [self appendResponseToTranscript:response];
	
    
    id <DAVSessionDelegate> delegate = self.session.delegate;
    if ([delegate respondsToSelector:@selector(webDAVSession:didReceiveChallenge:completionHandler:)])
    {
        [delegate webDAVSession:self.session didReceiveChallenge:challenge completionHandler:^(NSInteger disposition, NSURLCredential *credential) {
            
            switch (disposition)
            {
                case 1: // NSURLSessionAuthChallengePerformDefaultHandling
                    credential = challenge.proposedCredential;
                    
                case 0: // NSURLSessionAuthChallengeUseCredential
                    [challenge.sender useCredential:credential forAuthenticationChallenge:challenge];
                    
                    // Add to transcript
                    if (response)
                    {
                        NSURLRequest *request = self.request;
                        [self.session appendFormatToSentTranscript:@"%@ %@", request.HTTPMethod, request.URL.path];
                    }
                    
                    // Because of our -connectionShouldUseCredentialStorage: implementation,
                    // the URL Loading System won't respect the credential's persistence,
                    // which leaves it up to us to handle once the connection is successful
                    if (credential) [_pendingCredentials setObject:credential forKey:challenge.protectionSpace];
                    break;
                    
                default:
                    [challenge.sender cancelAuthenticationChallenge:challenge];
                    break;
            }
        }];
        return;
    }
    
	if ([challenge.protectionSpace.authenticationMethod isEqualToString:NSURLAuthenticationMethodServerTrust])
    {
		if (self.session.allowUntrustedCertificate)
			[challenge.sender useCredential:[NSURLCredential credentialForTrust:challenge.protectionSpace.serverTrust]
				 forAuthenticationChallenge:challenge];
		
		[challenge.sender continueWithoutCredentialForAuthenticationChallenge:challenge];
	}
    else
    {
		if ([challenge previousFailureCount] == 0) {
			[[challenge sender] useCredential:[challenge proposedCredential] forAuthenticationChallenge:challenge];
		} else {
			// Wrong login/password
			[[challenge sender] cancelAuthenticationChallenge:challenge];
		}
	}
}

- (void)_didFail:(NSError *)error {
	if ([_delegate respondsToSelector:@selector(request:didFailWithError:)]) {
		[_delegate request:self didFailWithError:[[error retain] autorelease]];
	}
	
	[self _didFinish];
}

- (void)_didFinish {
	[self willChangeValueForKey:@"isExecuting"];
	[self willChangeValueForKey:@"isFinished"];
	
	_done = YES;
	_executing = NO;
	
	[self didChangeValueForKey:@"isExecuting"];
	[self didChangeValueForKey:@"isFinished"];
    
    [_delegate release]; _delegate = nil;
}

- (void)connectionDidFinishLoading:(NSURLConnection *)connection {
    if ([_delegate respondsToSelector:@selector(request:didSucceedWithResult:)]) {
        id result = [self resultForData:_data];

        [_delegate request:self didSucceedWithResult:[[result retain] autorelease]];
    }
    
    [self _didFinish];
}

- (void)dealloc {
	[_path release];
	[_connection release];
    [_pendingCredentials release];
	[_data release];
    [_expectedStatuses release];
	
	[super dealloc];
}

@end


@implementation DAVRequest (Private)

- (NSMutableURLRequest *)newRequestWithPath:(NSString *)path method:(NSString *)method {
	NSURL *url = [self concatenatedURLWithPath:path];
	
	NSMutableURLRequest *request = [[NSMutableURLRequest alloc] initWithURL:url];
	[request setHTTPMethod:method];
	[request setCachePolicy:NSURLRequestReloadIgnoringLocalCacheData];
    [request setTimeoutInterval:DEFAULT_TIMEOUT];
	
	return request;
}

@end
