/******************************************************************************
*
* ADOBE CONFIDENTIAL
* ___________________
*
* Copyright 2013 Adobe Systems Incorporated
* All Rights Reserved.
*
* NOTICE:  All information contained herein is, and remains the property of
* Adobe Systems Incorporated and its suppliers, if any. The intellectual and
* technical concepts contained herein are proprietary to Adobe Systems
* Incorporated and its suppliers and are protected by trade secret or
* copyright law. Dissemination of this information or reproduction of this
* material is strictly forbidden unless prior written permission is obtained
* from Adobe Systems Incorporated.
******************************************************************************/

#ifndef AdobeCommonCacheHeader
#define AdobeCommonCacheHeader

#import <Foundation/Foundation.h>

#ifndef DMALIB
#import <UIKit/UIKit.h>
#endif

NS_ASSUME_NONNULL_BEGIN

//
// Cache Constants
//

/** Highest cache level at which to keep an object */
typedef NS_OPTIONS (NSUInteger, AdobeCommonCacheOptions)
{
/** Do not cache the object. */
AdobeCommonCacheUnset               = 0,
/** Keep object in memory cache. */
AdobeCommonCacheKeepInMemoryCache   = (1 << 0),
/** Keep object in disk cache. */
AdobeCommonCacheKeepOnDiskCache     = (1 << 1)
};

/** Report cache hit level */
typedef NS_ENUM (NSInteger, AdobeCommonCacheHitLocation)
{
/** did not hit. */
AdobeCommonCacheHitLocationNone,
/** Hit on memory cache. */
AdobeCommonCacheHitLocationMemory,
/** Hit on disk cache. */
AdobeCommonCacheHitLocationDisk
};

/** Convenience size-related constants for cache configuration, in bytes. */
typedef NS_ENUM (NSUInteger, AdobeCommonCacheSizeConstant)
{
/** One KByte */
AdobeCommonCacheSizeKBytes      = 1024,
/** One MByte */
AdobeCommonCacheSizeMBytes      = (AdobeCommonCacheSizeKBytes * 1024),
/** One GByte */
AdobeCommonCacheSizeGBytes      = (AdobeCommonCacheSizeMBytes * 1024)
};

/** Convenience time-related constants for time-based eviction policies, in seconds. */
typedef NS_ENUM (NSUInteger, AdobeCommonCacheTimeConstant)
{
/** One second. */
AdobeCommonCacheTimeSec         = 1,
/** One minute. */
AdobeCommonCacheTimeMin         = (AdobeCommonCacheTimeSec * 60),
/** One hour. */
AdobeCommonCacheTimeHr          = (AdobeCommonCacheTimeMin * 60),
/** One day. */
AdobeCommonCacheTimeDay         = (AdobeCommonCacheTimeHr * 24),
/** One week. */
AdobeCommonCacheTimeWeek        = (AdobeCommonCacheTimeDay * 7),
/** One year. */
AdobeCommonCacheTimeYear        = (AdobeCommonCacheTimeWeek * 52)
};

/** Cache operation policies:
*  - Disk cache eviction policies
*  - On/off-line configuration
*/
typedef NS_OPTIONS (NSUInteger, AdobeCommonCachePolicies)
{
/** Cache policies not set */
AdobeCommonCachePolicyUnset     = 0,

/** Least Recently Used policy: evict objects with oldest access time */
AdobeCommonCacheEvictionLRU     = (1 << 0),
/** First In First Out policy: evict objects with oldest creation time */
AdobeCommonCacheEvictionFIFO    = (1 << 1),
/** Large Size First: evict largest objects */
AdobeCommonCacheEvictionLSF     = (1 << 2),

/** Allow configuration of offline caches.  If this flag is set to 1 a cache can be created
*  even if user is not logged in to the Creative Cloud.  Otherwise the use must be logged in
*  to create a cache */
AdobeCommonCacheAllowOfflineUse = (1 << 3)
};

