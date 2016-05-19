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

#ifndef Adobe360MessagePrivateHeader
#define Adobe360MessagePrivateHeader

#ifndef DMALIB

typedef NS_ENUM (NSInteger, Adobe360MessageFormat)
{
Adobe360MessageFormatUnspecified,
Adobe360MessageFormatFromBuilder,
Adobe360MessageFormatComposite,
Adobe360MessageFormatSnapshot,
Adobe360MessageFormatTempSnapshot,
Adobe360MessageFormatTempComposite,
};


@interface Adobe360Message ()

// The unique actionId of the message
@property (nonatomic, readwrite) NSString *actionId;

// A 360 action type (e.g. "edit", "embed", or "capture")
@property (nonatomic, readwrite) NSString *actionType;

// The options dictionary with action-specific parameters
@property (nonatomic, readwrite) NSDictionary *requestOptions;

// Provides additional context to the recipient regarding the ownership and membership of the media asset being acted upon
@property (nonatomic, readwrite) Adobe360Context *requestContext;

// A dictionary that maps from output name to an array of media types that can be accepted for that output
@property (nonatomic, readwrite) NSMutableDictionary *acceptedMediaTypes;

// Application specific data added to a request message by the primary application
@property (nonatomic, readwrite) NSDictionary *appSpecificData;

// The results dictionary with action-specific data
@property (nonatomic, readwrite) NSDictionary *responseResults;

// Provides additional context to the recipient regarding the ownership and membership of the media assets returned
@property (nonatomic, readwrite) Adobe360Context *responseContext;

// A well-known, high-level status code (e.g. "ok", "cancelled", "error")
@property (nonatomic, readwrite) NSString *responseStatusCode;

// A more-specific error (e.g. "unsupported-media-type)
@property (nonatomic, readwrite) NSString *responseReason;

// Reserved for use by the library code that provides the data transport layer
@property (nonatomic, readwrite) NSDictionary *transportReservedData;

@property (nonatomic, readwrite) NSMutableDictionary *inputAssets;

@property (nonatomic, readwrite) NSMutableDictionary *outputAssets;

@property (nonatomic, readwrite) Adobe360MessageFormat format;

// Reserved for analytics.
@property (nonatomic, readwrite) NSDictionary *analyticsReservedData;


- (instancetype)initWithActionId:(NSString *)actionId;

- (BOOL)validateWithError:(NSError **)errorPtr;

@end

#endif // !DMALIB

#endif
