//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


@class ImportAssistant, NSArray, NSMutableArray, NSString;

@interface Importer : NSObject
{
    NSMutableArray *_importArray;
    BOOL _importCanceled;
    ImportAssistant *_delegate;
    NSArray *_importFields;
}

- (void)clearImportArray;
@property(readonly, nonatomic) NSUInteger countOfEnabledItems;
@property(readonly, nonatomic) NSUInteger countOfImportArray;
@property(retain, nonatomic) ImportAssistant *delegate; // @synthesize delegate=_delegate;
@property(readonly, copy, nonatomic) NSArray *importArray;
@property(nonatomic) BOOL importCanceled; // @synthesize importCanceled=_importCanceled;
@property(copy, nonatomic) NSArray *importFields; // @synthesize importFields=_importFields;
@property(readonly, copy, nonatomic) NSString *importFinishedText;
- (id)init;
- (void)insertObject:(id)arg1 inImportArrayAtIndex:(NSUInteger)arg2;
@property(readonly, copy, nonatomic) NSString *name;
- (void)sortImportArray;

@end

