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

#ifndef AdobeDCXCompositeXferHeader
#define AdobeDCXCompositeXferHeader

#import <Foundation/Foundation.h>

@class AdobeDCXCompositeBranch;
@class AdobeDCXComposite;
@class AdobeNetworkHTTPRequest;
@class AdobeRemixData;
@class AdobeDCXCommunityMetadata;
@class AdobeCommunitySession;
@class AdobeDCXMutableMetadata;

@protocol AdobeDCXTransferSessionProtocol;
@protocol AdobePublicationRecordProtocol;
@protocol AdobeDCXPublishSessionProtocol;

/**
* Implementation of the push & pull logic for composites.
*/
@interface AdobeDCXCompositeXfer : NSObject

#pragma mark Completion Handler Types

/**
* brief Type defining the signature of a completion handler for pushComposite:usingSession:queue:completionHandler.
*/
typedef void (^AdobeDCXPushCompletionHandler)(BOOL, NSError *);

/**
* brief Type defining the signature of a completion handler for pullComposite:usingSession:queue:completionHandler.
*/
typedef void (^AdobeDCXPullCompletionHandler)(AdobeDCXCompositeBranch *, NSError *);


#pragma mark - Push - Asynchronous

/**
*
* brief The first step of a composite push. Uploads the local committed state of the composite to the
* server, creating it on the server if it is a new composite.
*
* param composite The AdobeDCXComposite to push.
* param overwrite Whether to forcibly overwrite an already existing composite. Set this when the previous
*                attempt to push has failed with a AdobeDCXErrorCompositeAlreadyExists error and the
*                user has confirmed that it it OK to overwrite the composite.
* param session   The DCX session to use for the required http requests.
* param priority  The relative priority of the pull.
* param queue     Optional parameter. If not nil queue determines the operation queue handler
*                gets executed on.
* param handler   Gets called when the push has completed.  May be nil if the controller
*                property has been set on the composite since in that case errors will be always be reported
*                via the controller's AdobeDCXControllerDelegate interface.
*
*
* return          A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the priority
*                of the pull and to cancel it.
*
* note If the controller property of the composite is non-nil, then the associated AdobeDCXController
* will process any errors that result from calling this method and will inform the client via the
* controller:requestsClientHandleError:... method on its delegate in addition to calling the handler
* method passed to this function.
*
* This method reads the local committed manifest of the composite and analyzes it in order to determine whether
* it needs to create the composite and which of its component assets need to be uploaded (see Semantics
* of pushComposite below). If all of the necessary uploads succeed it does a final upload of the manifest
* (updated with links, etags, checksums and states of all the components) and returns the journal of
* these changes.
*
* There are some things that a client must **not** do while this method is executing:
*
* - Making changes to any of the component asset files in the current branch of the composite that are
* referenced by the current manifest at the time the pushComposite:withError: method gets called. I.e. the
* client must not write to or over any of those files nor is it allowed to delete any of them.
* - Call the pushComposite:withError: for the same composite.
*
* note pushComposite:withError: doesn't modify the current state of the composite and thus is only the first
* step of a 2-step push operation. See below for details.
*
* A Complete Push Operation
* -------------------------
*
* A composite push operation consists of 2 separate steps.
*
* 1. The first step is always to call pushComposite:withError:. If successful it uploads all necessary
* assets to the server and stores the resulting manifest, as well as a journal of all the uploads into
* the pushed branch of the composite. It does not modify the current state of the composite.
*
* 2. Once the call to pushComposite:withError: has completed successfully, the client must call [composite
* acceptPushWithError:]. This completes the push operation by merging the new server state now saved in the
* pushed branch into the current in memory and into the manifest file on disk.  It also
* updates the base branch to be the pushed branch before finally discarding the local copy of the pushed branch.
*
* Semantics of pushComposite:
* -------------------------
*
* What pushComposite does depends on whether composite points to an existing local
* composite and, if that is the case, on the state of the composite and its
* components as reflected in the manifest:
*
+ If the composite's state is AdobeDCXAssetStateCommittedDelete pushComposite will
+ do nothing and will set errorPtr to a AdobeDCXErrorDeletedComposite error.
+
+ Else if the composite doesn't exist in the cloud pushComposite
+ will create a new composite on the server, upload all its components (ignoring
+ their individual states) and update the local manifest with the correct links and
+ states.
+
+ Else if the composite's state is AdobeDCXAssetStatePendingDelete pushComposite
+ will try to delete the composite on the server. On success pushComposite will
+ change the composite's state to AdobeDCXAssetStateCommittedDelete, unbind the
+ manifest, _not_ set errorPtr and return nil.
+
+ Notice that pushComposite never deletes any local files.
+
+ Notice, too, that deleting a composite will fail if the composite has been modified on
+ the server. In this case errorPtr will contain a AdobeStorageErrorConflictingChanges error.
+
+ Else if the composite's state is AdobeDCXAssetStateUnmodified pushComposite will do
+ nothing and will _not_ set errorPtr.
+
+ Else pushComposite assumes the state to be AdobeDCXAssetStateModified. It will iterate over the
+ components of the composite, evaluate what to do with each of them based on their
+ state and update/upload the manifest:
+ If a component doesn't have an proper link it is considered a new component and
+ pushComposite will upload it and record its link in the manifest.
+ Else if a component's state is AdobeDCXAssetStateUnmodified the component
+ gets skipped.
+ Else if a component's state is AdobeDCXAssetStatePendingDelete pushComposite will
+ set its state to AdobeDCXAssetStateCommittedDelete so that it can get deleted
+ during a subsequent push. Notice that pushComposite never deletes any local
+ composites, so you will want to clean up after a successful push.
+ Else if a component's state is AdobeDCXAssetStateCommittedDelete pushComposite will
+ delete the component on the server and remove it from the manifest.
+ Else (must be AdobeDCXAssetStateModified) pushComposite will upload the component
+ as a new version to the server and record its new etag in the manifest.
+
+ Errors
+ -------------
+
+ These errors can occur (all in the AdobeAssetErrorDomain or AdobeDCXErrorDomain):
+ - AdobeAssetErrorBadRequest
+ - AdobeStorageErrorOffline
+ - AdobeAssetErrorUnexpectedResponse
+ - AdobeStorageErrorNetworkFailure
+ - AdobeStorageErrorAuthenticationFailed
+ - AdobeDCXErrorManifestReadFailure
+ - AdobeDCXErrorManifestWriteFailure
+ - AdobeDCXErrorManifestFinalWriteFailure
+ - AdobeDCXErrorInvalidManifest
+ - AdobeDCXErrorComponentReadFailure
+ - AdobeDCXErrorConflictingChanges
+ - AdobeDCXErrorDeletedComposite
+ - AdobeDCXErrorCompositeAlreadyExists
+
+ Of these a client must handle because they can happen during normal operations:
+
+ - AdobeStorageErrorNetworkFailure
+ - AdobeStorageErrorConflictingChanges
+ - AdobeDCXErrorCompositeAlreadyExists
+
+ This error ocurs if the copy of the composite on the server has been
+ modified since the last successfull push or pull. In this scenario the caller
+ should pull down the latest version from the server, resolve any
+ conflicts in that new copy and push that up to the server again.
+
+ Another cause of this error might be that the client has not yet called acceptPushWithError: or
+ acceptPushedManifest:withError: on the composite after a successful previous call to pushComposite:
+
+ - AdobeStorageErrorAuthenticationFailed
+
+ - AdobeStorageErrorOffline
*/
+ (AdobeNetworkHTTPRequest *)pushComposite:(AdobeDCXComposite *)composite
overwriteExisting:(BOOL)overwrite
usingSession:(id<AdobeDCXTransferSessionProtocol>)session
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionHandler:(AdobeDCXPushCompletionHandler)handler;

