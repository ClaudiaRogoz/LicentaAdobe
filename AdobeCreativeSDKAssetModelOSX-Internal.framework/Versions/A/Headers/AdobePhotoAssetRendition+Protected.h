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

#ifndef AdobePhotoAssetRenditionProtectedHeader
#define AdobePhotoAssetRenditionProtectedHeader

#import <AdobeCreativeSDKAssetModelOSX/AdobePhotoAssetRevision.h>

@interface AdobePhotoAssetRendition (Protected)

- (id)initWithGUID:(NSString *)GUID
withRevision:(AdobePhotoAssetRevision *)revision
withType:(AdobePhotoAssetRenditionType)type __deprecated_msg("Use initWithGUID:revision:type");

- (instancetype)initWithGUID:(NSString *)guid
revision:(AdobePhotoAssetRevision *)revision
type:(AdobePhotoAssetRenditionType)type;

- (id)initWithHref:(NSString *)href
withType:(AdobePhotoAssetRenditionType)type __deprecated_msg("Use initWithHref:type");

- (instancetype)initWithHref:(NSString *)href
type:(AdobePhotoAssetRenditionType)type;

@end

#endif /* ifndef AdobePhotoAssetRenditionProtectedHeader */
