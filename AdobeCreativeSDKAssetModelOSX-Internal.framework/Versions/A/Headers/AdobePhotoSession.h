/*************************************************************************
*
* ADOBE CONFIDENTIAL
* ___________________
*
*  Copyright 2015 Adobe Systems Incorporated
*  All Rights Reserved.
*
* NOTICE:  All information contained herein is, and remains
* the property of Adobe Systems Incorporated and its suppliers,
* if any.  The intellectual and technical concepts contained
* herein are proprietary to Adobe Systems Incorporated and its
* suppliers and are protected by trade secret or copyright law.
* Dissemination of this information or reproduction of this material
* is strictly forbidden unless prior written permission is obtained
* from Adobe Systems Incorporated.
**************************************************************************/

#ifndef AdobePhotoSessionHeader
#define AdobePhotoSessionHeader

#import <Foundation/Foundation.h>

@class AdobeCloudEndpoint;
@class AdobeNetworkHTTPRequest;
@class AdobeNetworkHTTPService;
@class AdobePhotoAsset;
@class AdobePhotoAssetRevision;
@class AdobePhotoCatalog;
@class AdobePhotoCollection;
@class AdobePhotoPage;

/** A generic completion handler for asynchronous data-based Photo Session data requests. */
typedef void (^AdobePhotoDataRequestCompletionHandler)(NSData *data, NSError *err);

/** The generic completion handler for asynchronous data-based Photo Session requests storing data to a file. */
typedef void (^AdobePhotoDataRequestToFileCompletionHandler)(NSString *file, NSError *err);

/** The generic completion handler for asynchronous catalog-based Photo Session requests. */
typedef void (^AdobePhotoCatalogRequestCompletionHandler)(AdobePhotoCatalog *catalog, NSError *err);

/** The generic completion handler for asynchronous multi-catalog-based Photo Session requests. */
typedef void (^AdobePhotoCatalogsRequestCompletionHandler)(AdobePhotoCatalogs *catalogs, NSError *err);

/** The generic completion handler for asynchronous collection-based Photo Session requests. */
typedef void (^AdobePhotoCollectionRequestCompletionHandler)(AdobePhotoCollection *collection, NSError *err);

/** The generic completion handler for asynchronous multi-collection-based Photo Session requests. */
typedef void (^AdobePhotoCollectionsRequestCompletionHandler)(AdobePhotoCollections *collections, NSError *err);

/** The generic completion handler for asynchronous order-based asset listing Photo Session requests. */
typedef void (^AdobePhotoAssetsListRequestCompletionHandler)(AdobePhotoAssets *assets, AdobePhotoPage *previousPage, AdobePhotoPage *nextPage, NSError *err);

/** The generic completion handler for asynchronous asset-based Photo Session requests. */
typedef void (^AdobePhotoAssetRequestCompletionHandler)(AdobePhotoAsset *asset, NSError *err);

/** The generic completion handler for asynchronous multi-asset-based Photo Session requests. */
typedef void (^AdobePhotoAssetsRequestCompletionHandler)(AdobePhotoAssets *assets, NSError *err);

typedef NS_ENUM (NSInteger, AdobePhotoAccountStatus)
{
AdobePhotoAccountStatusCreated = 1,
AdobePhotoAccountStatusTrial,
AdobePhotoAccountStatusTrialGracePeriod,
AdobePhotoAccountStatusTrialExpired,
AdobePhotoAccountStatusSubscriber,
AdobePhotoAccountStatusSubscriberGracePeriod,
AdobePhotoAccountStatusSubscriberExpired
};

typedef NS_ENUM (NSInteger, AdobePhotoSource)
{
AdobePhotoSourceUnknown = 0,
AdobePhotoSourceMaster,
AdobePhotoSourceProxy
};

/**
* Provides an Objective-C binding of the Adobe Photo Service API.
* Must be initialized with an instance of AdobeNetworkHTTPService, which in turn provides the configuration
* necessary to speak to a specific Adobe Photo environment (e.g., stage or production).
* See AdobePhotoSession:initWithHTTPService.
*/
@interface AdobePhotoSession : AdobeCloudServiceSession

/**
* Legacy service endpoint.
*/
+ (AdobeCloudEndpoint *)serviceEndpoint;

#pragma mark Catalog Methods
/** @name Catalog Methods */
///@{

/**
* Create a new catalog asynchronously.
*
* @param catalog           The catalog.
* @param type              The type of catalog.
* @param priority          The priority of the HTTP request.
* @param queue             If not nil queue determines the operation queue handler gets executed on.
* @param completionBlock   Called when the call has finished, failed or if it has been cancelled.
*
* @returns                 An AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)createCatalog:(AdobePhotoCatalog *)catalog
ofType:(AdobePhotoCatalogType)type
withRequestPriority:(NSOperationQueuePriority)priority
withHandlerQueue:(NSOperationQueue *)queue
onCompletion:(AdobePhotoCatalogRequestCompletionHandler)completionBlock __deprecated_msg("Use createCatalog:type:requestPriority:handlerQueue");

- (AdobeNetworkHTTPRequest *)createCatalog:(AdobePhotoCatalog *)catalog
type:(AdobePhotoCatalogType)type
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionBlock:(AdobePhotoCatalogRequestCompletionHandler)completionBlock;

/**
* Create a new catalog synchronously.
*
* @param catalog  The catalog.
* @param type     The type of catalog.
* @param name     The catalog name.
* @param priority The priority of the HTTP request.
* @param errorPtr An optional pointer to an NSError object that will be set in case of an error.
*
* @returns         The created catalog on success or nil on failure.
*/
- (AdobePhotoCatalog *)createCatalog:(AdobePhotoCatalog *)catalog
ofType:(AdobePhotoCatalogType)type
withRequestPriority:(NSOperationQueuePriority)priority
onError:(NSError **)errorPtr __deprecated_msg("Use createCatalog:type:requestPriority:error");

- (AdobePhotoCatalog *)createCatalog:(AdobePhotoCatalog *)catalog
type:(AdobePhotoCatalogType)type
requestPriority:(NSOperationQueuePriority)priority
error:(NSError **)errorPtr;

/**
* Update a catalog asynchronously.
*
* @param catalog           The catalog.
* @param priority          The priority of the HTTP request.
* @param queue             If not nil queue determines the operation queue handler gets executed on.
* @param completionBlock   Called when the call has finished, failed or if it has been cancelled.
*
* @returns                 An AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)updateCatalog:(AdobePhotoCatalog *)catalog
withRequestPriority:(NSOperationQueuePriority)priority
withHandlerQueue:(NSOperationQueue *)queue
onCompletion:(AdobePhotoCatalogRequestCompletionHandler)completionBlock __deprecated_msg("Use updateCatalog:requestPriority:handlerQueue:completionBlock");

- (AdobeNetworkHTTPRequest *)updateCatalog:(AdobePhotoCatalog *)catalog
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionBlock:(AdobePhotoCatalogRequestCompletionHandler)completionBlock;

/**
* Update a catalog synchronously.
*
* @param catalog  The catalog.
* @param priority The priority of the HTTP request.
* @param errorPtr An optional pointer to an NSError object that will be set in case of an error.
*
* @returns         The catalog updated on success or nil on failure.
*/
- (AdobePhotoCatalog *)updateCatalog:(AdobePhotoCatalog *)catalog
withRequestPriority:(NSOperationQueuePriority)priority
onError:(NSError **)errorPtr __deprecated_msg("Use updateCatalog:requestPriority:error");

- (AdobePhotoCatalog *)updateCatalog:(AdobePhotoCatalog *)catalog
requestPriority:(NSOperationQueuePriority)priority
error:(NSError **)errorPtr;

/**
* Delete a catalog asynchronously.
*
* @param catalog           The catalog.
* @param priority          The priority of the HTTP request.
* @param queue             If not nil queue determines the operation queue handler gets executed on.
* @param completionBlock   Called when the call has finished, failed or if it has been cancelled.
*
* @returns                 An AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)deleteCatalog:(AdobePhotoCatalog *)catalog
withRequestPriority:(NSOperationQueuePriority)priority
withHandlerQueue:(NSOperationQueue *)queue
onCompletion:(AdobePhotoCatalogRequestCompletionHandler)completionBlock __deprecated_msg("Use deleteCatalog:requestPriority:handlerQueue:completionBlock");

- (AdobeNetworkHTTPRequest *)deleteCatalog:(AdobePhotoCatalog *)catalog
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionBlock:(AdobePhotoCatalogRequestCompletionHandler)completionBlock;

/**
* Delete a catalog synchronously.
*
* @param catalog  The catalog.
* @param priority The priority of the HTTP request.
* @param errorPtr An optional pointer to an NSError object that will be set in case of an error.
*
* @returns         The catalog deleted on success or nil on failure.
*/
- (AdobePhotoCatalog *)deleteCatalog:(AdobePhotoCatalog *)catalog
withRequestPriority:(NSOperationQueuePriority)priority
onError:(NSError **)errorPtr __deprecated_msg("Use deleteCatalog:requestPriority:error");

- (AdobePhotoCatalog *)deleteCatalog:(AdobePhotoCatalog *)catalog
requestPriority:(NSOperationQueuePriority)priority
error:(NSError **)errorPtr;

