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
//  NSPreferences+CargoLifter.h
//  CargoLifter
//
//  Created by Fabian Jäger on 15/09/15.
//  Copyright (c) 2015 Mailbutler. All rights reserved.
//

#import "CLMailBundle.h"
#import "NSPreferences+CargoLifter.h"
#import "CLCargoLifterPreferenceModule.h"

#import "NSPreferences.h"

#import "objc/objc-class.h"

#define    NSPreferences_preferencesPanel_ivarName "_preferencesPanel"

void*      FOOGetIvar(id object, const char* name, const char* typeEncodingPrefix);
#define    FOOTypedIvarPtrOrNULL(o,t,n)     ( (t*) FOOGetIvar((o),n,@encode(t)) )

@implementation NSPreferences_CargoLifter

#pragma mark Swizzled class methods

+ (id)cargoLifter_sharedPreferences
{
    NSPreferences* preferences =  [self cargoLifter_sharedPreferences];// call swizzled-out method
    
    static BOOL _cargoLifterHasBeenAdded = NO;
    if ( preferences == nil || _cargoLifterHasBeenAdded)
        return preferences;
    
    CLCargoLifterPreferenceModule* myModule = [CLCargoLifterPreferenceModule sharedInstance]; // your singleton for controlling preferences
    NSString* myModuleName = [CLMailBundle preferencesPanelName];
    
    if ([preferences valueForKey:@"_preferenceModules"] && ![[preferences valueForKey:@"_preferenceModules"] containsObject:myModule])
    {
        [preferences addPreferenceNamed:myModuleName owner:myModule];
    }
    
    // add the preference item to the toolbar, if not yet there
    if (preferences!=nil && !_cargoLifterHasBeenAdded)
    {
        NSArray * currentToolBarItems = [[[preferences valueForKey:@"_preferencesPanel"] toolbar] items];
        
        // just be sure it isn't there
        for (NSToolbarItem* tbItem in currentToolBarItems)
        {
            if ([[tbItem itemIdentifier] isEqualToString:myModuleName])
            {
                _cargoLifterHasBeenAdded = YES;
            }
        }
        
        if (!_cargoLifterHasBeenAdded)
        {
            [[[preferences valueForKey:@"_preferencesPanel"] toolbar] insertItemWithItemIdentifier:myModuleName atIndex:[currentToolBarItems count]];
            _cargoLifterHasBeenAdded = YES;
        }
    }
    return preferences;
}

+ (void) load
{
    // add our methods as category
    CLAddClassAsCategory([self class], @class(NSPreferences));
    
    // swizzling
    NSError* swizzleError = nil;
    [@class(NSPreferences) jr_swizzleClassMethod:@selector(sharedPreferences) withClassMethod:@selector(cargoLifter_sharedPreferences) error:&swizzleError];
    if(swizzleError) NSLog(@"💥 CARGOLIFTER: Swizzle Error: %@", swizzleError);
    
    NSAssert(swizzleError==nil, @"Something went wrong during method swizzling: %@", swizzleError);
}

@end

// crazy helper function
void* FOOGetIvar(id object, const char* name, const char* typeEncodingPrefix)
{
    if( object == nil )
        return NULL;
    
    Ivar ivar = object_getInstanceVariable(object, name, NULL);
    if( ivar == NULL )
        return NULL;
    if( typeEncodingPrefix != NULL)
    {
        const char* typeEncoding = ivar_getTypeEncoding(ivar);
        if( strncmp( typeEncoding, typeEncodingPrefix, strlen(typeEncodingPrefix)) != 0 )
            return NULL;
    }
    return (void *)((char *)object + ivar_getOffset(ivar));
}