/** Cache configuration constants */
typedef NS_ENUM (NSUInteger, AdobeCommonCacheSetting)
{
/** Default memory cache "cost" specified as a byte capacity.  This allow using an object's size as
* the cost when inserting it in the cache. */
AdobeCommonCacheInitMemCache        = (16 * AdobeCommonCacheSizeMBytes),
/** Max memory cache "cost". */
AdobeCommonCacheMaxMemCache         = (128 * AdobeCommonCacheSizeMBytes),
/** Default disk cache size.  Approximate size the file-based cache occupies on storage.  The size
* is used to compute thresholds at which the eviction policies take effect.  */
AdobeCommonCacheInitDiskCache       = (128 * AdobeCommonCacheSizeMBytes),
/** Max disk cache size. */
AdobeCommonCacheMaxDiskCache        = (1 * AdobeCommonCacheSizeGBytes),
/** Default value for time based eviction ("evict all objects older than...").  Currently unused. */
AdobeCommonCacheInitTimeLimit       = (1 * AdobeCommonCacheTimeDay),
/** Default value for size based eviction ("evict all objects larger than...").  Currently unused. */
AdobeCommonCacheInitEntrySizeLimit  = (1 * AdobeCommonCacheSizeMBytes)
};


//
// Miss/Hit Handlers
//

typedef void (^AdobeCommonCacheObjectCompletionHandler)    (id _Nonnull object);

#ifndef DMALIB
typedef void (^AdobeCommonCacheImageCompletionHandler)     (UIImage *_Nonnull image);
#endif

typedef void (^AdobeCommonCacheDictionaryCompletionHandler)(NSDictionary *_Nonnull dictionary);
typedef void (^AdobeCommonCacheArrayCompletionHandler)     (NSArray *_Nonnull array);
typedef void (^AdobeCommonCacheDataCompletionHandler)      (NSData *_Nonnull data);

// begin deprecated
typedef void (^ AdobeCommonCacheMissHandler)() __deprecated_msg ("use completion handlers");
typedef void (^ AdobeCommonCacheObjectHitHandler)(id _Nonnull object, AdobeCommonCacheHitLocation location) __deprecated_msg ("AdobeCommonCacheImageCompletionHandler");

#ifndef DMALIB
typedef void (^ AdobeCommonCacheImageHitHandler)(UIImage * _Nonnull image, AdobeCommonCacheHitLocation location) __deprecated_msg ("AdobeCommonCacheImageCompletionHandler");
#endif

typedef void (^ AdobeCommonCacheDictionaryHitHandler)(NSDictionary * _Nonnull dictionary, AdobeCommonCacheHitLocation location) __deprecated_msg ("AdobeCommonCacheDictionaryCompletionHandler");
typedef void (^ AdobeCommonCacheArrayHitHandler)(NSArray * _Nonnull array, AdobeCommonCacheHitLocation location) __deprecated_msg ("AdobeCommonCacheArrayCompletionHandler");
typedef void (^ AdobeCommonCacheDataHitHandler)(NSData * _Nonnull data, AdobeCommonCacheHitLocation location) __deprecated_msg ("AdobeCommonCacheDataCompletionHandler");
// end deprecated

extern NSString *_Nonnull const AdobeCommonCacheAnonymousUserID;

//
// Notifications
//

/** Evicted an object from memory cache */
extern NSString *_Nonnull AdobeCommonCacheMemCacheEvictionNotification;

/** Evicted an object from disk cache */
extern NSString *_Nonnull AdobeCommonCacheDiskCacheEvictionNotification;

/** Cleared memory cache */
extern NSString *_Nonnull AdobeCommonCacheClearMemCacheNotification;

/** Deleted the disk cache directory */
extern NSString *_Nonnull AdobeCommonCacheClearDiskCacheNotification;


//
// Names of caches shared among several modules
//

extern NSString *_Nonnull const AdobeStorageSessionCacheID;
extern NSString *_Nonnull const Adobe360WorkflowSessionCacheName;
extern NSString *_Nonnull const Adobe360WorkflowAppIconCacheName;

/**
* AdobeCommonCache is the class that allows creating and managing caches on the Adobe Creative SDK.
* An application is able to create one or more caches, each identified by a unique 'name'.  Internally
* caches are identified by the AdobeID to isolate different users' caches.
*
* The cache is implemented in two levels: the first level memory cache, implemented using NSCache, and
* a second level disk cache.  The cache size and eviction policy are configurable.  The class
* provides methods to add, remove, query, and get items from the cache.
*/
@interface AdobeCommonCache : NSObject

///
/// @name Overall Operations
///
/// Methods affecting overall cache behavior.
///

