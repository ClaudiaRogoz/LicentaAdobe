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

#ifndef AdobePSDCompositeMutableBranchHeader
#define AdobePSDCompositeMutableBranchHeader

#import <AdobeCreativeSDKAssetModelOSX/AdobePSDCompositeBranch.h>

@class AdobePSDMutableLayerNode;

/**
 * Allows for changes to be made to the current PSD composite branch.
 */
__deprecated // AdobePSDCompositeMutableBranch will be replaced by CloudPSD and/or AGC
@interface AdobePSDCompositeMutableBranch : AdobePSDCompositeBranch

/** The applied layer comp. Is nil if no layer comp is applied. */
@property (nonatomic, readwrite) AdobePSDLayerComp *appliedLayerComp;

/** The dimensions of the composite */
@property (nonatomic, readwrite) CGRect bounds;

/** The name of the composite. */
@property (nonatomic, readwrite) NSString *name;

#pragma mark - Layer Nodes

/**
 * Inserts the given layer at the given index position within the list of layers of parent.
 *
 * \param layer       The layer node to insert.
 * \param parent      The group layer what should become the new parent of the layer or nil in order
 * to insert the layer in the list of root layers.
 * \param index       The index where to insert the layer node at.
 *
 * \return            The updated layer node.
 *
 * \note This method will modify the layer id of the layer node.
 */
- (AdobePSDMutableLayerNode *)insertLayer:(AdobePSDLayerNode *)layer toParent:(AdobePSDLayerNode *)parent
                                  atIndex:(NSUInteger)index;


/**
 * Inserts the given layer at the end (i.e. top) of the list of layers of parent.
 *
 * \param layer       The layer node to add.
 * \param parent      The group layer what should become the new parent of the layer or nil in order
 * to insert the layer in the list of root layers.
 *
 * \return            The updated layer node.
 *
 * \note This method will modify the layer id of the layer node.
 */
- (AdobePSDMutableLayerNode *)addLayer:(AdobePSDLayerNode *)layer toParent:(AdobePSDLayerNode *)parent;  // add to end

/**
 * Updates the properties of the given layer node.
 *
 * \param layer   The modified layer node.
 *
 * \return        The updated layer node.
 */
- (AdobePSDMutableLayerNode *)updateLayer:(AdobePSDLayerNode *)layer;

/**
 * Removes the given layer from the composite.
 *
 * \param layer   The layer node to remove.
 *
 * \return        The removed layer node.
 */
- (AdobePSDMutableLayerNode *)removeLayer:(AdobePSDLayerNode *)layer;


#pragma mark - Layer Comps

/**
 * Inserts the given layer comp at the given index position within the list of layer comps of the composite.
 *
 * \param comp       The layer comp to insert.
 * \param index       The index where to insert the layer comp at.
 *
 * \return            The updated layer comp.
 *
 * \note NOT YET IMPLEMENTED
 */
- (AdobePSDLayerComp *)insertLayerComp:(AdobePSDLayerComp *)comp atIndex:(NSUInteger)index;

/**
 * Adds the given layer comp the list of layer comps of the composite.
 *
 * \param comp       The layer comp to add.
 *
 * \return            The updated layer comp.
 *
 * \note NOT YET IMPLEMENTED
 */
- (AdobePSDLayerComp *)addLayerComp:(AdobePSDLayerComp *)comp;

/**
 * Updates the properties of the given layer comp.
 *
 * \param comp   The modified layer comp.
 *
 * \return        The updated layer comp.
 */
- (AdobePSDLayerComp *)updateLayerComp:(AdobePSDLayerComp *)comp;


/**
 * Removes the given layer comp from the composite.
 *
 * \param comp   The layer comp to remove.
 *
 * \return        The removed layer comp.
 */
- (AdobePSDLayerComp *)removeLayerComp:(AdobePSDLayerComp *)comp;


#pragma mark - Images


/**
 * Updates the pixels of the given layer node from sourceFile.
 *
 * \param layer       The layer node to update. This must be a layer node of type AdobePSDLayerNodeTypeRGBPixels.
 * \param origin      X and Y offset of the pixels.
 * \param sourceFile  The bitmap file. Must be a PNG file.
 * \param copy        Whether to copy or move source file.
 * \param errorPtr    Gets set in case of a failure.
 *
 * \return            The updated layer node or nil if something went wrong.
 *
 * \note This method returns the modified layer node but doesn't modify the layer node that was passed in.
 * If you want to make further changes to the layer node you will need to use the returned layer node to
 * do so.
 */
- (AdobePSDMutableLayerNode *)updatePixelsOf:(AdobePSDLayerNode *)layer withOrigin:(CGPoint)origin
                                    fromFile:(NSString *)sourceFile copy:(BOOL)copy
                                   withError:(NSError **)errorPtr;


/**
 * Updates or adds the mask of the given layer node from sourceFile.
 *
 * \param layer       The layer node to update.
 * \param origin      X and Y offset of the mask.
 * \param sourceFile  The bitmap file. Must be a PNG file.
 * \param copy        Whether to copy or move source file.
 * \param errorPtr    Gets set in case of a failure.
 *
 * \return            The updated layer node or nil if something went wrong.
 *
 * \note This method returns the modified layer node but doesn't modify the layer node that was passed in.
 * If you want to make further changes to the layer node you will need to use the returned layer node to
 * do so.
 */
- (AdobePSDMutableLayerNode *)updateMaskOf:(AdobePSDLayerNode *)layer withOrigin:(CGPoint)origin
                                  fromFile:(NSString *)sourceFile copy:(BOOL)copy
                                 withError:(NSError **)errorPtr;

/**
 * Removes the layer mask of the given layer node. Is a no-op if the layer node doesn't have a mask.
 *
 * \param layer       The layer node to remove the mask from.
 *
 * \return            The updated layer node or nil if something went wrong.
 *
 * \note This method returns the modified layer node but doesn't modify the layer node that was passed in.
 * If you want to make further changes to the layer node you will need to use the returned layer node to
 * do so.
 */
- (AdobePSDLayerNode *)removeMaskOf:(AdobePSDLayerNode *)layer;

@end

#endif
