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
//  HeadersEditor+CargoLifter.m
//  CargoLifter
//
//  Created by Fabian Jäger on 09/10/15.
//  Copyright © 2015 Mailbutler. All rights reserved.
//

#import "HeadersEditor+CargoLifter.h"

#import "ComposeHeaderRowView.h"
#import "ComposeStatusView.h"
#import "MFDeliveryAccount.h"

#import "CLServicesManager.h"
#import "CLCargoLifterPreferenceModule.h"

#import "Reachability.h"

#import "NSImage+CLAdditions.h"
#import "NSString+CLAdditions.h"

#import "ComposeBackEnd.h"

static NSPopUpButton* _serviceSelectorButton = nil;

@interface HeadersEditor_CargoLifter ()

@property (nonatomic, strong) NSView* cl_uploadAttachmentsView;

@end

@implementation HeadersEditor_CargoLifter

- (void)cargoLifter_configureButtonsAndPopUps
{
    [self cargoLifter_configureButtonsAndPopUps];
    
    if(isSierraOrLater()) {
        ComposeHeaderRowView* statusRow = [(HeadersEditor*)self statusRow];
        
        NSArray* subviews = [statusRow subviews];
        if([[subviews firstObject] isKindOfClass:@class(ComposeStatusView)]) {
            ComposeStatusView* statusView = [subviews firstObject];
            
            [self cargoLifter_refreshUploadAttachmentsView];
            if( self.cl_uploadAttachmentsView && ![statusView.views containsObject:self.cl_uploadAttachmentsView] )
            {
                [statusView addView:self.cl_uploadAttachmentsView inGravity:NSStackViewGravityCenter];
            }
        }
        
        [(HeadersEditor*)self changeFromHeader:nil];
    } else {
        [(HeadersEditor*)self updateDeliveryAccountControl:nil];
    }
}

- (void)cargoLifter_stackView:(id)stackView didReattachViews:(NSArray*)views
{
    NSAssert(isSierraOrLater() == NO, @"StackViews in 10.12+ just hide!");
    
    // add attachment upload view
    if([views containsObject:[(HeadersEditor*)self statusRow]])
    {
        ComposeHeaderRowView* statusRow = [(HeadersEditor*)self statusRow];
        
        NSArray* subviews = [statusRow subviews];
        
        if(![[subviews firstObject] isKindOfClass:@class(ComposeStatusView)])
            return;
        
        ComposeStatusView* statusView = [subviews firstObject];
        
        [self cargoLifter_refreshUploadAttachmentsView];
        if( self.cl_uploadAttachmentsView && ![statusView.views containsObject:self.cl_uploadAttachmentsView] )
        {
            [statusView addView:self.cl_uploadAttachmentsView inGravity:NSStackViewGravityCenter];
            
            [(HeadersEditor*)self updateDeliveryAccountControl:nil];
        }
    }
}

- (void)cargoLifter_stackView:(id)stackView willDetachViews:(NSArray*)views
{
    NSAssert(isSierraOrLater() == NO, @"StackViews in 10.12+ just hide!");
    
    // remove attachment upload view
    if([views containsObject:[(HeadersEditor*)self statusRow]])
    {
        ComposeHeaderRowView* statusRow = [(HeadersEditor*)self statusRow];
        
        NSArray* subviews = [statusRow subviews];
        
        if(![[subviews firstObject] isKindOfClass:@class(ComposeStatusView)])
            return;
        
        ComposeStatusView* statusView = [subviews firstObject];
        
        if( self.cl_uploadAttachmentsView &&  [statusView.views containsObject:self.cl_uploadAttachmentsView] )
            [statusView removeView:self.cl_uploadAttachmentsView];
    }
}

- (void) cargoLifter_updateDeliveryAccountControl:(id)control
{
    [self cargoLifter_updateDeliveryAccountControl:control];
    
    MFDeliveryAccount* deliveryAccount = [self cargoLifter_deliveryAccount];
    NSString* accountIdentifier = [deliveryAccount identifier];
    
    NSPopUpButton* selectorButton = [[self.cl_uploadAttachmentsView subviews] objectAtIndex:1];
    if((selectorButton && ![selectorButton isHidden]))
    {
        // check, if we have a last-used service
        NSString* defaultKey = [NSString stringWithFormat:@"CLCargoLifter_LastAttachmentService_%@", accountIdentifier];
        
        NSString* serviceIdentifier = [PLUGIN_DEFAULTS stringForKey:defaultKey];
        
        if(serviceIdentifier)
        {
            CLService* service = [[CLServicesManager sharedManager] serviceWithIdentifier:serviceIdentifier];
            
            if(service) {
                NSInteger index = MAX(0, [selectorButton indexOfItemWithRepresentedObject:service]);
                [selectorButton selectItemAtIndex:index];
                
                [self cargoLifter_didChangeService:[selectorButton selectedItem]];
            }
        }
    }
}

