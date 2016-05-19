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

#ifndef AdobeEntitlementServicesPrivateHeader
#define AdobeEntitlementServicesPrivateHeader

#import <AdobeCreativeSDKCoreOSX-Internal/AdobeEntitlementServices.h>

/**
* Creative Cloud (Public Storage)
*/
extern NSString * const AdobeEntitlementServiceCCPublicStorage;

/**
* Creative Cloud (Private Storage)
*/
extern NSString * const AdobeEntitlementServiceCCPrivateStorage;

@interface AdobeEntitlementServices ()

@property (nonatomic, assign, getter = hasAccessToPublicStorageServices) BOOL accessToPublicStorageServices;

@property (nonatomic, assign, getter = hasAccessToPrivateStorageServices) BOOL accessToPrivateStorageServices;

@end

#endif
