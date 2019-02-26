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
//  CLService.m
//  CargoLifter
//
//  Created by Fabian Jäger on 18/09/15.
//  Copyright © 2015 Mailbutler. All rights reserved.
//

#import "CLService.h"

#import "NSImage+CLAdditions.h"
#import "NSString+CLAdditions.h"

#import "CLServicesManager.h"
#import "NUKeychain.h"

#import "CLUploader.h"

@interface CLService ()
{
    NSString* _uniqueIdentifier;
    BOOL _linked;
    id<CLServiceSlaveProtocol> _slave;
}

@property (readonly) NSString* identifier;

- (void) savePasswordInKeychain;
- (void) removePasswordFromKeychain;
@end

@implementation CLService

#pragma mark Type Methods

+ (NSString*) nameForServiceType:(CLServiceType)type
{
    switch(type)
    {
        case CLBoxService:
            return @"Box";
        case CLCloudAppService:
            return @"CloudApp";
        case CLDropboxService:
            return @"Dropbox";
        case CLDroplrService:
            return @"Droplr";
        case CLDropmarkService:
            return @"Dropmark";
        case CLGenericService:
            return @"FTP/SFTP/WebDAV";
        case CLGoogleDriveService:
            return @"Google Drive";
        case CLMediafireService:
            return @"MediaFire";
        case CLOwnCloudService:
            return @"ownCloud";
        case CLOneDriveService:
            return @"OneDrive";
        case CLNumServices:
        default:
            return nil;
    }
}

+ (NSString*) identifierForServiceType:(CLServiceType)type
{
    switch(type)
    {
        case CLBoxService:
            return @"Box";
        case CLCloudAppService:
            return @"CloudApp";
        case CLDropboxService:
            return @"Dropbox";
        case CLDroplrService:
            return @"Droplr";
        case CLDropmarkService:
            return @"Dropmark";
        case CLGenericService:
            return @"FTP";
        case CLGoogleDriveService:
            return @"GoogleDrive";
        case CLMediafireService:
            return @"MediaFire";
        case CLOwnCloudService:
            return @"OwnCloud";
        case CLOneDriveService:
            return @"OneDrive";
        case CLNumServices:
        default:
            return nil;
    }
}

+ (NSImage*)iconForServiceType:(CLServiceType)type
{
    NSString* identifier = [self identifierForServiceType:type];
    return [NSImage cl_pluginImageNamed:[identifier stringByAppendingString:@"_Icon"]];
}

+ (BOOL) isDeletableServiceType:(CLServiceType)type
{
    return YES;
}

+ (BOOL) allowsMultipleOfServiceType:(CLServiceType)type
{
    return YES;
}

#pragma mark Service Methods

- (instancetype) init { return [self initWithServiceType:CLNumServices]; }

- (instancetype) initWithServiceType:(CLServiceType)type
{
    if( self = [super init] )
    {
        self.serviceType = type;
        _uniqueIdentifier = [[NSUUID UUID] UUIDString];
        
        NSAssert(_uniqueIdentifier.length > 0, @"Service does not have a valid unique identifier! This is critical!");
        
        self.credentials = [NSMutableDictionary dictionaryWithCapacity:2];
        
        _linked = NO;
    }
    return self;
}

- (NSString*) description {
    return [NSString stringWithFormat:@"%@ (%@)", self.name, self.uniqueIdentifier];
}

- (id<CLServiceSlaveProtocol>)slave
{
    // create new slave
    if(_slave == nil) {
        _slave = [[[CLUploader classForServiceType:self.serviceType] alloc] initWithService:self];
    }
    
    NSAssert(_slave, @"Could not find or create a slave for service '%@'!", self);
    
    return _slave;
}

- (NSString*) utility
{
    return NSLocalizedString(@"Attachment Upload", nil);
}

- (NSString*) name
{
    if(self.showUsername)
        return [NSString stringWithFormat:@"%@ (%@)", [CLService nameForServiceType:self.serviceType], self.login?self.login:NSLocalizedString(@"Unknown", nil)];
    else
        return [CLService nameForServiceType:self.serviceType];
}
- (NSString*) identifier { return [CLService identifierForServiceType:self.serviceType]; }
- (NSImage*) icon { return [CLService iconForServiceType:self.serviceType]; }

- (BOOL) canBeDeleted { return [CLService isDeletableServiceType:self.serviceType]; }