- (MFDeliveryAccount*) cargoLifter_deliveryAccount
{
    EditorClass* composeViewController = [(HeadersEditor*)self composeViewController];

    ComposeBackEnd* backEnd = [composeViewController backEnd];

    return backEnd.deliveryAccount;
}

+ (void) load
{
    // add our methods as category
    CLAddClassAsCategory([self class], @class(HeadersEditor));
    
    // swizzling
    NSError* swizzleError;
    
    if(isSierraOrLater())
    {
        [@class(HeadersEditor) jr_swizzleMethod:@selector(changeFromHeader:) withMethod:@selector(cargoLifter_updateDeliveryAccountControl:) error:&swizzleError];
        if(swizzleError) NSLog(@"💥 CARGOLIFTER: Swizzle Error: %@", swizzleError);
        
        [@class(HeadersEditor) jr_swizzleMethod:@selector(configureButtonsAndPopUps) withMethod:@selector(cargoLifter_configureButtonsAndPopUps) error:&swizzleError];
        if(swizzleError) NSLog(@"💥 CARGOLIFTER: Swizzle Error: %@", swizzleError);
    }
    else
    {
        [@class(HeadersEditor) jr_swizzleMethod:@selector(stackView:didReattachViews:) withMethod:@selector(cargoLifter_stackView:didReattachViews:) error:&swizzleError];
        if(swizzleError) NSLog(@"💥 CARGOLIFTER: Swizzle Error: %@", swizzleError);
        
        [@class(HeadersEditor) jr_swizzleMethod:@selector(stackView:willDetachViews:) withMethod:@selector(cargoLifter_stackView:willDetachViews:) error:&swizzleError];
        if(swizzleError) NSLog(@"💥 CARGOLIFTER: Swizzle Error: %@", swizzleError);
        
        [@class(HeadersEditor) jr_swizzleMethod:@selector(updateDeliveryAccountControl:) withMethod:@selector(cargoLifter_updateDeliveryAccountControl:) error:&swizzleError];
        if(swizzleError) NSLog(@"💥 CARGOLIFTER: Swizzle Error: %@", swizzleError);
        
        [@class(HeadersEditor) jr_swizzleMethod:@selector(configureButtonsAndPopUps) withMethod:@selector(cargoLifter_configureButtonsAndPopUps) error:&swizzleError];
        if(swizzleError) NSLog(@"💥 CARGOLIFTER: Swizzle Error: %@", swizzleError);
    }
    
    NSAssert(swizzleError==nil, @"Something went wrong during method swizzling: %@", swizzleError);
}

#pragma mark Private Methods

