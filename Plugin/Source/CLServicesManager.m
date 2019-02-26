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
//  CLServicesManager.m
//  CargoLifter
//
//  Created by Fabian Jäger on 19/09/15.
//  Copyright © 2015 Mailbutler. All rights reserved.
//

#import "CLServicesManager.h"

#import "CLUploader.h"

#import "NSImage+CLAdditions.h"

#import "MailApp.h"
#import "MFDeliveryAccount.h"

#define CLServicesList      @"CLServicesList"

@implementation CLServicesManager

- (instancetype) init
{
    if(self = [super init])
    {
        self.services = [NSMutableArray arrayWithCapacity:5];
        
        NSSortDescriptor *nameDescriptor = [[NSSortDescriptor alloc] initWithKey:@"name" ascending:YES];
        self.servicesSortDescriptors = @[nameDescriptor];
        
        // load from preferences, if available
        @try {
            NSData* encodedServicesData = [PLUGIN_DEFAULTS dataForKey:CLServicesList];
            if(encodedServicesData) {
                NSArray* storedServices = [NSKeyedUnarchiver unarchiveObjectWithData:encodedServicesData];
                if(storedServices)
                    [self.services addObjectsFromArray:storedServices];
            }
        } @catch (NSException* e) {
            // Surpress any unarchiving exceptions and continue
        }
        
        // remove invalid services
        for(CLService* aService in [self.services copy]) {
            if(aService.uniqueIdentifier == nil) {
                NSLog(@"⚠️ CARGOLIFTER: Removing service '%@' without valid identifier!", aService);
                [self.services removeObject:aService];
            }
        }
    }
    return self;
}

+ (CLServicesManager*) sharedManager
{
    static CLServicesManager* _sharedObject = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        _sharedObject = [[CLServicesManager alloc] init];
    });
    return _sharedObject;
}

- (CLService*) serviceWithIdentifier:(NSString*)identifier
{
    NSIndexSet* filteredIndexes = [self.services indexesOfObjectsPassingTest:^BOOL(CLService* obj, NSUInteger idx, BOOL *stop){
        return [obj.uniqueIdentifier isEqualToString:identifier];
    }];
    
    if(filteredIndexes.count == 0)
        return nil;
    
    return [[self.services objectsAtIndexes:filteredIndexes] firstObject];
}

- (NSArray<CLService*>*) linkedServices
{
    NSIndexSet* filteredIndexes = [self.services indexesOfObjectsPassingTest:^BOOL(CLService* obj, NSUInteger idx, BOOL *stop){
        return obj.linked;
    }];
    
    return [self.services objectsAtIndexes:filteredIndexes];
}

- (NSArray<CLService*>*) servicesOfServiceType:(CLServiceType)serviceType linkedOnly:(BOOL)linkedOnly
{
    NSIndexSet* filteredIndexes = [self.services indexesOfObjectsPassingTest:^BOOL(CLService* obj, NSUInteger idx, BOOL *stop){
        if(linkedOnly)
            return ((obj.serviceType == serviceType) && (obj.linked));
        else
            return obj.serviceType == serviceType;
    }];
    
    return [self.services objectsAtIndexes:filteredIndexes];
}

- (void) saveToPreferences
{
    // save to preferences
    NSData* encodedObject = [NSKeyedArchiver archivedDataWithRootObject:self.services];
    if(encodedObject) {
        [PLUGIN_DEFAULTS setObject:encodedObject forKey:CLServicesList];
        [PLUGIN_DEFAULTS synchronize];
    }
}

@end
