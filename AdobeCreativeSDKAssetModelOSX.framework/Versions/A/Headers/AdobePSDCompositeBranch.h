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

#ifndef AdobePSDCompositeBranchHeader
#define AdobePSDCompositeBranchHeader

#import <Foundation/Foundation.h>

// Import CoreGraphics for iOS and ApplicationServices for Mac OS X
#if defined(__IPHONE_OS_VERSION_MIN_REQUIRED)
#import <CoreGraphics/CoreGraphics.h>
#else
#import <ApplicationServices/ApplicationServices.h>
#endif

#import <AdobeCreativeSDKAssetModelOSX/AdobePSDLayerComp.h>
#import <AdobeCreativeSDKAssetModelOSX/AdobePSDLayerNode.h>

/**
 * AdobePSDCompositeBranch represent a branch of a PSD composite.  PSD composites support multiple branches. Developers work with a current branch but have the ability to bring in other branches that can then be merged in.
 *
 * The following properties/methods have been deprecated:
 * <ul>
 * <li><code>-getLayersIntersectingPath:withLayerComp:</code>
 * <li><code>–layerIsVisible:withLayerComp:</code>
 * <li><code>–layerHasVisibleChildren:ofTypes:withLayerComp:recursively:</code>
 * </ul>
 */
__deprecated // AdobePSDCompositeBranch will be replaced by CloudPSD and/or AGC
@interface AdobePSDCompositeBranch : NSObject

/** The applied layer comp. Is nil if no layer comp is applied. */
@property (nonatomic, readonly) AdobePSDLayerComp *appliedLayerComp;

/** The dimensions of the composite */
@property (nonatomic, readonly) CGRect bounds;

/** The name of the composite. */
@property (nonatomic, readonly) NSString *name;


#pragma mark - Layer Nodes

/**
 * Count the number of layer nodes of the specified type.
 *
 * \param parentLayer     Must be either an existing layer node of type AdobePSDLayerNodeTypeGroup or
 * nil in which case the count will start at the root.
 * \param type            The type of nodes to include in the count.
 * \param recursiveCount		Whether the count should recursively include the result from sub layers.
 *
 * \return The count of layer nodes of the specified type.
 */
- (NSUInteger)countNodesOf:(AdobePSDLayerNode *)parentLayer ofType:(AdobePSDLayerNodeType)type recursively:(BOOL)recursiveCount;

/**
 * Count the number of layer nodes of the specified type that have an pixel image component.
 *
 * \param parentLayer     Must be either an existing layer node of type AdobePSDLayerNodeTypeGroup or
 * nil in which case the count will start at the root.
 * \param type            The type of nodes to include in the count.
 * \param recursiveCount		Whether the count should recursively include the result from sub layers.
 *
 * \return The count of layer nodes present of the specified type.
 */
- (NSUInteger)countLayerPixelsOf:(AdobePSDLayerNode *)parentLayer ofType:(AdobePSDLayerNodeType)type recursively:(BOOL)recursiveCount;

/**
 * Count the number of layer nodes of the specified type that have a mask component.
 *
 * \param parentLayer     Must be either an existing layer node of type AdobePSDLayerNodeTypeGroup or
 * nil in which case the count will start at the root.
 * \param type            The type of nodes to include in the count.
 * \param recursiveCount		Whether the count should recursively include the result from sub layers.
 *
 * \return The count of layer nodes present of the specified type.
 */
- (NSUInteger)countLayerMasksOf:(AdobePSDLayerNode *)parentLayer ofType:(AdobePSDLayerNodeType)type recursively:(BOOL)recursiveCount;

/**
 * Returns an array of layer nodes of the given parent layer.
 *
 * \param parentLayer     Must be either an existing layer node of type AdobePSDLayerNodeTypeGroup or
 * nil in which case the list of layer nodes at the root level will be returned.
 *
 * \return                An array of layer nodes.
 */
- (NSArray *)getLayersOf:(AdobePSDLayerNode *)parentLayer;

/**
 * Returns the layer node with the given layer id or nil if it doesn't exist.
 *
 * \param layerId The layer id of the requested layer.
 *
 * \return The layer node with the given layer id or nil if it doesn't exist.
 */
