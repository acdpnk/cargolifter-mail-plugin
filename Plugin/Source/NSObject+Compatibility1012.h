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
//  NSObject+Compatibility1012.h
//  CargoLifter
//
//  Created by Fabian Jäger on 03.05.17.
//  Copyright © 2017 Mailbutler. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "MFLibraryIMAPStore.h"
#import "HeadersEditor.h"

#import "ComposeViewController.h"
#import "WebViewEditor.h"
#define EditorClass         ComposeViewController
#define WebViewEditorClass  WebViewEditor

#import "MFSignature.h"
#import "AttachmentViewController.h"
#import "MCContactsManager.h"
#import <Contacts/Contacts.h>
#define SignatureClassName         MFSignature
#define AttachmentViewControllerClassName AttachmentViewControllers

@interface HeadersEditor (Compatibility1012)
- (void)updateDeliveryAccountControl:(id)arg1;
@end

@interface ComposeViewController (Compatibility1012)
- (NSWindow*) window;
@end
