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

#ifndef AdobeAssetLibraryPrivateHeader
#define AdobeAssetLibraryPrivateHeader

#import <AdobeCreativeSDKAssetModelOSX/AdobeAssetLibrary.h>

@interface AdobeAssetLibrary ()

@property (strong, nonatomic, readwrite) NSString *libraryID;

@property (strong, nonatomic, readwrite) NSMutableDictionary *threeDElements;
@property (strong, nonatomic, readwrite) NSMutableDictionary *brushes;
@property (strong, nonatomic, readwrite) NSMutableDictionary *characterStyles;
@property (strong, nonatomic, readwrite) NSMutableDictionary *colors;
@property (strong, nonatomic, readwrite) NSMutableDictionary *colorThemes;
@property (strong, nonatomic, readwrite) NSMutableDictionary *images;
@property (strong, nonatomic, readwrite) NSMutableDictionary *layerStyles;
@property (strong, nonatomic, readwrite) NSMutableDictionary *looks;
@property (strong, nonatomic, readwrite) NSMutableDictionary *patterns;
@property (strong, nonatomic, readwrite) NSMutableDictionary *videos;

@property (assign, nonatomic, readonly) NSUInteger count;

@end

#endif
