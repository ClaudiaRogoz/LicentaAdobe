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

#ifndef AdobeImageOutputParamsHeader
#define AdobeImageOutputParamsHeader

#import <Foundation/Foundation.h>

@class AdobeStorageResourceItem;

/** Various AdobeImageSession methods use this enumeration to specify how outputs are handled. */

typedef NS_ENUM (NSInteger, AdobeImageOutputDisposition)
{
AdobeImageOutputDispositionNone,
AdobeImageOutputDispositionDownload,
AdobeImageOutputDispositionReference
};

@interface AdobeImageOutputParameters : NSObject

/** Disposition; see enum above. */
@property (nonatomic) AdobeImageOutputDisposition disposition;

/** A media range value, as defined by HTTP 1.1 accept: headers. */
@property (nonatomic) NSString *mediaRange;

/** The file locations to write the result images to. null if disposition is equal AdobeImageOutputDispositionNone*/
@property (nonatomic) NSString *location;

/** Whether to overwrite the result image file location. */
@property (nonatomic, assign) BOOL overwrite;

/** if disposition is DispositionDownload then path cannot be nil*/
@property (nonatomic) NSString *path;

/** if disposition is DispositionDownload then paths cannot be nil*/
@property (nonatomic) NSMutableDictionary *paths;

@end

#endif
