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

#ifndef AdobeAssetFolderProtectedHeader
#define AdobeAssetFolderProtectedHeader

#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeStorageResourceCollection.h>

@class AdobeAssetFolder;
@class AdobeCloud;

@interface AdobeAssetFolder (Protected)

+ (AdobeAssetFolder *)rootInCloud:(AdobeCloud *)cloud;

+ (AdobeAssetFolder *)rootInCloud:(AdobeCloud *)cloud
orderedByField:(AdobeAssetFolderOrderBy)field
orderDirection:(AdobeAssetFolderOrderDirection)direction __deprecated_msg("Use rootInCloud:config");

+ (AdobeAssetFolder *)rootInCloud:(AdobeCloud *)cloud
config:(AdobeAssetFolderConfiguration *)config;

- (id)initWithResourceCollection:(AdobeStorageResourceCollection *)collection
withParentResourceCollection:(AdobeStorageResourceCollection *)parent __deprecated_msg("Use initWithResourceCollection:parentResourceCollection");

- (instancetype)initWithResourceCollection:(AdobeStorageResourceCollection *)collection
parentResourceCollection:(AdobeStorageResourceCollection *)parent;

- (id)initWithResourceCollection:(AdobeStorageResourceCollection *)collection
orderBy:(AdobeStorageOrderByProperty)field
order:(AdobeStorageOrderRelation)direction
withParentHref:(NSString *)parentHref __deprecated_msg("Use iinitWithResourceCollection:config");

- (instancetype)initWithResourceCollection:(AdobeStorageResourceCollection *)collection
orderByField:(AdobeStorageOrderByProperty)field
orderRelation:(AdobeStorageOrderRelation)relation
parentHref:(NSString *)parentHref __deprecated_msg("Use initWithResourceCollection:config");

- (instancetype)initWithResourceCollection:(AdobeStorageResourceCollection *)collection
config:(AdobeAssetFolderConfiguration *)config
parentHref:(NSString *)parentHref;

- (AdobeStorageResourceCollection *)resourceCollection __deprecated_msg("Access to the lower level resource collection is going away. It is causing synchronization issues for this class.");

+ (AdobeAssetFolder *)folderFromHref:(NSString *)href
inCloud:(AdobeCloud *)cloud __deprecated_msg("Use folderFromHref:cloud");

+ (AdobeAssetFolder *)folderFromHref:(NSString *)href
cloud:(AdobeCloud *)cloud;

+ (AdobeAssetFolder *)folderFromHref:(NSString *)href
inCloud:(AdobeCloud *)cloud
orderByField:(AdobeAssetFolderOrderBy)field
orderDirection:(AdobeAssetFolderOrderDirection)direction __deprecated_msg("Use folderFromHref:cloud:config");

+ (AdobeAssetFolder *)folderFromHref:(NSString *)href
cloud:(AdobeCloud *)cloud
orderByField:(AdobeAssetFolderOrderBy)field
orderDirection:(AdobeAssetFolderOrderDirection)direction __deprecated_msg("Use folderFromHref:cloud:config");

+ (AdobeAssetFolder *)folderFromHref:(NSString *)href
cloud:(AdobeCloud *)cloud
config:(AdobeAssetFolderConfiguration *)config;

+ (AdobeStorageOrderByProperty)getStorageOrderByProperty:(AdobeAssetFolderOrderBy)orderBy __deprecated_msg("Use storageOrderByProperty");

+ (AdobeStorageOrderByProperty)storageOrderByProperty:(AdobeAssetFolderOrderBy)orderBy;

+ (AdobeStorageOrderRelation)getStorageOrderRelation:(AdobeAssetFolderOrderDirection)orderDirection __deprecated_msg("Use storageOrderRelation");

+ (AdobeStorageOrderRelation)storageOrderRelation:(AdobeAssetFolderOrderDirection)orderDirection;

+ (void)  create:(NSString *)name
inFolder:(AdobeAssetFolder *)folder
inCloud:(AdobeCloud *)cloud
onCompletion:(void (^)(AdobeAssetFolder *folder))completionBlock
onError:(void (^)(NSError *error))errorBlock __deprecated_msg("create:parentFolder:cloud:successBlock:errorBlock");

+ (void)  create:(NSString *)name
parentFolder:(AdobeAssetFolder *)folder
cloud:(AdobeCloud *)cloud
successBlock:(void (^)(AdobeAssetFolder *folder))successBlock
errorBlock:(void (^)(NSError *error))errorBlock;

// Not publicly available due to its destructive behavior. For QE only (to clean up post test).
+ (void)emptyArchive:(AdobeCloud *)cloud
successBlock:(void (^)(void))successBlock
errorBlock:(void (^)(NSError *error))errorBlock;

@end

#endif /* ifndef AdobeAssetFolderProtectedHeader */
