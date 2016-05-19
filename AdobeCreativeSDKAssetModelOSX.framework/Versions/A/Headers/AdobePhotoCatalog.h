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

#ifndef AdobePhotoCatalogHeader
#define AdobePhotoCatalogHeader

#import <AdobeCreativeSDKAssetModelOSX/AdobePhoto.h>

#import <AdobeCreativeSDKAssetModelOSX/AdobePhotoTypes.h>

@class AdobePhotoAsset;
@class AdobePhotoCollection;
@class AdobePhotoPage;

/**
 * A utility to help determine if an AdobePhoto is an AdobePhotoCatalog.
 */
#define IsAdobePhotoCatalog(item) ([item isKindOfClass:[AdobePhotoCatalog class]])

typedef NS_ENUM (NSInteger, AdobePhotoCatalogType)
{
    /** Lightroom catalog type */
    AdobePhotoCatalogTypeLightroom,
};

/**
 * AdobePhotoCatalog is the topmost container of assets in a user's library of assets.
 * Each catalog contains zero or more AdobePhotoCollections.
 */
@interface AdobePhotoCatalog : AdobePhoto <NSCopying, NSCoding>

/**
 * The name of the catalog.
 * Note: you will need to call update after setting the name for the changes to appear on the server.
 */
@property (readwrite, nonatomic, strong) NSString *name;

/**
 * Whether this catalog is shared to others.
 */
@property (readonly, nonatomic, assign, getter = isShared) BOOL shared;

/**
 * The type of the catalog.
 * Note: you will need to call update after setting the name for the changes to appear on the server.
 */
@property (readonly, nonatomic, assign) AdobePhotoCatalogType type;

/**
 * List catalog of type on the Adobe Photo service asynchronously.
 *
 * @param type          The type of Photo catalog to list.
 * @param successBlock  Get a list of all AdobePhotoCatalogs for the logged in user if successful.
 * @param errorBlock    Optionally be notified of an error.
 */
+ (void)listOfType:(AdobePhotoCatalogType)type
      onCompletion:(void (^)(AdobePhotoCatalogs *catalogs))successBlock
           onError:(void (^)(NSError *error))errorBlock __deprecated_msg("Use listOfType:successBlock:errorBlock");

+ (void)listOfType:(AdobePhotoCatalogType)type
      successBlock:(void (^)(AdobePhotoCatalogs *catalogs))successBlock
        errorBlock:(void (^)(NSError *error))errorBlock;

/**
 * Update this catalog from the Adobe Photo service asynchronously.
 *
 * @param successBlock  Optionally be notified if successful.
 * @param errorBlock    Optionally be notified of an error.
 */
- (void)update:(void (^)(AdobePhotoCatalog *catalog))successBlock
       onError:(void (^)(NSError *error))errorBlock __deprecated_msg("Use update:errorBlock");

- (void)update:(void (^)(AdobePhotoCatalog *catalog))successBlock
    errorBlock:(void (^)(NSError *error))errorBlock;

/**
 * Refresh this catalog from the Adobe Photo service asynchronously.
 *
 * @param successBlock  Optionally be notified if successful.
 * @param errorBlock    Optionally be notified of an error.
 */
- (void)refresh:(void (^)(AdobePhotoCatalog *catalog))successBlock
        onError:(void (^)(NSError *error))errorBlock __deprecated_msg("Use refresh:errorBlock");

- (void)refresh:(void (^)(AdobePhotoCatalog *catalog))successBlock
     errorBlock:(void (^)(NSError *error))errorBlock;

/**
 * List the assets for this catalog in the Adobe Photo service asynchronously.
 *
 * @param page          The page to pass in, use nil to start from the beginning.
 * @param limit         The number of assets to return. Default value is 100, max is 500. Please note that the response may contain more than 'limit' number of
 *                      assets returned if the assets at the 'limit' boundary has the same capture_date.
 * @param successBlock  Get a list of all AdobePhotoAssets for the logged in user if successful.
 * @param errorBlock    Optionally be notified of an error.
 */
- (void)listAssetsOnPage:(AdobePhotoPage *)page
                   limit:(NSUInteger)limit
            successBlock:(void (^)(AdobePhotoAssets *assets, AdobePhotoPage *previousPage, AdobePhotoPage *nextPage))successBlock
              errorBlock:(void (^)(NSError *error))errorBlock;

/**
 * List the collections in the catalog on the Adobe Photo service asynchronously.
 *
 * @param name          Start the list results after the "name," or nil to start at the beginning of the list.
 * @param limit         Number of collections to return. Default value is 100, max is 500. Note that the response may contain more than 'limit' number of collections
 *                      returned if the collections at the 'limit' boundary has the same name_after.
 * @param deleted       True to include deleted collections in the response.
 * @param successBlock  Get a list of all AdobePhotoCatalogs for the logged in user if successful.
 * @param errorBlock    Optionally be notified of an error.
 */
- (void)listCollectionsAfterName:(NSString *)name
                       withLimit:(NSUInteger)limit
       includeDeletedCollections:(BOOL)deleted
                    onCompletion:(void (^)(AdobePhotoCollections *collections))successBlock
                         onError:(void (^)(NSError *error))errorBlock __deprecated_msg("Use listCollectionsAfterName:limit:includeDeletedCollections:successBlock:errorBlock");

- (void)listCollectionsAfterName:(NSString *)name
                           limit:(NSUInteger)limit
       includeDeletedCollections:(BOOL)deleted
                    successBlock:(void (^)(AdobePhotoCollections *collections))successBlock
                      errorBlock:(void (^)(NSError *error))errorBlock;

/**
 * Get the number of collections in this catalog on the Adobe Photo service asynchronously.
 *
 * @param successBlock  Get the number of AdobePhotoCollections in this catalog if successful.
 * @param errorBlock    Optionally be notified of an error.
 */
- (void)collectionCount:(void (^)(NSUInteger count))successBlock
                onError:(void (^)(NSError *error))errorBlock __deprecated_msg("Use collectionCount:errorBlock");

- (void)collectionCount:(void (^)(NSUInteger count))successBlock
             errorBlock:(void (^)(NSError *error))errorBlock;

/**
 * Get the number of assets in this catalog on the Adobe Photo service asynchronously.
 *
 * @param successBlock  Get the number of AdobePhotoAssets in this catalog if successful.
 * @param errorBlock    Optionally be notified of an error.
 */
- (void)assetCount:(void (^)(NSUInteger count))successBlock
           onError:(void (^)(NSError *error))errorBlock __deprecated_msg("Use assetCount:errorBlock");

- (void)assetCount:(void (^)(NSUInteger count))successBlock
        errorBlock:(void (^)(NSError *error))errorBlock;

/**
 * A utility to test the equlity of two AdobePhotoCatalogs.
 *
 * @param catalog   The AdobePhotoCatalog to test against.
 * @returns True if the same.
 */
- (BOOL)isEqualToCatalog:(AdobePhotoCatalog *)catalog;

@end

#endif /* ifndef AdobePhotoCatalogHeader */