/**
* The cache is accessed through a singleton.  Several caches can be created in parallel,
* each identified by a "cacheName" and an "adobeID".
*/
+ (AdobeCommonCache *_Nonnull)sharedCache;

/**
* Configure or reconfigure the cache.
* If a cache exists with the given cacheName for a given adobeID, change the cache configuration,
* otherwise create a new one.
*
* @param cacheName     Cache identifier in reverse DNS notation.
* @param memCacheSize  Memory cache size (see AdobeCommonSetting values).
* @param diskCacheSize Disk cache size (see AdobeCommonSetting values).
* @param policy        Cache operation policy (see AdobeCommonCachePolicies values).
* @param errorPtr      Error status.  Returns an AdobeCommonCacheErrorCode if an error is found.
*/
- (BOOL)configureCache:(nonnull NSString *)cacheName
memCacheSize:(NSInteger)memCacheSize
diskCacheSize:(NSInteger)diskCacheSize
policies:(AdobeCommonCachePolicies)policy
error:(NSError **)errorPtr;

- (BOOL)configureCache:(nonnull NSString *)cacheName
memCacheSize:(NSInteger)memCacheSize
diskCacheSize:(NSInteger)diskCacheSize
withPolicies:(AdobeCommonCachePolicies)policy
withError:(NSError **)errorPtr __deprecated_msg("use configureCache:memCacheSize:diskCacheSize:policies:error");

/**
* Query if cache exists.
*
* @param cacheName     Cache identifier in reverse DNS notation.
*
* @return              Whether cache has been created by a previous call to configureCache:.
*/
- (BOOL)doesCacheExist:(nonnull NSString *)cacheName;

/**
* Clear both memory and disk caches, but keep the cache instance.
*
* @param cacheName     Cache identifier.
* @param errorPtr      Error status.  Returns an AdobeCommonCacheErrorCode if an error is found.
*/
- (BOOL)clearCache:(nonnull NSString *)cacheName
error:(NSError **)errorPtr;

- (BOOL)clearCache:(NSString *)cacheName
withError:(NSError **)errorPtr __deprecated_msg("use clearCache:error");


/**
* Clear both the memory and disk caches that contain Creative Cloud user data.  Do not clear the internal
* caches that the Foundation SDK maintains for its own use.  The method keeps the cache instances.
*/
- (void)clearAllUserDataCaches;

/**
* Clear both memory and disk caches for all namespaces, but keep the cache instances.  This method also
* clears the internal caches for Foundation SDK's own use.  SDK clients are discouraged from using this
* method.
*/
- (void)clearAllCaches;

/**
* Clear both memory and disk caches.  Also remove the cache instance.  This method must
* be called when there is no further use of the cache, e.g., when logging out.
*
* @param cacheName     Cache identifier.
* @param errorPtr      Error status.  Returns an AdobeCommonCacheErrorCode if an error is found.
*/
- (BOOL)removeCache:(nonnull NSString *)cacheName
error:(NSError **)errorPtr;

- (BOOL)removeCache:(NSString *)cacheName
withError:(NSError **)errorPtr __deprecated_msg("use removeCache:error");


/**
* Control changing the cache state.  If freeze is true, add and remove operations are
* disabled.  Query and data fetch operations are still enabled.
*
* @param freeze        Control the cache state.
* @param cacheName     Cache identifier.
* @param errorPtr      Error status.  Returns an AdobeCommonCacheErrorCode if an error is found.
*/
- (BOOL)freezeCache:(BOOL)freeze
cache:(nonnull NSString *)cacheName
error:(NSError **)errorPtr;

- (BOOL)freezeCache:(NSString *)cacheName
freeze:(BOOL)freeze
withError:(NSError **)errorPtr __deprecated_msg("use freezeCache:enable:error");

/**
* Freeze all caches.  The state of all caches is kept unchanged.
*/
- (void)freezeAllCaches:(BOOL)freeze;

/**
* Control cache operation.  If enable is false, the cache is frozen and its contents cleared.
* By default the cache is enabled.
*
* @param enable        Control cache operation.
* @param cacheName     Cache identifier.
* @param errorPtr      Error status.  Returns an AdobeCommonCacheErrorCode if an error is found.
*/
- (BOOL)setEnable:(BOOL)enable
cache:(nonnull NSString *)cacheName
error:(NSError **)errorPtr;

