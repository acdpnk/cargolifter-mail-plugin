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
//  HeadersEditor+CargoLifter.h
//  CargoLifter
//
//  Created by Fabian Jäger on 09/10/15.
//  Copyright © 2015 Mailbutler. All rights reserved.
//

#import <Foundation/Foundation.h>

@class CLService;

@interface HeadersEditor_CargoLifter : NSObject <NSMenuDelegate>

@property (strong) NSNumber* cl_uploadAttachments;
@property (strong) CLService* cl_uploadService;

@end
