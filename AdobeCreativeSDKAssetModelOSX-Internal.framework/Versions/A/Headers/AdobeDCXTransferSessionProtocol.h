/*************************************************************************
*
* ADOBE CONFIDENTIAL
* ___________________
*
*  Copyright 2014 Adobe Systems Incorporated
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

#ifndef AdobeDCXTransferSessionProtocolHeader
#define AdobeDCXTransferSessionProtocolHeader

#import <Foundation/Foundation.h>

#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeDCXComponentManagerProtocol.h>

@class AdobeDCXComposite;
@class AdobeDCXManifest;
@class AdobeDCXComponent;

@class AdobeNetworkHTTPRequest;

@class AdobeDCXXferETSContext;

/** The generic completion handlers for asynchronous manifest/component-based session requests. */
typedef void (^AdobeDCXCompositeRequestCompletionHandler)(AdobeDCXComposite *, NSError *);
typedef void (^AdobeDCXHeadRequestCompletionHandler)(NSString *etag, NSString *md5, NSString *version, NSNumber *length, NSError *);
typedef void (^AdobeDCXManifestRequestCompletionHandler)(AdobeDCXManifest *, NSError *);
typedef void (^AdobeDCXComponentRequestCompletionHandler)(AdobeDCXComponent *, NSError *);

/**
* Defines the protocol that a session has to implement in order to be used as a session for the
* push and pull methods of AdobeDCXCompositeXfer.
*/
@protocol AdobeDCXTransferSessionProtocol <NSObject>

///@}
#pragma mark Misc
/** @name Misc */
///@{

/**
* brief Returns the base URL of the underlying storage ervice
*/
- (NSString*)baseURL;

@optional

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
* brief Removes the shared composite from the user's view of assets on the server
*
* param composite The composite that has been shared with the current user
* param priority  The priority of the HTTP request.
* param queue     Optional parameter. If not nil queue determines the operation queue handler
* gets executed on.
* param handler   Called when the upload has finished or failed.
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
* brief Delete the specified composite, recursively and asynchronously.
*
* param composite The composite to delete.
* param priority  The priority of the HTTP request.
* param queue     Optional parameter. If not nil queue determines the operation queue handler
* gets executed on.
* param handler   Called when the upload has finished or failed.
*
*
* return          A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)deleteComposite:(AdobeDCXComposite *)composite
requestPriority:(NSOperationQueuePriority)priority
etsContext:(AdobeDCXXferETSContext*)etsContext
handlerQueue:(NSOperationQueue *)queue
completionHandler:(AdobeDCXCompositeRequestCompletionHandler)handler;


///@}
#pragma mark Manifest Methods
/** @name Manifest Methods */
///@{

@required

/**
* brief Upload a manifest asset from memory to the server asynchronously, creating it if it doesn't
* already exist.
*
* param manifest  The manifest to upload.
* param composite  The composite of the manifest.
* param overwrite Whether to overwrite the manifest.
* param priority The priority of the HTTP request.
* param queue     Optional parameter. If not nil queue determines the operation queue handler
* gets executed on.
* param handler   Called when the upload has finished or failed.
*
* note On success manifest gets copied, updated with the new etag, version, length, md5 values and
* passed to the completion handler.
*
* return          A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)updateManifest:(AdobeDCXManifest *)manifest ofComposite:(AdobeDCXComposite *)composite
overwriteExisting:(BOOL)overwrite
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
* gets executed on.
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
* gets executed on.
* param handler   Called when the upload has finished or failed.
*
* note On success the component will be duplicated, updated with etag, etc. and passed to the handler.
*
* return          A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
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
* gets executed on.
* param handler   Gets called when the upload has completed or failed.
*
* note On success the unmodified component will passed to the handler.
*
* return          A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)downloadComponent:(AdobeDCXComponent *)component ofComposite:(AdobeDCXComposite *)composite toPath:(NSString *)path
requestPriority:(NSOperationQueuePriority)priority
etsContext:(AdobeDCXXferETSContext*)etsContext
handlerQueue:(NSOperationQueue *)queue
completionHandler:(AdobeDCXComponentRequestCompletionHandler)handler;

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

@optional

/**
* brief Populate a component asset on the server asynchronously by executing a server-to-server
* copy from the specified href.
*
* param assetHref   The href to use as the source location for the server-to-server copy
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
* gets executed on.
* param handler   Gets called when the deletion has completed or failed.
*
* note On success the unmodified component will passed to the handler.
*
* return          A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)deleteComponent:(AdobeDCXComponent *)component ofComposite:(AdobeDCXComposite *)composite
requestPriority:(NSOperationQueuePriority)priority
etsContext:(AdobeDCXXferETSContext*)etsContext
handlerQueue:(NSOperationQueue *)queue
completionHandler:(AdobeDCXComponentRequestCompletionHandler)handler;


/**
* brief Get the HEAD info of an file asynchronously.
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


#pragma mark - Component Manager ( optional )

@optional

/**
brief Set component manager for unmanaged components.

param componentManager: An object of a class which implements the AdobeDCXComponentManagerProtocol

note The unmanaged components are being used then, the component manager needs to be specified so that the
Xfer logic can call the delegates of the component manager. Currently the ownership of the component manager
delegate resides within the session object which might be moved out in later releases
*/
- (void) setComponentManager:(id<AdobeDCXComponentManagerProtocol>) componentManager;


/**
brief Get the registered component manager, if any, for this session

returnsAn object of a class which implements the AdobeDCXComponentManagerProtocol, which has been previously registered by the client

note The unmanaged components are being used then, the component manager needs to be specified so that the
Xfer logic can call the delegates of the component manager. Currently the ownership of the component manager
delegate resides within the session object which might be moved out in later releases
*/
- (id<AdobeDCXComponentManagerProtocol>) getComponentManager;

/**
* brief Set a delegate queue which is to be associated with the component Manager
*
* note If the client wants all the delegate calls to be make on a specific queue,
* the delegate queue should be set to that NSOperationQueue using this function. If no delegate is specified,
* then the application's main dispatch queue is used (i.e. the serial queue that executes tasks on the
* main thread) to make the delegate calls.
*/
-(void) setComponentManagerDelegateQueue:(NSOperationQueue*) delegateQueue;


/**
* brief Get the delegate queue which is associated with the component Manager
*
* returns The NSOperation queue
*/
-(NSOperationQueue*) getComponentManagerDelegateQueue;

///@}

@end

#endif
