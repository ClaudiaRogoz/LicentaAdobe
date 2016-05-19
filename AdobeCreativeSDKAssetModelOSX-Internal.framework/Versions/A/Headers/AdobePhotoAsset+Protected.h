/******************************************************************************
*
* ADOBE CONFIDENTIAL
* ___________________
*
* Copyright 2014 Adobe Systems Incorporated
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

#ifndef AdobePhotoAssetProtectedHeader
#define AdobePhotoAssetProtectedHeader

@class AdobePhotoAssetRevision;

@interface AdobePhotoAsset (Protected)

/**
* This asset's revision.  Usually the current / latest revision.
*/
@property (nonatomic, readonly, strong) AdobePhotoAssetRevision *revision;


- (id)initWithName:(NSString *)name
catalog:(AdobePhotoCatalog *)catalog;

- (id)initWithName:(NSString *)name
guid:(NSString *)guid
catalog:(AdobePhotoCatalog *)catalog;

- (id)initWithGUID:(NSString *)guid
catalog:(AdobePhotoCatalog *)catalog;

/**
* Create (upload) a new asset and add into a collection on the Adobe Photo service asynchronously.
* For an image file: Preview, standard, and 2x thumbnail renditions are generated automatically.
*
* @param name              The name of the asset.
* @param guid              The guid of the asset.
* @param collection        The collection to add the asset into.
* @param path              The local path to the data. The path must be locally valid and cannot be nil.
* @param type              The content-type of the asset. The content-type is required and cannot be nil.
* @param progressBlock     Optionally track the upload progress.
* @param successBlock      Optionally get an updated reference to the created AdobePhotoAsset if successful.
* @param cancellationBlock Optionally be notified of a cancellation on upload.
* @param errorBlock        Optionally be notified of an error.
*/
+ (AdobePhotoAsset *)create:(NSString *)name
withGUID:(NSString *)guid
inCollection:(AdobePhotoCollection *)collection
withDataPath:(NSURL *)path
withContentType:(NSString *)type
onProgress:(void (^)(double fractionCompleted))progressBlock
onCompletion:(void (^)(AdobePhotoAsset *asset))successBlock
onCancellation:(void (^)(void))cancellationBlock
onError:(void (^)(NSError *error))errorBlock __deprecated_msg("Use create:guid:collection:dataPath:contentType:progressBlock:successBlock:cancellationBlock:errorBlock");

+ (AdobePhotoAsset *)create:(NSString *)name
guid:(NSString *)guid
collection:(AdobePhotoCollection *)collection
dataPath:(NSURL *)path
contentType:(NSString *)type
progressBlock:(void (^)(double fractionCompleted))progressBlock
successBlock:(void (^)(AdobePhotoAsset *asset))successBlock
cancellationBlock:(void (^)(void))cancellationBlock
errorBlock:(void (^)(NSError *error))errorBlock;

/**
* Create a child revision from a full payload table and update this asset asynchronously.
*
* @param newMetadata     The full new payload table for the child revision.
* @param priority        The priority of the HTTP request.
* @param successBlock    Optionally get an updated reference to the asset if successful.
* @param errorBlock      Optionally be notified of an error.
*/
- (void)createChildRevision:(NSDictionary *)newMetadata
withPriority:(NSOperationQueuePriority)priority
onCompletion:(void (^)(void))successBlock
onError:(void (^)(NSError *error))errorBlock __deprecated_msg("Use createChildRevision:requestPriority:successBlock:cancellationBlock:errorBlock");

- (void)createChildRevision:(NSDictionary *)newMetadata
requestPriority:(NSOperationQueuePriority)priority
successBlock:(void (^)(void))successBlock
errorBlock:(void (^)(NSError *error))errorBlock;

/**
* Create a child revision by updating a single payload entry (eg "develop") and update this asset asynchronously.
*
* @param newObject       The new object for the payload entry.
* @param key             The name of the payload entry to update (eg "develop").
* @param priority        The priority of the HTTP request.
* @param successBlock    Optionally get an updated reference to the asset if successful.
* @param errorBlock      Optionally be notified of an error.
*/
- (void)createChildRevisionWithObject:(NSObject *)newObject
forKey:(NSString *)key
withPriority:(NSOperationQueuePriority)priority
onCompletion:(void (^)(void))successBlock
onError:(void (^)(NSError *error))errorBlock __deprecated_msg("Use createChildRevisionWithObject:key:requestPriority:successBlock:exrrorBlock");

- (void)createChildRevisionWithObject:(NSObject *)newObject
key:(NSString *)key
requestPriority:(NSOperationQueuePriority)priority
successBlock:(void (^)(void))successBlock
errorBlock:(void (^)(NSError *error))errorBlock;
/**
* Update this asset's properties with information from data.  Asset properties will reflect those of the latest_revision in data.
*
* @param data     Data containing asset properties (retrieved from Oz).
* @param catalog  Catalog that contains this asset.
* @param errorPtr Optional container for error.
*/
- (BOOL)updateFromData:(NSData *)data
catalog:(AdobePhotoCatalog *)catalog
error:(NSError **)errorPtr;

/**
* Update this asset's properties with information from dictionary.  Asset properties will reflect those of the latest_revision in dictionary.
*
* @param dictionary  Dictionary containing asset properties (retrieved from Oz).
* @param catalog     Catalog that contains this asset.
* @param errorPtr    Optional container for error.
*/
- (BOOL)updateFromDictionary:(NSDictionary *)dictionary
catalog:(AdobePhotoCatalog *)catalog
error:(NSError **)errorPtr;

/**
* Update this asset's rendition links information from dictionary.  Asset rendition links will reflect those in the dictionary.
*
* @param dictionary  Dictionary containing rendition links (from response from Oz).
*/
- (void)updateRenditionLinksFromDictionary:(NSDictionary *)links;

@end

#endif /* ifndef AdobePhotoAssetProtectedHeader */
