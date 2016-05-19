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
*
**************************************************************************/

#ifndef AdobeCloudEndpointHeader
#define AdobeCloudEndpointHeader

#import <Foundation/Foundation.h>

#import <AdobeCreativeSDKCoreOSX-Internal/AdobeCloud.h>

/**
* AdobeCloudEndpoint is an object that holds the endpoint configuration for an Adobe Creative Cloud server.
*/

@interface AdobeCloudEndpoint : NSObject <NSCopying>

/**
* The URLs for the cloud endpoint.
*/
@property (nonatomic, readonly, strong) NSMutableDictionary *serviceURLs;

/**
* The service type of the cloud.
*/
@property (nonatomic, readonly, assign) AdobeCloudServiceType serviceType;

@end

#endif