#pragma mark Push - Synchronous

/**
* brief Synchronous version of pushComposite:usingSession:queue:completionHandler.
*
* param composite The AdobeDCXComposite to push.
* param overwrite Whether to forcibly overwrite an already existing composite. Set this when the previous
*                attempt to push has failed with a AdobeDCXErrorCompositeAlreadyExists error and the
*                user has confirmed that it it OK to overwrite the composite.
* param session   The DCX session to use for the required http requests.
* param priority  The relative priority of the pull.
* param errorPtr  Gets set to an NSError if the operation fails.
*
* return          YES if successful.
*/
+ (BOOL)pushComposite:(AdobeDCXComposite *)composite
overwriteExisting:(BOOL)overwrite
usingSession:(id<AdobeDCXTransferSessionProtocol>)session
requestPriority:(NSOperationQueuePriority)priority
withError:(NSError **)errorPtr;

#pragma mark - Pull - Asynchronous

/**
* brief Downloads a version of the composite as it currently exists on the server. The copy
* can be used to atomically update the local composite and/or to resolve conflicts between
* the local composite and the cloud.
*
* param composite   The local AdobeDCXComposite.
* param session     The DCX session to use for the required http requests.
* param priority    The relative priority of the pull.
* param queue       Optional parameter. If not nil queue determines the operation queue handler
*                  gets executed on.
* param handler     Gets called when the pull has completed. It gets passed the AdobeDCXCompositeBranch
*                  of the pulled branch if the pull succeeds otherwise the caller should check errorPtr
*                  to determine whether there has been a problem (see below).  May be nil if the controller
*                  property has been set on the composite since in that case errors will be always be reported
*                  via the controller's AdobeDCXControllerDelegate interface.
*
* return            An AdobeNetworkHTTPRequest object that can be used to track progress, adjust the priority
*                  of the pull and to cancel it.
*
* note If the controller property of the composite is non-nil, then the associated AdobeDCXController
* will process any errors that result from calling this method and will inform the client via the
* controller:requestsClientHandleError:... method on its delegate in addition to calling the handler
* method passed to this function.
*
* Pulling a composite can result on one of three possible outcomes:
*
* 1. The composite in the cloud has not been modified since the last successful pull.
* In this case pull returns nil and *errorPtr is nil as well.
*
* 2. pullComposite succeededs and returns a AdobeDCXCompositeBranch. The local storage for the composite now
* contains two branches of the composite. If there are no local changes to the composite
* the caller should immediately call [composite acceptPullWithError:notifyMonitor:] so that the pulled version
* of the composite becomes current. Otherwise the caller is expected to first resolve
* any conflicts in the pulled down version of the composite and then call
* [composite acceptPullWithError:notifyMonitor:].
*
* 3. An error occurs. In this case pullComposite returns nil and sets errorPtr
* to an NSError which contains more information about the failure.
*
* There are some things that a client must **not** do while this method is executing:
*
* - (If the local storage scheme in use is not a copy-on-write scheme:) Make changes to any of the
* component asset files in the current branch of the composite that are referenced by the current
* manifest at the time the pullComposite:... method gets called. I.e. the client must not write to or
* over any of those files nor is it allowed to delete any of them.
* - Call a pull... method for the same composite.
*
* note pullComposite:... doesn't modify the current state of the composite and thus is only the
* first step of a 2-3 step pull operation. See below for details.
*
* A Complete Pull Operation
* -------------------------
*
* A composite pull operation consists of 2 or 3 separate steps.
*
* 1. The first step is always a call to pullComposite:withError:. If successful it downloads all necessary
* assets from the server and stores the resulting manifest as well as a journal of all the downloads
* into the pull branch of the composite. Component asset files that have not changed on the server
* are getting copied into the pull branch from the current branch. This method does not modify the
* current state of the composite.
*
* 2. The second step of the pull operation is necessary if the client has made changes to the current
* state of the composite since the last successful pull of push operation of the composite. I.e. if
* the user is allowed to continue working with the composite and the client takes care to not affect
* any of the existing asset files by e.g. only creating new asset files that replace the existing
* ones. Or if a previous attempt to push local changes to the server has failed with a
* AdobeStorageErrorConflictingChanges error.
*
* If this is the case the client must now merge the local changes that are saved in the current
* branch into the pull branch.  This can be done by comparing the manifests stored in the current,
* pull and base branches of the composite.
*
* The end result of this step must be a complete and consistent resolved version of the composite
* in the pull branch.
*
* 3. Once the second step is complete (or if it is not necessary) the client must call [composite
* acceptPullWithError:]. This completes the pull operation by updating the current branch of the
* composite with the version stored in the pull branch.
*
* Errors
* -------------
*
* These errors can occur (all in the AdobeAssetErrorDomain or AdobeDCXErrorDomain):
* - AdobeAssetErrorBadRequest
* - AdobeStorageErrorOffline
* - AdobeDCXErrorManifestReadFailure
* - AdobeDCXErrorInvalidLocalManifest
* - AdobeDCXErrorUnknownComposite
* - AdobeStorageErrorAuthenticationFailed
* - AdobeAssetErrorUnexpectedResponse
* - AdobeStorageErrorNetworkFailure
* - AdobeDCXErrorInvalidRemoteManifest
* - AdobeDCXErrorManifestWriteFailure
* - AdobeDCXErrorMissingComponentAsset
* - AdobeDCXErrorComponentWriteFailure
* - AdobeDCXErrorComponentCopyFailure
*
* These errors can occur during normal operations:
*
* - AdobeStorageErrorNetworkFailure
* - AdobeStorageErrorAuthenticationFailed
* - AdobeStorageErrorUnknownComposite
* - AdobeStorageErrorOffline
*
*/
+ (AdobeNetworkHTTPRequest *)pullComposite:(AdobeDCXComposite *)composite
usingSession:(id<AdobeDCXTransferSessionProtocol>)session
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionHandler:(AdobeDCXPullCompletionHandler)handler;

