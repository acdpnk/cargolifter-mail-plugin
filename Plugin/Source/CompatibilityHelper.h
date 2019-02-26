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
//  CompatibilityHelper.h
//  CargoLifter
//
//  Created by Fabian Jäger on 04.05.17.
//  Copyright © 2017 Mailbutler. All rights reserved.
//

#ifndef CompatibilityHelper_h
#define CompatibilityHelper_h

#import <Foundation/Foundation.h>

#import <objc/runtime.h>
#import "JRSwizzle.h"

Class CLClassFromString(NSString* className);
void CLAddClassAsCategory(Class srcClass, Class targetClass);
#define CLAddAsCategoryToClass(targetClass)  CLAddClassAsCategory([self class], targetClass)

#define class(className) YES.boolValue?CLClassFromString([NSString stringWithFormat:@"%s",#className]):0

#define isElCapitan()           ([[NSProcessInfo processInfo] operatingSystemVersion].minorVersion == 11)
#define isElCapitanOrLater()    ([[NSProcessInfo processInfo] operatingSystemVersion].minorVersion >= 11)
#define isSierra()              ([[NSProcessInfo processInfo] operatingSystemVersion].minorVersion == 12)
#define isSierraOrLater()       ([[NSProcessInfo processInfo] operatingSystemVersion].minorVersion >= 12)
#define isHighSierra()          ([[NSProcessInfo processInfo] operatingSystemVersion].minorVersion == 13)
#define isHighSierraOrLater()   ([[NSProcessInfo processInfo] operatingSystemVersion].minorVersion >= 13)
#define isMojave()              ([[NSProcessInfo processInfo] operatingSystemVersion].minorVersion == 14)
#define isMojaveOrLater()       ([[NSProcessInfo processInfo] operatingSystemVersion].minorVersion >= 14)

#endif /* CompatibilityHelper_h */
