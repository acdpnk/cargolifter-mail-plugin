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
//  CLCargoLifterPreferenceModule.m
//  CargoLifter
//
//  Created by Fabian Jäger on 15/09/15.
//  Copyright (c) 2015 Mailbutler. All rights reserved.
//

#import "CLCargoLifterPreferenceModule.h"

#import "NSString+CLAdditions.h"
#import "NSImage+CLAdditions.h"
#import "NSView+DisableSubviews.h"

#import "CLServicesManager.h"

#import "CLGlobalFunctions.h"

#import "CLGoogleDriveUploader.h"
#import "CLGenericUploader.h"

#import "ITSwitch.h"

#import "NSPreferences+CargoLifter.h"

#import <QuartzCore/QuartzCore.h>

@interface CLCargoLifterPreferenceModule ()

@property (assign) NSWindow* currentAuthPanel;
@property (assign) NSButton* currentLinkButton;
@property (assign) BOOL authenticating;

- (CAKeyframeAnimation *)shakeAnimation:(NSRect)frame;

- (NSWindow*)preferencesWindow;
@end

@implementation CLCargoLifterPreferenceModule

- (NSString*)preferencesNibName
{
    return @"CargoLifterPreferenceView";
}

- (NSString*) versionString {
    NSString* version = [PLUGIN_BUNDLE objectForInfoDictionaryKey:(NSString *)kCFBundleVersionKey];
    return [NSString stringWithFormat:@"Version: %@", version];
}

- (NSView*)preferencesView { return _preferencesView; }

- (NSImage*)imageForPreferenceNamed:(NSString*)prefName { return [NSImage cl_pluginImageNamed:@"CargoLifter"]; }

- (void) moduleWillBeRemoved { [self saveChanges]; }

- (BOOL)preferencesWindowShouldClose
{
    [self saveChanges];
    return YES;
}

- (BOOL)isResizable { return NO; }

- (CLServicesManager*) servicesManager { return [CLServicesManager sharedManager]; }
- (NSUserDefaultsController*)defaultsController { return [CLPluginDelegate pluginDefaultsController]; }

- (BOOL) isSierraOrLater { return isSierraOrLater(); }
- (BOOL) isElCapitanOrLater { return isElCapitanOrLater(); }

- (void) saveChanges {
    [super saveChanges];

    [self.servicesManager saveToPreferences];
}

#pragma mark Action Methods

- (IBAction)addService:(id)sender
{
    NSMenuItem* senderItem = (NSMenuItem*)sender;
    
    CLService* newService = [[CLService alloc] initWithServiceType:(CLServiceType)senderItem.tag];

    [self.servicesArrayController addObject:newService];
    
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.5 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        [self linkService:newService];
    });
}

- (IBAction)removeService:(id)sender
{
    NSIndexSet* selectionIndexes = (self.servicesArrayController).selectionIndexes;
    
    // unlink services first
    [selectionIndexes enumerateIndexesUsingBlock:^(NSUInteger idx, BOOL * _Nonnull stop) {
        
        CLService* selectedService = self.servicesArrayController.arrangedObjects[idx];
        if( selectedService.linked )
        {
            // unlink
            [selectedService markAsLinked:NO];
            
            id<CLServiceSlaveProtocol> slave = selectedService.slave;
            if([slave respondsToSelector:@selector(deauthenticate)])
                [slave deauthenticate];
        }
    }];
    
    [NSAnimationContext runAnimationGroup:^(NSAnimationContext * _Nonnull context) {
        [self.servicesTableView removeRowsAtIndexes:selectionIndexes withAnimation:NSTableViewAnimationSlideUp];
    } completionHandler:^{
        [self.servicesArrayController removeObjectsAtArrangedObjectIndexes:selectionIndexes];
    }];
}

