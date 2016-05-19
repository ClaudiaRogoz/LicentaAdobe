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

#ifndef AdobeSelectionPhotoAssetHeader
#define AdobeSelectionPhotoAssetHeader

#import <AdobeCreativeSDKAssetModelOSX/AdobeSelection.h>

/**
 * A utility to help determine if an item is an AdobeSelectionPhotoAsset.
 */
#define IsAdobeSelectionPhotoAsset(item) ([item isKindOfClass:[AdobeSelectionPhotoAsset class]])

/**
 * AdobeSelectionPhotoAsset represents the selection of a file in the AdobeUXAssetBrowser.
 */
@interface AdobeSelectionPhotoAsset : AdobeSelection

@end

#endif
