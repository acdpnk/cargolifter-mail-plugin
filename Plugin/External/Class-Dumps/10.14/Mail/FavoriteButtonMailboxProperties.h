//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


@class NSString;

@interface FavoriteButtonMailboxProperties : NSObject
{
    BOOL _isContainer;
    BOOL _isPreferredSelection;
    int _type;
    NSString *_persistentID;
    NSString *_selectedSubMailboxPersistentID;
    NSString *_displayName;
    NSString *_accountURLString;
}

@property(retain, nonatomic) NSString *accountURLString; // @synthesize accountURLString=_accountURLString;
- (id)dictionaryRepresentation;
@property(retain, nonatomic) NSString *displayName; // @synthesize displayName=_displayName;
- (id)init;
- (id)initWithDictionaryRepresentation:(id)arg1;
- (id)initWithPersistentID:(id)arg1 selectedSubMailboxPersistentID:(id)arg2 displayName:(id)arg3 accountURLString:(id)arg4 type:(int)arg5 isContainer:(BOOL)arg6 isPreferredSelection:(BOOL)arg7;
@property(nonatomic) BOOL isContainer; // @synthesize isContainer=_isContainer;
@property(nonatomic) BOOL isPreferredSelection; // @synthesize isPreferredSelection=_isPreferredSelection;
@property(retain, nonatomic) NSString *persistentID; // @synthesize persistentID=_persistentID;
@property(retain, nonatomic) NSString *selectedSubMailboxPersistentID; // @synthesize selectedSubMailboxPersistentID=_selectedSubMailboxPersistentID;
@property(nonatomic) int type; // @synthesize type=_type;

@end

