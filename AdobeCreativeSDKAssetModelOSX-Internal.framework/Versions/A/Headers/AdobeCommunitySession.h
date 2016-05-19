/*************************************************************************
*
* ADOBE CONFIDENTIAL
* ___________________
*
*  Copyright 2015 Adobe Systems Incorporated
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

#ifndef AdobeCommunitySessionHeader
#define AdobeCommunitySessionHeader

#import <Foundation/Foundation.h>

#import <AdobeCreativeSDKAssetModelOSX/AdobeCommunityAsset.h>

@class AdobeNetworkHTTPRequest;
@class AdobeCloudEndpoint;

@interface AdobeCommunitySession : AdobeCloudServiceSession

/**
* Legacy service endpoint.
*/
+ (AdobeCloudEndpoint *)serviceEndpoint;

#pragma mark - Community

/**
* Get information about a community.
*
* @param communityID         The ID of the community.
* @param priority            The relative priority of the HTTP request.
* @param queue               If not nil queue determines the operation queue handler gets executed on.
* @param successBlock        Called when the method has successfully finished.
* @param errorBlock          Called when an error has occurred.
*
* @return                    A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)infoForCommunityID:(NSString *)communityID
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
successBlock:(void (^)(NSDictionary *meta))successBlock
errorBlock:(void (^)(NSError *err))errorBlock;

/**
* Get categories for a community.
*
* @param communityID         The ID of the community.
* @param priority            The relative priority of the HTTP request.
* @param queue               If not nil queue determines the operation queue handler gets executed on.
* @param successBlock        Called when the method has successfully finished.
* @param errorBlock          Called when an error has occurred.
*
* @return                    A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)categoriesForCommunityID:(NSString *)communityID
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
successBlock:(void (^)(NSDictionary *meta))successBlock
errorBlock:(void (^)(NSError *err))errorBlock;

/**
* Get history for a community.
*
* @param communityID         The ID of the community.
* @param priority            The relative priority of the HTTP request.
* @param queue               If not nil queue determines the operation queue handler gets executed on.
* @param successBlock        Called when the method has successfully finished.
* @param errorBlock          Called when an error has occurred.
*
* @return                    A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)historyForCommunityID:(NSString *)communityID
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
successBlock:(void (^)(NSDictionary *meta))successBlock
errorBlock:(void (^)(NSError *err))errorBlock;

#pragma mark - Assets

/**
* Get the assets for a community.
*
* @param communityID         The ID of the community.
* @param cursor              The page cursor to request. Pass in nil for initial page.
* @param size                The maximum number of items to return per page (set 0 to use default, max 50).
* @param query               Optional query string to filter the assets (max 128 characters).
* @param filters             Or'd values to filter by.
* @param sortOrderType       The sort order for the returned results.
* @param mimeTypes           Restrict to mime types.
* @param categories          Restrict to the specified category IDs.
* @param subCategories       Further restrict the category to the specified subcategory IDs.
* @param priority            The relative priority of the HTTP request.
* @param queue               If not nil queue determines the operation queue handler gets executed on.
* @param successBlock        Called when the method has successfully finished.
* @param errorBlock          Called when an error has occurred.
*
* @return                    A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)assetsForCommunityID:(NSString *)communityID
cursor:(NSString *)cursor
size:(NSUInteger)size
query:(NSString *)query
filters:(AdobeCommunityAssetFilterOptions)filters
sortOrder:(AdobeCommunityAssetSortType)sortOrderType
mimeTypes:(NSArray *)mimeTypes
categories:(NSArray *)categories
subCategories:(NSArray *)subCategories
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
successBlock:(void (^)(NSDictionary *meta, NSString *nextPageHref))successBlock
errorBlock:(void (^)(NSError *err))errorBlock;

/**
* Get information about an asset.
*
* @param assetID             The ID of the asset.
* @param communityID         The ID of the community.
* @param cursor              The page cursor to request (ignored for type AdobeCommunityAssetInfoTypeMetadata).
*                            Pass in nil for initial page.
* @param size                The maximum number of items to return per page (set 0 to use default, max 50).
*                            Ignored for type AdobeCommunityAssetInfoTypeMetadata.
* @param infoType            The type of information to request.
* @param priority            The relative priority of the HTTP request.
* @param queue               If not nil queue determines the operation queue handler gets executed on.
* @param successBlock        Called when the method has successfully finished.
* @param errorBlock          Called when an error has occurred.
*
* @return                    A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)infoForAssetID:(NSString *)assetID
communityID:(NSString *)communityID
cursor:(NSString *)cursor
size:(NSUInteger)size
infoType:(AdobeCommunityAssetInfoType)infoType
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
successBlock:(void (^)(NSDictionary *meta, NSString *nextPageHref))successBlock
errorBlock:(void (^)(NSError *err))errorBlock;

/**
* Create (publish) an asset.
*
* @param communityID         The ID of the community.
* @param data                The data to publish.
* @param priority            The relative priority of the HTTP request.
* @param queue               If not nil queue determines the operation queue handler gets executed on.
* @param successBlock        Called when the method has successfully finished.
* @param errorBlock          Called when an error has occurred.
*
* @return                    A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)createAssetInCommunityID:(NSString *)communityID
data:(NSDictionary *)data
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
successBlock:(void (^)(NSDictionary *meta))successBlock
errorBlock:(void (^)(NSError *err))errorBlock;

/**
* Update an asset.
*
* @param assetID             The ID of the asset.
* @param communityID         The ID of the community.
* @param data                The data to publish.
* @param priority            The relative priority of the HTTP request.
* @param queue               If not nil queue determines the operation queue handler gets executed on.
* @param successBlock        Called when the method has successfully finished.
* @param errorBlock          Called when an error has occurred.
*
* @return                    A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)updateAssetID:(NSString *)assetID
communityID:(NSString *)communityID
data:(NSDictionary *)data
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
successBlock:(void (^)(NSDictionary *meta))successBlock
errorBlock:(void (^)(NSError *err))errorBlock;

/**
* Delete (unpublish) an asset.
*
* @param assetID             The ID of the asset.
* @param communityID         The ID of the community.
* @param priority            The relative priority of the HTTP request.
* @param queue               If not nil queue determines the operation queue handler gets executed on.
* @param successBlock        Called when the method has successfully finished.
* @param errorBlock          Called when an error has occurred.
*
* @return                    A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)deleteAssetID:(NSString *)assetID
communityID:(NSString *)communityID
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
successBlock:(void (^)(void))successBlock
errorBlock:(void (^)(NSError *err))errorBlock;

#pragma mark - Renditions

/**
* Get rendition for asset.
*
* @param assetID             The ID of the asset
* @param communityID         The ID of the community.
* @param type                The mime-type of the rendition.
* @param dimension           The dimension of the rendition.
* @param size                The size of the rendition (max 1280).
* @param priority            The relative priority of the HTTP request.
* @param queue               If not nil queue determines the operation queue handler gets executed on.
* @param successBlock        Called when the method has successfully finished.
* @param errorBlock          Called when an error has occurred.
*
* @return                    A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)renditionForAssetID:(NSString *)assetID
communityID:(NSString *)communityID
type:(AdobeCommunityAssetImageType)type
dimension:(AdobeCommunityAssetImageDimension)dimension
size:(NSUInteger)size
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
successBlock:(void (^)(NSURL *renditionURL))successBlock
errorBlock:(void (^)(NSError *err))errorBlock;

/**
* Get rendition for asset.
*
* @param url                The url of the asset.
* @param priority            The relative priority of the HTTP request.
* @param queue               If not nil queue determines the operation queue handler gets executed on.
* @param successBlock        Called when the method has successfully finished.
* @param errorBlock          Called when an error has occurred.
*
* @return                    A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)renditionForAssetWithURL:(NSURL *)url
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
successBlock:(void (^)(NSData *))successBlock
errorBlock:(void (^)(NSError *))errorBlock;

#pragma mark - Original Content

/**
* Get original content for asset.
*
* @param assetID             The ID of the asset
* @param communityID         The ID of the community.
* @param resourcePath        Optional path for multi-resource assets. Pass nil for basic.
* @param version             The version of the asset (zero based). Pass in -1 for current version.
* @param downloadPath        File system path where the asset should be downloaded.
* @param priority            The relative priority of the HTTP request.
* @param queue               If not nil queue determines the operation queue handler gets executed on.
* @param successBlock        Called when the method has successfully finished.
* @param errorBlock          Called when an error has occurred.
*
* @return                    A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)contentForAssetID:(NSString *)assetID
communityID:(NSString *)communityID
resourcePath:(NSString *)resourcePath
version:(NSInteger)version
downloadPath:(NSString *)downloadPath
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
successBlock:(void (^)(void))successBlock
errorBlock:(void (^)(NSError *err))errorBlock;

#pragma mark - Video

/**
* Get video info for asset.
*
* @param assetID             The ID of the asset
* @param communityID         The ID of the community.
* @param priority            The relative priority of the HTTP request.
* @param queue               If not nil queue determines the operation queue handler gets executed on.
* @param successBlock        Called when the method has successfully finished.
* @param errorBlock          Called when an error has occurred.
*
* @return                    A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)videoForAssetID:(NSString *)assetID
communityID:(NSString *)communityID
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
successBlock:(void (^)(NSDictionary *meta))successBlock
errorBlock:(void (^)(NSError *err))errorBlock;

/**
* Get video embed document for asset.
*
* @param assetID             The ID of the asset
* @param communityID         The ID of the community.
* @param priority            The relative priority of the HTTP request.
* @param queue               If not nil queue determines the operation queue handler gets executed on.
* @param successBlock        Called when the method has successfully finished.
* @param errorBlock          Called when an error has occurred.
*
* @return                    A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)videoEmbedForAssetID:(NSString *)assetID
communityID:(NSString *)communityID
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
successBlock:(void (^)(NSString *html))successBlock
errorBlock:(void (^)(NSError *err))errorBlock;

/**
* Get video stream for asset.
*
* @param assetID             The ID of the asset
* @param communityID         The ID of the community.
* @param priority            The relative priority of the HTTP request.
* @param queue               If not nil queue determines the operation queue handler gets executed on.
* @param successBlock        Called when the method has successfully finished.
* @param errorBlock          Called when an error has occurred.
*
* @return                    A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)videoStreamForAssetID:(NSString *)assetID
communityID:(NSString *)communityID
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
successBlock:(void (^)(NSURL *streamURL))successBlock
errorBlock:(void (^)(NSError *err))errorBlock;

#pragma mark - XMP

/**
* Get XMP for asset.
*
* @param assetID             The ID of the asset
* @param communityID         The ID of the community.
* @param path                Optional path for multi-resource assets. Pass nil for basic.
* @param priority            The relative priority of the HTTP request.
* @param queue               If not nil queue determines the operation queue handler gets executed on.
* @param successBlock        Called when the method has successfully finished.
* @param errorBlock          Called when an error has occurred.
*
* @return                    A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)xmpForAssetID:(NSString *)assetID
communityID:(NSString *)communityID
path:(NSString *)path
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
successBlock:(void (^)(NSDictionary *xmp))successBlock
errorBlock:(void (^)(NSError *err))errorBlock;

#pragma mark - Artwork

/**
* Get artwork for asset.
*
* @param assetID             The ID of the asset
* @param communityID         The ID of the community.
* @param priority            The relative priority of the HTTP request.
* @param queue               If not nil queue determines the operation queue handler gets executed on.
* @param successBlock        Called when the method has successfully finished.
* @param errorBlock          Called when an error has occurred.
*
* @return                    A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)artworkForAssetID:(NSString *)assetID
communityID:(NSString *)communityID
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
successBlock:(void (^)(NSDictionary *meta))successBlock
errorBlock:(void (^)(NSError *err))errorBlock;

/**
* Add artwork to asset.
*
* @param assetID             The ID of the asset
* @param communityID         The ID of the community.
* @param resourcePath        The path to the resource to use for the artwork
* @param priority            The relative priority of the HTTP request.
* @param queue               If not nil queue determines the operation queue handler gets executed on.
* @param successBlock        Called when the method has successfully finished.
* @param errorBlock          Called when an error has occurred.
*
* @return                    A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)addArtworkToAssetID:(NSString *)assetID
communityID:(NSString *)communityID
resourcePath:(NSString *)resourcePath
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
successBlock:(void (^)(NSDictionary *meta))successBlock
errorBlock:(void (^)(NSError *err))errorBlock;

/**
* Remove artwork from asset.
*
* @param assetID             The ID of the asset
* @param communityID         The ID of the community.
* @param priority            The relative priority of the HTTP request.
* @param queue               If not nil queue determines the operation queue handler gets executed on.
* @param successBlock        Called when the method has successfully finished.
* @param errorBlock          Called when an error has occurred.
*
* @return                    A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)removeArtworkFromAssetID:(NSString *)assetID
communityID:(NSString *)communityID
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
successBlock:(void (^)(void))successBlock
errorBlock:(void (^)(NSError *err))errorBlock;

#pragma mark - My Info

/**
* Get info about calling user.
*
* @param communityID         The ID of the community.
* @param cursor              The page cursor to request. Pass in nil for initial page.
* @param size                The maximum number of items to return per page (set 0 to use default, max 50). Ignored for AdobeCommunityUserFilterTypeAll.
* @param filter              Filter the calling user's info.
* @param categories          Restrict to the specified category IDs. Ignored for AdobeCommunityUserFilterTypeAll.
* @param language            The language the information is returned in.
* @param priority            The relative priority of the HTTP request.
* @param queue               If not nil queue determines the operation queue handler gets executed on.
* @param successBlock        Called when the method has successfully finished.
* @param errorBlock          Called when an error has occurred.
*
* @return                    A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)myInfoForCommunityID:(NSString *)communityID
cursor:(NSString *)cursor
size:(NSUInteger)size
filter:(AdobeCommunityUserFilterType)filter
categories:(NSArray *)categories
language:(NSString *)language
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
successBlock:(void (^)(NSDictionary *meta, NSString *nextPageHref))successBlock
errorBlock:(void (^)(NSError *err))errorBlock;

/**
* Purchase asset.
*
* @param assetID             The asset ID to purchase.
* @param communityID         The ID of the community.
* @param priority            The relative priority of the HTTP request.
* @param queue               If not nil queue determines the operation queue handler gets executed on.
* @param successBlock        Called when the method has successfully finished.
* @param errorBlock          Called when an error has occurred.
*
* @return                    A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)purchaseAssetID:(NSString *)assetID
communityID:(NSString *)communityID
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
successBlock:(void (^)(void))successBlock
errorBlock:(void (^)(NSError *err))errorBlock;

#pragma mark - User Info

/**
* Get info about a user.
*
* @param userID              The ID of the user.
* @param communityID         The ID of the community.
* @param cursor              The page cursor to request. Pass in nil for initial page.
* @param size                The maximum number of items to return per page (set 0 to use default, max 50). Ignored for AdobeCommunityUserFilterTypeAll.
* @param filter              Filter the calling user's info. Only AdobeCommunityUserFilterTypeAll, AdobeCommunityUserFilterTypeAssets, AdobeCommunityUserFilterTypeLikes are supported.
* @param categories          Restrict to the specified category IDs. Ignored for AdobeCommunityUserFilterTypeAll.
* @param priority            The relative priority of the HTTP request.
* @param queue               If not nil queue determines the operation queue handler gets executed on.
* @param successBlock        Called when the method has successfully finished.
* @param errorBlock          Called when an error has occurred.
*
* @return                    A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)infoForUserID:(NSString *)userID
communityID:(NSString *)communityID
cursor:(NSString *)cursor
size:(NSUInteger)size
filter:(AdobeCommunityUserFilterType)filter
categories:(NSArray *)categories
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
successBlock:(void (^)(NSDictionary *meta, NSString *nextPageHref))successBlock
errorBlock:(void (^)(NSError *err))errorBlock;

#pragma mark - Likes

/**
* Get likes for an asset.
*
* @param assetID             The asset ID to get likes for.
* @param communityID         The ID of the community.
* @param cursor              The page cursor to request. Pass in nil for initial page.
* @param size                The maximum number of items to return per page (set 0 to use default, max 50).
* @param priority            The relative priority of the HTTP request.
* @param queue               If not nil queue determines the operation queue handler gets executed on.
* @param successBlock        Called when the method has successfully finished.
* @param errorBlock          Called when an error has occurred.
*
* @return                    A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)likesForAssetID:(NSString *)assetID
communityID:(NSString *)communityID
cursor:(NSString *)cursor
size:(NSUInteger)size
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
successBlock:(void (^)(NSDictionary *meta, NSString *nextPageHref))successBlock
errorBlock:(void (^)(NSError *err))errorBlock;

/**
* Like an asset.
*
* @param assetID             The asset ID to add like to.
* @param communityID         The ID of the community.
* @param priority            The relative priority of the HTTP request.
* @param queue               If not nil queue determines the operation queue handler gets executed on.
* @param successBlock        Called when the method has successfully finished.
* @param errorBlock          Called when an error has occurred.
*
* @return                    A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)addLikeToAssetID:(NSString *)assetID
communityID:(NSString *)communityID
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
successBlock:(void (^)(void))successBlock
errorBlock:(void (^)(NSError *err))errorBlock;

/**
* Unike an asset.
*
* @param assetID             The asset ID to remove like from.
* @param communityID         The ID of the community.
* @param priority            The relative priority of the HTTP request.
* @param queue               If not nil queue determines the operation queue handler gets executed on.
* @param successBlock        Called when the method has successfully finished.
* @param errorBlock          Called when an error has occurred.
*
* @return                    A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)removeLikeFromAssetID:(NSString *)assetID
communityID:(NSString *)communityID
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
successBlock:(void (^)(void))successBlock
errorBlock:(void (^)(NSError *err))errorBlock;

#pragma mark - Copy Asset

/**
* Copy an asset to a Creative Cloud location.
*
* @param assetID             The asset ID to purchase.
* @param communityID         The ID of the community.
* @param destinationPath     The destination path to copy to.
* @param priority            The relative priority of the HTTP request.
* @param queue               If not nil queue determines the operation queue handler gets executed on.
* @param successBlock        Called when the method has successfully finished.
* @param errorBlock          Called when an error has occurred.
*
* @return                    A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)copyAssetID:(NSString *)assetID
communityID:(NSString *)communityID
destinationPath:(NSString *)destinationPath
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
successBlock:(void (^)(NSDictionary *meta))successBlock
errorBlock:(void (^)(NSError *err))errorBlock;

/**
* Copy an asset to a Creative Cloud Design Library.
*
* @param assetID             The asset ID to copy.
* @param communityID         The ID of the community.
* @param libraryID           The design library ID to copy into.
* @param priority            The relative priority of the HTTP request.
* @param queue               If not nil queue determines the operation queue handler gets executed on.
* @param successBlock        Called when the method has successfully finished.
* @param errorBlock          Called when an error has occurred.
*
* @return                    A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)copyAssetID:(NSString *)assetID
communityID:(NSString *)communityID
designLibraryID:(NSString *)libraryID
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
successBlock:(void (^)(NSDictionary *meta))successBlock
errorBlock:(void (^)(NSError *err))errorBlock;

#pragma mark - Comments

/**
* Get comments for an asset.
*
* @param assetID             The asset ID to copy.
* @param communityID         The ID of the community.
* @param cursor              The page cursor to request. Pass in nil for initial page.
* @param size                The maximum number of items to return per page (set 0 to use default, max 50).
* @param priority            The relative priority of the HTTP request.
* @param queue               If not nil queue determines the operation queue handler gets executed on.
* @param successBlock        Called when the method has successfully finished.
* @param errorBlock          Called when an error has occurred.
*
* @return                    A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)commentsForAssetID:(NSString *)assetID
communityID:(NSString *)communityID
cursor:(NSString *)cursor
size:(NSUInteger)size
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
successBlock:(void (^)(NSDictionary *meta, NSString *nextPageHref))successBlock
errorBlock:(void (^)(NSError *err))errorBlock;

/**
* Get comment for an asset.
*
* @param commentID           The comment ID to get.
* @param assetID             The asset ID.
* @param communityID         The ID of the community.
* @param priority            The relative priority of the HTTP request.
* @param queue               If not nil queue determines the operation queue handler gets executed on.
* @param successBlock        Called when the method has successfully finished.
* @param errorBlock          Called when an error has occurred.
*
* @return                    A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)commentID:(NSString *)commentID
assetID:(NSString *)assetID
communityID:(NSString *)communityID
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
successBlock:(void (^)(NSDictionary *meta))successBlock
errorBlock:(void (^)(NSError *err))errorBlock;

/**
* Add comment to an asset.
*
* @param comment             The comment to add.
* @param assetID             The asset ID.
* @param communityID         The ID of the community.
* @param priority            The relative priority of the HTTP request.
* @param queue               If not nil queue determines the operation queue handler gets executed on.
* @param successBlock        Called when the method has successfully finished.
* @param errorBlock          Called when an error has occurred.
*
* @return                    A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)addComment:(NSString *)comment
assetID:(NSString *)assetID
communityID:(NSString *)communityID
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
successBlock:(void (^)(void))successBlock
errorBlock:(void (^)(NSError *err))errorBlock;

/**
* Remove comment from an asset.
*
* @param commentID           The comment ID to remove.
* @param assetID             The asset ID.
* @param communityID         The ID of the community.
* @param priority            The relative priority of the HTTP request.
* @param queue               If not nil queue determines the operation queue handler gets executed on.
* @param successBlock        Called when the method has successfully finished.
* @param errorBlock          Called when an error has occurred.
*
* @return                    A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)removeCommentID:(NSString *)commentID
assetID:(NSString *)assetID
communityID:(NSString *)communityID
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
successBlock:(void (^)(void))successBlock
errorBlock:(void (^)(NSError *err))errorBlock;

#pragma mark - Report Abuse

/**
* Report abuse on an asset.
*
* @param assetID             The asset ID.
* @param communityID         The ID of the community.
* @param type                The type of abuse.
* @param priority            The relative priority of the HTTP request.
* @param queue               If not nil queue determines the operation queue handler gets executed on.
* @param successBlock        Called when the method has successfully finished.
* @param errorBlock          Called when an error has occurred.
*
* @return                    A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)reportAbuseOnAssetID:(NSString *)assetID
communityID:(NSString *)communityID
type:(AdobeCommunityAssetAbuseType)type
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
successBlock:(void (^)(void))successBlock
errorBlock:(void (^)(NSError *err))errorBlock;

#pragma mark - Paging

/**
* Get page for an HREF (useful for paged APIs).
*
* @param href                The HREF to fetch.
* @param priority            The relative priority of the HTTP request.
* @param queue               If not nil queue determines the operation queue handler gets executed on.
* @param successBlock        Called when the method has successfully finished.
* @param errorBlock          Called when an error has occurred.
*
* @return                    A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)communityPageForHref:(NSString *)href
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
successBlock:(void (^)(NSDictionary *meta, NSString *nextPageHref))successBlock
errorBlock:(void (^)(NSError *err))errorBlock;

#pragma mark - Avatars

/**
* Get the avatar for the creator.
*
* @param avatarLinkString    The link for the avatar.
* @param priority            The relative priority of the HTTP request.
* @param queue               If not nil queue determines the operation queue handler gets executed on.
* @param successBlock        Called when the method has successfully finished.
* @param errorBlock          Called when an error has occurred.
*
* @return                    A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)avatarForCreatorHref:(NSString *)avatarLinkString
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
successBlock:(void (^)(NSData *data))successBlock
errorBlock:(void (^)(NSError *err))errorBlock;

@end

#endif
