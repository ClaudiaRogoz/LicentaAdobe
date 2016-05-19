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

#ifndef AdobeEntitlementSessionHeader
#define AdobeEntitlementSessionHeader

#import <Foundation/Foundation.h>

#import <AdobeCreativeSDKCoreOSX-Internal/AdobeCloudServiceSession.h>

@class AdobeAuthUserProfile;

extern NSString *const AdobeEntitlementUserProfileCountryCode;
extern NSString *const AdobeEntitlementUserProfileDisplayName;
extern NSString *const AdobeEntitlementUserProfileDeveloperMode;
extern NSString *const AdobeEntitlementUserProfileEmail;
extern NSString *const AdobeEntitlementUserProfileEmailVerified;
extern NSString *const AdobeEntitlementUserProfileFirstName;
extern NSString *const AdobeEntitlementUserProfileIsEnterprise;
extern NSString *const AdobeEntitlementUserProfileLastName;
extern NSString *const AdobeEntitlementUserProfileName;
extern NSString *const AdobeEntitlementUserProfilePhoneNumber;
extern NSString *const AdobeEntitlementUserProfileLanguages;
extern NSString *const AdobeEntitlementUserProfileUserId;
extern NSString *const AdobeEntitlementUserProfileUTCOffset;

// Keys in the ES JSON data
extern NSString *const AdobeEntitlementSessionESDataEndpointsKey;
extern NSString *const AdobeEntitlementSessionESDataServicesKey;
extern NSString *const AdobeEntitlementSessionESDataEntitledKey;
extern NSString *const AdobeEntitlementSessionESDataServiceLevelKey;
extern NSString *const AdobeEntitlementSessionESDataPublicCloudStorageKey;
extern NSString *const AdobeEntitlementSessionESDataPrivateCloudStorageKey;

@class AdobeNetworkHTTPRequest;
@class AdobeNetworkHTTPService;

/**
* Provides an Objective-C binding of the Entitlement Service API.
* Must be initialized with an instance of AdobeNetworkHTTPService, which in turn provides the configuration
* necessary to speak to a specific CC environment (e.g., stage or production).
* See AdobeEntitlementSession:initWithHTTPService.
*/
@interface AdobeEntitlementSession : AdobeCloudServiceSession

/**
* brief Returns an AdobeEntitlementSession singleton initialize with endpoint and user token
*/
+ (AdobeEntitlementSession *)sharedSession;

/**
* brief Refreshes the AdobeCloudEndpoint for the IMS setting.
*/
- (void)refreshEndpoint;

/**
* brief                     Get user profile synchronously from the cache.
* return                    The user profile if it is in the cache, else nil.
*/
- (NSDictionary *)userProfileFromCache;

/**
* brief                     Get user profile for the passed in access token asynchronously.
* param priority            The relative priority of the HTTP request.
* param queue               If not nil queue determines the operation queue handler gets executed on.
* param completionBlock     Called when the fetch has finished, failed or if it has been cancelled.
* return                    An AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)userProfileWithPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionBlock:(void (^)(NSDictionary *profileData, BOOL hasChanged, NSError *error))completionBlock;

/**
* brief                     Get user profile for the passed in access token synchronously.
* param priority            The relative priority of the HTTP request.
* param errorPtr            An optional pointer to an NSError object that will be set in case of an error.
* return                    A NSDictionary of the user profile.
*/
- (NSDictionary *)userProfileWithPriority:(NSOperationQueuePriority)priority
error:(NSError **)errorPtr;

/**
* brief                     Get the AdobeClouds from the user profile data.
* param userProfileItems    The user profile dictionary.
* param outputArray         The endpoints returned from the user profile.
* param error               An optional pointer to an NSError object that will be set in case of an error.
* return                    Returns NO if an error occurred.
*/
- (BOOL)cloudsFromUserProfile:(NSDictionary *)userProfileItems
outputArray:(NSMutableArray **)output
error:(NSError **)error;

/**
* brief                     Get services from the user profile data.
* param userProfileItems    The user profile dictionary.
* param outputArray         The services returned from the user profile.
* param error               An optional pointer to an NSError object that will be set in case of an error.
* return                    Returns NO if an error occurred.
*/
- (BOOL)servicesFromUserProfile:(NSDictionary *)userProfileItems
outputDictionary:(NSMutableDictionary **)output
error:(NSError **)error;

@end

#endif
