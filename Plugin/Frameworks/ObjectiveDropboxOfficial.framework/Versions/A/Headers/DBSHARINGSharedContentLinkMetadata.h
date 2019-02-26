///
/// Copyright (c) 2016 Dropbox, Inc. All rights reserved.
///
/// Auto-generated by Stone, do not modify.
///

#import <Foundation/Foundation.h>

#import "DBSHARINGSharedContentLinkMetadataBase.h"
#import "DBSerializableProtocol.h"

@class DBSHARINGLinkAudience;
@class DBSHARINGLinkPermission;
@class DBSHARINGSharedContentLinkMetadata;

NS_ASSUME_NONNULL_BEGIN

#pragma mark - API Object

///
/// The `SharedContentLinkMetadata` struct.
///
/// Metadata of a shared link for a file or folder.
///
/// This class implements the `DBSerializable` protocol (serialize and
/// deserialize instance methods), which is required for all Obj-C SDK API route
/// objects.
///
@interface DBSHARINGSharedContentLinkMetadata : DBSHARINGSharedContentLinkMetadataBase <DBSerializable, NSCopying>

#pragma mark - Instance fields

/// The URL of the link.
@property (nonatomic, readonly, copy) NSString *url;

#pragma mark - Constructors

///
/// Full constructor for the struct (exposes all instance variables).
///
/// @param audienceOptions The audience options that are available for the
/// content. Some audience options may be unavailable. For example, team_only
/// may be unavailable if the content is not owned by a user on a team. The
/// 'default' audience option is always available if the user can modify link
/// settings.
/// @param currentAudience The current audience of the link.
/// @param linkPermissions A list of permissions for actions you can perform on
/// the link.
/// @param passwordProtected Whether the link is protected by a password.
/// @param url The URL of the link.
/// @param expiry Whether the link has an expiry set on it. A link with an
/// expiry will have its  audience changed to members when the expiry is
/// reached.
///
/// @return An initialized instance.
///
- (instancetype)initWithAudienceOptions:(NSArray<DBSHARINGLinkAudience *> *)audienceOptions
                        currentAudience:(DBSHARINGLinkAudience *)currentAudience
                        linkPermissions:(NSArray<DBSHARINGLinkPermission *> *)linkPermissions
                      passwordProtected:(NSNumber *)passwordProtected
                                    url:(NSString *)url
                                 expiry:(nullable NSDate *)expiry;

///
/// Convenience constructor (exposes only non-nullable instance variables with
/// no default value).
///
/// @param audienceOptions The audience options that are available for the
/// content. Some audience options may be unavailable. For example, team_only
/// may be unavailable if the content is not owned by a user on a team. The
/// 'default' audience option is always available if the user can modify link
/// settings.
/// @param currentAudience The current audience of the link.
/// @param linkPermissions A list of permissions for actions you can perform on
/// the link.
/// @param passwordProtected Whether the link is protected by a password.
/// @param url The URL of the link.
///
/// @return An initialized instance.
///
- (instancetype)initWithAudienceOptions:(NSArray<DBSHARINGLinkAudience *> *)audienceOptions
                        currentAudience:(DBSHARINGLinkAudience *)currentAudience
                        linkPermissions:(NSArray<DBSHARINGLinkPermission *> *)linkPermissions
                      passwordProtected:(NSNumber *)passwordProtected
                                    url:(NSString *)url;

@end

#pragma mark - Serializer Object

///
/// The serialization class for the `SharedContentLinkMetadata` struct.
///
@interface DBSHARINGSharedContentLinkMetadataSerializer : NSObject

///
/// Serializes `DBSHARINGSharedContentLinkMetadata` instances.
///
/// @param instance An instance of the `DBSHARINGSharedContentLinkMetadata` API
/// object.
///
/// @return A json-compatible dictionary representation of the
/// `DBSHARINGSharedContentLinkMetadata` API object.
///
+ (NSDictionary *)serialize:(DBSHARINGSharedContentLinkMetadata *)instance;

///
/// Deserializes `DBSHARINGSharedContentLinkMetadata` instances.
///
/// @param dict A json-compatible dictionary representation of the
/// `DBSHARINGSharedContentLinkMetadata` API object.
///
/// @return An instantiation of the `DBSHARINGSharedContentLinkMetadata` object.
///
+ (DBSHARINGSharedContentLinkMetadata *)deserialize:(NSDictionary *)dict;

@end

NS_ASSUME_NONNULL_END
