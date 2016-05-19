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

#ifndef AdobeCommonErrorUtilsHeader
#define AdobeCommonErrorUtilsHeader

#import <Foundation/Foundation.h>

@class AdobeNetworkHTTPResponse;

/**
* A set of convenience methods that help constructing errors.
*/
@interface AdobeCommonErrorUtils : NSObject

/**
* Construct an error with the given code and other params.
*
* @param code    The error code
* @param domain  The error domain
* @param URL     An optional NSURL to be recorded in the userInfo via the AdobeNetworkRequestURLStringKey
* @param data    An optional data pointer to be recorded in the userInfo via the AdobeNetworkResponseDataKey
* @param status  The status code to be recorded in the userInfo via the AdobeNetworkHTTPStatusKey
* @param headers An optional pointer to the response headers to be recorded in the userInfo via the AdobeNetworkResponseHeadersKey
* @param error   An optional NSError to be recorded in the userInfo via the NSUnderlyingErrorKey
* @param details An optional NSString to be recorded in the userInfo via the AdobeErrorDetailsStringKey
* @param debugID An optional NSString to be recorded in the userInfo via the
AdobeNetworkHTTPDebugIDKey
*/
+ (NSError *)errorWithCode:(NSInteger)code
domain:(NSString *)domain
URL:(NSURL *)URL
responseData:(NSData *)data
httpStatusCode:(NSInteger)status
headers:(NSDictionary *)headers
underlyingError:(NSError *)error
details:(NSString *)details
debugID:(NSString *)debugID;

/**
* Construct an error with the given code and other params.
*
* @param code    The error code
* @param domain  The error domain
* @param details An optional NSString to be recorded in the userInfo via the AdobeErrorDetailsStringKey
* @param debugID An optional NSString to be recorded in the userInfo via the
AdobeNetworkHTTPDebugIDKey
*/
+ (NSError *)errorWithCode:(NSInteger)code
domain:(NSString *)domain
details:(NSString *)details
debugID:(NSString *)debugID;

/**
* Construct an error with the given code and other params.
*
* @param code    The error code
* @param domain  The error domain
* @param error   An optional NSError to be recorded in the userInfo via the NSUnderlyingErrorKey
* @param details An optional NSString to be recorded in the userInfo via the AdobeErrorDetailsStringKey
* @param debugID An optional NSString to be recorded in the userInfo via the
AdobeNetworkHTTPDebugIDKey
*/
+ (NSError *)errorWithCode:(NSInteger)code
domain:(NSString *)domain
underlyingError:(NSError *)error
details:(NSString *)details
debugID:(NSString *)debugID;

/**
* Construct an error with the given code and other params.
*
* @param code    The error code
* @param domain  The error domain
* @param error   An optional NSError to be recorded in the userInfo via the NSUnderlyingErrorKey
* @param path    An optional NSString containing a path of a file to be recorded in the userInfo via the AdobeErrorPathKey
* @param details An optional NSString to be recorded in the userInfo via the AdobeErrorDetailsStringKey
* @param debugID An optional NSString to be recorded in the userInfo via the
AdobeNetworkHTTPDebugIDKey
*/
+ (NSError *)errorWithCode:(NSInteger)code
domain:(NSString *)domain
underlyingError:(NSError *)error
path:(NSString *)path
details:(NSString *)details
debugID:(NSString *)debugID;

/**
* Construct an error with the given code and other params.
*
* @param code        The error code
* @param domain      The error domain
* @param userInfo    An optional NSDictionary to be used as the userInfo property of the error
*/
+ (NSError *)errorWithCode:(NSInteger)code
domain:(NSString *)domain
userInfo:(NSDictionary *)userInfo;

/**
* Construct an error with the given code and other params.
*
* @param code        The error code
* @param domain      The error domain
* @param response    A AdobeNetworkHTTPResponse to be used to populate the new error with relevant data
* @param details     An optional NSString to be recorded in the userInfo via the AdobeErrorDetailsStringKey
*/
+ (NSError *)errorWithCode:(int)code
domain:(NSString *)domain
response:(AdobeNetworkHTTPResponse *)response
details:(NSString *)details;

/**
* Construct an error with the given code and other params.
*
* @param code        The error code
* @param domain      The error domain
* @param response    AdobeNetworkHTTPResponse to be used to populate the new error with relevant data
* @param error       Optional NSError to be recorded in the userInfo via the NSUnderlyingErrorKey
* @param details     Optional NSString to be recorded in the userInfo via the AdobeErrorDetailsStringKey
*/
+ (NSError *)errorWithCode:(int)code
domain:(NSString *)domain
response:(AdobeNetworkHTTPResponse *)response
underlyingError:(NSError *)error
details:(NSString *)details;

@end

#endif
