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
 *
 ******************************************************************************/

/**************************************************************************
 * [PRIVATE BETA] CreativeSync enables seamless multi-app workflows via
 * the included APIs. If you have any questions, please contact us at
 * https://creativesdk.zendesk.com/hc/en-us/requests/new
 *************************************************************************/

#ifndef Adobe360MessageBuilderHeader
#define Adobe360MessageBuilderHeader

#import <Foundation/Foundation.h>

@class Adobe360Asset;
@class Adobe360Context;
@class Adobe360Message;

/*
 * \brief Provides an interface that is used to dynamically construct an Adobe360Message
 */
@interface Adobe360MessageBuilder : NSObject

// The unique actionId of the message.  This is auto-generated and should not typically be changed.
@property (strong, nonatomic) NSString *actionId;

// A 360 action type (i.e. "edit", "embed", "embedN", "capture", or "captureN")
@property (strong, nonatomic) NSString *actionType;

// The options dictionary with action-specific or application-specific parameters
@property (strong, nonatomic) NSDictionary *requestOptions;

// Provides additional context to the recipient regarding the ownership and membership of the media asset being acted upon
@property (strong, nonatomic) Adobe360Context *requestContext;

// A dictionary that maps from output name to an HTTP media-range string (as defined by the Accept header field)
@property (strong, nonatomic) NSDictionary *acceptedMediaTypes;

// Application specific data added to a request message by the primary application
@property (strong, nonatomic) NSDictionary *appSpecificData;

// The results dictionary with action-specific data
@property (strong, nonatomic) NSDictionary *responseResults;

// Provides additional context to the recipient regarding the ownership and membership of the media assets included as outputs
@property (strong, nonatomic) Adobe360Context *responseContext;

// A well-known, high-level status code (e.g. "ok", "canceled", "error")
@property (strong, nonatomic) NSString *responseStatusCode;

// A more-specific error (e.g. "unsupported-media-type")
@property (strong, nonatomic) NSString *responseReason;

// Reserved for use by the library code that provides the data transport layer
@property (strong, nonatomic) NSDictionary *transportReservedData;

// A dictionary mapping input names to Adobe360AssetDescriptors or arrays of descriptors
@property (nonatomic, readonly) NSDictionary *inputDescriptors;

// A dictionary mapping output names to Adobe360AssetDescriptors or arrays of descriptors
@property (nonatomic, readonly) NSDictionary *outputDescriptors;

/*
 * \brief Returns an instance of an Adobe360MessageBuilder that has been initialized with a unique actionId
 */
- (instancetype)init;

/*
 * \brief Returns and instance of an Adobe360MessageBuilder that has been initialized using the contents of a request message
 * \description This method is used to construct a builder for response messages.  All the request message's data is copied except
 * for the input assets, which are not included in the response message
 */
- (instancetype)initWithRequestMessage:(Adobe360Message *)message;

/*
 * \brief Adds a new scalar input asset to the builder
 */
- (void)addInputAsset:(Adobe360Asset *)input withName:(NSString*)name;

/*
 * \brief Adds a new input asset array to the builder
 */
- (void)addInputAssetArray:(NSArray *)assetArray withName:(NSString*)name;

/*
 * \brief Adds a new scalar output asset to the builder
 */
- (void)addOutputAsset:(Adobe360Asset *)output withName:(NSString*)name;

/*
 * \brief Adds a new input asset array to the builder
 */
- (void)addOutputAssetArray:(NSArray *)assetArray withName:(NSString*)name;

/*
 * \brief Adds a new input asset to the builder
 * \note This method has been replaced by addInputAsset (above)
 */
- (BOOL)addInputAsset:(Adobe360Asset *)input withError:(NSError **)error __deprecated;

/*
 * \brief Adds a new output asset to the builder
 * \note This method has been replaced by addOutputAsset (above)
 */
- (BOOL)addOutputAsset:(Adobe360Asset *)output withError:(NSError **)error __deprecated;

/*
 * \brief Returns the total number of bytes used by the inputs or outputs of the message
 *
 * \param errorPtr An optional NSError object that can receive error information
 * \return Number of bytes consumed by input or output assets; 0 if an error occurs.
 */
-(unsigned long long) sizeOfAssetsWithError:(NSError**)errorPtr;

/*
 * \brief Constructs an immutable Adobe360Message using the properties of this object
 */
- (Adobe360Message *)buildMessageWithError:(NSError **)errorPtr;

@end

#endif
