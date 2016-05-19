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

#ifndef AdobeCommunityAssetProtectedHeader
#define AdobeCommunityAssetProtectedHeader

@class AdobeCloud;
@class AdobeCommunitySession;

@interface AdobeCommunityAsset (Protected)

- (instancetype)initWithData:(NSDictionary *)data
community:(NSString *)commmunityID
cloud:(AdobeCloud *)cloud;

- (void)updateWithData:(NSDictionary *)data;

/**
* Get an array of all AdobeCommunityAsset objects asynchronously.
*
* @param communityID       The ID of the community.
* @param pageHref          The href for the page of assets. Pass nil for the initial page.
* @param priority          The priority of the request.
* @param queryString       A string to perform a server-side query on to filter the assets
* @param sortType          Defines how assets are sorted.
* @param categories        Filters assets to the specified categories.
* @param subCategories     Further filters assets to the specified subcategory.
* @param cloud             The cloud to which the assets belong.
* @param assetClass        The class type to be returned. The class must be (or extend) AdobeCommunityAsset.
*                          Pass nil to specify AdobeCommunityAsset.
* @param successBlock      Returns an array of AdobeCommunityAssets and the next page href (nil for last page).
* @param errorBlock        Optionally be notified of an error.
*/
+ (void)assetsForCommunityID:(NSString *)communityID
page:(NSString *)pageHref
priority:(NSOperationQueuePriority)priority
query:(NSString *)queryString
sortType:(AdobeCommunityAssetSortType)sortType
categories:(NSArray *)categories
subCategories:(NSArray *)subCategories
cloud:(AdobeCloud *)cloud
class:(Class)assetClass
successBlock:(void (^)(NSArray *assets, NSString *nextPageHref))successBlock
errorBlock:(void (^)(NSError *error))errorBlock;

+ (NSDate *)convertStringToDate:(NSString *)inputStrDate;

- (AdobeCommunitySession *)session;

@end

#endif
