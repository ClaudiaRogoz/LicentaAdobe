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

#ifndef Adobe360MessageHeader
#define Adobe360MessageHeader

#import <Foundation/Foundation.h>

@class AdobeDCXComposite;
@class AdobeDCXElement;
@class Adobe360Context;

extern NSString *const Adobe360ActionTypeCapture;
extern NSString *const Adobe360ActionTypeCaptureN;
extern NSString *const Adobe360ActionTypeEdit;
extern NSString *const Adobe360ActionTypeEmbed;
extern NSString *const Adobe360ActionTypeEmbedN;

/*
 * \brief A data structure that describes the attributes of a media asset embedded in an Adobe360Message
 */
@interface Adobe360AssetDescriptor : NSObject <NSCopying>

// The name used to identify the asset within the scope of the requested action.
// Note: the name property has been deprecated: it is redundant with the name of the input or output
// that refers to the asset.
@property (strong, nonatomic) NSString *name __deprecated;

// The Internet media type describing the content type of the asset.
@property (strong, nonatomic) NSString *type;

// The relative path used to locate the asset within the message and its serialized representation.
// Note: if the asset is an input then it is relative to <message root>/inputs; if it is an output
// then it is relative to <message root>/outputs.
@property (strong, nonatomic) NSString *path;

+ (instancetype)assetDescriptorWithType:(NSString *)type path:(NSString *)path;

// Note: this method has been replaced by assetDescriptorWithType:path (above)
+ (instancetype)assetDescriptorWithName:(NSString *)name type:(NSString *)type path:(NSString *)path __deprecated;

@end

/*
 * \brief A data structure that describes a generic media asset embedded in an Adobe360Message
 */
@interface Adobe360Asset : NSObject <NSCopying>

// A reference to the asset data
//    If data is a NSString then it specifies a path to a file to be included as the asset
//    If data is a NSData then it contains the bytes that comprise the asset
//    If data is an AdobeDCXElement then that element is embedded as the asset
//      Note: the specified type of the asset must match the type of the DCX element or
//          the assetWithData factory methods will throw an NSInvalidArgumentException
@property (strong, nonatomic) id data;

// Additional details describing the asset
@property (strong, nonatomic) Adobe360AssetDescriptor *descriptor;

+ (instancetype)assetWithData:(id)data type:(NSString *)type path:(NSString *)path;
+ (instancetype)assetWithData:(id)data descriptor:(Adobe360AssetDescriptor *)descriptor;

// Note: this method has been replaced by assetWithData:type:path (above)
+ (instancetype)assetWithData:(id)data name:(NSString *)name type:(NSString *)type path:(NSString *)path __deprecated;

@end

/*
 * \brief An Adobe360Message is an immutable object that provides an interface that allows access to the contents of
 * a 360 workflow message used to exchange data between applications participating in a 360 deg Workflow.
 *
 * \note Adobe360Message objects are constructed using the Adobe360MessageBuilder class and by the readFrom class methods.
 * It is important to note that message objects maintain references to the input and output files that are added
 * via the Adobe360MessageBuilder or are contained within the snapshots, composites, or archives that are used as inputs to the
 * readFrom... methods that may have constructed the object.  Therefore it is imperative that these source files are treated
 * as immutable by the client of the message object for lifetime of the object.
 */
@interface Adobe360Message : NSObject

// The unique actionId of the message
@property (nonatomic, readonly) NSString *actionId;

// A 360 action type (e.g. "edit", "embed", "embedN", "capture", "captureN")
@property (nonatomic, readonly) NSString *actionType;

// The options dictionary with action-specific parameters
@property (nonatomic, readonly) NSDictionary *requestOptions;

// Provides additional context to the recipient regarding the ownership and membership of the media asset being acted upon
@property (nonatomic, readonly) Adobe360Context *requestContext;

// A dictionary that maps from output name to an HTTP media-range string (as defined by the Accept header field)
@property (nonatomic, readonly) NSDictionary *acceptedMediaTypes;

// Application specific data added to a request message by the primary application
@property (nonatomic, readonly) NSDictionary *appSpecificData;

// The results dictionary with action-specific data
@property (nonatomic, readonly) NSDictionary *responseResults;

// Provides additional context to the recipient regarding the ownership and membership of the media assets included as outputs
@property (nonatomic, readonly) Adobe360Context *responseContext;