/**
* Get a catalog asynchronously.
*
* @param uuid              The catalog id.
* @param cloud             The cloud.
* @param priority          The priority of the HTTP request.
* @param queue             If not nil queue determines the operation queue handler gets executed on.
* @param completionBlock   Called when the call has finished, failed or if it has been cancelled.
*
* @returns                 An AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)getCatalogWithUUID:(NSString *)uuid
inCloud:(AdobeCloud *)cloud
withRequestPriority:(NSOperationQueuePriority)priority
withHandlerQueue:(NSOperationQueue *)queue
onCompletion:(AdobePhotoCatalogRequestCompletionHandler)completionBlock __deprecated_msg("Use catalogWithUUID:cloud:requestPriority:handlerQueue:completionBlock");

- (AdobeNetworkHTTPRequest *)catalogWithUUID:(NSString *)uuid
cloud:(AdobeCloud *)cloud
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionBlock:(AdobePhotoCatalogRequestCompletionHandler)completionBlock;

/**
* Get a catalog synchronously.
*
* @param uuid     The catalog id.
* @param cloud    The cloud.
* @param priority The priority of the HTTP request.
* @param errorPtr An optional pointer to an NSError object that will be set in case of an error.
*
* @returns         The catalog on success or nil on failure.
*/
- (AdobePhotoCatalog *)getCatalogWithUUID:(NSString *)uuid
inCloud:(AdobeCloud *)cloud
withRequestPriority:(NSOperationQueuePriority)priority
onError:(NSError **)errorPtr __deprecated_msg("Use catalogWithUUID:cloud:requestPriority:error");

- (AdobePhotoCatalog *)catalogWithUUID:(NSString *)uuid
cloud:(AdobeCloud *)cloud
requestPriority:(NSOperationQueuePriority)priority
error:(NSError **)errorPtr;

/**
* Get a catalog asynchronously.
*
* @param catalog           The catalog.
* @param priority          The priority of the HTTP request.
* @param queue             If not nil queue determines the operation queue handler gets executed on.
* @param completionBlock   Called when the call has finished, failed or if it has been cancelled.
*
* @returns                 An AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)getCatalog:(AdobePhotoCatalog *)catalog
withRequestPriority:(NSOperationQueuePriority)priority
withHandlerQueue:(NSOperationQueue *)queue
onCompletion:(AdobePhotoCatalogRequestCompletionHandler)completionBlock __deprecated_msg("Use catalog:requestPriority:handlerQueue:completionBlock");

- (AdobeNetworkHTTPRequest *)catalog:(AdobePhotoCatalog *)catalog
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionBlock:(AdobePhotoCatalogRequestCompletionHandler)completionBlock;

/**
* Get a catalog synchronously.
*
* @param catalog  The catalog.
* @param priority The priority of the HTTP request.
* @param errorPtr An optional pointer to an NSError object that will be set in case of an error.
*
* @returns         The catalog on success or nil on failure.
*/
- (AdobePhotoCatalog *)getCatalog:(AdobePhotoCatalog *)catalog
withRequestPriority:(NSOperationQueuePriority)priority
onError:(NSError **)errorPtr __deprecated_msg("Use catalog:requestPriority:error");

- (AdobePhotoCatalog *)catalog:(AdobePhotoCatalog *)catalog
requestPriority:(NSOperationQueuePriority)priority
error:(NSError **)errorPtr;

/**
* List a type of catalog asynchronously.
*
* @param type              The type of catalog to list.
* @param cloud             The cloud.
* @param priority          The priority of the HTTP request.
* @param queue             If not nil queue determines the operation queue handler gets executed on.
* @param completionBlock   Called when the call has finished, failed or if it has been cancelled.
*
* @returns                 An AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)listCatalogsOfType:(AdobePhotoCatalogType)type
inCloud:(AdobeCloud *)cloud
withRequestPriority:(NSOperationQueuePriority)priority
withHandlerQueue:(NSOperationQueue *)queue
onCompletion:(AdobePhotoCatalogsRequestCompletionHandler)completionBlock __deprecated_msg("Use listCatalogsOfType:cloud:requestPriority:handlerQueue:completionBlock");

- (AdobeNetworkHTTPRequest *)listCatalogsOfType:(AdobePhotoCatalogType)type
cloud:(AdobeCloud *)cloud
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionBlock:(AdobePhotoCatalogsRequestCompletionHandler)completionBlock;

/**
* List a type of catalog synchronously.
*
* @param type     The type of catalog to list.
* @param cloud    The cloud.
* @param priority The priority of the HTTP request.
* @param errorPtr An optional pointer to an NSError object that will be set in case of an error.
*
* @returns        The catalogs on success or nil on failure.
*/
- (AdobePhotoCatalogs *)listCatalogsOfType:(AdobePhotoCatalogType)type
inCloud:(AdobeCloud *)cloud
withRequestPriority:(NSOperationQueuePriority)priority
onError:(NSError **)errorPtr __deprecated_msg("Use listCatalogsOfType:cloud:requestPriority:error");

- (AdobePhotoCatalogs *)listCatalogsOfType:(AdobePhotoCatalogType)type
cloud:(AdobeCloud *)cloud
requestPriority:(NSOperationQueuePriority)priority
error:(NSError **)errorPtr;

/**
* List all assets in a catalog asynchronously.
*
* @param catalog           The catalog.
* @param page              The page to fetch. Nil for the first page.
* @param limit             Number of collections to return. Default value is 100. Note that the response may contain more than 'limit' number of
* collections returned if the collections at the 'limit' boundary has the same name_after.
* @param priority          The priority of the HTTP request.
* @param queue             If not nil queue determines the operation queue handler gets executed on.
* @param completionBlock   Called when the call has finished, failed or if it has been cancelled.
*
* @returns                 An AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)listAssetsInCatalog:(AdobePhotoCatalog *)catalog
page:(AdobePhotoPage *)page
limit:(NSUInteger)limit
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionBlock:(AdobePhotoAssetsListRequestCompletionHandler)completionBlock;

/**
* List all assets in a catalog using the date synchronously.
*
* @param collection  The collection.
* @param page        The page to fetch.
*                    On return, this value will change to be the next page (or nil if the last page).
* @param limit       Number of collections to return. Default value is 100. Note that the response may contain more than 'limit' number of collections
* returned if the collections at the 'limit' boundary has the same name_after.
* @param priority    The priority of the HTTP request.
* @param errorPtr    An optional pointer to an NSError object that will be set in case of an error.
*
* @returns           The assets on success or nil on failure.
*/
- (AdobePhotoAssets *)listAssetsInCatalog:(AdobePhotoCatalog *)catalog
page:(AdobePhotoPage *)page
limit:(NSUInteger)limit
requestPriority:(NSOperationQueuePriority)priority
error:(NSError **)errorPtr;

/**
* List all collections in a catalog asynchronously.
*
* @param catalog           The catalog.
* @param name              Start the list after the name, or nil to start at the beginning of the list.
* @param limit             Number of collections to return. Default value is 100. Note that the response may contain more than 'limit' number of
* collections returned if the collections at the 'limit' boundary has the same name_after.
* @param priority          The priority of the HTTP request.
* @param queue             If not nil queue determines the operation queue handler gets executed on.
* @param completionBlock   Called when the call has finished, failed or if it has been cancelled.
*
* @returns                 An AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)listCollectionsInCatalog:(AdobePhotoCatalog *)catalog
startingAfter:(NSString *)name
withLimit:(NSUInteger)limit
withRequestPriority:(NSOperationQueuePriority)priority
withHandlerQueue:(NSOperationQueue *)queue
onCompletion:(AdobePhotoCollectionsRequestCompletionHandler)completionBlock __deprecated_msg("Use listCollectionsInCatalog:afterName:limit:requestPriority:handlerQueue:completionBlock");

- (AdobeNetworkHTTPRequest *)listCollectionsInCatalog:(AdobePhotoCatalog *)catalog
afterName:(NSString *)name
limit:(NSUInteger)limit
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionBlock:(AdobePhotoCollectionsRequestCompletionHandler)completionBlock;

/**
* List all collections in a catalog synchronously.
*
* @param catalog  The catalog.
* @param name     Start the list after the name, or nil to start at the beginning of the list.
* @param limit    Number of collections to return. Default value is 100. Note that the response may contain more than 'limit' number of collections returned if the collections at the 'limit' boundary has the same name_after.
* @param priority The priority of the HTTP request.
* @param errorPtr An optional pointer to an NSError object that will be set in case of an error.
*
* @returns        The collections on success or nil on failure.
*/
- (AdobePhotoCollections *)listCollectionsInCatalog:(AdobePhotoCatalog *)catalog
startingAfter:(NSString *)name
withLimit:(NSUInteger)limit
withRequestPriority:(NSOperationQueuePriority)priority
onError:(NSError **)errorPtr __deprecated_msg("Use listCollectionsInCatalog:afterName:limit:requestPriority:error");

- (AdobePhotoCollections *)listCollectionsInCatalog:(AdobePhotoCatalog *)catalog
afterName:(NSString *)name
limit:(NSUInteger)limit
requestPriority:(NSOperationQueuePriority)priority
error:(NSError **)errorPtr;