- (BOOL)enableCache:(NSString *)cacheName
enable:(BOOL)enable
withError:(NSError **)errorPtr __deprecated_msg("use setEnable:cache:error:");

///
/// @name Individual Entry Operations
///
/// Each entry must be uniquely identified by the combination of an ID and a tag (the 'guid' and
/// 'key' arguments in each method below).  This allows caching different formats of a particular
/// asset, e.g., an asset's thumbnail, rendition, and actual image can be individually cached.
/// For multi-page assets where each page can be individually accessed, the page number must be
/// part of the 'key' argument.
///

#ifndef DMALIB


/**
* Add an image to the cache.
*
* For the @c AdobeCommonCacheKeepOnDiskCache option, the saved image data will be converted to a
* JPEG image type. The JPEG image quality is set to %100 so compression loss should be at a
* minimum. To preserve the transparency of @c image use
* @c addImage:preserveTransparency:withGUID:withKey:withOptions:toCache:withError:
*
* @param image         UIImage object to be added.
* @param guid          Unique ID.
* @param key           Asset tag.
* @param cacheName     Cache identifier.
* @param options       Hints for cache insertion (see AdobeCommonCacheOptions).
* @param errorPtr      Error status.  Returns an AdobeCommonCacheErrorCode if an error is found.
*
* @see addImage:preserveTransparency:withGUID:withKey:withOptions:toCache:withError:
*/
- (BOOL)addImage:(UIImage *)image
withGUID:(NSString *)guid
andKey:(NSString *)key
cache:(NSString *)cacheName
options:(AdobeCommonCacheOptions)options
error:(NSError **)errorPtr;

- (BOOL)addImage:(UIImage *)image
withGUID:(NSString *)guid
withKey:(NSString *)key
withOptions:(AdobeCommonCacheOptions)options
toCache:(NSString *)cacheName
withError:(NSError **)errorPtr __deprecated_msg("use addImageForGUID:andKey:options:cache:error");

/**
* Add an image to the cache.
*
* If the @c AdobeCommonCacheKeepOnDiskCache option is specified, depending on the value for
* @c preserveTransparency the image data will be converted to JPEG (preserveTransparency == NO) or
* PNG (preserveTransparency == YES) data. In the JPEG case, the quality is to %100 so compression
* loss should be at a minimum.
*
* @param image                UIImage object to be added.
* @param guid                 A unique ID to be used for identifying the cached image.
* @param key                  The cache key.
*                             argument is @c YES and the @c AdobeCommonCacheKeepOnDiskCache option
*                             is specified, the image data is converted to a PNG container. If
*                             this argument is @c NO, the image data is converted to JPEG
*                             container.
* @param cacheName            Cache identifier.
* @param options              Cache options (see @c AdobeCommonCacheOptions).
* @param preserveTransparency Whether to preserve the alpha layer of the image data. If this
* @param errorPtr             Error status. Returns an AdobeCommonCacheErrorCode if an error
*                             occurs while attempting to add the specified image to the cache.
*
* @return @c YES if @c image was successfully added the specified cache; @c NO otherwise. Inspect
*         @c errorPtr for more information about the error.
*/
- (BOOL)        addImage:(nonnull UIImage *)image
withGUID:(nonnull NSString *)guid
andKey:(nonnull NSString *)key
cache:(nonnull NSString *)cacheName
options:(AdobeCommonCacheOptions)options
preserveTransparency:(BOOL)preserveTransparency
error:(NSError *__autoreleasing *)errorPtr;


- (BOOL)        addImage:(UIImage *)image
preserveTransparency:(BOOL)preserveTransparency
withGUID:(NSString *)guid
withKey:(NSString *)key
withOptions:(AdobeCommonCacheOptions)options
toCache:(NSString *)cacheName
withError:(NSError *__autoreleasing *)errorPtr __deprecated_msg("addImage:withGUID:andKey:preserveTransparency:options:cache:error:");


#endif // !DMALIB

/**
* Add a dictionary to the cache.
*
* @param dictionary    NSDictionary object to be added.
* @param guid          Unique ID.
* @param key           Asset tag.
* @param cacheName     Cache identifier.
* @param options       Hints for cache insertion (see AdobeCommonCacheOptions).
* @param errorPtr      Error status.  Returns an AdobeCommonCacheErrorCode if an error is found.
*/
- (BOOL)addDictionary:(nonnull NSDictionary *)dictionary
withGUID:(nonnull NSString *)guid
andKey:(nonnull NSString *)key
cache:(nonnull NSString *)cacheName
options:(AdobeCommonCacheOptions)options
error:(NSError **)errorPtr;

