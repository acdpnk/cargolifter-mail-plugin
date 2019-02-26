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
//  NUKeychain.h
//
//  Created by Fabian Jäger on 05.06.07.
//  Copyright 2015 Mailbutler Software GmbH. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface NUKeychain : NSObject {
	
}

+ (BOOL)checkForExistanceOfKeychainItemWithLabel:(NSString *)itemLabel forAccount:(NSString *)accountName;
+ (BOOL)removeKeychainItemWithLabel:(NSString *)itemLabel forAccount:(NSString *)accountName;
+ (BOOL)setPassword:(NSString*)password forKeychainItemWithLabel:(NSString *)itemLabel forAccount:(NSString *)accountName;
+ (NSString *)passwordFromKeychainItemWithLabel:(NSString *)itemLabel forAccount:(NSString *)accountName;

@end