/**
* Get the number of collections in a catalog asynchronously.
*
* @param catalog           The catalog.
* @param priority          The priority of the HTTP request.
* @param queue             If not nil queue determines the operation queue handler gets executed on.
* @param completionBlock   Called when the call has finished, failed or if it has been cancelled.
*
* @returns                 An AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)getCollectionCountInCatalog:(AdobePhotoCatalog *)catalog
withRequestPriority:(NSOperationQueuePriority)priority
withHandlerQueue:(NSOperationQueue *)queue
onCompletion:(void (^)(NSUInteger count, NSError *err))handler __deprecated_msg("Use collectionCountInCatalog:requestPriority:handlerQueue:completionBlock");

- (AdobeNetworkHTTPRequest *)collectionCountInCatalog:(AdobePhotoCatalog *)catalog
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionBlock:(void (^)(NSUInteger count, NSError *err))completionBlock;

/**
* Get the number of collections in a catalog synchronously.
*
* @param catalog  The catalog.
* @param priority The priority of the HTTP request.
* @param errorPtr An optional pointer to an NSError object that will be set in case of an error.
*
* @returns        The collection count on success or nil on failure.
*/
- (NSUInteger)getCollectionCountInCatalog:(AdobePhotoCatalog *)catalog
withRequestPriority:(NSOperationQueuePriority)priority
onError:(NSError **)errorPtr __deprecated_msg("Use collectionCountInCatalog:requestPriority:error");

- (NSUInteger)collectionCountInCatalog:(AdobePhotoCatalog *)catalog
requestPriority:(NSOperationQueuePriority)priority
error:(NSError **)errorPtr;

/**
* Get the number of assets in a catalog asynchronously.
*
* @param catalog           The catalog.
* @param priority          The priority of the HTTP request.
* @param queue             If not nil queue determines the operation queue handler gets executed on.
* @param completionBlock   Called when the call has finished, failed or if it has been cancelled.
*
* @returns                 An AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)getAssetCountInCatalog:(AdobePhotoCatalog *)catalog
withRequestPriority:(NSOperationQueuePriority)priority
withHandlerQueue:(NSOperationQueue *)queue
onCompletion:(void (^)(NSUInteger count, NSError *err))completionBlock __deprecated_msg("Use assetCountInCatalog:requestPriority:handlerQueue:completionBlock");

- (AdobeNetworkHTTPRequest *)assetCountInCatalog:(AdobePhotoCatalog *)catalog
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionBlock:(void (^)(NSUInteger count, NSError *err))completionBlock;

/**
* Get the number of assets in a catalog synchronously.
*
* @param catalog  The catalog.
* @param priority The priority of the HTTP request.
* @param errorPtr An optional pointer to an NSError object that will be set in case of an error.
*
* @returns         The asset count on success or nil on failure.
*/
- (NSUInteger)getAssetCountInCatalog:(AdobePhotoCatalog *)catalog
withRequestPriority:(NSOperationQueuePriority)priority
onError:(NSError **)errorPtr __deprecated_msg("Use assetCountInCatalog:requestPriority:error");

- (NSUInteger)assetCountInCatalog:(AdobePhotoCatalog *)catalog
requestPriority:(NSOperationQueuePriority)priority
error:(NSError **)errorPtr;

///@}


#pragma mark Collection Methods
/** @name Collection Methods */
///@{

/**
* Create a new collection asynchronously.
*
* @param collection            The collection.
* @param catalog               The catalog.
* @param priority              The priority of the HTTP request.
* @param queue                 If not nil queue determines the operation queue handler gets executed on.
* @param completionBlock       Called when the call has finished, failed or if it has been cancelled.
*
* @returns                     An AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)createCollection:(AdobePhotoCollection *)collection
inCatalog:(AdobePhotoCatalog *)catalog
withRequestPriority:(NSOperationQueuePriority)priority
withHandlerQueue:(NSOperationQueue *)queue
onCompletion:(AdobePhotoCollectionRequestCompletionHandler)completionBlock __deprecated_msg("Use createCollection:catalog:requestPriority:handlerQueue:completionBlock");

- (AdobeNetworkHTTPRequest *)createCollection:(AdobePhotoCollection *)collection
catalog:(AdobePhotoCatalog *)catalog
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionBlock:(AdobePhotoCollectionRequestCompletionHandler)completionBlock;

/**
* Create a new collection synchronously.
*
* @param collection The collection.
* @param catalog    The catalog.
* @param priority   The priority of the HTTP request.
* @param errorPtr   An optional pointer to an NSError object that will be set in case of an error.
*
* @returns          The created collection on success or nil on failure.
*/
- (AdobePhotoCollection *)createCollection:(AdobePhotoCollection *)collection
inCatalog:(AdobePhotoCatalog *)catalog
withRequestPriority:(NSOperationQueuePriority)priority
onError:(NSError **)errorPtr __deprecated_msg("Use createCollection:catalog:requestPriority:error");

- (AdobePhotoCollection *)createCollection:(AdobePhotoCollection *)collection
catalog:(AdobePhotoCatalog *)catalog
requestPriority:(NSOperationQueuePriority)priority
error:(NSError **)errorPtr;

/**
* Update a collection asynchronously.
*
* @param collection            The collection.
* @param priority              The priority of the HTTP request.
* @param queue                 If not nil queue determines the operation queue handler gets executed on.
* @param completionBlock       Called when the call has finished, failed or if it has been cancelled.
*
* @returns                     An AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)updateCollection:(AdobePhotoCollection *)collection
withRequestPriority:(NSOperationQueuePriority)priority
withHandlerQueue:(NSOperationQueue *)queue
onCompletion:(AdobePhotoCollectionRequestCompletionHandler)completionBlock __deprecated_msg("Use updateCollection:requestPriority:handlerQueue:completionBlock");

- (AdobeNetworkHTTPRequest *)updateCollection:(AdobePhotoCollection *)collection
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionBlock:(AdobePhotoCollectionRequestCompletionHandler)completionBlock;

/**
* Update a collection synchronously.
*
* @param collection The collection.
* @param priority   The priority of the HTTP request.
* @param errorPtr   An optional pointer to an NSError object that will be set in case of an error.
*
* @returns          The collection updated on success or nil on failure.
*/
- (AdobePhotoCollection *)updateCollection:(AdobePhotoCollection *)collection
withRequestPriority:(NSOperationQueuePriority)priority
onError:(NSError **)errorPtr __deprecated_msg("Use updateCollection:requestPriority:error");

- (AdobePhotoCollection *)updateCollection:(AdobePhotoCollection *)collection
requestPriority:(NSOperationQueuePriority)priority
error:(NSError **)errorPtr;

/**
* Delete a collection asynchronously.
*
* @param collection            The collection.
* @param priority              The priority of the HTTP request.
* @param queue                 If not nil queue determines the operation queue handler gets executed on.
* @param completionBlock       Called when the call has finished, failed or if it has been cancelled.
*
* @returns                     An AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)deleteCollection:(AdobePhotoCollection *)collection
withRequestPriority:(NSOperationQueuePriority)priority
withHandlerQueue:(NSOperationQueue *)queue
onCompletion:(AdobePhotoCollectionRequestCompletionHandler)completionBlock __deprecated_msg("Use deleteCollection:requestPriority:handlerQueue:completionBlock");

- (AdobeNetworkHTTPRequest *)deleteCollection:(AdobePhotoCollection *)collection
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionBlock:(AdobePhotoCollectionRequestCompletionHandler)completionBlock;

/**
* Delete a collection synchronously.
*
* @param collection The collection.
* @param priority   The priority of the HTTP request.
* @param errorPtr   An optional pointer to an NSError object that will be set in case of an error.
*
* @returns          The collection deleted on success or nil on failure.
*/
- (AdobePhotoCollection *)deleteCollection:(AdobePhotoCollection *)collection
withRequestPriority:(NSOperationQueuePriority)priority
onError:(NSError **)errorPtr __deprecated_msg("Use deleteCollection:requestPriority:error");

- (AdobePhotoCollection *)deleteCollection:(AdobePhotoCollection *)collection
requestPriority:(NSOperationQueuePriority)priority
error:(NSError **)errorPtr;

/**
* Get a collection asynchronously.
*
* @param uuid              The collection id.
* @param catalog           The catalog.
* @param cloud             The cloud.
* @param priority          The priority of the HTTP request.
* @param queue             If not nil queue determines the operation queue handler gets executed on.
* @param completionBlock   Called when the call has finished, failed or if it has been cancelled.
*
* @returns                 An AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)getCollectionWithUUID:(NSString *)uuid
fromCatalog:(AdobePhotoCatalog *)catalog
withRequestPriority:(NSOperationQueuePriority)priority
withHandlerQueue:(NSOperationQueue *)queue
onCompletion:(AdobePhotoCollectionRequestCompletionHandler)completionBlock __deprecated_msg("Use collectionWithUUID:catalog:requestPriority:handlerQueue:completionBlock");

- (AdobeNetworkHTTPRequest *)collectionWithUUID:(NSString *)uuid
catalog:(AdobePhotoCatalog *)catalog
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionBlock:(AdobePhotoCollectionRequestCompletionHandler)completionBlock;

/**
* Get a collection synchronously.
*
* @param uuid     The collection id.
* @param catalog  The catalog.
* @param cloud    The cloud.
* @param priority The priority of the HTTP request.
* @param errorPtr An optional pointer to an NSError object that will be set in case of an error.
*
* @returns         The collection on success or nil on failure.
*/
- (AdobePhotoCollection *)getCollectionWithUUID:(NSString *)uuid
fromCatalog:(AdobePhotoCatalog *)catalog
withRequestPriority:(NSOperationQueuePriority)priority
onError:(NSError **)errorPtr __deprecated_msg("Use collectionWithUUID:catalog:requestPriority:error");

