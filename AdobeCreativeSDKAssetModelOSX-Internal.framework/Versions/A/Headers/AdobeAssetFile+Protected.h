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

#ifndef AdobeAssetFileProtectedHeader
#define AdobeAssetFileProtectedHeader

#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeStorageResourceCollection.h>
#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeStorageResourceItem.h>

extern NSString *const AdobeAssetFileCoderKeyType;
extern NSString *const AdobeAssetFileCoderKeyFileSize;
extern NSString *const AdobeAssetFileCoderKeyMD5Hash;
extern NSString *const AdobeAssetFileCoderKeyOptionalMeta;

@interface AdobeAssetFile (Protected)

@property (readwrite, nonatomic, strong) NSString *hlsHref;

- (id)initWithResourceItem:(AdobeStorageResourceItem *)item withParentResourceCollection:(AdobeStorageResourceCollection *)parent __deprecated_msg("initWithResourceItem:resourceCollection");

- (instancetype)initWithResourceItem:(AdobeStorageResourceItem *)item
resourceCollection:(AdobeStorageResourceCollection *)collection;

- (AdobeStorageResourceItem *)resourceItem __deprecated_msg("Access to the lower level resource item is going away. It is causing synchronization issues for this class.");

- (BOOL)isCached:(AdobeAssetFileRenditionType)type withSize:(CGSize)dimensions forPage:(NSUInteger)page __deprecated_msg("isCached:dimensions:page");

- (BOOL)isCached:(AdobeAssetFileRenditionType)type
dimensions:(CGSize)dimensions
page:(NSUInteger)page;

- (BOOL)isVideo;

- (UIImage *)getRenditionFromCacheWithType:(AdobeAssetFileRenditionType)type withSize:(CGSize)dimensions __deprecated_msg("renditionFromCacheWithType:dimensions");

- (UIImage *)renditionFromCacheWithType:(AdobeAssetFileRenditionType)type
dimensions:(CGSize)dimensions;

- (UIImage *)getRenditionFromCacheWithType:(AdobeAssetFileRenditionType)type withSize:(CGSize)dimensions forPage:(NSUInteger)page __deprecated_msg("renditionFromCacheWithType:dimensions:page");

- (UIImage *)renditionFromCacheWithType:(AdobeAssetFileRenditionType)type
dimensions:(CGSize)dimensions
page:(NSUInteger)page;

+ (AdobeAssetFile *)create:(NSString *)name
inFolder:(AdobeAssetFolder *)parentFolder
inCloud:(AdobeCloud *)cloud
withDataPath:(NSURL *)dataPath
withType:(NSString *)type
onProgress:(void (^)(double fractionCompleted))progressBlock
onCompletion:(void (^)(AdobeAssetFile *file))completionBlock
onCancellation:(void (^)(void))cancellationBlock
onError:(void (^)(NSError *error))errorBlock __deprecated_msg("Use create:folder:cloud:dataPath:contentType:policy:progressBlock:successBlock:cancellationBlock:errorBlock");

+ (AdobeAssetFile *)create:(NSString *)name
inFolder:(AdobeAssetFolder *)parentFolder
inCloud:(AdobeCloud *)cloud
withDataPath:(NSURL *)dataPath
withType:(NSString *)type
withCollisionPolicy:(AdobeAssetFileCollisionPolicy)policy
onProgress:(void (^)(double fractionCompleted))progressBlock
onCompletion:(void (^)(AdobeAssetFile *file))completionBlock
onCancellation:(void (^)(void))cancellationBlock
onError:(void (^)(NSError *error))errorBlock __deprecated_msg("Use create:folder:cloud:dataPath:contentType:policy:progressBlock:successBlock:cancellationBlock:errorBlock");

+ (AdobeAssetFile *)create:(NSString *)name
folder:(AdobeAssetFolder *)folder
cloud:(AdobeCloud *)cloud
dataPath:(NSURL *)dataPath
contentType:(NSString *)contentType
collisionPolicy:(AdobeAssetFileCollisionPolicy)policy
progressBlock:(void (^)(double fractionCompleted))progressBlock
successBlock:(void (^)(AdobeAssetFile *file))successBlock
cancellationBlock:(void (^)(void))cancellationBlock
errorBlock:(void (^)(NSError *error))errorBlock;

@end

#endif /* ifndef AdobeAssetFileProtectedHeader */
