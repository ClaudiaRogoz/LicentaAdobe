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

#ifndef AdobeDCXMetadataPathHeader
#define AdobeDCXMetadataPathHeader

#import <Foundation/Foundation.h>

/**
* brief Represents an XMP property path.
*/
@interface AdobeDCXMetadataPath : NSObject
+ (instancetype)pathFromSchema:(NSString *)schema andName:(NSString *)name;
- (id)initFromSchema:(NSString *)schema andName:(NSString *)name;

- (AdobeDCXMetadataPath *)withSchema:(NSString *)schema andName:(NSString *)name;
- (AdobeDCXMetadataPath *)withIndex:(NSUInteger)index;
- (AdobeDCXMetadataPath *)lastItem;


// Useful for moving subtrees from one place to another while iterating
- (AdobeDCXMetadataPath *)replacePrefix:(AdobeDCXMetadataPath *)prefix with:(AdobeDCXMetadataPath *)newPrefix;

+ (instancetype)documentId;
+ (instancetype)instanceId;
+ (instancetype)derivedFrom;
+ (instancetype)originalDocumentId;
+ (instancetype)history;
+ (instancetype)ingredients;
+ (instancetype)pantry;
+ (instancetype)manageTo;
+ (instancetype)manageUi;
+ (instancetype)creatorTool;
+ (instancetype)createDate;
+ (instancetype)modifyDate;
+ (instancetype)metadataDate;
+ (instancetype)license;
+ (instancetype)rightsMarked;
+ (instancetype)usageTerms;
+ (instancetype)format;
+ (instancetype)subject;
+ (instancetype)rights;
+ (instancetype)creator;
+ (instancetype)attributionURL;
+ (instancetype)attributionName;

@property (nonatomic, readonly) NSString *schema;
@property (nonatomic, readonly) NSString *name;
@end

#endif
