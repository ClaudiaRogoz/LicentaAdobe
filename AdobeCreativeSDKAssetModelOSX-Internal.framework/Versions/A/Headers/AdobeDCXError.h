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

#ifndef AdobeDCXErrorHeader
#define AdobeDCXErrorHeader

#import <Foundation/Foundation.h>

/** The domain for DCX errors */
extern NSString *const AdobeDCXErrorDomain;

/**
* brief Error codes for the DCX error domain.
*/
typedef NS_ENUM (NSInteger, AdobeDCXErrorCode)
{
/**
* brief The manifest could not be read from local file system.
*
* The NSUnderlyingErrorKey and AdobeErrorPathKey entries in userInfo often contain
* more information about the cause of this error.
*/
AdobeDCXErrorManifestReadFailure = 0,

/**
* brief The final write of the manifest to local storage has failed. When this occurs
* during a push it means that the changes have been successfully uploaded to the server,
* but the final write of the manifest file has failed so that it is now out of sync
* with the server.
*
* The NSUnderlyingErrorKey and AdobeErrorPathKey entries in userInfo often contain
* more information about the cause of this error.
*
* Once the problem with the local storage has been resolved a pull can be used to update
* the local copy of the composite.
*/
AdobeDCXErrorManifestFinalWriteFailure = 1,

/**
* brief Writing= the manifest to local storage has failed.
*
* The NSUnderlyingErrorKey and AdobeErrorPathKey entries in userInfo often contain
* more information about the cause of this error.
*/
AdobeDCXErrorManifestWriteFailure = 2,

/**
* brief A local file or server-provided resource that supposedly contains a valid manifest
* could not be parsed as such.
*
* The AdobeErrorDetailsStringKey, NSUnderlyingErrorKey and AdobeErrorPathKey entries in userInfo often
* contain more information about the cause of this error.
*/
AdobeDCXErrorInvalidManifest = 3,

/**
* brief A local file that supposedly contains a valid manifest could not be parsed
* as such.
*
* The AdobeErrorDetailsStringKey, NSUnderlyingErrorKey and AdobeErrorPathKey entries in userInfo often
* contain more information about the cause of this error.
*/
AdobeDCXErrorInvalidLocalManifest = 4,

/**
* brief A server-provided resource that supposedly contains a valid manifest
* could not be parsed as such.
*
* The AdobeErrorDetailsStringKey, NSUnderlyingErrorKey and AdobeErrorPathKey entries in userInfo often
* contain more information about the cause of this error.
*/
AdobeDCXErrorInvalidRemoteManifest = 5,

/**
* brief The composite on the server doesn't contain a manifest.
*
* This typically means that either the composite is currently in the process of
* being created or that the creation of the composite on the server has failed.
*/
AdobeDCXErrorMissingManifest = 6,

/**
* brief The asset file for a component could not be read from local file system.
*
* The NSUnderlyingErrorKey and AdobeErrorPathKey entries in userInfo often contain
* more information about the cause of this error.
*/
AdobeDCXErrorComponentReadFailure = 7,

/**
* brief Writing a component asset file to local storage has failed.
*
* The NSUnderlyingErrorKey and AdobeErrorPathKey entries in userInfo often contain
* more information about the cause of this error.
*/
AdobeDCXErrorComponentWriteFailure = 8,

/**
* brief Copying a component asset file has failed.
*
* The NSUnderlyingErrorKey and AdobeErrorPathKey entries in userInfo often contain
* more information about the cause of this error.
*/
AdobeDCXErrorComponentCopyFailure = 9,

/**
* brief A component referenced by the manifest is missing on the server.
*/
AdobeDCXErrorMissingComponentAsset = 10,

/**
* brief Trying to pull a AdobeDCXComposite that doesn't exist (any more?) on the server.
*
* The userInfo property of the error often contains additional information via
* the AdobeNetworkRequestURLKey, AdobeNetworkResponseDataKey, AdobeNetworkHTTPStatusKey, AdobeErrorResponseHeadersKey
* and NSUnderlyingErrorKey keys.
*/
AdobeDCXErrorUnknownComposite = 11,

/**
* brief Trying to pull or push a local composite that was previously deleted.
*
* In order to successfully upload the composite as a new composite on the server
* the caller should first unbind it.
*/
AdobeDCXErrorDeletedComposite = 12,

/**
* brief The journal data is not valid.
*
* This error occurs when you create a AdobeDCXPushJournal from either from a file. Check the AdobeAssetDetailsKey
* property in the userInfo dictionary of the error to get more details about the cause of the failure.
*/
AdobeDCXErrorInvalidJournal = 13,

/**
* brief The journal data is not complete.
*
* This error occurs when you try to merge or accept the results of a push if that push had
* not succeeded.
*/
AdobeDCXErrorIncompleteJournal = 14,

/**
* brief The attempt to store a copy of a manifest as base manifest has failed.
*
* This error indicates a file manager error during push or pull. See NSUnderlyingError and
* AdobeAssetPathErrorKey for details.
*/
AdobeDCXErrorFailedToStoreBaseManifest = 15,

/**
* brief An unimplemented function was called
*
* This error occurs if the DCX implementation calls a function that remains unimplemented.
*/
AdobeDCXErrorFunctionNotImplemented = 16,

/**
* brief A component of a composite has an invalid local storage path.
*/
AdobeDCXErrorInvalidLocalStoragePath = 17,

/**
* brief Trying to save a new composite over an existing composite on the server. You either
* need to pull the existing composite from the server and resolve any conflicts before pushing
* again, reset the identity of the composite to do the equivalent of a save as, or specify the
* overwrite flag on the next pull request.
*/
AdobeDCXErrorCompositeAlreadyExists = 18,

/**
* brief This error can happen when attempting to copy components and/or manifest child nodes
* between different branches of a composite if any of the components/child nodes already
* exists in the target branch.
*/
AdobeDCXErrorDuplicateId = 19,

/**
* brief A server operation was attempted on a composite that does not have an assigned href.
*/
AdobeDCXErrorCompositeHrefUnassigned = 20,

/**
* brief This error can happen when an operation on a branch would result into two items (nodes,
* components) with the same absolute path.
*/
AdobeDCXErrorDuplicatePath = 21,

/**
* brief A path of a manifest node or a component is invalid.
*/
AdobeDCXErrorInvalidPath = 22,

/**
* brief Cannot remove a component that has been locally modified from local storage
*/
AdobeDCXErrorCannotRemoveModifiedComponent = 23,

/**
* brief It is not permitted to delete a composite that has been shared with the current user.
*/
AdobeDCXErrorAttemptToDeleteIncomingShare = 24,

/**
* brief The component or child node ID could not be found.
*/
AdobeDCXErrorUnknownId = 25,

/**
* brief Metadata could not be parsed
*/
AdobeDCXErrorUnparsableMetadata = 26,

/**
* brief The specified local storage scheme is not supported.
*/
AdobeDCXErrorLocalStorageSchemeNotSupported = 27,

/**
* brief Problem with the component manager
*/
AdobeDCXInvalidComponentManager = 28,

/**
* brief An asynchronous DCX operation was cancelled.
*/
AdobeDCXErrorOperationCancelled = 29,

/**
* brief Tried to do something to a composite that isn't supported by the underlying service.
*/
AdobeDCXErrorOperationNotSupported = 30,

/**
* brief Returned by AdobeDCXCompositeXfer's publish operations when the composite could not get staged successfully
* or when the client tried to resume a publish operation with an incomplete stage. Clients should not attempt to
* resume the publish operation but rather inform the user and delete the stage directory. AdobeErrorDetailsStringKey and/or
* NSUnderlyingErrorKey might give more details.
*/
AdobeDCXErrorInvalidStageDirectory = 31,

/**
* brief Stage directory not empty.
*/
AdobeDCXErrorNonEmptyStageDirectory = 32,

/**
* brief Local component asset is missing.
*/
AdobeDCXErrorMissingComponentFile = 33,

/**
* brief An operation failed because a specified node does not meet the minimum requirements to be
* considered a DCX Element (i.e. have non-nil type and name properties)
*/
AdobeDCXErrorNodeIsNotElement = 34,

/**
* brief An attempt to update or abandon an element failed because the element is not currently pending on the branch.
*/
AdobeDCXErrorElementNotPendingOnBranch = 35,

/**
* brief A node, component, or element with the specified path could not be located on the branch or element.
*/
AdobeDCXErrorPathNotFound = 36,

/**
* brief Problem with the composite instance cache.
*/
AdobeDCXErrorInstanceCacheConflict = 37,

/**
* brief A manifest file for a composite branch does not exist in local storage.
*/
AdobeDCXErrorManifestFileNotFound = 38
};

#endif