- (IBAction)linkService:(id)sender
{
    CLService* selectedService = nil;
    
    if( [sender isKindOfClass:[NSView class]] )
    {
        NSInteger clickedRow = [self.servicesTableView rowForView:sender];
        selectedService = (self.servicesArrayController.arrangedObjects)[clickedRow];
    }
    else if( [sender isKindOfClass:[CLService class]] )
    {
        selectedService = sender;
    }
    else
    {
        return;
    }
    
    NSWindow *prefWindow = [self preferencesWindow];
    
    [self.servicesArrayController setSelectedObjects:@[selectedService]];
    
    self.currentAuthPanel = nil;
    
    if( selectedService.linked )
    {
        // unlink
        [selectedService markAsLinked:NO];
        
        id<CLServiceSlaveProtocol> slave = selectedService.slave;
        if([slave respondsToSelector:@selector(deauthenticate)])
            [slave deauthenticate];
    }
    else
    {
        // start linking
        switch (selectedService.serviceType) {
            case CLDropboxService:
            case CLBoxService:
            case CLGoogleDriveService:
            case CLOneDriveService:
            {
                id<CLServiceSlaveProtocol> slave = selectedService.slave;
                if([slave respondsToSelector:@selector(setAuthDelegate:)])
                    [slave setAuthDelegate:self];
                
                if([slave respondsToSelector:@selector(authenticateWithWindow:)])
                    [slave authenticateWithWindow:prefWindow];
                else if([slave respondsToSelector:@selector(authenticate)])
                    [slave authenticate];
                
                break;
            }
            case CLGenericService:
            {
                // show authentication panel
                self.currentAuthPanel = self.ftpAuthPanel;
                
                break;
            }
            case CLOwnCloudService:
            {
                // show authentication panel
                self.currentAuthPanel = self.ownCloudAuthPanel;
                
                break;
            }
            case CLCloudAppService:
            case CLDroplrService:
            case CLDropmarkService:
            case CLMediafireService:
                // show authentication panel
                self.currentAuthPanel = self.genericAuthPanel;
                
                break;
            default:
                break;
        }
    }
    
    if( self.currentAuthPanel )
    {
        [prefWindow beginSheet:self.currentAuthPanel completionHandler:^(NSModalResponse returnCode) {
            // nothing special to do here...
        }];
    }
}

- (IBAction)closeAuthSheet:(id)sender
{
    NSWindow *prefWindow = [self preferencesWindow];
    
    CLService* selectedService = (self.servicesArrayController).selectedObjects.firstObject;
    
    // reset state
    self.authenticating = NO;
    
    NSButton* senderButton = (NSButton*)sender;
    BOOL doLink = (BOOL)senderButton.tag;
    
    // commit editing
    [senderButton.window makeFirstResponder:nil];
    
    if( !doLink )   // cancel sheet
    {
        [(NSView*)self.currentAuthPanel.contentView disableSubviews:NO];
        [prefWindow endSheet:senderButton.window returnCode:NSModalResponseCancel];
    }
    else    // link
    {
        self.currentLinkButton = senderButton;
        
        switch (selectedService.serviceType)
        {
            case CLGenericService:
            {
                NSString* genericServer = selectedService.credentials[CLGenericServer];
                NSURL* genericServerURL = [NSURL URLWithString:genericServer];
                if( !genericServerURL.scheme )
                {
                    [NSApp activateIgnoringOtherApps:YES];
                    CLRunAlertPanel(NSLocalizedString(@"Invalid Server Address", nil),
                                    @"%@",
                                    nil,
                                    NSLocalizedString(@"The provided server address does not have the required format.", nil)
                                    );
                }
                break;
            }
            default:
                break;
        }
        
        if( selectedService.login )
        {
            [(NSView*)self.currentAuthPanel.contentView disableSubviews:YES ofType:[NSTextField class]];
            [self.currentLinkButton setEnabled:NO];
            [self.currentLinkButton setTitle:NSLocalizedString(@"Linking", nil)];
            
            // try to authenticate
            self.authenticating = YES;
            
            id<CLServiceSlaveProtocol> slave = selectedService.slave;
            if([slave respondsToSelector:@selector(setAuthDelegate:)])
                [slave setAuthDelegate:self];
            
            if([slave respondsToSelector:@selector(authenticateWithWindow:)])
            {
                if(self.currentAuthPanel.isVisible)
                {
                    [(NSView*)self.currentAuthPanel.contentView disableSubviews:NO];
                    [prefWindow endSheet:senderButton.window returnCode:NSModalResponseCancel];
                }
                [slave authenticateWithWindow:prefWindow];
            }
            else if([slave respondsToSelector:@selector(authenticate)])
                [slave authenticate];
        }
    }
}

