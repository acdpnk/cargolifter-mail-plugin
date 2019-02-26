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
//  CLCargoLifterPreferenceModule.h
//  CargoLifter
//
//  Created by Fabian Jäger on 15/09/15.
//  Copyright (c) 2015 Mailbutler. All rights reserved.
//

#import "NSPreferencesModule.h"
#import "CLServicesManager.h"
#import "CLUploader.h"

@interface CLCargoLifterPreferenceModule : NSPreferencesModule <NSTableViewDelegate,CLServiceSlaveAuthenticationDelegate,NSMenuDelegate>

@property (weak,readonly) NSView* preferencesView;

@property (strong) IBOutlet NSTableView* servicesTableView;

@property (strong) IBOutlet NSArrayController* servicesArrayController;

@property (weak,readonly) CLServicesManager* servicesManager;
@property (weak,readonly) NSUserDefaultsController* defaultsController;

@property (strong) IBOutlet NSWindow *ftpAuthPanel;
@property (strong) IBOutlet NSWindow *genericAuthPanel;
@property (strong) IBOutlet NSWindow *ownCloudAuthPanel;
@property (strong) IBOutlet NSWindow *evernoteAuthPanel;

@property (strong) IBOutlet NSMenu* servicesMenu;
@property (strong) IBOutlet NSButton* addServiceButton;

@property (readonly) BOOL isSierraOrLater;
@property (readonly) BOOL isElCapitanOrLater;

- (IBAction)addService:(id)sender;
- (IBAction)removeService:(id)sender;
- (IBAction)linkService:(id)sender;
- (IBAction)closeAuthSheet:(id)sender;

- (IBAction)selectPrivateKeyFile:(id)sender;

@end
