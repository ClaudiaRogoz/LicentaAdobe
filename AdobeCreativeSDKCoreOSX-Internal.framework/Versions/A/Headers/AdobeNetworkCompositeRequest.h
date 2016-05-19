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

#ifndef AdobeNetworkCompositeRequestHeader
#define AdobeNetworkCompositeRequestHeader

#import <AdobeCreativeSDKCoreOSX-Internal/AdobeNetworkHTTPRequest.h>

/**
* Subclass of AdobeNetworkHTTPRequest which represents all the individual HTTP requests for a
* larger logical operation as a single object, allowing clients to get progress for and/or cancel
* the operation.
*/
@interface AdobeNetworkCompositeRequest : AdobeNetworkHTTPRequest

- (instancetype)initWithPriority:(NSOperationQueuePriority)priority;

/**
* Adds the request to the list of component requests.
*
* @param request A component request that is part of this composite request.
*/
- (void)addComponentRequest:(AdobeNetworkHTTPRequest *)request;

/**
* Notifies the request that it shouldn't expect any more component requests.
*/
- (void)allComponentsHaveBeenAdded;

/**
* Releases all the component requests that were tracked by this composite request.
*/
- (void)releaseRequests;

@end

#endif