- (IBAction)registerService:(id)sender
{
    CLService* selectedService = (self.servicesArrayController).selectedObjects.firstObject;
    
    switch(selectedService.serviceType)
    {
        case CLBoxService:
            [[NSWorkspace sharedWorkspace] openURL:[NSURL URLWithString:@"https://box.com"]];
            break;
        case CLCloudAppService:
            [[NSWorkspace sharedWorkspace] openURL:[NSURL URLWithString:@"http://my.cl.ly/register"]];
            break;
        case CLDropboxService:
            [[NSWorkspace sharedWorkspace] openURL:[NSURL URLWithString:@"https://www.dropbox.com"]];
            break;
        case CLDroplrService:
            [[NSWorkspace sharedWorkspace] openURL:[NSURL URLWithString:@"https://auth.droplr.com"]];
            break;
        case CLDropmarkService:
            [[NSWorkspace sharedWorkspace] openURL:[NSURL URLWithString:@"http://www.dropmark.com"]];
            break;
        case CLMediafireService:
            [[NSWorkspace sharedWorkspace] openURL:[NSURL URLWithString:@"https://mediafire.com"]];
            break;
        case CLGoogleDriveService:
            [[NSWorkspace sharedWorkspace] openURL:[NSURL URLWithString:@"https://www.google.com/drive/"]];
            break;
        default:
            break;
    }
}

- (IBAction)selectPrivateKeyFile:(id)sender
{
    // Create a File Open Dialog class.
    NSOpenPanel* openDlg = [NSOpenPanel openPanel];
    
    // Enable options in the dialog.
    [openDlg setCanChooseFiles:YES];
    [openDlg setAllowsMultipleSelection:NO];
    [openDlg setCanChooseDirectories:NO];
    
    // Display the dialog box.  If the OK pressed,
    // process the files.
    [openDlg beginWithCompletionHandler:^(NSInteger result) {
        if(result == NSModalResponseOK)
        {
            // Gets list of all files selected
            NSArray *fileURLs = [openDlg URLs];
            NSURL* aFileURL = [fileURLs firstObject];
            
            // first file is our key file
            CLService* selectedService = (self.servicesArrayController).selectedObjects.firstObject;
            selectedService.credentials[CLGenericPrivateKey] = aFileURL.path;
        }
    }];
}

#pragma mark Delegate Methods

- (NSView*) tableView:(NSTableView *)tableView viewForTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row
{
    if(tableView == self.servicesTableView && [tableColumn.identifier isEqualToString:@"service"])
    {
        CLService* service = (self.servicesArrayController.arrangedObjects)[row];
        NSView* cellView = [tableView makeViewWithIdentifier:tableColumn.identifier owner:self];
        
        for(NSView* subView in cellView.subviews)
        {
            if([subView isKindOfClass:[ITSwitch class]])
            {
                // bind color
                [subView bind:@"color" toObject:service withKeyPath:@"linkStateColor" options:nil];
            }
        }
        
        return cellView;
    }
    
    // fallback
    return [tableView makeViewWithIdentifier:tableColumn.identifier owner:self];
}

#pragma mark Uploader Delegate Methods

- (void)uploadFailedWithStatus:(CLUploadStatus)status withError:(NSError *)error {}

