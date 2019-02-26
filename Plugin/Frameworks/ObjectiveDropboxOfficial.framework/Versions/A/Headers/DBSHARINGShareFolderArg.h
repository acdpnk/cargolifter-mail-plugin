///
/// Copyright (c) 2016 Dropbox, Inc. All rights reserved.
///
/// Auto-generated by Stone, do not modify.
///

#import <Foundation/Foundation.h>

#import "DBSerializableProtocol.h"

@class DBSHARINGAclUpdatePolicy;
@class DBSHARINGFolderAction;
@class DBSHARINGLinkSettings;
@class DBSHARINGMemberPolicy;
@class DBSHARINGShareFolderArg;
@class DBSHARINGSharedLinkPolicy;
@class DBSHARINGViewerInfoPolicy;

NS_ASSUME_NONNULL_BEGIN

#pragma mark - API Object

///
/// The `ShareFolderArg` struct.
///
/// This class implements the `DBSerializable` protocol (serialize and
/// deserialize instance methods), which is required for all Obj-C SDK API route
/// objects.
///
@interface DBSHARINGShareFolderArg : NSObject <DBSerializable, NSCopying>

#pragma mark - Instance fields

/// The path to the folder to share. If it does not exist, then a new one is
/// created.
@property (nonatomic, readonly, copy) NSString *path;

/// Who can be a member of this shared folder. Only applicable if the current
/// user is on a team.
@property (nonatomic, readonly, nullable) DBSHARINGMemberPolicy *memberPolicy;

/// Who can add and remove members of this shared folder.
@property (nonatomic, readonly, nullable) DBSHARINGAclUpdatePolicy *aclUpdatePolicy;

/// The policy to apply to shared links created for content inside this shared
/// folder.  The current user must be on a team to set this policy to `members`
/// in `DBSHARINGSharedLinkPolicy`.
@property (nonatomic, readonly, nullable) DBSHARINGSharedLinkPolicy *sharedLinkPolicy;

/// Whether to force the share to happen asynchronously.
@property (nonatomic, readonly) NSNumber *forceAsync;

/// This is a list indicating whether each returned folder data entry will
/// include a boolean field `allow` in `DBSHARINGFolderPermission` that
/// describes whether the current user can perform the `FolderAction` on the
/// folder.
@property (nonatomic, readonly, nullable) NSArray<DBSHARINGFolderAction *> *actions;

/// Settings on the link for this folder.
@property (nonatomic, readonly, nullable) DBSHARINGLinkSettings *linkSettings;

/// Who can enable/disable viewer info for this shared folder.
@property (nonatomic, readonly, nullable) DBSHARINGViewerInfoPolicy *viewerInfoPolicy;

#pragma mark - Constructors

///
/// Full constructor for the struct (exposes all instance variables).
///
/// @param path The path to the folder to share. If it does not exist, then a
/// new one is created.
/// @param memberPolicy Who can be a member of this shared folder. Only
/// applicable if the current user is on a team.
/// @param aclUpdatePolicy Who can add and remove members of this shared folder.
/// @param sharedLinkPolicy The policy to apply to shared links created for
/// content inside this shared folder.  The current user must be on a team to
/// set this policy to `members` in `DBSHARINGSharedLinkPolicy`.
/// @param forceAsync Whether to force the share to happen asynchronously.
/// @param actions This is a list indicating whether each returned folder data
/// entry will include a boolean field `allow` in `DBSHARINGFolderPermission`
/// that describes whether the current user can perform the `FolderAction` on
/// the folder.
/// @param linkSettings Settings on the link for this folder.
/// @param viewerInfoPolicy Who can enable/disable viewer info for this shared
/// folder.
///
/// @return An initialized instance.
///
- (instancetype)initWithPath:(NSString *)path
                memberPolicy:(nullable DBSHARINGMemberPolicy *)memberPolicy
             aclUpdatePolicy:(nullable DBSHARINGAclUpdatePolicy *)aclUpdatePolicy
            sharedLinkPolicy:(nullable DBSHARINGSharedLinkPolicy *)sharedLinkPolicy
                  forceAsync:(nullable NSNumber *)forceAsync
                     actions:(nullable NSArray<DBSHARINGFolderAction *> *)actions
                linkSettings:(nullable DBSHARINGLinkSettings *)linkSettings
            viewerInfoPolicy:(nullable DBSHARINGViewerInfoPolicy *)viewerInfoPolicy;

///
/// Convenience constructor (exposes only non-nullable instance variables with
/// no default value).
///
/// @param path The path to the folder to share. If it does not exist, then a
/// new one is created.
///
/// @return An initialized instance.
///
- (instancetype)initWithPath:(NSString *)path;

- (instancetype)init NS_UNAVAILABLE;

@end

#pragma mark - Serializer Object

///
/// The serialization class for the `ShareFolderArg` struct.
///
@interface DBSHARINGShareFolderArgSerializer : NSObject

///
/// Serializes `DBSHARINGShareFolderArg` instances.
///
/// @param instance An instance of the `DBSHARINGShareFolderArg` API object.
///
/// @return A json-compatible dictionary representation of the
/// `DBSHARINGShareFolderArg` API object.
///
+ (NSDictionary *)serialize:(DBSHARINGShareFolderArg *)instance;

///
/// Deserializes `DBSHARINGShareFolderArg` instances.
///
/// @param dict A json-compatible dictionary representation of the
/// `DBSHARINGShareFolderArg` API object.
///
/// @return An instantiation of the `DBSHARINGShareFolderArg` object.
///
+ (DBSHARINGShareFolderArg *)deserialize:(NSDictionary *)dict;

@end

NS_ASSUME_NONNULL_END
