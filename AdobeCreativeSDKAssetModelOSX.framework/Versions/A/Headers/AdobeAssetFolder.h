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

#ifndef AdobeAssetFolderHeader
#define AdobeAssetFolderHeader

#import <AdobeCreativeSDKAssetModelOSX/AdobeAsset.h>

@class AdobeAssetAsyncRequest;

/**
 * Folder items are fetched from the cloud in pages, so the field on which the items
 * should be sorted as well as the sort direction must be specified when setting up
 * this instance. If you need to change the sorting, you will need to create a new
 * instance with the specified sort options.
 *
 * Once you have an AdobeAssetFolder instance set up, you can call hasNextPage and
 * loadNextPage to start loading folder items from the cloud as needed.
 */

/**
 * A utility to help determine if an AdobeAsset is an AdobeAssetFolder.
 */
#define IsAdobeAssetFolder(item) ([item isKindOfClass:[AdobeAssetFolder class]])

/**
 * AdobeAssetFolderOrderBy is an enumerated type that specifies the field key to
 * sort on.
 */
typedef NS_ENUM (NSInteger, AdobeAssetFolderOrderBy)
{
    /** Order folder items by name. */
    AdobeAssetFolderOrderByName,

    /** Order folder items by date modified. */
    AdobeAssetFolderOrderByModified,
};

/**
 * AdobeAssetFolderOrderDirection is an enumerated type that specifies the ordering
 * direction.
 */
typedef NS_ENUM (NSInteger, AdobeAssetFolderOrderDirection)
{
    /** Order folder items in ascending order based on order type. */
    AdobeAssetFolderOrderAscending,

    /** Order folder items in descending order based on order type. */
    AdobeAssetFolderOrderDescending,
};

@interface AdobeAssetFolderConfiguration : NSObject

/**
 * Sets the field to order the folder contents by.
 */
@property (nonatomic) AdobeAssetFolderOrderBy orderBy;

/**
 * Sets the order direction ascending or decending
 */
@property (nonatomic) AdobeAssetFolderOrderDirection orderDirection;

/**
 * Filters the non renderable assets, such as zip and other file formats that dont
 * have a drawable representation.
 */
@property (nonatomic) BOOL renderableOnly;

@end

/**
 *
 * AdobeAssetFolder represents a folder in the Creative Cloud and provides access to folder contents
 * in pages of data as well as provisions for creating and deleting folders.
 *
 */
@interface AdobeAssetFolder : AdobeAsset <NSCopying, NSCoding>

/**
 *  Indicates whether a shared folder is read-only. If a folder is read-only, it may only be modified by the owner.
 */
@property (nonatomic, readonly, getter = isReadOnly) BOOL readOnly;

/**
 * DEPRECATED
 * Get the root folder of the logged in user sorted by default (name, ascending).
 *
 * @returns the folder.
 */
+ (AdobeAssetFolder *)getRoot __deprecated_msg("Use root");

/**
 * Get the root folder of the logged in user sorted by default (name, ascending).
 *
 * @returns the folder.
 */
+ (AdobeAssetFolder *)root;

/**
 * DEPRECATED
 * Get the root folder of the logged in user.
 *
 * @param field The field on which the items in the folder will be sorted (e.g., name, modification date). See AdobeAssetFolderOrderBy.
 * @param direction The direction (ascending or descending) of the sort. See AdobeAssetFolderOrderDirection.
 * @returns the folder.
 */
+ (AdobeAssetFolder *)getRootOrderedByField:(AdobeAssetFolderOrderBy)field
                             orderDirection:(AdobeAssetFolderOrderDirection)direction __deprecated_msg("Use root:config");

/**
 * DEPRECATED
 * Get the root folder of the logged in user.
 *
 * @param field     The field on which the items in the folder will be sorted (e.g., name, modification date). See AdobeAssetFolderOrderBy.
 * @param direction The direction (ascending or descending) of the sort. See AdobeAssetFolderOrderDirection.
 * @param renderable    Filter assets that are not renderable.
 * @returns the folder.
 */
+ (AdobeAssetFolder *)rootOrderedByField:(AdobeAssetFolderOrderBy)field
                          orderDirection:(AdobeAssetFolderOrderDirection)direction __deprecated_msg("Use root:config");


/**
 * Get the root folder of the logged in user.
 *
 * @param field     The field on which the items in the folder will be sorted (e.g., name, modification date). See AdobeAssetFolderOrderBy.
 * @param config    Settings for how the folder contents will be displayed see AdobeAssetFolderConfiguration
 * @param renderable    Filter assets that are not renderable.
 * @returns the folder.
 */
+ (AdobeAssetFolder *)root:(AdobeAssetFolderConfiguration *)config;


