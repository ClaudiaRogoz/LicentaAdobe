/*************************************************************************
*
* ADOBE CONFIDENTIAL
* ___________________
*
*  Copyright 2014 Adobe Systems Incorporated
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

#ifndef AdobeAnalyticsSessionHeader
#define AdobeAnalyticsSessionHeader

#import <Foundation/Foundation.h>

/**
* brief The AdobeAnalyticsSessionDelegate protocol
*
* The AdobeAnalyticsSessionDelegate is a protocol that clients of the Creative SDK should
* implement and register with the AdobeAnalyticsSession in order to receive analytics
* events from the Creative SDK. Clients should pass the data received through to the
* equivalent ADBMobile Analytics SDK methods, modifying any parameters as necessary.
*/
@protocol AdobeAnalyticsSessionDelegate

/**
* brief Track the data for an analytics "state" event generated within the Creative SDK.
*
* Reports the data for an analytics "state" event generated within the Creative SDK to
* clients registered with the AdobeAnalyticsSession. Clients of the Creative SDK can then
* forward this information to the Adobe analytics service if it is an event they would
* like to have tracked. Clients should pass the parameters through to the ADBMobile SDK's
* equivalent method, modified as necessary.
*
* param state The name of the state event being reported.
* param data The data associated with the action.
*/
- (void)trackState:(NSString *)state data:(NSDictionary *)data;

/**
* brief Track the data for an analytics "action" event generated within the Creative SDK.
*
* Reports the data for an analytics "action" event generated within the Creative SDK to
* clients registered with the AdobeAnalyticsSession. Clients of the Creative SDK can then
* forward this information to the Adobe analytics service if it is an event they would
* like to have tracked. Clients should pass the parameters through to the ADBMobile SDK's
* equivalent method, modified as necessary.
*
* param action The name of the action event being reported.
* param data The data associated with the action.
*/
- (void)trackAction:(NSString *)action data:(NSDictionary *)data;

/**
* brief Track the data for an analytics "timed action start" event generated within the Creative SDK.
*
* Reports the data for an analytics "timed action start" event generated within the Creative
* SDK to clients registered with the AdobeAnalyticsSession. Clients of the Creative SDK can
* then forward this information to the Adobe analytics service if it is an event they would
* like to have tracked. Clients should pass the parameters through to the ADBMobile SDK's
* equivalent method, modified as necessary.
*
* param action The name of the timed action event being reported.
* param data The data associated with the action.
*/
- (void)trackTimedActionStart:(NSString *)action data:(NSDictionary *)data;

/**
* brief Track the data for an analytics "timed action update" event generated within the Creative SDK.
*
* Reports the data for an analytics "timed action update" event generated within the Creative
* SDK to clients registered with the AdobeAnalyticsSession. Clients of the Creative SDK can
* then forward this information to the Adobe analytics service if it is an event they would
* like to have tracked. Clients should pass the parameters through to the ADBMobile SDK's
* equivalent method, modified as necessary.
*
* param action The name of the timed action event being reported.
* param data The data associated with the action.
*/
- (void)trackTimedActionUpdate:(NSString *)action data:(NSDictionary *)data;

/**
* brief Track the data for an analytics "timed action end" event generated within the Creative SDK.
*
* Reports the data for an analytics "timed action end" event generated within the Creative
* SDK to clients registered with the AdobeAnalyticsSession. Clients of the Creative SDK can
* then forward this information to the Adobe analytics service if it is an event they would
* like to have tracked. Clients should pass the parameters through to the ADBMobile SDK's
* equivalent method, modified as necessary.
*
* param action The name of the timed action event being reported.
* param block If provided, indicates that the block should be sent to the ADBMobile SDK's
* equivalent method so that the Creative SDK can get access to the duration information and
* provide the proper hit-handling response. Clients may wrap this in their own block as
* necessary, as long as they ensure that the Creative SDK's logic block gets invoked.
*/
- (void)trackTimedActionEnd:(NSString *)action
logic:(BOOL (^) (NSTimeInterval inAppDuration,
NSTimeInterval totalDuration,
NSMutableDictionary *data))block;

@end

/**
* class AdobeAnalyticsSession
* brief A singleton "analytics session" class.
*
* Provides a singleton session object through which clients can register to receive analytics
* data generated by the CreativeSDK.
*
* Clients applications use the 'sharedSession' method to grab the shared analytics session
* singleton with which they can then register their AdobeAnalyticsSessionDelegate instance
* using the 'registerDelegate' method.
*/
@interface AdobeAnalyticsSession : NSObject

/**
* brief Get the shared AdobeAnalyticsSession.
*
* Get the AdobeAnalyticsSession singleton instance through which all analytics reporting from
* the Creative SDK occurs. Client applications, after having retrieved this instance, should
* register their AdobeAnalyticsSessionDelegate using the 'registerDelegate' method.
*
* return The AdobeAnalyticsSession singleton object.
*/
+ (AdobeAnalyticsSession *)sharedSession;

/**
* brief Register an AdobeAnalyticsSessionDelegate instance.
*
* Register an AdobeAnalyticsSessionDelegate instance with the AdobeAnalyticsSession singleton
* instance. The AdobeAnalyticsSession instance will maintain a weak reference to the registered
* delegate and send reporting events to it as long as it exists. Clients should ensure that they
* maintain a strong reference to the delegate for the lifetime during which reporting is needed.
* Clients may (optionally) unregister their delegate explicitly using the unregisterDelegate method.
*
* param delegate A delegate to which all reporting events should be sent. A delegate can only
* be registered once, therefore calling registerDelegate more than once with the same delegate
* instance will be a no op.
* param queue The thread queue on which the delegate should be invoked. If nil the delegate
* will be invoked on the main thread.
*/
- (void)registerDelegate:(id<AdobeAnalyticsSessionDelegate>)delegate
withHandlerQueue:(NSOperationQueue *)queue;

/**
* brief Unregister a previously registered AdobeAnalyticsSessionDelegate instance.
*
* Unregister a previously registered AdobeAnalyticsSessionDelegate instance from the
* AdobeAnalyticsSession singleton.
*
* param delegate The delegate instance that should be unregistered.
*/
- (void)unregisterDelegate:(id<AdobeAnalyticsSessionDelegate>)delegate;

@end

#endif