// A well-known, high-level status code (e.g. "ok", "canceled", "error")
@property (nonatomic, readonly) NSString *responseStatusCode;

// A more-specific error (e.g. "unsupported-media-type)
@property (nonatomic, readonly) NSString *responseReason;

// A dictionary mapping input names to Adobe360AssetDescriptors or arrays of descriptors
@property (nonatomic, readonly) NSDictionary *inputDescriptors;

// A dictionary mapping output names to Adobe360AssetDescriptors or arrays of descriptors
@property (nonatomic, readonly) NSDictionary *outputDescriptors;

// Reserved for use by the library code that provides the data transport layer
@property (nonatomic, readonly) NSDictionary *transportReservedData;

// Reserved for analytics data.
@property (nonatomic, readonly) NSDictionary *analyticsReservedData;

/*
 * \brief Creates a message from the serialized message data that exists at filePath
 * \param filePath Path to message data (DCX snapshot, composite or archive file)
 * \param handlerQueue The operation queue on which the completion handler will be called
 * \param completionHandler Called upon completion with a references to the resulting message or error, depending
 * on whether the operation was successful
 * \return An NSProgress object that may be used to cancel the packaging operation or report progress events
 */
+ (NSProgress *)readFromPath:(NSString *)path handlerQueue:(NSOperationQueue *)queue completionHandler:(void (^)(Adobe360Message *message, NSError *error))handler;

/*
 * \brief Creates a message from an in-memory message archive
 * \param messageData NSData object containing the archive bytes
 * \param handlerQueue The operation queue on which the completion handler will be called
 * \param completionHandler Called upon completion with a references to the resulting message or error, depending
 * on whether the operation was successful
 * \return An NSProgress object that may be used to cancel the packaging operation or report progress events
 */
+ (NSProgress *)readFromData:(NSData *)messagedData handlerQueue:(NSOperationQueue *)queue completionHandler:(void (^)(Adobe360Message *message, NSError *error))handler;

/*
 * \brief Creates a message from a DCX composite representation
 * \param composite A "360-exchange composite" that was previously created by the writeToCompositeAtPath: method
 * \param handlerQueue The operation queue on which the completion handler will be called
 * \param completionHandler Called upon completion with a references to the resulting message or error, depending
 * on whether the operation was successful
 * \return An NSProgress object that may be used to cancel the packaging operation or report progress events
 */
+ (NSProgress *)readFromComposite:(AdobeDCXComposite *)composite handlerQueue:(NSOperationQueue *)queue completionHandler:(void (^)(Adobe360Message *message, NSError *error))handler;

/*
 * \brief Write the message to a DCX snapshot
 * \param path  Path where snapshot should be written.  If singleFile is true then path identifies a filename, otherwise it refers to a directory.
 * \param singleFile  Indicates whether the snapshot should be written to a single file representation.
 *      This is typically more expensive so this should only be done when needed by the transport layer
 * \param handlerQueue The operation queue on which the completion handler will be called
 * \param completionHandler Called upon completion with a non-nil file path or error, depending
 * on whether the operation was successful
 * \return An NSProgress object that may be used to cancel the packaging operation and report progress events
 */
- (NSProgress *)writeToSnapshotAtPath:(NSString *)path inSingleFile:(BOOL)singleFile handlerQueue:(NSOperationQueue *)queue completionHandler:(void (^)(NSString *filePath, NSError *error))handler;

/*
 * \brief Write the message to a DCX composite at the specified path
 * \param compositePath Path to the new composite
 * \param handlerQueue The operation queue on which the completion handler will be called
 * \param completionHandler Called upon completion with a non-nil composite or error, depending
 * on whether the operation was successful
 * \return An NSProgress object that may be used to cancel the packaging operation and report progress events
 */
- (NSProgress *)writeToCompositeAtPath:(NSString *)compositePath handlerQueue:(NSOperationQueue *)queue completionHandler:(void (^)(AdobeDCXComposite *composite, NSError *error))handler;

/*
 * \brief Create an in-memory representation of a message in a single buffer
 * \param handlerQueue The operation queue on which the completion handler will be called
 * \param completionHandler Called upon completion with a non-nil message data or error, depending
 * on whether the operation was successful
 * \return An NSProgress object that may be used to cancel the packaging operation and report progress events
 */
- (NSProgress *)writeToDataWithHandlerQueue:(NSOperationQueue *)queue completionHandler:(void (^)(NSData *messageData, NSError *error))handler;

