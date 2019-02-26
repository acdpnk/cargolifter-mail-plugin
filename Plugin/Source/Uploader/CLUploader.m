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
//  CLUploader.m
//
//  Created by Fabian Jäger on 09.04.13.
//  Copyright (c) 2013 Mailbutler. All rights reserved.
//

#import "CLUploader.h"

#import "CLDropboxUploader.h"
#import "CLGoogleDriveUploader.h"
#import "CLCloudAppUploader.h"
#import "CLDroplrUploader.h"
#import "CLDropmarkUploader.h"
#import "CLMediaFireUploader.h"
#import "CLGenericUploader.h"
#import "CLBoxUploader.h"
#import "CLOwnCloudUploader.h"
#import "CLOneDriveUploader.h"

@implementation CLUploader

- (instancetype) init
{
    return [self initWithService:nil];
}

- (instancetype) initWithService:(CLService*)service
{
    if(self = [super init])
    {
        self.service = service;
    }
    return self;
}

// need to be implemented in derived classes
- (void) uploadFile:(NSString*)localFilePath createPublicLink:(BOOL)createPublicLink rawFileAccess:(BOOL)rawFile { NSAssert(NO, @"This method must be implemented in base class!"); return; }
- (void) cancelUpload { self.busy = NO; self.canceled = YES; return; }
- (void) authenticate { NSAssert(NO, @"This method must be implemented in base class!");  return; }

- (BOOL) allowsRawAccess
{
    switch(self.service.serviceType)
    {
        case CLBoxService:
        case CLOneDriveService:
            return NO;
        default:
            return YES;
    }
}

+ (Class)classForServiceType:(CLServiceType)serviceType
{
    switch(serviceType)
    {
        case CLDropboxService:
            return [CLDropboxUploader class];
            break;
        case CLCloudAppService:
            return [CLCloudAppUploader class];
            break;
        case CLGenericService:
            return [CLGenericUploader class];
            break;
        case CLDroplrService:
            return [CLDroplrUploader class];
            break;
        case CLDropmarkService:
            return [CLDropmarkUploader class];
            break;
        case CLMediafireService:
            return [CLMediaFireUploader class];
            break;
        case CLBoxService:
            return [CLBoxUploader class];
            break;
        case CLGoogleDriveService:
            return [CLGoogleDriveUploader class];
            break;
        case CLOwnCloudService:
            return [CLOwnCloudUploader class];
            break;
        case CLOneDriveService:
            return [CLOneDriveUploader class];
            break;
        default:
            NSAssert(NO, @"Invalid class type requested: %d", serviceType);
            return nil;
            break;
    }
}

+ (NSString*)localizedErrorDescriptionForErrorCode:(CLServiceAuthError)errorCode
{
    switch (errorCode) {
        case CLServiceAuthErrorInvalidCredentials:
            return NSLocalizedString(@"Your login information is incomplete.", nil);
        case CLServiceAuthErrorPasswordIncorrect:
            return NSLocalizedString(@"The provided password is incorrect.", nil);
        case CLServiceAuthErrorUnknownError:
            return NSLocalizedString(@"An unknown error occurred during authentication.", nil);
        case CLServiceAuthErrorUserInactive:
            return NSLocalizedString(@"The user account is inactive.", nil);
        case CLServiceAuthErrorUserInvalid:
            return NSLocalizedString(@"The provided login is invalid", nil);
        case CLServiceAuthErrorUserIsGuest:
            return NSLocalizedString(@"The user account is not active yet.", nil);
        case CLServiceAuthErrorCreateDirectory:
            return NSLocalizedString(@"Cannot create CargoLifter directory for this service. Authentication failed.", nil);
        case CLServiceAuthErrorCredentialsNotFound:
            return NSLocalizedString(@"Your login information is incomplete.", nil);
        case CLServiceAuthErrorMissingAuthCode:
            return NSLocalizedString(@"Authentication is missing.", nil);
        case CLServiceAuthErrorSecurityChallenge:
            return NSLocalizedString(@"Invalid security challenge. Cannot authenticate with server.", nil);
    }
}

- (NSString *)MIMETypeFileName:(NSString *)path defaultMIMEType:(NSString *)defaultType
{
    NSString *result = defaultType;
    NSString *extension = path.pathExtension;
    CFStringRef uti = UTTypeCreatePreferredIdentifierForTag(kUTTagClassFilenameExtension, (__bridge CFStringRef)extension, NULL);
    if (uti)
    {
        CFStringRef cfMIMEType = UTTypeCopyPreferredTagWithClass(uti, kUTTagClassMIMEType);
        if (cfMIMEType)
        {
            result = CFBridgingRelease(cfMIMEType);
        }
        CFRelease(uti);
    }
    return result;
}

@end
