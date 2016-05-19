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

#ifndef AdobeAssetLibraryItemColorHeader
#define AdobeAssetLibraryItemColorHeader

#import <AdobeCreativeSDKAssetModelOSX/AdobeAssetLibraryItem.h>

@class UIColor;

/** Color Type */
typedef NS_ENUM (NSUInteger, AdobeAssetLibraryColorType)
{
    /** Process */
    AdobeAssetLibraryColorTypeProcess,
    /** Spot */
    AdobeAssetLibraryColorTypeSpot,
};

/** Color Mode */
typedef NS_ENUM (NSUInteger, AdobeAssetLibraryColorMode)
{
    /** Unknown */
    AdobeAssetLibraryColorModeUnknown,
    /** colorComponents is NSDictionary with keys: r, g, b (values: 0..255) */
    AdobeAssetLibraryColorModeRGB,
    /** colorComponents is NSDictionary with  keys: c, m, y, k (values: 0..100) */
    AdobeAssetLibraryColorModeCMYK,
    /** colorComponents is NSDictionary with  keys: l, a, b (l values: 0..100, a/b values: -128..127) */
    AdobeAssetLibraryColorModeLab,
    /** colorComponents is NSDictionary with  keys: h, s, b (h values: 0..360, s/b values: 0..100) */
    AdobeAssetLibraryColorModeHSB,
    /** colorComponents is NSDict (values: 0..100) */
    AdobeAssetLibraryColorModeGray,
};

#define IsAdobeAssetLibraryItemColor(item) ([item isKindOfClass:[AdobeAssetLibraryItemColor class]])

/**
 * AdobeAssetLibraryItemColor represents a color item within a library.
 *
 * Deprecated
 */

__deprecated_msg("Use selectedLibraryID and selectedElementIDs in AdobeSelectionLibraryAsset and get corresponding library and elements using AdobeLibraryManager")
@interface AdobeAssetLibraryItemColor : AdobeAssetLibraryItem

/** Alpha value of the color */
@property (readonly, nonatomic, assign) NSNumber *colorAlpha;
/** Components of the color */
@property (readonly, nonatomic, strong) NSObject *colorComponents;
/** Mode setting of this color object */
@property (readonly, nonatomic, assign) AdobeAssetLibraryColorMode colorMode;
/** Profile name of the color */
@property (readonly, nonatomic, strong) NSString *colorProfileName;
/** Whether this is a spot color or a process color */
@property (readonly, nonatomic, assign) AdobeAssetLibraryColorType colorType;
/** Alpha value for the rendition */
@property (readonly, nonatomic, assign) NSNumber *renditionAlpha;
/** Components for the rendition */
@property (readonly, nonatomic, strong) NSObject *renditionComponents;
/** Mode setting of this rendition */
@property (readonly, nonatomic, assign) AdobeAssetLibraryColorMode renditionMode;
/** Profile name for this rendition */
@property (readonly, nonatomic, strong) NSString *renditionProfileName;
/** Type for this rendition */
@property (readonly, nonatomic, assign) AdobeAssetLibraryColorType renditionType;

- (UIColor *)color;

@end

#endif
