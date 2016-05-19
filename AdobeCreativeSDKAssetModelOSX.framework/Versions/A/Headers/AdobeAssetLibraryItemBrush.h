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

#ifndef AdobeAssetLibraryItemBrushHeader
#define AdobeAssetLibraryItemBrushHeader

#import <AdobeCreativeSDKAssetModelOSX/AdobeAssetFile.h>
#import <AdobeCreativeSDKAssetModelOSX/AdobeAssetLibraryItem.h>

#define IsAdobeAssetLibraryItemBrush(item) ( [item isKindOfClass: [AdobeAssetLibraryItemBrush class]])

/**
 * AdobeAssetLibraryItemBrush represents a brush item within a library.
 *
 * Deprecated
 */

__deprecated_msg("Use selectedLibraryID and selectedElementIDs in AdobeSelectionLibraryAsset and get corresponding library and elements using AdobeLibraryManager")
@interface AdobeAssetLibraryItemBrush : AdobeAssetLibraryItem

@property (readonly, nonatomic, strong) AdobeAssetFile *brush;
@property (readonly, nonatomic, strong) AdobeAssetFile *rendition;
@property (readonly, nonatomic, assign) CGFloat renditionHeight;
@property (readonly, nonatomic, assign) CGFloat renditionWidth;

@end

#endif