- (AdobePhotoCollection *)collectionWithUUID:(NSString *)uuid
catalog:(AdobePhotoCatalog *)catalog
requestPriority:(NSOperationQueuePriority)priority
error:(NSError **)errorPtr;

/**
* Get a collection asynchronously.
*
* @param collection            The collection.
* @param priority              The priority of the HTTP request.
* @param queue                 If not nil queue determines the operation queue handler gets executed on.
* @param completionBlock       Called when the call has finished, failed or if it has been cancelled.
*
* @returns                     An AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)getCollection:(AdobePhotoCollection *)collection
withRequestPriority:(NSOperationQueuePriority)priority
withHandlerQueue:(NSOperationQueue *)queue
onCompletion:(AdobePhotoCollectionRequestCompletionHandler)completionBlock __deprecated_msg("Use collection:requestPriority:handlerQueue:completionBlock");

- (AdobeNetworkHTTPRequest *)collection:(AdobePhotoCollection *)collection
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionBlock:(AdobePhotoCollectionRequestCompletionHandler)completionBlock;

/**
* Get a collection synchronously.
*
* @param collection The collection.
* @param priority   The priority of the HTTP request.
* @param errorPtr   An optional pointer to an NSError object that will be set in case of an error.
*
* @returns          The collection on success or nil on failure.
*/
- (AdobePhotoCollection *)getCollection:(AdobePhotoCollection *)collection
withRequestPriority:(NSOperationQueuePriority)priority
onError:(NSError **)errorPtr __deprecated_msg("Use collection:requestPriority:error");

- (AdobePhotoCollection *)collection:(AdobePhotoCollection *)collection
requestPriority:(NSOperationQueuePriority)priority
error:(NSError **)errorPtr;

/**
* Add assets to a collection asynchronously.
*
* @param assets                The assets.
* @param collection            The collection.
* @param priority              The priority of the HTTP request.
* @param queue                 If not nil queue determines the operation queue handler gets executed on.
* @param completionBlock       Called when the call has finished, failed or if it has been cancelled.
*
* @returns                     An AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)addAssets:(AdobePhotoAssets *)assets
toCollection:(AdobePhotoCollection *)collection
withRequestPriority:(NSOperationQueuePriority)priority
withHandlerQueue:(NSOperationQueue *)queue
onCompletion:(AdobePhotoAssetsRequestCompletionHandler)completionBlock __deprecated_msg("Use addAssets:collection:requestPriority:handlerQueue:completionBlock");

- (AdobeNetworkHTTPRequest *)addAssets:(AdobePhotoAssets *)assets
collection:(AdobePhotoCollection *)collection
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionBlock:(AdobePhotoAssetsRequestCompletionHandler)completionBlock;

/**
* Add assets to a collection asynchronously.
*
* @param assets     The assets.
* @param collection The collection.
* @param priority   The priority of the HTTP request.
* @param errorPtr   An optional pointer to an NSError object that will be set in case of an error.
*
* @returns          The assets added to the collection on success or nil on failure.
*/
- (AdobePhotoAssets *)addAssets:(AdobePhotoAssets *)assets
toCollection:(AdobePhotoCollection *)collection
withRequestPriority:(NSOperationQueuePriority)priority
onError:(NSError **)errorPtr __deprecated_msg("Use addAssets:collection:requestPriority:error");

- (AdobePhotoAssets *)addAssets:(AdobePhotoAssets *)assets
collection:(AdobePhotoCollection *)collection
requestPriority:(NSOperationQueuePriority)priority
error:(NSError **)errorPtr;

/**
* Update assets to a collection asynchronously.
*
* @param assets                The assets.
* @param collection            The collection.
* @param priority              The priority of the HTTP request.
* @param queue                 If not nil queue determines the operation queue handler gets executed on.
* @param completionBlock       Called when the call has finished, failed or if it has been cancelled.
*
* @returns                     An AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)updateAssets:(AdobePhotoAssets *)assets
inCollection:(AdobePhotoCollection *)collection
withRequestPriority:(NSOperationQueuePriority)priority
withHandlerQueue:(NSOperationQueue *)queue
onCompletion:(AdobePhotoAssetsRequestCompletionHandler)completionBlock __deprecated_msg("Use updateAssets:collection:requestPriority:handlerQueue:completionBlock");

- (AdobeNetworkHTTPRequest *)updateAssets:(AdobePhotoAssets *)assets
collection:(AdobePhotoCollection *)collection
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionBlock:(AdobePhotoAssetsRequestCompletionHandler)completionBlock;

/**
* Update assets to a collection asynchronously.
*
* @param assets     The assets.
* @param collection The collection.
* @param priority   The priority of the HTTP request.
* @param errorPtr   An optional pointer to an NSError object that will be set in case of an error.
*
* @returns          The assets updated in the collection on success or nil on failure.
*/
- (AdobePhotoAssets *)updateAssets:(AdobePhotoAssets *)assets
inCollection:(AdobePhotoCollection *)collection
withRequestPriority:(NSOperationQueuePriority)priority
onError:(NSError **)errorPtr __deprecated_msg("Use updateAssets:collection:requestPriority:error");

- (AdobePhotoAssets *)updateAssets:(AdobePhotoAssets *)assets
collection:(AdobePhotoCollection *)collection
requestPriority:(NSOperationQueuePriority)priority
error:(NSError **)errorPtr;

/**
* Remove assets from a collection asynchronously.
*
* @param assets                The assets.
* @param collection            The collection.
* @param priority              The priority of the HTTP request.
* @param queue                 If not nil queue determines the operation queue handler gets executed on.
* @param completionBlock       Called when the call has finished, failed or if it has been cancelled.
*
* @returns                     An AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)removeAssets:(AdobePhotoAssets *)assets
fromCollection:(AdobePhotoCollection *)collection
withRequestPriority:(NSOperationQueuePriority)priority
withHandlerQueue:(NSOperationQueue *)queue
onCompletion:(AdobePhotoAssetsRequestCompletionHandler)completionBlock __deprecated_msg("Use removeAssets:collection:requestPriority:handlerQueue:completionBlock");

- (AdobeNetworkHTTPRequest *)removeAssets:(AdobePhotoAssets *)assets
collection:(AdobePhotoCollection *)collection
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionBlock:(AdobePhotoAssetsRequestCompletionHandler)completionBlock;

/**
* Remove assets from a collection asynchronously.
*
* @param assets     The assets.
* @param collection The collection.
* @param priority   The priority of the HTTP request.
* @param errorPtr   An optional pointer to an NSError object that will be set in case of an error.
*
* @returns          The assets removed from the collection on success or nil on failure.
*/
- (AdobePhotoAssets *)removeAssets:(AdobePhotoAssets *)assets
fromCollection:(AdobePhotoCollection *)collection
withRequestPriority:(NSOperationQueuePriority)priority
onError:(NSError **)errorPtr __deprecated_msg("Use removeAssets:collection:requestPriority:error");

- (AdobePhotoAssets *)removeAssets:(AdobePhotoAssets *)assets
collection:(AdobePhotoCollection *)collection
requestPriority:(NSOperationQueuePriority)priority
error:(NSError **)errorPtr;

