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

#ifndef AdobeSelectionAssetHeader
#define AdobeSelectionAssetHeader

#import <AdobeCreativeSDKAssetModelOSX/AdobeAsset.h>
#import <AdobeCreativeSDKAssetModelOSX/AdobeSelection.h>

/**
 * A utility to help determine if an item is an AdobeSelectionAsset.
 */
#define IsAdobeSelectionAsset(item) ([item isKindOfClass:[AdobeSelectionAsset class]])

/**
 * AdobeSelectionAsset is the base class of an object that represents an AdobeAsset selection.
 * Selections are used with the AdobeUXAssetBrowser to identify which assets should be or are
 * selected in the asset browser.
 */
@interface AdobeSelectionAsset : AdobeSelection

/**
 * The selected asset.
 */
@property (readonly, nonatomic, strong) AdobeAsset *selectedItem;

@end

typedef NSArray AdobeSelectionAssetArray;

#endif
