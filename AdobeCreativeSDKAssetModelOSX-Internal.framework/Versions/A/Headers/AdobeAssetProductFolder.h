/******************************************************************************
*
* ADOBE CONFIDENTIAL
* ___________________
*
* Copyright 2014 Adobe Systems Incorporated
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

#ifndef AdobeAssetProductFolderHeader
#define AdobeAssetProductFolderHeader

#import <AdobeCreativeSDKAssetModelOSX/AdobeAssetFolder.h>

@class AdobeCloud;

typedef NS_ENUM (NSInteger, AdobeAssetProduct)
{
AdobeAssetProductUndefined = 0,
AdobeAssetProductDraw,
AdobeAssetProductLibrary __deprecated_enum_msg("Now done with ALM"),
AdobeAssetProductLine,
AdobeAssetProductSketch,
AdobeAssetProductMix,
AdobeAssetProductComp
};

/**
* AdobeAssetProductFolder items are fetched from the cloud in pages, so the field on which the items
* should be sorted as well as the sort direction must be specified when setting up
* this instance. If you need to change the sorting, you will need to create a new
* instance with the specified sort options.
*
* Once you have an AdobeAssetProductFolder instance set up, you can call hasNextPage and
* loadNextPage to start loading folder items from the cloud as needed.
*/

/**
*
* AdobeAssetProductFolder represents a folder type for Adobe app product files in the Creative Cloud and
* provides access to its packages in pages of data.
*
*/
@interface AdobeAssetProductFolder : AdobeAssetFolder

+ (AdobeAssetProductFolder *)rootForProduct:(AdobeAssetProduct)product
inCloud:(AdobeCloud *)cloud __deprecated_msg("Use rootForProduct:cloud");

+ (AdobeAssetProductFolder *)rootForProduct:(AdobeAssetProduct)product
cloud:(AdobeCloud *)cloud;

+ (AdobeAssetProductFolder *)rootForProduct:(AdobeAssetProduct)product
inCloud:(AdobeCloud *)cloud
orderedByField:(AdobeAssetFolderOrderBy)field
orderDirection:(AdobeAssetFolderOrderDirection)direction __deprecated_msg("Use rootForProduct:cloud:orderedByField:orderDirection");

+ (AdobeAssetProductFolder *)rootForProduct:(AdobeAssetProduct)product
cloud:(AdobeCloud *)cloud
orderedByField:(AdobeAssetFolderOrderBy)field
orderDirection:(AdobeAssetFolderOrderDirection)direction;

@end

#endif /* ifndef AdobeAssetProductFolderHeader */
