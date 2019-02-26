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
//  CLServicesManager.h
//  CargoLifter
//
//  Created by Fabian Jäger on 19/09/15.
//  Copyright © 2015 Mailbutler. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "CLService.h"

@interface CLServicesManager : NSObject

@property (strong) NSMutableArray* services;
@property (strong) NSArray* servicesSortDescriptors;

+ (CLServicesManager*) sharedManager;

- (CLService*) serviceWithIdentifier:(NSString*)identifier;

- (NSArray<CLService*>*) linkedServices;

- (NSArray<CLService*>*) servicesOfServiceType:(CLServiceType)serviceType linkedOnly:(BOOL)linkedOnly;

- (void) saveToPreferences;

@end
