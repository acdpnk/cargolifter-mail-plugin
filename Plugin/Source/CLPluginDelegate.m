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
//  CLPluginDelegate.m
//  CargoLifter
//
//  Created by Fabian Jäger on 22/09/15.
//  Copyright © 2015 Mailbutler. All rights reserved.
//

#import "CLPluginDelegate.h"

#import "NSImage+CLAdditions.h"
#import "DocumentEditor+CargoLifter.h"

#import "CLServicesManager.h"

@interface CLPluginDelegate ()

@end

@implementation CLPluginDelegate

- (instancetype) init
{
    if( self = [super init] )
    {
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(appWillTerminate:) name:NSApplicationWillTerminateNotification object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(appWillResignActive:) name:NSApplicationWillResignActiveNotification object:nil];
    }
    return self;
}

- (void) dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

+ (CLPluginDelegate*) sharedDelegate
{
    static CLPluginDelegate* _sharedObject = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        _sharedObject = [[CLPluginDelegate alloc] init];
    });
    return _sharedObject;
}

- (void) appWillTerminate:(NSNotification*)notification
{
    [[CLServicesManager sharedManager] saveToPreferences];
}
- (void) appWillResignActive:(NSNotification*)notification
{
    [[CLServicesManager sharedManager] saveToPreferences];
}

#pragma mark Other Methods

+ (NSUserDefaults*)pluginDefaults
{
    static NSUserDefaults* _sharedDefaults = nil;
    static dispatch_once_t onceTokenDefaults;
    dispatch_once(&onceTokenDefaults, ^{
        _sharedDefaults = [[NSUserDefaults alloc] initWithSuiteName:CLCargoLifterDefaultsSuiteName];
        
        // Load user defaults
        NSString* defaultDictFile = [PLUGIN_BUNDLE pathForResource:@"CargoLifterDefaults" ofType:@"plist"];
        NSDictionary* defaultDict = [NSDictionary dictionaryWithContentsOfFile:defaultDictFile];
        [_sharedDefaults registerDefaults:defaultDict];
    });
    return _sharedDefaults;
}

+ (NSUserDefaultsController*)pluginDefaultsController
{
    static NSUserDefaultsController* _sharedDefaultsController = nil;
    static dispatch_once_t onceTokenDefaultsController;
    dispatch_once(&onceTokenDefaultsController, ^{
        _sharedDefaultsController = [[NSUserDefaultsController alloc] initWithDefaults:[self pluginDefaults] initialValues:nil];
    });
    return _sharedDefaultsController;
}

@end
