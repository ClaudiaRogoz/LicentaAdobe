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

#ifndef AdobePSDLayerCompHeader
#define AdobePSDLayerCompHeader

#import <AdobeCreativeSDKAssetModelOSX/AdobePSDLayerNode.h>

/**
 * AdobePSDLayerComp presents the core interface to a composition of layers. It determines which layers are visible.
 */
@interface AdobePSDLayerComp : NSObject <NSMutableCopying>

/**
 * The name of the layer comp ID.
 */
@property (readonly, nonatomic) NSNumber *compId;

/**
 * IDs for all the layers that are part of the receiver.
 */
@property (readonly, nonatomic) NSArray *layerIds;

/**
 * The name of the layer comp.
 */
@property (readonly, nonatomic) NSString *name;

/**
 * Checks whether this layer comp includes the specified layer.
 * @param layer Layer being checked.
 */
- (BOOL)hasLayer:(AdobePSDLayerNode *)layer;

/**
 * Checks whether this layer comp includes the layer with the specified ID.
 * @param layerId ID of the field being checked.
 */
- (BOOL)hasLayerId:(NSNumber *)layerId;

@end

#endif
