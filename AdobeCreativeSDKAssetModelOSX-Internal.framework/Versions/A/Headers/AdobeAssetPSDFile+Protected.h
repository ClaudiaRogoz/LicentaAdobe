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

#ifndef AdobeAssetPSDFileProtectedHeader
#define AdobeAssetPSDFileProtectedHeader

#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeStorageResourceItem.h>
#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeStorageResourceCollection.h>

@class AdobeCloud;
@class AdobeNetworkHTTPRequest;

extern NSString *const AdobeAssetFileCoderKeyType;
extern NSString *const AdobeAssetFileCoderKeyFileSize;
extern NSString *const AdobeAssetFileCoderKeyMD5Hash;
extern NSString *const AdobeAssetFileCoderKeyOptionalMeta;
extern NSString *const AdobeAssetFileCoderKeyHLSHref;

@interface AdobeAssetPSDFile (Protected)

- (id)initWithResourceItem:(AdobeStorageResourceItem *)item withParentResourceCollection:(AdobeStorageResourceCollection *)parent __deprecated_msg("Use initWithResourceItem:resourceCollection");

- (instancetype)initWithResourceItem:(AdobeStorageResourceItem *)item
resourceCollection:(AdobeStorageResourceCollection *)collection;

- (AdobeStorageResourceItem *)resourceItem;

- (NSString *)cacheKeyForLayerID:(NSNumber *)layerID
layerCompID:(NSNumber *)layerCompID
renditionType:(AdobeAssetFileRenditionType)renditionType
dimensions:(CGSize)dimensions;

- (BOOL)isCachedForKey:(NSString *)key;

/**
* Create a PSD file by asynchronously pushing a PSD composite structure to Adobe Creative
* Cloud. This operation performs a pushPSDComposite operation on
* the returned AdobeAssetPSDFile instance, which can then be used to either change the request
* priority or to cancel it.
*
* @param psdComposite The PSD composite used to create the PSD file on Adobe Creative Cloud.
* @param overwrite In the case of a new PSD composite whether it should overwrite an already existing
* composite. Set this to YES if a previous push has failed with an AdobeDCXErrorCompositeAlreadyExists
* @param cloud The cloud to create this composite in.
* @param progressBlock Optionally, track the upload progress.
* @param completionBlock Optionally, get an updated reference to the created file when complete.
* @param cancellationBlock Optionally, be notified of a cancellation on upload.
* @param errorBlock Optionally, be notified of an error.
*
* @returns A place holder pointer to the AdobeAssetPSDFile.
*/
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations" // suppress warnings about deprecated class AdobePSDComposite
+ (AdobeAssetPSDFile *)createWithPSDComposite:(AdobePSDComposite *)psdComposite
overwrite:(BOOL)overwrite
cloud:(AdobeCloud *)cloud
progressBlock:(void (^)(double fractionCompleted))progressBlock
completionBlock:(void (^)(AdobeAssetPSDFile *file))completionBlock
cancellationBlock:(void (^)(void))cancellationBlock
errorBlock:(void (^)(NSError *error))errorBlock __deprecated;
#pragma clang diagnostic pop

/**
* DEPRECATED
* Get renditions for an array of layers in the PSD asynchronously.
*
* @param layerIDs array of layer IDs for which a rendition should be generated. This is to support batch rendering mode.
* @param layerCompID The ID of the layerComp which should be applied. Pass nil to apply the default layerComp.
* @param type The type of rendition to request.
* @param dimensions The dimensions of the rendition in 'points'.  The value gets adjusted to
* pixels depending on the screen resolution.  The largest of the dimensions' width and
* height sets the bounds for the rendition size (width and height).
* @param priority The priority of the request.
* @param progressBlock Optionally, track the upload progress.
* @param completionBlock Get the rendition data, and notified if returned from local cache.
* @param cancellationBlock Optionally, be notified of a cancellation on upload.
* @param errorBlock Optionally, be notified of an error for a request.
*
* @return The token for the request that can be used to cancel the request or change its priority.
*/
- (AdobeNetworkHTTPRequest *)getRenditionForLayers:(NSArray *)layers
withLayerComp:(NSNumber *)layerCompID
withType:(AdobeAssetFileRenditionType)type
withSize:(CGSize)dimensions
withPriority:(NSOperationQueuePriority)priority
onProgress:(void (^)(double))progressBlock
onCompletion:(void (^)(BOOL))completionBlock
onCancellation:(void (^)(void))cancellationBlock
onError:(void (^)(NSError *))errorBlock;

