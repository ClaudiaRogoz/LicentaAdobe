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

#ifndef AdobeMarketAssetHeader
#define AdobeMarketAssetHeader

#import <Foundation/Foundation.h>

#import <AdobeCreativeSDKAssetModelOSX/AdobeCommunity.h>
#import <AdobeCreativeSDKAssetModelOSX/AdobeCommunityAsset.h>
#import <AdobeCreativeSDKAssetModelOSX/AdobeCommunityUser.h>
#import <AdobeCreativeSDKAssetModelOSX/AdobeMarketCategory.h>

@class AdobeCommunityAsyncRequest;

/**
 * The content-types for which to request a market asset rendition.
 */
typedef NS_ENUM (NSInteger, AdobeMarketAssetFileRenditionType)
{
    /** The JPEG file rendition type on the Creative Cloud */
    AdobeMarketAssetFileRenditionTypeJPEG = 0,

    /** The PNG file rendition type on the Creative Cloud */
    AdobeMarketAssetFileRenditionTypePNG = 1
};

/**
 * AdobeMarketImageDimension represents the image dimensions in width and height
 * of an AdobeMarketAsset
 */
typedef NS_ENUM (NSInteger, AdobeMarketImageDimension)
{
    /** Width of the image. */
    AdobeMarketImageDimensionWidth  = 0,

    /** Height of the image. */
    AdobeMarketImageDimensionHeight = 1
};

/**
 * AdobeMarketAssetSortType is an enumerated type that allows the client to specify
 * sorting options when accessing market assets
 */
typedef NS_ENUM (NSInteger, AdobeMarketAssetSortType)
{
    /** Sort by featured. */
    AdobeMarketAssetSortTypeFeatured   = 0,

    /** Sort by date. */
    AdobeMarketAssetSortTypeDate       = 1,

    /** Sort by relevance. */
    AdobeMarketAssetSortTypeRelevance  = 8,

    /** Sort by downloaded. */
    AdobeMarketAssetSortTypeDownloaded = 99
};

/**
 * AdobeMarketAsset represents an asset in the Creative Cloud Market. It provides accessors that
 * allow the client to obtain information about the asset, download the asset, download thumbnails
 * and previews of the asset, and browse for 'similar' assets given an asset.
 */
@interface AdobeMarketAsset : AdobeCommunityAsset

/**
 * The category where the asset may be found.
 */
@property (nonatomic, readonly, strong) AdobeMarketCategory *category;

/**
 * Dimensions for the thumbnail representing the asset.
 */
@property (nonatomic, readonly, assign) CGSize thumbnailDimensions;

/**
 * Whether or not the asset has been downloaded to the user's Creative Cloud files.
 */
@property (nonatomic, readwrite, assign, getter = isDownloaded) BOOL downloaded;

/**
 * Fetch Market Assets based on the specified parameters asynchronously.
 *
 * This method will use the passed in arguments to construct a network request to fetch Market
 * Assets from the Creative Cloud Market Browser.
 *
 * @note If the logged-in user is not entitled to the Market Browser, the @c onError block will be
 * called with an appropriate error message.
 *
 * @param pageHref          The HREF for the page of assets or @c nil to fetch the first page.
 *                          The completion block will indicate the next page's HREF value that can
 *                          be specified for this argument to fetch that page.
 * @param priority          Priority of the network request.
 * @param queryString       A string query to further filter asset based on their names and tags.
 * @param sortType          Defines how the results should be sorted.
 * @param creator           Filter the returned assets to the specified creator. Specify @c nil to
 *                          omit.
 * @param categories        Filter the assets to the specified categories. Specify @c nil to omit.
 * @param subCategories     Filter the returned assets to the specified subcategories. The
 *                          specified subcategory must match it's super-category that is specified
 *                          for the @c categores argument. Specify @c to omit.
 * @param successBlock      Block to execute when all the request assets have been fetched. An
 *                          array of @c AdobeMarketAsset objects and an NSString HREF value for the
 *                          next page of assets will be passed to that block. If there are no more
 *                          page available, the HREF value will be @c nil.
 * @param errorBlock        Bock to execute if an error occurs. Specify @c NULL to omit.
 */
+ (void)assetsForPage:(NSString *)pageHref
             priority:(NSOperationQueuePriority)priority
                query:(NSString *)queryString
             sortType:(AdobeMarketAssetSortType)sortType
              creator:(NSString *)creator
           categories:(NSArray *)categories
        subCategories:(NSArray *)subCategories
         successBlock:(void (^)(NSArray *assets, NSString *nextPageHref))successBlock
           errorBlock:(void (^)(NSError *error))errorBlock;


/**
 * Copy the asset to the logged-in user's account.
 *
 * @param priority          Priority of the request.
 * @param successBlock      Block that is called when the asset has been copied.
 * @param errorBlock        Called when an error occurs.
 */
- (void)copyAssetWithRequestPriority:(NSOperationQueuePriority)priority
                        successBlock:(void (^)(NSDictionary *))successBlock
                          errorBlock:(void (^)(NSError *))errorBlock;

@end

#endif