- (BOOL)addDictionary:(NSDictionary *)dictionary
withGUID:(NSString *)guid
withKey:(NSString *)key
withOptions:(AdobeCommonCacheOptions)options
toCache:(NSString *)cacheName
withError:(NSError **)errorPtr __deprecated_msg("addDictionary:GUID:key:options:cache:error");


/**
* Add an array to the cache.
*
* @param array         NSArray object to be added.
* @param guid          Unique ID.
* @param key           Asset tag.
* @param cacheName     Cache identifier.
* @param options       Hints for cache insertion (see AdobeCommonCacheOptions).
* @param errorPtr      Error status.  Returns an AdobeCommonCacheErrorCode if an error is found.
*/
- (BOOL)addArray:(nonnull NSArray *)array
withGUID:(nonnull NSString *)guid
andKey:(nonnull NSString *)key
cache:(NSString *)cacheName
options:(AdobeCommonCacheOptions)options
error:(NSError **)errorPtr;

- (BOOL)addArray:(NSArray *)array
withGUID:(NSString *)guid
withKey:(NSString *)key
withOptions:(AdobeCommonCacheOptions)options
toCache:(NSString *)cacheName
withError:(NSError **)errorPtr __deprecated_msg("addArray:withGUID:andKey:opitons:cache:error");

/**
* Add data to the cache.
*
* @param data          NSData object to be added.
* @param guid          Unique ID.
* @param key           Asset tag.
* @param cacheName     Cache identifier.
* @param options       Hints for cache insertion (see AdobeCommonCacheOptions).
* @param errorPtr      Error status.  Returns an AdobeCommonCacheErrorCode if an error is found.
*/
- (BOOL)addData:(nonnull NSData *)data
withGUID:(nonnull NSString *)guid
andKey:(nonnull NSString *)key
cache:(nonnull NSString *)cacheName
options:(AdobeCommonCacheOptions)options
error:(NSError **)errorPtr;

- (BOOL)addData:(NSData *)data
withGUID:(NSString *)guid
withKey:(NSString *)key
withOptions:(AdobeCommonCacheOptions)options
toCache:(NSString *)cacheName
withError:(NSError **)errorPtr __deprecated_msg("addData:withGUID:andKey:options:cache:error:");


/**
* Add a ganeric object to the cache.
* The object must be serializable.  Generic objects are inserted and returned from the cache
* using the NSKeyedArchiver and NSKeyedUnarchiver classes.
*
* @param object        Generic object to be added.
* @param guid          Unique ID.
* @param key           Asset tag.
* @param cacheName     Cache identifier.
* @param options       Hints for cache insertion (see AdobeCommonCacheOptions).
* @param errorPtr      Error status.  Returns an AdobeCommonCacheErrorCode if an error is found.
*/
- (BOOL)addObject:(nonnull id)object
withGUID:(nonnull NSString *)guid
andKey:(nonnull NSString *)key
cache:(nonnull NSString *)cacheName
options:(AdobeCommonCacheOptions)options
error:(NSError **)errorPtr;

- (BOOL)addObject:(id)object
withGUID:(NSString *)guid
withKey:(NSString *)key
withOptions:(AdobeCommonCacheOptions)options
toCache:(NSString *)cacheName
withError:(NSError **)errorPtr __deprecated_msg("addObject:withGUID:andKey:options:cache:error:");


/**
* Check if an object exists in the cache.
*
* @param guid          Unique ID.
* @param key           Asset tag.
* @param cacheName     Cache identifier.
* @param errorPtr      Error status.  Returns an AdobeCommonCacheErrorCode if an error is found.
*
* @return              Whether the object is in the cache.
*/
- (BOOL)containsItemForGUID:(nonnull NSString *)guid
andKey:(nonnull NSString *)key
cache:(nonnull NSString *)cacheName
error:(NSError **)errorPtr;

- (BOOL)containsItemForGUID:(NSString *)guid
withKey:(NSString *)key
inCache:(NSString *)cacheName
withError:(NSError **)errorPtr __deprecated_msg("containsItemForGUID:andKey:cache:error:");


