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

#ifndef AdobeLibraryManagerHeader
#define AdobeLibraryManagerHeader

#import <Foundation/Foundation.h>

@class AdobeLibraryComposite;
@class AdobeLibraryElement;
@class AdobeLibraryRepresentation;
@class AdobeStorageSession;
@class AdobeLibraryDelegateStartupOptions;

@protocol AdobeLibraryDelegate;
@protocol AdobeDCXSyncSessionProtocol;
@protocol AdobeDCXTransferSessionProtocol;

/**
 * Represents a sync status.
 */
@interface AdobeLibrarySyncStatus : NSObject

/** The last time a sync was successfully completed. */
@property (readonly, nonatomic) NSDate *lastSyncTime;

/** Whether or not a sync is currently in progress. */
@property (readonly, nonatomic, getter = isSyncing) BOOL syncing;

@end

/**
 * AdobeLibraryManager is a shared instance that manages libraries and the syncing operations. It can be
 * used to set filtering options for what gets synced in libraries, for controlling sync operations, as
 * well as for getting, creating, and deleting libraries.
 */
@interface AdobeLibraryManager : NSObject

/**
 * Indicates whether the manager is allowed to do a sync based on the known network status.
 */
@property (nonatomic, readonly, getter = isSyncAllowedByNetworkStatus) BOOL syncAllowedByNetworkStatus;

/**
 * A bitmask of network statuses that will allow the manager to perform its sync operation. The default value is
 * AdobeNetworkReachableViaWiFi which means that the manager would only do sync when the WiFi is available.
 * See the declaration of AdobeNetworkStatus for other possible values.
 */
@property (nonatomic, readwrite) NSUInteger syncAllowedByNetworkStatusMask;

/**
 * Specifies whether the sync should be enabled or not. Setting this to false will cause the manager not to sync at all (auto or manual).
 * The default value is YES, and clients are responsible to setting this back to YES, if they set it to NO.
 */
@property (nonatomic, getter = isSyncEnabled) BOOL syncEnabled;

/**
 * Tells the library manager to generate thumbnails locally when it can instead of using the 
 * imaging service which requires network calls.
 */
@property (nonatomic, readwrite) BOOL generateLocalThumbnails;

/**
 * \brief Get the global shared instance of this singleton.
 *
 * \return shared AdobeLibraryManager instance
 */
+ (AdobeLibraryManager *)sharedInstance;

/**
 * \brief A utility method to delete the local library files in the given root libraries folder.
 *              You can use this method when the user logs out and logs in as a different user and you wish
 *              to clean up the local design library folder.
 * \param rootFolderPath	The local root folder for where the libraries and renditions are stored.
 * \param errorPtr		An optional pointer to an error to receive error information.
 */
+ (void)removeLocalLibraryFilesInRootFolder:(NSString *)rootFolderPath withError:(NSError **)errorPtr;

/**
 * \brief Startup the Adobe Library service.
 *
 * \param rootFolder The root folder to use for storing libraries and their content.
 * \param errorPtr An optional pointer to an error to receive startup error information.
 *
 * \see AdobeLibraryManager.h for the syncEnabled synthesized set method.
 *
 * \return An error object with the status of the startup operation.
 */
- (BOOL)startWithFolder:(NSString *)rootFolder
               andError:(NSError **)errorPtr;

/**
 * \brief Registers a delegate with the given startup options.
 * \param delegate	The delegate instance to register
 * \param options	Startup options to use by the manager. The manager merges the options if there are more than one delegate registered.
 */
- (void)registerDelegate:(id<AdobeLibraryDelegate>)delegate options:(AdobeLibraryDelegateStartupOptions *)options;

/**
 * \brief Deregisters a delegate. The manager automatically shutdowns if there is no more delegate registered after deregistering a delegate.
 * \param delegate	The delegate instance to deregister
 */
- (void)deregisterDelegate:(id<AdobeLibraryDelegate>)delegate;

/**
 * \brief Shut down the design library manager.
 *
 * \param errorPtr Gets set if an error occurs while shutting down the manager.
 *
 * \return YES if the manager is shutdown successfully, NO otherwise.
 */
- (BOOL)shutdownWithError:(NSError **)errorPtr;

/**
 * \brief Force shut down the design library manager.Manager will be shutdown
 * even if there is active delegates.
 */
- (void)shutdown;

/**
 * \brief Returns whether or not the manager has been started.
 *
 * \return YES if the manager has been successfully started up, otherwise NO.
 */
- (BOOL)isStarted;

