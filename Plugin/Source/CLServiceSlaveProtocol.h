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
//  CLServiceSlaveProtocol.h
//  CargoLifter
//
//  Created by Fabian Jäger on 05/10/15.
//  Copyright © 2015 Mailbutler. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSUInteger, CLServiceAuthError) {
    CLServiceAuthErrorInvalidCredentials,
    CLServiceAuthErrorCredentialsNotFound,
    CLServiceAuthErrorUserInvalid,
    CLServiceAuthErrorPasswordIncorrect,
    CLServiceAuthErrorUserInactive,
    CLServiceAuthErrorUserIsGuest,
    CLServiceAuthErrorUnknownError,
    CLServiceAuthErrorMissingAuthCode,
    CLServiceAuthErrorSecurityChallenge,
    CLServiceAuthErrorCreateDirectory,
};

#define CLServiceAuthErrorDomain   @"com.mailbutler.CargoLifter.Service.Auth"

@class CLService;

@protocol CLServiceSlaveAuthenticationDelegate <NSObject>

@required
- (void)didFinishAuthenticationWithError:(NSError*)error;

@end

@protocol CLServiceSlaveProtocol <NSObject>

@required
- (instancetype) initWithService:(CLService*)service;

@optional

@property (weak) id<CLServiceSlaveAuthenticationDelegate> authDelegate;
- (void) authenticate;
- (void) authenticateWithWindow:(NSWindow*)window;
- (void) authenticateWithCode:(NSString*)code;

- (void) deauthenticate;

@end

@protocol CLUploadServiceSlaveProtocol <NSObject>

@required
- (void) uploadFile:(NSString*)localFilePath createPublicLink:(BOOL)createPublicLink rawFileAccess:(BOOL)rawFile;
- (void) cancelUpload;
- (BOOL) allowsRawAccess;

@end
