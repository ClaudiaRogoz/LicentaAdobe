/******************************************************************************
 *
 * ADOBE CONFIDENTIAL
 * ___________________
 *
 * Copyright 2015 Adobe Systems Incorporated
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

#ifndef AdobeCommunityAssetHeader
#define AdobeCommunityAssetHeader

#import <Foundation/Foundation.h>

#ifndef DMALIB
#import <UIKit/UIKit.h>
#endif

#import <AdobeCreativeSDKAssetModelOSX/AdobeCommunityCategory.h>
#import <AdobeCreativeSDKAssetModelOSX/AdobeCommunityUser.h>

@class AdobeCommunityAsyncRequest;

typedef NSArray AdobeCommunityAssets;

/**
 * AdobeCommunityAssetSortType is an enumerated type that allows the client to specify
 * sorting options when accessing community assets.
 */
typedef NS_ENUM (NSInteger, AdobeCommunityAssetSortType)
{
    /** Sort by featured. */
    AdobeCommunityAssetSortTypeFeatured = 0,

    /** Sort by date. */
    AdobeCommunityAssetSortTypeDate = 1,

    /** Sort by date ascending. */
    AdobeCommunityAssetSortTypeDateAscending = 2,

    /** Sort by date descending. */
    AdobeCommunityAssetSortTypeDateDescending = 3,

    /** Sort by popular. */
    AdobeCommunityAssetSortTypePopular = 4,

    /** Sort by alphabetical. */
    AdobeCommunityAssetSortTypeAlphabetical = 5,

    /** Sort by alphabetical ascending. */
    AdobeCommunityAssetSortTypeAlphabeticalAscending = 6,

    /** Sort by alphabetical descending. */
    AdobeCommunityAssetSortTypeAlphabeticalDescending = 7,

    /** Sort by relevance. */
    AdobeCommunityAssetSortTypeRelevance = 8,

    /** Sort by views. */
    AdobeCommunityAssetSortTypeViews = 9,

    /** Sort by likes. */
    AdobeCommunityAssetSortTypeLikes = 10
};

/**
 * AdobeCommunityAssetFilterOptions is an enumerated type that allows the client to specify
 * filter options when accessing community assets.
 */
typedef NS_OPTIONS (NSUInteger, AdobeCommunityAssetFilterOptions)
{
    /** Default filters */
    AdobeCommunityAssetFilterOptionDefaults         = (1 << 0),

    /** Filter by tags. */
    AdobeCommunityAssetFilterOptionTags             = (1 << 1),

    /** Filter by title. */
    AdobeCommunityAssetFilterOptionTitle            = (1 << 2),

    /** Filter by creator. */
    AdobeCommunityAssetFilterOptionCreator          = (1 << 3),

    /** Filter by owner. */
    AdobeCommunityAssetFilterOptionOwner            = (1 << 4),

    /** Filter by description. */
    AdobeCommunityAssetFilterOptionDescription      = (1 << 5)
};

/**
 * AdobeCommunityAssetInfoType is an enumerated type that allows the client to specify
 * information options when getting asset information.
 */
typedef NS_ENUM (NSInteger, AdobeCommunityAssetInfoType)
{
    /** Get asset metadata. */
    AdobeCommunityAssetInfoTypeMetadata = 0,

    /** Get recommended assets. */
    AdobeCommunityAssetInfoTypeRecommended,

    /** Get similar assets. */
    AdobeCommunityAssetInfoTypeSimilar
};

/**
 * AdobeCommunityImageDimension represents the image dimensions in width and height
 * of an Adobe community asset
 */
typedef NS_ENUM (NSInteger, AdobeCommunityAssetImageDimension)
{
    /** Width of the image. */
    AdobeCommunityAssetImageDimensionWidth  = 0,

    /** Height of the image. */
    AdobeCommunityAssetImageDimensionHeight = 1
};

/**
 * AdobeCommunityAssetImageType represents the mime-type of the rendition image.
 */
typedef NS_ENUM (NSInteger, AdobeCommunityAssetImageType)
{
    /** JPEG */
    AdobeCommunityAssetImageTypeJPEG = 0,

    /** PNG */
    AdobeCommunityAssetImageTypePNG = 1,
};

