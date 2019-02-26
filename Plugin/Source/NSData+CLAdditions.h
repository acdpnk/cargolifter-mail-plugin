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


#import <Foundation/Foundation.h>

void *NewBase64Decode(
	const char *inputBuffer,
	size_t length,
	size_t *outputLength);

char *NewBase64Encode(
	const void *inputBuffer,
	size_t length,
	bool separateLines,
	size_t *outputLength);

@interface NSData (CLAdditions)

+ (NSData *)dataFromBase64String:(NSString *)aString;
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSString *base64EncodedString;
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSString *base64EncodedStringWithLineBreaks;

+(NSData *)MD5Digest:(NSData *)input;
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSData *MD5Digest;

+(NSString *)MD5HexDigest:(NSData *)input;
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSString *MD5HexDigest;

+(NSData *)SHA256Digest:(NSData *)input;
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSData *SHA256Digest;

+(NSString *)SHA256HexDigest:(NSData *)input;
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSString *SHA256HexDigest;

+ (NSData *)randomDataWithBytes:(NSUInteger)length;

+ (NSData*)HMACSHA1DigestOfString:(NSString*)toHash withKey:(NSString*)key;

@end
