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

#ifndef AdobeAssetLibraryHeader
#define AdobeAssetLibraryHeader

#import <AdobeCreativeSDKAssetModelOSX/AdobeAssetPackage.h>

/**
 * A utility to help determine if an AdobeAsset is an AdobeAssetLibrary.
 */
#define IsAdobeAssetLibrary(item) ([item isKindOfClass:[AdobeAssetLibrary class]])

/**
 * AdobeAssetLibrary represents a Creative Cloud Library and provides access to its contents.
 */
__deprecated_msg("Use AdobeLibraryComposite API")
@interface AdobeAssetLibrary : AdobeAssetPackage

/**
 * The ID of the library composite. This is an ID suitable for use with the AdobeLibraryManager
 * for full library support.
 */
@property (strong, nonatomic, readonly) NSString *libraryID;

/**
 * A dictionary of element id to element representing 3D Elements in the library.
 */
@property (strong, nonatomic, readonly) NSDictionary *threeDElements;

/**
 * The color items in the library. All dictionary objects are referenced by item ID.
 */
@property (strong, nonatomic, readonly) NSDictionary *colors;

/**
 * The color theme items in the library. All dictionary objects are referenced by item ID.
 */
@property (strong, nonatomic, readonly) NSDictionary *colorThemes;

/**
 * The image items in the library. All dictionary objects are referenced by item ID.
 */
@property (strong, nonatomic, readonly) NSDictionary *images;

/**
 * The brush items in the library. All dictionary objects are referenced by item ID.
 */
@property (strong, nonatomic, readonly) NSDictionary *brushes;

/**
 * The character style items in the library. The key is the item ID.
 */
@property (strong, nonatomic, readonly) NSDictionary *characterStyles;

/**
 * The layer style items in the library. The key is the item ID.
 */
@property (strong, nonatomic, readonly) NSDictionary *layerStyles;

/**
 * All Look assets in the library. The key is the Look Id and the value is the related Look object 
 * (AdobeAssetLibraryItemLook).
 */
@property (strong, nonatomic, readonly) NSDictionary *looks;

/**
 * All Pattern assets in the library. The key is the item Id and value is the related Pattern 
 * object (AdobeAssetLibraryItemPattern).
 */
@property (strong, nonatomic, readonly) NSDictionary *patterns;

/**
 * Videos in the library. The key is the item ID.
 */
@property (strong, nonatomic, readonly) NSDictionary *videos;

/**
 * A utility to test the equlity of two AdobeAssetLibrary instances.
 *
 * @param library the AdobeAssetLibrary to test against.
 */
- (BOOL)isEqualToLibrary:(AdobeAssetLibrary *)library;

@end

#endif
