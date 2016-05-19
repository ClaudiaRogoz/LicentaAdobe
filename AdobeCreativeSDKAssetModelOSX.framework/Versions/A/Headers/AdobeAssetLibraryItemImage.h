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

#ifndef AdobeAssetLibraryItemImageHeader
#define AdobeAssetLibraryItemImageHeader

#import <AdobeCreativeSDKAssetModelOSX/AdobeAssetLibraryItem.h>

@class AdobeAssetFile;

#define IsAdobeAssetLibraryItemImage(item) ([item isKindOfClass:[AdobeAssetLibraryItemImage class]])

/**
 * AdobeAssetLibraryItemImageFile represents an image item within a library.
 *
 * Deprecated
 */

__deprecated_msg("Use selectedLibraryID and selectedElementIDs in AdobeSelectionLibraryAsset and get corresponding library and elements using AdobeLibraryManager")
@interface AdobeAssetLibraryItemImage : AdobeAssetLibraryItem

/** An AdobeAssetFile object representing the image. */
@property (readonly, nonatomic, strong) AdobeAssetFile *image;

/** The image height. */
@property (readonly, nonatomic, assign) CGFloat imageHeight;

/** The image width. */
@property (readonly, nonatomic, assign) CGFloat imageWidth;

/** The primary component type of this AdobeAssetLibraryItemImage. */
@property (readonly, nonatomic, strong) NSString *primaryComponentType;

/** An AdobeAssetFile object representing the rendition. */
@property (readonly, nonatomic, strong) AdobeAssetFile *rendition;

/** The rendition height. */
@property (readonly, nonatomic, assign) CGFloat renditionHeight;

/** The rendition width. */
@property (readonly, nonatomic, assign) CGFloat renditionWidth;

@end

#endif
