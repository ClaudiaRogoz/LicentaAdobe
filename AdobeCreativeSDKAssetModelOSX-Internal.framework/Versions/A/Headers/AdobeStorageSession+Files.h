/*************************************************************************
*
* ADOBE CONFIDENTIAL
* ___________________
*
*  Copyright 2013 Adobe Systems Incorporated
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

#ifndef AdobeStorageSessionFilesHeader
#define AdobeStorageSessionFilesHeader

#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeStorageResourceCollection.h>
#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeStorageSession.h>

@class AdobeNetworkHTTPRequest;

/**
* Adds file-related APIs to AdobeStorageSession.
*/
@interface AdobeStorageSession (Files)

#pragma mark Directory Methods
/** @name Directory Methods */
///@{

/**
*  DEPRECATED: Get the data for the specified directory, including the children list, asynchronously.
*
*  @param dir      The directory collection.
*  @param mode     How the directory collection object should be updated with the results of the request.
*  @param priority The priority of the HTTP request.
*  @param queue    If not nil queue determines the operation queue handler gets executed on.
*  @param handler  Called when the call has finished, failed or if it has been cancelled.
*
*  @return         A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*
*  @note On success dir will get updated and handed to the handler.
*/
- (AdobeNetworkHTTPRequest *)getDirectory:(AdobeStorageResourceCollection *)dir
pagingMode:(AdobeStoragePagingMode)mode
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionHandler:(AdobeStorageCollectionRequestCompletionHandler)handler __deprecated_msg("Use directoryData:pagingMode:requestPriority:handlerQueue:completionBlock:");

/**
*  Get the data for the specified directory, including the children list, asynchronously.
*
*  @param dir               The directory collection.
*  @param mode              How the directory collection object should be updated with the results of the request.
*  @param priority          The priority of the HTTP request.
*  @param queue             If not nil it determines the queue that the completion block gets executed on.
*  @param completionBlock   Called when the call has finished, failed or if it has been cancelled.
*
*  @return         A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*
*  @note On success dir will get updated and handed to the completion block.
*/
- (AdobeNetworkHTTPRequest *)directoryData:(AdobeStorageResourceCollection *)dir
pagingMode:(AdobeStoragePagingMode)mode
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionBlock:(AdobeStorageCollectionRequestCompletionHandler)completionBlock;

/**
*  DEPRECATED: Get the data for the specified directory, including the children list, synchronously.
*
*  @param dir      The directory collection.
*  @param priority The priority of the HTTP request.
*  @param errorPtr An optional pointer to an NSError object that will be set in case of an error.
*
*  @return         The updated directory on success or nil on failure.
*
*  @note On success dir will get updated and returned.
*/
- (AdobeStorageResourceCollection *)getDirectory:(AdobeStorageResourceCollection *)dir
pagingMode:(AdobeStoragePagingMode)mode
requestPriority:(NSOperationQueuePriority)priority
withError:(NSError **)errorPtr __deprecated_msg("Use directoryData:pagingMode:requestPriority:error:");

/**
*  Get the data for the specified directory, including the children list, synchronously.
*
*  @param dir      The directory collection.
*  @param priority The priority of the HTTP request.
*  @param errorPtr An optional pointer to an NSError object that will be set in case of an error.
*
*  @return         The updated directory on success or nil on failure.
*
*  @note On success dir will get updated and returned.
*/
- (AdobeStorageResourceCollection *)directoryData:(AdobeStorageResourceCollection *)dir
pagingMode:(AdobeStoragePagingMode)mode
requestPriority:(NSOperationQueuePriority)priority
error:(NSError **)errorPtr;

/**
*  DEPRECATED: Create a new directory asynchronously.
*
*  @param dir      The directory collection.
*  @param priority The priority of the HTTP request.
*  @param queue    If not nil queue determines the operation queue handler gets executed on.
*  @param handler  Called when the call has finished, failed or if it has been cancelled.
*
*  @return         A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)createDirectory:(AdobeStorageResourceCollection *)dir
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionHandler:(AdobeStorageCollectionRequestCompletionHandler)handler __deprecated_msg("createDirectory:requestPriority:handlerQueue:completionBlock:");

/**
*  Create a new directory asynchronously.
*
*  @param dir               The directory collection.
*  @param priority          The priority of the HTTP request.
*  @param queue             If not nil it determines the queue that the completion block gets executed on.
*  @param completionBlock   Called when the call has finished, failed or if it has been cancelled.
*
*  @return         A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)createDirectory:(AdobeStorageResourceCollection *)dir
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionBlock:(AdobeStorageCollectionRequestCompletionHandler)completionBlock;

/**
* Create a new directory synchronously.
*
*  @param dir      The directory collection.
*  @param priority The priority of the HTTP request.
*  @param errorPtr An optional pointer to an NSError object that will be set in case of an error.
*
*  @return         The created directory on success or nil on failure.
*/
- (AdobeStorageResourceCollection *)createDirectory:(AdobeStorageResourceCollection *)dir
requestPriority:(NSOperationQueuePriority)priority
withError:(NSError **)errorPtr __deprecated_msg("createDirectory:requestPriority:error:");