- (AdobePSDLayerNode *)getLayer:(NSNumber *)layerId;

#pragma mark - Layer Comps

/**
 * Count the number of layer comps.
 *
 * \return        The count of layer comps.
 */
- (NSUInteger)countLayerComps;

/**
 * Returns an array of layer comps of the composite.
 *
 * \return                An array of layer comps.
 */
- (NSArray *)getLayerComps;

/**
 * Returns the layer comps with the given layer comp id or nil if it doesn't exist.
 *
 * \param layerCompId The layer comp id of the requested layer comp.
 *
 * \return The layer comp with the given layer comp id or nil if it doesn't exist.
 */
- (AdobePSDLayerComp *)getLayerComp:(NSNumber *)layerCompId;



#pragma mark - Images

/**
 * Returns whether the pixels path of the given layer node exists.
 *
 * \param layer   The layer node to check.
 *
 * \return        True if the layer node contains a pixels image.
 */
- (BOOL)hasPixelsPathOf:(AdobePSDLayerNode *)layer;

/**
 * Returns the file path for the pixels of the given layer node.
 *
 * \param layer   The layer to return the pixels path for. This must be a layer node of type
 * AdobePSDLayerNodeTypeRGBPixels.
 * \param errorPtr Gets set to an NSError if something goes wrong.
 * \return        The file path for the pixels of the given layer node.
 */
- (NSString *)getPixelsPathOf:(AdobePSDLayerNode *)layer withError:(NSError **)errorPtr;

/**
 * Returns whether the mask path of the given layer node exists.
 *
 * \param layer   The layer node to check.
 *
 * \return        True if the layer node contains a mask image.
 */
- (BOOL)hasMaskPathOf:(AdobePSDLayerNode *)layer;

/**
 * Returns the file path for the mask of the given layer node or nil
 *
 * \param layer   The layer node to return the mask path for.
 * \param errorPtr	Gets set to an NSError if something goes wrong.
 * \return        The file path for the mask of the given layer node.
 */
- (NSString *)getMaskPathOf:(AdobePSDLayerNode *)layer withError:(NSError **)errorPtr;


#pragma mark - Deprecated

/**
 * Returns a list of layer nodes that intersect the given path.
 *
 * \param path        Selected path.
 * \param comp        The layer comp to search. Optional; pass \c nil to omit.
 *
 * \return The list of layer nodes that intersect the given path.
 */
- (NSArray *)getLayersIntersectingPath:(CGPathRef)path
                         withLayerComp:(AdobePSDLayerComp *)comp __deprecated;

/**
 * Returns whether a layer is visible, optionally taking into account the effects
 * of an applied layer comp.
 *
 * \param layer		The layer to check.
 * \param layerComp	The optional layer comp to apply when checking for visibility.
 *
 * \return True if the layer is visible.
 */
- (BOOL)layerIsVisible:(AdobePSDLayerNode *)layer withLayerComp:(AdobePSDLayerComp *)layerComp __deprecated;

/**
 * Returns whether a layer contains any visible sub-layers, optionally taking into
 * account the effects of an applied layer comp.
 *
 * Note that, when performing a recursive check, if a sub-layer group is invisible,
 * then all of its children are considered invisible regardless of their visibility
 * settings. If a recursive check is not performed, the layer group's visibility is
 * included in the check only if provided as part of the bit mask of types to consider.
 *
 * \param parentLayer     Must be either an existing layer node of type AdobePSDLayerNodeTypeGroup or
 * nil in which case the check will start at the root.
 * \param typesMask       Bit mask specifying which layer types should be checked for visibility.
 * AdobePSDLayerNodeTypeGroup bit mask will be ignored if recursive is true.
 * \param layerComp		The optional layer comp to apply when checking for visibility.
 * \param recursive		Whether the check should recursively include the result from sub layers.
 *
 * \return True if any sub-layers of the specified types are visible.
 */
- (BOOL)layerHasVisibleChildren:(AdobePSDLayerNode *)parentLayer ofTypes:(AdobePSDLayerNodeType)typesMask
                  withLayerComp:(AdobePSDLayerComp *)layerComp recursively:(BOOL)recursive __deprecated;

@end

#endif
