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

#ifndef AdobeDCXMutableMetadataHeader
#define AdobeDCXMutableMetadataHeader

#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeDCXMetadata.h>
#import <Foundation/Foundation.h>

@class AdobeDCXMetadataPath;

/**
* brief XMP Metadata in a DCX composite or being prepared for a rendition.
*/

@interface AdobeDCXMutableMetadata : AdobeDCXMetadata

#/**@}*/
#pragma mark History
/** name History */
/**@{*/

- (void)appendHistoryEvent:(NSString *)action withParam:(NSString *)param;

- (void) fixDerivedCompositeWithDocId:(NSString*)compositeId;

/**@}*/
#pragma mark XMP property accessors
/** name XMP property accessors */
/**@{*/

- (void)setPropertyWithSchema:(NSString *)schema andName:(NSString *)name andValue:(NSString *)value;

- (void)setLocalizedPropertyWithSchema:(NSString *)schema andName:(NSString *)name andValue:(NSString *)value;

- (void)setPropertyWithPath:(AdobeDCXMetadataPath *)path andValue:(NSString *)value;
- (void)setPropertyWithPath:(AdobeDCXMetadataPath *)path andValue:(NSString *)value andOptions:(NSUInteger)options;

- (void)setLocalizedPropertyWithPath:(AdobeDCXMetadataPath *)path andValue:(NSString *)value;
- (void)setLocalizedPropertyWithPath:(AdobeDCXMetadataPath *)path andValue:(NSString *)value andOptions:(NSUInteger)options;

- (void)appendToOrderedArrayWithPath:(AdobeDCXMetadataPath *)path andValue:(NSString *)value;
- (void)appendToUnorderedArrayWithPath:(AdobeDCXMetadataPath *)path andValue:(NSString *)value;
- (void)appendStructItemToOrderedArrayWithPath:(AdobeDCXMetadataPath *)path;
- (void)appendStructItemToUnorderedArrayWithPath:(AdobeDCXMetadataPath *)path;

- (void)deletePropertyWithSchema:(NSString *)schema andName:(NSString *)name;
- (void)deletePropertyWithPath:(AdobeDCXMetadataPath *)path;

/**@}*/
#pragma mark Copying
/** name Copying */
/**@{*/

- (void)copySubTree:(AdobeDCXMetadata *)sourceXmp fromPath:(AdobeDCXMetadataPath *)sourcePath toPath:(AdobeDCXMetadataPath *)destPath;

- (void)assignNewDocumentId;

/**@}*/
#pragma mark Merging
/** name Merging */
/**@{*/

- (BOOL)mergeMetadataFrom:(AdobeDCXMetadata *)from withBase:(AdobeDCXMetadata *)base;

/**@}*/
#pragma mark Ingredients
/** name Ingredients */
/**@{*/

- (BOOL)addIngredient:(AdobeDCXMetadata *)from fromPart:(NSString *)fromPart fromDescription:(NSString *)fromDescription
toPart:(NSString *)toPart toDescription:(NSString *)toDescription;
- (BOOL)addIngredient:(AdobeDCXMetadata *)from fromPart:(NSString *)fromPart toPart:(NSString *)toPart;
- (BOOL)addIngredientAndPantry:(AdobeDCXMetadata *)from fromPart:(NSString *)fromPart fromDescription:(NSString *)fromDescription
toPart:(NSString *)toPart toDescription:(NSString *)toDescription;
- (BOOL)addIngredientAndPantry:(AdobeDCXMetadata *)from fromPart:(NSString *)fromPart toPart:(NSString *)toPart;

/**@}*/
#pragma mark Origin information
/** name Origin information */
/**@{*/

- (void)addOriginUrl:(NSString *)originUrl withManageUI:(NSString *)manageUiUrl;

/**@}*/
#pragma mark Licensing
/** name Licensing */
/**@{*/

- (void)addLicenseInfo:(NSString *)licenseAbbrev attributionURL:(NSString *)attributionURL
attributionName:(NSString *)attributionName;

- (void)removeLicenseInfo;

- (BOOL)ensureMinimalXMPForFile:(NSString *)filePath andType:(NSString *)type andAgent:(NSString *)agent;

/**@}*/
#pragma mark Tags (subject keywords)
/** name Tags (subject keywords) */
/**@{*/

- (void)addTag:(NSString *)tag;
- (void)addTags:(NSArray *)tags;

/**@}*/
#pragma mark Updating file Metadata
/** name Update File Metadata */
/**@{*/

- (BOOL)updateFile:(NSString *)filePath withError:(NSError **)errorPtr;

/**@}*/
#pragma mark Thumbnails
/** name Thumbnails */
/**@{*/

/**
* Delete all thumbnail metadata
*/
- (void)deleteThumbnails;

/**
* Add a JPEG thumbnail
*/
- (void)addJPEGThumbnail:(NSData *)data width:(NSInteger)width height:(NSInteger)height;

/**@}*/
@end

#endif
