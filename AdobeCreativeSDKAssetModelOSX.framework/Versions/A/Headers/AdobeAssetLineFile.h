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

#ifndef AdobeAssetLineFileHeader
#define AdobeAssetLineFileHeader

#import <AdobeCreativeSDKAssetModelOSX/AdobeAssetPackagePages.h>

/**
 * AdobeAssetLineFile represents an Adobe Line file and provides access to data about the package (manifest, renditions, etc).
 */

/**
 * A utility to help determine if an AdobeAssetPackage is an AdobeAssetLineFile.
 */
#define IsAdobeAssetLineFile(item) ([item isKindOfClass:[AdobeAssetLineFile class]])

/**
 *
 * AdobeAssetLineFile represents a package in the Creative Cloud and provides access to its contents.
 */
@interface AdobeAssetLineFile : AdobeAssetPackagePages

/**
 * A utility to test the equlity of two AdobeAssetLineFiles.
 *
 * @param file the AdobeAssetLineFile to test against.
 */
- (BOOL)isEqualToLineFile:(AdobeAssetLineFile *)file;

@end

#endif
