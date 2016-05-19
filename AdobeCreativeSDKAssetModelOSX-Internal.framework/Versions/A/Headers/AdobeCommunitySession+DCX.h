/*************************************************************************
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
* suppliers and are protected by all applicable intellectual property
* laws, including trade secret and copyright laws.
* Dissemination of this information or reproduction of this material
* is strictly forbidden unless prior written permission is obtained
* from Adobe Systems Incorporated.
**************************************************************************/

#ifndef AdobeCommunitySessionDCXHeader
#define AdobeCommunitySessionDCXHeader

#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeDCXTransferSessionProtocol.h>
#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeDCXPublishSessionProtocol.h>

@class AdobeCommunityPublicationRecord;

/**
* Adds composite-related functionality to the Community Session.
*/
@interface AdobeCommunitySession (DCX) <AdobeDCXTransferSessionProtocol, AdobeDCXPublishSessionProtocol>

///@}
#pragma mark Misc
/** @name Misc */
///@{

/**
* brief Returns the base URL of the underlying storage ervice
*/
- (NSString*)baseURL;

///@}
#pragma mark Composite Methods
/** @name Misc */
///@{


typedef void (^AdobeDCXPublicationRecordCompletionHandler)(AdobeCommunityPublicationRecord *pubRecord, NSError *error);

/**
* brief Returns the publication record of the published composite from CP.
*
* param composite     The composite to get the record for. Must have its href set to the asset href as returned
*                      from a previous publish operation.
* param priority      The priority of the HTTP request.
* param queue         Optional parameter. If not nil queue determines the operation queue handler
*                      gets executed on.
* param handler       Called when the request has finished or failed.
*/
-(AdobeNetworkHTTPRequest*)getPublicationRecordOfComposite:(AdobeDCXComposite *)composite
requestPriority:(NSOperationQueuePriority)priority
etsContext:(AdobeDCXXferETSContext*)etsContext
handlerQueue:(NSOperationQueue *)queue
completionHandler:(AdobeDCXPublicationRecordCompletionHandler)handler;

///@}
#pragma mark Manifest Methods
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
*  Download a rendition for a component from the server asynchronously.
*
* param component     The component to download a rendition for.
* param composite     The composite the component belongs to.
* param filePath      File path to download the component rendition to.
* param dimension     The dimention for the given size of the rendition (width or height).
* param size          The size for the rendition (on the given dimension.
* param type          The content type of the rendition.
* param priority      The priority of the HTTP request.
* param queue         If not nil it determines the queue that the completion block gets executed on.
* param handler       Called when the call has finished successfully or has failed.
*
* return              An AdobeNetworkHTTPRequest object that can be used to track progress, adjust the priority
*                      of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)downloadComponentRendition:(AdobeDCXComponent *)component
ofComposite:(AdobeDCXComposite *)composite
toPath:(NSString *)filePath
dimension:(AdobeCommunityAssetImageDimension)dimension
size:(NSUInteger)size
contentType:(NSString *)type
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionHandler:(void (^)(NSError *))handler;

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
// TODO
/*
- (AdobeNetworkHTTPRequest *)uploadServerAssetWithHref:(NSString *)assetHref
toComponent:(AdobeDCXComponent *)component
ofComposite:(AdobeDCXComposite *)composite
componentIsNew:(BOOL)isNew
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionHandler:(AdobeDCXComponentRequestCompletionHandler)componentCompletionHandler;
*/

///@}

@end

#endif
