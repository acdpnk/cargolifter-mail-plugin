//
//  ITSwitch.h
//  ITSwitch-Demo
//
//  Created by Ilija Tovilo on 01/02/14.
//  Copyright (c) 2014 Ilija Tovilo. All rights reserved.
//

#import <Cocoa/Cocoa.h>

/**
 *  ITSwitch is a replica of UISwitch for Mac OS X
 */
IB_DESIGNABLE
@interface ITSwitch : NSButton

/**
 *  @property onColor - Gets or sets the switches on color
 */
@property (nonatomic, strong) IBInspectable NSColor *onColor;

/**
 *  @property onColor - Gets or sets the switches off color
 */
@property (nonatomic, strong) IBInspectable NSColor *offColor;

/**
 *  @property color - Gets or sets the switches current color (overrides on/off colors)
 */
@property (nonatomic, strong) IBInspectable NSColor *color;

/**
 *  @property drawShadow - Gets or sets whether the knob has a shadow
 */
@property (nonatomic, assign) IBInspectable BOOL drawShadow;

@property (nonatomic, assign) BOOL intermediateState;

@end
