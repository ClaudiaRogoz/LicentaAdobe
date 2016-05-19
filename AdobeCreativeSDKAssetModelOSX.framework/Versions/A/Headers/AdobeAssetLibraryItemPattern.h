/******************************************************************************
*
* ADOBE CONFIDENTIAL
* ___________________
*
* Copyright 2016 Adobe Systems Incorporated
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

#ifndef AdobeAssetLibraryItemPatternHeader
#define AdobeAssetLibraryItemPatternHeader

#import <AdobeCreativeSDKAssetModelOSX/AdobeAssetLibraryItem.h>

@class AdobeAssetFile;

#define IsAdobeAssetLibraryItemPattern(item) ( [item isKindOfClass:[AdobeAssetLibraryItemPattern class]])

/**
 * Represents a Pattern asset within a Creative Cloud Library.
 *
 * Deprecated
 */

__deprecated_msg("Use selectedLibraryID and selectedElementIDs in AdobeSelectionLibraryAsset and get corresponding library and elements using AdobeLibraryManager")
@interface AdobeAssetLibraryItemPattern : AdobeAssetLibraryItem

@property (strong, nonatomic, readonly) AdobeAssetFile *pattern;
@property (strong, nonatomic, readonly) AdobeAssetFile *rendition;
@property (assign, nonatomic, readonly) NSUInteger renditionHeight;
@property (assign, nonatomic, readonly) NSUInteger renditionWidth;

@end

#endif