/**
* brief Downloads a minimal version of the specified composite (i.e. its manifest and its metadata),
* which can be used to selectively pull specific components and/or add new components to the composite.
*
* param composite   The local AdobeDCXComposite.
* param session     The DCX session to use for the required http requests.
* param priority    The relative priority of the pull.
* param queue       Optional parameter. If not nil queue determines the operation queue handler
*                  gets executed on.
* param handler     Gets called when the pull has completed. It gets passed the AdobeDCXCompositeBranch of the new
*                  version if the pull succeeds otherwise the caller should check errorPtr to determine
*                  whether there has been a problem (see below). May be nil if the controller
*                  property has been set on the composite since in that case errors will be always be reported
*                  via the controller's AdobeDCXControllerDelegate interface.
*
* return            An AdobeNetworkHTTPRequest object that can be used to track progress, adjust the priority
* of the pull and to cancel it.
*
* note If the controller property of the composite is non-nil, then the associated AdobeDCXController
* will process any errors that result from calling this method and will inform the client via the
* controller:requestsClientHandleError:... method on its delegate in addition to calling the handler
* method passed to this function.
*
* Pulling a composite manifest can result on one of three possible outcomes:
*
* 1. The composite in the cloud has not been modified since the last successful pull.
* In this case pull returns nil and *errorPtr is nil as well.
*
* 2. pullMinimalComposite succeeds and returns a AdobeDCXCompositeBranch.
*
* 3. An error occurs. In this case pullComposite returns nil and sets errorPtr
* to an NSError which contains more information about the failure.
*
* There are some things that a client must **not** do while this method is executing:
*
* - (If the local storage scheme in use is not a copy-on-write scheme:) Make changes to any of the
* component asset files in the current branch of the composite that are referenced by the current
* manifest at the time the pullComposite:... method gets called. I.e. the client must not write to or
* over any of those files nor is it allowed to delete any of them.
* - Call a pull... method for the same composite.
*
* Errors
* -------------
*
* These errors can occur (all in the AdobeAssetErrorDomain or AdobeDCXErrorDomain):
* - AdobeAssetErrorBadRequest
* - AdobeStorageErrorOffline
* - AdobeDCXErrorManifestReadFailure
* - AdobeDCXErrorInvalidLocalManifest
* - AdobeDCXErrorUnknownComposite
* - AdobeStorageErrorAuthenticationFailed
* - AdobeAssetErrorUnexpectedResponse
* - AdobeStorageErrorNetworkFailure
* - AdobeDCXErrorInvalidRemoteManifest
* - AdobeDCXErrorManifestWriteFailure
*
* These errors can occur during normal operations:
*
* - AdobeStorageErrorNetworkFailure
* - AdobeStorageErrorAuthenticationFailed
* - AdobeStorageErrorUnknownComposite
* - AdobeStorageErrorOffline
*
*/
+ (AdobeNetworkHTTPRequest *)pullMinimalComposite:(AdobeDCXComposite *)composite
usingSession:(id<AdobeDCXTransferSessionProtocol>)session
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionHandler:(AdobeDCXPullCompletionHandler)handler;

