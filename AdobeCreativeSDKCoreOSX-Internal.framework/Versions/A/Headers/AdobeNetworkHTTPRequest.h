/*************************************************************************
*
* ADOBE CONFIDENTIAL
* ___________________
*
* Copyright 2013 Adobe Systems Incorporated
* All Rights Reserved.
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

#ifndef AdobeNetworkHTTPRequestHeader
#define AdobeNetworkHTTPRequestHeader

#import <Foundation/Foundation.h>

/**
* Represents a single HTTP request that is either scheduled or already in progress. Allows the
* client to receive progress updates, manage the relative priority of the request and cancel it.
*/
@interface AdobeNetworkHTTPRequest : NSObject

/**
* Exposes progress and the ability to cancel.
*
* See the documentation for NSProgress for more details.
*
* @note Clients must not set the @c cancellationHandler on the progress object, since that is
* being utilized internally to actually cancel the operation.
*/
@property (strong, atomic, readonly) NSProgress *progress;

/**
* Whether the request is currently being executed.
*/
@property (assign, atomic, readonly) BOOL isExecuting;

/**
* Whether the request has finished.
*/
@property (assign, atomic, readonly) BOOL isFinished;

/**
* Whether the request has been canceled.
*/
@property (assign, atomic, readonly) BOOL isCancelled;

/**
* Allows setting the priority of the request relative to other queued requests. Setting this
* property has no effect if the request is already executing.
*/
@property (assign, atomic) NSOperationQueuePriority priority;

@end

#endif
