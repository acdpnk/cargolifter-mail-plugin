//
//  ITSwitch.m
//  ITSwitch-Demo
//
//  Created by Ilija Tovilo on 01/02/14.
//  Copyright (c) 2014 Ilija Tovilo. All rights reserved.
//

#import "ITSwitch.h"
#import <QuartzCore/QuartzCore.h>


// ----------------------------------------------------
#pragma mark - Static Constants
// ----------------------------------------------------

static NSTimeInterval const kAnimationDuration = 0.4f;

static CGFloat const kBorderLineWidth = 1.f;

static CGFloat const kGoldenRatio = 1.61803398875f;
static CGFloat const kDecreasedGoldenRatio = 1.38;

static CGFloat const kEnabledOpacity = 1.f;
static CGFloat const kDisabledOpacity = 0.5f;

// ----------------------------------------------------
#pragma mark - Preprocessor
// ----------------------------------------------------


#define kKnobBackgroundColor [NSColor colorWithCalibratedWhite:1.f alpha:1.f]

#define kDefaultOffColor    [NSColor colorWithCalibratedRed:0.87 green:0.87 blue:0.87 alpha:1.0]
#define kDefaultOnColor     [NSColor colorWithCalibratedRed:0.20 green:0.78 blue:0.29 alpha:1.0]

// ---------------------------------------------------------------------------------------
#pragma mark - Interface Extension
// ---------------------------------------------------------------------------------------

@interface ITSwitch () {
    
}

@property (nonatomic, getter = isActive) BOOL active;
@property (nonatomic, getter = hasDragged) BOOL dragged;
@property (nonatomic, getter = isDraggingTowardsOn) BOOL draggingTowardsOn;

@property (nonatomic, readonly, strong) CALayer *rootLayer;
@property (nonatomic, readonly, strong) CALayer *backgroundLayer;
@property (nonatomic, readonly, strong) CALayer *knobLayer;
@property (nonatomic, readonly, strong) CALayer *knobInsideLayer;

- (void)propagateValue:(id)value forBinding:(NSString*)binding;

@end



// ---------------------------------------------------------------------------------------
#pragma mark - ITSwitch
// ---------------------------------------------------------------------------------------

@implementation ITSwitch
@synthesize onColor = _onColor;
@synthesize offColor = _offColor;
@synthesize color = _color;

// ----------------------------------------------------
#pragma mark - Init
// ----------------------------------------------------

- (id)initWithCoder:(NSCoder *)coder {
    self = [super initWithCoder:coder];
    if (!self) return nil;
    
    [self setUp];
    
    return self;
}

- (id)initWithFrame:(NSRect)frame {
    self = [super initWithFrame:frame];
    if (!self) return nil;
    
    [self setUp];
    
    return self;
}

- (void) awakeFromNib {
    [super awakeFromNib];
    
    [self setUp];
    
    if(!self.onColor)
        self.onColor = kDefaultOnColor;
    if(!self.offColor)
        self.offColor = kDefaultOffColor;
}

- (void)setUp {
    // The Switch is enabled per default
    self.enabled = YES;
    
    self.allowsMixedState = NO;
    
    if(!self.toolTip || self.toolTip.length==0)
        self.toolTip = self.title;
    
    self.title = @"";
    
    // Set up the layer hierarchy
    [self setUpLayers];
}

