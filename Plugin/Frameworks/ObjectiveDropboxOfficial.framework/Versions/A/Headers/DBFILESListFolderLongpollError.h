///
/// Copyright (c) 2016 Dropbox, Inc. All rights reserved.
///
/// Auto-generated by Stone, do not modify.
///

#import <Foundation/Foundation.h>

#import "DBSerializableProtocol.h"

@class DBFILESListFolderLongpollError;

NS_ASSUME_NONNULL_BEGIN

#pragma mark - API Object

///
/// The `ListFolderLongpollError` union.
///
/// This class implements the `DBSerializable` protocol (serialize and
/// deserialize instance methods), which is required for all Obj-C SDK API route
/// objects.
///
@interface DBFILESListFolderLongpollError : NSObject <DBSerializable, NSCopying>

#pragma mark - Instance fields

/// The `DBFILESListFolderLongpollErrorTag` enum type represents the possible
/// tag states with which the `DBFILESListFolderLongpollError` union can exist.
typedef NS_ENUM(NSInteger, DBFILESListFolderLongpollErrorTag) {
  /// Indicates that the cursor has been invalidated. Call `listFolder` to
  /// obtain a new cursor.
  DBFILESListFolderLongpollErrorReset,

  /// (no description).
  DBFILESListFolderLongpollErrorOther,

};

/// Represents the union's current tag state.
@property (nonatomic, readonly) DBFILESListFolderLongpollErrorTag tag;

#pragma mark - Constructors

///
/// Initializes union class with tag state of "reset".
///
/// Description of the "reset" tag state: Indicates that the cursor has been
/// invalidated. Call `listFolder` to obtain a new cursor.
///
/// @return An initialized instance.
///
- (instancetype)initWithReset;

///
/// Initializes union class with tag state of "other".
///
/// @return An initialized instance.
///
- (instancetype)initWithOther;

- (instancetype)init NS_UNAVAILABLE;

#pragma mark - Tag state methods

///
/// Retrieves whether the union's current tag state has value "reset".
///
/// @return Whether the union's current tag state has value "reset".
///
- (BOOL)isReset;

///
/// Retrieves whether the union's current tag state has value "other".
///
/// @return Whether the union's current tag state has value "other".
///
- (BOOL)isOther;

///
/// Retrieves string value of union's current tag state.
///
/// @return A human-readable string representing the union's current tag state.
///
- (NSString *)tagName;

@end

#pragma mark - Serializer Object

///
/// The serialization class for the `DBFILESListFolderLongpollError` union.
///
@interface DBFILESListFolderLongpollErrorSerializer : NSObject

///
/// Serializes `DBFILESListFolderLongpollError` instances.
///
/// @param instance An instance of the `DBFILESListFolderLongpollError` API
/// object.
///
/// @return A json-compatible dictionary representation of the
/// `DBFILESListFolderLongpollError` API object.
///
+ (NSDictionary *)serialize:(DBFILESListFolderLongpollError *)instance;

///
/// Deserializes `DBFILESListFolderLongpollError` instances.
///
/// @param dict A json-compatible dictionary representation of the
/// `DBFILESListFolderLongpollError` API object.
///
/// @return An instantiation of the `DBFILESListFolderLongpollError` object.
///
+ (DBFILESListFolderLongpollError *)deserialize:(NSDictionary *)dict;

@end

NS_ASSUME_NONNULL_END
