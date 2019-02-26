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
//  CLService.h
//  CargoLifter
//
//  Created by Fabian Jäger on 18/09/15.
//  Copyright © 2015 Mailbutler. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "CLServiceSlaveProtocol.h"

typedef enum _CSServiceType {
    CLDropboxService,
    CLCloudAppService,
    CLDroplrService,
    CLDropmarkService,
    CLMediafireService,
    CLBoxService,
    CLGoogleDriveService,
    CLOwnCloudService,
    CLGenericService,
    CLOneDriveService,
    
    CLNumServices,   // not a real service ;)
} CLServiceType;

@interface CLService : NSObject

@property CLServiceType serviceType;

@property (strong) NSString* login;
@property (strong) NSString* password;
@property (strong) NSMutableDictionary* credentials;
@property (assign) BOOL linked;
@property (assign) BOOL linking;
@property (readonly) NSColor* linkStateColor;

@property (readonly) BOOL canBeDeleted;

@property (readonly) BOOL showUsername;

@property (readonly) NSString* utility;
@property (readonly) NSString* name;
@property (readonly) NSImage* icon;
@property (readonly) NSImage* bannerImage;

@property (readonly) NSString* keychainIdentifier;
@property (strong,readonly) NSString* uniqueIdentifier;

- (instancetype) initWithServiceType:(CLServiceType)type NS_DESIGNATED_INITIALIZER;

- (void)markAsLinked:(BOOL)linked;  // this method is to be used, setLinked: is a dummy

@property (readonly, strong) id<CLServiceSlaveProtocol> slave;

+ (NSString*) nameForServiceType:(CLServiceType)type;
+ (NSString*) identifierForServiceType:(CLServiceType)type;
+ (NSImage*)iconForServiceType:(CLServiceType)type;

+ (BOOL) isDeletableServiceType:(CLServiceType)type;
+ (BOOL) allowsMultipleOfServiceType:(CLServiceType)type;

@end