- (void) cargoLifter_refreshUploadAttachmentsView
{
    NSArray* availableServices = [[CLServicesManager sharedManager] linkedServices];
    
    if(!self.cl_uploadAttachmentsView)
    {
        self.cl_uploadAttachmentsView = [[NSView alloc] initWithFrame:NSMakeRect(0, 0, 200, 30)];
        [self.cl_uploadAttachmentsView setTranslatesAutoresizingMaskIntoConstraints:NO];
        
        NSButton* checkboxButton = [[NSButton alloc] initWithFrame:NSMakeRect(0, 0, 20, 22)];
        [checkboxButton setTranslatesAutoresizingMaskIntoConstraints:NO];
        
        [checkboxButton setButtonType:NSSwitchButton];
        [checkboxButton setTitle:NSLocalizedString(@"Upload attachments with", nil)];
        [checkboxButton setTranslatesAutoresizingMaskIntoConstraints:NO];
        
        [self.cl_uploadAttachmentsView addSubview:checkboxButton];
        
        NSPopUpButton* selectorButton = [[NSPopUpButton alloc] initWithFrame:NSMakeRect(0, 0, 100, 22) pullsDown:NO];
        [selectorButton setTranslatesAutoresizingMaskIntoConstraints:NO];
        
        [self.cl_uploadAttachmentsView addSubview:selectorButton];
        
        // do some auto-layouting
        NSArray* spaceConstraint = [NSLayoutConstraint constraintsWithVisualFormat:@"H:|-0-[checkboxButton]-8-[selectorButton]-0-|"
                                                                               options:NSLayoutFormatAlignAllBaseline
                                                                               metrics:nil
                                                                                 views:NSDictionaryOfVariableBindings(checkboxButton, selectorButton)];
        [self.cl_uploadAttachmentsView addConstraints:spaceConstraint];
        
        NSArray* verticalCenterConstraint = [NSLayoutConstraint constraintsWithVisualFormat:@"V:|-0-[selectorButton]-0-|"
                                                                           options:0
                                                                           metrics:nil
                                                                             views:NSDictionaryOfVariableBindings(selectorButton)];
        [self.cl_uploadAttachmentsView addConstraints:verticalCenterConstraint];
    }
    
    // refresh our attachment-related controls
    NSButton* uploadCheckbox = [[self.cl_uploadAttachmentsView subviews] objectAtIndex:0];
    NSPopUpButton* selectorButton = [[self.cl_uploadAttachmentsView subviews] objectAtIndex:1];
    
    [selectorButton.menu removeAllItems];
    [selectorButton.menu setAutoenablesItems:NO];
    
    for(CLService* aService in availableServices)
    {
        NSMenuItem* aServiceItem = [selectorButton.menu addItemWithTitle:aService.name action:nil keyEquivalent:@""];
        aServiceItem.image = aService.icon;
        [aServiceItem.image setSize:NSMakeSize(18.0, 18.0)];
        aServiceItem.representedObject = aService;
        
        [aServiceItem setTarget:self];
        [aServiceItem setAction:@selector(cargoLifter_didChangeService:)];
        
        [aServiceItem setEnabled:YES];
    }
    // check, if we have a last-used service
    MFDeliveryAccount* deliveryAccount = [self cargoLifter_deliveryAccount];
    NSString* accountIdentifier = [deliveryAccount identifier];
    NSString* defaultKey = [NSString stringWithFormat:@"CLCargoLifter_LastAttachmentService_%@", accountIdentifier];
    
    NSString* serviceIdentifier = [PLUGIN_DEFAULTS stringForKey:defaultKey];
    
    if(serviceIdentifier)
    {
        CLService* service = [[CLServicesManager sharedManager] serviceWithIdentifier:serviceIdentifier];
        
        if(service)
            self.cl_uploadService = service;
        else
            self.cl_uploadService = [availableServices firstObject];   // use first item, if we don't have a last-used service'
    }
    else
    {
        self.cl_uploadService = [availableServices firstObject];   // use first item, if we don't have a last-used service'
    }
    
    Reachability* reachability = [Reachability reachabilityForInternetConnection];
    
    if([[selectorButton.menu itemArray] count] == 0)
    {
        // no available services
        uploadCheckbox.state = NSOffState;
        uploadCheckbox.enabled = NO;
        [uploadCheckbox unbind:NSValueBinding];
        
        selectorButton.enabled = NO;
        
        // add dummy item
        [selectorButton.menu addItemWithTitle:NSLocalizedString(@"No upload service available", nil) action:nil keyEquivalent:@""];
    }
    else if(!([reachability isReachable] && ![reachability isInterventionRequired]))
    {
        uploadCheckbox.state = NSOffState;
        uploadCheckbox.enabled = NO;
        [uploadCheckbox unbind:NSValueBinding];
        
        selectorButton.enabled = NO;
        
        // add dummy item
        [selectorButton.menu addItemWithTitle:NSLocalizedString(@"No internet connection", nil) action:nil keyEquivalent:@""];
    }
    else
    {
        // upload service available
        uploadCheckbox.enabled = YES;
        selectorButton.enabled = YES;
        [uploadCheckbox bind:NSValueBinding toObject:self withKeyPath:@"cl_uploadAttachments" options:nil];
    }
}

#pragma mark Action Methods

- (void)cargoLifter_didChangeService:(id)sender
{
    NSMenuItem* selectedItem = sender;
    
    self.cl_uploadService = [selectedItem representedObject];
}

#pragma mark Associated Objects

- (void)setCl_uploadAttachmentsView:(NSView *)uploadAttachmentsView
{
    objc_setAssociatedObject(self, @selector(cl_uploadAttachmentsView), uploadAttachmentsView, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}

- (NSView*)cl_uploadAttachmentsView
{
    return objc_getAssociatedObject(self, @selector(cl_uploadAttachmentsView));
}

- (void)setCl_uploadAttachments:(NSNumber*)uploadAttachments
{
    objc_setAssociatedObject(self, @selector(cl_uploadAttachments), uploadAttachments, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}

- (NSNumber*)cl_uploadAttachments
{
    return objc_getAssociatedObject(self, @selector(cl_uploadAttachments));
}

- (void)setCl_uploadService:(CLService *)uploadService
{
    objc_setAssociatedObject(self, @selector(cl_uploadService), uploadService, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
    
    // store last used-cloud service for current account
    MFDeliveryAccount* deliveryAccount = [self cargoLifter_deliveryAccount];
    NSString* accountIdentifier = [deliveryAccount identifier];
    NSString* defaultKey = [NSString stringWithFormat:@"CLCargoLifter_LastAttachmentService_%@", accountIdentifier];
    
    NSString* uploadServiceIdentifier = uploadService.uniqueIdentifier;
    [PLUGIN_DEFAULTS setObject:uploadServiceIdentifier forKey:defaultKey];
}

- (CLService*)cl_uploadService
{
    return objc_getAssociatedObject(self, @selector(cl_uploadService));
}
@end