- (void)setUpLayers {
    // Root layer
    _rootLayer = [CALayer layer];
    //_rootLayer.delegate = self;
    self.layer = _rootLayer;
    self.wantsLayer = YES;
    
    // Background layer
    _backgroundLayer = [CALayer layer];
    _backgroundLayer.autoresizingMask = kCALayerWidthSizable | kCALayerHeightSizable;
    _backgroundLayer.bounds = _rootLayer.bounds;
    _backgroundLayer.anchorPoint = (CGPoint){ .x = 0.f, .y = 0.f };
    _backgroundLayer.borderWidth = kBorderLineWidth;
    [_rootLayer addSublayer:_backgroundLayer];
    
    // Knob layer
    _knobLayer = [CALayer layer];
    _knobLayer.frame = [self rectForKnob];
    _knobLayer.autoresizingMask = kCALayerHeightSizable;
    _knobLayer.backgroundColor = [kKnobBackgroundColor CGColor];
    if(self.drawShadow) {
        _knobLayer.shadowColor = [[NSColor blackColor] CGColor];
        _knobLayer.shadowOffset = (CGSize){ .width = 0.f, .height = -2.f };
        _knobLayer.shadowRadius = 1.f;
        _knobLayer.shadowOpacity = 0.3f;
    }
    [_rootLayer addSublayer:_knobLayer];
    
    _knobInsideLayer = [CALayer layer];
    _knobInsideLayer.frame = _knobLayer.bounds;
    _knobInsideLayer.autoresizingMask = kCALayerWidthSizable | kCALayerHeightSizable;
    _knobInsideLayer.shadowColor = [[NSColor blackColor] CGColor];
    _knobInsideLayer.shadowOffset = (CGSize){ .width = 0.f, .height = 0.f };
    _knobInsideLayer.backgroundColor = [[NSColor whiteColor] CGColor];
    _knobInsideLayer.shadowRadius = 1.f;
    _knobInsideLayer.shadowOpacity = 0.35f;
    [_knobLayer addSublayer:_knobInsideLayer];
    
    // Initial
    [self reloadLayerSize];
    [self reloadLayer];
}



// ----------------------------------------------------
#pragma mark - NSView
// ----------------------------------------------------

- (BOOL)acceptsFirstMouse:(NSEvent *)theEvent {
    return YES;
}

- (void)setFrame:(NSRect)frameRect {
    [super setFrame:frameRect];
    
    [self reloadLayerSize];
}

- (void)drawFocusRingMask {
	CGFloat cornerRadius = NSHeight([self bounds])/2.0;
	NSBezierPath *path = [NSBezierPath bezierPathWithRoundedRect:[self bounds] xRadius:cornerRadius yRadius:cornerRadius];
	[[NSColor blackColor] set];
	[path fill];
}

- (BOOL)canBecomeKeyView {
	return [NSApp isFullKeyboardAccessEnabled];
}

- (NSRect)focusRingMaskBounds {
	return [self bounds];
}

- (void) drawRect:(NSRect)dirtyRect {
    return;
}

// ----------------------------------------------------
#pragma mark - Update Layer
// ----------------------------------------------------

- (void)reloadLayer {
    [CATransaction begin];
    [CATransaction setAnimationDuration:kAnimationDuration];
    {
        // ------------------------------- Animate Border
        // The green part also animates, which looks kinda weird
        // We'll use the background-color for now
        //        _backgroundLayer.borderWidth = (YES || self.isActive || self.isOn) ? NSHeight(_backgroundLayer.bounds) / 2 : kBorderLineWidth;
        
        // ------------------------------- Animate Colors
        if(self.color) {
            NSColor* color = [self.color colorUsingColorSpaceName:NSCalibratedRGBColorSpace];
            _backgroundLayer.borderColor = [[NSColor colorWithCalibratedHue:color.hueComponent saturation:color.saturationComponent brightness:color.brightnessComponent*0.91 alpha:color.alphaComponent] CGColor];
            _backgroundLayer.backgroundColor = [color CGColor];
        }
        else if (([self hasDragged] && [self isDraggingTowardsOn]) || (![self hasDragged] && self.state)) {
            NSColor* color = [self.onColor colorUsingColorSpaceName:NSCalibratedRGBColorSpace];
            _backgroundLayer.borderColor = [[NSColor colorWithCalibratedHue:color.hueComponent saturation:color.saturationComponent brightness:color.brightnessComponent*0.91 alpha:color.alphaComponent] CGColor];
            _backgroundLayer.backgroundColor = [color CGColor];
        } else {
            NSColor* color = [self.offColor colorUsingColorSpaceName:NSCalibratedRGBColorSpace];
            _backgroundLayer.borderColor = [[NSColor colorWithCalibratedHue:color.hueComponent saturation:color.saturationComponent brightness:color.brightnessComponent*0.8 alpha:color.alphaComponent] CGColor];
            _backgroundLayer.backgroundColor = [color CGColor];
        }
        
        // ------------------------------- Animate Enabled-Disabled state
        _rootLayer.opacity = (self.isEnabled) ? kEnabledOpacity : kDisabledOpacity;

        // ------------------------------- Animate Frame
        if (![self hasDragged]) {
            CAMediaTimingFunction *function = [CAMediaTimingFunction functionWithControlPoints:0.25f :1.5f :0.5f :1.f];
            [CATransaction setAnimationTimingFunction:function];
        }
        
        self.knobLayer.frame = [self rectForKnob];
        self.knobInsideLayer.frame = self.knobLayer.bounds;
    }
    [CATransaction commit];
}

