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
//  NSObject+Compatibility1012.m
//  CargoLifter
//
//  Created by Fabian Jäger on 03.05.17.
//  Copyright © 2017 Mailbutler. All rights reserved.
//

#define NotAvailable()  NSAssert(false, @"This method does not exist in macOS 10.12!")

#import <Cocoa/Cocoa.h>

#import "CompatibilityHelper.h"

#import "../External/Class-Dumps/macosx10.12/CNAvatarViewController.h"

@implementation HeadersEditor_CLCompatibility1012 : NSObject

- (void)updateDeliveryAccountControl:(id)arg1 { NotAvailable(); }

+ (void)load { if(isSierra()) CLAddAsCategoryToClass(@class(HeadersEditor)); }

@end

@implementation ComposeViewController_CLCompatibility1012 : NSObject

- (NSWindow*)window { return [[(NSViewController*)self view] window]; }

+ (void)load { if(isSierra()) CLAddAsCategoryToClass(@class(ComposeViewController)); }

@end
