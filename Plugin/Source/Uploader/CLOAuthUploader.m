// Copyright (C) 2019 Mailbutler GmbH
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
//  CLOAuthUploader.m
//  CargoLifter
//
//  Created by Fabian Jäger on 13.01.19.
//  Copyright © 2019 Mailbutler. All rights reserved.
//

#import "CLOAuthUploader.h"

#import "AFOAuth2Manager.h"
#import "CLOAuthViewController.h"

@interface CLOAuthUploader ()
@property (strong) CLOAuthViewController* authViewController;
@end

@implementation CLOAuthUploader

- (void) authenticateWithWindow:(NSWindow *)window {
    self.authViewController = [[CLOAuthViewController alloc] init];

    self.service.linking = YES;

    [self.authViewController authorizeService:self attachedToWindow:window withHandler:^(BOOL success) {
        if(success) {
            [self postAuthenticationHookWithHandler:^(NSError *error) {
                [self.service markAsLinked:error==nil];

                if( [self.authDelegate respondsToSelector:@selector(didFinishAuthenticationWithError:)] )
                    [self.authDelegate didFinishAuthenticationWithError:error];
            }];
        } else {
            NSError* error = [NSError errorWithDomain:CLCargoLifterErrorDomain code:12345671 userInfo:@{NSLocalizedDescriptionKey:@"Failed to successfuly finish OAuth process."}];
            [self.service markAsLinked:NO];

            if( [self.authDelegate respondsToSelector:@selector(didFinishAuthenticationWithError:)] )
                [self.authDelegate didFinishAuthenticationWithError:error];
        }

        self.service.linking = NO;
    }];
}

- (void) deauthenticate {
    if(self.revokeTokenPath == nil) {
        [AFOAuthCredential deleteCredentialWithIdentifier:self.service.uniqueIdentifier];
        return;
    }
    
    AFOAuthCredential* credentials = [AFOAuthCredential retrieveCredentialWithIdentifier:self.service.uniqueIdentifier];

    AFHTTPSessionManager *generalManager = [[AFHTTPSessionManager alloc] initWithBaseURL:self.authBaseURL];

    [generalManager POST:self.revokeTokenPath parameters:@{@"client_id":self.clientID, @"client_secret":self.clientSecret,@"token":credentials.accessToken} progress:nil success:^(NSURLSessionDataTask * _Nonnull task, id  _Nullable responseObject) {
        NSLog(@"📯 CARGOLIFTER: Successfully revoked access.");

        // we are done here!
        [AFOAuthCredential deleteCredentialWithIdentifier:self.service.uniqueIdentifier];

    } failure:^(NSURLSessionDataTask * _Nullable task, NSError * _Nonnull error) {
        NSLog(@"💥 CARGOLIFTER: Could not revoke access: %@", error);
    }];
}

- (void) postAuthenticationHookWithHandler:(void (^)(NSError *error))completionBlock {
    // by default, do nothing
    completionBlock(nil);
}

- (void)_refreshAccessTokenWithSuccess:(void (^)(void))success failure:(void (^)(NSError *error))failure {
    AFOAuthCredential* credentials = [AFOAuthCredential retrieveCredentialWithIdentifier:self.service.uniqueIdentifier];

    if (credentials == nil || credentials.refreshToken == nil) {
        if (failure) {
            NSError *error = [NSError errorWithDomain:CLServiceAuthErrorDomain code:CLServiceAuthErrorCredentialsNotFound userInfo:@{NSLocalizedDescriptionKey:NSLocalizedString(@"Failed to get credentials",nil)}];
            failure(error);
        }

        [self.service markAsLinked:NO];

        return;
    }

    if (!credentials.isExpired) {
        NSLog(@"📯 CARGOLIFTER: refreshAccessTokenWithSuccess: credential has not expired");

        if (success)
            success();

        [self.service markAsLinked:YES];

        return;
    }

    AFOAuth2Manager *OAuth2Manager = [[AFOAuth2Manager alloc] initWithBaseURL:self.authBaseURL clientID:self.clientID secret:self.clientSecret];
    OAuth2Manager.useHTTPBasicAuthentication = NO;

    [OAuth2Manager authenticateUsingOAuthWithURLString:self.refreshTokenPath refreshToken:credentials.refreshToken success:^(AFOAuthCredential *newCredential) {
        NSLog(@"📯 CARGOLIFTER: Successfully refreshed OAuth credentials %@", newCredential.accessToken);

        if( newCredential )
            [AFOAuthCredential storeCredential:newCredential withIdentifier:self.service.uniqueIdentifier];

        if (success)
            success();

        [self.service markAsLinked:YES];

    } failure:^(NSError *error) {
        NSLog(@"💥 CARGOLIFTER: An error occurred refreshing credential: %@", error);
        if (failure) {
            failure(error);
        }

        [self.service markAsLinked:NO];
    }];
}

@end
