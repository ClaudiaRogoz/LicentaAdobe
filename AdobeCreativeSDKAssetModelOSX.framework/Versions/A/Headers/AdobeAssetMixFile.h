/******************************************************************************
 *
 * ADOBE CONFIDENTIAL
 * ___________________
 *
 * Copyright 2015 Adobe Systems Incorporated
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

#ifndef AdobeAssetMixFileHeader
#define AdobeAssetMixFileHeader

/**
 * A utility to help determine if an AdobeAssetPackage is an AdobeAssetMixFile.
 */
#define IsAdobeAssetMixFile(item) ([item isKindOfClass:[AdobeAssetMixFile class]])

#import <AdobeCreativeSDKAssetModelOSX/AdobeAssetPackagePages.h>

/**
 * AdobeAssetMixFile represents a Photoshop Mix package and provides access to data about that
 * package (manifest, renditions, etc).
 */
@interface AdobeAssetMixFile : AdobeAssetPackagePages

/**
 * A utility to test the equality of two AdobeAssetMixFiles.
 *
 * @param file the AdobeAssetMixFile to test against.
 */
- (BOOL)isEqualToMixFile:(AdobeAssetMixFile *)file;

@end

#endif
