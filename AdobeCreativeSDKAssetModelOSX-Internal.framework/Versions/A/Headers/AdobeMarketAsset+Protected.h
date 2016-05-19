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

#ifndef AdobeMarketAssetProtectedHeader
#define AdobeMarketAssetProtectedHeader

@class AdobeCloud;

@interface AdobeMarketAsset (Protected)

- (instancetype)initWithData:(NSDictionary *)data
community:(NSString *)commmunityID
cloud:(AdobeCloud *)cloud;

/**
* Get an array of all AdobeMarketAsset objects asynchronously.
*
* @param pageHref          The href for the next page of assets
* @param priority          The priority of the request.
* @param queryString       A string to perform a server-side query on to filter the assets
* @param sortType          Defines how assets are sorted.
* @param creator           Filters assets to a creator.
* @param categories        Filters assets to the specified categories.
* @param subCategories     Further filters assets to the specified subcategory.
* @parma cloud             The cloud to which the assets belong.
* @param successBlock      Get the rendition data, and notified if returned from local cache.
* @param errorBlock        Optionally be notified of an error.
*/
+ (void)assetsForPage:(NSString *)pageHref
priority:(NSOperationQueuePriority)priority
query:(NSString *)queryString
sortType:(AdobeMarketAssetSortType)sortType
creator:(NSString *)creator
categories:(NSArray *)categories
subCategories:(NSArray *)subCategories
cloud:(AdobeCloud *)cloud
successBlock:(void (^)(NSArray *assets, NSString *nextPageHref))successBlock
errorBlock:(void (^)(NSError *error))errorBlock;

@end

#endif
