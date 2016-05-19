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

#ifndef AdobeSelectionPSDLayerHeader
#define AdobeSelectionPSDLayerHeader

#import <Foundation/Foundation.h>

@class AdobePSDLayerNode;

/**
 * A utility to help determine if an item is an AdobeSelectionPSDLayer.
 */
#define IsAdobeSelectionPSDLayer(item) ([item isKindOfClass:[AdobeSelectionPSDLayer class]])

/**
 * AdobeSelectionPSDLayer represents a layer within a PSD that is selected.
 * Typically it is one item in an AdobePSDLayerSelectionArray (which is defined
 * in this class as a NSArray). It has one property, layer, that represents the
 * actual layer.
 *
 * @see AdobeSelectionAssetPSDFile
 */
@interface AdobeSelectionPSDLayer : NSObject <NSCoding>

/**
 * This represents the actual layer object.
 */
@property (readonly, nonatomic) AdobePSDLayerNode *layer;

/**
 * This represents the bounding rectangle of the layer object.
 */
@property (readwrite, nonatomic) CGRect bounds;

@end

/**
 * AdobePSDLayerSelectionArray represents an array of selected layers.
 * @see AdobeSelectionPSDLayer
 * @see AdobeSelectionAssetPSDFile
 */
typedef NSArray AdobePSDLayerSelectionArray;

#endif /* ifndef AdobeSelectionPSDLayerHeader */
