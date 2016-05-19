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

#ifndef AdobeDCXMetadataIteratorHeader
#define AdobeDCXMetadataIteratorHeader

#import <Foundation/Foundation.h>

@class AdobeDCXMetadata;
@class AdobeDCXMetadataPath;

/**
* brief Iterate XMP Properties
*/

@interface AdobeDCXMetadataIterator : NSObject
- (id)initFromXMP:(AdobeDCXMetadata *)meta deep:(BOOL)deep;
+ (instancetype)iteratorFromXMP:(AdobeDCXMetadata *)meta;
+ (instancetype)deepIteratorFromXMP:(AdobeDCXMetadata *)meta;
- (id)initFromXMP:(AdobeDCXMetadata *)meta andPath:(AdobeDCXMetadataPath *)path deep:(BOOL)deep;
+ (instancetype)iteratorFromXMP:(AdobeDCXMetadata *)meta andPath:(AdobeDCXMetadataPath *)path;
+ (instancetype)deepIteratorFromXMP:(AdobeDCXMetadata *)meta andPath:(AdobeDCXMetadataPath *)path;
- (BOOL)next;
- (void)skip;
- (void)skipSubtree;
- (void)skipSiblings;

@property (nonatomic, readonly) AdobeDCXMetadataPath *path;
@property (nonatomic, readonly) NSString *value;
@property (nonatomic, readonly) NSUInteger options;
@end

#endif
