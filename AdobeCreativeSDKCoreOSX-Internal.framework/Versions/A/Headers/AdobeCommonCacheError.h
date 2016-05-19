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

#ifndef AdobeCommonCacheErrorHeader
#define AdobeCommonCacheErrorHeader

#import <Foundation/Foundation.h>

/** The domain for SDK Cache errors */
extern NSString *const AdobeCommonCacheErrorDomain;

/**
* Error codes for the SDK Cache error domain.
*/
typedef NS_ENUM (NSInteger, AdobeCommonCacheErrorCode){
/**
* A cache could not be created.
*
* The NSLocalizedFailureReasonErrorKey entry in userInfo contains
* more information about the cause of this error.
*/
AdobeCommonCacheErrorCannotCreateCache = 0,

/**
* A cache could not be accessed.
*
* The NSLocalizedFailureReasonErrorKey entry in userInfo contains
* more information about the cause of this error.
*/
AdobeCommonCacheErrorCannotAccessCache = 1
};

#endif
