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

#ifndef AdobeDCXRenditionMetadataBuilderHeader
#define AdobeDCXRenditionMetadataBuilderHeader

#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeDCXMutableMetadata.h>
#import <Foundation/Foundation.h>

/**
* brief XMP Metadata being prepared for a rendition.
*/

@interface AdobeDCXRenditionMetadataBuilder : NSObject

#pragma mark Constructors
/** name Constructors */
/**@{*/

/**
* brief Instantiates a rendition metadata builder associated with the given composite branch.
*/
+ (instancetype)renditionMetadataBuilderForCompositeBranch:(AdobeDCXCompositeBranch *)compositeBranch withType:(NSString *)type;
- (id)initRenditionMetadataBuilderForCompositeBranch:(AdobeDCXCompositeBranch *)compositeBranch withType:(NSString *)type;

/**@}*/
#pragma mark Adding components
/** name Adding components */
/**@{*/

- (BOOL)addComponent:(AdobeDCXComponent *)component fromBranch:(AdobeDCXCompositeBranch *)branch fromPart:(NSString *)fromPart fromDescription:(NSString *)fromDescription toPart:(NSString *)toPart toDescription:(NSString *)toDescription withError:(NSError **)errorPtr;
- (BOOL)addComponent:(AdobeDCXComponent *)component fromBranch:(AdobeDCXCompositeBranch *)branch fromPart:(NSString *)fromPart toPart:(NSString *)toPart withError:(NSError **)errorPtr;
- (BOOL)addComponent:(AdobeDCXComponent *)component fromBranch:(AdobeDCXCompositeBranch *)branch toPart:(NSString *)toPart toDescription:(NSString *)toDescription withError:(NSError **)errorPtr;

/**@}*/
#pragma mark Adding files
/** name Adding files */
/**@{*/

- (BOOL)addFile:(NSString *)filePath fromPart:(NSString *)fromPart fromDescription:(NSString *)fromDescription toPart:(NSString *)toPart toDescription:(NSString *)toDescription withError:(NSError **)errorPtr;
- (BOOL)addFile:(NSString *)filePath fromPart:(NSString *)fromPart toPart:(NSString *)toPart withError:(NSError **)errorPtr;

/**@}*/
#pragma mark Accessing other metadata
/** name Accessing other metadata */
/**@{*/

@property (readonly, nonatomic) AdobeDCXMutableMetadata *metadata;

/**@}*/
@end

#endif
