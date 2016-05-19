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

#ifndef AdobeDCXControllerHeader
#define AdobeDCXControllerHeader

#import <Foundation/Foundation.h>

#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeDCXComposite.h>
#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeDCXCompositeXfer.h>
#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeDCXSyncGroupMonitor.h>

@protocol AdobeDCXTransferSessionProtocol;
@protocol AdobeDCXSyncSessionProtocol;
@protocol AdobeDCXSyncGroupMonitorDelegate;

@class AdobeStorageResource;
@class AdobeStorageResourceCollection;
@class AdobeDCXComposite;
@class AdobeDCXCompositeBranch;
@class AdobeNetworkHTTPRequest;

@protocol AdobeDCXSyncSessionProtocol;
@protocol AdobeDCXTransferSessionProtocol;
@protocol AdobeDCXControllerDelegate;


/** The operational mode of the controller **/
typedef NS_ENUM (NSInteger, AdobeDCXControllerMode)
{
// Pulls and pushes changes from and to the server as needed in order to synchronize
// all known local and remote composites.  Periodically polls server to track new
// and updated composites to pull.
AdobeDCXControllerSyncing,

// Periodically polls server to track new and updated composites to pull, however
// no pushes or pulls are initiated.
AdobeDCXControllerPaused,

// No background server updates take place.  All sync activity is suspended.
AdobeDCXControllerStopped,
};

/** Synchronization phases in which a composite may exist **/
typedef NS_ENUM (NSInteger, AdobeDCXSyncPhase)
{
// Composite has no known local or remote changes
AdobeDCXSyncPhaseInSync,

// Controller has been informed of local changes and the composite should be pushed
AdobeDCXSyncPhasePush,

// Controller has detected server changes and and the composite should be pulled
AdobeDCXSyncPhasePull,

// Controller has been informed of a successful push operation and the composite
// should now be accepted
AdobeDCXSyncPhaseAccept,

// Controller has been informed of a successful pull operation and the composite
// should now be resolved
AdobeDCXSyncPhaseResolve,

// Controller has detected that the composite has been deleted from the server
// by another client
AdobeDCXSyncPhaseDelete,

// An error or invalid composite has led to an indeterminate sync phase
AdobeDCXSyncPhaseError
};

/**
* brief Manages the DCX synchronization cycle for a set of cloud assets (composites).
*
* An instance of AdobeDCXController keeps a set of local cloud assets synchronized with their
* server-stored counterparts. This is accomplished by executing the DCX synchronization algorithm
* for each asset any time it is changed either locally or remotely. The algorithm then executes until
* the asset is in sync; this may involve multiple pushes and pulls of the document. The details of the
* synchronization algorithm are documented at https://wiki.corp.adobe.com/display/dma/Synchronization.
*
* The synchronization algorithm is itself based on a state machine that describes how each asset moves
* through the four phases of synchornization. Instances of AdobeDCXController maintain the current
* state of each asset.
*
* AdobeDCXController relies heavily on cooperation with its client to coordinate synchronization.
* It monitors the associated service for remote changes, but must be explicitly informed of local changes.
* Similarly, it will automatically execute state transitions during the sync process when possible, but
* some transitions require the client to take action. The client is informed of such transitions via
* the delegate registered on the controller.
*/
@interface AdobeDCXController : NSObject <AdobeDCXSyncGroupMonitorDelegate>

/**
* brief Creates a new controller object.
*
* The controller object is responsible for managing the synchronization of composites
* contained within the specified sync group on the server, as well as composites that
* are discovered as the result of the client calling the scanLocalCompositesInPath method on this object.
*
* param syncGroupName  A string identifying a sync group that should be monitored for remote changes.
* param session   The DCX session to use.
* param delegate  The delegate object that should receive the notifications. The controller will keep a
* weak reference to it.
* param queue     The NSOperation queue on which the delegate methods are called.  If nil, then the
* application's main dispatch queue is used (i.e. the serial queue that executes tasks on the
* main thread.).
*
* return The newly created controller object.
*/
+ (id)controllerForSyncGroup:(NSString *)syncGroupName
withSession:(id<AdobeDCXTransferSessionProtocol, AdobeDCXSyncSessionProtocol>)session
withDelegate:(id<AdobeDCXControllerDelegate>)delegate
onQueue:(NSOperationQueue *)queue;


/**
* brief Controls the set of asynchronous background operations performed by the controller
*
* Defaults to AdobeDCXControllerStopped when a new instance of the controller is created.
*/
@property (nonatomic) AdobeDCXControllerMode mode;