/**
 * AdobeCommunityAssetAbuseType represents the types of abuse.
 */
typedef NS_ENUM (NSInteger, AdobeCommunityAssetAbuseType)
{
    /** General abuse */
    AdobeCommunityAssetAbuseTypeAbuse = 0,

    /** Defamation */
    AdobeCommunityAssetAbuseTypeDefamation,

    /** Pornography */
    AdobeCommunityAssetAbuseTypePornography,

    /** Copyright violation */
    AdobeCommunityAssetAbuseTypeCopyright,

    /** Trademark violation */
    AdobeCommunityAssetAbuseTypeTrademark,

    /** Vulgar */
    AdobeCommunityAssetAbuseTypeVulgar,

    /** Hate */
    AdobeCommunityAssetAbuseTypeHate,

    /** Missing or exploitation of children */
    AdobeCommunityAssetAbuseTypeNCMEC,

    /** Spam */
    AdobeCommunityAssetAbuseTypeSpam,

    /** Phishing */
    AdobeCommunityAssetAbuseTypePhishing,

    /** Other */
    AdobeCommunityAssetAbuseTypeOther
};

/**
 * AdobeCommunityAsset represents an asset in the Creative Cloud Community. It provides accessors that
 * allow the client to obtain information about the asset, download the asset, download thumbnails
 * and previews of the asset, and browse for 'similar' assets given an asset.
 */
@interface AdobeCommunityAsset : NSObject <NSCopying, NSCoding>

/**
 * The asset ID.
 */
@property (nonatomic, readonly, copy) NSString *assetID;

/**
 * The community ID.
 */
@property (nonatomic, readonly, copy) NSString *communityID;

/**
 * Name of the asset.
 */
@property (nonatomic, readonly, copy) NSString *name;

/**
 * The category where the asset may be found.
 */
@property (nonatomic, readonly, strong) AdobeCommunityCategory *category;

/**
 * Creator of the asset.
 */
@property (nonatomic, readonly, strong) AdobeCommunityUser *creator;

/**
 * Date the asset was created.
 */
@property (nonatomic, readonly, strong) NSDate *dateCreated;

/**
 * Date the asset was published.
 */
@property (nonatomic, readonly, strong) NSDate *datePublished;

/**
 * The date the asset was featured.
 */
@property (nonatomic, readonly, strong) NSDate *dateFeatured;

/**
 * Dimensions of the asset.
 */
@property (nonatomic, readonly, assign) CGSize dimensions;

/**
 * File size of the asset.
 */
@property (nonatomic, readonly, assign) long fileSize;

/**
 * Label of the asset.
 */
@property (nonatomic, readonly, copy) NSString *label;

/**
 * MIME type of the asset.
 */
@property (nonatomic, readonly, copy) NSString *nativeMimeType;

/**
 * Additional MIME types that may be used with the asset.
 */
@property (nonatomic, readonly, copy) NSArray *supportedMimeTypes;

/**
 * Array of tags related to the asset.
 */
@property (nonatomic, readonly, copy) NSArray *tags;

#pragma mark - Asset

/**
 * Fetch Community Assets based on the specified parameters asynchronously.
 *
 * @note If the logged-in user is not entitled to access the community, the @c onError block will be
 * called with an appropriate error message.
 *
 * @param communityID       The ID of the community.
 * @param pageHref          The HREF for the next page of assets or @c nil to fetch the first page.
 *                          The success block will indicate the next page's HREF value that can
 *                          be specified for this argument to fetch that page.
 * @param priority          Priority of the network request.
 * @param queryString       A string query to further filter asset based on their names and tags.
 * @param sortType          Defines how the results should be sorted.
 * @param categories        Filter the assets to the specified categories. Specify @c nil to omit.
 * @param subCategories     Filter the returned assets to the specified subcategories. The
 *                          specified subcategory must match it's super-category that is specified
 *                          for the @c categores argument. Specify @c to omit.
 * @param successBlock      Block to execute when all the request assets have been fetched. An
 *                          array of @c AdobeCommunityAsset objects and an NSString HREF value for the
 *                          next page of assets will be passed to that block. If there are no more
 *                          page available, the HREF value will be @c nil.
 * @param errorBlock        Bock to execute if an error occurs. Specify @c NULL to omit.
 */
