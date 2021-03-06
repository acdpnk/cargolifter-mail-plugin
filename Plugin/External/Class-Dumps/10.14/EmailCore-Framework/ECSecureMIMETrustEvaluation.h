//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//
#pragma clang system_header


@class NSError, NSString;

@interface ECSecureMIMETrustEvaluation : NSObject
{
    unsigned int _trustResult;
    struct __SecTrust *_trust;
    NSString *_signerEmailAddress;
    NSUInteger _options;
    NSError *_error;
}

+ (id)anchorCertificatesForTesting;
+ (id)evaluateTrust:(struct __SecTrust *)arg1 withOptions:(NSUInteger)arg2 signerEmailAddress:(id)arg3;
+ (id)log;
+ (id)reevaluateWithNetworkAccessAllowed:(id)arg1;
+ (void)setAnchorCertificatesForTesting:(id)arg1;
- (void)_evaluate;
- (id)_initWithTrust:(struct __SecTrust *)arg1 options:(NSUInteger)arg2 signerEmailAddress:(id)arg3;
- (void)dealloc;
- (id)description;
@property(readonly, nonatomic) NSError *error; // @synthesize error=_error;
@property(readonly, nonatomic) NSUInteger options; // @synthesize options=_options;
@property(readonly, nonatomic) BOOL requiresReevaluationWithNetworkAccess;
@property(readonly, copy, nonatomic) NSString *signerEmailAddress; // @synthesize signerEmailAddress=_signerEmailAddress;
@property(readonly, nonatomic) struct __SecTrust *trust; // @synthesize trust=_trust;
@property(readonly, nonatomic) unsigned int trustResult; // @synthesize trustResult=_trustResult;

@end

