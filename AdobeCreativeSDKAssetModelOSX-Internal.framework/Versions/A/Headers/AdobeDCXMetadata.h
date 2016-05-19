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

#ifndef AdobeDCXMetadataHeader
#define AdobeDCXMetadataHeader

#import <Foundation/Foundation.h>

@class AdobeDCXMetadataPath;
@class AdobeDCXCompositeBranch;
@class AdobeDCXCompositeMutableBranch;
@class AdobeDCXComponent;
@class AdobeDCXManifestNode;
@class AdobeDCXNode;
@class AdobeRemixData;

/**
* brief XMP Metadata in a DCX composite or being prepared for a rendition.
*/

@interface AdobeDCXMetadata : NSObject <NSMutableCopying, NSCopying>

#pragma mark Initializers
/** name Initializers */
/**@{*/

/**
* brief Designated initializer. Used by the other initializers.
*/

- (id)init;

/**@}*/
#pragma mark Properties
/** name Properties */
/**@{*/

- (BOOL)isDirty;  // immutable metadata can be dirty because it's never been saved

/**@}*/
+ (void)setCreatorTool:(NSString *)toolName;
+ (NSString *)creatorTool;

+ (void)registerNamespace:(NSString *)ns as:(NSString *)shortName;

+ (AdobeDCXComponent *)getMetadataComponentInBranch:(AdobeDCXCompositeBranch *)compositeBranch __deprecated;
+ (AdobeDCXComponent *)getMetadataComponentInBranchOrElement:(id)branchOrElement;

+ (NSString *)getMetadataComponentAbsolutePath;

/** Creates and returns an instance of AdobeRemixData with the relevant fields filled in from the metadata instance. */
-(AdobeRemixData*)createRemixData;

/**@}*/
#pragma mark Serialization
/** name Serialization */
/**@{*/

- (NSString *)serializeAsString;
- (NSData *)serializeAsUTF8Data;

/*
* Save or update the metadata in the specified composite branch.
* This method is applicable to element metadata returned from [branch getOrCreateMetadataForElement].
*/

- (BOOL)saveInCompositeBranch:(AdobeDCXCompositeMutableBranch *)compositeBranch withError:(NSError **)errorPtr;

- (BOOL)saveInCompositeBranchOrElement:(id)branchOrElement withError:(NSError **)errorPtr;

/**
* branch updates a metadata component in the specified branch.
*/
- (AdobeDCXComponent *)updateComponent:(AdobeDCXComponent *)component inBranch:(AdobeDCXCompositeMutableBranch *)branch withError:(NSError **)errorPtr __deprecated;

- (AdobeDCXComponent*) updateComponent:(AdobeDCXComponent*)component inBranchOrElement:(id)branchOrElement withError:(NSError **)errorPtr;

/**
* brief Creates a metadata component in the specified branch.
*/
- (AdobeDCXComponent *)saveAsComponentOf:(AdobeDCXManifestNode *)node inBranch:(AdobeDCXCompositeMutableBranch *)branch withPath:(NSString *)path withError:(NSError **)errorPtr __deprecated;

- (AdobeDCXComponent*)saveAsComponentOfNode:(AdobeDCXNode*)node inBranchOrElement:(id)branchOrElement withPath:(NSString*)path withError:(NSError **)errorPtr;

/**@}*/
#pragma mark Debugging support
/** name Debugging support */
/**@{*/

- (void)dump;
- (void)dumpAsXMP;

/**@}*/
#pragma mark XMP property accessors
/** name XMP property accessors */
/**@{*/

- (NSString *)getPropertyWithSchema:(NSString *)schema andName:(NSString *)name;

- (NSString *)getLocalizedPropertyWithSchema:(NSString *)schema andName:(NSString *)name;

- (NSString *)getPropertyWithPath:(AdobeDCXMetadataPath *)path;
- (NSString *)getPropertyWithPath:(AdobeDCXMetadataPath *)path returningOptions:(NSUInteger *)optionsp;
- (NSString *)getPropertyWithPath:(AdobeDCXMetadataPath *)path qualifierSchema:(NSString *)qualifierSchema qualifierName:(NSString *)qualifierName returningOptions:(NSUInteger *)optionsp;

- (NSString *)getLocalizedPropertyWithPath:(AdobeDCXMetadataPath *)path;
- (NSString *)getLocalizedPropertyWithPath:(AdobeDCXMetadataPath *)path returningOptions:(NSUInteger *)optionsp;
- (BOOL)hasTag:(NSString *)tag;

/**@}*/
#pragma mark XMP Schema Constants
/** name XMP Schema Constants */
/**@{*/

+ (NSString *)XMP_NS_XMP;
+ (NSString *)XMP_NS_XMP_MM;
+ (NSString *)XMP_NS_XMP_ResourceRef;
+ (NSString *)XMP_NS_XMP_ResourceEvent;
+ (NSString *)XMP_NS_XMP_Rights;
+ (NSString *)XMP_NS_Photoshop;
+ (NSString *)XMP_NS_EXIF;
+ (NSString *)XMP_NS_DC;
+ (NSString *)XMP_NS_XMP_Image;
+ (NSString *)XMP_NS_CREATIVE_COMMONS;

/**@}*/

@end

#endif
