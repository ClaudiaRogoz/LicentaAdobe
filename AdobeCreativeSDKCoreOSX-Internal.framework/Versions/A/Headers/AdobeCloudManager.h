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

#ifndef AdobeCloudManagerHeader
#define AdobeCloudManagerHeader

#import <Foundation/Foundation.h>

#import <AdobeCreativeSDKCoreOSX-Internal/AdobeCloud.h>

/**
* Dispatched when the cloud manager has updated its array of clouds.
*/
extern NSString *const AdobeCloudManagerCloudsUpdatedNotification;

/**
* Dispatched when the cloud manager's default cloud has been changed.
* The default cloud is passed as the object associated with the notification.
*/
extern NSString *const AdobeCloudManagerDefaultCloudUpdatedNotification;

/**
* AdobeCloudManager is a component that manages a collection of AdobeCloud objects.
*
* refreshClouds:error: needs to be called during the application startup before using the Creative SDK.
*
* Note that AdobeCloudManager should not be used before the AdobeUXAuthManager has
* been configured.
*/
@interface AdobeCloudManager : NSObject

/**
* A list of clouds currently being managed.
*/
@property (nonatomic, readonly, strong) NSArray *clouds;

/**
* The default cloud.
*/
@property (nonatomic, strong) AdobeCloud *defaultCloud;

/**
* The singleton object for the AdobeCloudManager.
*/
+ (AdobeCloudManager *)sharedManager;

/**
* Asynchronously update the cloud manager with the user's available clouds.
*
* Note: Completion blocks will be invoked on the main thread.
*/
- (void)refreshClouds:(void (^)(NSArray *clouds))successBlock
error:(void (^)(NSError *error))errorBlock;

/**
* Synchronously update the cloud manager with the user's available clouds.
*
* Note: This call will block the thread on which it is invoked until the
* the underlying network operation completes. Do not invoke this on the
* main thread if you do not want the main thread to block during execution.
*
* Usage: This call is meant to be invoked primarily at app launch if the
* following conditions hold:
*    a) The user is already authenticated
*    b) defaultCloud is set to nil
*
* If these conditions hold, then it is possible that we have never queried
* the entitlement service to get the user's set of clouds, and applications
* that cannot proceeed in a state without a default cloud can use this call
* to block until the user's clouds are fetched.
*
* @param errorPtr The error status if the return result is NO.
*
* @returns YES if the operation completed successfully; if NO then consult
* the returned error.
*/
- (BOOL)refreshCloudsWithError:(NSError **)errorPtr;

@end

#endif
