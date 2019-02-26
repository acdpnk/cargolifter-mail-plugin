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
//  NSString+CLAdditions.h
//  CargoLifter
//
//  Created by Fabian Jäger on 30.01.12.
//  Copyright (c) 2012 Mailbutler. All rights reserved.
//

#import <Foundation/Foundation.h>

enum {
    kUnitStringBinaryUnits     = 1 << 0,
    kUnitStringOSNativeUnits   = 1 << 1,
    kUnitStringLocalizedFormat = 1 << 2
};

@interface NSString (CLAdditions)

@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSString *MD5;

@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSString *sha1_digest;

+ (NSString *)stringByDecodingBase64:(NSString *)base64String withCharacterEncoding:(NSStringEncoding)encoding;
+ (NSString *)stringByEncodingBase64:(NSString *)plainText withCharacterEncoding:(NSStringEncoding)encoding;
- (BOOL) containsString:(NSString *) string options:(NSStringCompareOptions) options;

- (NSString*)asciiString;


@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSString *urlEncodedQueryString;
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSString *urlEncodedPathString;

// Mail-specific
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSString *trimmedContentID;

@end