/**
* brief Downloads specific components of the specified composite branch
*
* param components          Optional list of components to download. Pass nil to download all missing components.
* param branch              The AdobeDCXCompositeBranch whose components are to be downloaded.
* param session             The DCX session to use for the required http requests.
* param priority            The relative priority of the pull.
* param queue               Optional parameter. If not nil queue determines the operation queue handler
* gets executed on.
* param handler             Gets called when the download has completed. It gets passed the AdobeDCXCompositeBranch of the new
* version if the download succeeds otherwise the caller should check errorPtr to determine
* whether there has been a problem (see below).
*
* return                    An AdobeNetworkHTTPRequest object that can be used to track progress, adjust the priority
* of the pull and to cancel it.
*
* note                      Unlike the pull methods, the client is expected to provide its own handler method
* even when the composite's controller property is non nil in order to obtain notification
* of the success or failure of the component download operation.
*
* There are some things that a client must **not** do while this method is executing:
*
* - (If the local storage scheme in use is not a copy-on-write scheme:) Make changes to any of the
* component asset files in the current branch of the composite that are referenced by the current
* manifest at the time the pullComposite:... method gets called. I.e. the client must not write to or
* over any of those files nor is it allowed to delete any of them.
* - Call a pull... method for the same composite.
*
* Errors
* -------------
*
* These errors can occur (all in the AdobeAssetErrorDomain or AdobeDCXErrorDomain):
* - AdobeAssetErrorBadRequest
* - AdobeStorageErrorOffline
* - AdobeDCXErrorManifestReadFailure
* - AdobeDCXErrorInvalidLocalManifest
* - AdobeStorageErrorAuthenticationFailed
* - AdobeAssetErrorUnexpectedResponse
* - AdobeStorageErrorNetworkFailure
* - AdobeDCXErrorInvalidRemoteManifest
* - AdobeDCXErrorManifestWriteFailure
* - AdobeDCXErrorMissingComponentAsset
* - AdobeDCXErrorComponentWriteFailure
* - AdobeDCXErrorComponentCopyFailure
*
* These errors can occur during normal operations:
*
* - AdobeStorageErrorNetworkFailure
* - AdobeStorageErrorAuthenticationFailed
* - AdobeStorageErrorUnknownComposite
* - AdobeStorageErrorOffline
*
*/
+ (AdobeNetworkHTTPRequest *)downloadComponents:(NSArray *)components
ofCompositeBranch:(AdobeDCXCompositeBranch *)branch
usingSession:(id<AdobeDCXTransferSessionProtocol>)session
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionHandler:(AdobeDCXPullCompletionHandler)handler;


