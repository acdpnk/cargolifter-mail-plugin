//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


@class NSString;

@interface StationeryDynamicElement : NSObject
{
    NSString *_dateFormat;
    long long _type;
}

+ (id)dynamicElementFromDOMElement:(id)arg1;
- (void)_setDateFormat:(id)arg1;
- (id)description;
- (id)fragmentToReplaceHTMLObjectBackEnd:(id)arg1;
- (id)init;
- (id)initWithType:(long long)arg1;
@property(readonly, nonatomic) long long type; // @synthesize type=_type;

@end

