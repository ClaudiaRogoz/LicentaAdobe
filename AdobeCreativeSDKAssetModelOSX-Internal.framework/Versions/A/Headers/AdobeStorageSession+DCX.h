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

#ifndef AdobeStorageSessionDCXHeader
#define AdobeStorageSessionDCXHeader

#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeStorageSession.h>

#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeDCXTransferSessionProtocol.h>

/**
* Adds composite-related functionality to the Creative Cloud Storage Session.
*/
@interface AdobeStorageSession (DCX) <AdobeDCXTransferSessionProtocol>

///@}
#pragma mark Misc
/** @name Misc */
///@{

/**
* brief Returns the base URL of the underlying storage service
*/
- (NSString*)baseURL;

///@}
#pragma mark Composite Methods
/** @name Composite Methods */
///@{

/**
* brief Returns the sync group name corresponding to the href path for the given composite
*
* param composite The composite whose sync group we wish to discover
*
* return The name of the sync group
*/
- (NSString *)getSyncGroupNameForComposite:(AdobeDCXComposite *)composite;

/**
* brief Create the specified composite (if it doesn't yet exist) asynchronously.
*
* param composite The composite to create on the server.
* param priority  The priority of the HTTP request.
* param queue     Optional parameter. If not nil queue determines the operation queue handler
* gets executed on.
* param handler   Called when the upload has finished or failed.
*
*
* return          A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*
* note Returns success even if there is already a composite directory with the same href.
*/
- (AdobeNetworkHTTPRequest *)createComposite:(AdobeDCXComposite *)composite
overwriteExisting:(BOOL)overwrite
requestPriority:(NSOperationQueuePriority)priority
etsContext:(AdobeDCXXferETSContext*)etsContext
handlerQueue:(NSOperationQueue *)queue
completionHandler:(AdobeDCXCompositeRequestCompletionHandler)handler;

/**
* brief Create the specified composite (if it doesn't yet exist) synchronously.
*
* param composite The composite to create.
* param overwrite Whether to overwrite the composite.
* param priority  The priority of the HTTP request.
* param errorPtr  An optional pointer to an NSError object that will be set in case of an error.
*
* return          YES on success, NO on failure.
*
* note Returns success even if there is already a composite directory with the same href.
*/
- (BOOL)createComposite:(AdobeDCXComposite *)composite
overwriteExisting:(BOOL)overwrite
requestPriority:(NSOperationQueuePriority)priority
etsContext:(AdobeDCXXferETSContext*)etsContext
withError:(NSError **)errorPtr;

/**
* brief Delete the specified composite, recursively and asynchronously.
*
* param composite The composite to delete.
* param priority  The priority of the HTTP request.
* param queue     Optional parameter. If not nil queue determines the operation queue handler
*                gets executed on.
* param handler   Called when the upload has finished or failed.
*
*
* return          A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
*                priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)deleteComposite:(AdobeDCXComposite *)composite
requestPriority:(NSOperationQueuePriority)priority
etsContext:(AdobeDCXXferETSContext*)etsContext
handlerQueue:(NSOperationQueue *)queue
completionHandler:(AdobeDCXCompositeRequestCompletionHandler)handler;

/**
* brief Delete the specified composite, recursively and synchronously.
*
* param composite The composite to delete.
* param priority  The priority of the HTTP request.
* param errorPtr  An optional pointer to an NSError object that will be set in case of an error.
*
* return          YES on success, NO on failure.
*/
- (BOOL)deleteComposite:(AdobeDCXComposite *)composite
requestPriority:(NSOperationQueuePriority)priority
etsContext:(AdobeDCXXferETSContext*)etsContext
withError:(NSError **)errorPtr;

/**
* brief Removes the shared composite from the user's view of assets on the server
*
* param composite The composite that has been shared with the current user
* param priority  The priority of the HTTP request.
* param queue     Optional parameter. If not nil queue determines the operation queue handler
* gets executed on.
* param handler   Called when the request has succeeded or failed.
*
*
* return          A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)leaveSharedComposite:(AdobeDCXComposite *)composite
requestPriority:(NSOperationQueuePriority)priority
etsContext:(AdobeDCXXferETSContext*)etsContext
handlerQueue:(NSOperationQueue *)queue
completionHandler:(AdobeDCXCompositeRequestCompletionHandler)handler;


/**
* brief Removes the shared composite from the user's view of assets on the server
*
* param composite The composite that has been shared with the current user
* param priority  The priority of the HTTP request.
* param errorPtr  An optional pointer to an NSError object that will be set in case of an error.
*
* return          YES on success, NO on failure.
*/
- (BOOL)leaveSharedComposite:(AdobeDCXComposite *)composite
requestPriority:(NSOperationQueuePriority)priority
etsContext:(AdobeDCXXferETSContext*)etsContext
withError:(NSError **)errorPtr;

