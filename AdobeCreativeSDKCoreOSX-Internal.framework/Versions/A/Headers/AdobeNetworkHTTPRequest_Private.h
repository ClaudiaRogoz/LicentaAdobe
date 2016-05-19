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

#ifndef AdobeNetworkHTTPRequestPrivateHeader
#define AdobeNetworkHTTPRequestPrivateHeader

#import <AdobeCreativeSDKCoreOSX-Internal/AdobeNetworkHTTPRequest.h>

/**
* Private extensions to AdobeNetworkHTTPRequest.
*/
@interface AdobeNetworkHTTPRequest ()

- (instancetype)initWithProgress:(NSProgress *)progress andOperation:(NSOperation *)operation;

/**
* Manually sets the operation object to be used.
*
* @param operation The operation object to use for HTTP requests.
*/
- (void)setOperation:(NSOperation *)operation;

@end

#endif
