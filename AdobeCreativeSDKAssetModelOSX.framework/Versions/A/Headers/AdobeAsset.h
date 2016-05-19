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

#ifndef AdobeAssetHeader
#define AdobeAssetHeader

#import <Foundation/Foundation.h>

@class AdobeCloud;

/**
 * AdobeAsset is the base class of an object that is on the Adobe Creative Cloud.
 * It is extended by AdobeAssetFile, AdobeAssetFolder, AdobeAssetPSDFile, AdobeAssetSketchbook,
 * AdobeAssetLineFile, AdobeAssetDrawFile, and AdobeAssetLibrary classes.
 *
 */
@interface AdobeAsset : NSObject <NSCopying, NSCoding>

/**
 * The cloud instance this asset belongs to.
 */
@property (readonly, nonatomic, strong) AdobeCloud *cloud;

/**
 * The creation date of the item.
 */
@property (readonly, nonatomic, strong) NSDate *creationDate;

/**
 * The etag of the item.
 */
@property (readonly, nonatomic, strong) NSString *etag;

/**
 * The unique identifier of the item.
 */
@property (readonly, nonatomic, strong) NSString *GUID;

/**
 * The remote href of the item.
 */
@property (readonly, nonatomic, strong) NSString *href;

/**
 * The modification date of the item.
 */
@property (readonly, nonatomic, strong) NSDate *modificationDate;

/**
 * The name of the item.
 */
@property (readonly, nonatomic, strong) NSString *name;

/**
 * The remote href of the enclosing parent of the item.
 */
@property (readonly, nonatomic, strong) NSString *parentHref;

/**
 * The type of the item.
 */
@property (readonly, nonatomic, strong) NSString *type;

/**
 * A utility to test the equality of two AdobeAssets.
 *
 * @param item the AdobeAsset to test against.
 */
- (BOOL)isEqualToAsset:(AdobeAsset *)item;

@end

typedef NSArray AdobeAssetArray;

#endif /* ifndef AdobeAssetHeader */
