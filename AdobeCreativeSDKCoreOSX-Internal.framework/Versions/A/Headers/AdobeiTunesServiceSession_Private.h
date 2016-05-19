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

#ifndef AdobeiTunesServiceSessionPrivateHeader
#define AdobeiTunesServiceSessionPrivateHeader

#import <AdobeCreativeSDKCoreOSX-Internal/AdobeiTunesServiceSession.h>

@interface AdobeiTunesServiceSession ()

/**
*  Takes an NSDictionary and converts it into an XML string.
*
*  @param dict An NSDictionary to convert into XML.
*
*  @return An XML representation of @c dict in an NSString object.
*
*  @note Acceptable keys must be of type: @c NSString. Acceptable values must of types: @c NSString, @c NSValue or
*  @c NSDictionary--@c NSArray values are @b not supported.
*/
- (NSString *)xmlStringFromDictionary:(NSDictionary *)dict;

@end

#endif
