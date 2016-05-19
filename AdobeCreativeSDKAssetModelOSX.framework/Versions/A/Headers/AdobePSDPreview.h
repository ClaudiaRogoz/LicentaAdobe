/******************************************************************************
 *
 * ADOBE CONFIDENTIAL
 * ___________________
 *
 * Copyright 2015 Adobe Systems Incorporated
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

#ifndef AdobePSDPreviewHeader
#define AdobePSDPreviewHeader

#import <Foundation/Foundation.h>

// Import CoreGraphics for iOS and ApplicationServices for Mac OS X
#if defined(__IPHONE_OS_VERSION_MIN_REQUIRED)
#import <CoreGraphics/CoreGraphics.h>
#else
#import <ApplicationServices/ApplicationServices.h>
#endif

@class AdobePSDRGBColor;
@class AdobePSDPreviewLayerNode;

#pragma mark - AdobePSDPreviewLayerComp

/**
 * Read-only description of a layer comp in a PSD preview.
 */
@interface AdobePSDPreviewLayerComp : NSObject

/** The id of the layer comp.*/
@property (readonly) NSNumber *layerCompId;

/**
 * IDs for all the layers that are part of the receiver.
 */
@property (readonly, nonatomic) NSArray *layerIds;

/** The name of the layer comp.*/
@property (readonly) NSString *name;

/**
 * Checks whether this layer comp includes the layer with the specified ID.
 * @param layerId ID of the field being checked.
 */
- (BOOL)hasLayerId:(NSNumber *)layerId;

/**
 * Checks whether this layer comp includes the specified layer.
 * @param layer Layer being checked.
 */
- (BOOL)hasLayer:(AdobePSDPreviewLayerNode *)layer;

@end

#pragma mark - AdobePSDPreviewLayerNode

/** The different types of layer nodes.*/
typedef NS_OPTIONS (NSUInteger, AdobePSDPreviewLayerNodeType)
{
    /** Pixel layer */
    AdobePSDPreviewLayerNodeTypePixelsLayer         = (1 << 0),
    /** Text layer */
    AdobePSDPreviewLayerNodeTypeTextLayer           = (1 << 1),
    /** Layer group */
    AdobePSDPreviewLayerNodeTypeLayerGroup          = (1 << 2),
    /** Content layer */
    AdobePSDPreviewLayerNodeTypeContentLayer        = (1 << 3),
    /** Background layer */
    AdobePSDPreviewLayerNodeTypeBackgroundLayer     = (1 << 4),
    /** Adjustment layer */
    AdobePSDPreviewLayerNodeTypeAdjustmentLayer     = (1 << 5),
    /** Unknown */
    AdobePSDPreviewLayerNodeTypeUnknown             = (1 << 6)
};

/** The different classes of adjustment layers.*/
typedef NS_OPTIONS (NSUInteger, AdobePSDPreviewContentLayerClass)
{
    /** Solid color fill */
    AdobePSDPreviewContentLayerClassSolidColorFill   = (1 << 0),
    /** Gradient fill */
    AdobePSDPreviewContentLayerClassGradientFill     = (1 << 1),
    /** Pattern fill */
    AdobePSDPreviewContentLayerClassPatternFill      = (1 << 2),
    /** Unknown */
    AdobePSDPreviewContentLayerClassUnknown          = (1 << 3)
};

/**
 * Read-only description of a layer node in a PSD preview.
 */
@interface AdobePSDPreviewLayerNode : NSObject

/** The absolute index of the layer within the hierarchy of layer nodes. Layer nodes that are lower in the layer
 * panel in PS will have a lower index value. */
@property (readonly) NSUInteger absoluteLayerIndex;

/** The visible bounds of the layer. */
@property (readonly) CGRect bounds;

/** The class of the content layer. Only valid if the layer is of type AdobePSDPreviewLayerNodeTypeContentLayer.*/
@property (readonly) AdobePSDPreviewContentLayerClass contentLayerClass;

/** Whether the layer has a pixel mask. */
@property (readonly) BOOL hasPixelMask;

/** The id of the layer node.*/
@property (readonly) NSNumber *layerId;