/**
* Remove object from the cache.
*
* @param guid          Unique ID.
* @param key           Asset tag.
* @param cacheName     Cache identifier.
* @param errorPtr      Error status.  Returns an AdobeCommonCacheErrorCode if an error is found.
*/
- (BOOL)removeItemForGUID:(nonnull NSString *)guid
andKey:(nonnull NSString *)key
cache:(nonnull NSString *)cacheName
error:(NSError **)errorPtr;

- (BOOL)removeItemForGUID:(NSString *)guid
withKey:(NSString *)key
fromCache:(NSString *)cacheName
withError:(NSError **)errorPtr __deprecated_msg("removeItemForGUID:andKey:cache:error:");

/**
* Remove a set of objects that have the same guid from the cache.
*
* @param guid          Unique ID for a group of objects.
* @param cacheName     Cache identifier.
* @param errorPtr      Error status.  Returns an AdobeCommonCacheErrorCode if an error is found.
*/
- (BOOL)removeSetForGUID:(nonnull NSString *)guid
cache:(nonnull NSString *)cacheName
error:(NSError **)errorPtr;

- (BOOL)removeSetForGUID:(NSString *)guid
fromCache:(NSString *)cacheName
withError:(NSError **)errorPtr __deprecated_msg("removeSetForGUID:cache:error:");


#ifndef DMALIB

/**
* Get an image from the cache synchronously.
*
* @param guid          Unique ID.
* @param key           Asset tag.
* @param cacheName     Cache identifier.
* @param options       Hints for cache insertion (see AdobeCommonCacheOptions).
* @return UIImage		A UIImage instance if the image was cached; nil otherwise.
*/
- (nullable UIImage *)imageForGUID:(nonnull NSString *)guid
andKey:(nonnull NSString *)key
cache:(nonnull NSString *)cacheName
options:(AdobeCommonCacheOptions)options;

- (nullable UIImage *)getImageFromGUID:(NSString *)guid
withKey:(NSString *)key
withOptions:(AdobeCommonCacheOptions)options
fromCache:(NSString *)cacheName __deprecated_msg("imageForGUID:andKey:options:cache:");

/**
* Get an image from the cache.
*
* @param guid              Unique ID.
* @param key               Asset tag.
* @param options           Hints for cache insertion (see AdobeCommonCacheOptions).
* @param cacheName         Cache identifier.
* @param errorPtr          Error status.  Returns an AdobeCommonCacheErrorCode if an error is found.
* @param completionQueue   Completion handler execution queue.  If nil, execute hit on the main thread, if miss calls back on current thread
* @param completionBlock   Block to invoke when completed.
*/
- (BOOL)imageForGUID:(nonnull NSString *)guid
andKey:(nonnull NSString *)key
cache:(nonnull NSString *)cacheName
options:(AdobeCommonCacheOptions)options
error:(NSError *_Nullable *)errorPtr
completionQueue:(nullable NSOperationQueue *)completion
completionBlock:(nullable AdobeCommonCacheImageCompletionHandler)completion;

- (BOOL)getImageFromGUID:(NSString *)guid
withKey:(NSString *)key
withOptions:(AdobeCommonCacheOptions)options
fromCache:(NSString *)cacheName
onHit:(AdobeCommonCacheImageHitHandler)hitHandler
hitQueue:(NSOperationQueue *)hitQueue
onMiss:(AdobeCommonCacheMissHandler)missHandler
missQueue:(NSOperationQueue *)missQueue
withError:(NSError **)errorPtr __deprecated_msg("imageForGUID:andKey:options:cache:error:completionQueue:completionBlock:");


#endif // !DMALIB


/**
* Get a dictionary from the cache.
*
* @param guid          Unique ID.
* @param key           Asset tag.
* @param cacheName     Cache identifier.
* @param options       Hints for cache insertion (see AdobeCommonCacheOptions).
* @param errorPtr      Error status.  Returns an AdobeCommonCacheErrorCode if an error is found.
* @return NSDictionary dictionary requested.
*/
- (nullable NSDictionary *)dictionaryForGUID:(nonnull NSString *)guid
andKey:(nonnull NSString *)key
cache:(nonnull NSString *)cacheName
options:(AdobeCommonCacheOptions)options;

