/******************************************************************************
 *
 * ADOBE CONFIDENTIAL
 * ___________________
 *
 * Copyright 2015 Adobe Systems Incorporated
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

#ifndef AdobeAssetLibraryItemStockImageHeader
#define AdobeAssetLibraryItemStockImageHeader

#import <Foundation/Foundation.h>

#import <AdobeCreativeSDKAssetModelOSX/AdobeAssetLibraryItemImage.h>


/*
* Deprecated
*/
__deprecated_msg("Use selectedLibraryID and selectedElementIDs in AdobeSelectionLibraryAsset and get corresponding library and elements using AdobeLibraryManager")
@interface AdobeAssetLibraryItemStockImage : AdobeAssetLibraryItemImage

@property (strong, nonatomic, readonly) NSURL *assetURL;
@property (assign, nonatomic, getter = isLicensed, readonly) BOOL licensed;

@end

#endif
