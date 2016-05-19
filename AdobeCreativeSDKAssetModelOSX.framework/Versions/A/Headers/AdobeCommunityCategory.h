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

#ifndef AdobeCommunityCategoryHeader
#define AdobeCommunityCategoryHeader

#import <Foundation/Foundation.h>

typedef NSArray AdobeCommunityCategories;

/**
 * AdobeCommunityCategory represents a category in the Adobe Community. It provides methods that allow
 * the client to obtain information about the category and to enumerate the categories available in
 * the Creative Cloud Community.
 */
@interface AdobeCommunityCategory : NSObject <NSCopying, NSCoding>

/**
 * Unique ID of the category.
 */
@property (nonatomic, readonly, copy) NSString *categoryID;

/**
 * The category name.
 */
@property (nonatomic, readonly, copy) NSString *name;

/**
 * A English name for the category. This value can be displayed to the end user.
 */
@property (nonatomic, readonly, copy) NSString *englishName;

/**
 * Whether the reciever has any subcategories. If so, @c subCategories can be used to get those
 * subcategories.
 */
@property (readonly, nonatomic) BOOL hasSubCategories;

/**
 * List of subcategories. Each subcategory is an instance of AdobeCommunityCategory.
 */
@property (readonly, nonatomic) NSArray *subCategories;

/**
 * Fetch all the available categories from the server asynchronously.
 *
 * @param communityID       The ID of the community.
 * @param priority          The priority of the network request.
 * @param successBlock      Block to execute when the categories have been retrieved. An NSArray of
 *                          AdobeCommunityCategory objects will be passed to that block.
 * @param errorBlock        Block to execute if an error occurs. Specify @c NULL to omit.
 */
+ (void)categoriesForCommunityID:(NSString *)communityID
                        priority:(NSOperationQueuePriority)priority
                    successBlock:(void (^)(NSArray *categories))successBlock
                      errorBlock:(void (^)(NSError *error))errorBlock;

@end

#endif