/*
 * \brief Writes an scalar valued input to the specified path
 * \note This method may be used with both atomic and DCX assets.  In the case
 * of a DCX element then path specifies the directory into which the corresponding composite will be written.
 */
- (BOOL)writeInputWithName:(NSString *)name toPath:(NSString *)path withError:(NSError **)errorPtr;

/*
 * \brief Writes an scalar valued output to the specified path
 * \note This method may be used with both atomic and DCX assets.  In the case
 * of a DCX element then path specifies the directory into which the corresponding composite will be written.
 */
- (BOOL)writeOutputWithName:(NSString *)name toPath:(NSString *)path withError:(NSError **)errorPtr;

/*
 * \brief Writes an asset stored at a specific index in a named input array to the specified path.
 * \note This method may only be used for  inputs that refer to an array of assets, which may consist of both atomic and DCX elements.
 * If the asset is a DCX element then the path specifies the directory into which the corresponding composite will be written.
 * The number of elements in a given input array correspond to the size of the NSArray for the named input that is available through
 * the 'inputDescriptors' property of the this object.
 */
- (BOOL)writeAssetInInputArrayWithName:(NSString *)name atIndex:(NSUInteger)index toPath:(NSString *)path withError:(NSError **)errorPtr;

/*
 * \brief Writes an asset stored at a specific index in a named input array to the specified path.
 * \note This method may only be used for outputs that refer to an array of assets, which may be both atomic or DCX elements.
 * If the asset is a DCX element then the path specifies the directory into which the corresponding composite will be written.
 * The number of elements in a given output array correspond to the size of the NSArray for the named output that is available through
 * the 'outputDescriptors' property of the this object.
 */
- (BOOL)writeAssetInOutputArrayWithName:(NSString *)name atIndex:(NSUInteger)index toPath:(NSString *)path withError:(NSError **)errorPtr;

/*
 * \brief Writes an scalar valued input or output asset to the specified path
 * \note This method may be used with both atomic and DCX assets.  In the case
 * of a DCX element then path specifies the directory into which the corresponding composite will be written.
 
 */
- (BOOL)writeAssetWithName:(NSString *)name toPath:(NSString *)path withError:(NSError **)errorPtr __deprecated;

/*
 * \brief Returns an NSData object with the bytes that comprise an atomic asset refered by a scalar named input.
 * \note This method may be used for action assets that have both on-disk and in-memory representations
 * within the message but is not used for assets that are represented as DCX elements.
 */
- (NSData *)dataForInputWithName:(NSString *)name withError:(NSError **)errorPtr;

/*
 * \brief Returns an NSData object with the bytes that comprise an atomic asset refered by a scalar named output.
 * \note This method may be used for action assets that have both on-disk and in-memory representations
 * within the message but is not used for assets that are represented as DCX elements.
 */
- (NSData *)dataForOutputWithName:(NSString *)name withError:(NSError **)errorPtr;

/*
 * \brief Returns an NSData object with the bytes that comprise an atomic asset that is stored at a specific index
 * in a named input array.
 * \note This method may only be used for named inputs that refer to an array of assets.  The assets themselves may have either
 * on-disk or in-memory representations within the message but this method may not used for assets that are represented as DCX elements.
 * The number of elements in a given input array correspond to the size of the NSArray for the named input that is available through
 * the 'inputDescriptors' property of the this object.
 */
- (NSData *)dataForAssetInInputArrayWithName:(NSString *)name atIndex:(NSUInteger)index withError:(NSError **)errorPtr;

/*
 * \brief Returns an NSData object with the bytes that comprise an atomic asset that is stored at a specific index
 * in a named output array.
 * \note This method may only be used for outputs that refer to an array of assets.  The assets themselves may have either
 * on-disk or in-memory representations within the message but this method may not used for assets that are represented as DCX elements.
 * The number of elements in a given output array correspond to the size of the NSArray for the named output that is available through
 * the 'outputDescriptors' property of the this object.
 */
- (NSData *)dataForAssetInOutputArrayWithName:(NSString *)name atIndex:(NSUInteger)index withError:(NSError **)errorPtr;

/*
 * \brief Returns an NSData object with the bytes that comprise an atomic input or output asset.
 * \note This method may be used for action assets that have both on-disk and in-memory representations
 * within the message.
 * This method has been replaced by dataForInputWithName and dataForOutputWithName.
 */
