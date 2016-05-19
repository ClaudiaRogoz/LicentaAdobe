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

#ifndef AdobeCloudServiceSessionProtectedHeader
#define AdobeCloudServiceSessionProtectedHeader

#ifndef DMALIB
#import <AdobeCreativeSDKCoreOSX-Internal/AdobeCommonCache.h>
#endif

@interface AdobeCloudServiceSession (Protected)

- (instancetype)initWithEndpoint:(AdobeCloudEndpoint *)endpoint;

- (instancetype)initWithEndpoint:(AdobeCloudEndpoint *)endpoint userAgent:(NSString *)userAgent;

- (void)configureEndpoint:(AdobeCloudEndpoint *)endpoint;

/**
* Called to do any setup for the service.
*/
- (void)setupService;

/**
* Called to do a refresh of the service when coming from an offline to online state.
*/
- (void)refreshService;

/**
* Called to do a suspension of the service when coming from an online to offline state.
*/
- (void)suspendService;

/**
* Called to do any cleanup for the service.
*/
- (void)teardownService;

/**
* Called during setupService. You can override the default configuration for your cache, if specified.
*/
- (void)configureCache;

/**
* The ID specified for the cache.
*/
- (NSString *)cacheID;

/**
* Return YES if the session type allows multiple environments to be run concurrently. The default behavior is @YES.
*/
- (BOOL)supportsConcurrentEnvironments;

#ifndef DMALIB
/**
* The caching policies.
*/
- (AdobeCommonCachePolicies)cachePolicies;
#endif

- (void)setupOngoingConnectionTimer:(NSTimeInterval)timeInterval
onlyIfAuthenticated:(BOOL)condition;

- (void)stopOngoingConnectionTimer;

@end

#endif
