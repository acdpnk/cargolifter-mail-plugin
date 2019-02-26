///
/// Copyright (c) 2016 Dropbox, Inc. All rights reserved.
///
/// Auto-generated by Stone, do not modify.
///

#import <Foundation/Foundation.h>

#import "DBSerializableProtocol.h"

@class DBSHARINGJobError;
@class DBSHARINGJobStatus;

NS_ASSUME_NONNULL_BEGIN

#pragma mark - API Object

///
/// The `JobStatus` union.
///
/// This class implements the `DBSerializable` protocol (serialize and
/// deserialize instance methods), which is required for all Obj-C SDK API route
/// objects.
///
@interface DBSHARINGJobStatus : NSObject <DBSerializable, NSCopying>

#pragma mark - Instance fields

/// The `DBSHARINGJobStatusTag` enum type represents the possible tag states
/// with which the `DBSHARINGJobStatus` union can exist.
typedef NS_ENUM(NSInteger, DBSHARINGJobStatusTag) {
  /// The asynchronous job is still in progress.
  DBSHARINGJobStatusInProgress,

  /// The asynchronous job has finished.
  DBSHARINGJobStatusComplete,

  /// The asynchronous job returned an error.
  DBSHARINGJobStatusFailed,

};

/// Represents the union's current tag state.
@property (nonatomic, readonly) DBSHARINGJobStatusTag tag;

/// The asynchronous job returned an error. @note Ensure the `isFailed` method
/// returns true before accessing, otherwise a runtime exception will be raised.
@property (nonatomic, readonly) DBSHARINGJobError *failed;

#pragma mark - Constructors

///
/// Initializes union class with tag state of "in_progress".
///
/// Description of the "in_progress" tag state: The asynchronous job is still in
/// progress.
///
/// @return An initialized instance.
///
- (instancetype)initWithInProgress;

///
/// Initializes union class with tag state of "complete".
///
/// Description of the "complete" tag state: The asynchronous job has finished.
///
/// @return An initialized instance.
///
- (instancetype)initWithComplete;

///
/// Initializes union class with tag state of "failed".
///
/// Description of the "failed" tag state: The asynchronous job returned an
/// error.
///
/// @param failed The asynchronous job returned an error.
///
/// @return An initialized instance.
///
- (instancetype)initWithFailed:(DBSHARINGJobError *)failed;

- (instancetype)init NS_UNAVAILABLE;

#pragma mark - Tag state methods

///
/// Retrieves whether the union's current tag state has value "in_progress".
///
/// @return Whether the union's current tag state has value "in_progress".
///
- (BOOL)isInProgress;

///
/// Retrieves whether the union's current tag state has value "complete".
///
/// @return Whether the union's current tag state has value "complete".
///
- (BOOL)isComplete;

///
/// Retrieves whether the union's current tag state has value "failed".
///
/// @note Call this method and ensure it returns true before accessing the
/// `failed` property, otherwise a runtime exception will be thrown.
///
/// @return Whether the union's current tag state has value "failed".
///
- (BOOL)isFailed;

///
/// Retrieves string value of union's current tag state.
///
/// @return A human-readable string representing the union's current tag state.
///
- (NSString *)tagName;

@end

#pragma mark - Serializer Object

///
/// The serialization class for the `DBSHARINGJobStatus` union.
///
@interface DBSHARINGJobStatusSerializer : NSObject

///
/// Serializes `DBSHARINGJobStatus` instances.
///
/// @param instance An instance of the `DBSHARINGJobStatus` API object.
///
/// @return A json-compatible dictionary representation of the
/// `DBSHARINGJobStatus` API object.
///
+ (NSDictionary *)serialize:(DBSHARINGJobStatus *)instance;

///
/// Deserializes `DBSHARINGJobStatus` instances.
///
/// @param dict A json-compatible dictionary representation of the
/// `DBSHARINGJobStatus` API object.
///
/// @return An instantiation of the `DBSHARINGJobStatus` object.
///
+ (DBSHARINGJobStatus *)deserialize:(NSDictionary *)dict;

@end

NS_ASSUME_NONNULL_END