/**
 * DEPRECATED
 * Get an AdobeAssetFolder based on the href using the default sorting (name, ascending).
 *
 * @param href The absolute HREF of the folder
 */
+ (AdobeAssetFolder *)getFolderFromHref:(NSString *)href __deprecated_msg("Use folderFromHref");

/**
 * Get an AdobeAssetFolder based on the href using the default sorting (name, ascending).
 *
 * @param href The absolute HREF of the folder
 */
+ (AdobeAssetFolder *)folderFromHref:(NSString *)href;

/**
 * DEPRECATED
 * Get an AdobeAssetFolder based on the href for the logged in user.
 *
 * Folder items are fetched from the cloud in pages, so the field on which the items
 * should be sorted as well as the sort direction must be specified when setting up
 * this instance. If you need to change the sorting, you will need to create a new
 * instance with the specified sort options.
 *
 * Once you have an AdobeAssetFolder instance set up, you can call hasNextPage and
 * loadNextPage to start loading folder items from the cloud as needed.
 *
 * @param href The absolute HREF of the folder
 * @param field The field on which the items in the folder will be sorted (e.g., name, modification date). See AdobeAssetFolderOrderBy.
 * @param direction The direction (ascending or descending) in the the items will be sorted. See AdobeAssetFolderOrderDirection.
 * @returns the folder.
 */
+ (AdobeAssetFolder *)getFolderFromHref:(NSString *)href
                           orderByField:(AdobeAssetFolderOrderBy)field
                         orderDirection:(AdobeAssetFolderOrderDirection)direction __deprecated_msg("Use folderFromHref:config");

/**
 * Get an AdobeAssetFolder based on the href for the logged in user.
 *
 * Folder items are fetched from the cloud in pages, so the field on which the items
 * should be sorted as well as the sort direction must be specified when setting up
 * this instance. If you need to change the sorting, you will need to create a new
 * instance with the specified sort options.
 *
 * Once you have an AdobeAssetFolder instance set up, you can call hasNextPage and
 * loadNextPage to start loading folder items from the cloud as needed.
 *
 * @param href      The absolute HREF of the folder
 * @param field     The field on which the items in the folder will be sorted (e.g., name, modification date). See AdobeAssetFolderOrderBy.
 * @param direction The direction (ascending or descending) in the the items will be sorted. See AdobeAssetFolderOrderDirection.
 * @returns the folder.
 */
+ (AdobeAssetFolder *)folderFromHref:(NSString *)href
                        orderByField:(AdobeAssetFolderOrderBy)field
                      orderDirection:(AdobeAssetFolderOrderDirection)direction;

/**
 * Get an AdobeAssetFolder based on the href for the logged in user.
 *
 * Folder items are fetched from the cloud in pages, so the field on which the items
 * should be sorted as well as the sort direction must be specified when setting up
 * this instance. If you need to change the sorting, you will need to create a new
 * instance with the specified sort options.
 *
 * Once you have an AdobeAssetFolder instance set up, you can call hasNextPage and
 * loadNextPage to start loading folder items from the cloud as needed.
 *
 * @param href      The absolute HREF of the folder
 * @param config    Set folder configuration parameter as specified in AdobeAssetFolderConfiguration
 * @returns the folder.
 */
+ (AdobeAssetFolder *)folderFromHref:(NSString *)href
                              config:(AdobeAssetFolderConfiguration *)config;

/**
 * DEPRECATED
 * Create a new folder on the Adobe Creative Cloud asynchronously.
 *
 * @param name The name of the folder.
 * @param folder The enclosing folder.
 * @param completionBlock Optionally get an updated reference to the created folder when complete.
 * @param errorBlock Optionally be notified of an error.
 */
+ (void)  create:(NSString *)name
        inFolder:(AdobeAssetFolder *)folder
    onCompletion:(void (^)(AdobeAssetFolder *folder))completionBlock
         onError:(void (^)(NSError *error))errorBlock __deprecated_msg("Use create:parentFolder:successBlock:errorBlock");

/**
 * Create a new folder on the Adobe Creative Cloud asynchronously.
 *
 * @param name          The name of the folder.
 * @param folder        The enclosing folder.
 * @param successBlock  Optionally get an updated reference to the created folder when complete.
 * @param errorBlock    Optionally be notified of an error.
 */
+ (void)  create:(NSString *)name
    parentFolder:(AdobeAssetFolder *)folder
    successBlock:(void (^)(AdobeAssetFolder *folder))successBlock
      errorBlock:(void (^)(NSError *error))errorBlock;