- (BOOL) linked { return _linked; }
- (void) setLinked:(BOOL)linked {}
- (void) markAsLinked:(BOOL)linked
{
    // we seem to have a new state now
    self.linking = NO;
    
    if(linked==_linked)
        return;
    
    [self willChangeValueForKey:@"linked"];
    _linked = linked;
    [self didChangeValueForKey:@"linked"];
    
    if(self.linked)
    {
        [self savePasswordInKeychain];
    }
    else
    {
        [self removePasswordFromKeychain];
    }
}

- (void) savePasswordInKeychain
{
    if(self.login && self.password)
    {
        [NUKeychain setPassword:self.password forKeychainItemWithLabel:self.keychainIdentifier forAccount:self.login];
    }
}

- (void) removePasswordFromKeychain
{
    if(self.login)
    {
        [NUKeychain removeKeychainItemWithLabel:self.keychainIdentifier forAccount:self.login];
    }
}

- (NSString*) keychainIdentifier
{
    NSString* bundleName = PLUGIN_BUNDLE.infoDictionary[@"CFBundleName"];
    NSString* serviceName = self.identifier;
    NSString* uniqueIdentifier = self.uniqueIdentifier;
    
    return [NSString stringWithFormat:@"%@ - %@ (%@)", bundleName, serviceName, uniqueIdentifier];
}

- (NSImage*) bannerImage
{
    return [NSImage cl_pluginImageNamed:[self.identifier stringByAppendingString:@"_Banner"]];
}

- (NSColor*) linkStateColor
{
    if(self.linking)
        return [NSColor colorWithCalibratedRed:0.99 green:0.75 blue:0.25 alpha:1.0];    // orange
    else if(self.linked)
        return [NSColor colorWithCalibratedRed:0.20 green:0.78 blue:0.29 alpha:1.0];    // green
    else
        return [NSColor colorWithCalibratedRed:0.88 green:0.88 blue:0.88 alpha:1.0];    // gray
}

- (BOOL) showUsername
{
    return ([[CLServicesManager sharedManager] servicesOfServiceType:self.serviceType linkedOnly:NO].count > 1);
}

+ (NSSet *)keyPathsForValuesAffectingValueForKey:(NSString *)key{
    
    NSSet *keyPaths = [super keyPathsForValuesAffectingValueForKey:key];
    
    if ([key isEqualToString:@"linkStateColor"]) {
        NSArray *affectingKeys = @[@"linked", @"linking"];
        keyPaths = [keyPaths setByAddingObjectsFromArray:affectingKeys];
    }
    return keyPaths;
}

- (void)encodeWithCoder:(NSCoder *)encoder
{
    [encoder encodeObject:@(self.serviceType) forKey:@"serviceType"];
    [encoder encodeObject:_uniqueIdentifier forKey:@"uniqueIdentifier"];
    [encoder encodeObject:self.credentials forKey:@"credentials"];
    [encoder encodeObject:self.login forKey:@"login"];
    [encoder encodeObject:@(self.linked) forKey:@"linked"];
}

- (instancetype) initWithCoder:(NSCoder *)decoder
{
    CLServiceType serviceType = (CLServiceType)[[decoder decodeObjectForKey:@"serviceType"] integerValue];
    
    if((self = [self initWithServiceType:serviceType]))
    {
        NSAssert(serviceType == self.serviceType, @"Something is wrong with our service identifier: %@!", self);
        
        _uniqueIdentifier = [decoder decodeObjectForKey:@"uniqueIdentifier"];
        self.credentials = [decoder decodeObjectForKey:@"credentials"];
        self.login = [decoder decodeObjectForKey:@"login"];
        _linked = [[decoder decodeObjectForKey:@"linked"] boolValue];
        
        if(_uniqueIdentifier.length == 0)
        {
            NSLog(@"⚠️ CARGOLIFTER: Could not load unique identifier for this service. Creating new identifier now!");
            _uniqueIdentifier = [[NSUUID UUID] UUIDString];
        }
        
        NSAssert(_uniqueIdentifier.length > 0, @"Service does not have a valid unique identifier! This is critical!");
        
        // load password from keychain
        if(self.login)
            self.password = [NUKeychain passwordFromKeychainItemWithLabel:self.keychainIdentifier forAccount:self.login];
    }
    return self;
}

@end