- (NSData *)dataForAssetWithName:(NSString *)name withError:(NSError **)errorPtr __deprecated;

/*
 * \brief Returns a file path to the scalar input asset with the specified name if it has an independent
 * on-disk representation
 *
 * \note The file should not be modified and is only guaranteed to exist for the lifetime of the
 * message object.
 */
- (NSString *)pathToImmutableInputWithName:(NSString *)name withError:(NSError **)errorPtr;

/*
 * \brief Returns a file path to the scalar output asset with the specified name if it has an independent
 * on-disk representation
 *
 * \note The file should not be modified and is only guaranteed to exist for the lifetime of the
 * message object.
 */
- (NSString *)pathToImmutableOutputWithName:(NSString *)name withError:(NSError **)errorPtr;

/*
 * \brief Returns a file path to the input asset stored at a specific index in a named asset array
 * if it has an independent on-disk representation.
 *
 * \note The file should not be modified and is only guaranteed to exist for the lifetime of the
 * message object.
 * The number of elements in a given input array correspond to the size of the NSArray for the named input that is available through
 * the 'inputDescriptors' property of the this object.
 */
- (NSString *)pathToImmutableAssetInInputArrayWithName:(NSString *)name atIndex:(NSUInteger)index withError:(NSError **)errorPtr;

/*
 * \brief Returns a file path to the output asset stored at a specific index in a named asset array
 * if it has an independent on-disk representation.
 *
 * \note The file should not be modified and is only guaranteed to exist for the lifetime of the
 * message object.
 * The number of elements in a given output array correspond to the size of the NSArray for the named output that is available through
 * the 'outputDescriptors' property of the this object.
 */
- (NSString *)pathToImmutableAssetInOutputArrayWithName:(NSString *)name atIndex:(NSUInteger)index withError:(NSError **)errorPtr;

/*
 * \brief Returns a file path to the input or output asset with the specified name if it has an independent
 * on-disk representation
 * \note The file should not be modified and is ony guaranteed to exist for the lifetime of the
 * message object.
 * This method has been replaced by pathToImmutableInputWithName and pathToImmutableOutputWithName.
 */
- (NSString *)pathToImmutableAssetWithName:(NSString *)name withError:(NSError **)errorPtr __deprecated;

/*
 * \brief Returns a DCX Element if the scalar input asset with the specified name is represented as such
 */
- (AdobeDCXElement *)elementForInputWithName:(NSString *)name withError:(NSError **)errorPtr;

/*
 * \brief Returns a DCX Element if the scalar output asset with the specified name is represented as such
 */
- (AdobeDCXElement *)elementForOutputWithName:(NSString *)name withError:(NSError **)errorPtr;

/*
 * \brief Returns a DCX Element if the asset stored at a specific index in an input array is represented as such
 * \note The number of elements in a given input array correspond to the size of the NSArray for the named input that is available through
 * the 'inputDescriptors' property of the this object.
 */
- (AdobeDCXElement *)elementForAssetInInputArrayWithName:(NSString *)name atIndex:(NSUInteger)index withError:(NSError **)errorPtr;

/*
 * \brief Returns a DCX Element if the asset stored at a specific index in an output array is represented as such
 * \note The number of elements in a given output array correspond to the size of the NSArray for the named output that is available through
 * the 'outputDescriptors' property of the this object.
 */
- (AdobeDCXElement *)elementForAssetInOutputArrayWithName:(NSString *)name atIndex:(NSUInteger)index withError:(NSError **)errorPtr;

/*
 * \brief Returns a DCX Element if the input or output asset with the specified name is represented as such
 * \note This method has been replaced by elementForInputWithName and elementForOutputWithName.
 */
- (AdobeDCXElement *)elementForAssetWithName:(NSString *)name withError:(NSError **)errorPtr __deprecated;

/**
 * \brief Helper method that deletes the files referenced by the message
 *
 * \description Depending on the method used to instantiate the message object, these files may comprise the snapshot,
 * composite, or input/output assets added via the Adobe360MessageBuilder class
 *
 * \param errorPtr Gets set if an error occurs.
 * \return YES on success.
 * \note Subsequent calls to writeAssetWithName, dataForAssetWithName, and pathToImmutableAssetWithName will
 * result in Adobe360ErrorAssetFileDoesNotExist errors.
 */
- (BOOL)removeLocalStorage:(NSError **)errorPtr;

@end

#endif
