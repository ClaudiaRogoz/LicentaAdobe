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

#ifndef AdobeAssetDrawFileHeader
#define AdobeAssetDrawFileHeader

/**
 * A utility to help determine if an AdobeAssetPackage is an AdobeAssetDrawFile.
 */
#define IsAdobeAssetDrawFile(item) ([item isKindOfClass:[AdobeAssetDrawFile class]])

#import <AdobeCreativeSDKAssetModelOSX/AdobeAssetPackagePages.h>

/**
 * AdobeAssetDrawFile represents an Adobe Draw package and provides access to data about that
 * package (manifest, renditions, etc).
 */
@interface AdobeAssetDrawFile : AdobeAssetPackagePages

/**
 * A utility to test the equality of two AdobeAssetDrawFiles.
 *
 * @param file the AdobeAssetDrawFile to test against.
 */
- (BOOL)isEqualToDrawFile:(AdobeAssetDrawFile *)file;

@end

#endif