- (void)reloadLayerSize {
    [CATransaction begin];
    [CATransaction setDisableActions:YES];
    {
        self.knobLayer.frame = [self rectForKnob];
        self.knobInsideLayer.frame = self.knobLayer.bounds;
        
        [_backgroundLayer setCornerRadius:_backgroundLayer.bounds.size.height / 2.f];
        [_knobLayer setCornerRadius:_knobLayer.bounds.size.height / 2.f];
        [_knobInsideLayer setCornerRadius:_knobLayer.bounds.size.height / 2.f];
    }
    [CATransaction commit];
}

- (CGFloat)knobHeightForSize:(NSSize)size
{
    return size.height - (kBorderLineWidth * 2.f);
}

- (CGRect)rectForKnob {
    CGFloat height = [self knobHeightForSize:_backgroundLayer.bounds.size];
    CGFloat width = ![self isActive] ? (NSWidth(_backgroundLayer.bounds) - 2.f * kBorderLineWidth) * 1.f / kGoldenRatio :
    (NSWidth(_backgroundLayer.bounds) - 2.f * kBorderLineWidth) * 1.f / kDecreasedGoldenRatio;
    CGFloat x = ((![self hasDragged] && !self.state) || (self.hasDragged && ![self isDraggingTowardsOn])) ?
    kBorderLineWidth :
    NSWidth(_backgroundLayer.bounds) - width - kBorderLineWidth;
    
    return (CGRect) {
        .size.width = width,
        .size.height = height,
        .origin.x = x,
        .origin.y = kBorderLineWidth,
    };
}



// ----------------------------------------------------
#pragma mark - NSResponder
// ----------------------------------------------------

- (BOOL)acceptsFirstResponder {
	return [NSApp isFullKeyboardAccessEnabled];
}

- (void)mouseDown:(NSEvent *)theEvent {
    if (!self.isEnabled) return;

    self.active = YES;
    
    [self reloadLayer];
}

- (void)mouseDragged:(NSEvent *)theEvent {
    if (!self.isEnabled) return;

    self.dragged = YES;
    
    NSPoint draggingPoint = [self convertPoint:[theEvent locationInWindow] fromView:nil];
    self.draggingTowardsOn = draggingPoint.x >= NSWidth(self.bounds) / 2.f;
    
    [self reloadLayer];
}

- (void)mouseUp:(NSEvent *)theEvent {
    if (!self.isEnabled) return;

    self.active = NO;
    
    BOOL checked = (![self hasDragged]) ? !self.state : [self isDraggingTowardsOn];
    BOOL invokeTargetAction = (checked != self.state);
    
    self.state = checked;
    if (invokeTargetAction) [self _invokeTargetAction];
    
    // Reset
    self.dragged = NO;
    self.draggingTowardsOn = NO;
    self.intermediateState = NO;
    
    [self reloadLayer];
}

