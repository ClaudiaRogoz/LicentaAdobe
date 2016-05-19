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

#ifndef AdobeAssetFilePrivateHeader
#define AdobeAssetFilePrivateHeader

#import <AdobeCreativeSDKAssetModelOSX/AdobeAssetFile.h>

#import <AdobeCreativeSDKAssetModelOSX/AdobeAsset.h>
#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeAsset_Private.h>

@class AdobeAssetAsyncRequest;
@class AdobeStorageResourceItem;

@interface AdobeAssetFile ()

@property (readwrite, nonatomic, strong) AdobeStorageResourceItem *asrItem;
@property (readwrite, nonatomic, strong) NSString *hlsHref;
@property (readwrite, nonatomic, strong) NSString *md5Hash;
@property (readwrite, nonatomic, strong) NSDictionary *optionalMetadata;
@property (readwrite, nonatomic, assign) long long fileSize;
@property (readwrite, nonatomic, assign) NSUInteger currentVersion;
@property (readwrite, nonatomic, assign) BOOL renderable;
@property (nonatomic, readwrite, strong) AdobeAssetAsyncRequest *createAssetAsyncRequest;
@property (nonatomic, readwrite, strong) NSMutableDictionary *progressBlocks;
@property (nonatomic, readwrite, strong) NSMutableDictionary *networkRequests;

/**
* We now calculate the scaled size of the thumbnail that needs to be displayed in the grid view
* cells. This is to avoid showing any whitespace around awkwardly-sized images. We need to know
* this dimension in the one-up view so we can grab a similarly-sized image from the cache, while
* the full rendition is loading. We store the dimensions of the loaded thumbnail from either list
* or grid view here.
*/
@property (nonatomic, assign) CGSize thumbnailDimensions;

@end

#endif /* ifndef AdobeAssetFilePrivateHeader */
