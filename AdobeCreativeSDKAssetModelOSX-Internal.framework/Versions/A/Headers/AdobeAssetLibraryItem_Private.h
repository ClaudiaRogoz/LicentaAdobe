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

#ifndef AdobeAssetLibraryItemPrivateHeader
#define AdobeAssetLibraryItemPrivateHeader

#import <AdobeCreativeSDKAssetModelOSX/AdobeAssetLibraryItem.h>

@class AdobeDCXManifestNode;

@interface AdobeAssetLibraryItem ()

@property (strong, nonatomic, readwrite) NSString *name;
@property (strong, nonatomic, readwrite) NSString *renditionName;
@property (strong, nonatomic, readwrite) NSString *itemID;
@property (assign, nonatomic, readwrite) BOOL hasExternalLinks;
@property (strong, nonatomic, readwrite) NSDate *creationDate;
@property (strong, nonatomic, readwrite) NSDate *modificationDate;
@property (weak, nonatomic, readwrite) AdobeAssetLibrary *library;

/**
* Stores the actual node object. This property is internal only.
*/
@property (copy, nonatomic) AdobeDCXManifestNode *node;

- (instancetype)initWithNode:(AdobeDCXManifestNode *)name
withRenditionName:(NSString *)renditionName
inLibrary:(AdobeAssetLibrary *)library;

- (NSString *)nameOrIdForDisplay;

@end

#endif