/**
*  Create a new directory synchronously.
*
*  @param dir      The directory collection.
*  @param priority The priority of the HTTP request.
*  @param errorPtr An optional pointer to an NSError object that will be set in case of an error.
*
*  @return         The created directory on success or nil on failure.
*/
- (AdobeStorageResourceCollection *)createDirectory:(AdobeStorageResourceCollection *)dir
requestPriority:(NSOperationQueuePriority)priority
error:(NSError **)errorPtr;

/**
*  DEPRECATED: Archive the specified directory asynchronously. It does not permanently delete the directory from the cloud.
*      There is no API to expunge nor restore the directory from the archive as of this time.
*
*  @param dir       The directory collection.
*  @param ifExists  If YES then don't return an error in the event that the directory doesn't exist.
*  @param priority  The priority of the HTTP request.
*  @param queue     If not nil queue determines the operation queue handler gets executed on.
*  @param handler   Called when the call has finished, failed or if it has been cancelled.
*
*  @return         YES on success, NO on failure.
*/
- (AdobeNetworkHTTPRequest *)archiveDirectory:(AdobeStorageResourceCollection *)dir
ifExists:(BOOL)ifExists
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionHandler:(AdobeStorageCollectionRequestCompletionHandler)handler __deprecated_msg("archiveDirectory:requestPriority:handlerQueue:completionBlock:");

/**
*  Archive the specified directory asynchronously. It does not permanently delete the directory from the cloud.
*      There is no API to expunge nor restore the directory from the archive as of this time.
*
*  @param dir               The directory collection.
*  @param ifExists          If YES then don't return an error in the event that the directory doesn't exist.
*  @param priority          The priority of the HTTP request.
*  @param queue             If not nil it determines the queue that the completion block gets executed on.
*  @param completionBlock   Called when the call has finished, failed or if it has been cancelled.
*
*  @return         A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)archiveDirectory:(AdobeStorageResourceCollection *)dir
ifExists:(BOOL)ifExists
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionBlock:(AdobeStorageCollectionRequestCompletionHandler)completionBlock;

/**
*  DEPRECATED: Archive the specified directory synchronously. It does not permanently delete the directory from the cloud.
*      There is no API to expunge nor restore the directory from the archive as of this time.
*
*  @param dir       The directory collection.
*  @param ifExists  If YES then don't return an error in the event that the directory doesn't exist.
*  @param priority  The priority of the HTTP request.
*  @param errorPtr  An optional pointer to an NSError object that will be set in case of an error.
*
*  @return         YES on success, NO on failure.
*/
- (BOOL)archiveDirectory:(AdobeStorageResourceCollection *)dir
ifExists:(BOOL)ifExists
requestPriority:(NSOperationQueuePriority)priority
withError:(NSError **)errorPtr __deprecated_msg("archiveDirectory:ifExists:requestPriority:error:");

/**
*  Archive the specified directory synchronously. It does not permanently delete the directory from the cloud.
*      There is no API to expunge nor restore the directory from the archive as of this time.
*
*  @param dir       The directory collection.
*  @param ifExists  If YES then don't return an error in the event that the directory doesn't exist.
*  @param priority  The priority of the HTTP request.
*  @param errorPtr  An optional pointer to an NSError object that will be set in case of an error.
*
*  @return         YES on success, NO on failure.
*/
- (BOOL)archiveDirectory:(AdobeStorageResourceCollection *)dir
ifExists:(BOOL)ifExists
requestPriority:(NSOperationQueuePriority)priority
error:(NSError **)errorPtr;

