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

#ifndef AdobeNotificationSessionHeader
#define AdobeNotificationSessionHeader

#import <Foundation/Foundation.h>

#import <AdobeCreativeSDKAssetModelOSX/AdobeSendToDesktopApplication.h>

@class AdobeNetworkHTTPRequest;
@class AdobeNetworkHTTPResponse;
@class AdobeNetworkHTTPService;

static NSString *_serviceEndpointURL;

/**
* Provides an Objective-C binding of the Send to Desktop Service API.
* Must be initialized with an instance of AdobeNetworkHTTPService, which in turn provides the configuration
* necessary to speak to a specific CC environment (e.g., stage or production).
* See AdobeNotificationSession:initWithHTTPService.
*/
@interface AdobeNotificationSession : AdobeCloudServiceSession

/**
* brief Returns an AdobeNotificationSession singleton initialize with endpoint and user token
*/
+ (AdobeNotificationSession *)sharedSession;

/**
* brief Create a send to desktop application request.
*
* param cloudAsset          Asset name.
* param targetName          Name on the destination application.
* param cloud               Asset source cloud.  A nil value refers to the default cloud.
* param pushToApplication   Application to send the asset to.
*/
- (NSMutableURLRequest *)requestFor:(NSString *)cloudAsset
targetName:(NSString *)targetName
cloud:(AdobeCloud *)cloud
pushToApplication:(AdobeCreativeCloudApplication)pushToApplication;

/**
* brief Gets the response of the specified request asynchronously.
*
* param request  The request to get the response for.
* param priority The prioprity of the HTTP request.
* param handler  Called when the upload has finished or failed.
*/
- (AdobeNetworkHTTPRequest *)responseFor:(NSMutableURLRequest *)request
requestPriority:(NSOperationQueuePriority)priority
completionHandler:(void (^)(AdobeNetworkHTTPResponse *response))handler;

/**
* brief Gets the response of the specified request synchronously.
*
* Regardless of delays, this method blocks until HTTP request has completed.
*
* param request  The request to get the response for.
* param priority The priority of the HTTP request.
*
* return The response
*/
- (AdobeNetworkHTTPResponse *)responseFor:(NSMutableURLRequest *)request
requestPriority:(NSOperationQueuePriority)priority;

/**
* brief Sets the class' serviceEndpointURL.
*
* param endpointURL           New endpointURL.
*/
+ (void)setServiceEndpointURL:(NSString *)endpointURL;

/**
* brief Gets the class' serviceEndpointURL.
*/
+ (NSString *)serviceEndpointURL;

@end

#endif
