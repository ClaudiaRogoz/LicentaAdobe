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

#ifndef AdobeiTunesServiceSessionHeader
#define AdobeiTunesServiceSessionHeader

#import <Foundation/Foundation.h>

@class AdobeNetworkHTTPService;

/**
*  A completion block that is used in API calls to AiTS.
*
*  @param results Depending on the API, a set of results or nil if none are available.
*  @param error   An NSError object that is non-nil on error.
*/
typedef void (^AdobeiTunesServiceSessionCompletionBlock)(NSArray *results, NSError *error);

/** Domain for kAccountService-created errors . */
static NSString *const kAccountServiceErrorDomain = @"AccountService";

/* Error codes returned by AITS as defined at
* https://zerowing.corp.adobe.com/display/Suites/Adobe+iTunes+Service+Interface
* that the client may be able to do something about.
*
* AccountService/getProductIDsWithCompletionBlock: can return
* kAccountServiceErrorCodeInvalidTouchApp,
* kAccountServiceErrorCodeInvalidProductOffering,
* kAccountServiceErrorCodeReauthenticatonNeeded,
* kAccountServiceErrorCodeTimeOut
*
* AccountService/postITunesReceipt:withCompletionBlock: can return
* kAccountServiceErrorCodeInvalidTouchApp,
* kAccountServiceErrorCodeReceiptValidationFailed,
* kAccountServiceErrorCodeReceiptExpired,
* kAccountServiceErrorCodeAlreadyActiveSubscription,
* kAccountServiceErrorCodeReauthenticatonNeeded,
* kAccountServiceErrorCodeTimeOut
*/

typedef NS_ENUM (int, AccountServiceErrorCode)
{
kAccountServiceErrorCodeUnknown = 0,
kAccountServiceErrorCodeReauthenticatonNeeded = 1,
kAccountServiceErrorCodeInvalidTouchApp = 2,

// receipt validation failed from Apple iTunes server
kAccountServiceErrorCodeReceiptValidationFailed = 3,
kAccountServiceErrorCodeReceiptExpired = 4,

// duplicate receipt, i.e. sending same receipt from a different Adobe ID
kAccountServiceErrorCodeDuplicateReceipt = 5,

// invalid product (offering not configured in iTunes Service db)
kAccountServiceErrorCodeInvalidProductOffering = 6,

// already an active subscription against sa    me person guid and apple transaction i.e. a duplicate claim request
kAccountServiceErrorCodeAlreadyActiveSubscription = 7,
kAccountServiceErrorCodeTimeOut = 8
};

@interface AdobeiTunesServiceSession : NSObject

/**
*  Initializes this object with an AdobeNetworkHTTPService object that has been appropriately initialized
*  for use with the Adobe iTunes Service.
*
*  @param service the service to initialize with
*
*  @return An instance of AdobeiTunesServiceSession
*/
- (id)initWithHTTPService:(AdobeNetworkHTTPService *)service;

/**
*  Attempts to fetch available product id for the currently authenticated user.
*
*  @param completionBlock A completion block that is called upon success or failure.
*/
- (void)requestProductIDsWithCompletionBlock:(AdobeiTunesServiceSessionCompletionBlock)completionBlock;

/**
*  Attempts to validate base64 IAP receipt data for a a given productID.
*
*  @param receiptData     Base64 encoded receipt data.
*  @param productID       The product ID to which the receipt corresponds.
*  @param completionBlock A completion block that is called upon success or failure.
*/
- (void)postITunesReceipt:(NSData *)receiptData
productID:(NSString *)productID
withCompletionBlock:(AdobeiTunesServiceSessionCompletionBlock)completionBlock;

@end

#endif
