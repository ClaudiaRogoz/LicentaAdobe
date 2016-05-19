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

#ifndef AdobeSelectionLibraryAssetProtectedHeader
#define AdobeSelectionLibraryAssetProtectedHeader

#import <AdobeCreativeSDKAssetModelOSX/AdobeSelectionLibraryAsset.h>

@class AdobeLibraryComposite;
@class AdobeLibraryElement;
@class AdobeAssetLibrary;

@interface AdobeSelectionLibraryAsset (Protected)

- (instancetype)initWithLibrary:(AdobeAssetLibrary *)library
selected3DElementIDs:(NSArray<NSString *> *)selected3DElementIDs
selectedBrushIDs:(NSArray<NSString *> *)selectedBrushIDs
selectedCharacterStyleIDs:(NSArray<NSString *> *)selectedCharacterStyleIDs
selectedColorIDs:(NSArray<NSString *> *)selectedColorIDs
selectedColorThemeIDs:(NSArray<NSString *> *)selectedColorThemeIDs
selectedImageIDs:(NSArray<NSString *> *)selectedImageIDs
selectedLayerStyleIDs:(NSArray<NSString *> *)selectedLayerStyleIDs
selectedLookIDs:(NSArray<NSString *> *)selectedLookIDs
selectedPatternIDs:(NSArray<NSString *> *)selectedPatternIDs
selectedVideoIDs:(NSArray<NSString *> *)selectedVideoIDs __deprecated_msg("use initWithLibrary:elements:deprecatedLibrary");

- (instancetype)initWithLibrary:(AdobeLibraryComposite *)composite
elements:(NSArray<AdobeLibraryElement *> *)elements
deprecatedLibrary:(id)library;

@end

#endif
