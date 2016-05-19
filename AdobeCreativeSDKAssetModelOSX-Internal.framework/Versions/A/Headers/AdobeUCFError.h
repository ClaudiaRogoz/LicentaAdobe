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

#ifndef AdobeUCFErrorHeader
#define AdobeUCFErrorHeader

#import <Foundation/Foundation.h>

/** The domain for 360-related errors */
extern NSString *const AdobeUCFErrorDomain;

/**
* brief Error codes for the 360 error domain.
*/
typedef NS_ENUM (NSInteger, AdobeUCFErrorCode)
{
/**
* brief The archive file or data was invalid
*/
AdobeUCFErrorArchiveInvalid = 0,

/**
* brief An error occurred while creating the archive file
*/
AdobeUCFErrorArchiveCreateFailed = 1,

/**
* brief An error occurred while writing to the filesystem during an archive operation
*/
AdobeUCFErrorArchiveWriteFailed = 2,

/**
* brief An error occurred while reading from the filesystem during an archive operation
*/
AdobeUCFErrorArchiveReadFailed = 3,

/**
* brief An archive operation was canceled at the request of the client
*/
AdobeUCFErrorOperationCancelled = 4

};

#endif
