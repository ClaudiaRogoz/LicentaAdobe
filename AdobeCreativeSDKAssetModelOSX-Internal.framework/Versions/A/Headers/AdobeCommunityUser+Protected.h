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

#ifndef AdobeCommunityUserProtectedHeader
#define AdobeCommunityUserProtectedHeader

@class AdobeCloud;

@interface AdobeCommunityUser (Protected)

- (instancetype)initWithData:(NSDictionary *)data
communityID:(NSString *)communityID
cloud:(AdobeCloud *)cloud;

- (void)updateWithData:(NSDictionary *)data;

/**
* Get assets in a community objects asynchronously.
*
* @param pageHref          The href for the page of assets. Pass nil for the initial page.
* @param size              The number of items per page.
* @param priority          The priority of the request.
* @param assetClass        The class type to be returned. The class must be (or extend) AdobeCommunityAsset.
*                          Pass nil to specify AdobeCommunityAsset.
* @param successBlock      Returns an array of AdobeCommunityAssets and the next page href (nil for last page).
* @param errorBlock        Optionally be notified of an error.
*/
- (void)assetsForPage:(NSString *)pageHref
size:(NSUInteger)size
priority:(NSOperationQueuePriority)priority
class:(Class)assetClass
successBlock:(void (^)(NSArray *assets, NSString *nextPageHref))successBlock
errorBlock:(void (^)(NSError *))errorBlock;

@end

#endif
