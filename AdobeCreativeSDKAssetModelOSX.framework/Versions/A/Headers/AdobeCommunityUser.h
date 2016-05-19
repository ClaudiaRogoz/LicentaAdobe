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

#ifndef AdobeCommunityUserHeader
#define AdobeCommunityUserHeader

#import <Foundation/Foundation.h>

#ifndef DMALIB
#import <UIKit/UIKit.h>
#endif

@class UIImage;
@class AdobeCommunityAsyncRequest;

typedef NSArray AdobeCommunityUsers;

/**
 * AdobeCommunityUserFilterType represents the types of user metadata to filter on.
 */
typedef NS_ENUM (NSInteger, AdobeCommunityUserFilterType)
{
    /** All metadata */
    AdobeCommunityUserFilterTypeAll = 0,

    /** Only show assets */
    AdobeCommunityUserFilterTypeAssets,

    /** Only show likes */
    AdobeCommunityUserFilterTypeLikes,

    /** Only show purchase */
    AdobeCommunityUserFilterTypePurchases,

    /** Only show recommended */
    AdobeCommunityUserFilterTypeRecommended
};

/**
 * AdobeCommunityUserAvatarSize represents the size of the avatar for an AdobeMarket asset creator.
 */
typedef NS_ENUM (NSInteger, AdobeCommunityUserAvatarSize)
{
    /** Small */
    AdobeCommunityUserAvatarSizeSmall  = 0,

    /** Medium */
    AdobeCommunityUserAvatarSizeMedium,

    /** Large */
    AdobeCommunityUserAvatarSizeLarge,
};

/**
 * AdobeCommunityUser represents a user in the AdobeCommunity. It provides accessors for determining
 * the properties of the user as well as the ability to enumerate the assets in the Adobe Community
 * and for retrieving the user's avatar as a UIImage.
 */
@interface AdobeCommunityUser : NSObject <NSCopying, NSCoding>

/**
 * Dimensions of the avatar image.
 */
@property (nonatomic, readonly, assign) CGSize avatarSize;

/**
 * Array of images for the avatar the user.
 */
@property (nonatomic, readonly, strong) NSArray *images;

/**
 * Unique Id for the user.
 */
@property (nonatomic, readonly, copy) NSString *userID;

/**
 * User name for the user.
 */
@property (nonatomic, readonly, copy) NSString *userName;

/**
 * Display name for the user.
 */
@property (nonatomic, readonly, copy) NSString *displayName;

/**
 * First name of the user.
 */
@property (nonatomic, readonly, copy) NSString *firstName;

/**
 * Last name of the user.
 */
@property (nonatomic, readonly, copy) NSString *lastName;

/**
 * City location of the user.
 */
@property (nonatomic, readonly, copy) NSString *city;

/**
 * State location of the user.
 */
@property (nonatomic, readonly, copy) NSString *state;

/**
 * Country location of the user.
 */
@property (nonatomic, readonly, copy) NSString *country;

/**
 * Behance profile.
 */
@property (nonatomic, readonly, copy) NSString *behanceProfile;

/**
 * Refresh the user data.
 *
 * @param successBlock      Get the metadata.
 * @param cancellationBlock Code block run when the process is cancelled.
 * @param errorBlock        Optionally be notified of an error.
 */
- (AdobeCommunityAsyncRequest *)refresh:(void (^)(AdobeCommunityUser *user))successBlock
                      cancellationBlock:(void (^)(void))cancellationBlock
                             errorBlock:(void (^)(NSError *error))errorBlock;

#ifndef DMALIB
/**
 * Get the user's avatar.
 *
 * @param size              The size of the avatar to return.
 * @param progressBlock     Code block passed the current fraction completed for creating the avatar.
 * @param successBlock      Get the rendition data, and notified if returned from local cache.
 * @param cancellationBlock Code block run when the process is cancelled.
 * @param errorBlock        Optionally be notified of an error.
 */
- (AdobeCommunityAsyncRequest *)avatarImageForSize:(AdobeCommunityUserAvatarSize)size
                                     progressBlock:(void (^)(double fractionCompleted))progressBlock
                                      successBlock:(void (^)(UIImage *image, BOOL fromCache))successBlock
                                 cancellationBlock:(void (^)(void))cancellationBlock
                                        errorBlock:(void (^)(NSError *error))errorBlock;
#endif

/**
 * Get an array of all AdobeCommunityAsset objects created by the user asynchronously.
 *
 * @param pageHref          The page of assets to retrieve. Pass nil for the first page.
 * @param size              The number of assets per page.
 * @param priority          The priority of the request.
 * @param successBlock      Get an array of AdobeCommunityAsset objects and a possible next page.
 * @param errorBlock        Optionally be notified of an error.
 */
- (void)assetsForPage:(NSString *)pageHref
                 size:(NSUInteger)size
             priority:(NSOperationQueuePriority)priority
         successBlock:(void (^)(NSArray *assets, NSString *nextPageHref))successBlock
           errorBlock:(void (^)(NSError *error))errorBlock;

@end

#endif
