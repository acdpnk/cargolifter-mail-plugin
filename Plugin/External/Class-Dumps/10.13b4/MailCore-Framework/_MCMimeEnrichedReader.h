//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


@class NSMutableArray, NSMutableString;

@interface _MCMimeEnrichedReader : NSObject
{
    long long _currentIndex;
    long long _inputLength;
    unsigned int _noFillLevel:30;
    unsigned int _eatOneNewline:1;
    unsigned int _insideComment:1;
    long long _lastQuoteLevel;
    NSMutableArray *_commandStack;
    NSMutableString *_outputString;
    NSMutableString *_outputBuffer;
    BOOL outputShouldBeHTML;
}

- (void)appendStringToBuffer:(id)arg1;
- (void)beginCommand:(id)arg1;
- (void)closeUpQuoting;
- (void)convertEnrichedString:(id)arg1 intoOutputString:(id)arg2;
- (void)convertEnrichedString:(id)arg1 intoPlainOutputString:(id)arg2;
- (void)convertRichTextString:(id)arg1 intoOutputString:(id)arg2;
- (id)copyCommand;
- (id)copyNextTokenWithDelimiters:(id)arg1;
- (id)currentFont;
- (id)debugDescription;
- (id)description;
- (void)endCommand:(id)arg1;
- (void)fixConsecutiveSpaces:(id)arg1;
- (id)init;
- (void)nowWouldBeAGoodTimeToAppendToTheAttributedString;
- (id)parenthesesSet;
- (void)parseParameterString:(id)arg1;
- (id)punctuationSet;
- (long long)readTokenInto:(id *)arg1;
- (void)resetStateWithString:(id)arg1 outputString:(id)arg2;
- (void)setupFontStackEntry:(id)arg1;

@end
