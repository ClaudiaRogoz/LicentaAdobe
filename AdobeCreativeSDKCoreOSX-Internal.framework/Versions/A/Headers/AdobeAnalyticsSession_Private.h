/*************************************************************************
*
* ADOBE CONFIDENTIAL
* ___________________
*
*  Copyright 2013 Adobe Systems Incorporated
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

#ifndef AdobeAnalyticsSessionPrivateHeader
#define AdobeAnalyticsSessionPrivateHeader

#import <AdobeCreativeSDKCoreOSX-Internal/AdobeAnalyticsSession.h>

/**
* /brief The AdobeAnalyticsSession methods used within the Creative SDK to trigger the client callbacks.
*/
@interface AdobeAnalyticsSession ()

/**
* brief Return whether or not the instance has any delegates.
*
* Internal APIs should use this to determine whether or not they need to initiate reporting.
* If there is no delegate, no analytics data needs to be generated or reported.
*
* return YES if there is one or more registered AdobeAnalyticsSessionDelegate, NO otherwise.
*/
- (BOOL)hasDelegate;

/**
* brief Reports the data for an analytics "state" event to all delegates registered with the AdobeAnalyticsSession.
*
* param state The name of the state event being reported.
* param data The data associated with the action.
*/
- (void)trackState:(NSString *)state data:(NSDictionary *)data;

/**
* brief Reports the data for an analytics "action" event to all delegates registered with the AdobeAnalyticsSession.
*
* param action The name of the action event being reported.
* param data The data associated with the action.
*/
- (void)trackAction:(NSString *)action data:(NSDictionary *)data;

/**
* brief Reports the data for an analytics "timed action start" event to all delegates registered with the AdobeAnalyticsSession.
*
* param action The name of the timed action event being reported.
* param data The data associated with the action.
*/
- (void)trackTimedActionStart:(NSString *)action data:(NSDictionary *)data;

/**
* brief Reports the data for an analytics "timed action update" event to all delegates registered with the AdobeAnalyticsSession.
*
* param action The name of the timed action event being reported.
* param data The data associated with the action.
*/
- (void)trackTimedActionUpdate:(NSString *)action data:(NSDictionary *)data;

/**
* brief Reports the data for an analytics "timed action end" event to all delegates registered with the AdobeAnalyticsSession.
*
* param action The name of the timed action event being reported.
* param block If you provide block, you will have access to the final time values and be
* able to manipulate data prior to sending the final hit. If you provide block, you must
* return YES to send a hit. Passing in nil for block sends the final hit.
*/
- (void)trackTimedActionEnd:(NSString *)action
logic:(BOOL (^) (NSTimeInterval inAppDuration,
NSTimeInterval totalDuration,
NSMutableDictionary *data))block;

@end

#endif
