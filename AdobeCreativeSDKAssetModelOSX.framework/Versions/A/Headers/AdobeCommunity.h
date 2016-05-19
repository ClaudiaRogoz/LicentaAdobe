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

#ifndef AdobeCommunityHeader
#define AdobeCommunityHeader

#import <Foundation/Foundation.h>

#import <AdobeCreativeSDKAssetModelOSX/AdobeCommunityCategory.h>

/**
 * AdobeCommunity represents a Creative Cloud Community. It provides accessors that
 * allow the client to obtain information and manage the commnuity.
 */
@interface AdobeCommunity : NSObject

/**
 * Unique identifier for the community.
 */
@property (nonatomic, readonly, strong) NSString *communityID;

/**
 * Creative Cloud Market
 */
+ (AdobeCommunity *)market;

/**
 * Initialize a community object.
 *
 * @param communityID       Initialize AdobeCommunity object with this ID.
 */
- (instancetype)initWithCommunityID:(NSString *)communityID;

/**
 * Get the history of the category from the server asynchronously.
 *
 * @param priority          The priority of the network request.
 * @param successBlock      Block to execute when the categories have been retrieved. An NSArray of
 *                          AdobeCommunityCategory objects will be passed to that block.
 * @param errorBlock        Block to execute if an error occurs. Specify @c NULL to omit.
 */
- (void)categoriesWithRequestPriority:(NSOperationQueuePriority)priority
                         successBlock:(void (^)(AdobeCommunityCategories *categories))successBlock
                           errorBlock:(void (^)(NSError *))errorBlock;

@end

#endif