/**
* Indicates whether the set of composites managed by this controller are known to be out of sync
* with the set of composites being tracked on the server.
*/
@property (nonatomic, readonly) BOOL isInSync;

/**
* The frequency at which the server is queried for updates to files in the sync group
* The default value, as well as the minimum frequency, is 60 seconds.  Changes to this
* value will only take effect when the mode of the controller is AdobeDCXControllerStopped.
*/
@property (nonatomic) NSTimeInterval serverPollingFrequency;

/**
* brief Force the controller's sync group monitor to update its view of the server contents
*/
- (void)forceServerPoll;

/**
* A bitmask of network statuses that will allow the controller to perform its sync operation
* as determined by its mode property.  The default value is AdobeNetworkReachableViaWiFi.
* See the declaration of AdobeNetworkStatus for other possible values.
*/
@property (nonatomic, readwrite) NSUInteger syncAllowedByNetworkStatusMask;

/**
* Indicates whether controller's sync operation is currently enabled based on the known
* network status.
*/
@property (nonatomic, readonly) BOOL syncAllowedByNetworkStatus;

/**
* If set to YES then the controller will create a background task to attempt to complete any
* in-progress sync operations when the application transitions to the background on an iOS device.
* The default value is YES, unless this class is being used from within an application extension,
* in which case it is NO and cannot be changed (an exception will be thrown).
*/
@property (nonatomic) BOOL permitBackgroundExecution;

/**
* The minimum number of seconds that the Controller should wait before requesting a push
* after a composite's most recent commit to disk. The default value is 0 (no delay).
*/
@property (nonatomic) NSUInteger delayPushBySeconds;

/**
* brief Scans a local directory for composites to be tracked and examines their state in
* order to determine what, if any, action the controller should request in order to sync the
* composite.
*
* scanLocalCompositesInPath can be called multiple times with different paths in order
* to track local composites residing in more than one local directory
*
* param path A local path used to store composites
*
* note scanLocalCompositesInPath or scanLocalComposites should be called at least once prior to
* setting the mode of the controller to anything other than AdobeDCXControllerStopped (it's default mode upon initialization).
* It should *only* be called while the 'mode' property is set to AdobeDCXControllerStopped.
*/
- (BOOL)scanLocalCompositesInPath:(NSString *)path withError:(NSError **)errorPtr;

/**
brief A deprecated version of the scanLocalCompositesInPath function that ignores its 'scheme' parameter and always assumes that
the local storage scheme uses the copy-on-write scheme (the only scheme that we currently support).

note Replace calls to this method with scanLocalCompositesInPath:withError instead.
*/
- (BOOL)scanLocalCompositesInPath:(NSString *)path usingStorageScheme:(AdobeDCXLocalStorageScheme)scheme withError:(NSError **)errorPtr __deprecated;

/**
* brief Scans an array of composites to be tracked and examines their state in
* order to determine what, if any, action the controller should request in order to sync the
* composite.  Automatically assigns this instance of the controller to the controller property
* of the composite.
*
* param composites An array of AdobeDCXComposite objects
*
* note scanLocalCompositesInPath or scanLocalComposites should be called at least once prior to
* setting the mode of the controller to anything other than suspended (it's default mode upon initialization).
*/

- (BOOL)scanLocalComposites:(NSArray *)composites;

/**
* brief Pauses synchronization of the specified composite until further notice.
*
* The current state of the composite's synchronization is maintained. Any outstanding push
* or pull is canceled.
*
* When sync of a composite is paused, the sync controller will not take any steps to progress
* synchronization, even if it is aware that a document is not curently fully synchronized.
* However, a client _can_ progress synchornization by explicitly informing the controller of changes.
* For example, if a composite is paused in the RESOLVE state and the client complete the resolve,
* the composite will move to the PUSH state. However, the push itself will not be started until
* the composite is un-paused.
*/
- (void)pauseSyncForComposite:(AdobeDCXComposite *)composite;

/**
* brief Re-enables sync of the specified composite.
*
* Invoking this on a composite that is already in sync has no effect. Otherwise, any step that the controller
* can take to progress synchronization will be immediately triggered.
*/
- (void)resumeSyncForComposite:(AdobeDCXComposite *)composite;

/**
* brief Determines whether or not synchronization for a given composite is currently paused.
*/
- (BOOL)isSyncPausedForComposite:(AdobeDCXComposite *)composite;

/**
* brief Returns the current synchronization phase for the specified composite
*
* return AdobeDCXSyncPhaseError if the specified composite is unknown to the controller
*/
- (AdobeDCXSyncPhase)currentSyncPhaseForComposite:(AdobeDCXComposite *)composite;

