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

#ifndef AdobeNetworkUtilsHeader
#define AdobeNetworkUtilsHeader

#import <Foundation/Foundation.h>

/**
* brief Miscellaneous network-related helper methods.
*/
@interface AdobeNetworkUtils : NSObject

+ (NSDictionary *)lowerCaseKeyedCopyOfDictionary:(NSDictionary *)source;

+ (NSString *)rfc2047DecodeValue:(NSString *)inputValue;
+ (NSString *)rfc5987EncodeValue:(NSString *)inputValue forKey:(NSString *)inputKey;

+ (NSDictionary *)decodeResponseHeaders:(NSDictionary *)source;
+ (NSDictionary *)encodeRequestHeaders:(NSDictionary *)source;

+ (NSDictionary *)parseAndDecodeHTTPHeadersFromString:(NSString *)headers;

+ (NSString *)encodeQueryParameterForURLWithString:(NSString *)string;
+ (NSString *)encodePathForURLWithString:(NSString *)pathString;

/**
* brief Returns YES if resourceURL can be used to refer to server resources hosted by a service endpoint at serviceURL.
*
* param resourceURL The URL of the resource being referenced. May be a fully-qualified, absolute, or relative URL
* param serviceURL  Must be a fully-qualified URL that a minimum specifies a host
*
* note If resourceURL is missing a host then this routine will return YES since the resource can be resolved
* relative to sourceURL
*/
+ (BOOL)isURL:(NSURL *)resourceURL compatibleWithServiceEndpointAtURL:(NSURL *)serviceURL;


/**
* brief Determines, if possible, whether two URLs refer to resources hosted by the same service endpoint
*
* param firstURL  A fully-qualified, absolute, or relative URL.
* param secondURL A fully-qualified, absolute, or relative URL.
*
* return If both URLs are fully-qualified then determines whether they refer to the same service endpoint.
* If either or neither URL is fully-qualified then returns NO since we can not determine with certainty that
* the endpoints are incompatible.
*
* notes This routine only examines the URL and does not perform any DNS translation.
*/
+ (BOOL)isURL:(NSURL *)firstURL incompatibleWithURL:(NSURL *)secondURL;

@end

#endif
