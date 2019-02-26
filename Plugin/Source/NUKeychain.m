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
//  NUKeychain.m
//
//  Created by Fabian Jäger on 05.06.07.
//  Copyright 2015 Mailbutler Software GmbH. All rights reserved.
//

#import "NUKeychain.h"

#import <Security/Security.h>
#import <CoreFoundation/CoreFoundation.h>

@interface NUKeychain ()

+ (BOOL)_modifyKeychainItemWithLabel:(NSString *)itemLabel forAccount:(NSString *)accountName withNewPassword:(NSString *)newPassword;

@end


@implementation NUKeychain

+ (BOOL)checkForExistanceOfKeychainItemWithLabel:(NSString *)itemLabel forAccount:(NSString *)accountName
{
	// get password from keychain
    OSStatus status;
    
    status = SecKeychainFindGenericPassword (
                                             NULL,                               // default keychain
                                             (UInt32)itemLabel.length,                     // length of service name
                                             itemLabel.UTF8String,                 // service name
                                             (UInt32)accountName.length,    // length of account name
                                             accountName.UTF8String,// account name
                                             NULL,                  // length of password
                                             NULL,              // pointer to password data
                                             NULL                                // the item reference
                                             );
	
	return (status == noErr);
}

+ (BOOL)removeKeychainItemWithLabel:(NSString *)itemLabel forAccount:(NSString *)accountName
{
	if(![NUKeychain checkForExistanceOfKeychainItemWithLabel:itemLabel forAccount:accountName])
		return NO;
	
    // first get item from keychain
    OSStatus status;
    SecKeychainItemRef itemRef = nil;
    
    status = SecKeychainFindGenericPassword (
                                             NULL,                               // default keychain
                                             (UInt32)itemLabel.length,                     // length of service name
                                             itemLabel.UTF8String,                 // service name
                                             (UInt32)accountName.length,    // length of account name
                                             accountName.UTF8String,// account name
                                             NULL,                  // length of password
                                             NULL,              // pointer to password data
                                             &itemRef                                // the item reference
                                             );
    
    if(!itemRef || status != noErr)
        return NO;
    
    status = SecKeychainItemDelete(itemRef);
    
    if(itemRef)
        CFRelease(itemRef);
	
	return (status == noErr);
}

+ (BOOL)setPassword:(NSString*)password forKeychainItemWithLabel:(NSString *)itemLabel forAccount:(NSString *)accountName
{
	if([NUKeychain checkForExistanceOfKeychainItemWithLabel:itemLabel forAccount:accountName])
    {
		return [NUKeychain _modifyKeychainItemWithLabel:itemLabel forAccount:accountName withNewPassword:password];
    }
    
	// create our new item
    OSStatus status;
    status = SecKeychainAddGenericPassword (
                                            NULL,                               // default keychain
                                            (UInt32)itemLabel.length,                     // length of service name
                                            itemLabel.UTF8String,                 // service name
                                            (UInt32)accountName.length,    // length of account name
                                            accountName.UTF8String,// account name
                                            (UInt32)password.length,                  // length of password
                                            password.UTF8String,              // pointer to password data
                                            NULL                                // the item reference
                                            );
	
    if (status != 0) {
        NSLog(@"📯 CARGOLIFTER: Error creating new item: %ld\n", (long)status);
    }
    
	return (status == noErr);
}

+ (NSString *)passwordFromKeychainItemWithLabel:(NSString *)itemLabel forAccount:(NSString *)accountName
{
	if(![NUKeychain checkForExistanceOfKeychainItemWithLabel:itemLabel forAccount:accountName])
		return nil;
	
    // get password from keychain
    OSStatus status;
    void *passwordData = NULL;
    UInt32 passwordLength;
    NSString *passwordString = nil;
    
    status = SecKeychainFindGenericPassword (
                                              NULL,                               // default keychain
                                              (UInt32)itemLabel.length,                     // length of service name
                                              itemLabel.UTF8String,                 // service name
                                              (UInt32)accountName.length,    // length of account name
                                              accountName.UTF8String,// account name
                                              &passwordLength,                  // length of password
                                              &passwordData,              // pointer to password data
                                              NULL                                // the item reference
                                              );
    
    if (status == noErr)
    {
        if( passwordLength > 0 )
            passwordString = [[NSString alloc] initWithBytes:passwordData length:passwordLength encoding:NSUTF8StringEncoding];
        
        //Free the data allocated by SecKeychainFindGenericPassword:
        SecKeychainItemFreeContent ( NULL, passwordData );
    }
	
    return passwordString;
}

#pragma mark Private Methods

+ (BOOL)_modifyKeychainItemWithLabel:(NSString *)itemLabel forAccount:(NSString *)accountName withNewPassword:(NSString *)newPassword
{
	if(![NUKeychain checkForExistanceOfKeychainItemWithLabel:itemLabel forAccount:accountName])
		return NO;
    
    // first get item from keychain
    OSStatus status;
    SecKeychainItemRef itemRef = nil;
    
    status = SecKeychainFindGenericPassword (
                                             NULL,                               // default keychain
                                             (UInt32)itemLabel.length,                     // length of service name
                                             itemLabel.UTF8String,                 // service name
                                             (UInt32)accountName.length,    // length of account name
                                             accountName.UTF8String,// account name
                                             NULL,                  // length of password
                                             NULL,              // pointer to password data
                                             &itemRef                                // the item reference
                                             );
    
    if(!itemRef || status != noErr)
        return NO;
	
    // update item with new password
    void * password = (void*)newPassword.UTF8String;
    UInt32 passwordLength = (UInt32)newPassword.length;
    
    status = SecKeychainItemModifyAttributesAndData (
                                                     itemRef,         // the item reference
                                                     NULL,            // no change to attributes
                                                     passwordLength,  // length of password
                                                     password         // pointer to password data
                                                     );
    
    if (itemRef)
        CFRelease(itemRef);
    
    return (status == noErr);
}


@end
