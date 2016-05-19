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

#ifndef AdobePhotoAssetRenditionHeader
#define AdobePhotoAssetRenditionHeader

typedef NSArray AdobePhotoAssetRenditions;

/**
 * List of rendition types.
 */
typedef NS_ENUM (NSInteger, AdobePhotoAssetRenditionType)
{
    /** Full size */
    AdobePhotoAssetRenditionTypeImageFullSize,
    /** Favorite */
    AdobePhotoAssetRenditionTypeImageFavorite,
    /** Panorama */
    AdobePhotoAssetRenditionTypeImagePanorama,
    /** 2048x2048 */
    AdobePhotoAssetRenditionTypeImage2048,
    /** 1280x1280 */
    AdobePhotoAssetRenditionTypeImage1280,
    /** 1024x1024 */
    AdobePhotoAssetRenditionTypeImage1024,
    /** 640x640 */
    AdobePhotoAssetRenditionTypeImage640,
    /** Retina thumbnail */
    AdobePhotoAssetRenditionTypeImageThumbnail2x,
    /** Thumbnail */
    AdobePhotoAssetRenditionTypeImageThumbnail,
};

/**
 * An asset rendition.
 */
@interface AdobePhotoAssetRendition : NSObject <NSCopying, NSCoding>

/**
 * The asset renditions's data path.
 */
@property (nonatomic, readonly, strong) NSURL *dataPath;

/**
 * The asset rendition ID
 */
@property (nonatomic, readonly, strong) NSString *GUID;

/**
 * The asset renditions's type.
 */
@property (nonatomic, readonly, assign) AdobePhotoAssetRenditionType type;

/**
 * Create a new rendition.
 * @param path The path to the rendition data. The path must be locally valid and cannot be nil.
 * @param type The type of rendtion.
 * @returns a new AdobePhotoAssetRendition
 */
- (id)initWithPath:(NSURL *)path
          withType:(AdobePhotoAssetRenditionType)type __deprecated_msg("Use initWithPath:type");

- (instancetype)initWithPath:(NSURL *)path
                        type:(AdobePhotoAssetRenditionType)type;

@end

#endif /* ifndef AdobePhotoAssetRenditionHeader */
