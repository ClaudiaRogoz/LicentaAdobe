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

#ifndef AdobePSDMutableLayerCompHeader
#define AdobePSDMutableLayerCompHeader

#import <AdobeCreativeSDKAssetModelOSX/AdobePSDLayerComp.h>

/**
 * This class allows you to create (or edit) a layer comp. You can define which layers should be visible when the comp is applied.
 */
@interface AdobePSDMutableLayerComp : AdobePSDLayerComp

#pragma mark Properties

// Override selected properties as mutable.

/**
 * The name of the layer comp
 */
@property (readwrite, nonatomic) NSString *name;

#pragma mark Convenience Constructors

/**
 * Create a new layer comp.
 *
 * \param name    The name of the new layer comp.
 *
 * \return        The new layer comp. */
+ (id)layerNodeWithName:(NSString *)name;

#pragma mark Initializers

/**
 * Initialize a newly allocated layer comp.
 *
 * \param name    The name of the new layer comp.
 *
 * \return        The new layer comp.
 */
- (id)initWithName:(NSString *)name;

@end

#endif
