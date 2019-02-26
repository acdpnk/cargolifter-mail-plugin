///
/// Copyright (c) 2016 Dropbox, Inc. All rights reserved.
///
/// Auto-generated by Stone, do not modify.
///

#import <Foundation/Foundation.h>

#import "DBSerializableProtocol.h"

@class DBFILESPathRootError;

NS_ASSUME_NONNULL_BEGIN

#pragma mark - API Object

///
/// The `PathRootError` struct.
///
/// This class implements the `DBSerializable` protocol (serialize and
/// deserialize instance methods), which is required for all Obj-C SDK API route
/// objects.
///
@interface DBFILESPathRootError : NSObject <DBSerializable, NSCopying>

#pragma mark - Instance fields

/// The user's latest path root value. None if the user no longer has a path
/// root.
@property (nonatomic, readonly, copy, nullable) NSString *pathRoot;

#pragma mark - Constructors

///
/// Full constructor for the struct (exposes all instance variables).
///
/// @param pathRoot The user's latest path root value. None if the user no
/// longer has a path root.
///
/// @return An initialized instance.
///
- (instancetype)initWithPathRoot:(nullable NSString *)pathRoot;

///
/// Convenience constructor (exposes only non-nullable instance variables with
/// no default value).
///
///
/// @return An initialized instance.
///
- (instancetype)initDefault;

- (instancetype)init NS_UNAVAILABLE;

@end

#pragma mark - Serializer Object

///
/// The serialization class for the `PathRootError` struct.
///
@interface DBFILESPathRootErrorSerializer : NSObject

///
/// Serializes `DBFILESPathRootError` instances.
///
/// @param instance An instance of the `DBFILESPathRootError` API object.
///
/// @return A json-compatible dictionary representation of the
/// `DBFILESPathRootError` API object.
///
+ (NSDictionary *)serialize:(DBFILESPathRootError *)instance;

///
/// Deserializes `DBFILESPathRootError` instances.
///
/// @param dict A json-compatible dictionary representation of the
/// `DBFILESPathRootError` API object.
///
/// @return An instantiation of the `DBFILESPathRootError` object.
///
+ (DBFILESPathRootError *)deserialize:(NSDictionary *)dict;

@end

NS_ASSUME_NONNULL_END