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

#ifndef AdobeDCXSyncSessionProtocolHeader
#define AdobeDCXSyncSessionProtocolHeader

#import <Foundation/Foundation.h>

#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeStorageResourceCollection.h>

@class AdobeNetworkHTTPRequest;

/** The generic completion handler for asynchronous resource-based StorageSession requests. */
typedef void (^AdobeDCXResourceRequestCompletionHandler)(AdobeStorageResourceItem *, NSError *);

/** The generic completion handlers for asynchronous collection-based session requests. */
typedef void (^AdobeDCXCollectionRequestCompletionHandler)(AdobeStorageResourceCollection *, NSError *);

/** The generic completion handler for asynchronous collection-based CCStorageSession requests. */
typedef void (^AdobeDCXMultiAssetCompletionHandler)(NSArray *, NSError *);

/**
* Defines the protocol that a session has to implement in order to be used as a session for the
* sync methods of AdobeDCXSyncGroupMonitor.
*/
@protocol AdobeDCXSyncSessionProtocol <NSObject>

/**
* brief Creates a collection for the sync groups available to the current user.
*
* return The new collection resource.
*/
- (AdobeStorageResourceCollection *)collectionOfSyncGroups;

/**
* brief Creates a collection for the given sync group name.
*
* param syncGroupName The name of the sync group.
*
* return The new collection resource.
*/
- (AdobeStorageResourceCollection *)collectionForSyncGroup:(NSString *)syncGroupName;

/**
* brief Translates a sync group name into the corresponding relative href for the current session
*
* param syncGroupName   The name of the sync group
*
* return The href corresponding to the sync group
*
* note The returned href is suitable to use as a prefix for the href assigned to a new composite that
* will be bound to a server using this session object.
*/
- (NSString *)hrefForSyncGroup:(NSString *)syncGroupName;

/**
* brief Get the list of sync groups asynchronously.
*
* param syncGroups  An optional collection object for the collection of sync groups. If not nil
* it will get updated.
* param priority    The relative priority of the HTTP request.
* param queue       If not nil queue determines the operation queue handler gets executed on.
* param handler     Called when the upload has finished, failed or if it has been cancelled.
*
* return            A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*
* note On success syncGroups will get updated and handed to the handler.
*/
- (AdobeNetworkHTTPRequest *)getSyncGroups:(AdobeStorageResourceCollection *)syncGroups
pagingMode:(AdobeStoragePagingMode)mode
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionHandler:(AdobeDCXCollectionRequestCompletionHandler)handler;

/**
* brief Get the list of assets in the given sync group asynchronously.
*
* param syncGroup   The name of the sync group.
* param priority    The relative priority of the HTTP request.
* param queue       If not nil queue determines the operation queue handler gets executed on.
* param handler     Called when the upload has finished, failed or if it has been cancelled.
*
* return            A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*
* note On success syncGroup will get updated and handed to the handler.
*/
- (AdobeNetworkHTTPRequest *)getAssetsInSyncGroup:(AdobeStorageResourceCollection *)syncGroup
pagingMode:(AdobeStoragePagingMode)mode
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionHandler:(AdobeDCXCollectionRequestCompletionHandler)handler;



///@}

@end

#endif