/**
* The last computed size of local storage in bytes used by the composites that are
* being managed by this controller. This number is not actively updated during synchronization.
* It is recomputed when all composites are in sync.
*/
@property (nonatomic, readonly) NSNumber *localStorageBytesConsumed;

/**
* brief Informs the controller that a local composite has been deleted and should no longer be tracked.
*/
- (void)reportDeletedComposite:(AdobeDCXComposite *)composite;

@end

@protocol AdobeDCXControllerDelegate <NSObject>

/**
* brief The delegate should pull the composite with the specified ID by calling the
* pullComposite:requestPriority: or pullMinimalComposite:requestPriority methods on AdobeDCXCompositeXfer.
*
* param compositeID The ID of the composite to be pulled
* param href        The server location of the composite if the composite
*
* note If the composite ID is not found among the delegate's known local composites then it should create
* a new composite object with the specified ID and href in the location of its choice prior to pulling.
*
* note It is essential that the composite object's controller property be set to this controller instance
* in order for the controller to operate correctly.
*/
- (void)controller:(AdobeDCXController *)controller requestsPullOfCompositeWithID:(NSString *)compositeID
withHref:(NSString *)href;

/**
* brief The delegate should push the composite with the specified ID by calling the
* pushComposite:overwriteExisting:requestPriority: method on AdobeDCXCompositeXfer.
*
* param compositeID The ID of the composite to be pulled
*
* note It is essential that the composite object's controller property be set to this controller instance
* in order for the controller to operate correctly.
*/
- (void)controller:(AdobeDCXController *)controller requestsPushOfCompositeWithID:(NSString *)compositeID;

/**
* brief The delegate should accept the pushed branch of the composite with the specified ID by calling
* the composite's acceptPushForComposite:withError: method
*
* param compositeID The ID of the composite to be accepted
*
* note It is essential that the composite object's controller property be set to this controller instance
* in order for the controller to operate correctly.
*/
- (void)controller:(AdobeDCXController *)controller requestsAcceptOfCompositeWithID:(NSString *)compositeID;

/**
* brief The delegate should resolve the pulled branch of the composite with the specified ID by calling
* the composite's resolvePullForComposite:withBranch:withError:
*
* param compositeID The ID of the composite to be resolved
*
* note If the client has initiated a pull by calling the pullMinimalComposite method, it may choose to
* pull additional components by calling pullComponents using the AdobeDCXCompositeXfer class upon receiving
* this method and prior to resolving.
*
* note It is essential that the composite object's controller property be set to this controller instance
* in order for the controller to operate correctly.
*/
- (void)controller:(AdobeDCXController *)controller requestsResolveOfCompositeWithID:(NSString *)compositeID;

/**
* brief Informs the delegate that a composite was deleted from the server so it should be removed
* from local storage.
*
* param compositeID The UUID string that uniquely identifies the composite
*
* note If the delegate receives this message than it can assume that the controller has removed the corresponding
* composite from the list of pending composites to push.  If the composite has been modified locally then it
* is the client's responsibility to reset the identity of the composite and call reportNewComposite to
* schedule it for a push.
*/
- (void)controller:(AdobeDCXController *)controller requestsDeleteOfCompositeWithID:(NSString *)compositeID;

/**
* brief The delegate should return the value of the localStorageBytesConsumed property of the composite with
* the specified ID.
*
* param compositeID The UUID string that uniquely identifies the composite
*
* note The controller calls this method only for composites that it has detected as having updated
* on-disk representations during the last synchronization cycle.
*/
- (NSNumber *)controller:(AdobeDCXController *)controller requestsBytesConsumedByCompositeWithID:(NSString *)compositeID;

/**
* brief Informs the delegate that the controller has encountered an error that needs to be handled by the client
* while attempting to perform an operation requested by the client on a composite (commit, push, pull, accept, or resolve).
*
* param controller  The instance of the controller sending the message
* param error       The error that occurred
* param compositeID The ID of the composite being operated upon
* param currentSyncPhase    The sync phase of the composite that generated the error
* param isPaused    The controller has paused further sync operations on this composite.  The client must address the
* error condition and then resume syncing for this composite by calling the resumeSyncForComposite method
*
* note Generally errors fall into 3 categories:
*  1. errors the controller can recover from which will simply result in retrying the operational request to the delegate
*  (e.g. a transient network error or timeout)
*  2. errors that require client intervention (e.g. filesystem errors resulting from running out of storage) before
*  the operation can succeed
*  3. sustained server or network errors that result in the network stack 'disconnecting' and cause the controller to
*  enter AdobeDCXControllerModePaused.  The client should wait at least several minutes before changing the
*  mode of the controller back to AdobeDCXControllerModeSyncing in order to try again.
*
*  This delegate method is called when the controller encounters and error in category #2
*/
- (void)        controller:(AdobeDCXController *)controller requestsClientHandleError:(NSError *)error
forCompositeWithID:(NSString *)compositeID
currentSyncPhase:(AdobeDCXSyncPhase)phase
syncPausedForComposite:(BOOL)isPaused;

