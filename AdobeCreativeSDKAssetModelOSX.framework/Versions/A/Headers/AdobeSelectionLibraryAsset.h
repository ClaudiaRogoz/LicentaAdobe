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

#ifndef AdobeSelectionLibraryAssetHeader
#define AdobeSelectionLibraryAssetHeader

#import <Foundation/Foundation.h>

#import <AdobeCreativeSDKAssetModelOSX/AdobeSelection.h>

@class AdobeLibraryComposite;
@class AdobeLibraryElement;

/**
 * A utility to help determine if an item is an AdobeSelectionLibraryAsset.
 */
#define IsAdobeSelectionLibraryAsset(item) ([item isKindOfClass:[AdobeSelectionLibraryAsset class]])

/**
 * Holds information about the items that are selected by a user from a library.
 */
@interface AdobeSelectionLibraryAsset : AdobeSelection


/**
 * Retrieves the selected AdobeLibraryComposite ID from the Library that is being explored
 */
@property (strong, nonatomic, readonly) NSString *selectedLibraryID;


/**
 * Retrieves the selected AdobeLibraryElement IDs from the Library that is being explored
 */
@property (strong, nonatomic, readonly) NSArray<NSString *> *selectedElementIDs;


// deprecated ------------------------------------------------------------------

/**
 * Contains the IDs of AdobeAssetLibraryItem3DElement instances selected from a library.
 */
@property (strong, nonatomic, readonly) NSArray<NSString *> *selected3DElementIDs __deprecated_msg("use selectedElements");


/**
 * Contains the IDs of AdobeAssetLibraryItemBrush instances selected from a library.
 */
@property (strong, nonatomic, readonly) NSArray<NSString *> *selectedBrushIDs __deprecated_msg("use selectedElements");


/**
 * Contains the IDs of AdobeAssetLibraryItemCharacterStyle instances selected from a library.
 */
@property (strong, nonatomic, readonly) NSArray<NSString *> *selectedCharacterStyleIDs __deprecated_msg("use selectedElements");


/**
 * Contains the IDs of AdobeAssetLibraryItemColor instances selected from a library.
 */
@property (strong, nonatomic, readonly) NSArray<NSString *> *selectedColorIDs __deprecated_msg("use selectedElements");


/**
 * Contains the IDs of AdobeAssetLibraryItemColorTheme instances selected from a library.
 */
@property (strong, nonatomic, readonly) NSArray<NSString *> *selectedColorThemeIDs __deprecated_msg("use selectedElements");


/**
 * Contains the IDs of AdobeAssetLibraryItemImage instances selected from a library.
 */
@property (strong, nonatomic, readonly) NSArray<NSString *> *selectedImageIDs __deprecated_msg("use selectedElements");


/**
 * Contains the IDs of AdobeAssetLibraryItemLayerStyle instances selected from a library.
 */
@property (strong, nonatomic, readonly) NSArray<NSString *> *selectedLayerStyleIDs __deprecated_msg("use selectedElements");


/**
 * Contains the IDs of AdobeAssetLibraryItemLook instances selected from a library.
 */
@property (strong, nonatomic, readonly) NSArray<NSString *> *selectedLookIDs __deprecated_msg("use selectedElements");


/**
 * Contains the IDs of AdobeAssetLibraryItemPattern instances selected from a library.
 */
@property (strong, nonatomic, readonly) NSArray<NSString *> *selectedPatternIDs __deprecated_msg("use selectedElements");


/**
 * Contains the IDs of AdobeAssetLibraryItemVideo instances selected from a library.
 */
@property (strong, nonatomic, readonly) NSArray<NSString *> *selectedVideoIDs __deprecated_msg("use selectedElements");


@end

#endif
