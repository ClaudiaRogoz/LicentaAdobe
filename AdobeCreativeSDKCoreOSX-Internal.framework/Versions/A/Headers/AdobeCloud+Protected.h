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

#ifndef AdobeCloudProtectedHeader
#define AdobeCloudProtectedHeader

#import <Foundation/Foundation.h>

extern NSString *const AdobeCloudCoderKeyGUID;
extern NSString *const AdobeCloudCoderKeyETag;
extern NSString *const AdobeCloudCoderKeyName;
extern NSString *const AdobeCloudCoderKeyDescription;
extern NSString *const AdobeCloudCoderKeyRegion;
extern NSString *const AdobeCloudCoderKeyLogoURL;
extern NSString *const AdobeCloudCoderKeyEndpoints;
extern NSString *const AdobeCloudCoderKeyParameters;
extern NSString *const AdobeCloudCoderKeyVersion;
extern NSString *const AdobeCloudCoderKeyAvailablity;
extern NSString *const AdobeCloudCoderKeyPrivateCloud;

@interface AdobeCloud (Protected)

- (instancetype)initWithGUID:(NSString *)guid
etag:(NSString *)etag
name:(NSString *)name
description:(NSString *)description
region:(NSString *)region
version:(NSUInteger)version
logoURL:(NSURL *)logoURL
endpoints:(NSDictionary *)endpoints
parameters:(NSDictionary *)parameters;

- (id)initWithCoder:(NSCoder *)coder;
- (void)encodeWithCoder:(NSCoder *)coder;

- (BOOL)updateFromData:(NSData *)data
error:(NSError **)errorPtr;

- (BOOL)updateFromDictionary:(NSDictionary *)data
error:(NSError **)errorPtr;

/**
* Called to do any setup for the service.
*/
- (void)setupService:(AdobeCloudServiceType)serviceType;

/**
* Called to do any cleanup for the service.
*/
- (void)teardownService:(AdobeCloudServiceType)serviceType;

/**
* Called on logout.
*/
- (void)removeAllSessions;

@end

#endif