/**
* brief Informs the delegate that the controller has encountered an error that needs to be handled by the client
* while attempting to perform an operation requested by the client on a composite (commit, push, pull, accept, or resolve).
*
* param controller  The instance of the controller sending the message
* param error       The error that occurred
*
* note Generally errors fall into 3 categories:
* 1. errors the controller can recover from which will simply result in retrying the operational request to the delegate
* (e.g. a transient network error or timeout)
* 2. errors that require client intervention (e.g. filesystem errors resulting from running out of storage) before
* the operation can succeed
* 3. sustained server or network errors that result in the network stack "disconnecting" and cause the controller to
* enter AdobeDCXControllerModePaused.  The client should wait at least several minutes before changing the
* mode of the controller back to AdobeDCXControllerModeSyncing in order to try again.
*
* This delegate method is called when the controller encounters and error in category #3.  If the error
* is AdobeNetworkErrorServiceDisconnected then the application is expected to call 'reconnect' on the
* session's service property (an AdobeNetworkHTTPService object) prior to setting the mode of the controller back
* to AdobeDCXControllerModeSyncing.
*/
- (void)controller:(AdobeDCXController *)controller hasPausedSyncForAllCompositesDueToError:(NSError *)error;

/**
* brief The controller has detected that one or more composites needed to be synced and
* will initiate a sync cycle by sending specific requests to the delegate.
*
* param controller The controller that is calling the delegate.
*
* note This is an optional delegate method that is for informational purposes.
*/
@optional
- (void)controllerHasStartedSync:(AdobeDCXController *)controller;

/**
* brief Informs the delegate that a sync cycle has finished.
*
* param controller The controller that is calling the delegate.
*
* note This is an optional delegate method that is for informational purposes.
* //TODO: add note about inspecting the isInSync property to determine whether sync finished successfully
*/
@optional
- (void)controllerHasFinishedSync:(AdobeDCXController *)controller;

/**
* brief Informs the delegate that the controller has finished calculating the total number of bytes
* consumed in local storage by the composites that it tracks.  The calculation takes place in a low-priority
* background thread which is spawned when a synchronization cycle finishes.
*
* param controller The controller that is calling the delegate.
* param bytesConsumed The total number of bytes consumed in local storage by the composites being tracked
* by the controller
*
* note This is an optional delegate method.
*/
@optional
- (void)controller:(AdobeDCXController *)controller hasUpdatedLocalStorageBytesConsumed:(NSNumber *)bytesConsumed;


/**
* brief The controller has enabled sync operation due to detecting a network status
* that matches the syncAllowedByNetworkStatusMask property.
*/
@optional
- (void)controllerHasEnabledSync:(AdobeDCXController *)controller dueToNetworkStatus:(AdobeNetworkStatus)networkStatus;

/**
* brief The controller has temporarily disabled sync operation due to detecting a network
* status that does not match the syncAllowedByNetworkStatusMask property.
*/
@optional
- (void)controllerHasDisabledSync:(AdobeDCXController *)controller dueToNetworkStatus:(AdobeNetworkStatus)networkStatus;

/**
* brief Notifies the delegate that the controller will add the specified composite to its list of local tracked composites
* as the result of a call to scanLocalComposites:inPath:withError.  The delegate should return NO if wishes to prevent
* the controller from adding the composite to its internal cache of synchronized composites and from subsequently managing
* the synchronization state of the composite.  Otherwise, it should return YES.  If the delegate chooses not to implement
* this method then scanLocalComposites will behave as though YES were returned for each composite (i.e they will all be tracked).
*
* note This method is not dispatched on the operation queue designated in the
* controllerForSyncGroup:withSession:withDelegate:onQueue: method.  It is always called on the same thread as, and is scoped by
* a call to the controller's scanLocalComposites:inPath:withError method.
*/
@optional
- (BOOL)controller:(AdobeDCXController *)controller willTrackLocalComposite:(AdobeDCXComposite *)composite;

@end

#endif