/**
 *  Refreshes the folder's metadata.
 *
 *  @param successBlock         A block that notifies the caller when the refresh operation has succeeded.
 *  @param cancellationBlock    Optionally be notified of a cancellation on upload.
 *  @param errorBlock           An block that informs the caller of any error that may have occurred
 *                              while refreshing.
 *
 * @return An @c AdobeAssetAsyncRequest which can be used to control the cancellation of the request.
 */
- (AdobeAssetAsyncRequest *)refresh:(void (^)(AdobeAssetFolder *folder))successBlock
                  cancellationBlock:(void (^)(void))cancellationBlock
                         errorBlock:(void (^)(NSError *error))errorBlock;

/**
 * DEPRECATED
 * Archive the specified folder asynchronously. It does not permanently delete the folder from the cloud.
 * There is no API to expunge nor restore the folder from the archive as of this time.
 *
 * @param completionBlock Optionally be notified when complete.
 * @param errorBlock Optionally be notified of an error.
 */
- (void)archive:(void (^)(void))completionBlock
        onError:(void (^)(NSError *error))errorBlock __deprecated_msg("Use archive:errorBlock");

/**
 * Archive the specified folder asynchronously. It does not permanently delete the folder from the cloud.
 * There is no API to expunge nor restore the folder from the archive as of this time.
 *
 * @param successBlock  Optionally be notified when complete.
 * @param errorBlock    Optionally be notified of an error.
 */
- (void)archive:(void (^)(void))successBlock
     errorBlock:(void (^)(NSError *error))errorBlock;

/**
 * Indicates whether the cloud folder has another page of items that can be loaded.
 *
 * @returns true if the another page of items can be loaded; false otherwise.
 */
- (BOOL)hasNextPage;

/**
 * DEPRECATED
 * Asynchronously gets the next page of items from the cloud folder. This should
 * only be called if hasNextPage returns true. Behavior is undefined if hasNextPage
 * returned false;
 *
 * @param pageSize The number of items to be fetched. This is just a hint. The actual number fetched may be more or less than this amount.
 * @param completionBlock An NSArray of AdobeAssets, and total number of items retrieved.
 * @param errorBlock Optionally be notified of an error.
 */
- (void)getNextPage:(NSUInteger)pageSize
       onCompletion:(void (^)(AdobeAssetArray *items, NSUInteger totalItemsInFolder))completionBlock
            onError:(void (^)(NSError *error))errorBlock __deprecated_msg("Use nextPage:successBlock:errorBlock");

/**
 * Asynchronously gets the next page of items from the cloud folder. This should
 * only be called if hasNextPage returns true. Behavior is undefined if hasNextPage
 * returned false;
 *
 * @param pageSize      The number of items to be fetched. This is just a hint. The actual number fetched may be more or less than this amount.
 * @param successBlock  An NSArray of AdobeAssets, and total number of items retrieved.
 * @param errorBlock    Optionally be notified of an error.
 */
- (void)nextPage:(NSUInteger)pageSize
    successBlock:(void (^)(AdobeAssetArray *items, NSUInteger totalItemsInFolder))successBlock
      errorBlock:(void (^)(NSError *error))errorBlock;

/**
 * Resets the page iterator so that any subsequent call to hasNextPage will return
 * true, and getNextPage will return the first page of cloud items. Keeps the current
 * sorting options in effect.
 */
- (void)resetPaging;

/**
 * DEPRECATED
 * Resets the page iterator so that any subsequent call to hasNextPage will return
 * true, and getNextPage will return the first page of cloud items. Sets new sorting
 * options for the cloud folder.
 *
 * @param field     The field on which the items in the folder will be sorted (e.g., name, modification date).
 * @param direction The direction (ascending or descending) in the the items will be sorted.
 * @param renderable Filter assets that are not renderable.
 */
- (void)resetPagingOrderedByField:(AdobeAssetFolderOrderBy)field
                   orderDirection:(AdobeAssetFolderOrderDirection)direction __deprecated_msg("resetPaging:config");

/**
 * Resets the page iterator so that any subsequent call to hasNextPage will return
 * true, and getNextPage will return the first page of cloud items. Sets new sorting
 * options for the cloud folder.
 *
 * @param field     The field on which the items in the folder will be sorted (e.g., name, modification date).
 * @param config    Set folder configuration parameter as specified in AdobeAssetFolderConfiguration
 * @param renderable Filter assets that are not renderable.
 */
- (void)resetPaging:(AdobeAssetFolderConfiguration *)config;

/**
 * A utility to test the equlity of two AdobeAssetFolders.
 *
 * @param folder the AdobeAssetFolder to test against.
 */
- (BOOL)isEqualToFolder:(AdobeAssetFolder *)folder;

/**
 * Whether this folder is a shared folder.
 */
- (BOOL)isShared;

@end

#endif /* ifndef AdobeAssetFolderHeader */
