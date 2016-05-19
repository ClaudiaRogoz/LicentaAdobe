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

#ifndef AdobeDCXSyncGroupMonitorHeader
#define AdobeDCXSyncGroupMonitorHeader

#import <Foundation/Foundation.h>

@class AdobeStorageResource;
@class AdobeStorageResourceCollection;
@class AdobeDCXComposite;

@protocol AdobeDCXTransferSessionProtocol;
@protocol AdobeDCXSyncSessionProtocol;

@protocol AdobeDCXSyncGroupMonitorDelegate;

/**
* brief Used to monitor changes to a set of composites stored on a particular service.
* This class is the remote half of synchronizing a set of composites; it informs the
* client when a document may have changed remotely. Clients provide the local half of
* synchronization by tracking local changes, and pushing them as appropriate.
*
* Each monitor tracks all documents of a particular type and associated with a particular user.
* Clients are notified of changes via the delegate, which they are required to provide. Clients
* that wish to monitor documents of more than one type on a given service should configure one
* monitor for each, re-using the same session object.
*/
@interface AdobeDCXSyncGroupMonitor : NSObject

/**
* The sync group that this monitor monitors.
*/
@property (nonatomic, readonly) NSString *syncGroup;

/**
* brief The frequency in seconds of sync group update requests made to the storage service.
* Changes to the updateFrequency will only take affect after the next call to startWithSyncGroup.
* The default value is 60.0 seconds. Any attempt to set the update frequency to a value lower than the
* allowed minimum of 60.0 seconds will result in it being set to the minimum value instead.
*/
@property (nonatomic) NSTimeInterval updateFrequency;

/**
* brief The priority with which the update requests are being made (relative to other HTTP requests
* issued to the same service session). The default value of this property is NSOperationQueuePriorityNormal.
* A change of this property takes effect for the next update request.
*/
@property (nonatomic) NSOperationQueuePriority updatePriority;


/**
* brief Creates a new asset monitor.
*
* param syncGroup The name of the sync group this monitor monitors.
* param session   The DCX session to use.
* param delegate  The delegate that should receive the notifications. The monitor will keep a weak
*                reference to it.
* param queue     The NSOperation queue identifying the thread on which the delegate methods are called
*
* return The newly created asset monitor.
*/
+ (id)assetMonitorForSyncGroup:(NSString *)syncGroup
usingSession:(id<AdobeDCXTransferSessionProtocol, AdobeDCXSyncSessionProtocol>)session
withDelegate:(id<AdobeDCXSyncGroupMonitorDelegate>)delegate
onQueue:(NSOperationQueue *)queue;

/**
* brief Creates an returns a resource for the given composite to be used in the local assets
* array for the startWithLocalAssets: method.
*
* param composite The composite to create the resource for.
*
* return The new resource or nil if the given composite is not bound.
*/
- (AdobeStorageResource *)resourceForComposite:(AdobeDCXComposite *)composite;


/**
* brief Begin monitoring with the given list of local assets.
*
* param localAssets An NSArray containing the resource items of the locally stored assets. Use
* resourceForComposite: to create these resource items.
*
* note This method will raise a NSInternalInconsistency exception if called again without first
* calling stop.
*/
- (void)startWithLocalAssets:(NSArray *)localAssets;

/**
* brief Begin monitoring with a collection object previously returned by calling getMonitoredCollection
*
* param collection An AdobeStorageResourceCollection that was previously obtained by calling
* getMonitoredCollection on an instance of the monitor for the same sync group.
*
* note This method will raise a NSInvalidArgument exception if called with a collection whose href
* does not match that of the current sync group.  It will raise a NSInternalInconsistency exception if
* called again without first calling stop.  When starting the monitor using this method it is
* the caller's responsibility to inform the monitor of changes to local assets that may have occurred
* since the collection was obtained by using the updateLocalAsset method.
*/
- (void)startWithMonitoredCollection:(AdobeStorageResourceCollection *)collection;

/**
* brief Stop monitoring.
*/
- (void)stop;

/**
* brief Restarts monitoring using the last-known state of local and remote assets as a starting point.
*
* note This method with raise a NSInternalInconsistency exception in the event that it is called on an
* instance that hasn't been previously started and stopped.
*/
- (void)resume;

