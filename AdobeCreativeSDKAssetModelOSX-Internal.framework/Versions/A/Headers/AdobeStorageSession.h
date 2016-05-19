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

#ifndef AdobeStorageSessionHeader
#define AdobeStorageSessionHeader

#import <Foundation/Foundation.h>

@class AdobeCloudEndpoint;
@class AdobeNetworkHTTPService;
@class AdobeStorageResourceItem;
@class AdobeStorageResourceCollection;

/** A generic completion handler for asynchronous resource-based StorageSession data requests. */
typedef void (^AdobeStorageDataRequestCompletionHandler)(NSData *data, NSError *error);

/** The generic completion handler for asynchronous resource-based StorageSession requests. */
typedef void (^AdobeStorageResourceRequestCompletionHandler)(AdobeStorageResourceItem *item, NSError *error);

/** The generic completion handler for asynchronous collection-based StorageSession requests. */
typedef void (^AdobeStorageCollectionRequestCompletionHandler)(AdobeStorageResourceCollection *collection, NSError *error);

/** Sent if the storage service is disconnected */
extern NSString *const AdobeStorageServiceDisconnectedNotification;

/**
* Provides an Objective-C binding of the Creative Cloud Service API.
* Must be initialized with an instance of AdobeNetworkHTTPService, which in turn provides the configuration
* necessary to speak to a specific CC environment (e.g., stage or production).
* See AdobeStorageSession:initWithHTTPService.
*/
@interface AdobeStorageSession : AdobeCloudServiceSession

/**
* Get a newly created and fully configured storage session object with the specified endpoint.
*
* @param cloudEndpoint Cloud endpoint object to use when configuring the storage session instance.
* If @c cloudEndpoint isn't specified (is @c nil), the default endpoint, retrieved from
* @c serviceEndpoint, is used.
*
* @return A fully configured and usable instance of the storage session.
*/
+ (instancetype)sessionForCloudEndpoint:(AdobeCloudEndpoint *)cloudEndpoint;

/**
* Retrieves the legacy service endpoint.
*
* @return A cloud endpoint that represent the default (lagacy) cloud.
*/
+ (AdobeCloudEndpoint *)serviceEndpoint;

/**
* Retrieve the currently logged-in user's quota information asynchronously.
*
* @param completionBlock Block to execute when the quot information has been retrieved.
* @param errorBlock      Block to execute in case of errors. Specify @c NULL to omit.
*/
- (void)quotaInformationOnCompletion:(void (^)(NSNumber *used, NSNumber *available, NSNumber *total))completionBlock
error:(void (^)(NSError *error))errorBlock __deprecated_msg("Use quota:handlerQueue:completionBlock:");

/**
*  Get the quota information for the logged in user, asynchronously.
*
*  @param priority         The priority of the HTTP request.
*  @param queue            If not nil it determines the queue that the completion block gets executed on.
*  @param completionBlock  Called when the call has finished, failed or if it has been cancelled.
*
*  @return A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)quota:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionBlock:(void (^)(NSNumber *used, NSNumber *available, NSNumber *total, NSError *err))completionBlock;

@end

#endif /* ifndef AdobeStorageSessionHeader */
