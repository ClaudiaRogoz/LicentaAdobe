/*************************************************************************
*
* ADOBE CONFIDENTIAL
* ___________________
*
*  Copyright 2013 Adobe Systems Incorporated
*  All Rights Reserved.
*
* NOTICE:  All information contained herein is, and remains
* the property of Adobe Systems Incorporated and its suppliers,
* if any.  The intellectual and technical concepts contained
* herein are proprietary to Adobe Systems Incorporated and its
* suppliers and are protected by trade secret or copyright law.
* Dissemination of this information or reproduction of this material
* is strictly forbidden unless prior written permission is obtained
* from Adobe Systems Incorporated.
**************************************************************************/

// Reviewed by rhorns on October 10, 2013

#ifndef AdobeDCXManifestFormatConverterHeader
#define AdobeDCXManifestFormatConverterHeader

#import <Foundation/Foundation.h>

extern const NSUInteger AdobeDCXManifestFormatVersion;

/**
* brief Converter for the various verrsions of manifests.
*/
@interface AdobeDCXManifestFormatConverter : NSObject

/**
* brief Updates the manifest dictionary dict from the specified version to the current version of the manifest format.
*
* param dict The dictionary containing the manifest.
* param fversion The current format version of the manifest.
* param errorPtr Gets set to an NSError if the manifest cannot be converted.
*
* return YES is successful.
*/
+ (BOOL)updateManifestDictionary:(NSMutableDictionary *)dict fromVersion:(NSUInteger)fversion withError:(NSError **)errorPtr;
@end

#endif
