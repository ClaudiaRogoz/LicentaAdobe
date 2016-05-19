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

#ifndef AdobeAssetLibraryItem3DElementHeader
#define AdobeAssetLibraryItem3DElementHeader

#import <CoreGraphics/CoreGraphics.h>
#import <Foundation/Foundation.h>

#import <AdobeCreativeSDKAssetModelOSX/AdobeAssetLibraryItem.h>

@class AdobeAssetFile;

#define IsAdobeAssetLibraryItem3DElement(item) ( [item isKindOfClass:[AdobeAssetLibraryItem3DElement class]])

/**
 * AdobeAssetLibraryItem3DElement represents a 3D Element within a library.
 *
 * Deprected
 */

__deprecated_msg("Use selectedLibraryID and selectedElementIDs in AdobeSelectionLibraryAsset and get corresponding library and elements using AdobeLibraryManager")
@interface AdobeAssetLibraryItem3DElement : AdobeAssetLibraryItem

@property (strong, nonatomic, readonly) AdobeAssetFile *threeDElement;
@property (strong, nonatomic, readonly) AdobeAssetFile *rendition;
@property (assign, nonatomic, readonly) CGFloat renditionHeight;
@property (assign, nonatomic, readonly) CGFloat renditionWidth;
@property (strong, nonatomic, readonly) NSString *primaryComponentType;

@end

#endif
