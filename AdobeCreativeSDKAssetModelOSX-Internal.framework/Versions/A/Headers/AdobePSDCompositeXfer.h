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

#ifndef AdobePSDCompositeXferHeader
#define AdobePSDCompositeXferHeader

#import <Foundation/Foundation.h>

@class AdobePSDComposite;
@class AdobePSDCompositeBranch;
@class AdobeNetworkHTTPRequest;

@protocol AdobePSDSessionProtocol;
@protocol AdobeDCXTransferSessionProtocol;

/**
* Implementation of the push & pull logic for PSD composites.
* TBD: EXPANDED
*/
@interface AdobePSDCompositeXfer : NSObject

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations" // suppress warnings about deprecated class AdobePSDComposite

#pragma mark Completion Handler Types

/**
* brief Type defining the signature of a completion handler for asynchronous push.
*/
typedef void (^AdobePSDPushCompletionHandler)(BOOL, NSError *);

/**
* brief Type defining the signature of a completion handler for asynchronous pull.
*/
typedef void (^AdobePSDPullCompletionHandler)(AdobePSDCompositeBranch *, NSError *);

#pragma mark - Push - Asynchronous

/**
* brief The first step of a PSD composite push. Updates or creates the PSD and its composite
* representation on the server and (if successful) propulates the pushed branch of the composite with
* the results of the push.
*
* param composite       The AdobePSDComposite to push.
* param overwrite       Whether to forcibly overwrite an already existing composite. Set this when the previous
*                      attempt to push has failed with a AdobeDCXErrorCompositeAlreadyExists error and the
*                      user has confirmed that it it OK to overwrite the composite.
* param imageSession    The session used to update the PSD.
* param storageSession  The session used to push components to.
* param priority        The relative priority of the pull.
* param queue           Optional parameter. If not nil queue determines the operation queue handler
*                      gets executed on.
* param handler         Gets called when the push has completed.
*
* return                A AdobeNetworkHTTPRequest object that can be used to track progress, adjust
*                      the priority of the pull and to cancel it.
*
* This method reads the local committed branch of the composite and analyzes it in order to determine
* whether anything has changed and which of its component assets need to be uploaded. If all of the necessary
* uploads succeed it does a final upload of the manifest (updated with links, etags, checksums and
* states of all the components) which will trigger the creation or update of the orginal PSD on the
* server.
*
* note On success the composite has a second branch which is accessible via the pushed property and
* the caller needs to call acceptPushWithError: on the PSD composite in order to update the current
* into the current in memory and into the manifest file on disk with the server state that is captured in the
* pushed branch.
*/
+ (AdobeNetworkHTTPRequest *)pushPSDComposite:(AdobePSDComposite *)composite
overwriteExisting:(BOOL)overwrite
imageSession:(id<AdobePSDSessionProtocol>) imageSession
storageSession:(id<AdobeDCXTransferSessionProtocol>) storageSession
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionHandler:(AdobePSDPushCompletionHandler)handler;

#pragma mark - Push - Synchronous

/**
* brief Synchronous version of pushPSDComposite:imageSession:storageSession:requestPriority:handlerQueue:completionHandler:
*
* param composite       The AdobePSDComposite to push.
* param overwrite       Whether to forcibly overwrite an already existing composite. Set this when the previous
*                      attempt to push has failed with a AdobeDCXErrorCompositeAlreadyExists error and the
*                      user has confirmed that it it OK to overwrite the composite.
* param imageSession    The session used to update the PSD.
* param storageSession  The session used to push components to.
* param priority        The relative priority of the pull.
* param errorPtr        Gets set to an NSError if the operation fails.
*
* return                YES if successful.
*/
+ (BOOL)pushPSDComposite:(AdobePSDComposite *)composite
overwriteExisting:(BOOL)overwrite
imageSession:(id<AdobePSDSessionProtocol>) imageSession
storageSession:(id<AdobeDCXTransferSessionProtocol>) storageSession
requestPriority:(NSOperationQueuePriority)priority
withError:(NSError **)errorPtr;


#pragma mark - Pull - Asynchronous

/**
* brief Downloads the PSD composite with all its component assets as it currently exists on the server
* and stores it in the pulled branch of the composite. The copy can be used to atomically update the
* local current branch of the composite and/or to resolve conflicts between the two branches.
*
* param composite   The local AdobePSDComposite.
* param imageSession     The DCX session to use for the required http requests.
* param storageSession  The session used to push components to.
* param priority    The relative priority of the pull.
* param queue       Optional parameter. If not nil queue determines the operation queue handler gets executed on.
* param handler     Gets called when the pull has completed. It gets passed the pulled AdobePSDCompositeBranch
*                  if the pull succeeds otherwise the caller should check errorPtr to determine
*                  whether there has been a problem.
*
* return            An AdobeNetworkHTTPRequest object that can be used to track progress, adjust the priority
*                  of the pull and to cancel it.
*
* note On success the composite has a second branch which is accessible via the pulled property.
* The caller needs to either call resolvePulledBranchWithError: on the PSD composite or (if it has local changes
* in the current branch) merge the two branches.
*/
+ (AdobeNetworkHTTPRequest *)pullPSDComposite:(AdobePSDComposite *)composite
imageSession:(id<AdobePSDSessionProtocol>) imageSession
storageSession:(id<AdobeDCXTransferSessionProtocol>) storageSession
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionHandler:(AdobePSDPullCompletionHandler)handler;