- (void)moveLeft:(id)sender {
	if (self.state) {
		self.state = NSOffState;
		[self _invokeTargetAction];
	}
}

- (void)moveRight:(id)sender {
	if (!self.state) {
		self.state = NSOnState;
		[self _invokeTargetAction];
	}
}

- (BOOL)performKeyEquivalent:(NSEvent *)theEvent {
	BOOL handledKeyEquivalent = NO;
	if ([[self window] firstResponder] == self) {
		NSInteger ch = [theEvent keyCode];
		
		if (ch == 49) // space
		{
			self.state = !self.state;
			[self _invokeTargetAction];
			handledKeyEquivalent = YES;
		}
	}
	return handledKeyEquivalent;
}


// ----------------------------------------------------
#pragma mark - Accessors
// ----------------------------------------------------

- (void)setState:(NSInteger)state {
    
    if(state != self.state)
        self.intermediateState = NO;
    
    [super setState:state];
    
    [self reloadLayer];
}

- (void)setOnColor:(NSColor *)onColor {
    _onColor = onColor;
    
    [self reloadLayer];
}

- (void)setOffColor:(NSColor *)offColor {
    _offColor = offColor;
    
    [self reloadLayer];
}

- (void)setColor:(NSColor *)color {
    _color = color;
    
    [self reloadLayer];
}

- (void)setEnabled:(BOOL)enabled {
    [super setEnabled:enabled];
    [self reloadLayer];
}

- (void)setIntermediateState:(BOOL)intermediateState {
    _intermediateState = intermediateState;
    [self reloadLayer];
}

// -----------------------------------
#pragma mark - Helpers
// -----------------------------------

- (void)_invokeTargetAction {
    if (self.target && self.action) {
        NSMethodSignature *signature = [[self.target class] instanceMethodSignatureForSelector:self.action];
        NSInvocation *invocation = [NSInvocation invocationWithMethodSignature:signature];
        [invocation setTarget:self.target];
        [invocation setSelector:self.action];
        [invocation setArgument:(void *)&self atIndex:2];
        
        [invocation invoke];
    }
    
    [self propagateValue:@(self.state) forBinding:NSValueBinding];
}

// -----------------------------------
#pragma mark - Accessibility
// -----------------------------------

- (BOOL)accessibilityIsIgnored {
	return NO;
}

- (id)accessibilityHitTest:(NSPoint)point {
	return self;
}

- (NSArray *)accessibilityAttributeNames {
	static NSArray *attributes = nil;
	if (attributes == nil)
	{
		NSMutableArray *mutableAttributes = [[super accessibilityAttributeNames] mutableCopy];
		if (mutableAttributes == nil)
			mutableAttributes = [NSMutableArray new];
		
		// Add attributes
		if (![mutableAttributes containsObject:NSAccessibilityValueAttribute])
			[mutableAttributes addObject:NSAccessibilityValueAttribute];
		
		if (![mutableAttributes containsObject:NSAccessibilityEnabledAttribute])
			[mutableAttributes addObject:NSAccessibilityEnabledAttribute];
		
		if (![mutableAttributes containsObject:NSAccessibilityDescriptionAttribute])
			[mutableAttributes addObject:NSAccessibilityDescriptionAttribute];
		
		// Remove attributes
		if ([mutableAttributes containsObject:NSAccessibilityChildrenAttribute])
			[mutableAttributes removeObject:NSAccessibilityChildrenAttribute];
		
		attributes = [mutableAttributes copy];
	}
	return attributes;
}

- (id)accessibilityAttributeValue:(NSString *)attribute {
	id retVal = nil;
	if ([attribute isEqualToString:NSAccessibilityRoleAttribute])
		retVal = NSAccessibilityCheckBoxRole;
	else if ([attribute isEqualToString:NSAccessibilityValueAttribute])
		retVal = [NSNumber numberWithInteger:self.state];
	else if ([attribute isEqualToString:NSAccessibilityEnabledAttribute])
		retVal = [NSNumber numberWithBool:self.enabled];
	else
		retVal = [super accessibilityAttributeValue:attribute];
	return retVal;
}

