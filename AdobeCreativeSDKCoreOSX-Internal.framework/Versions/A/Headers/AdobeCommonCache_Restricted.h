/******************************************************************************
*
* ADOBE CONFIDENTIAL
* ___________________
*
* Copyright 2013 Adobe Systems Incorporated
* All Rights Reserved.
*
* NOTICE:  All information contained herein is, and remains the property of
* Adobe Systems Incorporated and its suppliers, if any. The intellectual and
* technical concepts contained herein are proprietary to Adobe Systems
* Incorporated and its suppliers and are protected by trade secret or
* copyright law. Dissemination of this information or reproduction of this
* material is strictly forbidden unless prior written permission is obtained
* from Adobe Systems Incorporated.
******************************************************************************/

#ifndef AdobeCommonCacheRestrictedHeader
#define AdobeCommonCacheRestrictedHeader

// Cache debugging, tracing, and performance measurements.

@interface AdobeCommonCache ()

@property (nonatomic, readwrite, assign, getter = isVerboseLogging, setter = useVerboseLogging :) BOOL verboseLogging;

- (BOOL)printStatistics:(NSString *)cacheName
withError:(NSError **)errorPtr;

- (BOOL)logCacheMiss:(NSString *)path
latency:(NSTimeInterval)msLatency
forCache:(NSString *)cacheName
withError:(NSError **)errorPtr;

+ (NSString *)hashForAdobeID:(NSString *)adobeID;

/**
* Hard remove of all caches (removes at the root level).
*/
- (void)removeAllCaches;

/**
* Hard remove of all caches for a given user.
*/
- (void)removeAllCachesForAdobeID:(NSString *)adobeID;

@end

#endif
