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
//  NSObject+Compatibility1011.h
//  CargoLifter
//
//  Created by Fabian Jäger on 03.05.17.
//  Copyright © 2017 Mailbutler. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "MFLibraryIMAPStore.h"
#import "MCAttachment.h"
#import "TableViewManager.h"

#import "MUISenderPhotoView.h"

#import "ComposeViewController.h"
#import "WebViewEditor.h"
#define EditorClass         ComposeViewController
#define WebViewEditorClass  WebViewEditor

#import "Signature.h"
#import "MFAttachmentViewController.h"
#define SignatureClassName         Signature
#define AttachmentViewControllerClassName MFAttachmentViewController

@interface MCAttachment (Compatibility1011)
- (NSUInteger)approximateSizeForAccessLevel:(long long)arg1;
- (id)fileWrapperForAccessLevel:(long long)arg1;
@end
