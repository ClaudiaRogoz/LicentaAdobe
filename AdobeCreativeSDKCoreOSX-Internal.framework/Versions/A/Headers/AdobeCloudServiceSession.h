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

#ifndef AdobeCloudServiceSessionHeader
#define AdobeCloudServiceSessionHeader

#import <Foundation/Foundation.h>

#import <AdobeCreativeSDKCoreOSX-Internal/AdobeNetworkHTTPService.h>

@class AdobeCloudEndpoint;

typedef NSMutableDictionary AdobeNetworkHTTPServices;

/**
* Base class for all Adobe Cloud Service Sessions
*/
@interface AdobeCloudServiceSession : NSObject

/**
* If the service is for a private cloud return @YES.
*/
@property (nonatomic, readwrite, assign, getter = isPrivateService) BOOL privateService;

/**
* If the service is active return @YES.
*/
@property (atomic, readonly, assign, getter = isActive) BOOL active;

/**
* The service the session has been intialized with.
*/
@property (nonatomic, readonly, strong) AdobeNetworkHTTPServices *httpServices;

/**
* The notifier sent when a disconnection of the service occurs.
*/
@property (nonatomic, readwrite, strong) NSString *disconnectionNotifier;

/**
* Create a session object with the given endpoint.
*
* @param cloudEndpoint The cloud endpoint to use when configuring the session object.
*
* @return A fully configured and ready-to-use session object.
*/
+ (instancetype)sessionForCloudEndpoint:(AdobeCloudEndpoint *)cloudEndpoint;

/**
* Initializes this object with an AdobeNetworkHTTPService object that has been appropriately initialized
* for use with the Creative Cloud Service.
*
* @param service the service to initialize with
*
* @returns The inititialized session.
*/
- (instancetype)initWithHTTPService:(AdobeNetworkHTTPService *)service;

/**
* Initializes this object with an AdobeNetworkHTTPService object that has been appropriately initialized
* for use with the Creative Cloud Service.
*
* @param service the service to initialize with
* @param serviceName the name of the service
*
* @returns The inititialized session.
*/
- (instancetype)initWithHTTPService:(AdobeNetworkHTTPService *)service
serviceName:(NSString *)serviceName;

/**
* Get the default HTTP service for the session.
*
* @return the default HTTP service.
*/
- (AdobeNetworkHTTPService *)service;

/**
* Get the HTTP service for the entitlement schema id.
*
* @param serviceId The id of the service as represented in the entitlements schema, pass nil for the default.
*
* @return the HTTP service for the given name.
*/
- (AdobeNetworkHTTPService *)serviceForSchemaId:(NSString *)serviceId;

@end

#endif
