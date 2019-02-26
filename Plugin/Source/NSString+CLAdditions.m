// Copyright (C) 2019 Mailbutler GmbH
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
//  NSString+CLAdditions.m
//  CargoLifter
//
//  Created by Fabian Jäger on 30.01.12.
//  Copyright (c) 2012 Mailbutler. All rights reserved.
//

#import "NSString+CLAdditions.h"

#import "NSData+CLAdditions.h"
#import <CommonCrypto/CommonDigest.h>

@implementation NSString (CLAdditions)

// From <http://stackoverflow.com/questions/2018550/how-do-i-create-an-md5-hash-of-a-string-in-cocoa>
- (NSString*)MD5
{
    const char *cStr = self.UTF8String;
    unsigned char result[16];
    CC_MD5( cStr, (CC_LONG)strlen(cStr), result );
    return [NSString stringWithFormat:
             @"%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X",
             result[0], result[1], result[2], result[3],
             result[4], result[5], result[6], result[7],
             result[8], result[9], result[10], result[11],
             result[12], result[13], result[14], result[15]
             ].lowercaseString;
}

+ (NSString *)stringByEncodingBase64:(NSString *)plainText withCharacterEncoding:(NSStringEncoding)encoding
{
    NSData *plainTextData = [plainText dataUsingEncoding:encoding];
    NSString *base64String = [plainTextData base64EncodedString];
    return base64String;
}

+ (NSString *)stringByDecodingBase64:(NSString *)base64String withCharacterEncoding:(NSStringEncoding)encoding
{
    NSData *plainTextData = [NSData dataFromBase64String:base64String];
    NSString *plainText = [[NSString alloc] initWithData:plainTextData encoding:encoding];
    return plainText;
}

- (BOOL) containsString:(NSString*)string options:(NSStringCompareOptions)options
{
    if(!string)
        return NO;
    
    NSRange rng = [self rangeOfString:string options:options];
    return rng.location != NSNotFound;
}

- (NSString*)asciiString
{
    NSData *asciiStringData = [self dataUsingEncoding:NSASCIIStringEncoding allowLossyConversion:YES];
    
    return [[NSString alloc] initWithData:asciiStringData encoding:NSASCIIStringEncoding];
}

- (NSString *) urlEncodedQueryString
{
    return [self stringByAddingPercentEncodingWithAllowedCharacters:[NSCharacterSet URLQueryAllowedCharacterSet]];
}
- (NSString *) urlEncodedPathString
{
    return [self stringByAddingPercentEncodingWithAllowedCharacters:[NSCharacterSet URLPathAllowedCharacterSet]];
}

- (NSString *)sha1_digest
{
    NSData *data = [self dataUsingEncoding:NSUTF8StringEncoding];
    uint8_t digest[CC_SHA1_DIGEST_LENGTH];
    
    CC_SHA1(data.bytes, (CC_LONG)data.length, digest);
    
    NSMutableString *output = [NSMutableString stringWithCapacity:CC_SHA1_DIGEST_LENGTH * 2];
    
    for (int i = 0; i < CC_SHA1_DIGEST_LENGTH; i++)
    {
        [output appendFormat:@"%02x", digest[i]];
    }
    
    return output;
}

- (NSString*) trimmedContentID
{
    NSString* origContentID = self;
    
    NSString* trimmedContentID = [origContentID stringByReplacingOccurrencesOfString:@"<" withString:@""];
    trimmedContentID = [trimmedContentID stringByReplacingOccurrencesOfString:@">" withString:@""];
    
    if([trimmedContentID hasPrefix:@"cid:"])
    {
        trimmedContentID = [trimmedContentID substringFromIndex:4];
    }
    
    return trimmedContentID;
}

@end