/**
*  Refresh a folder's metadata asynchronously.
*
*  @param resource         The resource describing the file to refresh. If the resource has its path property
*                  set then the file will be written directly to a file at that location, overriding
*                  it if it already exists.
*  @param priority         The priority of the HTTP reqeust.
*  @param queue            If not nil it determines the queue that the completion block gets executed on.
*  @param completionBlock  Called when the call has finished, failed or if it has been cancelled.
*
*  @return         An AdobeNetworkHTTPRequest object that can be used to track progress, adjust the priority
*                  of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)refreshFolder:(AdobeStorageResourceCollection *)resource
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionBlock:(AdobeStorageCollectionRequestCompletionHandler)completionBlock;
/**
*  Refresh a folder's metadata synchronously.
*
*  @param resource         The resource describing the file to refresh. If the resource has its path property
*                  set then the file will be written directly to a file at that location, overriding
*                  it if it already exists.
*  @param priority         The priority of the HTTP reqeust.
*  @param errorPtr     An optional pointer to an NSError object that will be set in case of an error.
*
*  @return The refreshed file on success or nil on failure.
*/
- (AdobeStorageResourceCollection *)refreshFolder:(AdobeStorageResourceCollection *)resource
requestPriority:(NSOperationQueuePriority)priority
error:(NSError **)errorPtr;
///@}

#pragma mark File Methods
/** @name File Methods */
///@{

/**
*  DEPRECATED: Upload a file to the server asynchronously, creating it if it doesn't already exist.
*
*  @param resource              The resource describing the file to upload. If the resource has its path
*                            property set then the file will be uploaded from the file at that path
*                            otherwise its data property will be used as the body of the request.
*                            For an existing file the resource should have its etag property set.
*  @param overrideRemoteChanges Determines the behavior when the resource on the server has been changed
*                            since the local resource was last up- or downloaded. If YES the upload
*                            will succeed, if NO the upload will fail with a AdobeStorageConflictingChanges error.
*  @param priority              The relative priority of the HTTP request.
*  @param queue                 If not nil queue determines the operation queue handler gets executed on.
*  @param handler               Called when the upload has finished, failed or if it has been cancelled.
*
*  @return                      A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
*                            priority of the request and to cancel it.
*
*  @note On success the properties resource param will get updated and handed to the handler.
*/
- (AdobeNetworkHTTPRequest *)updateFile:(AdobeStorageResourceItem *)resource
overrideRemoteChanges:(BOOL)overrideRemoteChanges
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionHandler:(AdobeStorageResourceRequestCompletionHandler)handler __deprecated_msg("Use updateFile:overrideRemoteChanges:requestPriority:handlerQueue:completionBlock:");

/**
*  Upload a file to the server asynchronously, creating it if it doesn't already exist.
*
*  @param resource              The resource describing the file to upload. If the resource has its path
*                            property set then the file will be uploaded from the file at that path
*                            otherwise its data property will be used as the body of the request.
*                              For an existing file the resource should have its etag property set.
*  @param overrideRemoteChanges Determines the behavior when the resource on the server has been changed
*                            since the local resource was last up- or downloaded. If YES the upload
*                            will succeed, if NO the upload will fail with a AdobeStorageConflictingChanges error.
*  @param priority              The relative priority of the HTTP request.
*  @param queue                 If not nil it determines the queue that the completion block gets executed on.
*  @param completionBlock       Called when the call has finished, failed or if it has been cancelled.
*
*  @return                      A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
*                            priority of the request and to cancel it.
*
*  @note On success the properties resource param will get updated and handed to the handler.
*/
- (AdobeNetworkHTTPRequest *)updateFile:(AdobeStorageResourceItem *)resource
overrideRemoteChanges:(BOOL)overrideRemoteChanges
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionBlock:(AdobeStorageResourceRequestCompletionHandler)completionBlock;


/**
*  DEPRECATED: Upload a file to the server synchronously, creating it if it doesn't already exist.
*
*  @param resource              The resource describing the file to upload. If the resource has its path
*                            property set then the file will be uploaded from the file at that path
*                            otherwise its data property will be used as the body of the request.
*                            For an existing file the resource should have its etag property set.
*  @param overrideRemoteChanges Determines the behavior when the resource on the server has been changed
*                            since the local resource was last up- or downloaded. If YES the upload
*                            will succeed, if NO the upload will fail with a AdobeStorageConflictingChanges error.
*  @param priority              The relative priority of the HTTP request.
*  @param errorPtr              An optional pointer to an NSError object that will be set in case of an
*                            error.
*
*  @return                      YES on success, NO on failure or cancellation.
*
*  @note On success the properties of the resource param will get updated.
*/
- (BOOL)       updateFile:(AdobeStorageResourceItem *)resource
overrideRemoteChanges:(BOOL)overrideRemoteChanges
requestPriority:(NSOperationQueuePriority)priority
withError:(NSError **)errorPtr __deprecated_msg("Use updateFile:overrideRemoteChanges:requestPriority:error:");

