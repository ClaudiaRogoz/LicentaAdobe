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

#ifndef AdobeAssetSketchbookHeader
#define AdobeAssetSketchbookHeader

#import <AdobeCreativeSDKAssetModelOSX/AdobeAssetPackagePages.h>

/**
 * AdobeAssetSketchbook represents an Adobe Sketchbook and provides access to data about the package (manifest, renditions, etc).
 */

typedef NSArray AdobeAssetSketchbookPages;

/**
 * A utility to help determine if an AdobeAssetPackage is an AdobeAssetSketchPackage.
 */
#define IsAdobeAssetSketchbook(item) ([item isKindOfClass:[AdobeAssetSketchbook class]])

/**
 * AdobeAssetSketchbook represents a package in the Creative Cloud and provides access to its contents.
 */
@interface AdobeAssetSketchbook : AdobeAssetPackagePages

/**
 * A utility to test the equlity of two AdobeAssetSketchbooks.
 *
 * @param sketchbook the AdobeAssetSketchbook to test against.
 */
- (BOOL)isEqualToSketchbook:(AdobeAssetSketchbook *)sketchbook;

@end

#endif
