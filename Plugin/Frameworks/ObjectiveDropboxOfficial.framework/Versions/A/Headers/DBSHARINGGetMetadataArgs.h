///
/// Copyright (c) 2016 Dropbox, Inc. All rights reserved.
///
/// Auto-generated by Stone, do not modify.
///

#import <Foundation/Foundation.h>

#import "DBSerializableProtocol.h"

@class DBSHARINGFolderAction;
@class DBSHARINGGetMetadataArgs;

NS_ASSUME_NONNULL_BEGIN

#pragma mark - API Object

///
/// The `GetMetadataArgs` struct.
///
/// This class implements the `DBSerializable` protocol (serialize and
/// deserialize instance methods), which is required for all Obj-C SDK API route
/// objects.
///
@interface DBSHARINGGetMetadataArgs : NSObject <DBSerializable, NSCopying>

#pragma mark - Instance fields

/// The ID for the shared folder.
@property (nonatomic, readonly, copy) NSString *sharedFolderId;

/// This is a list indicating whether the returned folder data will include a
/// boolean value  `allow` in `DBSHARINGFolderPermission` that describes whether
/// the current user can perform the  FolderAction on the folder.
@property (nonatomic, readonly, nullable) NSArray<DBSHARINGFolderAction *> *actions;

#pragma mark - Constructors

///
/// Full constructor for the struct (exposes all instance variables).
///
/// @param sharedFolderId The ID for the shared folder.
/// @param actions This is a list indicating whether the returned folder data
/// will include a boolean value  `allow` in `DBSHARINGFolderPermission` that
/// describes whether the current user can perform the  FolderAction on the
/// folder.
///
/// @return An initialized instance.
///
- (instancetype)initWithSharedFolderId:(NSString *)sharedFolderId
                               actions:(nullable NSArray<DBSHARINGFolderAction *> *)actions;

///
/// Convenience constructor (exposes only non-nullable instance variables with
/// no default value).
///
/// @param sharedFolderId The ID for the shared folder.
///
/// @return An initialized instance.
///
- (instancetype)initWithSharedFolderId:(NSString *)sharedFolderId;

- (instancetype)init NS_UNAVAILABLE;

@end

#pragma mark - Serializer Object

///
/// The serialization class for the `GetMetadataArgs` struct.
///
@interface DBSHARINGGetMetadataArgsSerializer : NSObject

///
/// Serializes `DBSHARINGGetMetadataArgs` instances.
///
/// @param instance An instance of the `DBSHARINGGetMetadataArgs` API object.
///
/// @return A json-compatible dictionary representation of the
/// `DBSHARINGGetMetadataArgs` API object.
///
+ (NSDictionary *)serialize:(DBSHARINGGetMetadataArgs *)instance;

///
/// Deserializes `DBSHARINGGetMetadataArgs` instances.
///
/// @param dict A json-compatible dictionary representation of the
/// `DBSHARINGGetMetadataArgs` API object.
///
/// @return An instantiation of the `DBSHARINGGetMetadataArgs` object.
///
+ (DBSHARINGGetMetadataArgs *)deserialize:(NSDictionary *)dict;

@end

NS_ASSUME_NONNULL_END
