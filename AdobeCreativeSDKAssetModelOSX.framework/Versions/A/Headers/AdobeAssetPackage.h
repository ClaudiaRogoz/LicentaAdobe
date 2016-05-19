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

#ifndef AdobeAssetPackageHeader
#define AdobeAssetPackageHeader

#import <AdobeCreativeSDKAssetModelOSX/AdobeAssetFolder.h>

@class AdobeAssetAsyncRequest;
@class AdobeDCXComponent;

/**
 * AdobeAssetPackage represents a package and provides access to data about the package (manifest, renditions, etc).
 */

/**
 * A utility to help determine if an AdobeAsset is an AdobeAssetPackage.
 */
#define IsAdobeAssetPackage(item) ([item isKindOfClass:[AdobeAssetPackage class]])

/**
 * AdobeAssetPackage represents a package in the Creative Cloud and provides access to its contents.
 */
@interface AdobeAssetPackage : AdobeAssetFolder <NSCopying, NSCoding>

/**
 * Returns true if the metadata is loaded.
 */
@property (nonatomic, readonly, assign, getter = isMetadataLoaded) BOOL metadataLoaded;

/**
 * DEPRECATED
 * Load package metadata.
 *
 * @param successBlock Code to run on succession metadata load.
 * @param errorBlock Code to run on error.
 */
- (void)loadMetadata:(void (^)(void))successBlock
             onError:(void (^)(NSError *err))errorBlock __deprecated_msg("Use loadMetadata:cancellationBlock:errorBlock");

/**
 * Load package metadata.
 *
 * @param successBlock         Code to run on succession metadata load.
 * @param cancellationBlock    Optionally be notified of a cancellation on upload.
 * @param errorBlock           Code to run on error.
 *
 * @return An @c AdobeAssetAsyncRequest which can be used to control the cancellation of the request.
 */
- (AdobeAssetAsyncRequest *)loadMetadata:(void (^)(void))successBlock
                       cancellationBlock:(void (^)(void))cancellationBlock
                              errorBlock:(void (^)(NSError *err))errorBlock;

/**
 * DEPRECATED
 * Reloads the package metadata, regardless of whether it has already been loaded.
 *
 * @param successBlock The success block that is invoked when the metedata is successfully loaded.
 * @param errorBlock   Invoked in the case of any errors.
 */
- (void)reloadMetadata:(void (^)(void))successBlock
               onError:(void (^)(NSError *error))errorBlock __deprecated_msg("Use reloadMetadata:cancellationBlock:errorBlock");

/**
 * Reloads the package metadata, regardless of whether it has already been loaded.
 *
 * @param successBlock         The success block that is invoked when the metedata is successfully loaded.
 * @param cancellationBlock    Optionally be notified of a cancellation on upload.
 * @param errorBlock           Invoked in the case of any errors.
 *
 * @return An @c AdobeAssetAsyncRequest which can be used to control the cancellation of the request.
 */
- (AdobeAssetAsyncRequest *)reloadMetadata:(void (^)(void))successBlock
                         cancellationBlock:(void (^)(void))cancellationBlock
                                errorBlock:(void (^)(NSError *error))errorBlock;

/**
 * A utility to test the equlity of two AdobeAssetPackage instances.
 *
 * @param package the AdobeAssetPackage to test against.
 */
- (BOOL)isEqualToPackage:(AdobeAssetPackage *)package;

@end

#endif /* ifndef AdobeAssetPackageHeader */