/**
*  Upload a file to the server synchronously, creating it if it doesn't already exist.
*
*  @param resource              The resource describing the file to upload. If the resource has its path
*                            property set then the file will be uploaded from the file at that path
*                            otherwise its data property will be used as the body of the request.
*                            For an existing file the resource should have its etag property set.
*  @param overrideRemoteChanges Determines the behavior when the resource on the server has been changed
*                            since the local resource was last up- or downloaded. If YES the upload
*                            will succeed, if NO the upload will fail with a AdobeStorageConflictingChanges error.
*  @param priority              The relative priority of the HTTP request.
*  @param errorPtr              An optional pointer to an NSError object that will be set in case of an error.
*
*  @return         The updated file on success or nil on failure.
*/
- (AdobeStorageResourceItem *)updateFile:(AdobeStorageResourceItem *)resource
overrideRemoteChanges:(BOOL)overrideRemoteChanges
requestPriority:(NSOperationQueuePriority)priority
error:(NSError **)errorPtr;

/**
*  DEPRECATED: Download a video metadata from the server asynchronously.
*
*  @param resource    The resource describing the file to download. If the resource has its path property
* set then the file will be written directly to a file at that location, overriding
* it if it already exists. If the resoruce has its version property set then the
* corresponding version of the file will get downloaded. Otherwise the head version
* of the file will get downloaded.
*  @param type        The content type of the rendition.
*  @param priority    The priority of the HTTP request.
*  @param queue       Optional parameter. If not nil queue determines the operation queue handler gets
* executed on.
*  @param handler     Gets called when the download has completed or failed.
*
*  @return            An AdobeNetworkHTTPRequest object that can be used to track progress, adjust the priority
* of the request and to cancel it.
*
*  @note that in the case where the latest version is requested, the resource has its etag set and the
* latest version of the file file on the server has the same etag the file will not get downloaded
* and no error will be returned.
*
*  @note On success the properties of the resource param will get updated and handed to the handler.
*/
- (AdobeNetworkHTTPRequest *)getVideoMetadata:(AdobeStorageResourceItem *)resource
type:(NSString *)type
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionHandler:(AdobeStorageDataRequestCompletionHandler)handler __deprecated_msg("Use videoMetadata:contentType:requestPriority:handlerQueue:completionBlock:");

/**
*  Get the video metadata from the server asynchronously.
*
*  @param resource              The resource describing the file to download. If the resource has its path property
* set then the file will be written directly to a file at that location, overriding
* it if it already exists. If the resoruce has its version property set then the
* corresponding version of the file will get downloaded. Otherwise the head version
* of the file will get downloaded.
*  @param type                  The content type of the rendition.
*  @param priority              The priority of the HTTP request.
*  @param queue                 If not nil it determines the queue that the completion block gets executed on.
*  @param completionBlock       Called when the call has finished, failed or if it has been cancelled.
*
*  @return            An AdobeNetworkHTTPRequest object that can be used to track progress, adjust the priority
* of the request and to cancel it.
*
*  @note that in the case where the latest version is requested, the resource has its etag set and the
* latest version of the file file on the server has the same etag the file will not get downloaded
* and no error will be returned.
*
*  @note On success the properties of the resource param will get updated and handed to the handler.
*/
- (AdobeNetworkHTTPRequest *)videoMetadata:(AdobeStorageResourceItem *)resource
contentType:(NSString *)type
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionBlock:(AdobeStorageDataRequestCompletionHandler)completionBlock;

/**
*  Get the video metadata from the server synchronously.
*
*  @param resource              The resource describing the file to upload. If the resource has its path
*                            property set then the file will be uploaded from the file at that path
*                            otherwise its data property will be used as the body of the request.
*                            For an existing file the resource should have its etag property set.
*  @param type                  The content type of the rendition.
*  @param priority              The priority of the HTTP request.
*  @param errorPtr              An optional pointer to an NSError object that will be set in case of an error.
*
*  @return The video metadata on success or nil on failure.
*/
- (NSData *)videoMetadata:(AdobeStorageResourceItem *)resource
contentType:(NSString *)type
requestPriority:(NSOperationQueuePriority)priority
error:(NSError **)errorPtr;