#pragma mark Pull - Synchronous


/**
* brief Synchronous version of @see pullComposite:usingSession:requestPriority:handlerQueue:completionHandler:
*
* param composite The AdobeDCXComposite to pull.
* param session   The DCX session to use for the required http requests.
* param priority  The relative priority of the pull.
* param errorPtr  Gets set to an NSError if an error occurs.
*
* return The pulled AdobeDCXCompositeBranch if the pull succeeds. If nil the caller should check
* errorPtr in order to determine whether there has been a problem. If the method returns nil and there
* no error it means that there were no new changes to pull and that the current version of the composite
* is in sync with the composite on the server.
*/
+ (AdobeDCXCompositeBranch *)pullComposite:(AdobeDCXComposite *)composite
usingSession:(id<AdobeDCXTransferSessionProtocol>)session
requestPriority:(NSOperationQueuePriority)priority
error:(NSError **)errorPtr;


/**
* brief Synchronous version of pullMinimalComposite:....
*
* param composite The AdobeDCXComposite to pull.
* param session   The DCX session to use for the required http requests.
* param priority  The relative priority of the pull.
* param errorPtr  Gets set to an NSError if an error occurs.
*
* return The pulled AdobeDCXCompositeBranch if the pull succeeds. If nil the caller should check
* errorPtr in order to determine whether there has been a problem. If the method returns nil and there
* no error it means that there were no new changes to pull and that the current version of the composite
* is in sync with the composite on the server.
*/
+ (AdobeDCXCompositeBranch *)pullMinimalComposite:(AdobeDCXComposite *)composite
usingSession:(id<AdobeDCXTransferSessionProtocol>)session
requestPriority:(NSOperationQueuePriority)priority
error:(NSError **)errorPtr;

