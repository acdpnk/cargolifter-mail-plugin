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
#import "CLMenuButton.h"

#define LABEL_OFFSET_X	1
#define LABEL_OFFSET_Y	-1

@implementation CLMenuButton

//
- (id)copyWithZone:(NSZone *)zone
{
	CLMenuButton *newButton = [[[self class] allocWithZone:zone] initWithFrame:self.frame];
	
	newButton.menu = [self.menu copy];
	
	return newButton;
}

- (instancetype)initWithFrame:(NSRect)frameRect
{
	if ((self = [super initWithFrame:frameRect])) {
		//Default title and image
		self.title = @"";
		self.bezelStyle = NSSmallSquareBezelStyle;
	}
	
	return self;    
}

- (void)sizeToFit
{		
	[super sizeToFit];
	
	NSRect frame = self.frame;
	frame.size.width += LABEL_OFFSET_X * 2;
	
	self.frame = frame;
}

//silly NSControl...
- (void)setMenu:(NSMenu *)menu {
	super.menu = menu;
	self.cell.menu = menu;
}

//Mouse Tracking -------------------------------------------------------------------------------------------------------
#pragma mark Mouse Tracking
//Custom mouse down tracking to display our menu and highlight
- (void)mouseDown:(NSEvent *)theEvent
{
	if (!self.menu) {
		[super mouseDown:theEvent];
	} else {
		if (self.enabled) {
			[self highlight:YES];
			
			//2 pt down, 1 pt to the left.
			NSPoint point = [self convertPoint:self.bounds.origin toView:nil];
			point.y -= NSHeight(self.frame) + 2;
			point.x -= 1;
			
			NSEvent *event = [NSEvent mouseEventWithType:theEvent.type
												location:point
										   modifierFlags:theEvent.modifierFlags
											   timestamp:theEvent.timestamp
											windowNumber:theEvent.window.windowNumber
												 context:theEvent.context
											 eventNumber:theEvent.eventNumber
											  clickCount:theEvent.clickCount
												pressure:theEvent.pressure];
			[NSMenu popUpContextMenu:self.menu withEvent:event forView:self];
			
			[self mouseUp:[NSApplication sharedApplication].currentEvent];
		}
	}
}

//Remove highlight on mouse up
- (void)mouseUp:(NSEvent *)theEvent
{
	[self highlight:NO];
	[super mouseUp:theEvent];
}

//Ignore dragging
- (void)mouseDragged:(NSEvent *)theEvent
{
	//Empty
}

@end
