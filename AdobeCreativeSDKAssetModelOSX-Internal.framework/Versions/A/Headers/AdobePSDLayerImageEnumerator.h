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

#ifndef AdobePSDLayerImageEnumeratorHeader
#define AdobePSDLayerImageEnumeratorHeader

#ifndef DMALIB

#import <Foundation/Foundation.h>

#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobePSDLayerImage.h>

@class AdobePSDCompositeBranch;

@interface AdobePSDLayerImageEnumerator : NSObject

- (AdobePSDLayerImageEnumerator *)initWithPsdPreview:(AdobePSDPreview *)psdPreview
layerId:(NSNumber *)parentLayerId
layerCompId:(NSNumber *)layerCompId
selectionPath:(UIBezierPath *)path
selectUsingFill:(BOOL)selectUsingFill
recursive:(BOOL)recursive;

+ (AdobePSDLayerImageEnumerator *)enumeratorWithPSDPreview:(AdobePSDPreview *)psdPreview
layerId:(NSNumber *)parentLayerId
layerCompId:(NSNumber *)layerCompId
selectionPath:(UIBezierPath *)path
selectUsingFill:(BOOL)selectUsingFill
recursive:(BOOL)recursive;

- (AdobePSDLayerImage *)next;

- (NSArray *)allObjects;

@end

#endif // !DMALIB

#endif
