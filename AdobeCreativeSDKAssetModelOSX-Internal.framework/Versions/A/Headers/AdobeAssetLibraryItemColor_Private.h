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

#ifndef AdobeAssetLibraryItemColorPrivateHeader
#define AdobeAssetLibraryItemColorPrivateHeader

#import <AdobeCreativeSDKAssetModelOSX/AdobeAssetLibraryItemColor.h>
#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeAssetLibraryItem_Private.h>
#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeDCXManifestNode.h>

@interface AdobeAssetLibraryItemColor ()

@property (readwrite, nonatomic, assign) AdobeAssetLibraryColorType colorType;
@property (readwrite, nonatomic, assign) AdobeAssetLibraryColorMode colorMode;
@property (readwrite, nonatomic, strong) NSObject *colorComponents;
@property (readwrite, nonatomic, assign) NSNumber *colorAlpha;
@property (readwrite, nonatomic, strong) NSString *colorProfileName;
@property (readwrite, nonatomic, assign) AdobeAssetLibraryColorType renditionType;
@property (readwrite, nonatomic, assign) AdobeAssetLibraryColorMode renditionMode;
@property (readwrite, nonatomic, strong) NSObject *renditionComponents;
@property (readwrite, nonatomic, assign) NSNumber *renditionAlpha;
@property (readwrite, nonatomic, strong) NSString *renditionProfileName;

- (id)          initWithNode:(AdobeDCXManifestNode *)node
withRenditionName:(NSString *)renditionName
withColorType:(NSString *)colorType
withColorMode:(NSString *)colorMode
withColorComponents:(NSObject *)colorComponents
withColorAlpha:(NSNumber *)colorAlpha
withColorProfileName:(NSString *)colorProfileName
withRenditionType:(NSString *)renditionType
withRenditionMode:(NSString *)renditionMode
withRenditionComponents:(NSObject *)renditionComponents
withRenditionAlpha:(NSNumber *)renditionAlpha
withRenditionProfileName:(NSString *)renditionProfileName
inLibrary:(AdobeAssetLibrary *)library;

@end

#endif
