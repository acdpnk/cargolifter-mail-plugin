//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header

#pragma mark Blocks

typedef void (^id)(void); // return type and parameters are unknown

#pragma mark Named Structures

struct CGSize {
    double _field1;
    double _field2;
};

struct _NSRange {
    NSUInteger location;
    NSUInteger length;
};

struct re_guts;

#pragma mark Typedef'd Structures

typedef struct {
    unsigned char _field1;
    unsigned char _field2;
    unsigned char _field3;

typedef struct {
    NSUInteger _field1;
    NSUInteger _field2;
    char _field3;
    char _field4;

typedef struct {
    long long _field1;
    NSUInteger _field2;

typedef struct {
    long long _field1;
    long long _field2;

typedef struct {
    unsigned short _field1[64];
    struct __CFString *_field2;
    unsigned short *_field3;
    char *_field4;
    long long _field6;
    long long _field7;

typedef struct {
    int re_magic;
    NSUInteger re_nsub;
    char *re_endp;
    struct re_guts *re_g;

