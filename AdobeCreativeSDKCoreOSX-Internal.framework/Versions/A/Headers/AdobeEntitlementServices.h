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

#ifndef AdobeEntitlementServicesHeader
#define AdobeEntitlementServicesHeader

#import <Foundation/Foundation.h>

@class AdobeCloud;

/**
* Storage
*/
extern NSString * const AdobeEntitlementServiceStorage;

/**
* Typekit
*/
extern NSString * const AdobeEntitlementServiceTypekit;

/**
* Behance.net
*/
extern NSString * const AdobeEntitlementServiceBehance;

/**
* Adobe Story CC Plus
*/
extern NSString * const AdobeEntitlementServiceStory;

/**
* PhoneGap Build
*/
extern NSString * const AdobeEntitlementServicePhoneGapBuild;

/**
* Lightroom
*/
extern NSString * const AdobeEntitlementServiceLightroom;

/**
* Edge Inspect
*/
extern NSString * const AdobeEntitlementServiceEdgeInspect;

/**
* Image Services
*/
extern NSString * const AdobeEntitlementServiceImage;

/**
* Extract
*/
extern NSString * const AdobeEntitlementServiceExtract;

/**
* Preview
*/
extern NSString * const AdobeEntitlementServicePreview;

/**
* Login to Mobile Apps
*/
extern NSString * const AdobeEntitlementServiceAllowMobile;

/**
* Desktop File Sync
*/
extern NSString * const AdobeEntitlementServiceFileSync;

/**
* Collaboration
*/
extern NSString * const AdobeEntitlementServiceCollaboration;

/**
* Assets/Files (Storage)
*/
extern NSString * const AdobeEntitlementServiceAssets;

/**
* Creative Cloud Libraries
*/
extern NSString * const AdobeEntitlementServiceLibraries;

/**
* Design Assets (Creative Cloud Market)
*/
extern NSString * const AdobeEntitlementServiceDesignAssets;

/**
* Color (Kuler)
*/
extern NSString * const AdobeEntitlementServiceColor;

/**
* Desktop Sync Settings
*/
extern NSString * const AdobeEntitlementServiceSyncSettings;

/**
* Sync Metadata
*/
extern NSString * const AdobeEntitlementServiceSyncMetadata;

/**
* Premiere Clip
*/
extern NSString * const AdobeEntitlementServicePremiereClip;

/**
* CCV
*/
extern NSString * const AdobeEntitlementServiceCCV;

/**
* Stock
*/
extern NSString * const AdobeEntitlementServiceStock;

typedef NS_ENUM(NSInteger, AdobeEntitlementServiceLevel)
{
AdobeEntitlementServiceLevelUnknown = 0,
AdobeEntitlementServiceLevelFreeBasic,
AdobeEntitlementServiceLevelPaidOne,
AdobeEntitlementServiceLevelPaidTwo,
AdobeEntitlementServiceLevelPaidThree
};

/**
* AdobeEntitlementServices is an object that holds the services configuration for an Adobe Creative Cloud user.
*/
@interface AdobeEntitlementServices : NSObject

/**
* The services.
*/
@property (nonatomic, readonly, strong) NSDictionary *services;

+ (AdobeEntitlementServices *)sharedServices;

/**
* Whether the user is entitled to use the specified service.
*
* @param serviceName The service name constant. Use one of the constants defined in the
*                    @c AdobeEntitlementServices header file.
* @param cloud       The appropriate cloud object to use.
*
* @return @c YES if the user has access to the specified service; @c NO otherwise.
*/
- (BOOL)isEntitledToService:(NSString *)serviceName
withCloud:(AdobeCloud *)cloud;

/**
* Get the service level for the user in the specified service.
*
* @param serviceName The service name constant. Use one of the constants defined in the
*                    @c AdobeEntitlementServices header file.
* @param cloud       The appropriate cloud object to use.
*
* @return @c YES if the user has access to the specified service; @c NO otherwise.
*/
- (AdobeEntitlementServiceLevel)levelForService:(NSString *)serviceName
withCloud:(AdobeCloud *)cloud;

@end

#endif