/**
*  DEPRECATED: Download a rendition from the server asynchronously.
*
*  @param resource    The resource describing the file to download. If the resource has its path property
* set then the file will be written directly to a file at that location, overriding
* it if it already exists. If the resoruce has its version property set then the
* corresponding version of the file will get downloaded. Otherwise the head version
* of the file will get downloaded.
*  @param pixels      The longest side (width or height) of the rendition.
*  @param type        The content type of the rendition.
*  @param page        The page number to pull a rendition. O or 1 is valid for a single page.
*  @param priority    The priority of the HTTP request.
*  @param queue       Optional parameter. If not nil queue determines the operation queue handler gets
* executed on.
*  @param handler     Gets called when the download has completed or failed.
*
*  @return            An AdobeNetworkHTTPRequest object that can be used to track progress, adjust the priority
* of the request and to cancel it.
*
*  @note that in the case where the latest version is requested, the resource has its etag set and the
* latest version of the file file on the server has the same etag the file will not get downloaded
* and no error will be returned.
*
*  @note On success the properties of the resource param will get updated and handed to the handler.
*/
- (AdobeNetworkHTTPRequest *)getRendition:(AdobeStorageResourceItem *)resource
longestSideInPixels:(NSUInteger)pixels
type:(NSString *)type
page:(NSUInteger)page
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionHandler:(AdobeStorageDataRequestCompletionHandler)handler __deprecated_msg("Use downloadFileRendition:longestSizeInPixels:contentType:page:requestPriority:handlerQueue:completionBlock:");

/**
*  Download a rendition from the server asynchronously.
*
*  @param resource              The resource describing the file to download. If the resource has its path property
* set then the file will be written directly to a file at that location, overriding
* it if it already exists. If the resoruce has its version property set then the
* corresponding version of the file will get downloaded. Otherwise the head version
* of the file will get downloaded.
*  @param pixels                The longest side (width or height) of the rendition.
*  @param type                  The content type of the rendition.
*  @param page                  The page number to pull a rendition. O or 1 is valid for a single page.
*  @param priority              The priority of the HTTP request.
*  @param queue                 If not nil it determines the queue that the completion block gets executed on.
*  @param completionBlock       Called when the call has finished, failed or if it has been cancelled.
*
*  @return            An AdobeNetworkHTTPRequest object that can be used to track progress, adjust the priority
* of the request and to cancel it.
*
*  @note that in the case where the latest version is requested, the resource has its etag set and the
* latest version of the file file on the server has the same etag the file will not get downloaded
* and no error will be returned.
*
*  @note On success the properties of the resource param will get updated and handed to the handler.
*/
- (AdobeNetworkHTTPRequest *)downloadFileRendition:(AdobeStorageResourceItem *)resource
longestSideInPixels:(NSUInteger)pixels
contentType:(NSString *)type
page:(NSUInteger)page
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionBlock:(AdobeStorageDataRequestCompletionHandler)completionBlock;

/**
*  DEPRECATED: Download a file from the server asynchronously.
*
*  @param resource    The resource describing the file to download. If the resource has its path property
*                  set then the file will be written directly to a file at that location, overriding
*                  it if it already exists. If the resoruce has its version property set then the
*                  corresponding version of the file will get downloaded. Otherwise the head version
*                  of the file will get downloaded.
*  @param priority    The priority of the HTTP request.
*  @param queue       Optional parameter. If not nil queue determines the operation queue handler gets
*                  executed on.
*  @param handler     Gets called when the download has completed or failed.
*
*  @return            A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the priority
*                  of the request and to cancel it.
*
*  @note that in the case where the latest version is requested, the resource has its etag set and the
* latest version of the file file on the server has the same etag the file will not get downloaded
* and no error will be returned.
*
*  @note On success the properties of the resource param will get updated and handed to the handler.
*/
- (AdobeNetworkHTTPRequest *)getFile:(AdobeStorageResourceItem *)resource
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionHandler:(AdobeStorageResourceRequestCompletionHandler)handler __deprecated_msg("Use downloadFileData:requestPriority:handlerQueue:completionBlock:");

/**
*  Get a file's data from the server asynchronously.
*
*  @param resource              The resource describing the file to download. If the resource has its path property
*                  set then the file will be written directly to a file at that location, overriding
*                  it if it already exists. If the resoruce has its version property set then the
*                  corresponding version of the file will get downloaded. Otherwise the head version
*                  of the file will get downloaded.
*  @param priority              The priority of the HTTP request.
*  @param queue                 If not nil it determines the queue that the completion block gets executed on.
*  @param completionBlock       Called when the call has finished, failed or if it has been cancelled.
*
*  @return            A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the priority
*                  of the request and to cancel it.
*
*  @note that in the case where the latest version is requested, the resource has its etag set and the
* latest version of the file file on the server has the same etag the file will not get downloaded
* and no error will be returned.
*
*  @note On success the properties of the resource param will get updated and handed to the handler.
*/
- (AdobeNetworkHTTPRequest *)downloadFileData:(AdobeStorageResourceItem *)resource
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionBlock:(AdobeStorageResourceRequestCompletionHandler)completionBlock;

