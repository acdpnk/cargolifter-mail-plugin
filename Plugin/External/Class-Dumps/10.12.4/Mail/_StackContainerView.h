//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header



@class MailStackViewController, NSString;

@interface _StackContainerView : NSView <NSAccessibilityGroup, NSDraggingSource>
{
    MailStackViewController *_controller;
}

- (id)accessibilityLabel;
@property(nonatomic) __weak MailStackViewController *controller; // @synthesize controller=_controller;
- (NSUInteger)draggingSession:(id)arg1 sourceOperationMaskForDraggingContext:(long long)arg2;
- (void)mouseDragged:(id)arg1;
- (void)mui_performAnimation;
- (void)mui_prepareToAnimate:(id)arg1;
- (void)mui_prepareToLayoutSynchronously:(id)arg1;
- (void)viewDidEndLiveResize;

// Remaining properties
@property(readonly, copy) NSString *debugDescription;
@property(readonly, copy) NSString *description;
@property(readonly) NSUInteger hash;
@property(readonly) Class superclass;

@end