/**
* List all assets in a collection using the date asynchronously.
*
* @param collection            The collection.
* @param page                  The page to fetch. Nil for the first page.
* @param sortType              The sort type to use.
* @param flag                  The result to return the assets using.
* @param limit                 Number of collections to return. Default value is 100. Note that the response may contain more than 'limit' number of
* collections returned if the collections at the 'limit' boundary has the same name_after.
* @param priority              The priority of the HTTP request.
* @param queue                 If not nil queue determines the operation queue handler gets executed on.
* @param completionBlock       Called when the call has finished, failed or if it has been cancelled.
*
* @returns                     An AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)listAssetsInCollection:(AdobePhotoCollection *)collection
forPage:(AdobePhotoPage *)page
sortingBy:(AdobePhotoCollectionSort)sortType
withFlag:(AdobePhotoCollectionFlag)flag
withLimit:(NSUInteger)limit
withRequestPriority:(NSOperationQueuePriority)priority
withHandlerQueue:(NSOperationQueue *)queue
onCompletion:(AdobePhotoAssetsListRequestCompletionHandler)completionBlock __deprecated_msg("Use listAssetsInCollection:page:sortType:flag:limit:requestPriority:handlerQueue:completionBlock");

- (AdobeNetworkHTTPRequest *)listAssetsInCollection:(AdobePhotoCollection *)collection
page:(AdobePhotoPage *)page
sortType:(AdobePhotoCollectionSort)sortType
flag:(AdobePhotoCollectionFlag)flag
limit:(NSUInteger)limit
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionBlock:(AdobePhotoAssetsListRequestCompletionHandler)completionBlock;

/**
* List all assets in a collection using the date synchronously.
*
* @param collection  The collection.
* @param page        The page to fetch.
*                    On return, this value will change to be the next page (or nil if the last page).
* @param sortType    The sort type to use.
* @param flag        The result to return the assets using.
* @param limit       Number of collections to return. Default value is 100. Note that the response may contain more than 'limit' number of collections
* returned if the collections at the 'limit' boundary has the same name_after.
* @param priority    The priority of the HTTP request.
* @param errorPtr    An optional pointer to an NSError object that will be set in case of an error.
*
* @returns           The assets on success or nil on failure.
*/
- (AdobePhotoAssets *)listAssetsInCollection:(AdobePhotoCollection *)collection
forPage:(AdobePhotoPage *)page
sortingBy:(AdobePhotoCollectionSort)sortType
withFlag:(AdobePhotoCollectionFlag)flag
withLimit:(NSUInteger)limit
withRequestPriority:(NSOperationQueuePriority)priority
onError:(NSError **)errorPtr __deprecated_msg("Use listAssetsInCollection:page:sortType:flag:limit:requestPriority:error");

- (AdobePhotoAssets *)listAssetsInCollection:(AdobePhotoCollection *)collection
page:(AdobePhotoPage *)page
sortType:(AdobePhotoCollectionSort)sortType
flag:(AdobePhotoCollectionFlag)flag
limit:(NSUInteger)limit
requestPriority:(NSOperationQueuePriority)priority
error:(NSError **)errorPtr;

/**
* Get the number of assets in a collection asynchronously.
*
* @param collection            The collection.
* @param priority              The priority of the HTTP request.
* @param queue                 If not nil queue determines the operation queue handler gets executed on.
* @param completionBlock       Called when the call has finished, failed or if it has been cancelled.
*
* @returns                     An AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)getAssetCountInCollection:(AdobePhotoCollection *)collection
withRequestPriority:(NSOperationQueuePriority)priority
withHandlerQueue:(NSOperationQueue *)queue
onCompletion:(void (^)(NSUInteger count, NSError *err))completionBlock __deprecated_msg("Use assetCountInCollection:requestPriority:handlerQueue:completionBlock");

- (AdobeNetworkHTTPRequest *)assetCountInCollection:(AdobePhotoCollection *)collection
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionBlock:(void (^)(NSUInteger count, NSError *err))completionBlock;

/**
* Get the number of assets in a collection synchronously.
*
* @param collection The collection.
* @param priority   The priority of the HTTP request.
* @param errorPtr   An optional pointer to an NSError object that will be set in case of an error.
*
* @returns          The asset count on success or nil on failure.
*/
- (NSUInteger)getAssetCountInCollection:(AdobePhotoCollection *)collection
withRequestPriority:(NSOperationQueuePriority)priority
onError:(NSError **)errorPtr __deprecated_msg("Use assetCountInCollection:requestPriority:error");

- (NSUInteger)assetCountInCollection:(AdobePhotoCollection *)collection
requestPriority:(NSOperationQueuePriority)priority
error:(NSError **)errorPtr;

///@}


#pragma mark Asset Methods
/** @name Asset Methods */
///@{

/**
* Create a new asset asynchronously.
*
* @param asset             The asset.
* @param catalog           The catalog.
* @param path              The path to the data.
* @param type              The content-type of the file.
* @param priority          The priority of the HTTP request.
* @param queue             If not nil queue determines the operation queue handler gets executed on.
* @param completionBlock   Called when the call has finished, failed or if it has been cancelled.
*
* @returns                 An AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)createAsset:(AdobePhotoAsset *)asset
inCatalog:(AdobePhotoCatalog *)catalog
withDataPath:(NSURL *)path
withContentType:(NSString *)type
withRequestPriority:(NSOperationQueuePriority)priority
withHandlerQueue:(NSOperationQueue *)queue
onCompletion:(AdobePhotoAssetRequestCompletionHandler)completionBlock __deprecated_msg("Use createAsset:catalog:dataPath:contentType:requestPriority:handlerQueue:completionBlock");

- (AdobeNetworkHTTPRequest *)createAsset:(AdobePhotoAsset *)asset
catalog:(AdobePhotoCatalog *)catalog
dataPath:(NSURL *)path
contentType:(NSString *)type
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionBlock:(AdobePhotoAssetRequestCompletionHandler)completionBlock;

/**
* Create a new asset synchronously.
*
* @param asset    The asset.
* @param catalog  The catalog.
* @param path     The path to the data.
* @param type     The content-type of the file.
* @param priority The priority of the HTTP request.
* @param errorPtr An optional pointer to an NSError object that will be set in case of an error.
*
* @returns         The created asset on success or nil on failure.
*/
- (AdobePhotoAsset *)createAsset:(AdobePhotoAsset *)asset
inCatalog:(AdobePhotoCatalog *)catalog
withDataPath:(NSURL *)path
withContentType:(NSString *)type
withRequestPriority:(NSOperationQueuePriority)priority
onError:(NSError **)errorPtr __deprecated_msg("Use createAsset:catalog:dataPath:contentType:requestPriority:error");

- (AdobePhotoAsset *)createAsset:(AdobePhotoAsset *)asset
catalog:(AdobePhotoCatalog *)catalog
dataPath:(NSURL *)path
contentType:(NSString *)type
requestPriority:(NSOperationQueuePriority)priority
error:(NSError **)errorPtr;

/**
* Create a new asset in a collection asynchronously.
*
* @param asset                 The asset.
* @param collection            The collection to add the asset into.
* @param path                  The path to the data.
* @param type                  The content-type of the file.
* @param priority              The priority of the HTTP request.
* @param queue                 If not nil queue determines the operation queue handler gets executed on.
* @param completionBlock       Called when the call has finished, failed or if it has been cancelled.
*
* @returns                     An AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)createAsset:(AdobePhotoAsset *)asset
inCollection:(AdobePhotoCollection *)collection
withDataPath:(NSURL *)path
withContentType:(NSString *)type
withRequestPriority:(NSOperationQueuePriority)priority
withHandlerQueue:(NSOperationQueue *)queue
onCompletion:(AdobePhotoAssetRequestCompletionHandler)completionBlock __deprecated_msg("Use createAsset:collection:dataPath:contentType:requestPriority:handlerQueue:completionBlock");

- (AdobeNetworkHTTPRequest *)createAsset:(AdobePhotoAsset *)asset
collection:(AdobePhotoCollection *)collection
dataPath:(NSURL *)path
contentType:(NSString *)type
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionBlock:(AdobePhotoAssetRequestCompletionHandler)completionBlock;

/**
* Create a new asset in a collection synchronously.
*
* @param asset      The name.
* @param collection The collection to add the asset into.
* @param path       The path to the data.
* @param type       The content-type of the file.
* @param priority   The priority of the HTTP request.
* @param errorPtr   An optional pointer to an NSError object that will be set in case of an error.
*
* @returns          The created asset on success or nil on failure.
*/
- (AdobePhotoAsset *)createAsset:(AdobePhotoAsset *)asset
inCollection:(AdobePhotoCollection *)collection
withDataPath:(NSURL *)path
withContentType:(NSString *)type
withRequestPriority:(NSOperationQueuePriority)priority
onError:(NSError **)errorPtr __deprecated_msg("Use createAsset:collection:dataPath:contentType:requestPriority:error");

- (AdobePhotoAsset *)createAsset:(AdobePhotoAsset *)asset
collection:(AdobePhotoCollection *)collection
dataPath:(NSURL *)path
contentType:(NSString *)type
requestPriority:(NSOperationQueuePriority)priority
error:(NSError **)errorPtr;

/**
* Create a child revision for the given asset asynchronously.
*
* @param asset                 The asset for which to create a child revision.
* @param metadata              The full payload table for the new child revision.
* @param priority              The priority of the HTTP request.
* @param queue                 If not nil queue determines the operation queue handler gets executed on.
* @param completionBlock       Called when the call has finished, failed or if it has been cancelled.
*
* @returns                     An AdobeNetworkHTTPRequest object that can be used to track progress, adjust the  priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)createAssetChildRevision:(AdobePhotoAsset *)asset
withMetadata:(NSDictionary *)metadata
withRequestPriority:(NSOperationQueuePriority)priority
withHandlerQueue:(NSOperationQueue *)queue
onCompletion:(AdobePhotoAssetRequestCompletionHandler)completionBlock __deprecated_msg("Use createAssetChildRevision:metadata:requestPriority:handlerQueue:completionBlock");

- (AdobeNetworkHTTPRequest *)createAssetChildRevision:(AdobePhotoAsset *)asset
metadata:(NSDictionary *)metadata
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionBlock:(AdobePhotoAssetRequestCompletionHandler)completionBlock;

/**
* Create a child revision for the given asset synchronously.
*
* @param asset       The asset.
* @param metadata    The metadata for the new child revision.
* @param priority    The priority of the HTTP request.
* @param errorPtr    An optional pointer to an NSError object that will be set in case of an error.
*
* @returns           The asset deleted on success or nil on failure.
*/
- (AdobePhotoAsset *)createAssetChildRevision:(AdobePhotoAsset *)asset
withMetadata:(NSDictionary *)metadata
withRequestPriority:(NSOperationQueuePriority)priority
onError:(NSError **)errorPtr __deprecated_msg("Use createAssetChildRevision:metadata:requestPriority:error");

