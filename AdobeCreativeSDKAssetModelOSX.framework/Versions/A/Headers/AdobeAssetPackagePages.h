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

#ifndef AdobeAssetPackagePagesHeader
#define AdobeAssetPackagePagesHeader

#import <AdobeCreativeSDKAssetModelOSX/AdobeAssetPackage.h>

/**
 * AdobeAssetPackagePages represents a package that holds "pages" and provides
 * access to data about the package (manifest, renditions, etc). Examples of
 * such packages include Sketch, Line, and Draw DCX documents.
 */

/**
 * A utility to help determine if an AdobeAsset is an AdobeAssetPackagePages.
 */
#define IsAdobeAssetPackagePages(item) ([item isKindOfClass:[AdobeAssetPackagePages class]])

/**
 * AdobeAssetPackagePages represents a paged package in the Creative Cloud and provides access to its contents.
 */
@interface AdobeAssetPackagePages : AdobeAssetPackage

/**
 * The items in the package.
 */
@property (nonatomic, readonly, strong) NSArray *pages;

/**
 * A utility to test the equlity of two AdobeAssetPackagePages instances.
 *
 * @param package the AdobeAssetPackagePages to test against.
 */
- (BOOL)isEqualToPackagePages:(AdobeAssetPackagePages *)package;

@end

#endif
