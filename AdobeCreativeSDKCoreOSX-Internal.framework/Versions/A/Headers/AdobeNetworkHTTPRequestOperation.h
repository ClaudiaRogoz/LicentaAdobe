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

// Reviewed by rhorns on October 11, 2013

#ifndef AdobeNetworkHTTPRequestOperationHeader
#define AdobeNetworkHTTPRequestOperationHeader

#import <Foundation/Foundation.h>
#import <AdobeCreativeSDKCoreOSX-Internal/AdobeNetworkHTTPRequest.h>

@class AdobeNetworkHTTPResponse;
@class AdobeNetworkErrorResponse;
@protocol AdobeNetworkHTTPBodyStreamFactory;

/** The type of the operation. */
typedef NS_ENUM (NSInteger, AdobeNetworkHTTPRequestType)
{
AdobeNetworkHTTPDataRequestType,
AdobeNetworkHTTPDownloadRequestType,
AdobeNetworkHTTPUploadRequestType,
AdobeNetworkHTTPDownloadWithBodyStreamRequestType,
AdobeNetworkHTTPUploadWithBodyStreamRequestType
};

/**
* An internal utility class that helps AdobeNetworkHTTPService with request queue
* management.
*
* In order to schedule a request, the service object will make
* an instance of this class and place it on the queue.
*
* When the operation is executed by the queue, it will call
* AdobeNetworkHTTPService::processQueuedRequest:.
*
* If the request is successful, the service will then call
* AdobeNetworkHTTPRequestOperation::notifyScheduler, which runs the given
* notification block. That will signal the original requestor,
* one way or another.
*
* If the request fails due to a temporary issue, the service will
* call clone: to get another, identical operation, and then schedule
* that operation on the queue. The queue will also be paused until
* the issue causing the failure is cleared.
*/
@interface AdobeNetworkHTTPRequestOperation : NSOperation <NSCopying>

/** The request that this operation will attempt to issue. */
@property NSURLRequest *request;

/** The type of request. */
@property AdobeNetworkHTTPRequestType type;

/** The path of the request (for a download or upload). */
@property NSString *path;

/** The input stream of the request (for a download). */
@property (strong) id <AdobeNetworkHTTPBodyStreamFactory> bodyStreamFactory;


/** The block invoked when this request is to be issued. */
@property (strong)void(^ invocationBlock)(AdobeNetworkHTTPRequestOperation *);

/** The block invoked if notifyScheduler: is called. */
@property (strong)void(^ notificationBlock)(AdobeNetworkHTTPResponse *);

/** Every request has a unique id, even if it's re-issued */
@property NSString *id;

/** Request id to track if this request has been issued previously */
@property NSString *originalId;

/** Used to store an error from a request. */
@property NSError *error;

/** Used to collect the received data from a data request. */
@property NSMutableData *receivedData;

/** Used to parse the response JSON into an ERD. */
@property (strong) AdobeNetworkErrorResponse *errorResponseDocument;

/** Used to store the NSURLSessionTask while it is active. */
@property NSURLSessionTask *sessionTask;

/** Is YES then canceling the NSProgress will not cancel the session task. */
@property BOOL disallowCancel;

/** Used by AdobeNetworkHTTPHTTService to store an internal completion callback. */
@property (strong)void(^ completionHandler)(AdobeNetworkHTTPResponse *);

/** The request object that is returned to the caller. It provides progress as well as means of cancellation
* and prioritization. Declared as weak to avoid a retain cycle, since it itself has a reference to the
* operarion. */
@property (weak) AdobeNetworkHTTPRequest *weakClientRequestObject;

/** Executes this operation, and invoked by NSOperationQueue. */
- (void)main;

/**
* brief Notifies the scheduler of this operation by invoking the notification block.
*
* param response The response to the request.
*
* This method is *not* invoked by main: when this operation is executed. Instead, the entity responsible
* for managing the queue is expected to determine when and whether to call this.
*/
- (void)notifyRequesterOfResponse:(AdobeNetworkHTTPResponse *)response;

@end

#endif