- (AdobePhotoAsset *)createAssetChildRevision:(AdobePhotoAsset *)asset
metadata:(NSDictionary *)metadata
requestPriority:(NSOperationQueuePriority)priority
error:(NSError **)errorPtr;

/**
* Create a child revision by updating a single payload entry (eg "develop") for the given asset asynchronously.
*
* @param asset                 The asset for which to create a child revision.
* @param newObject             The new object for the payload entry.
* @param key                   The name of the payload entry to update (eg "develop").
* @param priority              The priority of the HTTP request.
* @param queue                 If not nil queue determines the operation queue handler gets executed on.
* @param completionBlock       Called when the call has finished, failed or if it has been cancelled.
*
* @returns                     An AdobeNetworkHTTPRequest object that can be used to track progress, adjust the  priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)createAssetChildRevision:(AdobePhotoAsset *)asset
withObject:(NSObject *)newObject
forKey:(NSString *)key
withRequestPriority:(NSOperationQueuePriority)priority
withHandlerQueue:(NSOperationQueue *)queue
onCompletion:(AdobePhotoAssetRequestCompletionHandler)completionBlock __deprecated_msg("Use createAssetChildRevision:object:key:requestPriority:handlerQueue:completionBlock");

- (AdobeNetworkHTTPRequest *)createAssetChildRevision:(AdobePhotoAsset *)asset
object:(NSObject *)newObject
key:(NSString *)key
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionBlock:(AdobePhotoAssetRequestCompletionHandler)completionBlock;

/**
* Create a child revision by updating a single payload entry (eg "develop") for the given asset synchronously.
*
* @param asset       The asset.
* @param newObject   The new object for the payload entry.
* @param key         The name of the payload entry to update (eg "develop").
* @param priority    The priority of the HTTP request.
* @param errorPtr    An optional pointer to an NSError object that will be set in case of an error.
*
* @returns           The asset deleted on success or nil on failure.
*/
- (AdobePhotoAsset *)createAssetChildRevision:(AdobePhotoAsset *)asset
withObject:(NSObject *)newObject
forKey:(NSString *)key
withRequestPriority:(NSOperationQueuePriority)priority
onError:(NSError **)errorPtr __deprecated_msg("Use createAssetChildRevision:object:key:requestPriority:error");

- (AdobePhotoAsset *)createAssetChildRevision:(AdobePhotoAsset *)asset
object:(NSObject *)newObject
key:(NSString *)key
requestPriority:(NSOperationQueuePriority)priority
error:(NSError **)errorPtr;

/**
* Delete an asset asynchronously.
*
* @param asset             The asset.
* @param priority          The priority of the HTTP request.
* @param queue             If not nil queue determines the operation queue handler gets executed on.
* @param completionBlock   Called when the call has finished, failed or if it has been cancelled.
*
* @returns                 An AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)deleteAsset:(AdobePhotoAsset *)asset
withRequestPriority:(NSOperationQueuePriority)priority
withHandlerQueue:(NSOperationQueue *)queue
onCompletion:(AdobePhotoAssetRequestCompletionHandler)completionBlock __deprecated_msg("Use deleteAsset:requestPriority:handlerQueue:completionBlock");

- (AdobeNetworkHTTPRequest *)deleteAsset:(AdobePhotoAsset *)asset
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionBlock:(AdobePhotoAssetRequestCompletionHandler)completionBlock;

/**
* Delete an asset synchronously.
*
* @param asset    The asset.
* @param priority The priority of the HTTP request.
* @param errorPtr An optional pointer to an NSError object that will be set in case of an error.
*
* @returns        The asset deleted on success or nil on failure.
*/
- (AdobePhotoAsset *)deleteAsset:(AdobePhotoAsset *)asset
withRequestPriority:(NSOperationQueuePriority)priority
onError:(NSError **)errorPtr __deprecated_msg("Use deleteAsset:requestPriority:error");

- (AdobePhotoAsset *)deleteAsset:(AdobePhotoAsset *)asset
requestPriority:(NSOperationQueuePriority)priority
error:(NSError **)errorPtr;

/**
* Upload the master file asynchronously.
*
* @param asset             The asset.
* @param dataPath          The file path.
* @param generate          Generate renditions for this master file.
* @param priority          The priority of the HTTP request.
* @param queue             If not nil queue determines the operation queue handler gets executed on.
* @param completionBlock   Called when the call has finished, failed or if it has been cancelled.
*
* @returns                 An AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)uploadMasterDataForAsset:(AdobePhotoAsset *)asset
fromDataPath:(NSURL *)dataPath
autoGenerateRenditions:(BOOL)generate
withRequestPriority:(NSOperationQueuePriority)priority
withHandlerQueue:(NSOperationQueue *)queue
onCompletion:(AdobePhotoAssetRequestCompletionHandler)completionBlock __deprecated_msg("Use uploadMasterDataForAsset:dataPath:autoGenerateRenditions:requestPriority:handlerQueue:completionBlock");

- (AdobeNetworkHTTPRequest *)uploadMasterDataForAsset:(AdobePhotoAsset *)asset
dataPath:(NSURL *)dataPath
autoGenerateRenditions:(BOOL)generate
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionBlock:(AdobePhotoAssetRequestCompletionHandler)completionBlock;

/**
* Upload the master file synchronously.
*
* @param asset    The asset.
* @param dataPath The file path.
* @param generate Generate renditions for this master file.
* @param priority The priority of the HTTP request.
* @param errorPtr An optional pointer to an NSError object that will be set in case of an error.
*
* @returns         The updated asset on success or nil on failure.
*/
- (AdobePhotoAsset *)uploadMasterDataForAsset:(AdobePhotoAsset *)asset
fromDataPath:(NSURL *)dataPath
autoGenerateRenditions:(BOOL)generate
withRequestPriority:(NSOperationQueuePriority)priority
onError:(NSError **)errorPtr __deprecated_msg("Use uploadMasterDataForAsset:dataPath:autoGenerateREnditions:requestPriority:error");

- (AdobePhotoAsset *)uploadMasterDataForAsset:(AdobePhotoAsset *)asset
dataPath:(NSURL *)dataPath
autoGenerateRenditions:(BOOL)generate
requestPriority:(NSOperationQueuePriority)priority
error:(NSError **)errorPtr;

