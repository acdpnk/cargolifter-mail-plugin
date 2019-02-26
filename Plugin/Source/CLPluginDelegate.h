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
//  CLPluginDelegate.h
//  CargoLifter
//
//  Created by Fabian Jäger on 22/09/15.
//  Copyright © 2015 Mailbutler. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface CLPluginDelegate : NSObject

+ (CLPluginDelegate*) sharedDelegate;

+ (NSUserDefaults*) pluginDefaults;
+ (NSUserDefaultsController*)pluginDefaultsController;

@end
