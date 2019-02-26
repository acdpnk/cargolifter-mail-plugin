//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


@class NSArray, NSDictionary, NSIndexSet, NSMutableArray, NSMutableIndexSet;

@interface _MFRedundantTextIdentifierSolutionContext : NSObject
{
    NSMutableArray *_redundantRanges;
    NSMutableIndexSet *_redundantAttachmentStartIndexes;
    NSMutableArray *_attributionLineRanges;
    BOOL _searchInForwardDirection;
    BOOL _matchedEntireOriginalContiguously;
    long long _replyStartIndex;
    long long _replyLength;
    long long _originalStartIndex;
    long long _originalLength;
    NSDictionary *_originalAttachmentContextsByURL;
    NSDictionary *_replyAttachmentContextsByURL;
    NSUInteger _startingIndexForRedundantRanges;
    NSUInteger _startingIndexForAttributionLineRanges;
    long long _lastIndexMatchedInOriginal;
    long long _lastIndexMatchedInReply;
}

- (void)addAttributionLineRanges:(id)arg1;
- (void)addRangeWithStart:(long long)arg1 end:(long long)arg2 toArray:(id)arg3;
- (void)addRedundantAttachmentStartIndexes:(id)arg1;
- (void)addRedundantRanges:(id)arg1;
@property(readonly, copy, nonatomic) NSArray *attributionLineRanges;
- (void)computeAttributionRangesInReply;
- (void)computeRedundantRangesInReply;
- (long long)contentTypeForIndex:(long long)arg1;
- (id)description;
- (id)init;
@property(nonatomic) long long lastIndexMatchedInOriginal; // @synthesize lastIndexMatchedInOriginal=_lastIndexMatchedInOriginal;
@property(nonatomic) long long lastIndexMatchedInReply; // @synthesize lastIndexMatchedInReply=_lastIndexMatchedInReply;
- (BOOL)location:(long long)arg1 isInRangeArray:(id)arg2 startingIndex:(NSUInteger *)arg3;
@property(nonatomic) BOOL matchedEntireOriginalContiguously; // @synthesize matchedEntireOriginalContiguously=_matchedEntireOriginalContiguously;
@property(readonly, copy, nonatomic) NSDictionary *originalAttachmentContextsByURL; // @synthesize originalAttachmentContextsByURL=_originalAttachmentContextsByURL;
@property(readonly, nonatomic) long long originalLength; // @synthesize originalLength=_originalLength;
@property(nonatomic) long long originalStartIndex; // @synthesize originalStartIndex=_originalStartIndex;
@property(readonly, copy, nonatomic) NSIndexSet *redundantAttachmentStartIndexes;
@property(readonly, copy, nonatomic) NSArray *redundantRanges;
@property(readonly, copy, nonatomic) NSDictionary *replyAttachmentContextsByURL; // @synthesize replyAttachmentContextsByURL=_replyAttachmentContextsByURL;
@property(readonly, nonatomic) long long replyLength; // @synthesize replyLength=_replyLength;
@property(nonatomic) long long replyStartIndex; // @synthesize replyStartIndex=_replyStartIndex;
@property(nonatomic) BOOL searchInForwardDirection; // @synthesize searchInForwardDirection=_searchInForwardDirection;
@property(nonatomic) NSUInteger startingIndexForAttributionLineRanges; // @synthesize startingIndexForAttributionLineRanges=_startingIndexForAttributionLineRanges;
@property(nonatomic) NSUInteger startingIndexForRedundantRanges; // @synthesize startingIndexForRedundantRanges=_startingIndexForRedundantRanges;

@end
