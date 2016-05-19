/******************************************************************************
 *
 * ADOBE CONFIDENTIAL
 * ___________________
 *
 * Copyright 2016 Adobe Systems Incorporated
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

#ifndef AdobeAssetLibraryItemVideoHeader
#define AdobeAssetLibraryItemVideoHeader

#import <AdobeCreativeSDKAssetModelOSX/AdobeAssetLibraryItem.h>

@class AdobeAssetFile;

#define IsAdobeAssetLibraryItemVideo(item) ([item isKindOfClass:[AdobeAssetLibraryItemVideo class]])

/**
 * AdobeAssetLibraryItemVideo represents a video item within a library.
 *
 * Deprecated
 */

__deprecated_msg("Use selectedLibraryID and selectedElementIDs in AdobeSelectionLibraryAsset and get corresponding library and elements using AdobeLibraryManager")
@interface AdobeAssetLibraryItemVideo : AdobeAssetLibraryItem

/**
 * An AdobeAssetFile object representing the video.
 */
@property (strong, nonatomic, readonly) AdobeAssetFile *video;

/**
 * The video height.
 */
@property (assign, nonatomic, readonly) CGFloat videoHeight;

/**
 * The video width.
 */
@property (assign, nonatomic, readonly) CGFloat videoWidth;

/**
 * An AdobeAssetFile object representing the rendition of the receiver.
 */
@property (strong, nonatomic, readonly) AdobeAssetFile *rendition;

/**
 * The rendition height.
 */
@property (assign, nonatomic, readonly) CGFloat renditionHeight;

/**
 * The rendition width.
 */
@property (assign, nonatomic, readonly) CGFloat renditionWidth;

@end

#endif
