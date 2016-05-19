/******************************************************************************
 *
 * ADOBE CONFIDENTIAL
 * ___________________
 *
 * Copyright 2014 Adobe Systems Incorporated
 * All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains the property of
 * Adobe Systems Incorporated and its suppliers, if any. The intellectual and
 * technical concepts contained herein are proprietary to Adobe Systems
 * Incorporated and its suppliers and are protected by trade secret or
 * copyright law. Dissemination of this information or reproduction of this
 * material is strictly forbidden unless prior written permission is obtained
 * from Adobe Systems Incorporated.
 *
 * THIS FILE IS PART OF THE CREATIVE SDK PUBLIC API
 *
 * 0.1 Doc Status: Complete
 ******************************************************************************/

#ifndef AdobeAssetAsyncRequestHeader
#define AdobeAssetAsyncRequestHeader

#import <Foundation/Foundation.h>

/**
 * AdobeAssetAsyncRequest is the class by which asynchronous network operations on assets are managed.
 *
 * It allows clients to:
 *
 * - Change the priority of asynchronous network requests that have not yet been started.
 * - Cancel asynchronous network requests.
 */
@interface AdobeAssetAsyncRequest : AdobeNetworkHTTPAsyncRequest

@end

#endif