/**
* Download source data asynchronously.
*
* @param asset                 The asset.
* @param sourceType            The type of source data (master or proxy) to download.
* @param priority              The priority of the HTTP request.
* @param queue                 If not nil queue determines the operation queue handler gets executed on.
* @param completionBlock       Called when the call has finished, failed or if it has been cancelled.
*
* @returns                     An AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)downloadSourceDataForAsset:(AdobePhotoAsset *)asset
withSourceType:(AdobePhotoSource)sourceType
withRequestPriority:(NSOperationQueuePriority)priority
withHandlerQueue:(NSOperationQueue *)queue
onCompletion:(AdobePhotoDataRequestCompletionHandler)completionBlock __deprecated_msg("Use downloadMasterDataForAsset:sourceType:requestPriority:handlerQueue:completionBlock");

- (AdobeNetworkHTTPRequest *)downloadSourceDataForAsset:(AdobePhotoAsset *)asset
sourceType:(AdobePhotoSource)sourceType
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionBlock:(AdobePhotoDataRequestCompletionHandler)completionBlock;

/**
* Download source data synchronously.
*
* @param asset       The asset.
* @param sourceType  The type of source data (master or proxy) to download.
* @param priority    The priority of the HTTP request.
* @param errorPtr An optional pointer to an NSError object that will be set in case of an error.
*
* @returns           An AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (NSData *)downloadSourceDataForAsset:(AdobePhotoAsset *)asset
withSourceType:(AdobePhotoSource)sourceType
withRequestPriority:(NSOperationQueuePriority)priority
onError:(NSError **)errorPtr __deprecated_msg("Use downloadMasterDataForAsset:sourceType:requestPriority:error");

- (NSData *)downloadSourceDataForAsset:(AdobePhotoAsset *)asset
sourceType:(AdobePhotoSource)sourceType
requestPriority:(NSOperationQueuePriority)priority
error:(NSError **)errorPtr;

/**
* Download source data to the specified location asynchronously.
*
* @param asset             The asset.
* @param sourceType        The type of source data (master or proxy) to download.
* @param filePath          File system path where the downloaded photo asset should be stored.
* @param priority          Priority of the download request.
* @param queue             The operation queue used to execute @c completionHandler.
* @param completionBlock   Block to execute when the download task has been completed.
*
* @return                  An AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)downloadSourceDataForAsset:(AdobePhotoAsset *)asset
withSourceType:(AdobePhotoSource)sourceType
toFile:(NSString *)filePath
withRequestPriority:(NSOperationQueuePriority)priority
withHandlerQueue:(NSOperationQueue *)queue
onCompletion:(AdobePhotoDataRequestToFileCompletionHandler)completionBlock __deprecated_msg("Use downloadSourceDataForAsset:sourceType:filePath:requestPriority:handlerQueue:completionBlock");

- (AdobeNetworkHTTPRequest *)downloadSourceDataForAsset:(AdobePhotoAsset *)asset
sourceType:(AdobePhotoSource)sourceType
filePath:(NSString *)filePath
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionBlock:(AdobePhotoDataRequestToFileCompletionHandler)completionBlock;

/**
* Download source data to the specified location synchronously.
*
* @param asset       The asset.
* @param sourceType  The type of source data (master or proxy) to download.
* @param filePath    File system path where the downloaded photo asset should be stored.
* @param priority    The priority of the HTTP request.
* @param errorPtr    An optional pointer to an NSError object that will be set in case of an error.
*
* @returns           An AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (void)downloadSourceDataForAsset:(AdobePhotoAsset *)asset
withSourceType:(AdobePhotoSource)sourceType
toFile:(NSString *)filePath
withRequestPriority:(NSOperationQueuePriority)priority
onError:(NSError **)errorPtr __deprecated_msg("Use downloadSourceDataForAsset:filePath:requestPriority:error");

- (void)downloadSourceDataForAsset:(AdobePhotoAsset *)asset
sourceType:(AdobePhotoSource)sourceType
filePath:(NSString *)filePath
requestPriority:(NSOperationQueuePriority)priority
error:(NSError **)errorPtr;

/**
* Upload a file rendition asynchronously.
*
* @param rendition         The rendition.
* @param asset             The asset the rendition is for.
* @param priority          The priority of the HTTP request.
* @param queue             If not nil queue determines the operation queue handler gets executed on.
* @param completionBlock   Called when the call has finished, failed or if it has been cancelled.
*
* @returns                 An AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/

- (AdobeNetworkHTTPRequest *)uploadRendition:(AdobePhotoAssetRendition *)rendition
forAsset:(AdobePhotoAsset *)asset
withRequestPriority:(NSOperationQueuePriority)priority
withHandlerQueue:(NSOperationQueue *)queue
onCompletion:(AdobePhotoAssetRequestCompletionHandler)completionBlock __deprecated_msg("Use uploadRendition:asset:requestPriority:handlerQueue:completionBlock");

- (AdobeNetworkHTTPRequest *)uploadRendition:(AdobePhotoAssetRendition *)rendition
asset:(AdobePhotoAsset *)asset
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionBlock:(AdobePhotoAssetRequestCompletionHandler)completionBlock;

/**
* Upload a file rendition synchronously.
*
* @param rendition       The rendition.
* @param asset           The asset the rendition is for.
* @param priority        The priority of the HTTP request.
* @param errorPtr        An optional pointer to an NSError object that will be set in case of an error.
*
* @returns               The updated asset on success or nil on failure.
*/

- (AdobePhotoAsset *)uploadRendition:(AdobePhotoAssetRendition *)rendition
forAsset:(AdobePhotoAsset *)asset
withRequestPriority:(NSOperationQueuePriority)priority
onError:(NSError **)errorPtr __deprecated_msg("Use uploadRendition:asset:requestPriority:error");

- (AdobePhotoAsset *)uploadRendition:(AdobePhotoAssetRendition *)rendition
asset:(AdobePhotoAsset *)asset
requestPriority:(NSOperationQueuePriority)priority
error:(NSError **)errorPtr;

/**
* Download an asset rendition asynchronously.
*
* @param rendition         The asset rendition uuid.
* @param asset             The asset.
* @param priority          The priority of the HTTP request.
* @param queue             If not nil queue determines the operation queue handler gets executed on.
* @param completionBlock   Called when the call has finished, failed or if it has been cancelled.
*
* @returns                 An AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)downloadRendition:(AdobePhotoAssetRendition *)rendition
fromAsset:(AdobePhotoAsset *)asset
withRequestPriority:(NSOperationQueuePriority)priority
withHandlerQueue:(NSOperationQueue *)queue
onCompletion:(AdobePhotoDataRequestCompletionHandler)completionBlock __deprecated_msg("Use downloadRendition:asset:requestPriority:handlerQueue:completionBlock");

- (AdobeNetworkHTTPRequest *)downloadRendition:(AdobePhotoAssetRendition *)rendition
asset:(AdobePhotoAsset *)asset
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionBlock:(AdobePhotoDataRequestCompletionHandler)completionBlock;

/**
* Download an asset rendition synchronously.
*
* @param rendition The asset rendition uuid.
* @param asset     The asset.
* @param priority  The priority of the HTTP request.
* @param errorPtr  An optional pointer to an NSError object that will be set in case of an error.
*
* @returns         The data for a rendition on success or nil on failure.
*/
- (NSData *)downloadRendition:(AdobePhotoAssetRendition *)rendition
fromAsset:(AdobePhotoAsset *)asset
withRequestPriority:(NSOperationQueuePriority)priority
onError:(NSError **)errorPtr __deprecated_msg("Use downloadRendition:asset:requestPriority:error");

- (NSData *)downloadRendition:(AdobePhotoAssetRendition *)rendition
asset:(AdobePhotoAsset *)asset
requestPriority:(NSOperationQueuePriority)priority
error:(NSError **)errorPtr;

/**
* Generate the file renditions asynchronously.
*
* @param asset             The asset.
* @param types             The type of renditions to generate.
* @param priority          The priority of the HTTP request.
* @param queue             If not nil queue determines the operation queue handler gets executed on.
* @param completionBlock   Called when the call has finished, failed or if it has been cancelled.
*
* @returns                 An AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)generateRenditionForAsset:(AdobePhotoAsset *)asset
withRenditionTypes:(AdobePhotoAssetRenditionTypes *)types
withRequestPriority:(NSOperationQueuePriority)priority
withHandlerQueue:(NSOperationQueue *)queue
onCompletion:(AdobePhotoAssetRequestCompletionHandler)completionBlock __deprecated_msg("Use generateRenditionForAsset:renditionTypes:requestPriority:handlerQueue:completionBlock");

- (AdobeNetworkHTTPRequest *)generateRenditionForAsset:(AdobePhotoAsset *)asset
renditionTypes:(AdobePhotoAssetRenditionTypes *)types
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionBlock:(AdobePhotoAssetRequestCompletionHandler)completionBlock;

/**
* Generate the file renditions synchronously.
*
* @param asset           The asset.
* @param types           The type of renditions to generate.
* @param priority        The priority of the HTTP request.
* @param errorPtr        An optional pointer to an NSError object that will be set in case of an error.
*
* @returns               The updated asset on success or nil on failure.
*/

- (AdobePhotoAsset *)generateRenditionForAsset:(AdobePhotoAsset *)asset
withRenditionTypes:(AdobePhotoAssetRenditionTypes *)renditionTypes
withRequestPriority:(NSOperationQueuePriority)priority
onError:(NSError **)errorPtr __deprecated_msg("Use generateRenditionForAsset:renditionTypes:requestPriority:error");

- (AdobePhotoAsset *)generateRenditionForAsset:(AdobePhotoAsset *)asset
renditionTypes:(AdobePhotoAssetRenditionTypes *)renditionTypes
requestPriority:(NSOperationQueuePriority)priority
error:(NSError **)errorPtr;

/**
* Get an asset asynchronously.
*
* @param uuid              The asset uuid.
* @param catalog           The catalog.
* @param priority          The priority of the HTTP request.
* @param queue             If not nil queue determines the operation queue handler gets executed on.
* @param completionBlock   Called when the call has finished, failed or if it has been cancelled.
*
* @returns                 An AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)getAssetWithUUID:(NSString *)uuid
fromCatalog:(AdobePhotoCatalog *)catalog
withRequestPriority:(NSOperationQueuePriority)priority
withHandlerQueue:(NSOperationQueue *)queue
onCompletion:(AdobePhotoAssetRequestCompletionHandler)completionBlock __deprecated_msg("Use assetWithUUID:catalog:requestPriority:handlerQueue:completionBlock");

- (AdobeNetworkHTTPRequest *)assetWithUUID:(NSString *)uuid
catalog:(AdobePhotoCatalog *)catalog
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionBlock:(AdobePhotoAssetRequestCompletionHandler)completionBlock;

/**
* Get an asset synchronously.
*
* @param uuid     The asset uuid.
* @param catalog  The catalog.
* @param priority The priority of the HTTP request.
* @param errorPtr An optional pointer to an NSError object that will be set in case of an error.
*
* @returns        The AdobePhotoAsset on success or nil on failure.
*/
- (AdobePhotoAsset *)getAssetWithUUID:(NSString *)uuid
fromCatalog:(AdobePhotoCatalog *)catalog
withRequestPriority:(NSOperationQueuePriority)priority
onError:(NSError **)errorPtr __deprecated_msg("Use assetWithUUID:catalog:requestPriority:error");

- (AdobePhotoAsset *)assetWithUUID:(NSString *)uuid
catalog:(AdobePhotoCatalog *)catalog
requestPriority:(NSOperationQueuePriority)priority
error:(NSError **)errorPtr;