/**
* brief Retieves a copy of the collection object that describes the known state of the assets
* that are being monitored by this instance.  The collection may be subsequently used when calling
* startWithMonitoredCollection.
*/
- (AdobeStorageResourceCollection *)getMonitoredCollection;

/**
* brief Updates the internal list of local assets to reflect a change initiated by the client.
*
* param asset The resource that has been updated
* param deleted If YES, indicates that the asset was deleted and should be removed from the list of local assets
*
* note This method should only be called on a monitor instance that is currently running
* (i.e. that has been started or resumed)
*/
- (void)updateLocalAsset:(AdobeStorageResource *)asset wasDeleted:(BOOL)deleted;


/**
* brief Forces an immediate, explicit update of monitored sync group.
*
* note Updates complete asynchronously, and may take several seconds or longer to complete.
* Calling this method a second time while an update is already in progress has no effect.
*/
- (void)update;

/**
* brief Behaves like the update method (above) except that we poll the server without
* attempting to use cached collection data from the previous request
*
* note This method only exists to support a hack for R/O Shared Libraries required because
* changes to read-only state on shared composites is not reflected in an update to a sync
* group etag.
*/
-(void) updateAndForceSyncGroupRefresh;

/**
* brief Synchronously performs an update of the monitored sync group.  Mostly useful for testing.
*/
- (void)waitForUpdate;

@end


/**
* brief Instances of AdobeStorageAssetMonitor send the following messages to their delegate
* while monitoring sync groups. Messages may be received at any time, and in any order.
*
* note Clients are assumed to take appropriate action on all messages; the monitor
* is not aware of synchronization activity and clients are not re-notified if they, say,
* fail to synchronize a document that has previously changed.
*/
@protocol AdobeDCXSyncGroupMonitorDelegate <NSObject>

/**
* brief An update has started.
*
* param monitor The monitor that is calling the delegate.
*
* note This is an optional delegate method that is for informational purposes.
*/
@optional
- (void)monitorHasStartedUpdate:(AdobeDCXSyncGroupMonitor *)monitor;

/**
* brief An update has finished. This is an optional delegate method.
*
* param monitor The monitor that is calling the delegate.
*
* note This is an optional delegate method that is for informational purposes.
*/
@optional
- (void)monitorHasFinishedUpdate:(AdobeDCXSyncGroupMonitor *)monitor;

/**
* brief An update has finished. This is an optional delegate method.
*
* param monitor The monitor that is calling the delegate.
* param refreshed The monitor refreshed its sync group listing by way of a 200 response
* to the corresponding sync group during this update cycle.  This may be triggered either
* because the sync group's etag has been updated on the server or because updateAndForceSyncGroupRefresh
* was invoked on the monitor.
*
* note This is an optional delegate method that is an alternative to the above
*/
@optional
- (void)monitorHasFinishedUpdate:(AdobeDCXSyncGroupMonitor *)monitor syncGroupWasRefreshed:(BOOL)refreshed;

/**
* brief The asset described by the item object was updated and should be synchronized.
*
* param monitor     The monitor that is calling the delegate.
* param resource    The item that was updated.
*/
- (void)monitor:(AdobeDCXSyncGroupMonitor *)monitor assetWasUpdated:(AdobeStorageResource *)resource;


/**
* brief The asset described by the item object was deleted.
*
* param monitor     The monitor that is calling the delegate.
* param resource    The item that was deleted.
*
* note This is not the same as setting the status of a composite document to 'deleted', which would generate a
* assetWasChanged: message. This message indicates that the server copy has been removed
* entirely. If the client has a local copy that it wishes to keep, it must upload that copy as a new
* document.
*/
- (void)monitor:(AdobeDCXSyncGroupMonitor *)monitor assetWasDeleted:(AdobeStorageResource *)resource;


/**
* brief The asset described by the item object has been added; the client should download it in order to
* remain in sync with the contents of the sync group being monitored.
*
* param monitor     The monitor that is calling the delegate.
* param resource    The item that was added.
*/
- (void)monitor:(AdobeDCXSyncGroupMonitor *)monitor assetWasAdded:(AdobeStorageResource *)resource;

@end

#endif
