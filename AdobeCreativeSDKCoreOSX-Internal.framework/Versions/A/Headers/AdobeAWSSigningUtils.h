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

#ifndef AdobeAWSSigningUtilsHeader
#define AdobeAWSSigningUtilsHeader

#import <Foundation/Foundation.h>

@interface AdobeAWSSigningUtils : NSObject

+ (NSString*)canonicalRequestWithMethod:(NSString*)method
path:(NSString*)path
query:(NSString*)query
headers:(NSDictionary *)headers
contentSha256:(NSString*)contentSha256;

// Returns "yyyyMMdd" formatted date string
+ (NSString*)shortDateStampWithDate:(NSDate*)date;

// Returns ISO-8601 variant suitable for the X-Amz-Date header
+ (NSString*)xAmzDateStampWithDate:(NSDate*)date;

+ (NSString *)scopeStringWithDate:(NSDate*)date region:(NSString*)region service:(NSString*)service;

+ (NSData*)deriveV4KeyFromSecret:(NSString*)secret
date:(NSDate*)date
region:(NSString*)region
service:(NSString*)service;

+ (NSString*)signedHeadersString:(NSDictionary *)headers;

+ (NSString*)v4SignatureStringWithRequest:(NSURLRequest*)urlRequest
contentSha256:(NSString*)contentSha256
scope:(NSString*)scope
derivedKey:(NSData*)derivedKey;

+ (NSString*)v4AuthorizationStringWithRequest:(NSURLRequest*)urlRequest
accessKey:(NSString*)accessKey
scope:(NSString*)scope
signature:(NSString*)signature;

+ (NSMutableURLRequest*)updateURLRequestWithV4SignedQueryString:(NSMutableURLRequest*)urlRequest
accessKey:(NSString*)accessKey
secretKey:(NSString*)secretKey
sessionToken:(NSString*)sessionToken
regionName:(NSString*)region
serviceName:(NSString*)service;
@end

#endif