/**
* brief Downloads a minimal version of the specified PSD composite (i.e. its manifest and its metadata)
* as it currently exists on the server and stores it in the pulled branch of the composite,
* which can be used to selectively pull specific layer components and/or add new layers to the composite.
*
* param composite       The AdobePSDComposite to pull.
* param imageSession    The DCX session to use for the required http requests.
* param storageSession  The DCX session to use to determine the composite href.
* param priority        The relative priority of the pull.
* param queue           Optional parameter. If not nil queue determines the operation queue handler
*                      gets executed on.
* param handler         Gets called when the pull has completed. It gets passed the pulled AdobePSDCompositeBranch
*                      if the pull succeeds otherwise the caller should check errorPtr to determine
*                      whether there has been a problem.
*
* return                An AdobeNetworkHTTPRequest object that can be used to track progress, adjust the priority
*                      of the pull and to cancel it.
*
* note On success the composite has a second branch which is accessible via the pulled property.
* The caller needs to either call resolvePulledBranchWithError: on the PSD composite or (if it has local changes
* in the current branch) merge the two branches.
*/
+ (AdobeNetworkHTTPRequest *)pullMinimalPSDComposite:(AdobePSDComposite *)composite
imageSession:(id<AdobePSDSessionProtocol>) imageSession
storageSession:(id<AdobeDCXTransferSessionProtocol>) storageSession
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionHandler:(AdobePSDPullCompletionHandler)handler;

/**
* brief Downloads the components for the specificed layers of the composite. Components that already
* exist locally and haven't changed on the server will not get downloaded again.
*
* param layers      Optional list of layers for which to pull the components. Pass nil to pull all components.
* param recursively Whether the components of child layers should be loaded as well. Gets ignored if layers is nil.
* param composite   The local AdobePSDComposite.
* param session     The DCX session to use for the required http requests.
* param priority    The relative priority of the pull.
* param queue       Optional parameter. If not nil queue determines the operation queue handler gets executed on.
* param handler     Gets called when the pull has completed. It gets passed the pulled or current
*                  AdobePSDCompositeBranch if the pull succeeds otherwise the caller should check
*                  errorPtr to determine whether there has been a problem.
*
* return            An AdobeNetworkHTTPRequest object that can be used to track progress, adjust the priority
*                  of the pull and to cancel it.
*
* note If this method gets called with a composite that has a pulled branch the components will be
* loaded for that branch and it is that branch that will get passed to the completion handler. You can
* also call this method with a composite that doesn't have a pulled branch but rather an incomplete
* current branch in order to pull down additional components. In that case the current branch will be
* passed to the completion handler.
*/
+ (AdobeNetworkHTTPRequest *)pullComponentsForLayers:(NSArray *)layers
recursively:(BOOL)recursively
ofPSDComposite:(AdobePSDComposite *)composite
usingSession:(id<AdobeDCXTransferSessionProtocol>) session
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionHandler:(AdobePSDPullCompletionHandler)handler;

#pragma mark Pull - Synchronous

/**
* brief Synchronous version of @see pullPSDComposite:from:imageSession:storageSession:requestPriority:handlerQueue:completionHandler:
*
* param composite      The AdobePSDComposite to pull.
* param imageSession   The DCX session to use to trigger the conversion to a composite.
* param storageSession The DCX session to use to get the components.
* param priority       The relative priority of the pull.
* param errorPtr       Gets set to an NSError if an error occurs.
*
* return The AdobePSDCompositeBranch of the new version if the pull succeeds. If nil the caller should check
* errorPtr in order to determine whether there has been a problem. If the method returns nil and there
* no error it means that there were no new changes to pull and that the current version of the composite
* is in sync with the composite on the server.
*/
+ (AdobePSDCompositeBranch *)pullPSDComposite:(AdobePSDComposite *)composite
imageSession:(id<AdobePSDSessionProtocol>) imageSession
storageSession:(id<AdobeDCXTransferSessionProtocol>) storageSession
requestPriority:(NSOperationQueuePriority)priority
error:(NSError **)errorPtr;

/**
* brief Synchronous version of @see pullMinimalPSDComposite:imageSession:storageSession:requestPriority:handlerQueue:
*
* param composite      The AdobePSDComposite to pull.
* param imageSession   The DCX session to use to trigger the conversion to a composite.
* param storageSession The DCX session to use to determine the composite href.
* param priority       The relative priority of the pull.
* param errorPtr       Gets set to an NSError if an error occurs.
*
* return The AdobePSDCompositeBranch of the new version if the pull succeeds. If nil the caller should check
* errorPtr in order to determine whether there has been a problem. If the method returns nil and there
* no error it means that there were no new changes to pull and that the current version of the composite
* is in sync with the composite on the server.
*/
+ (AdobePSDCompositeBranch *)pullMinimalPSDComposite:(AdobePSDComposite *)composite
imageSession:(id<AdobePSDSessionProtocol>) imageSession
storageSession:(id<AdobeDCXTransferSessionProtocol>) storageSession
requestPriority:(NSOperationQueuePriority)priority
error:(NSError **)errorPtr;
/**
* brief Synchronous version of pullComponentsForLayers:ofPSDComposite:usingSession:requestPriority:handlerQueue:completionHandler:
*
* param layers      Optional list of layers for which to pull the components. Pass nil to pull all components.
* param recursively Whether the components of child layers should be loaded as well. Gets ignored if layers is nil.
* param composite   The AdobePSDComposite to pull the components for.
* param session     The DCX session to use for the required http requests.
* param priority    The relative priority of the pull.
* param errorPtr    Gets set to an NSError if an error occurs.
*
* return            The pulled or current AdobePSDCompositeBranch if the pull succeeds.
*/
+ (AdobePSDCompositeBranch *)pullComponentsForLayers:(NSArray *)layers
recursively:(BOOL)recursively
ofComposite:(AdobePSDComposite *)composite
usingSession:(id<AdobeDCXTransferSessionProtocol>) session
requestPriority:(NSOperationQueuePriority)priority
error:(NSError **)errorPtr;

#pragma clang diagnostic pop

@end

#endif
