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
//  CLOAuthUploader.h
//  CargoLifter
//
//  Created by Fabian Jäger on 13.01.19.
//  Copyright © 2019 Mailbutler. All rights reserved.
//

#import "CLUploader.h"

NS_ASSUME_NONNULL_BEGIN

@interface CLOAuthUploader : CLUploader

@property (readonly) NSString* clientID;
@property (readonly) NSString* clientSecret;

@property (readonly) NSURL* oauthStartURL;
@property (readonly) NSURL* authBaseURL;
@property (readonly) NSURL* redirectURL;

@property (readonly) NSString* getTokenPath;
@property (readonly) NSString* refreshTokenPath;
@property (readonly) NSString* revokeTokenPath;

- (void)_refreshAccessTokenWithSuccess:(void (^)(void))success failure:(void (^)(NSError *error))failure;

@end

NS_ASSUME_NONNULL_END
