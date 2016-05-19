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

#ifndef AdobeCloudHeader
#define AdobeCloudHeader

#import <Foundation/Foundation.h>

@class AdobeCloudServiceSession;

// Do NOT re-order this enum unless you understand the implications.
typedef NS_ENUM (NSInteger, AdobeCloudServiceType)
{
AdobeCloudServiceTypeUnknown = 0,
AdobeCloudServiceTypeImage = 1,
AdobeCloudServiceTypeCommunity = 2,
AdobeCloudServiceTypePhoto = 3,
AdobeCloudServiceTypeStorage = 4,
AdobeCloudServiceTypeEntitlement = 5,
AdobeCloudServiceTypeNotification = 6,
AdobeCloudServiceTypeClipboard = 7,
AdobeCloudServiceTypeStock = 8,
AdobeCloudServiceTypeStockResources = 9,
AdobeCloudServiceTypeLibrary = 10,
};

/**
* AdobeCloud is a component that represents the metadata representing the endpoints and
* other configuration data for Adobe Creative Cloud.
*/
@interface AdobeCloud : NSObject <NSCopying>

/**
* The unique identifier for the cloud.
*/
@property (nonatomic, readonly, strong) NSString *GUID;

/**
* The eTag for the cloud.
*/
@property (nonatomic, readonly, strong) NSString *eTag;

/**
* The human readable name for the cloud.
*/
@property (nonatomic, readonly, strong) NSString *name;

/**
* The description of the cloud.
*/
@property (nonatomic, readonly, strong) NSString *cloudDescription;

/**
* The geographical region of this cloud.
*/
@property (nonatomic, readonly, strong) NSString *region;

/**
* The logo (or avatar) associated with the cloud.
*/
@property (nonatomic, readonly, strong) NSURL *logoURL;

/**
* A list of AdobeCloudEndpoints keyed by the AdobeCloudEndpointService.
*/
@property (nonatomic, readonly, strong) NSMutableDictionary *endpoints;

/**
* Custom parameters.
*/
@property (nonatomic, readonly, strong) NSMutableDictionary *parameters;

/**
* The version of the cloud.
*/
@property (nonatomic, readonly, assign) NSUInteger version;

/**
* Whether the cloud is reachable.
*/
@property (nonatomic, readonly, assign, getter = isAvailable) BOOL available;

/**
* Whether the cloud is a private cloud.
*/
@property (nonatomic, readonly, assign, getter = isPrivateCloud) BOOL privateCloud;

/**
* Whether this cloud has a quota for the user.
*/
@property (nonatomic, readonly, assign, getter = isQuotaEnabled) BOOL quotaEnabled;

/**
* The session for the specified endpoint service type.
*/
- (AdobeCloudServiceSession *)sessionForService:(AdobeCloudServiceType)service;

/**
* A stricter check to see if the clouds are equal.
*/
- (BOOL)isStrictlyEqual:(AdobeCloud *)cloud;

@end

#endif /* ifndef AdobeCloudHeader */
