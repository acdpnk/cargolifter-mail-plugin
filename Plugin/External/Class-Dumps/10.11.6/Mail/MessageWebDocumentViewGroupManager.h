//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


@class MUIWebDocumentViewGroup;

@interface MessageWebDocumentViewGroupManager : NSObject
{
    MUIWebDocumentViewGroup *_viewGroup;
}

+ (id)allocWithZone:(struct _NSZone *)arg1;
+ (id)sharedInstance;
- (void)dealloc;
- (id)init;
- (void)observeValueForKeyPath:(id)arg1 ofObject:(id)arg2 change:(id)arg3 context:(void *)arg4;
@property(retain, nonatomic) MUIWebDocumentViewGroup *viewGroup; // @synthesize viewGroup=_viewGroup;

@end

