/*************************************************************************
*
* ADOBE CONFIDENTIAL
* ___________________
*
*  Copyright 2013 Adobe Systems Incorporated
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

#ifndef AdobeStorageResourceCollectionHeader
#define AdobeStorageResourceCollectionHeader

#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeStorageResourceItem.h>

/**
*
* AdobeStorageOrderRelation is an enumerated type that specifies the collection
* ordering direction.
*
* See AdobeStorageResourceCollection
*
*/
typedef NS_ENUM (NSInteger, AdobeStorageOrderRelation)
{
/** order current collection in ascending order based on order type */
AdobeStorageOrderAscending,

/** order current collection in descending order based on order type */
AdobeStorageOrderDescending
};

/**
*
* AdobeStorageOrderByProperty is an enumerated type that specifies the resource field
* key to sort on.
*
* See AdobeStorageResourceCollection
*
*/
typedef NS_ENUM (NSInteger, AdobeStorageOrderByProperty)
{
/** order current collection by name */
AdobeStorageOrderByName,

/** order current collection by modification date */
AdobeStorageOrderByModified
};

/**
*
* AdobeStoragePagingMode is an enumerated type that specifies the page mode of the
* Resource Collection.
*
* See AdobeStorageResourceCollection
*
*/
typedef NS_ENUM (NSInteger, AdobeStoragePagingMode)
{
/** replace current collection contents with first page of resource */
AdobeStorageFirstPage,

/** append next page of resource to current collection contents */
AdobeStorageNextPageAppend,

/** replace current collection contents with next page of resource */
AdobeStorageNextPageReplace
};


/**
* class AdobeStorageResourceCollection
* brief Represents a resource that contains other resources.
*/
@interface AdobeStorageResourceCollection : AdobeStorageResource<NSCopying>

/**
* brief Creates a collection with the given href.
*
* param href The href of the resource, i.e. its path relaitve to the service URL.
*
* return The new collection resource.
*/
+ (id)collectionFromHref:(NSString *)href;

/**
* brief Resets the internal directory paging index.  Readies the object
*  to retrieve a directory starting from the first page of items.
*/
- (void)resetPageIndex;

/** The items in the collection. Can be nil if the items have not yet been fetched from the server. */
@property (readonly) NSArray *children;

/** Returns NO if the collection has been populated but subsequent pages exist to be retrieved from the server. */
@property (readonly, getter = isComplete) BOOL complete;

/** The child item limit "hint" provided to the storage service (which may not be strictly adhered to). */
@property (nonatomic) NSUInteger limit;

/** The type of ordering relation (ascending vs. descending) to request when retrieving the collection listing
*  from the service. */
@property (nonatomic) AdobeStorageOrderRelation order;

/** Filter out non renderable items */
@property (nonatomic) BOOL renderableOnly;

/** The property used to order the collection listing requested from the storage service. */
@property (nonatomic) AdobeStorageOrderByProperty orderBy;

/** The content type used to filter the collection listing requested from the storage service. */
@property (nonatomic) NSString *filterByType;

@end

#endif
