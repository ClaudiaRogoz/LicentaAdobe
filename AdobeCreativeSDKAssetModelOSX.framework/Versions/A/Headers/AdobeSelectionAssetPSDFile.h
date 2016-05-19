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

#ifndef AdobeSelectionAssetPSDFileHeader
#define AdobeSelectionAssetPSDFileHeader

#import <AdobeCreativeSDKAssetModelOSX/AdobeSelectionAssetFile.h>

#import <AdobeCreativeSDKAssetModelOSX/AdobePSDComposite.h>
#import <AdobeCreativeSDKAssetModelOSX/AdobePSDPreview.h>
#import <AdobeCreativeSDKAssetModelOSX/AdobeSelectionPSDLayer.h>

/**
 * A utility to help determine if an item is an AdobeSelectionAssetPSDFile.
 *
 * TBD: EXPANDED
 *
 */
#define IsAdobeSelectionAssetPSDFile(item) ([item isKindOfClass:[AdobeSelectionAssetPSDFile class]])

/**
 * AdobeSelectionAssetPSDFile represents the selection of a PSD file and its selected components
 * in the AdobeUXAssetBrowser.
 */
@interface AdobeSelectionAssetPSDFile : AdobeSelectionAssetFile <NSCoding>

/**
 * The composite in the selection.
 */
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
@property (readonly, nonatomic, strong) AdobePSDComposite *composite __deprecated; // AdobePSDComposite will be replaced by CloudPSD and/or AGC
#pragma clang diagnostic pop

/**
 * The layer comp of the selection.
 */
@property (readonly, nonatomic, strong) AdobePSDPreviewLayerComp *layerComp;

/**
 * The array of selected layers in the selection.
 */
@property (readonly, nonatomic, strong) AdobePSDLayerSelectionArray *layerSelections;

@end

#endif /* ifndef AdobeSelectionAssetPSDFileHeader */
