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
*
******************************************************************************/

#ifndef AdobeUXAuthManagerProtectedHeader
#define AdobeUXAuthManagerProtectedHeader

#import <Foundation/Foundation.h>

/**
* This notification is sent through the NSNotificationManager when a silent token refresh succeeds.
*/
extern NSString *const AdobeAuthManagerRefreshedTokenNotification;

/**
* For calls to the Behance API that require the user's Adobe ID to be linked with the
* corresponding Behance ID, the following header value is returned in the response to those API
* calls. Currently the only valid value for this key is the string "not-linked".
*/
extern NSString *const AdobeAuthManagerAdobeIDLinkingReasonResponseHeaderKey;

/**
* The only valid value for the @c AdobeAuthManagerAdobeIDLinkingReasonResponseHeaderKey which is
* equivalent to "not-linked," meaning the Adobe ID is present and matches an account on the
* Behance side, but the accounts are not linked.
*/
extern NSString *const AdobeAuthManagerAdobeIDLinkingReasonResponseHeaderValueNotLinked;

/**
* For calls to the Behance API that require the user's Adobe ID to be linked with the
* corresponding Behance ID, the following header value is returned in the response to those API
* calls. The value for this key is the URL for the linking UI that the user should use to link
* their two accounts.
*/
extern NSString *const AdobeAuthManagerAdobeIDLinkingURLResponseHeaderKey;

/**
* Notification indicating that an Adobe ID was successfully linked to a Behance account
*/
extern NSString *const AdobeAuthManagerAdobeIDLinkingSuccessNotification;

@interface AdobeUXAuthManager (Protected)

typedef NS_ENUM (NSInteger, AdobeAuthInteraction)
{
AdobeAuthInteractionHeadless,
AdobeAuthInteractionInteractive
};

// @note: do not call this on the main thread... it blocks!
- (BOOL)reauthenticate;

+ (NSData *)certificateData:(NSString *)certName;

- (void)loginInternal:(AdobeAuthInteraction)allowUserInteration
animateOnStart:(BOOL)animateStart
animateOnComplete:(BOOL)animateComplete
onSuccess:(void (^)(NSString *adobeID, NSString *accessToken))successBlock
onError:(void (^)(NSError *error))errorBlock;

- (void)loginInternal:(AdobeAuthInteraction)allowUserInteration
animateOnStart:(BOOL)animateStart
animateOnComplete:(BOOL)animateComplete
embedInParent:(BOOL)shouldEmbed
onSuccess:(void (^)(NSString *adobeID, NSString *accessToken))successBlock
onError:(void (^)(NSError *error))errorBlock;

#ifndef DMALIB
- (void)        login:(UIViewController *)parentViewController
animateOnStart:(BOOL)animateStart
animateOnComplete:(BOOL)animateComplete
embedInParent:(BOOL)shouldEmbed
onSuccess:(void (^)(AdobeAuthUserProfile *profile))successBlock
onError:(void (^)(NSError *error))errorBlock;

- (void)        login:(UIViewController *)parentViewController
animateOnStart:(BOOL)animateStart
animateOnComplete:(BOOL)animateComplete
onSuccess:(void (^)(AdobeAuthUserProfile *profile))successBlock
onError:(void (^)(NSError *error))errorBlock;

- (void)setParentViewController:(UIViewController *)parent;

/**
* Presents the account linking UI in a webview on @c parentViewController. If
* @c parentViewController is nil, either top-most presented view controller or the main window is
* used.
*
* @param parentViewController The view controller to present the linking UI on top of.
* @param url                  Behance endpoint URL
* @param successBlock         Success block
* @param errorBlock           Error block
*/
- (void)presentBehanceAccountLinkingControllerWithParent:(UIViewController *)parentViewController
endpointURL:(NSURL *)url
onSuccess:(void (^)(void))successBlock
onError:(void (^)(NSError *error))errorBlock;

#endif // !DMALIB

@end

#endif
