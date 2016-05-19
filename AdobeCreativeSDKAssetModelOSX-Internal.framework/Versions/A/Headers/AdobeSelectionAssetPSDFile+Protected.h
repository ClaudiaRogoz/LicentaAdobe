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

#ifndef AdobeSelectionAssetPSDFileProtectedHeader
#define AdobeSelectionAssetPSDFileProtectedHeader

#import <AdobeCreativeSDKAssetModelOSX/AdobeSelectionAssetPSDFile.h>
#import <AdobeCreativeSDKAssetModelOSX/AdobePSDCompositeBranch.h>
#import <AdobeCreativeSDKAssetModelOSX/AdobePSDPreview.h>
#import <AdobeCreativeSDKAssetModelOSX/AdobeSelectionPSDLayer.h>

@interface AdobeSelectionAssetPSDFile (Protected)

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations" // suppress warning about deprecated class AdobePSDComposite

- (id)initWithAssetPSDFile:(AdobeAssetPSDFile *)file
composite:(AdobePSDComposite *)composite
layerComp:(AdobePSDPreviewLayerComp *)layerComp
layerSelections:(AdobePSDLayerSelectionArray *)layerSelections __deprecated;

#pragma clang diagnostic pop

@end

#endif
