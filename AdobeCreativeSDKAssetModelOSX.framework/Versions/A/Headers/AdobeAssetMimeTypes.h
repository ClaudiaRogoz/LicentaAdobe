/******************************************************************************
 *
 * ADOBE CONFIDENTIAL
 * ___________________
 *
 * Copyright 2013 Adobe Systems Incorporated
 * All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains the property of
 * Adobe Systems Incorporated and its suppliers, if any. The intellectual and
 * technical concepts contained herein are proprietary to Adobe Systems
 * Incorporated and its suppliers and are protected by trade secret or
 * copyright law. Dissemination of this information or reproduction of this
 * material is strictly forbidden unless prior written permission is obtained
 * from Adobe Systems Incorporated.
 *
 * THIS FILE IS PART OF THE CREATIVE SDK PUBLIC API
 *
 ******************************************************************************/

#ifndef AdobeAssetMimeTypesHeader
#define AdobeAssetMimeTypesHeader

#import <Foundation/Foundation.h>

/** The mime type for octet streams */
extern NSString *const kAdobeMimeTypeOctetStream;

/** The mime type for compressed zip files */
extern NSString *const kAdobeMimeTypeZip;

/** The mime type for Photoshop documents */
extern NSString *const kAdobeMimeTypePhotoshop;

/** The mime type for jpeg files */
extern NSString *const kAdobeMimeTypeJPEG;

/** The mime type for InDesign idml files */
extern NSString *const kAdobeMimeTypeIDML;

/** The mime type for InDesign idms files */
extern NSString *const kAdobeMimeTypeIDMS;

/** The mime type for Illustrator documents */
extern NSString *const kAdobeMimeTypeIllustrator;

/** The mime type for InDesign documents */
extern NSString *const kAdobeMimeTypeInDesign;

/** The mime type for gif files */
extern NSString *const kAdobeMimeTypeGIF;

/** The mime type for png files */
extern NSString *const kAdobeMimeTypePNG;

/** The mime type for tiff files */
extern NSString *const kAdobeMimeTypeTIFF;

/** The mime type for bmp files */
extern NSString *const kAdobeMimeTypeBMP;

/** The mime type for pdf files */
extern NSString *const kAdobeMimeTypePDF;

/** The mime type for dmg files */
extern NSString *const kAdobeMimeTypeDMG;

/** The mime type for dng files */
extern NSString *const kAdobeMimeTypeDNG;

/** The mime type for raw files */
extern NSString *const kAdobeMimeTypeRaw;

/** The mime type for shape files */
extern NSString *const kAdobeMimeTypeShape;

/** The mime type for svg files */
extern NSString *const kAdobeMimeTypeSVG;

/** The mime type for postscript files */
extern NSString *const kAdobeMimeTypePostscript;

/** The mime type for Quicktime video files */
extern NSString *const kAdobeMimeTypeQuicktime;

/** The mime type for MP4 video files */
extern NSString *const kAdobeMimeTypeMP4;

/** The mime type for Adobe video metadata */
extern NSString *const kAdobeMimeTypeVideoMetadata;

/** The mime type for Adobe brush metadata */
extern NSString *const kAdobeMimeTypeAdobeBrush;

/**
 * Adobe Muse collection MIME type.
 */
extern NSString *const kAdobeMimeTypeAdobeMuseCollection;

@interface AdobeAssetMimeTypes : NSObject

/**
 * A utility method that returns the MIME type (e.g, "application/pdf") for
 * a given file extension (e.g., ".pdf"), if available. This method only
 * provides mappings to MIME type constants defined in this file.
 *
 * @param ext The extension.
 *
 * @return The MIME type, if a mapping is available for it; otherwise nil.
 */
+ (NSString *)mimeTypeForExtension:(NSString *)ext;

@end

#endif
