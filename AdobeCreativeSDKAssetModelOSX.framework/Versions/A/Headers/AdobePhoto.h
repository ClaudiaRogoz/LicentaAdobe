/******************************************************************************
 *
 * ADOBE CONFIDENTIAL
 * ___________________
 *
 * Copyright 2014 Adobe Systems Incorporated
 * All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains the property of
 * Adobe Systems Incorporated and its suppliers, if any. The intellectual and
 * technical concepts contained herein are proprietary to Adobe Systems
 * Incorporated and its suppliers and are protected by trade secret or
 * copyright law. Dissemination of this information or reproduction of this
 * material is strictly forbidden unless prior written permission is obtained
 * from Adobe Systems Incorporated.
 ******************************************************************************/

#ifndef AdobePhotoHeader
#define AdobePhotoHeader

#import <Foundation/Foundation.h>

@class AdobeCloud;

/**
 * AdobePhoto is the base class of an object that is on the Adobe Photo Service.
 * It is extended by AdobePhotoCollection, AdobePhotoAsset, and AdobePhotoCatalog.
 *
 */
@interface AdobePhoto : NSObject <NSCopying, NSCoding>

/**
 * The base href of the item.
 */
@property (readonly, nonatomic, strong) NSString *baseHref;

/**
 * The creation date of the item.
 */
@property (readonly, nonatomic, strong) NSDate *creationDate;

/**
 * The unique identifier of the item.
 */
@property (readonly, nonatomic, strong) NSString *GUID;

/**
 * The remote href of the item.
 */
@property (readonly, nonatomic, strong) NSString *href;

/**
 * The internal id of the item.
 */
@property (readonly, nonatomic, strong) NSString *internalID;

/**
 * The modification date of the item.
 */
@property (readonly, nonatomic, strong) NSDate *modificationDate;

/**
 * A utility to test the equality of two AdobePhotos.
 *
 * @param item the AdobePhoto to test against.
 */
- (BOOL)isEqualToPhoto:(AdobePhoto *)item;

@end

#endif
