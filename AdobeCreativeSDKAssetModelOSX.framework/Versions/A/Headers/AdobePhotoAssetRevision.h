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

#ifndef AdobePhotoAssetRevHeader
#define AdobePhotoAssetRevHeader

/**
 * An asset revision.
 */
@interface AdobePhotoAssetRevision : NSObject <NSCopying, NSCoding>

/**
 * The asset revision id.
 */
@property (nonatomic, readonly, strong) NSString *GUID;

/**
 * Create a new revision.
 * @returns a new AdobePhotoAssetRevision
 */
+ (instancetype)create;

/**
 * Create a new revision.
 * @param GUID The GUID of the revision data.
 *
 * @returns a new AdobePhotoAssetRevision
 */
- (instancetype)initWithGUID:(NSString *)guid;

/**
 * Create a new revision.
 * @param href The href of the revision data.
 *
 * @returns a new AdobePhotoAssetRevision
 */
- (instancetype)initWithHref:(NSString *)href;

/**
 * A utility to test the equlity of two AdobePhotoAssetRevisions.
 *
 * @param revision The AdobePhotoAssetRevision to test against.
 *
 * @returns True if the revisions are the same.
 */
- (BOOL)isEqualToRevision:(AdobePhotoAssetRevision *)revision;

@end

#endif /* ifndef AdobePhotoAssetRevHeader */
