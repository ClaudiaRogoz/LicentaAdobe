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

#ifndef AdobeDCXFileMetadataHeader
#define AdobeDCXFileMetadataHeader

#import <Foundation/Foundation.h>

@class AdobeDCXMetadata;
@class AdobeDCXMutableMetadata;

/**
* brief XMP Metadata in a DCX composite or being prepared for a rendition.
*/

@interface AdobeDCXFileMetadata : NSObject

/**@}*/
#pragma mark Class Methdods
/** name Class Methdods */
/**@{*/

/** Gets metadata from the file at the given path.
* returns nil if there is none. */
+ (AdobeDCXMetadata *)getMetadataForFile:(NSString *)path withError:(NSError **)errorPtr;

/** Gets metadata from the file at the given path, creating if necessary, and ensures it contains minimal properties */
+ (AdobeDCXMutableMetadata *)getOrCreateMetadataForFile:(NSString *)path withError:(NSError **)errorPtr;

/** Can metadata be updated in the file? */
+ (BOOL)isMetadataUpdatableForFile:(NSString *)path;

/** Adds metaddata to the file at the given path */
+ (BOOL)addMetadata:(AdobeDCXMetadata *)metadata toFile:(NSString *)path withError:(NSError **)errorPtr;

/** Adds metaddata to the file at the given path if the metadata has changed (isDirty) */
+ (BOOL)updateMetadata:(AdobeDCXMetadata *)metadata inFile:(NSString *)path withError:(NSError **)errorPtr;

/** Adds metaddata to the data object, returning new one */
+ (NSData *)addMetadata:(AdobeDCXMetadata *)metadata toDataObject:(NSData *)data;

/**@}*/

@end

#endif