///@}
#pragma mark Manifest Methods

/**
* brief Creates and returns an AdobeStorageResourceItem for the given manifest.
*
* param manifest  The manifest to return the resource for.
* param composite The composite of the manifest to return the resource for.
*
* return The resource.
*/
- (AdobeStorageResourceItem *)resourceForManifest:(AdobeDCXManifest *)manifest
ofComposite:(AdobeDCXComposite *)composite;

/** @name Manifest Methods */
///@{

/**
* brief Upload a manifest asset from memory to the server asynchronously, creating it if it doesn't
* already exist.
*
* param manifest  The manifest to upload.
* param composite  The composite of the manifest.
* param overwrite Whether to overwrite the manifest.
* param priority The priority of the HTTP request.
* param queue     Optional parameter. If not nil queue determines the operation queue handler
*                gets executed on.
* param handler   Called when the upload has finished or failed.
*
* note On success manifest gets copied, updated with the new etag, version, length, md5 values and
* passed to the completion handler.
*
* return          A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
*                priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)updateManifest:(AdobeDCXManifest *)manifest ofComposite:(AdobeDCXComposite *)composite
overwriteExisting:(BOOL)overwrite
requestPriority:(NSOperationQueuePriority)priority
etsContext:(AdobeDCXXferETSContext*)etsContext
handlerQueue:(NSOperationQueue *)queue
completionHandler:(AdobeDCXManifestRequestCompletionHandler)handler;

/**
* brief Upload a manifest asset from memory to the server synchronously, creating it if it doesn't
* already exist.
*
* param manifest  The manifest to upload.
* param composite The composite of the manifest.
* param overwrite Whether to overwrite the manifest.
* param priority  The priority of the HTTP request.
* param errorPtr  An optional pointer to an NSError object that will be set in case of an error.
*
* return          On success the updated manifest. Nil on failure.
*/
- (AdobeDCXManifest *)updateManifest:(AdobeDCXManifest *)manifest ofComposite:(AdobeDCXComposite *)composite
overwriteExisting:(BOOL)overwrite
requestPriority:(NSOperationQueuePriority)priority
etsContext:(AdobeDCXXferETSContext*)etsContext
withError:(NSError **)errorPtr;

/**
* brief Download a manifest asset to memory from the server asynchronously.
*
* param manifest  Optional: A locally existing manifest.
* param composite The composite to download the manifest of.
* param priority  The priority of the HTTP request.
* param queue     Optional parameter. If not nil queue determines the operation queue handler
*                gets executed on.
* param handler   Gets called when the upload has completed or failed.
*
* note If the manifest has its etag set and the latest version of the manifest file on
* the server has the same etag the manifest will not get downloaded and no error will be returned.
*
* return          A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
*                priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)getManifest:(AdobeDCXManifest *)manifest ofComposite:(AdobeDCXComposite *)composite
requestPriority:(NSOperationQueuePriority)priority
etsContext:(AdobeDCXXferETSContext*)etsContext
handlerQueue:(NSOperationQueue *)queue
completionHandler:(AdobeDCXManifestRequestCompletionHandler)handler;


/**
* brief Download a manifest asset to memory from the server synchronously.
*
* param manifest  Optional: A locally existing manifest.
* param composite The composite to download the manifest of.
* param priority  The priority of the HTTP request.
* param errorPtr  An optional pointer to an NSError object that will be set in case of an error.
*
* return          On success the updated manifest. Nil on failure or if the manifest hasn't changed.
*/
- (AdobeDCXManifest *)getManifest:(AdobeDCXManifest *)manifest ofComposite:(AdobeDCXComposite *)composite
requestPriority:(NSOperationQueuePriority)priority
etsContext:(AdobeDCXXferETSContext*)etsContext
withError:(NSError **)errorPtr;

/**
* brief Get the header information for the manifest asset from the server asynchronously.
*
* param composite The composite to download the manifest of.
* param priority  The priority of the HTTP request.
* param queue     Optional parameter. If not nil queue determines the operation queue handler
*                gets executed on.
* param handler   Gets called when the upload has completed or failed.
*
* return          A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)getHeaderInfoForManifestOfComposite:(AdobeDCXComposite *)composite
requestPriority:(NSOperationQueuePriority)priority
etsContext:(AdobeDCXXferETSContext*)etsContext
handlerQueue:(NSOperationQueue *)queue
completionHandler:(AdobeDCXHeadRequestCompletionHandler)handler;

///@}
#pragma mark Component Methods
/** @name Component Methods */
///@{