/**
*  DEPRECATED: Get a file's data from the server synchronously.
*
*  @param resource    The resource describing the file to download. If the resource has its path property
*                  set then the file will be written directly to a file at that location, overriding
*                  it if it already exists. If the resoruce has its version property set then the
*                  corresponding version of the file will get downloaded. Otherwise the head version
*                  of the file will get downloaded.
*  @param priority    The priority of the HTTP request.
*  @param errorPtr    An optional pointer to an NSError object that will be set in case of an error.
*
*  @return            YES on success, NO on failure.
*
*  @note that in the case where the latest version is requested, the resource has its etag set and the
* latest version of the file file on the server has the same etag the file will not get downloaded
* and no error will be returned.
*
*  @note On success the properties of the resource param will get updated.
*/
- (BOOL)    getFile:(AdobeStorageResourceItem *)resource
requestPriority:(NSOperationQueuePriority)priority
withError:(NSError **)errorPtr __deprecated_msg("Use downloadFileData:requestPriority:error:");

/**
*  Get a file's data from the server synchronously.
*
*  @param resource    The resource describing the file to download. If the resource has its path property
*                  set then the file will be written directly to a file at that location, overriding
*                  it if it already exists. If the resoruce has its version property set then the
*                  corresponding version of the file will get downloaded. Otherwise the head version
*                  of the file will get downloaded.
*  @param priority    The priority of the HTTP request.
*  @param errorPtr    An optional pointer to an NSError object that will be set in case of an error.
*
*  @return The file data on success or nil on failure.
*
*  @note that in the case where the latest version is requested, the resource has its etag set and the
* latest version of the file file on the server has the same etag the file will not get downloaded
* and no error will be returned.
*/
- (AdobeStorageResourceItem *)downloadFileData:(AdobeStorageResourceItem *)resource
requestPriority:(NSOperationQueuePriority)priority
error:(NSError **)errorPtr;

/**
*  DEPRECATED: Refresh a file's metadata asynchronously.
*
*  @param resource The resource describing the file to refresh. If the resource has its path property
*                  set then the file will be written directly to a file at that location, overriding
*                  it if it already exists.
*  @param priority The priority of the HTTP reqeust.
*  @param queue    Optional parameter. If not nil queue determines the operation queue handler gets
*                  executed on.
*  @param handler  Gets called when the download has completed or failed.
*
*  @return         An AdobeNetworkHTTPRequest object that can be used to track progress, adjust the priority
*                  of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)refreshFile:(AdobeStorageResourceItem *)resource
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionHandler:(AdobeStorageResourceRequestCompletionHandler)handler __deprecated_msg("Use refreshFile:requestPriority:handlerQueue:completionBlock:");

/**
*  Refresh a file's metadata asynchronously.
*
*  @param resource         The resource describing the file to refresh. If the resource has its path property
*                  set then the file will be written directly to a file at that location, overriding
*                  it if it already exists.
*  @param priority         The priority of the HTTP reqeust.
*  @param queue            If not nil it determines the queue that the completion block gets executed on.
*  @param completionBlock  Called when the call has finished, failed or if it has been cancelled.
*
*  @return         An AdobeNetworkHTTPRequest object that can be used to track progress, adjust the priority
*                  of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)refreshFile:(AdobeStorageResourceItem *)resource
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionBlock:(AdobeStorageResourceRequestCompletionHandler)completionBlock;

/**
*  Refresh a file's metadata synchronously.
*
*  @param resource         The resource describing the file to refresh. If the resource has its path property
*                  set then the file will be written directly to a file at that location, overriding
*                  it if it already exists.
*  @param priority         The priority of the HTTP reqeust.
*  @param errorPtr     An optional pointer to an NSError object that will be set in case of an error.
*
*  @return The refreshed file on success or nil on failure.
*/
- (AdobeStorageResourceItem *)refreshFile:(AdobeStorageResourceItem *)resource
requestPriority:(NSOperationQueuePriority)priority
error:(NSError **)errorPtr;

/**
*  DEPRECATED: Get the header information of an file asynchronously.
*
*  @param resource    The resource describing the file to get the header info for.
*  @param includeVersion If YES then the X-Latest-Version header is used to set the version property of the returned resource.
*  @param priority    The priority of the HTTP request.
*  @param queue       Optional parameter. If not nil queue determines the operation queue handler gets
*                  executed on.
*  @param handler     Gets called when the request has completed or failed.
*
*
*  @return            A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the priority
*                  of the request and to cancel it.
*
*  @note On success the properties of the resource param will get updated and handed to the handler.
*/
- (AdobeNetworkHTTPRequest *)getHeaderInfoForFile:(AdobeStorageResourceItem *)resource
includeVersion:(BOOL)includeVersion
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionHandler:(AdobeStorageResourceRequestCompletionHandler)handler __deprecated_msg("Use fileHeaderMetadata:includeVersion:requestPriority:handlerQueue:completionBlock:");

