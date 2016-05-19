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

#ifndef AdobePSDMutableLayerNodeHeader
#define AdobePSDMutableLayerNodeHeader

#import <AdobeCreativeSDKAssetModelOSX/AdobePSDLayerNode.h>

/**
 * This class allows you to create (or edit) the properties for a layer node. Examples would be creating layer groups, RGB pixel layers, etc.
 */
@interface AdobePSDMutableLayerNode : AdobePSDLayerNode

#pragma mark General Layer Properties

// Override selected properties as mutable.

/**
 * The name of the layer node
 */
@property (readwrite, nonatomic) NSString *name;

/**
 * Whether the layer is visible.
 */
@property (readwrite, nonatomic) BOOL visible;

#pragma mark Blend Options Properties

/**
 * Blend Mode for this layer node
 */
@property (readwrite, nonatomic) AdobePSDBlendMode blendMode;

/**
 * Blend Opacity for this layer node
 */
@property (readwrite, nonatomic) NSNumber *blendOpacity;

#pragma mark Pixel Mask Properties

/**
 * The density value of the pixel mask. This must not be modified for layers that do not have a pixel mask.
 */
@property (readwrite, nonatomic) NSNumber *pixelMaskDensity;

/**
 * Whether the pixel mask is enabled. This must not be modified for layers that do not have a pixel mask.
 */
@property (readwrite, nonatomic) BOOL pixelMaskEnabled;

/**
 * The feather value of the pixel mask. This must not be modified for layers that do not have a pixel mask.
 */
@property (readwrite, nonatomic) NSNumber *pixelMaskFeather;

/**
 * Whether the pixel mask is linked. This must not be modified for layers that do not have a pixel mask.
 */
@property (readwrite, nonatomic) BOOL pixelMaskLinked;

/**
 * The x and y offset of the mask. This must not be modified for layers that do not have a pixel mask.
 */
@property (readwrite, nonatomic) CGPoint pixelMaskOrigin;

#pragma mark Pixel Layer Properties

/**
 * The x and y offset of the pixel layer. This must not be modified for layers that are not pixels layers.
 */
@property (readwrite, nonatomic) CGPoint pixelLayerOrigin;


#pragma mark Fill Layer Properties

/**
 * The color of a fill layer. This must not be modified for layers that are not solid color fill layers.
 */
@property (readwrite, nonatomic) AdobePSDRGBColor *fillColor;

#pragma mark Convenience Constructors

/**
 * Create a new layer node.
 *
 * \param name    The name of the new layer node.
 * \param type    The type of the new layer node.
 *
 * \return        The new layer node.
 *
 * \note The newly created layer node does not yet have a valid layerId. Its layerId gets set when
 * it gets added to the PSD composite.
 */
+ (id)layerNodeWithName:(NSString *)name andType:(AdobePSDLayerNodeType)type;

#pragma mark Initializers

/**
 * Initialize a newly allocated layer node.
 *
 * \param name    The name of the new layer node.
 * \param type    The type of the new layer node.
 *
 * \return        The new layer node.
 *
 * \note The newly initialized layer node does not yet have a valid layerId. Its layerId gets set when
 * it gets added to the PSD composite.
 */
- (id)initWithName:(NSString *)name andType:(AdobePSDLayerNodeType)type;

@end

#endif