- (void)uploadProgress:(CGFloat)progress forFile:(NSString *)filePath {}
- (void)createdLink:(NSURL *)linkURL forFile:(NSString *)path withIconURL:(NSURL *)iconURL {}

- (void)didFinishAuthenticationWithError:(NSError*)error
{
    if(!self.authenticating)
        return;
    self.authenticating = NO;
    
    NSWindow *prefWindow = [self preferencesWindow];
    
    // restore states
    [self.currentAuthPanel.contentView disableSubviews:NO];
    [self.currentLinkButton setTitle:NSLocalizedString(@"Link", nil)];
    
    // general reaction
    if( error != nil )
    {
        if(self.currentAuthPanel)
        {
            // shake and error
            [CATransaction begin]; {
                [CATransaction setCompletionBlock:^{
                    CLRunAlertPanel(NSLocalizedString(@"Linking Error", nil), @"%@", nil, error.localizedDescription);
                }];
                self.currentAuthPanel.animations = @{@"frame": [self shakeAnimation:self.currentAuthPanel.frame]};
                [[self.currentAuthPanel animator] setFrame:self.currentAuthPanel.frame display:NO];
            } [CATransaction commit];
        }
        else
        {
            // just show error
            CLRunAlertPanel(NSLocalizedString(@"Linking Error", nil), @"%@", nil, error.localizedDescription);
        }
    }
    else
    {
        if(self.currentAuthPanel)
        {
            [prefWindow endSheet:self.currentAuthPanel returnCode:NSModalResponseOK];
            self.currentAuthPanel = nil;
        }
    }
}

#pragma mark Menu Delegate Methods

- (void)menuNeedsUpdate:(NSMenu *)menu
{
    if(menu == self.servicesMenu)
    {
        [menu removeAllItems];
        [menu setAutoenablesItems:NO];
        
        for(CLServiceType i=0; i<CLNumServices; i++)
        {
            if(![CLService isDeletableServiceType:i])
            {
                // this does not belong into the menu, skip
                continue;
            }
            
            NSString* serviceName = [CLService nameForServiceType:i];
            NSImage* serviceIcon = [CLService iconForServiceType:i];
            
            if(!(serviceName && serviceIcon))
                continue;
            
            NSMenuItem* newItem = [self.servicesMenu addItemWithTitle:serviceName action:@selector(addService:) keyEquivalent:@""];
            newItem.image = serviceIcon;
            newItem.image.size = NSMakeSize(18, 18);
            newItem.target = self;
            newItem.tag = i;
            
            NSInteger numServicesOfSameType = [[CLServicesManager sharedManager] servicesOfServiceType:i linkedOnly:NO].count;
            newItem.enabled = [CLService allowsMultipleOfServiceType:i] || numServicesOfSameType == 0;
        }
    }
}

#pragma mark Private Methods

static int numberOfShakes = 3;
static float durationOfShake = 0.13f;
static float vigourOfShake = 0.03f;

- (CAKeyframeAnimation *)shakeAnimation:(NSRect)frame
{
    CAKeyframeAnimation *shakeAnimation = [CAKeyframeAnimation animationWithKeyPath:@"frame"];
    
    NSRect rectLeft = NSMakeRect(NSMinX(frame) - frame.size.width * vigourOfShake, NSMinY(frame), frame.size.width, frame.size.height);
    NSRect rectRight = NSMakeRect(NSMinX(frame) + frame.size.width * vigourOfShake, NSMinY(frame), frame.size.width, frame.size.height);
    NSArray *leftRightRects = @[[NSValue valueWithRect:frame], [NSValue valueWithRect:rectLeft], [NSValue valueWithRect:rectRight], [NSValue valueWithRect:frame]];
    
    shakeAnimation.values = leftRightRects;
    shakeAnimation.duration = durationOfShake;
    shakeAnimation.repeatCount = numberOfShakes;
    
    return shakeAnimation;
}

- (NSWindow*)preferencesWindow {
    return [[self preferencesView] window];
}

@end