/**
*  Get the header information of an file asynchronously.
*
*  @param resource         The resource describing the file to get the header info for.
*  @param includeVersion   If YES then the X-Latest-Version header is used to set the version property of the returned resource.
*  @param priority         The priority of the HTTP request.
*  @param queue            If not nil it determines the queue that the completion block gets executed on.
*  @param completionBlock  Called when the call has finished, failed or if it has been cancelled.
*
*
*  @return            A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the priority
*                  of the request and to cancel it.
*
*  @note On success the properties of the resource param will get updated and handed to the handler.
*/
- (AdobeNetworkHTTPRequest *)fileHeaderMetadata:(AdobeStorageResourceItem *)resource
includeVersion:(BOOL)includeVersion
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionBlock:(AdobeStorageResourceRequestCompletionHandler)completionBlock;

/**
*  DEPRECATED: Get the header information of an file synchronously.
*
*  @param resource     The resource describing the file to get the header info for.
*  @param includeVersion If YES then the X-Latest-Version header is used to set the version property of the returned resource.
*  @param priority     The priority of the HTTP request.
*  @param errorPtr     An optional pointer to an NSError object that will be set in case of an error.
*
*  @return             YES on success, NO on failure.
*
*  @note On success the properties of the resource param will get updated and handed to the handler.
*/
- (BOOL)getHeaderInfoForFile:(AdobeStorageResourceItem *)resource
includeVersion:(BOOL)includeVersion
requestPriority:(NSOperationQueuePriority)priority
withError:(NSError **)errorPtr __deprecated_msg("Use fileHeaderMetadata:includeVersion:requestPriority:error:");

/**
*  Get the header information of an file synchronously.
*
*  @param resource     The resource describing the file to get the header info for.
*  @param includeVersion If YES then the X-Latest-Version header is used to set the version property of the returned resource.
*  @param priority     The priority of the HTTP request.
*  @param errorPtr     An optional pointer to an NSError object that will be set in case of an error.
*
*  @return The file filled in with header data on success or nil on failure.
*
*  @note On success the properties of the resource param will get updated and handed to the handler.
*/
- (AdobeStorageResourceItem *)fileHeaderMetadata:(AdobeStorageResourceItem *)resource
includeVersion:(BOOL)includeVersion
requestPriority:(NSOperationQueuePriority)priority
error:(NSError **)errorPtr;

/**
*  DEPRECATED: Archive the specified file asynchronously. It does not permanently delete the file from the cloud.
*  There is no API to expunge nor restore the file from the archive as of this time.
*
*  @param resource    The resource describing the file to archive.
*  @param ifExists    If YES then don't return an error in the event that the file is missing.
*  @param priority    The priority of the HTTP request.
*  @param queue       Optional parameter. If not nil queue determines the operation queue handler gets executed on.
*  @param handler     Gets called when the deletion has completed or failed.
*
*  @return         A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the priority of
*               the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)archiveFile:(AdobeStorageResourceItem *)resource
ifExists:(BOOL)ifExists
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionHandler:(AdobeStorageResourceRequestCompletionHandler)handler __deprecated_msg("Use archiveFile:ifExists:requestPriority:handlerQueue:completionBlock:");

/**
*  Archive the specified file asynchronously. It does not permanently delete the file from the cloud.
*  There is no API to expunge nor restore the file from the archive as of this time.
*
*  @param resource         The resource describing the file to archive.
*  @param ifExists         If YES then don't return an error in the event that the file is missing.
*  @param priority         The priority of the HTTP request.
*  @param queue            If not nil it determines the queue that the completion block gets executed on.
*  @param completionBlock  Called when the call has finished, failed or if it has been cancelled.
*
*  @return         A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the priority of
*               the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)archiveFile:(AdobeStorageResourceItem *)resource
ifExists:(BOOL)ifExists
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionBlock:(AdobeStorageResourceRequestCompletionHandler)completionBlock;

/**
*  DEPRECATED: Archive the specified file synchronously. It does not permanently delete the file from the cloud.
*  There is no API to expunge nor restore the file from the archive as of this time.
*
*  @param resource    The resource describing the file to archive.
*  @param ifExists    If YES then don't return an error in the event that the file is missing.
*  @param priority    The priority of the HTTP request.
*  @param errorPtr    An optional pointer to an NSError object that will be set in case of an error.
*
*  @return         YES on success, NO on failure.
*/
- (BOOL)archiveFile:(AdobeStorageResourceItem *)resource
ifExists:(BOOL)ifExists
requestPriority:(NSOperationQueuePriority)priority
withError:(NSError **)errorPtr __deprecated_msg("Use archiveFile:ifExists:requestPriority:error:");