+ (void)assetsForCommunityID:(NSString *)communityID
                        page:(NSString *)pageHref
                    priority:(NSOperationQueuePriority)priority
                       query:(NSString *)queryString
                    sortType:(AdobeCommunityAssetSortType)sortType
                  categories:(NSArray *)categories
               subCategories:(NSArray *)subCategories
                successBlock:(void (^)(NSArray *assets, NSString *nextPageHref))successBlock
                  errorBlock:(void (^)(NSError *error))errorBlock;

/**
 * Refresh the asset metadata asynchronously.
 *
 * @param priority          The priority of the request.
 * @param successBlock      The refreshed asset.
 * @param errorBlock        Optionally be notified of an error.
 */
- (void)refreshMetadataWithPriority:(NSOperationQueuePriority)priority
                       successBlock:(void (^)(AdobeCommunityAsset *))successBlock
                         errorBlock:(void (^)(NSError *error))errorBlock;

/**
 * Get recommended assets asynchronously.
 *
 * @param pageHref          The HREF for the next page of assets or @c nil to fetch the first page.
 *                          The success block will indicate the next page's HREF value that can
 *                          be specified for this argument to fetch that page.
 * @param priority          The priority of the request.
 * @param successBlock      Block to execute when all the request assets have been fetched. An
 *                          array of @c AdobeCommunityAsset objects and an NSString HREF value for the
 *                          next page of assets will be passed to that block. If there are no more
 *                          page available, the HREF value will be @c nil.
 * @param errorBlock        Optionally be notified of an error.
 */
- (void)recommendedAssetsOnPage:(NSString *)pageHref
                       priority:(NSOperationQueuePriority)priority
                   successBlock:(void (^)(AdobeCommunityAssets *, NSString *nextPageHref))successBlock
                     errorBlock:(void (^)(NSError *error))errorBlock;

/**
 * Get similar assets asynchronously.
 *
 * @param pageHref          The HREF for the next page of assets or @c nil to fetch the first page.
 *                          The success block will indicate the next page's HREF value that can
 *                          be specified for this argument to fetch that page.
 * @param priority          The priority of the request.
 * @param successBlock      Block to execute when all the request assets have been fetched. An
 *                          array of @c AdobeCommunityAsset objects and an NSString HREF value for the
 *                          next page of assets will be passed to that block. If there are no more
 *                          page available, the HREF value will be @c nil.
 * @param errorBlock        Optionally be notified of an error.
 */
- (void)similarAssetsOnPage:(NSString *)pageHref
                   priority:(NSOperationQueuePriority)priority
               successBlock:(void (^)(AdobeCommunityAssets *, NSString *nextPageHref))successBlock
                 errorBlock:(void (^)(NSError *))errorBlock;

#pragma mark - Copy Asset

/**
 * Copy the asset to the logged-in user's account.
 *
 * @param path              A valid path in the Adobe Creative Cloud.
 * @param purchase          Purchase the asset, if needed, before the copy.
 * @param priority          Priority of the request.
 * @param successBlock      Block that is called when the asset has been copied.
 * @param errorBlock        Called when an error occurs.
 *
 * @return An asynchronous request object that can be used to monitor the progress of the request
 * and optionally cancel/interrupt it.
 */
- (void)copyAssetToCreativeCloudPath:(NSString *)path
                    purchaseIfNeeded:(BOOL)purchase
                     requestPriority:(NSOperationQueuePriority)priority
                        successBlock:(void (^)(NSDictionary *))successBlock
                          errorBlock:(void (^)(NSError *))errorBlock;

/**
 * Copy the asset to the logged-in user's account.
 *
 * @param designLibID       The Adobe Design Library ID.
 * @param purchase          Purchase the asset, if needed, before the copy.
 * @param priority          Priority of the request.
 * @param successBlock      Block that is called when the asset has been copied.
 * @param errorBlock        Called when an error occurs.
 *
 * @return An asynchronous request object that can be used to monitor the progress of the request
 * and optionally cancel/interrupt it.
 */
