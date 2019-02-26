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
//  Compatibility.h
//  CargoLifter
//
//  Created by Fabian Jäger on 03.05.17.
//  Copyright © 2017 Mailbutler. All rights reserved.
//

#ifndef Compatibility_h
#define Compatibility_h

#import "CompatibilityHelper.h"

#if MAIL_OSX_SDK_MAJOR == 10
#if MAIL_OSX_SDK_MINOR == 11
#include "NSObject+Compatibility1011.h"
#endif
#if MAIL_OSX_SDK_MINOR == 12
#include "NSObject+Compatibility1012.h"
#endif
#if MAIL_OSX_SDK_MINOR == 13
#include "NSObject+Compatibility1013.h"
#endif
#if MAIL_OSX_SDK_MINOR == 14
#include "NSObject+Compatibility1014.h"
#endif
#endif

#endif /* Compatibility_h */