/**
* Get an asset revision asynchronously.
*
* @param uuid              The asset uuid.
* @param catalog           The catalog.
* @param revision          The asset revision.
* @param priority          The priority of the HTTP request.
* @param queue             If not nil queue determines the operation queue handler gets executed on.
* @param completionBlock   Called when the call has finished, failed or if it has been cancelled.
*
* @returns                 An AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)getAssetWithUUID:(NSString *)uuid
fromCatalog:(AdobePhotoCatalog *)catalog
withRevision:(AdobePhotoAssetRevision *)revision
withRequestPriority:(NSOperationQueuePriority)priority
withHandlerQueue:(NSOperationQueue *)queue
onCompletion:(AdobePhotoAssetRequestCompletionHandler)completionBlock __deprecated_msg("Use assetWithUUID:catalog:revision:requestPriority:handlerQueue:completionBlock");

- (AdobeNetworkHTTPRequest *)assetWithUUID:(NSString *)uuid
catalog:(AdobePhotoCatalog *)catalog
revision:(AdobePhotoAssetRevision *)revision
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionBlock:(AdobePhotoAssetRequestCompletionHandler)completionBlock;

/**
* Get an asset revision synchronously.
*
* @param uuid     The asset uuid.
* @param catalog  The catalog.
* @param revision The asset revision.
* @param priority The priority of the HTTP request.
* @param errorPtr An optional pointer to an NSError object that will be set in case of an error.
*
* @returns        The AdobePhotoAsset on success or nil on failure.
*/
- (AdobePhotoAsset *)getAssetWithUUID:(NSString *)uuid
fromCatalog:(AdobePhotoCatalog *)catalog
withRevision:(AdobePhotoAssetRevision *)revision
withRequestPriority:(NSOperationQueuePriority)priority
onError:(NSError **)errorPtr __deprecated_msg("Use assetWithUUID:catalog:revision:requestPriority:error");

- (AdobePhotoAsset *)assetWithUUID:(NSString *)uuid
catalog:(AdobePhotoCatalog *)catalog
revision:(AdobePhotoAssetRevision *)revision
requestPriority:(NSOperationQueuePriority)priority
error:(NSError **)errorPtr;

/**
* Get an asset asynchronously.
*
* @param asset             The asset.
* @param priority          The priority of the HTTP request.
* @param queue             If not nil queue determines the operation queue handler gets executed on.
* @param completionBlock   Called when the call has finished, failed or if it has been cancelled.
*
* @returns                 An AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)getAsset:(AdobePhotoAsset *)asset
withRequestPriority:(NSOperationQueuePriority)priority
withHandlerQueue:(NSOperationQueue *)queue
onCompletion:(AdobePhotoAssetRequestCompletionHandler)completionBlock __deprecated_msg("Use asset:requestPriority:handlerQueue:completionBlock");

- (AdobeNetworkHTTPRequest *)asset:(AdobePhotoAsset *)asset
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionBlock:(AdobePhotoAssetRequestCompletionHandler)completionBlock;

/**
* Get an asset synchronously.
*
* @param asset    The asset.
* @param priority The priority of the HTTP request.
* @param errorPtr An optional pointer to an NSError object that will be set in case of an error.
*
* @returns        The AdobePhotoAsset on success or nil on failure.
*/
- (AdobePhotoAsset *)getAsset:(AdobePhotoAsset *)asset
withRequestPriority:(NSOperationQueuePriority)priority
onError:(NSError **)errorPtr __deprecated_msg("Use asset:requestPriority:error");

- (AdobePhotoAsset *)asset:(AdobePhotoAsset *)asset
requestPriority:(NSOperationQueuePriority)priority
error:(NSError **)errorPtr;

/**
* Get an asset revision asynchronously.
*
* @param asset             The asset.
* @param revision          The asset revision.
* @param priority          The priority of the HTTP request.
* @param queue             If not nil queue determines the operation queue handler gets executed on.
* @param completionBlock   Called when the call has finished, failed or if it has been cancelled.
*
* @returns                 An AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)getAsset:(AdobePhotoAsset *)asset
withRevision:(AdobePhotoAssetRevision *)revision
withRequestPriority:(NSOperationQueuePriority)priority
withHandlerQueue:(NSOperationQueue *)queue
onCompletion:(AdobePhotoAssetRequestCompletionHandler)completionBlock __deprecated_msg("Use asset:revision:requestPriority:handlerQueue:completionBlock");

- (AdobeNetworkHTTPRequest *)asset:(AdobePhotoAsset *)asset
revision:(AdobePhotoAssetRevision *)revision
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionBlock:(AdobePhotoAssetRequestCompletionHandler)completionBlock;

/**
* Get an asset revision synchronously.
*
* @param asset    The asset.
* @param revision The asset revision.
* @param priority The priority of the HTTP request.
* @param errorPtr An optional pointer to an NSError object that will be set in case of an error.
*
* @returns        The an AdobePhotoAsset on success or nil on failure.
*/
- (AdobePhotoAsset *)getAsset:(AdobePhotoAsset *)asset
withRevision:(AdobePhotoAssetRevision *)revision
withRequestPriority:(NSOperationQueuePriority)priority
onError:(NSError **)errorPtr __deprecated_msg("Use asset:revision:requestPriority:error");

- (AdobePhotoAsset *)asset:(AdobePhotoAsset *)asset
revision:(AdobePhotoAssetRevision *)revision
requestPriority:(NSOperationQueuePriority)priority
error:(NSError **)errorPtr;

///@}

#pragma mark Accounting Methods
/** @name Accounting Methods */
///@{

/**
* Get the account status asynchronously.
*
* @param accountID             The account id.
* @param priority              The priority of the HTTP request.
* @param queue                 If not nil queue determines the operation queue handler gets executed on.
* @param completionBlock       Called when the call has finished, failed or if it has been cancelled.
*
* @returns                     An AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)getAccountStatusForID:(NSString *)accountID
withPriority:(NSOperationQueuePriority)priority
withHandlerQueue:(NSOperationQueue *)queue
onCompletion:(void (^)(AdobePhotoAccountStatus status, NSError *err))completionBlock __deprecated_msg("Use accountStatusForID:requestPriority:handlerQueue:completionBlock");

- (AdobeNetworkHTTPRequest *)accountStatusForID:(NSString *)accountID
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionBlock:(void (^)(AdobePhotoAccountStatus status, NSError *err))completionBlock;

/**
* Get the account status synchronously.
*
* @param accountID The account id.
* @param priority  The priority of the HTTP request.
* @param priority  The priority of the HTTP request.
* @param errorPtr  An optional pointer to an NSError object that will be set in case of an error.
*
* @returns         The an AdobePhotoAsset on success or nil on failure.
*/
- (AdobePhotoAccountStatus)getAccountStatusForID:(NSString *)accountID
withPriority:(NSOperationQueuePriority)priority
onError:(NSError **)errorPtr __deprecated_msg("Use accountStatusForID:requestPriority:error");

- (AdobePhotoAccountStatus)accountStatusForID:(NSString *)accountID
requestPriority:(NSOperationQueuePriority)priority
error:(NSError **)errorPtr;

/**
* Get the account subscriptions.
*
* @param accountID         The account id.
* @param priority          The priority of the HTTP request.
* @param queue             If not nil queue determines the operation queue handler gets executed on.
* @param completionBlock   Called when the call has finished, failed or if it has been cancelled.
*
* @returns                 An AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)getAccountSubscriptionsForID:(NSString *)accountID
withPriority:(NSOperationQueuePriority)priority
withHandlerQueue:(NSOperationQueue *)queue
onCompletion:(void (^)(NSString *productID, NSDate *purchase, NSDate *expiration, NSError *err))completionBlock __deprecated_msg("Use accountSubscriptionsForID:requestPriority:handlerQueue:completionBlock");

- (AdobeNetworkHTTPRequest *)accountSubscriptionsForID:(NSString *)accountID
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionBlock:(void (^)(NSString *productID, NSDate *purchase, NSDate *expiration, NSError *err))completionBlock;

/**
* Get the limits for the logged in user, asynchronously.
*
* @param accountID         The account id.
* @param priority          The priority of the HTTP request.
* @param queue             If not nil queue determines the operation queue handler gets executed on.
* @param completionBlock   Called when the call has finished, failed or if it has been cancelled.
*
* @returns                 An AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)getAccountLimitsForID:(NSString *)accountID
withPriority:(NSOperationQueuePriority)priority
withHandlerQueue:(NSOperationQueue *)queue
onCompletion:(void (^)(NSUInteger maxCatalogs, NSUInteger maxUsersPerCatalog, NSUInteger uploadsPerMonth, BOOL canUploadRawData, NSError *err))completionBlock __deprecated_msg("Use accountLimitsForID:priority:handlerQueue:completionBlock");

- (AdobeNetworkHTTPRequest *)accountLimitsForID:(NSString *)accountID
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionBlock:(void (^)(NSUInteger uploadsPerMonth, BOOL canUploadRawData, NSError *err))completionBlock;

///@}

@end

#endif /* ifndef AdobePhotoSessionHeader */
