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

// Reviewed by rhorns on October 14, 2013

#ifndef AdobeNetworkHTTPServiceEventHeader
#define AdobeNetworkHTTPServiceEventHeader

#import <Foundation/Foundation.h>

@class AdobeNetworkHTTPResponse;

/**
* brief Data object capturing the properties sent as an event to the DMA analytics server.
*/
@interface AdobeNetworkHTTPServiceEvent : NSObject

/** The unique identifier of the event. */
@property (nonatomic) NSString *id;

/** The unique identifier of the original event in case the request was repeated. */
@property (nonatomic) NSString *originalId;

/** The unique identifier of the operation the request is a part of. */
@property (nonatomic) NSString *operationId;

/** The HTTP verb (e.g. GET, POST, DELETE). */
@property (nonatomic) NSString *httpVerb;

/** The http status code returned by the request's server response. */
@property (nonatomic) NSString *httpStatus;

/** The url of the request. */
@property (nonatomic) NSString *url;

/** The number of bytes that were sent. */
@property (nonatomic) NSString *bytesSent;

/** The number of bytes received as part of the request's server response. */
@property (nonatomic) NSString *bytesReceived;

/** Timestamp generated just before the request was issued. */
@property (nonatomic) NSString *sendStartTime;

/** Timestamp generated just after the request's response was received. */
@property (nonatomic) NSString *receiveEndTime;

/** The type of network used for the request. */
@property (nonatomic) NSString *networkType;

/** The client application. */
@property (nonatomic) NSString *application;

/**
* brief Helper method to set the event's properties based on the request.
*
* param urlRequest The request.
*/
- (void)recordRequest:(NSURLRequest *)urlRequest;

/**
* brief Helper method to set the event's properties based on the response.
*
* param response The response.
*/
- (void)recordResponse:(AdobeNetworkHTTPResponse *)response;

@end

#endif
