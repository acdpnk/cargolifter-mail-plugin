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
//  CompatibilityHelper.c
//  CargoLifter
//
//  Created by Fabian Jäger on 04.05.17.
//  Copyright © 2017 Mailbutler. All rights reserved.
//

#import "CompatibilityHelper.h"

Class CLClassFromString(NSString* className)
{
    static NSMutableDictionary * classNameLookup =nil;
    static NSRecursiveLock * threadlock = nil;
    if (!threadlock) {
        threadlock = [[NSRecursiveLock alloc] init];
        classNameLookup = [[NSMutableDictionary alloc] init];
    }
    
    Class resultClass =nil;
    [threadlock lock];
    resultClass = classNameLookup[className];
    [threadlock unlock];
    if (resultClass){
        return resultClass;
    }
    else{
        resultClass = NSClassFromString(className);
        if (!resultClass){
            resultClass = NSClassFromString([@"MF" stringByAppendingString:className]);
        }
        if (!resultClass){
            resultClass = NSClassFromString([@"MC" stringByAppendingString:className]);
        }
        if (!resultClass){
            NSLog(@"FATAL ERROR: Could not find a class for %@", className);
            return nil;
        }
        else{
            [threadlock lock];
            classNameLookup[className] = resultClass;
            [threadlock unlock];
        }
        // NSLog(@"found class %@ -->%@",className,resultClass);
        return resultClass;
        
    }
    return nil;
}

void CLAddClassAsCategory(Class srcClass, Class targetClass)
{
    unsigned int theCount = 0;
    Method* theMethods = class_copyMethodList(object_getClass(srcClass), &theCount);
    Class theClass = object_getClass(targetClass);
    unsigned int i = 0;
    
    while (YES)
    {
        for (i = 0; i < theCount; i++)
        {
            if (
                !class_addMethod(
                                 theClass,
                                 method_getName(theMethods[i]),
                                 method_getImplementation(theMethods[i]),
                                 method_getTypeEncoding(theMethods[i])
                                 )
                )
            {
                NSLog(
                      @"FATAL ERROR: Could not add method %@ to %@",
                      NSStringFromSelector(method_getName(theMethods[i])),
                      targetClass
                      );
            }
        }
        
        if (theMethods != nil)
        {
            free(theMethods);
        }
        
        if (theClass != targetClass)
        {
            theClass = targetClass;
            theMethods = class_copyMethodList(srcClass, &theCount);
        }
        else
        {
            break;
        }
    }
}