/**
* brief Synchronous version of downloadComponentsOfComposite:....
*
* param components          Optional list of components to download. Pass nil to download all missing components.
* param branch              The AdobeDCXCompositeBranch whose components are being downloaded.
* param session             The DCX session to use for the required http requests.
* param priority            The relative priority of the pull.
* param errorPtr            Gets set to an NSError if an error occurs.
*
* return                    The AdobeDCXCompositeBranch of the new version if the pull succeeds.
*/
+ (AdobeDCXCompositeBranch *)downloadComponents:(NSArray *)components
ofCompositeBranch:(AdobeDCXCompositeBranch *)branch
usingSession:(id<AdobeDCXTransferSessionProtocol>)session
requestPriority:(NSOperationQueuePriority)priority
error:(NSError **)errorPtr;

#pragma mark - Publish

/**
* brief Type defining the signature of a completion handler for publishComposite:...
*/
typedef void (^AdobeDCXPublishCompletionHandler)(NSString *assetHref, NSError *error);

/**
* brief Type defining the signature of a metadata handler for publishComposite:...
* If it returns NO the publish operation fails -- in that case it should set errorPtr to
* an error describing the reason of the failure.
*/
typedef BOOL (^AdobeDCXPublishMetadataHandler)(AdobeDCXMutableMetadata* metadata, NSError **errorPtr);

/**
* brief Type defining the signature of a completion handler for copyPublishedCompositeAtHref:...
*/
typedef void (^AdobeDCXRemixCompletionHandler)(AdobeDCXComposite *composite, NSError *error);

/**
* brief Publishes given composite as a new CP assest.
*
* param composite         The composite to publish.
* param remixData         Instance of AdobeRemixData.
* param publicationRecord The service-specific record for the published asset.
* param stageDirPath      The path of the directory that gets used to stage the composite to be published.
*                          Must be either non-existent or empty.
* param publishSession    The community session.
* param metadataHandler   Optional. Gets called when staging the composite and can be used to modify
*                          the metadata of the to-be-published composite. Notice that this method gets called
*                          on a background thread.
* param queue             Optional parameter. If not nil queue determines the operation queue the completion handler
*                          gets executed on.
* param handler           Gets called when the publish operation has completed or failed.
*
* return                  An AdobeNetworkHTTPRequest object that can be used to track progress, adjust the priority
*                          of the publish operation and to cancel it.
*
* note                    The push operation uses stageDirPath to prepare a composite that can be pushed to the
*                          publish service. It doesn't ever delete stageDirPath or its contents. It is the caller's
*                          responsibility to delete stageDirPath when no longer needed, i.e. when the publish
*                          operation has succeeded or when it fails with an AdobeDCXErrorInvalidStageDirectory
*                          error. Otherwise the caller can keep stageDirPath around and resume the publish operation
*                          at a later point in time.
*/
+ (AdobeNetworkHTTPRequest*)publishComposite:(AdobeDCXComposite*)composite
remixData:(AdobeRemixData*)remixData
publicationRecord:(id<AdobePublicationRecordProtocol>)publicationRecord
stageDirectory:(NSString*)stageDirPath
publishSession:(id<AdobeDCXPublishSessionProtocol,AdobeDCXTransferSessionProtocol>)publishSession
requestPriority:(NSOperationQueuePriority)priority
metadataHandler:(AdobeDCXPublishMetadataHandler)metadataHandler
handlerQueue:(NSOperationQueue *)queue
completionHandler:(AdobeDCXPublishCompletionHandler)handler;