/**
* brief Upload a component asset from a file to the server asynchronously, creating it if it doesn't
* already exist.
*
* param component The component to upload.
* param composite The composite the component belongs to.
* param path      File path to upload the component from.
* param isNew     Whether the component is considered a new component of the composite.
* param priority  The priority of the HTTP request.
* param queue     Optional parameter. If not nil queue determines the operation queue handler
*                gets executed on.
* param handler   Called when the upload has finished or failed.
*
* note On success the component will be duplicated, updated with etag, etc. and passed to the handler.
*
* return          A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
*                priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)uploadComponent:(AdobeDCXComponent *)component
ofComposite:(AdobeDCXComposite *)composite
fromPath:(NSString *)path
componentIsNew:(BOOL)isNew
requestPriority:(NSOperationQueuePriority)priority
etsContext:(AdobeDCXXferETSContext*)etsContext
handlerQueue:(NSOperationQueue *)queue
completionHandler:(AdobeDCXComponentRequestCompletionHandler)handler;


/**
* brief Upload a component asset from a file to the server synchronously, creating it if it doesn't
* already exist.
*
* param component The component to upload.
* param composite The composite the component belongs to.
* param path      File path to upload the component from.
* param isNew     Whether the component is considered a new component of the composite.
* param priority  The priority of the HTTP request.
* param errorPtr  An optional pointer to an NSError object that will be set in case of an error.
*
* return          On succes the updated component. Otherwise nil.
*/
- (AdobeDCXComponent *)uploadComponent:(AdobeDCXComponent *)component
ofComposite:(AdobeDCXComposite *)composite
fromPath:(NSString *)path
componentIsNew:(BOOL)isNew
requestPriority:(NSOperationQueuePriority)priority
etsContext:(AdobeDCXXferETSContext*)etsContext
withError:(NSError **)errorPtr;

/**
* brief Download a component asset from the server asynchronously.
*
* param component The component to download.
* param composite The composite the component belongs to.
* param path      File path to download the component to.
* param priority  The priority of the HTTP request.
* param queue     Optional parameter. If not nil queue determines the operation queue handler
*                gets executed on.
* param handler   Gets called when the upload has completed or failed.
*
* note On success the unmodified component will passed to the handler.
*
* return          A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
*                priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)downloadComponent:(AdobeDCXComponent *)component ofComposite:(AdobeDCXComposite *)composite toPath:(NSString *)path
requestPriority:(NSOperationQueuePriority)priority
etsContext:(AdobeDCXXferETSContext*)etsContext
handlerQueue:(NSOperationQueue *)queue
completionHandler:(AdobeDCXComponentRequestCompletionHandler)handler;

/**
* brief Download a component asset from the server synchronously.
*
* param component The component to download.
* param composite The composite the component belongs to.
* param path      File path to download the component to.
* param priority  The priority of the HTTP request.
* param errorPtr  An optional pointer to an NSError object that will be set in case of an error.
*
* return          YES on success, NO on failure.
*/
- (BOOL)downloadComponent:(AdobeDCXComponent *)component ofComposite:(AdobeDCXComposite *)composite toPath:(NSString *)path
requestPriority:(NSOperationQueuePriority)priority
etsContext:(AdobeDCXXferETSContext*)etsContext
withError:(NSError **)errorPtr;

/**
* brief Download a component asset from a specific href asynchronously
*
* param sourceHref The href of a server resource accessible via this sesssion
* param component The component to download.
* param composite The composite the component belongs to.
* param path      File path to download the component to.
* param priority  The priority of the HTTP request.
* param queue     Optional parameter. If not nil queue determines the operation queue handler
* gets executed on.
* param handler   Gets called when the upload has completed or failed.
*
* note On success the modified component, whose length property has been updated to reflect
* the downloaded content, will passed to the handler.
*
* return          A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)downloadFromHref:(NSString *)sourceHref toComponent:(AdobeDCXComponent *)component ofComposite:(AdobeDCXComposite *)composite
withPath:(NSString *)path
requestPriority:(NSOperationQueuePriority)priority
etsContext:(AdobeDCXXferETSContext*)etsContext
handlerQueue:(NSOperationQueue *)queue
completionHandler:(AdobeDCXComponentRequestCompletionHandler)handler;

/**
* brief Delete a component asset on the server asynchronously.
*
* param component The component to download.
* param composite The composite the component belongs to.
* param priority  The priority of the HTTP request.
* param queue     Optional parameter. If not nil queue determines the operation queue handler
*                gets executed on.
* param handler   Gets called when the deletion has completed or failed.
*
* note On success the unmodified component will passed to the handler.
*
* return          A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
*                priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)deleteComponent:(AdobeDCXComponent *)component ofComposite:(AdobeDCXComposite *)composite
requestPriority:(NSOperationQueuePriority)priority
etsContext:(AdobeDCXXferETSContext*)etsContext
handlerQueue:(NSOperationQueue *)queue
completionHandler:(AdobeDCXComponentRequestCompletionHandler)handler;

/**
* brief Delete a component asset on the server synchronously.
*
* param component The component to download.
* param composite The composite the component belongs to.
* param priority  The priority of the HTTP request.
* param errorPtr  An optional pointer to an NSError object that will be set in case of an error.
*
* return          YES on success, NO on failure.
*/
- (BOOL)deleteComponent:(AdobeDCXComponent *)component ofComposite:(AdobeDCXComposite *)composite
requestPriority:(NSOperationQueuePriority)priority
etsContext:(AdobeDCXXferETSContext*)etsContext
withError:(NSError **)errorPtr;

