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

#ifndef AdobeAssetLibraryItemCharacterStyleHeader
#define AdobeAssetLibraryItemCharacterStyleHeader

#import <AdobeCreativeSDKAssetModelOSX/AdobeAssetLibraryItem.h>

#define IsAdobeAssetLibraryItemCharacterStyle(item) ( [item isKindOfClass: [AdobeAssetLibraryItemCharacterStyle class]])

/**
 * AdobeAssetLibraryItemCharacterStyle represents a character style item within a library.
 *
 * Deprecated
 */

__deprecated_msg("Use selectedLibraryID and selectedElementIDs in AdobeSelectionLibraryAsset and get corresponding library and elements using AdobeLibraryManager")
@interface AdobeAssetLibraryItemCharacterStyle : AdobeAssetLibraryItem

@property (strong, nonatomic, readonly) NSDictionary *styleData;
@property (strong, nonatomic, readonly) AdobeAssetFile *rendition;
@property (assign, nonatomic, readonly) CGFloat renditionHeight;
@property (assign, nonatomic, readonly) CGFloat renditionWidth;

@end

#endif
