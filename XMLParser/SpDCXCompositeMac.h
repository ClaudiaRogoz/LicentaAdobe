/*************************************************************************
 *
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
 * suppliers and are protected by trade secret or copyright law.
 * Dissemination of this information or reproduction of this material
 * is strictly forbidden unless prior written permission is obtained
 * from Adobe Systems Incorporated.
 **************************************************************************/


#import <AdobeCreativeSDKCoreOSX/AdobeCreativeSDKCoreOSX.h>
#import <AdobeCreativeSDKCoreOSX-Internal/AdobeCreativeSDKCoreOSX-Internal.h>
#import <AdobeCreativeSDKAssetModelOSX/AdobeCreativeSDKAssetModelOSX.h>
#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeCreativeSDKAssetModelOSX-Internal.h>

#import <Foundation/Foundation.h>

@class AdobeNetworkHTTPService;
@class AdobeStorageSession;


struct ArtboardParams {
    const char* name;
    float x;
    float y;
    float width;
    float height;
    float viewportWidth;
    float viewportHeight;
};

struct ComponentParams {
    bool isAGCComponent;
    const char* componentPath;
    const char* type;
    const char* rel;
};

/**
 * Implementation of SpDCXComposite for Mac. Wraps an Objective-C DCX composite object.
 */
@interface SpDCXCompositeMac : NSObject
{

    AdobeDCXComposite* m_composite;


};

- (int) addArtboardNode:(const char*) artboardId params:(struct ArtboardParams) params;
- (int) addArtboardComponent:(const char*) artboardId path: (const char*) filePath params:( struct ComponentParams) params;
- (AdobeDCXNode*) getArtboardNode:(const char*) nodePath;

@end;