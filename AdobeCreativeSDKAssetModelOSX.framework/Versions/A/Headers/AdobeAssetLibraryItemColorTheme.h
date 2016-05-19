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

#ifndef AdobeAssetLibraryItemColorThemeHeader
#define AdobeAssetLibraryItemColorThemeHeader

#import <AdobeCreativeSDKAssetModelOSX/AdobeAssetLibraryItem.h>
#import <AdobeCreativeSDKAssetModelOSX/AdobeColorTheme.h>

#define IsAdobeAssetLibraryItemColorTheme(item) ([item isKindOfClass:[AdobeAssetLibraryItemColorTheme class]])

/**
 * AdobeAssetLibraryItemColorTheme represents a color theme item within a library.
 *
 * Deprecated
 */

__deprecated_msg("Use selectedLibraryID and selectedElementIDs in AdobeSelectionLibraryAsset and get corresponding library and elements using AdobeLibraryManager")
@interface AdobeAssetLibraryItemColorTheme : AdobeAssetLibraryItem

/** The color theme associated with this AdobeAssetLibraryItemColorTheme element. */
@property (readonly, nonatomic, strong) AdobeColorTheme *colorTheme;

@end

#endif