/**
* brief Updates a published composite from the given composite.
*
* param publishedComposite    A composite that was previously pulished and should get updated from the contents
*                              of modifiedComposite. The publishedComposite does not have to be pulled, a simple
*                              composite instance created with the asset href and a local storage path pointing to
*                              a non-existent or empty directory is sufficient.
*                              (e.g. "/api/v2/{community id}/assets/{asset id}/original" would be the href for a CP asset)
* param modifiedComposite     The source composite that contains the changes that publishedComposite
*                              should get updated with.
* param remixData             Optional instance of AdobeRemixData. If not provided by the caller the method
*                              regenerates remix data from the metadata component of publishedComposite.
* param publicationRecord     Optional. The service-specific record for the published composite.
* param stageDirPath          The path of the directory that gets used to stage the composite to be published.
*                              Must be either non-existent or empty.
* param publishSession        The community session.
* param metadataHandler       Optional. Gets called when staging the composite and can be used to modify
*                              the metadata of the to-be-published composite. Notice that this method gets called
*                              on a background thread.
* param queue                 Optional parameter. If not nil queue determines the operation queue the completion handler
*                              gets executed on.
* param handler               Gets called when the publish operation has completed or failed.
*
* return                      An AdobeNetworkHTTPRequest object that can be used to track progress, adjust the priority
*                              of the publish operation and to cancel it.
*
* note                        The push operation uses stageDirPath to prepare a composite that can be pushed to the
*                              publish service. It doesn't ever delete stageDirPath or its contents. It is the caller's
*                              responsibility to delete stageDirPath when no longer needed, i.e. when the publish
*                              operation has succeeded or when it fails with an AdobeDCXErrorInvalidStageDirectory
*                              error. Otherwise the caller can keep stageDirPath around and resume the publish operation
*                              at a later point in time.
*
* note                        At this point updatePublishedComposite: is not atomic if you specify a new publication record.
*                              This means that there is a chance that the update of the published composite succeeds but
*                              the update of the publication record (e.g. the artwork) does not.
*
*/
+ (AdobeNetworkHTTPRequest*)updatePublishedComposite:(AdobeDCXComposite*)publishedComposite
from:(AdobeDCXComposite*)modifiedComposite
remixData:(AdobeRemixData*)remixData
publicationRecord:(id<AdobePublicationRecordProtocol>)publicationRecord
stageDirectory:(NSString*)stageDirPath
publishSession:(id<AdobeDCXPublishSessionProtocol,AdobeDCXTransferSessionProtocol>)publishSession
requestPriority:(NSOperationQueuePriority)priority
metadataHandler:(AdobeDCXPublishMetadataHandler)metadataHandler
handlerQueue:(NSOperationQueue *)queue
completionHandler:(AdobeDCXPublishCompletionHandler)handler;

/**
* brief Resumes the publish operation of a previously failed publishComposite: or updatePublishedComposite: operation.
*
* param stageDirPath      The path of the directory that got used as staging directory in a previous attempt to publish
*                          the composite or to update a published composite.
* param publishSession    The community session.
* param queue             Optional parameter. If not nil queue determines the operation queue the completion handler
*                          gets executed on.
* param handler           Gets called when the publish operation has completed or failed.
*
* return                  An AdobeNetworkHTTPRequest object that can be used to track progress, adjust the priority
*                          of the publish operation and to cancel it.
*
* note                    If the operation fails with a AdobeDCXErrorInvalidStageDirectory error then the stage directory
*                          does not contain all necessary data and the publish operation cannot be resumed. In this case
*                          client should notify the user (if appropriate) and delete stageDirPath. Client also should delete
*                          stageDirPath upon success.
*/
+ (AdobeNetworkHTTPRequest*)resumePublishFromStageDirectory:(NSString*)stageDirPath
publishSession:(id<AdobeDCXPublishSessionProtocol,AdobeDCXTransferSessionProtocol>)publishSession
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionHandler:(AdobeDCXPublishCompletionHandler)handler;

#pragma mark - Remix

/**
* brief Pulls a copy of a published composite that is suitable for remixing to the specified local path
*
* param publishHref       The href of the published composite that will be resolved via the publishSession.
* param path              The local storage path in which the pulled copy of the composite will be saved.
* param stageDir          The path of the directory that gets used to stage the composite as it is pulled and updated.
*                          Must be either non-existent or empty.
* param publishSession    The community session.
* param queue             Optional parameter. If not nil queue determines the operation queue the completion handler
*                          gets executed on.
* param handler           Gets called when the publish operation has completed or failed.
*
* return                  An AdobeNetworkHTTPRequest object that can be used to track progress, adjust the priority
*                          of the publish operation and to cancel it.
*
* note                    The copy operation uses stageDirPath to prepare a composite that is pulled from the
*                          publish service. It doesn't ever delete stageDirPath or its contents. It is the caller's
*                          responsibility to delete stageDirPath when no longer needed, i.e. when the copy
*                          operation has succeeded or when it fails with an AdobeDCXErrorInvalidStageDirectory
*                          error. Otherwise the caller can keep stageDirPath around and resume the copy operation
*                          at a later point in time.
 */
