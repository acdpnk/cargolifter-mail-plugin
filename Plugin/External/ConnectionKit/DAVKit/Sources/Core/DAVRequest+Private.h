//
//  DAVRequest+Private.h
//  DAVKit
//
//  Copyright Matt Rajca 2010. All rights reserved.
//

#if TARGET_OS_IPHONE
    #import <MobileCoreServices/MobileCoreServices.h>
#else
    #import <CoreServices/CoreServices.h>
#endif

@class DAVSession;

@interface DAVRequest (Private)

- (NSMutableURLRequest *)newRequestWithPath:(NSString *)path method:(NSString *)method;

@end