/**
*  Archive the specified file synchronously. It does not permanently delete the file from the cloud.
*  There is no API to expunge nor restore the file from the archive as of this time.
*
*  @param resource    The resource describing the file to archive.
*  @param ifExists    If YES then don't return an error in the event that the file is missing.
*  @param priority    The priority of the HTTP request.
*  @param errorPtr    An optional pointer to an NSError object that will be set in case of an error.
*
*  @return         YES on success, NO on failure.
*/
- (BOOL)archiveFile:(AdobeStorageResourceItem *)resource
ifExists:(BOOL)ifExists
requestPriority:(NSOperationQueuePriority)priority
error:(NSError **)errorPtr;

/**
*  Empty the archive (trash) asynchronously.
*
*  @param priority         The priority of the HTTP request.
*  @param queue            If not nil it determines the queue that the completion block gets executed on.
*  @param completionBlock  Called when the call has finished, failed or if it has been cancelled.
*
*  @return         A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the priority of
*               the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)emptyArchiveWithPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionBlock:(void (^)(NSError *err))completionBlock;

/**
*  Empty the archive (trash) synchronously.
*
*  @param priority    The priority of the HTTP request.
*  @param errorPtr    An optional pointer to an NSError object that will be set in case of an error.
*
*  @return         YES on success, NO on failure.
*/
- (BOOL)emptyArchiveWithPriority:(NSOperationQueuePriority)priority
error:(NSError **)errorPtr;

/**
* DEPRECATED: Asynchronously copies a file resource on the server. This API may not handle special characters
* correctly and no replacement API is available yet.
*
* @param srcResource   Resource that identifies the source file
* @param destResource  Resource that identifies a destination file that does not yet exist.
* @param createIntermediateDirs  Indicates whether intermediate directories should be created if they don't already exist.
* @param priority      The priority of the HTTP request.
* @param queue         Optional parameter. If not nil, queue determines the operation queue that handler gets executed on.
* @param completionBlock   Called when the copy request has finished or failed.  If successful then the handler will be called
* with an AdobeStorageResourceItem that describes the destination file.
*
* @return            AdobeNetworkHTTPRequest object that can be used to track progress or cancel the request
*
* @note  Overwriting existing destination files is not supported by the server and will result in an AdobeAssetUnexpectedResponse error
*/
- (AdobeNetworkHTTPRequest *)copyFile:(AdobeStorageResourceItem *)srcResource
destination:(AdobeStorageResourceItem *)destResource
createIntermediateDirs:(BOOL)createIntermediateDirs
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionBlock:(AdobeStorageResourceRequestCompletionHandler)completionBlock __deprecated_msg("API may not handle special characters in asset names properly. Avoid if possible. A replacement API is not yet available.");

/**
* DEPRECATED: Synchronously copies a file resource on the server. This API may not handle special characters
* correctly and no replacement API is available yet.
*
* @param srcResource   Resource that identifies the source file.
* @param destResource  Resource that identifies a destination file that does not yet exist.
* @param createIntermediateDirs  Indicates whether intermediate directories should be created if they don't already exist.
* @param errorPtr    An optional pointer to an NSError object that will be set in case of an error.
*
* @return AdobeStorageResourceItem object that describes the destination resource if the request succeeds.  Nil if the request fails.
*
* @note  Overwriting existing destination files is not supported by the server and will result in an AdobeAssetUnexpectedResponse error
*/

- (AdobeStorageResourceItem *)copyFile:(AdobeStorageResourceItem *)srcResource
destination:(AdobeStorageResourceItem *)destResource
createIntermediateDirs:(BOOL)createIntermediateDirs
error:(NSError **)errorPtr __deprecated_msg("API may not handle special characters in asset names properly. Avoid if possible. A replacement API is not yet available.");

///@}

#pragma mark Profile Methods
/** @name Profile Methods */
///@{

/**
*  Get the quota information for the logged in user, asynchronously.
*
*  @param priority The priority of the HTTP request.
*  @param queue            If not nil it determines the queue that the completion block gets executed on.
*  @param completionBlock  Called when the call has finished, failed or if it has been cancelled.
*
*  @return         A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*
*  @note On success dir will get updated and handed to the handler.
*/
- (AdobeNetworkHTTPRequest *)getQuota:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionHandler:(void (^)(NSNumber *used, NSNumber *available, NSNumber *total, NSError *err))handler __deprecated_msg("Use quota:handlerQueue:completionBlock:");

///@}

@end

#endif /* ifndef AdobeStorageSessionFilesHeader */
