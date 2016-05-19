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

#ifndef AdobeSelectionLineAssetHeader
#define AdobeSelectionLineAssetHeader

#import <AdobeCreativeSDKAssetModelOSX/AdobeSelection.h>

extern NSString *const AdobeSelectionLineAssetPageIndexKey;

/**
 * A utility to help determine if an item is an AdobeSelectionLineAsset.
 */
#define IsAdobeSelectionLineAsset(item) ([item isKindOfClass:[AdobeSelectionLineAsset class]])

/**
 * Represents an Adobe Line selected asset.
 */
@interface AdobeSelectionLineAsset : AdobeSelection

/** Represents the selected page within the asset. */
@property (assign, nonatomic, readonly) NSInteger selectedPageIndex;

@end

#endif
