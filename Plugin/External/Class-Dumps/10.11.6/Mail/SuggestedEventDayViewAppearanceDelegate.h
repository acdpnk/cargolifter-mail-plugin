//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header

#import "CalUIDayViewGadgetDefaultAppearance.h"

@class EKEvent;

@interface SuggestedEventDayViewAppearanceDelegate : CalUIDayViewGadgetDefaultAppearance
{
    EKEvent *_displayedEvent;
}

- (long long)backgroundStyle;
- (id)displayEnd;
- (id)displayStart;
- (long long)displayType;
@property(retain, nonatomic) EKEvent *displayedEvent; // @synthesize displayedEvent=_displayedEvent;
- (double)hourHeight;
- (BOOL)shouldAllDayEventsShowColorBar;
- (BOOL)shouldDisplayCurrentTime;
- (BOOL)shouldDisplayPreviewEventsAsTentative;

@end
