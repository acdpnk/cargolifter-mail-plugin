//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


@interface MSExternalAction : NSObject
{
    BOOL _remote;
    long long _sequenceNumber;
}

+ (id)entityName;
- (void)_msExternalActionCommonInitWithSequenceNumber:(long long)arg1;
- (id)init;
- (id)initWithManagedObject:(id)arg1;
- (id)managedObjectForContext:(id)arg1;
@property BOOL remote; // @synthesize remote=_remote;
@property long long sequenceNumber; // @synthesize sequenceNumber=_sequenceNumber;

@end

