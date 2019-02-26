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
//  NSObject+Compatibility1014.h
//  Mailbutler
//
//  Created by Fabian Jäger on 06.06.17.
//  Copyright © 2017 Mailbutler. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "ComposeViewController.h"
#import "WebViewEditor.h"
#import "HeadersEditor.h"
#import "MFSignature.h"
#import "MCAttachment.h"
#import "AttachmentViewController.h"
#import "MCContactsManager.h"
#import <Contacts/Contacts.h>

#define EditorClass         ComposeViewController
#define WebViewEditorClass  WebViewEditor

#define SignatureClassName         MFSignature
#define AttachmentViewControllerClassName AttachmentViewController

@interface ComposeViewController (Compatibility1014)
- (NSWindow*) window;
@end

@interface MCAttachment (Compatibility1014)
- (id)fileWrapperForAccessLevel:(long long)arg1;
@end

@interface HeadersEditor (Compatibility1014)
- (void)updateDeliveryAccountControl:(id)arg1;
@end