/** The list of sub-layer nodes. Only valid if the layer is of type AdobePSDPreviewLayerNodeTypeLayerGroup. */
@property (readonly) NSArray *layerNodes;

/** The name of the layer node.*/
@property (readonly) NSString *name;

/** Whether the pixel mask is enabled. Only valid if the layer has a pixel mask. */
@property (readonly) BOOL pixelMaskEnabled;

/** The fill color of the layer. Only valid if the layer is of type AdobePSDPreviewLayerNodeTypeAdjustmentLayer
 * and has the adjustmentLayerClass AdobePSDPreviewAdjustmentLayerClassSolidColorFill. */
@property (readonly) AdobePSDRGBColor *solidFillColor;

/** The type of the layer node.*/
@property (readonly) AdobePSDPreviewLayerNodeType type;

/** Whether the layer is visible.*/
@property (readonly) BOOL visible;

/**
 * Retrieve the layer node with a specific layer id.
 *
 * @param layerID The ID of the layer to be returned.
 *
 * @return The AdobePSDPreviewLayerNode with the requested ID.
 */
- (AdobePSDPreviewLayerNode *)layerNodeWithLayer:(NSNumber *)layerID;

@end


#pragma mark - AdobePSDPreview
/**
 * Read-only description of the structure of a PSD file. Allows clients to inspect properties, layers
 * and layer comps of a PSD.
 */
@interface AdobePSDPreview : NSObject

/** The id of the applied layer comp or nil if non is applied. */
@property (readonly) NSNumber *appliedLayerCompId;

/** The bounds of the PSD. */
@property (readonly) CGRect bounds;

/** The list of layer comps. The objects are of class AdobePSDPreviewLayerComp. */
@property (readonly) NSArray *layerComps;

/** The list of first-level layer nodes. The objects are of class AdobePSDPreviewLayerNode. */
@property (readonly) NSArray *layerNodes;

/** The name of the PSD file. */
@property (readonly) NSString *name;

/**
 * Retrieve the PSD Preview from the given file
 *
 * \param filePath  File Path to the file containing the PSD Preview to retrieve.
 * \param name      Name of the PSD Preview.
 * \param errorPtr  An optional pointer to an error to receive error information.
 *
 * \return Instance of an AdobePSDPreview.
 */
+ (id)psdPreviewFromFile:(NSString *)filePath withName:(NSString *)name withError:(NSError **)errorPtr;

/**
 * Initialize an instance of AdobePSDPreview with a dictionary
 *
 * \param dict      Dictionary of parameters for creating the PSD Preview
 * \param name      Name of the PSD Preview
 * \param errorPtr  An optional pointer to an error to receive error information.
 *
 * \return Instance of an AdobePSDPreview.
 */
- (id)initWithDictionary:(NSDictionary *)dict withName:(NSString *)name withError:(NSError **)errorPtr;

/**
 * Return the layer node object for a given layer id.
 *
 * \param layerID   ID of the layer to retrieve.
 *
 * \return AdobePSDPreviewLayerNode object corresponding to the layerID
 */
- (AdobePSDPreviewLayerNode *)layerNodeWithLayer:(NSNumber *)layerID;

/**
 * Check whether the given layer is visible.
 *
 * \param layer   ID of the layer to retrieve.
 *
 * \return YES if layer is visible.
 */
- (BOOL)layerIsVisible:(AdobePSDPreviewLayerNode *)layer;

/**
 * Return the layer comp object for a given layer comp id.
 *
 * \param layerCompID   ID of the layer to retrieve.
 *
 * \return AdobePSDPreviewLayerComp object corresponding to the layerCompID.
 */
- (AdobePSDPreviewLayerComp *)getLayerComp:(NSNumber *)layerCompID;

/**
 * Check whether a layer has visible child layers.
 *
 * \param parentLayer   The parent layer to use to begin the check.
 * \param typesMask     Types of layer nodes to check.
 * \param recursive     YES to check recursively.
 *
 * \return YES if the parentLayer has visible children.
 */
- (BOOL)layerHasVisibleChildren:(AdobePSDPreviewLayerNode *)parentLayer ofTypes:(AdobePSDPreviewLayerNodeType)typesMask recursively:(BOOL)recursive;

@end

#endif