/**
* Get a dictionary from the cache.
*
* @param guid          Unique ID.
* @param key           Asset tag.
* @param cacheName     Cache identifier.
* @param options       Hints for cache insertion (see AdobeCommonCacheOptions).
* @param errorPtr          Error status.  Returns an AdobeCommonCacheErrorCode if an error is found.
* @param completionQueue   Completion handler execution queue.  If nil, execute hit on the main thread, if miss calls back on current thread
* @param completionBlock   Block to invoke when completed.
*/
- (BOOL)dictionaryForGUID:(nonnull NSString *)guid
andKey:(nonnull NSString *)key
cache:(nonnull NSString *)cacheName
options:(AdobeCommonCacheOptions)options
error:(NSError **)errorPtr
completionQueue:(nullable NSOperationQueue *)completion
completionBlock:(nullable AdobeCommonCacheDictionaryCompletionHandler)completion;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

- (BOOL)getDictionaryFromGUID:(NSString *)guid
withKey:(NSString *)key
withOptions:(AdobeCommonCacheOptions)options
fromCache:(NSString *)cacheName
onHit:(AdobeCommonCacheDictionaryHitHandler)hitHandler
hitQueue:(NSOperationQueue *)hitQueue
onMiss:(AdobeCommonCacheMissHandler)missHandler
missQueue:(NSOperationQueue *)missQueue
withError:(NSError **)errorPtr __deprecated_msg("dictionaryForGUID:andKey:options:cache::error:completionQueue:completionBlock:");

#pragma clang diagnostic pop

/**
* Get an array from the cache.
*
* @param guid          Unique ID.
* @param key           Asset tag.
* @param cacheName     Cache identifier.
* @param options       Hints for cache insertion (see AdobeCommonCacheOptions).
* @param errorPtr      Error status.  Returns an AdobeCommonCacheErrorCode if an error is found.
*/
- (nullable NSArray *)arrayForGUID:(nonnull NSString *)guid
andKey:(nonnull NSString *)key
cache:(nonnull NSString *)cacheName
options:(AdobeCommonCacheOptions)options;

/**
* Get an array from the cache.
*
* @param guid              Unique ID.
* @param key               Asset tag.
* @param cacheName         Cache identifier.
* @param options           Hints for cache insertion (see AdobeCommonCacheOptions).
* @param errorPtr          Error status.  Returns an AdobeCommonCacheErrorCode if an error is found.
* @param completionQueue   Completion handler execution queue.  If nil, execute hit on the main thread, if miss calls back on current thread
* @param completionBlock   Block to invoke when completed.
*/
- (BOOL)arrayForGUID:(nonnull NSString *)guid
andKey:(nonnull NSString *)key
cache:(nonnull NSString *)cacheName
options:(AdobeCommonCacheOptions)options
error:(NSError *_Nullable *)errorPtr
completionQueue:(nullable NSOperationQueue *)completion
completionBlock:(nullable AdobeCommonCacheArrayCompletionHandler)completion;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

- (BOOL)getArrayFromGUID:(NSString *)guid
withKey:(NSString *)key
withOptions:(AdobeCommonCacheOptions)options
fromCache:(NSString *)cacheName
onHit:(AdobeCommonCacheArrayHitHandler)hitHandler
hitQueue:(NSOperationQueue *)hitQueue
onMiss:(AdobeCommonCacheMissHandler)missHandler
missQueue:(NSOperationQueue *)missQueue
withError:(NSError **)errorPtr __deprecated_msg("arrayForGUID:andKey:options:cache:error:completionQueue:completionBlock:");

#pragma clang diagnostic pop

/**
* Get data from the cache.
*
* @param guid          Unique ID.
* @param key           Asset tag.
* @param cacheName     Cache identifier.
* @param options       Hints for cache insertion (see AdobeCommonCacheOptions).
* @return NSData		An NSData instance if the data was cached; nil otherwise.
*/
- (nullable NSData *)dataForGUID:(nonnull NSString *)guid
andKey:(nonnull NSString *)key
cache:(nonnull NSString *)cacheName
options:(AdobeCommonCacheOptions)options;

- (nullable NSData *)getDataFromGUID:(NSString *)guid
withKey:(NSString *)key
withOptions:(AdobeCommonCacheOptions)options
fromCache:(NSString *)cacheName __deprecated_msg("dataForGUID:andKey:options:cache:");

