/*************************************************************************
*
* ADOBE CONFIDENTIAL
* ___________________
*
*  Copyright 2013 Adobe Systems Incorporated
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

// Reviewed by rhorns on October 14, 2013

#ifndef AdobeStorageUtilsHeader
#define AdobeStorageUtilsHeader

#import <Foundation/Foundation.h>

/**
* brief Miscellaneous helper methods.
*/
@interface AdobeStorageUtils : AdobeCommonUtils

#pragma mark - Parsing Methods
/** name Helper methods */
/**@{*/

/**
* brief Wrapper for constructing an object from an NSData object containing JSON.
*
* Checks for for nil data pointer in order to avoid unexpected illegal argument exception.
*/

+ (id)JSONObjectWithData:(NSData *)data options:(NSJSONReadingOptions)opt error:(NSError **)errorPtr;

+ (NSDate *)convertStringToDate:(NSString *)inputStrDate;

+ (NSString *)convertDateToString:(NSDate *)inputDate;

/**@}*/
#pragma mark - Media type handling
/** name Media type handling */
/**@{*/

/**
* brief Determines if a media type string matches the accepted media types as defined by the HTTP Accept header
* and returns its associated quality score.
*
* param mediaType An Internet media type string
* param acceptedMedia A string identifying a set of accepted media types that adheres to the syntax and semantics defined at http://www.w3.org/Protocols/rfc2616/rfc2616-sec14.html#sec14.1
*
* return A floating point value ranging from 0 to 1.0. A score of 0 implies that there was no match.
*
* note The default quality score of a media type without a 'q' param in the media range is 1. Quoted media type parameters values are not currently supported.
*/
+ (float)qualityScoreForMediaType:(NSString *)mediaType withAcceptHeader:(NSString *)acceptedMedia;

/**
* brief Returns the best match out of a array of media type strings as determined by the media range string using
* HTTP Accept header syntax and semantics
*
* param mediaTypes An array containing one or more Internet media type strings
* param acceptedMedia A string identifying a set of accepted media types that adheres to the syntax and semantics defined at http://www.w3.org/Protocols/rfc2616/rfc2616-sec14.html#sec14.1
*
* return A string containing the Internet media type that was the best match
* note Quoted media type parameters values are not currently supported.
*/
+ (NSString *)bestMatchOfMediaTypes:(NSArray *)mediaTypes withAcceptHeader:(NSString *)acceptedMedia;

/**
* brief Returns an NSDictionary containing the type, subtype, and parameters dictionary of a media type string
* note Quoted media type parameters values are not currently supported.
*/
+ (NSDictionary *)parseMediaType:(NSString *)mediaType;

/**@}*/
@end

#endif /* ifndef AdobeStorageUtilsHeader */
