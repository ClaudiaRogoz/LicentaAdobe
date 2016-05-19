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

#ifndef AdobeCloudPrivateHeader
#define AdobeCloudPrivateHeader

#import <AdobeCreativeSDKCoreOSX-Internal/AdobeCloud.h>

@interface AdobeCloud ()

@property (nonatomic, readwrite, strong) NSString *GUID;
@property (nonatomic, readwrite, strong) NSString *eTag;
@property (nonatomic, readwrite, strong) NSString *name;
@property (nonatomic, readwrite, strong) NSString *cloudDescription;
@property (nonatomic, readwrite, strong) NSString *region;
@property (nonatomic, readwrite, strong) NSURL *logoURL;
@property (nonatomic, readwrite, strong) NSMutableDictionary *endpoints;
@property (nonatomic, readwrite, strong) NSMutableDictionary *sessions;
@property (nonatomic, readwrite, strong) NSMutableDictionary *parameters;

@property (nonatomic, readwrite, assign, getter = isAvailable) BOOL available;
@property (nonatomic, readwrite, assign, getter = isPrivateCloud) BOOL privateCloud;
@property (nonatomic, readwrite, assign, getter = isQuotaEnabled) BOOL quotaEnabled;
@property (nonatomic, readwrite, assign) NSUInteger version;

// This property may become public once the cloud href is returned by ERS.
@property (nonatomic, readonly, strong) NSString *href;

@end

#endif