- (void)copyAssetToDesignLibrary:(NSString *)designLibID
                purchaseIfNeeded:(BOOL)purchase
                 requestPriority:(NSOperationQueuePriority)priority
                    successBlock:(void (^)(NSDictionary *))successBlock
                      errorBlock:(void (^)(NSError *))errorBlock;

#pragma mark - Download Asset

/**
 * Get the data of the file asynchronously.
 *
 * The downloaded bits for the asset will be stored in memory as they arrive from the network. If
 * the asset being downloaded is large, this method could use a significant amount of memory, which
 * could potentially cause your application to be terminated. It is recommended to only use this
 * method for downloading small assets. For downloading assets of any arbitrary size, consider using
 * @c downloadToPath:priority:progressBlock:successBlock:cancellationBlock:errorBlock: which stores
 * the downloaded bits in a temporary file on disk during download.
 *
 * @param priority          The priority of the request.
 * @param progressBlock     Optionally track the upload progress.
 * @param successBlock      Get the rendition data, and notified if returned from local cache.
 * @param cancellationBlock Optionally be notified of a cancellation on upload.
 * @param errorBlock        Optionally be notified of an error.
 *
 * @see downloadToPath:priority:progressBlock:successBlock:cancellationBlock:errorBlock:
 */
- (AdobeCommunityAsyncRequest *)download:(NSOperationQueuePriority)priority
                           progressBlock:(void (^)(double fractionCompleted))progressBlock
                            successBlock:(void (^)(NSData *data))successBlock
                       cancellationBlock:(void (^)(void))cancellationBlock
                              errorBlock:(void (^)(NSError *error))errorBlock;

/**
 * Download the asset to the specified @c filePath asynchronously.
 *
 * This method is the preferred way for downloading Market Assets since the downloaded bits are
 * stored in a temporary file on disk instead of memory. Once the download operation has finished,
 * the downloaded bits will be available at the specified file system path.
 *
 * @note The downloaded bits are only accessible @em after the file has been fully downloaded. To
 * observer the progress of the download process, use the @c onProgress block.
 *
 * @param filePath            File system path where the downloaded bits will be placed once the
 *                            download process has completed.
 * @param priority            The initial priority of the request. This can be changed using the
 *                            returned object from the this method.
 * @param progressBlock       Optionally used to track the progress of the download task. Specify
 *                            @c NULL if you don't want to track the download progress.
 * @param successBlock        The block to execute after the file has been successfully downloaded.
 *                            The file system path to the downloaded file will be returned.
 * @param cancellationBlock   Optionally used to be notified of cancellation of the request.
 *                            Specify @c NULL to omit the block.
 * @param errorBlock          Optionally be notified of any errors. Specify @c NULL to omit the
 *                            error block.
 *
 * @return An instance of the @c AdobeCommunityAsyncRequest used to control the request. The request
 *         priority can be changed or the request itself can be cancelled.
 */
- (AdobeCommunityAsyncRequest *)downloadToPath:(NSString *)filePath
                                      priority:(NSOperationQueuePriority)priority
                                 progressBlock:(void (^)(double fractionCompleted))progressBlock
                                  successBlock:(void (^)(AdobeCommunityAsset *asset))successBlock
                             cancellationBlock:(void (^)(void))cancellationBlock
                                    errorBlock:(void (^)(NSError *error))errorBlock;

#pragma mark - Download Rendition

/**
 * Get the rendition of the asset as NSData asynchronously and scale along an edge.
 *
 * The maximum size value is 1024. Any values larger are clipped to 1024.
 *
 * @param dimension         Width or height to scale to.
 * @param size              Max length of the edge we scale to.
 * @param type              Rendition file type.
 * @param priority          The priority of the request.
 * @param progressBlock     Optionally track the upload progress.
 * @param successBlock      Get the rendition data, and notified if returned from local cache.
 * @param cancellationBlock Optionally be notified of a cancellation on upload.
 * @param errorBlock        Optionally be notified of an error.
 */
