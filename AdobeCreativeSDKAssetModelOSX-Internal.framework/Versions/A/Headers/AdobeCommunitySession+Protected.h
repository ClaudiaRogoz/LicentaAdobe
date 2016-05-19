/*************************************************************************
*
* ADOBE CONFIDENTIAL
* ___________________
*
*  Copyright 2015 Adobe Systems Incorporated
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

#ifndef AdobeCommunitySessionProtectedHeader
#define AdobeCommunitySessionProtectedHeader

#import <Foundation/Foundation.h>

extern NSString *const AdobeCommunitySessionCacheID;

@interface AdobeCommunitySession (Protected)

// expose protected properties
@property (readwrite, nonatomic, strong) NSNumber *directUploadLimitInBytes;
@property (readwrite, nonatomic, strong) AdobeNetworkHTTPService *awsS3Service;

/**
* brief Starts an asynchronous request using the proper method for the request.
*
* param request  The request to get the response for.
* param path     The file to upload from or download to. Can be nil.
* param data     The data to upload. Can be nil. Ignored if path is set.
* param priority The prioprity of the HTTP request.
* param handler  Called when the upload has finished or failed.
*/
- (AdobeNetworkHTTPRequest *)getResponseFor:(NSMutableURLRequest *)request
streamToOrFrom:(NSString *)path
data:(NSData *)data
requestPriority:(NSOperationQueuePriority)priority
completionHandler:(void (^)(AdobeNetworkHTTPResponse *))handler;

/**
* brief Constructs an error for the response.
*
* param response The response.
* param path     Optional file path which will be recorded in the error.
* param details  Optional string that will be recorded in the error.
*
* return The newly constructed error.
*/
- (NSError *)errorFromResponse:(AdobeNetworkHTTPResponse *)response
path:(NSString *)path
details:(NSString *)details;

@end

#endif
