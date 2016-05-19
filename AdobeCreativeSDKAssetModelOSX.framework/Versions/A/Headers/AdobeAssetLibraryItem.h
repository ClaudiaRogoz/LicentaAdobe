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

#ifndef AdobeAssetLibraryItemHeader
#define AdobeAssetLibraryItemHeader

#import <Foundation/Foundation.h>

@class AdobeAssetLibrary;

#define IsAdobeAssetLibraryItem(item) ([item isKindOfClass:[AdobeAssetLibraryItem class]])

/**
 * AdobeAssetLibraryItem is the base class for all items within a Creative Cloud library
 * when selected via the asset browser.
 *
 * Deprecated.
 */
__deprecated_msg("Use selectedLibraryID and selectedElementIDs in AdobeSelectionLibraryAsset and get corresponding library and elements using AdobeLibraryManager")
@interface AdobeAssetLibraryItem : NSObject

/** Created date */
@property (readonly, nonatomic, strong) NSDate *creationDate;

/** Name */
@property (readonly, nonatomic, strong) NSString *name;

/** Item ID */
@property (readonly, nonatomic, strong) NSString *itemID;

/** External Links */
@property (readonly, nonatomic, assign) BOOL hasExternalLinks;

/** Parent library */
@property (readonly, nonatomic, weak) AdobeAssetLibrary *library;

/** Modification date */
@property (readonly, nonatomic, strong) NSDate *modificationDate;

/**
 * Utility method to test equality.
 *
 * @param item Item to be compared.
 */
- (BOOL)isEqualToAssetLibraryItem:(AdobeAssetLibraryItem *)item;

@end

#endif