/**
* brief Populate a component asset on the server asynchronously by executing a server-to-server
* copy from the specified href.
*
* param assetHref   The URI-encoded href to use as the source location for the server-to-server copy
* param component   The component to upload
* param composite   The composite the component belongs to.
* param isNew       Whether the component is considered a new component of the composite.
* param priority    The priority of the HTTP request.
* param queue       Optional parameter. If not nil, queue determines the operation queue handler
* gets executed on.
* param handler     Called when the copy has finished or failed.
* return            AdobeNetworkHTTPRequest object that can be used to track progress or cancel the request.
*
* note On success the component will be duplicated, updated with etag, version, etc. and passed to the handler.
* Note that this method does not update the composite's manifest on the server.  The client must still commit and
* push changes to composites using the appropriate AdobeDCXComposite and AdobeDCXCompositeXfer APIs.
*/
- (AdobeNetworkHTTPRequest *)uploadServerAssetWithHref:(NSString *)assetHref
toComponent:(AdobeDCXComponent *)component
ofComposite:(AdobeDCXComposite *)composite
componentIsNew:(BOOL)isNew
requestPriority:(NSOperationQueuePriority)priority
etsContext:(AdobeDCXXferETSContext*)etsContext
handlerQueue:(NSOperationQueue *)queue
completionHandler:(AdobeDCXComponentRequestCompletionHandler)componentCompletionHandler;

/**
* brief Populate a component asset on the server synchronously by executing a server-to-server
* copy from the specified href.
*
* param component   The component to upload
* param composite   The composite the component belongs to.
* param assetHref   The href to use as the source location for the server-to-server copy
* param isNew       Whether the component is considered a new component of the composite.
* param priority    The priority of the HTTP request.
* param errorPtr  An optional pointer to an NSError object that will be set in case of an error.
*
* return            AdobeNetworkHTTPRequest object that can be used to track progress or cancel the request.
*
* note On success a duplicated and updated component will be returned to the caller.
* Note that this method does not update the composite's manifest on the server.  The client must still commit and
* push changes to composites using the appropriate AdobeDCXComposite and AdobeDCXCompositeXfer APIs.
*/

- (AdobeDCXComponent *)uploadServerAssetWithHref:(NSString *)assetHref
toComponent:(AdobeDCXComponent *)component
ofComposite:(AdobeDCXComposite *)composite
componentIsNew:(BOOL)isNew
requestPriority:(NSOperationQueuePriority)priority
etsContext:(AdobeDCXXferETSContext*)etsContext
withError:(NSError **)errorPtr;

/**
* brief Get the HEAD info of a file for a component asynchronously.
*
* param href        The href of the file whose HEAD info should be retrieved
* param version     Optional version of the file.
* param priority    The priority of the HTTP request.
* param queue       Optional parameter. If not nil queue determines the operation queue handler gets
*                  executed on.
* param handler     Gets called when the request has completed or failed.
*
*
* return            A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the priority
*                  of the request and to cancel it.
*
* note On success the properties of the resource param will get updated and handed to the handler.
*/
- (AdobeNetworkHTTPRequest *)getHeaderInfoForAssetAt:(NSString *)href
forComponent:(AdobeDCXComponent *)component
version:(NSString*)version
requestPriority:(NSOperationQueuePriority)priority
etsContext:(AdobeDCXXferETSContext*)etsContext
handlerQueue:(NSOperationQueue *)queue
completionHandler:(AdobeDCXHeadRequestCompletionHandler)handler;

/**
* brief Returns the versioned href of a previously uploaded component of a composite that has been pushed to
* the network service ensapsulated by this session.
*
* param component     The component whose href should be returned
* param composite     The composite containing the component
*
* return  An href that can be resolved using this session.  Nil if the component has not been previously uploaded.
*/
-(NSString *)hrefForUploadedComponent:(AdobeDCXComponent*)component ofComposite:(AdobeDCXComposite *)composite;


///@}

@end

#endif