+ (AdobeNetworkHTTPRequest*)remixPublishedCompositeAtHref:(NSString*)publishHref
toLocalPath:(NSString*)path
stageDirectory:(NSString*)stageDir
publishSession:(id<AdobeDCXPublishSessionProtocol,AdobeDCXTransferSessionProtocol>)publishSession
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionHandler:(AdobeDCXRemixCompletionHandler)handler;

/**
* brief Resumes the copy of a published composite using the staging directory from a previously interrupted call to
remixPublishedCompositeAtHref:... or resumeRemixPublishedCompositeFromStageDirectory:...
*
* param assetHref         The href of the published asset that will be resolved via the publishSession.
* param path              The local storage path in which the pulled copy of the composite will be saved.
* param stageDirPath      The path of the directory that got used as staging directory in a previous attempt to copy
*                          the composite.
* param publishSession    The community session.
* param queue             Optional parameter. If not nil queue determines the operation queue the completion handler
*                          gets executed on.
* param handler           Gets called when the publish operation has completed or failed.
*
* return                  An AdobeNetworkHTTPRequest object that can be used to track progress, adjust the priority
*                          of the publish operation and to cancel it.
*
* note                    The copy operation uses stageDirPath to prepare a composite that is pulled from the
*                          publish service. It doesn't ever delete stageDirPath or its contents. It is the caller's
*                          responsibility to delete stageDirPath when no longer needed, i.e. when the copy
*                          operation has succeeded or when it fails with an AdobeDCXErrorInvalidStageDirectory
*                          error. Otherwise the caller can keep stageDirPath around and resume the copy operation
*                          at a later point in time.
*/
+ (AdobeNetworkHTTPRequest*)resumeRemixPublishedCompositeFromStageDirectory:(NSString*)stageDirPath
toLocalPath:(NSString*)path
publishSession:(AdobeCommunitySession*)publishSession
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionHandler:(AdobeDCXRemixCompletionHandler)handler;

#pragma mark - Snapshot

/**
* brief  Writes a snapshot representation of a composite to the specified directory
*
* param branch    The AdobeDCXCompositeBranch to be used as the source for the snapshot
* param snapshotPath Destination path in which snapshot will be written
* param mimetype  The internet media type identifying the type of the snapshot and to be written to the mimetype file
* param queue     Optional parameter. If not nil queue determines the operation queue handler gets executed on.
* param handler   Block called when the snapshot operation completes .
* return          An NSProgress that may be used to cancel the operation or receive progress events
*/
+ (NSProgress*) writeSnapshotOfCompositeBranch:(AdobeDCXCompositeBranch *)branch
toPath:(NSString*)snapshotPath
mimetype:(NSString*)mimetype
handlerQueue:(NSOperationQueue*)queue
completionHandler:(void(^)(BOOL success, NSError *error))handler;

/**
* brief  Writes a snapshot representation of a composite to a UCF archive file
*
* param branch    The AdobeDCXCompositeBranch to be used as the source for the snapshot
* param archivePath  Destination filename to which a UCF archive containing the snapshot will be written
* param mimetype  The internet media type identifying the type of the snapshot and to be written to the mimetype file
* param queue     Optional parameter. If not nil queue determines the operation queue handler gets executed on.
* param handler   Block called when the snapshot operation completes .
* return          An NSProgress that may be used to cancel the operation or receive progress events
*/
+ (NSProgress*) writeSnapshotOfCompositeBranch:(AdobeDCXCompositeBranch *)branch
toArchiveFileAtPath:(NSString*)archivePath
mimetype:(NSString*)mimetype
handlerQueue:(NSOperationQueue*)queue
completionHandler:(void(^)(BOOL success, NSError *error))handler;


/**
* brief  Creates a new composite from a snapshot representation located at snapshotPath
*
* param  compositePath The path of the new composite
* param  snapshotPath  The path to an existing snapshot - either a directory or a UCF archive file
* param queue     Optional parameter. If not nil queue determines the operation queue handler gets executed on.
* param handler   Block called when the snapshot operation completes .
* return          An NSProgress that may be used to cancel the operation or receive progress events
*/
+ (NSProgress*) createCompositeAtPath:(NSString*)compositePath
fromSnapshotAtPath:(NSString*)snapshotPath
handlerQueue:(NSOperationQueue *)queue
completionHandler:(void(^)(AdobeDCXComposite *composite, NSString *mimetype, NSError *error))handler;

@end

#endif