/**
* Get data from the cache.
*
* @param guid              Unique ID.
* @param key               Asset tag.
* @param cacheName         Cache identifier.
* @param options           Hints for cache insertion (see AdobeCommonCacheOptions).
* @param errorPtr          Error status.  Returns an AdobeCommonCacheErrorCode if an error is found.
* @param completionQueue   Completion handler execution queue.  If nil, execute hit on the main thread, if miss calls back on current thread
* @param completionBlock   Block to invoke when completed.
*/
- (BOOL)dataForGUID:(nonnull NSString *)guid
andKey:(nonnull NSString *)key
cache:(nonnull NSString *)cacheName
options:(AdobeCommonCacheOptions)options
error:(NSError **)errorPtr
completionQueue:(nullable NSOperationQueue *)completion
completionBlock:(nullable AdobeCommonCacheDataCompletionHandler)completion;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

- (BOOL)getDataFromGUID:(NSString *)guid
withKey:(NSString *)key
withOptions:(AdobeCommonCacheOptions)options
fromCache:(NSString *)cacheName
onHit:(AdobeCommonCacheDataHitHandler)hitHandler
hitQueue:(NSOperationQueue *)hitQueue
onMiss:(AdobeCommonCacheMissHandler)missHandler
missQueue:(NSOperationQueue *)missQueue
withError:(NSError **)errorPtr __deprecated_msg("dataForGUID:andKey:options:cache:error:completionQueue:completionBlock:");

#pragma clang diagnostic pop

/**
* Get a generic object from the cache.
*
* @param guid          Unique ID.
* @param key           Asset tag.
* @param cacheName     Cache identifier.
* @param options       Hints for cache insertion (see AdobeCommonCacheOptions).
* @return id           object.
*/
- (nullable id)objectForGUID:(nonnull NSString *)guid
andKey:(nonnull NSString *)key
cache:(nonnull NSString *)cacheName
options:(AdobeCommonCacheOptions)options;

/**
* Get a generic object from the cache.
*
* @param guid              Unique ID.
* @param key               Asset tag.
* @param cacheName         Cache identifier.
* @param options           Hints for cache insertion (see AdobeCommonCacheOptions).
* @param errorPtr          Error status.  Returns an AdobeCommonCacheErrorCode if an error is found.
* @param completionQueue   Completion handler execution queue.  If nil, execute hit on the main thread, if miss call back immediately
* @param completionBlock   Block to invoke when completed.
*/
- (BOOL)objectForGUID:(nonnull NSString *)guid
andKey:(nonnull NSString *)key
cache:(nonnull NSString *)cacheName
options:(AdobeCommonCacheOptions)options
error:(NSError **)errorPtr
completionQueue:(nullable NSOperationQueue *)completion
completionBlock:(nullable AdobeCommonCacheObjectCompletionHandler)completion;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

- (BOOL)getObjectFromGUID:(NSString *)guid
withKey:(NSString *)key
withOptions:(AdobeCommonCacheOptions)options
fromCache:(NSString *)cacheName
onHit:(AdobeCommonCacheObjectHitHandler)hitHandler
hitQueue:(NSOperationQueue *)hitQueue
onMiss:(AdobeCommonCacheMissHandler)missHandler
missQueue:(NSOperationQueue *)missQueue
withError:(NSError **)errorPtr __deprecated_msg("objectForGUID:andKey:options:cache:error:completionQueue:completionBlock:");

#pragma clang diagnostic pop

/**
* Get the timestamp for the cached item.
*
* @param guid          Unique ID.
* @param key           Asset tag.
* @param cacheName     Cache identifier.
*
* @return NSDate       The date of the cached asset. nil will be returned if the asset was not found
*                      or some other error occurred.
*/
- (nullable NSDate *)timestampForGUID:(nonnull NSString *)guid
andKey:(nonnull NSString *)key
cache:(nonnull NSString *)cacheName;

- (nullable NSDate *)timestampForGUID:(NSString *)guid
key:(NSString *)key
cache:(NSString *)cacheName __deprecated_msg("timestampForGUID:andKey:cache:");


@end
NS_ASSUME_NONNULL_END

#endif /* ifndef AdobeCommonCacheHeader */
