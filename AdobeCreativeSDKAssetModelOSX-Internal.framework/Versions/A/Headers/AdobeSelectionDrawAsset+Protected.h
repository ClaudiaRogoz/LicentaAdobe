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

#ifndef AdobeSelectionDrawAssetProtectedHeader
#define AdobeSelectionDrawAssetProtectedHeader

#import <AdobeCreativeSDKAssetModelOSX/AdobeSelectionDrawAsset.h>

@class AdobeAssetDrawFile;

@interface AdobeSelectionDrawAsset (Protected)

- (instancetype)initWithDrawFile:(AdobeAssetDrawFile *)file pageIndex:(NSInteger)pageIndex;

@end

#endif
