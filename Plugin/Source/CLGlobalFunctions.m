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
//  CLCargoLifterFunctions.m
//  CargoLifter
//
//  Created by Fabian Jäger on 15/09/15.
//  Copyright (c) 2015 Mailbutler. All rights reserved.
//

#import "CLGlobalFunctions.h"
#import "NSImage+CLAdditions.h"
#import "NSAlert+SynchronousSheet.h"

NSString* CLNextAvailableFilePath(NSString* filePath)
{
    NSString* pathExtension = [filePath pathExtension];
    NSString* pathWithoutExtension = [filePath stringByDeletingPathExtension];
    
    NSFileManager* fm = [NSFileManager defaultManager];
    
    NSString* finalPath = filePath;
    
    if( [fm fileExistsAtPath:finalPath] )
    {
        for (NSUInteger numDuplicates = 1; numDuplicates < 999; numDuplicates++)
        {
            finalPath = [NSString stringWithFormat:@"%@-%ld.%@",pathWithoutExtension, numDuplicates, pathExtension];
            if( ![fm fileExistsAtPath:finalPath] )
                break;
        }
    }
    
    return finalPath;
}

NSInteger CLRunAlertPanel(NSString *title, NSString *msgFormat, NSArray* buttonTitles, ...)
{
    va_list args;
    va_start(args, buttonTitles);
    
    NSString* message = [[NSString alloc] initWithFormat:msgFormat arguments:args];
    
    NSAlert* alert = [[NSAlert alloc] init];
    alert.window.title = title;
    
    alert.messageText = title;
    
    for(NSString* aTitle in buttonTitles)
        [alert addButtonWithTitle:aTitle];
    
    alert.informativeText = message;

#ifdef PLUGIN_BUNDLE
    NSString* bundleName = [PLUGIN_BUNDLE objectForInfoDictionaryKey:@"CFBundleName"];
    NSImage* image = [NSImage cl_pluginImageNamed:bundleName];
    alert.icon = image;
#endif

    [alert.window setLevel:NSPopUpMenuWindowLevel];
    
    va_end(args);
    
    return [alert runModal];
}
