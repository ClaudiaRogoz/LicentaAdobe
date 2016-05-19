/*************************************************************************
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
* suppliers and are protected by all applicable intellectual property
* laws, including trade secret and copyright laws.
* Dissemination of this information or reproduction of this material
* is strictly forbidden unless prior written permission is obtained
* from Adobe Systems Incorporated.
**************************************************************************/

#ifndef AdobeAssetBrowserViewDSHeader
#define AdobeAssetBrowserViewDSHeader

#import <Foundation/Foundation.h>

@class AdobeAssetMIMETypeFilter;
@class AdobeCommonAssetViewAdapter;

@protocol AdobeAssetBrowserViewDataSource <NSObject>

/**
* Return the total number of assets available for the paging view.
*/
- (NSUInteger)numberOfAssetsInAssetBrowserView;

/**
* Retrieve the asset's view adapter. The adapter wraps the asset to provide
* a consistent interface for all asset types.
*/
- (AdobeCommonAssetViewAdapter *)assetAdapterForItemAtIndex:(NSInteger)index;

/**
* Loads the next page of data from the data source.
*/
- (BOOL)loadNextPage;

@optional

/**
* The mime type filter for the assets. This is needed for enabling/disabling
* the open button.
*/
@property (nonatomic, strong) AdobeAssetMIMETypeFilter *mimeTypeFilter;

@end

#endif