- (BOOL)accessibilityIsAttributeSettable:(NSString *)attribute {
	BOOL retVal;
	if ([attribute isEqualToString:NSAccessibilityValueAttribute])
		retVal = YES;
	else if ([attribute isEqualToString:NSAccessibilityEnabledAttribute])
		retVal = NO;
	else if ([attribute isEqualToString:NSAccessibilityDescriptionAttribute])
		retVal = NO;
	else
		retVal = [super accessibilityIsAttributeSettable:attribute];
	return retVal;
}

- (void)accessibilitySetValue:(id)value forAttribute:(NSString *)attribute {
	if ([attribute isEqualToString:NSAccessibilityValueAttribute]) {
		BOOL invokeTargetAction = self.state != [value integerValue];
		self.state = [value integerValue];
		if (invokeTargetAction) {
			[self _invokeTargetAction];
		}
	}
	else {
		[super accessibilitySetValue:value forAttribute:attribute];
	}
}

- (NSArray *)accessibilityActionNames {
	static NSArray *actions = nil;
	if (actions == nil)
	{
		NSMutableArray *mutableActions = [[super accessibilityActionNames] mutableCopy];
		if (mutableActions == nil)
			mutableActions = [NSMutableArray new];
		if (![mutableActions containsObject:NSAccessibilityPressAction])
			[mutableActions addObject:NSAccessibilityPressAction];
		actions = [mutableActions copy];
	}
	return actions;
}

- (void)accessibilityPerformAction:(NSString *)actionString {
	if ([actionString isEqualToString:NSAccessibilityPressAction]) {
		self.state = !self.state;
		[self _invokeTargetAction];
	}
	else {
		[super accessibilityPerformAction:actionString];
	}
}

#pragma mark -
#pragma mark Bindings Extension

- (void)propagateValue:(id)value forBinding:(NSString*)binding
{
    NSParameterAssert(binding != nil);
    
    // WARNING: bindingInfo contains NSNull, so it must be accounted for
    NSDictionary* bindingInfo = [self infoForBinding:binding];
    if(!bindingInfo)
        return; //there is no binding
    
    // apply the value transformer, if one has been set
    NSDictionary* bindingOptions = [bindingInfo objectForKey:NSOptionsKey];
    if(bindingOptions){
        NSValueTransformer* transformer = [bindingOptions valueForKey:NSValueTransformerBindingOption];
        if(!transformer || (id)transformer == [NSNull null]){
            NSString* transformerName = [bindingOptions valueForKey:NSValueTransformerNameBindingOption];
            if(transformerName && (id)transformerName != [NSNull null]){
                transformer = [NSValueTransformer valueTransformerForName:transformerName];
            }
        }
        
        if(transformer && (id)transformer != [NSNull null]){
            if([[transformer class] allowsReverseTransformation]){
                value = [transformer reverseTransformedValue:value];
            } else {
                NSLog(@"WARNING: binding \"%@\" has value transformer, but it doesn't allow reverse transformations in %s", binding, __PRETTY_FUNCTION__);
            }
        }
    }
    
    id boundObject = [bindingInfo objectForKey:NSObservedObjectKey];
    if(!boundObject || boundObject == [NSNull null]){
        NSLog(@"ERROR: NSObservedObjectKey was nil for binding \"%@\" in %s", binding, __PRETTY_FUNCTION__);
        return;
    }
    
    NSString* boundKeyPath = [bindingInfo objectForKey:NSObservedKeyPathKey];
    if(!boundKeyPath || (id)boundKeyPath == [NSNull null]){
        NSLog(@"ERROR: NSObservedKeyPathKey was nil for binding \"%@\" in %s", binding, __PRETTY_FUNCTION__);
        return;
    }
    
    [boundObject setValue:value forKeyPath:boundKeyPath];
}

@end