/**
 * \brief Get all library composites from all library collections.
 *
 * \return an array of AdobeLibraryComposite objects.
 */
- (NSArray *)libraries;


/**
 * \brief Get all library composites from all library collections for the given delegate
 * and its startup options. The delegate can choose to filter out bookmarked libraries.
 *
 * \return an array of AdobeLibraryComposite objects.
 */
- (NSArray *) libraries:(id<AdobeLibraryDelegate>)delegate;

/**
 * \brief Get the library composite with the given id.
 *
 * \param libraryId   The id of the library composite to get.
 *
 * \return that library with the given id or nil if it is not found.
 */
- (AdobeLibraryComposite *)libraryWithId:(NSString *)libraryId;

/**
 * \brief Returns the default library composite. The default library is considered to be the oldest
 * library based on the creation date of each library. A library that has been shared with the user
 * cannot be the default library. If this method returns nil, clients may create a new default
 * library. The new library should be named "My Library" for consistency with other applications.
 *
 * \return the default library composite or nil if no library can be found.
 */
- (AdobeLibraryComposite *)getDefaultLibrary;

/**
 * \brief Create a new library composite with the given name.
 *
 * \param name        The name to use for the new library composite.
 * \param errorPtr    Gets set if an error occurs while creating the library composite.
 *
 * \return the newly created library composite or nil if an error occurs during creation.
 */
- (AdobeLibraryComposite *)newLibraryWithName:(NSString *)name andError:(NSError **)errorPtr;

/**
 * \brief Leave the shared library composite with the given id.
 *
 * \param libraryId   The id of the library composite to leave.
 * \param errorPtr    Gets set if an error occurs while leaving the library.
 *
 * \return YES if the library is left successfully, NO otherwise.
 */
- (BOOL)leaveSharedLibraryWithId:(NSString *)libraryId andError:(NSError **)errorPtr;

/**
 * \brief Delete the library composite with the given id.
 *
 * \param libraryId   The id of the library composite to delete.
 * \param errorPtr    Gets set if an error occurs while deleting the library.
 *
 * \return YES if the library is deleted successfully, NO otherwise.
 */
- (BOOL)deleteLibraryWithId:(NSString *)libraryId andError:(NSError **)errorPtr;

/**
 * \brief Returns whether or not the manager can perform a sync. This considers all the factors
 * (network status, authentication status, syncEnabled flag) while determining whether or not
 * the manager can sync.
 *
 * \return YES if the manager can sync, NO otherwise.
 */
- (BOOL)canSync;

/**
 * \brief Kick of a sync operation with the cloud. This should be called by the client at
 *              appropriate UI events such as a refresh button, activate, etc.
 * \return	YES if a sync was successfully kicked off, otherwise NO. If a sync is already
 *                      in progress this returns YES. If there is an error and sync cannot be started
 *                      it returns NO and an error will be sent in the onSyncError delegate call.
 */
- (BOOL)sync;

/**
 * \brief Get the current sync status.
 *
 * \return the current sync status.
 */
- (AdobeLibrarySyncStatus *)getSyncStatus;

/**
 * \brief Returns whether or not the sync is suspended due to an authentication failure.
 * If the manager receives a AdobeNetworkErrorAuthenticationFailed error from any of its
 * network requests, it suspends itself until AdobeLibraryManager#unsuspendSyncDueToNewAuthenticationStatus
 * method is called by the client.
 *
 * \return YES if the sync has been suspended due to an authentication error, NO otherwise.
 */
- (BOOL)isSyncSuspendedDueToAuthenticationError;

/**
 * \brief Unsuspends the sync status of the manager so that the manager can sync again.
 * This method should be called when the manager is suspended and the client is sure that
 * the corresponding storageSession has now a valid authentication token to use with network requests.
 */
- (void)unsuspendSyncDueToNewAuthenticationStatus;

/**
 * \brief Reports an event that indicates a library element was used in the client app.
 * The purpose of this method is to collect usage data from clients on which elements
 * are used. This should be called whenever a library element is used in the client app.
 *
 * \param library library that contains the used element
 * \param element element that is used/applied in the client app
 * \param representation representation of the element that is used (optional)
 * \param operationType operation type of which the element used with (such as setStokeColor for color elements) (optional)
 */
- (void)reportElementUsed:(AdobeLibraryComposite *)library
                  element:(AdobeLibraryElement *)element
           representation:(AdobeLibraryRepresentation *)representation
            operationType:(NSString *)operationType;
@end

#endif
