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

#ifndef AdobeEntitlementErrorHeader
#define AdobeEntitlementErrorHeader

/** The domain for Adobe Entitlement errors.  When NSErrors are delivered to AdobeEntitlement code blocks,
*  the domain property of the NSError will be set to the value of this string constant when
*  the NSError is an AdobeEntitlement error.
*/
extern NSString *const AdobeEntitlementErrorDomain;

/**
* Error codes for the AdobeEntitlementErrorDomain domain.
*/
typedef NS_ENUM (NSInteger, AdobeEntitlementErrorCode)
{
/**
* A response from the server did not match its anticipated form and therefore
* could not be processed.
*
* This could be caused by an unexpected HTTP response code or missing/malformed data.
* Typically this indicates a (temporary) problem with the server or the network.
*
* The userInfo property of the error often contains additional information via
* the AdobeNetworkRequestURLKey, AdobeNetworkResponseDataKey, AdobeNetworkHTTPStatusKey, AdobeErrorResponseHeadersKey
* and NSUnderlyingErrorKey keys.
*/
AdobeEntitlementErrorUnexpectedResponse = 2,

/**
* An attempt was made to use an empty JSON payload.
*/
AdobeEntitlementErrorMissingJSONData = 11,

/**
* No clouds returned for the user.
*/
AdobeEntitlementErrorNoCloudsAvailable = 12,

/**
* No services returned for the user.
*/
AdobeEntitlementErrorNoServicesAvailable = 13
};

#endif
