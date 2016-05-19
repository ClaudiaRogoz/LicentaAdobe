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

#ifndef AdobeCommunityUtilsHeader
#define AdobeCommunityUtilsHeader

#import <Foundation/Foundation.h>

/**
* brief Miscellaneous helper methods.
*/
@interface AdobeCommunityUtils : AdobeCommonUtils

#pragma mark JSON parsing
/** name Helper methods */
/**@{*/

/**
* brief Wrapper for constructing an object from an NSData object containing JSON.
*
* Checks for for nil data pointer in order to avoid unexpected illegal argument exception.
*/

+ (id)JSONObjectWithData:(NSData *)data options:(NSJSONReadingOptions)opt error:(NSError **)errorPtr;

/**@}*/
@end

#endif
