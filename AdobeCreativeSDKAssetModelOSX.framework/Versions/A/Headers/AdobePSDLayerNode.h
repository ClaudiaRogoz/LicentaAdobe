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

#ifndef AdobePSDLayerNodeHeader
#define AdobePSDLayerNodeHeader

#import <Foundation/Foundation.h>

// Import CoreGraphics for iOS and ApplicationServices for Mac OS X
#if defined(__IPHONE_OS_VERSION_MIN_REQUIRED)
#import <CoreGraphics/CoreGraphics.h>
#else
#import <ApplicationServices/ApplicationServices.h>
#endif

#import <AdobeCreativeSDKAssetModelOSX/AdobePSDRGBColor.h>

/**
 * Represents the type of the layer.
 */
typedef NS_OPTIONS (NSInteger, AdobePSDLayerNodeType)
{
    /** Unknown */
    AdobePSDLayerNodeTypeUnknown    = (1 << 0),
    /** RGB */
    AdobePSDLayerNodeTypeRGBPixels  = (1 << 1),
    /** Solid Color */
    AdobePSDLayerNodeTypeSolidColor = (1 << 2),
    /** Grouped */
    AdobePSDLayerNodeTypeGroup      = (1 << 3),
    /** Adjustement */
    AdobePSDLayerNodeTypeAdjustment = (1 << 4)
};

/**
 * Layer blend modes.
 */
typedef NS_ENUM (NSInteger, AdobePSDBlendMode)
{
    /** Normal */
    AdobePSDBlendModeNormal         =  0,
    /** Dissolve */
    AdobePSDBlendModeDissolve       =  1,
    /** Darken */
    AdobePSDBlendModeDarken         =  2,
    /** Multiple */
    AdobePSDBlendModeMultiply       =  3,
    /** Color Burn */
    AdobePSDBlendModeColorBurn      =  4,
    /** Linear Burn */
    AdobePSDBlendModeLinearBurn     =  5,
    /** Darker Color */
    AdobePSDBlendModeDarkerColor    =  6,
    /** Lighten */
    AdobePSDBlendModeLighten        =  7,
    /** Screen */
    AdobePSDBlendModeScreen         =  8,
    /** Color Dodge */
    AdobePSDBlendModeColorDodge     =  9,
    /** Linear Dodge */
    AdobePSDBlendModeLinearDodge    = 10,
    /** Lighter Color */
    AdobePSDBlendModeLighterColor   = 11,
    /** Mode Overlay */
    AdobePSDBlendModeOverlay        = 12,
    /** Soft Light */
    AdobePSDBlendModeSoftLight      = 13,
    /** Hard Light */
    AdobePSDBlendModeHardLight      = 14,
    /** Vivid Light */
    AdobePSDBlendModeVividLight     = 15,
    /** Linear Light */
    AdobePSDBlendModeLinearLight    = 16,
    /** Pin Light */
    AdobePSDBlendModePinLight       = 17,
    /** Hard Mix */
    AdobePSDBlendModeHardMix        = 18,
    /** Difference */
    AdobePSDBlendModeDifference     = 19,
    /** Exclusion */
    AdobePSDBlendModeExclusion      = 20,
    /** Subtract */
    AdobePSDBlendModeSubtract       = 21,
    /** Divide */
    AdobePSDBlendModeDivide         = 22,
    /** Hue */
    AdobePSDBlendModeHue            = 23,
    /** Saturation */
    AdobePSDBlendModeSaturation     = 24,
    /** Color */
    AdobePSDBlendModeColor          = 25,
    /** Luminosity */
    AdobePSDBlendModeLuminosity     = 26,

    /** Pass Through. This mode is only valid for layer groups. */
    AdobePSDBlendModePassThrough    = 27,
    /** Unknown */
    AdobePSDBlendModeUnknown        = 28
};

/**
 * AdobePSDLayerNode represents a layer node (either a leaf layer or a layer group within a PSD file.
 * Notice that this is an immutable class. If you need to make changes to a layer node you will need
 * to create a mutable copy of it and then call updateLayerNode: on its composite.
 *
 * The following properties/methods have been deprecated:
 * <ul>
 * <li><code>bounds</code>
 * </ul>
 *
 */
@interface AdobePSDLayerNode : NSObject <NSMutableCopying>

#pragma mark General Layer Properties

/**
 * The ID of the layer node.
 */
@property (readonly, nonatomic) NSNumber *layerId;

/**
 * The absolute index of the layer node within the structure of the PSD. The bottom-most layer (in z-order)
 * has the lowest layerIndex -- albeit not necessarily a specific value like 0 or 1. Is NSNotFound
 * if the layer node is not part of a PSD composite branch.
 */
@property (readonly, nonatomic) NSUInteger layerIndex;

/**
 * The name of the layer node.
 */
@property (nonatomic) NSString *name;

/**
 * The type of the layer.
 */
@property (readonly, nonatomic) AdobePSDLayerNodeType type;

/**
 * Whether the layer is visible.
 */
@property (readonly, nonatomic) BOOL visible;

#pragma mark Blend Options Properties

/**
 * The blend mode of the layer.
 */
@property (readonly, nonatomic) AdobePSDBlendMode blendMode;

/**
 * The opacity value of the layer.
 */
@property (readonly, nonatomic) NSNumber *blendOpacity;


#pragma mark Pixel Mask Properties

/**
 * Whether the layer has a pixel mask.
 */
@property (readonly, nonatomic) BOOL hasPixelMask;

/**
 * The bounding box of the pixelMask. Only valid for layers that have a pixel mask.
 */
@property (readonly, nonatomic) CGRect pixelMaskBounds;

/**
 * The density value of the pixel mask. Only valid for layers that have a pixel mask.
 */
@property (readonly, nonatomic) NSNumber *pixelMaskDensity;

/**
 * Whether the pixel mask is enabled. Only valid for layers that have a pixel mask.
 */
@property (readonly, nonatomic) BOOL pixelMaskEnabled;

/**
 * The feather value of the pixel mask. Only valid for layers that have a pixel mask.
 */
@property (readonly, nonatomic) NSNumber *pixelMaskFeather;

/**
 * Whether the pixel mask is linked. Only valid for layers that have a pixel mask.
 */
@property (readonly, nonatomic) BOOL pixelMaskLinked;


#pragma mark Pixel Layer Properties

/**
 * The bounding box of the pixelLayer. Returns nil if the layer is not a pixels layer.
 */
@property (readonly, nonatomic) CGRect pixelLayerBounds;

#pragma mark Content Layer Properties

/**
 * The color of a fill layer. Returns nil if the layer is not a fill layer.
 */
@property (readonly, nonatomic) AdobePSDRGBColor *fillColor;

#pragma mark - Deprecated

@property (readonly, nonatomic) CGRect bounds __deprecated;

@end

#endif
