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

#ifndef AdobeMarketCategoryHeader
#define AdobeMarketCategoryHeader

#import <AdobeCreativeSDKAssetModelOSX/AdobeCommunityCategory.h>

/**
 * Brushes category.
 */
extern NSString *const kMarketAssetsCategoryBrushes;

/**
 * The "For Placement" category.
 */
extern NSString *const kMarketAssetsCategoryForPlacement;

/**
 * Icons category.
 */
extern NSString *const kMarketAssetsCategoryIcons;

/**
 * Patterns category.
 */
extern NSString *const kMarketAssetsCategoryPatterns;

/**
 * User Interfaces category.
 */
extern NSString *const kMarketAssetsCategoryUserInterfaces;

/**
 * Vectors category.
 */
extern NSString *const kMarketAssetsCategoryVectors;

/**
 * AdobeMarketCategory represents a category in the Adobe Market. It provides methods that allow
 * the client to obtain information about the category and to enumerate the categories available in
 * the Creative Cloud Market.
 *
 * Currently the following constants can be used to for the corresponding category.
 *
 * - `kMarketAssetsCategoryBrushes`
 * - `kMarketAssetsCategoryForPlacement`
 * - `kMarketAssetsCategoryIcons`
 * - `kMarketAssetsCategoryPatterns`
 * - `kMarketAssetsCategoryUserInterfaces`
 * - `kMarketAssetsCategoryVectors`
 */
@interface AdobeMarketCategory : AdobeCommunityCategory

@end

#endif