- (AdobeCommunityAsyncRequest *)downloadRenditionWithDimension:(AdobeCommunityAssetImageDimension)dimension
                                                          size:(NSUInteger)size
                                                          type:(AdobeCommunityAssetImageType)type
                                                      priority:(NSOperationQueuePriority)priority
                                                 progressBlock:(void (^)(double fractionCompleted))progressBlock
                                                  successBlock:(void (^)(NSData *imageData, BOOL fromCache))successBlock
                                             cancellationBlock:(void (^)(void))cancellationBlock
                                                    errorBlock:(void (^)(NSError *error))errorBlock;

#pragma mark - Likes

/**
 * Get likes on the asset asynchronously.
 *
 * @param pageHref          The HREF for the next page of assets or @c nil to fetch the first page.
 * @param priority          The priority of the request.
 * @param successBlock      An array of AdobeCommunityUsers who like the asset.
 * @param errorBlock        Optionally be notified of an error.
 */
- (void)likesForAssetOnPage:(NSString *)pageHref
                   priority:(NSOperationQueuePriority)priority
               successBlock:(void (^)(AdobeCommunityUsers *userLikes, NSString *nextPageHref))successBlock
                 errorBlock:(void (^)(NSError *error))errorBlock;

/**
 * Add like to asset asynchronously.
 *
 * @param priority          The priority of the request.
 * @param successBlock      An array of recommended AdobeCommunityAssets.
 * @param errorBlock        Optionally be notified of an error.
 */
- (void)addLikeToAssetWithPriority:(NSOperationQueuePriority)priority
                      successBlock:(void (^)(void))successBlock
                        errorBlock:(void (^)(NSError *error))errorBlock;

/**
 * Remove like from asset asynchronously.
 *
 * @param priority          The priority of the request.
 * @param successBlock      An array of recommended AdobeCommunityAssets.
 * @param errorBlock        Optionally be notified of an error.
 */
- (void)removeLikeFromAssetWithPriority:(NSOperationQueuePriority)priority
                           successBlock:(void (^)(void))successBlock
                             errorBlock:(void (^)(NSError *error))errorBlock;

#pragma mark - Comments

/**
 * Get comments on the asset asynchronously.
 *
 * @param pageHref          The HREF for the next page of assets or @c nil to fetch the first page.
 * @param priority          The priority of the request.
 * @param successBlock      An array of comment metadata on the asset.
 * @param errorBlock        Optionally be notified of an error.
 */
- (void)commentsForAssetOnPage:(NSString *)pageHref
                      priority:(NSOperationQueuePriority)priority
                  successBlock:(void (^)(NSArray *comments, NSString *nextPageHref))successBlock
                    errorBlock:(void (^)(NSError *error))errorBlock;

/**
 * Add comment to asset asynchronously.
 *
 * @param comment           The comment to add to the asset.
 * @param priority          The priority of the request.
 * @param successBlock      An array of recommended AdobeCommunityAssets.
 * @param errorBlock        Optionally be notified of an error.
 */
- (void)addCommentToAsset:(NSString *)comment
                 priority:(NSOperationQueuePriority)priority
             successBlock:(void (^)(void))successBlock
               errorBlock:(void (^)(NSError *error))errorBlock;

/**
 * Remove comment from asset asynchronously.
 *
 * @param commentID         The commentID to remove from the asset.
 * @param priority          The priority of the request.
 * @param successBlock      An array of recommended AdobeCommunityAssets.
 * @param errorBlock        Optionally be notified of an error.
 */
- (void)removeCommentFromAsset:(NSString *)commentID
                      priority:(NSOperationQueuePriority)priority
                  successBlock:(void (^)(void))successBlock
                    errorBlock:(void (^)(NSError *error))errorBlock;

#pragma mark - Report Abuse

/**
 * Report abuse on asset asynchronously.
 *
 * @param abuseType         The abuse type.
 * @param priority          The priority of the request.
 * @param successBlock      An array of recommended AdobeCommunityAssets.
 * @param errorBlock        Optionally be notified of an error.
 */
- (void)reportAbuseOnAsset:(AdobeCommunityAssetAbuseType)abuseType
                  priority:(NSOperationQueuePriority)priority
              successBlock:(void (^)(void))successBlock
                errorBlock:(void (^)(NSError *error))errorBlock;

@end

#endif
