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

/**
* The set of header files needed to work with digital composites.
*/

// Error Domains
#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeDCXError.h>

#import <AdobeCreativeSDKAssetModelOSX/AdobeAssetError.h>

// DCX DOM
#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeDCXComponent.h>
#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeDCXComposite.h>
#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeDCXCompositeBranch.h>
#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeDCXCompositeBranch_Deprecated.h>
#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeDCXCompositeMutableBranch.h>
#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeDCXCompositeMutableBranch_Deprecated.h>
#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeDCXComposite_Deprecated.h>
#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeDCXElement.h>
#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeDCXManifestNode.h>
#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeDCXNode.h>
#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeDCXMutableComponent.h>
#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeDCXMutableManifestNode.h>
#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeDCXSyncSessionProtocol.h>
#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeDCXTransferSessionProtocol.h>

// DCX Logic
#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeDCXCompositeXfer.h>
#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeDCXConstants.h>
#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeDCXController.h>
#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeDCXSyncGroupMonitor.h>

// Resources
#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeStorageResource.h>
#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeStorageResourceCollection.h>
#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeStorageResourceItem.h>

// Service
#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeStorageSession.h>
#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeStorageSession+Assets.h>
#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeStorageSession+DCX.h>
