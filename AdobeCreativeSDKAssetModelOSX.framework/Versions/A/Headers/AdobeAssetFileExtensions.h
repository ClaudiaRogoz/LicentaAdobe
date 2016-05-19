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
 *
 * THIS FILE IS PART OF THE CREATIVE SDK PUBLIC API
 *
 ******************************************************************************/

#ifndef AdobeAssetFileExtensionsHeader
#define AdobeAssetFileExtensionsHeader

#import <Foundation/Foundation.h>

/** The file extension for compressed zip files */
extern NSString *const kAdobeFileExtensionTypeZip;

/** The file extension for PSD Photoshop documents */
extern NSString *const kAdobeFileExtensionTypePSD;

/** The file extension for PSB Photoshop documents */
extern NSString *const kAdobeFileExtensionTypePSB;

/** The file extension for Quicktime video files */
extern NSString *const kAdobeFileExtensionTypeMOV;

/** The file extension for MP4 video files */
extern NSString *const kAdobeFileExtensionTypeMP4;

/** The file extension for jpeg files */
extern NSString *const kAdobeFileExtensionTypeJPEG;

/** The file extension for AI Illustrator documents */
extern NSString *const kAdobeFileExtensionTypeAI;

/** The file extension for AIT Illustrator documents */
extern NSString *const kAdobeFileExtensionTypeAIT;

/** The file extension for Postscript files */
extern NSString *const kAdobeFileExtensionTypeEPS;

/** The file extension for INDD InDesign documents */
extern NSString *const kAdobeFileExtensionTypeINDD;

/** The file extension for IDML InDesign documents */
extern NSString *const kAdobeFileExtensionTypeIDML;

/** The file extension for IDMS InDesign documents */
extern NSString *const kAdobeFileExtensionTypeIDMS;

/** The file extension for INDT InDesign documents */
extern NSString *const kAdobeFileExtensionTypeINDT;

/** The file extension for gif files */
extern NSString *const kAdobeFileExtensionTypeGIF;

/** The file extension for png files */
extern NSString *const kAdobeFileExtensionTypePNG;

/** The file extension for tiff files */
extern NSString *const kAdobeFileExtensionTypeTIFF;

/** The file extension for bmp files */
extern NSString *const kAdobeFileExtensionTypeBMP;

/** The file extension for pdf files */
extern NSString *const kAdobeFileExtensionTypePDF;

/** The file extension for dmg files */
extern NSString *const kAdobeFileExtensionTypeDMG;

/** The file extension for dng files */
extern NSString *const kAdobeFileExtensionTypeDNG;

/** The file extension for shape files */
extern NSString *const kAdobeFileExtensionTypeSHAPE;

/** The file extension for svg files */
extern NSString *const kAdobeFileExtensionTypeSVG;

/** The file extension for brush files */
extern NSString *const kAdobeFileExtensionTypeAdobeBrush;

@interface AdobeAssetFileExtensions : NSObject

/**
 * A utility method that returns the file extension (e.g, ".pdf") for a
 * given MIME type (e.g., "application/pdf"), if available. This method
 * only provides mappings to extension constants defined in this file.
 *
 * @param type The MIME type.
 *
 * @return The extension, if a mapping is available for it; otherwise nil.
 */
+ (NSString *)extensionForMIMEType:(NSString *)type;

@end

#endif
