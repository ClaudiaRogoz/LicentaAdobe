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

#ifndef AdobeNetworkHTTPResponseHeader
#define AdobeNetworkHTTPResponseHeader

#import <Foundation/Foundation.h>

@class AdobeNetworkErrorResponse;

/**
* Data object that captures the result of an HTTP request.
*/
@interface AdobeNetworkHTTPResponse : NSObject

/**
* Contains an NSError if the request has failed.
*/
@property (strong, nonatomic) NSError *error;

/**
* The data returned by the server. Can be nil if the request has failed or if it was a download.
*/
@property (strong, nonatomic) NSData *data;

/**
* The path to the downloaded file. Can be nil if the request has failed or if it was not a
* download.
*/
@property (strong, nonatomic) NSString *path;

/**
* The HTTP status code returned by the server.
*/
@property (assign, nonatomic) int statusCode;

/**
* The Request ID returned by the server.
*/
@property (strong, nonatomic) NSString *requestID;

/**
* The URL of the request.
*/
@property (strong, nonatomic) NSURL *URL;

/**
* Dictionary of the response header key/value pairs. Keys are lower case.
*/
@property (strong, nonatomic) NSDictionary *headers;

/**
* Number of bytes sent.
*/
@property (assign, nonatomic) int64_t bytesSent;

/**
* Number of bytes received.
*/
@property (assign, nonatomic) int64_t bytesReceived;

/**
* Used to parse the response JSON into an ERD.
*/
@property (strong, nonatomic) AdobeNetworkErrorResponse *errorResponseDocument;

@end

#endif