/**
* Get renditions for an array of layers in the PSD asynchronously.
*
* @param layerIDs          Array of layer IDs for which a rendition should be generated. This is to support batch rendering mode.
* @param layerCompID       The ID of the layerComp which should be applied. Pass nil to apply the default layerComp.
* @param renditionType     The type of rendition to request.
* @param dimensions        The dimensions of the rendition in 'points'.  The value gets adjusted to
*                              pixels depending on the screen resolution.  The largest of the dimensions' width and
*                              height sets the bounds for the rendition size (width and height).
* @param priority          The priority of the request.
* @param progressBlock     Optionally, track the upload progress.
* @param successBlock      Get the rendition data, and notified if returned from local cache.
* @param cancellationBlock Optionally, be notified of a cancellation on upload.
* @param errorBlock        Optionally, be notified of an error for a request.
*
* @return An @c AdobeAssetAsyncRequest which can be used to control the cancellation of the request.
*/
- (AdobeAssetAsyncRequest *)downloadRenditionForLayersIDs:(NSArray *)layerIDs
layerCompID:(NSNumber *)layerCompID
renditionType:(AdobeAssetFileRenditionType)renditionType
dimensions:(CGSize)dimensions
requestPriority:(NSOperationQueuePriority)priority
progressBlock:(void (^)(double))progressBlock
successBlock:(void (^)(BOOL))successBlock
cancellationBlock:(void (^)(void))cancellationBlock
errorBlock:(void (^)(NSError *))errorBlock;

/**
* Push (i.e., save) the PSD composite object, including any modifications, to Adobe Creative Cloud
* asynchronously. The PSD composite is converted back into a PSD file and saved to
* this file's href location.
*
* @param psdComposite The PSD composite for the Creative Cloud file to be pushed back to the cloud.
* @param overwrite In the case of a new PSD composite whether it should overwrite an already existing
* composite. Set this to YES if a previous push has failed with an AdobeDCXErrorCompositeAlreadyExists
* error. Notice that this method will fail if overwrite is YES but there is nothing to overwrite.
* @param progressBlock Optionally, track the progress of the composite push.
* @param completionBlock Optionally, get a reference to a PSD composite object for the composite representation when the push is complete.
* @param cancellationBlock Optionally, be notified of a cancellation of the push.
* @param errorBlock Optionally, be notified of an error.
*/
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations" // suppress warnings about deprecated class AdobePSDComposite

- (void)pushPSDComposite:(AdobePSDComposite *)psdComposite
overwriteExisting:(BOOL)overwrite
onProgress:(void (^)(double))progressBlock
onCompletion:(void (^)(AdobePSDComposite *psdComposite))completionBlock
onCancellation:(void (^)(void))cancellationBlock
onError:(void (^)(NSError *error))errorBlock __deprecated;


/**
* Push (i.e., save) the PSD composite object, including any modifications, to Adobe Creative Cloud.
* The PSD composite will be converted back into a PSD file and saved to the file's
* href location.
*
* @param psdComposite The PSD composite for this cloud file to be push back to the cloud.
* @param overwrite In the case of a new PSD composite whether it should overwrite an already existing
* composite. Set this to YES if a previous push has failed with an AdobeDCXErrorCompositeAlreadyExists
* error. Notice that this method will fail if overwrite is YES but there is nothing to overwrite.
* @param errorPtr The error, if any, encountered during the push operation.
*
* @return Whether or not the push operation succeeded.
*/
- (BOOL)pushPSDComposite:(AdobePSDComposite *)psdComposite overwriteExisting:(BOOL)overwrite withError:(NSError **)errorPtr __deprecated;

#pragma clang diagnostic pop

@end

#endif /* ifndef AdobeAssetPSDFileProtectedHeader */
