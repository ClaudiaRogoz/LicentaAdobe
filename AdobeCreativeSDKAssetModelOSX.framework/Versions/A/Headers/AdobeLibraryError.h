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

#ifndef AdobeLibraryErrorHeader
#define AdobeLibraryErrorHeader

#import <Foundation/Foundation.h>

/** The domain for Adobe Library errors */
extern NSString *const AdobeLibraryErrorDomain;

/** The key for error details */
extern NSString *const AdobeLibraryErrorDetailsKey;

/**
 * Error codes for the AdobeLibraryErrorDomain.
 */
typedef NS_ENUM (NSInteger, AdobeLibraryErrorCode)
{
    /**
     * The local root folder for libraries and renditions could not be created.
     */
    AdobeLibraryErrorLocalRootCreateFailure = 0,

    /**
     * One or more of the parmaeters passed in is invalid.
     */
    AdobeLibraryErrorBadParameter = 1,

    /**
     * Operation is not supported.
     */
    AdobeLibraryErrorOperationNotSupported = 2,

    /**
     * AdobeLibraryManager startup has not been called or did not succeed.
     */
    AdobeLibraryErrorStartupFailure = 3,

    /**
     * The local folder for a new library could not be created.
     */
    AdobeLibraryErrorLocalLibraryCreateFailure = 4,

    /**
     * The local library does not exist.
     */
    AdobeLibraryErrorLocalLibraryDoesNotExist = 5,

    /**
     * Error creating the library.
     */
    AdobeLibraryErrorLibraryCreateFailure = 6,

    /**
     * The library has not been initialized.
     */
    AdobeLibraryErrorLibraryNotInitialized = 7,

    /**
     * Error occurred while saving the library.
     */
    AdobeLibraryErrorLibraryFailedToSave = 8,

    /**
     * endChanges was called without a matching beginChanges.
     */
    AdobeLibraryErrorLibraryEndWithoutBegin = 9,

    /**
     * The category does not exist.
     */
    AdobeLibraryErrorCategoryDoesNotExist = 10,

    /**
     * Could not add the category to the library. It may already exist or is invalid.
     */
    AdobeLibraryErrorLibraryFailedToAddCategory = 11,

    /**
     * Could not add the element to the library. Element with the same id exists or the element is invalid.
     */
    AdobeLibraryErrorLibraryFailedToAddElement = 12,

    /**
     * Could not add the element to the library because the library contains the maximum number of elements.
     */
    AdobeLibraryErrorLibraryMaximumElementsReached = 13,

    /**
     * The specified index is out of range.
     */
    AdobeLibraryErrorLibraryIndexOutOfRange = 14,

    /**
     * The element does not exist.
     */
    AdobeLibraryErrorElementDoesNotExist = 15,

    /**
     * Could not add the representation to the element.
     */
    AdobeLibraryErrorLibraryFailedToAddRepresentation = 16,

    /**
     * The representation does not exist.
     */
    AdobeLibraryErrorRepresentationDoesNotExist = 17,

    /**
     * The representation does not have a file.
     */
    AdobeLibraryErrorRepresentationHasNoFile = 18,

    /**
     * The key for the custom value is a reserved key word.
     */
    AdobeLibraryErrorRepresentationReservedKey = 19,

    /**
     * The element must have one and only one primary representation.
     * If you get this error when adding a representation, make sure you add the primary
     * representation first.
     */
    AdobeLibraryErrorElementMustHaveOnePrimaryRepresentation = 20,

    /**
     * The rendition could not be copied. See underlying error for details.
     */
    AdobeLibraryErrorCopyingRenditionFile = 21,

    /**
     * Failed to delete the library on the server. See underlying error for more info.
     * The library id is in the error details key.
     */
    AdobeLibraryErrorDeleteLibraryOnServerFailed = 22,

    /**
     * The key does not contain namespace.
     */
    AdobeLibraryErrorNamespaceNotFoundForKey = 23,

    /**
     * Failed to download the representation asset from the server.
     * See underlying error for more information.
     */
    AdobeLibraryErrorDownloadingRepresentationAsset = 24,

    /**
     * Failed to merge the downloaded library from the cloud with the local version.
     * This should not occur, please file a bug report.
     */
    AdobeLibraryErrorInternalMergeDownloadedLibrary = 25,

    /**
     * The rendition could not be downloaded from the server. See underlying error for details.
     */
    AdobeLibraryErrorDownloadingRenditionFile = 26,

    /**
     * AdobeLibraryManager startup has already been called. You must call shutdown first
     *   in order to start a new session.
     */
    AdobeLibraryErrorStartupAlreadyStarted = 27,

    /**
     * A library that was changed locally failed to be synced because the library was
     *   deleted on the server. The library has been assigned a new id and the sync will
     *   automatically be re-attempted. The given library has the new id, and the old
     *   library id is in the error details.
     */
    AdobeLibraryErrorSyncLibraryDeletedOnServer = 28,

    /**
     * AdobeLibraryManager cannot sync because the sync has been disabled by the client.
     * Call AdobeLibraryManager#syncEnabled in order to re-enable sync.
     */
    AdobeLibraryErrorSyncNotEnabled = 29,

    /**
     * AdobeLibraryManager cannot sync because either the network is not reachable or sync is not allowed
     * for the current network status. @see AdobeLibraryManager#syncAllowedByNetworkStatusMask
     */
    AdobeLibraryErrorSyncNotAvailableDueToNetwork = 30,

    /**
     * AdobeLibraryManager cannot sync because the manager is suspended due to an authentication failure.
     * This is because either no valid user session has been passed during startup or the user session
     * has expired after the manager has been started. Clients should call AdobeLibraryManager#unsuspendSyncDueToNewAuthenticationStatus
     * to unsuspend the manager after they are sure the storageSession passed to the manager has now a valid authentication token.
     */
    AdobeLibraryErrorSyncNotAvailableDueToUserSession = 31,

    /**
     * AdobeLibraryManager cannot write a downloaded file. There could be a disc space issue. Clients
     * should clean up some files.
     */
    AdobeLibraryErrorSyncWriteFailure = 32,

    /**
     * An unexpected error occurred during sync. See underlying error for details.
     */
    AdobeLibraryErrorSyncUnexpectedError = 33,

    /**
     * This error occurs when the library composite is either corrupt or invalid.
     */
    AdobeLibraryErrorInvalidLibraryComposite = 34,

    /**
     * This error occurs when none of the representations of the element can be used to generate a rendition.
     */
    AdobeLibraryErrorNoRenditionCandidate = 35,

    /**
     * This error occurs if the client tries to leave a library that is owned by the current user.
     * A user can only leave libraries that are shared with them by other users.
     * Clients should call AdobeLibraryManager#deleteLibraryWithId instead.
     */
    AdobeLibraryErrorCannotLeaveLibraryOwnedByUser = 36,

    /**
     * This error occurs if the client tries to delete a library that is shared with the current user.
     * A library that is shared with the user can only be left, not deleted.
     * Clients should call AdobeLibraryManager#leaveSharedLibraryWithId instead.
     */
    AdobeLibraryErrorCannotDeleteLibrarySharedWithUser = 37,

    /**
     * Failed to leave an shared (incoming) library.
     * See underlying error for more information.
     */
    AdobeLibraryErrorLeavingSharedLibrary = 38,

    /**
     * Failed to shutdown the manager because there are still active delegates attached to the manager.
     */
    AdobeLibraryErrorCannotShutdownDelegatesExist = 39,
    
    /**
     * Error code for an invalid URL.
     */
    AdobeLibraryErrorURLNotValid = 40,
    
    /**
     * Error code for a URL that is not part of the allowed whitelist.
     */
    AdobeLibraryErrorURLNotAllowed = 41,
    
    /**
     * The element copy failed. See the underlying error for more details.
     */
    AdobeLibraryErrorElementCopyFailed = 42,
    
    /**
     * The element is not a valid AdobeLibraryElement.
     */
    AdobeLibraryErrorInvalidElement = 43,

    /**
     * Error code for trying to modify a read only library
     */
    AdobeLibraryErrorNoWriteAccess = 44,
    
    /**
     * Error while trying to sync bookmarks to the cloud.
     */
    AdobeLibraryErrorSyncBookmarksToCloud = 45
};

#endif
