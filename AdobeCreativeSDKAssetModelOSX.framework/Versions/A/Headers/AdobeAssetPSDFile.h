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

#ifndef AdobeAssetPSDFileHeader
#define AdobeAssetPSDFileHeader

#import <AdobeCreativeSDKAssetModelOSX/AdobeAssetFile.h>
#import <AdobeCreativeSDKAssetModelOSX/AdobePSDComposite.h>

@class AdobeAGCManifest;
@class AdobePSDPreview;

/**
 * A utility to help determine if an AdobeAsset is an AdobeAssetPSDFile.
 */
#define IsAdobeAssetPSDFile(item) ([item isKindOfClass:[AdobeAssetPSDFile class]])

/**
 * AdobeAssetPSDFile represents a Photoshop Document (PSD file).  It provides methods for reading
 * PSD previews and composites from PSD files, creating PSD files from composites, and getting
 * layer renditions from PSD files.
 */
@interface AdobeAssetPSDFile : AdobeAssetFile

#pragma mark Create

/**
 * Create a PSD file by asynchronously pushing a PSD composite structure to Adobe Creative
 * Cloud. This operation performs a pushPSDComposite operation on
 * the returned AdobeAssetPSDFile instance, which can then be used to either change the request
 * priority or to cancel it.
 *
 * @param psdComposite The PSD composite used to create the PSD file on Adobe Creative Cloud.
 * @param overwrite In the case of a new PSD composite whether it should overwrite an already existing
 * composite. Set this to YES if a previous push has failed with an AdobeDCXErrorCompositeAlreadyExists
 * @param progressBlock Optionally, track the upload progress.
 * @param completionBlock Optionally, get an updated reference to the created file when complete.
 * @param cancellationBlock Optionally, be notified of a cancellation on upload.
 * @param errorBlock Optionally, be notified of an error.
 *
 * @returns A place holder pointer to the AdobeAssetPSDFile.
 */
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
+ (AdobeAssetPSDFile *)createWithPSDComposite:(AdobePSDComposite *)psdComposite
                            overwriteExisting:(BOOL)overwrite
                                   onProgress:(void (^)(double fractionCompleted))progressBlock
                                 onCompletion:(void (^)(AdobeAssetPSDFile *file))completionBlock
                               onCancellation:(void (^)(void))cancellationBlock
                                      onError:(void (^)(NSError *error))errorBlock __deprecated; // AdobePSDComposite will be replaced by CloudPSD and/or AGC
#pragma clang diagnostic pop

/**
 * Create a PSD file by asynchronously pushing an AdobeAGCManifest to Adobe Creative Cloud.
 *
 * @param name              The output name of the PSD file.
 * @param folder            The destination folder the PSD should be written to.
 * @param manifest          The AGC manifest used to create the PSD file on Adobe Creative Cloud.
 * @param imageComponents   An array of AdobeAGCImageComponent objects. Only image/jpg and image/png are supported content types.
 * @param overwrite         In the case of a new PSD file, whether it should overwrite an already existing composite.
 * @param progressBlock     Optionally, track the upload progress.
 * @param successBlock      Optionally, get an updated reference to the created file when complete.
 * @param cancellationBlock Optionally, be notified of a cancellation on upload.
 * @param errorBlock        Optionally, be notified of an error.
 *
 * @returns A place holder pointer to the AdobeAssetPSDFile.
 */
+ (AdobeAssetPSDFile *)create:(NSString *)name
                       folder:(AdobeAssetFolder *)folder
                  agcManifest:(AdobeAGCManifest *)manifest
              imageComponents:(NSArray *)imageComponents
                    overwrite:(BOOL)overwrite
                progressBlock:(void (^)(double fractionCompleted))progressBlock
                 successBlock:(void (^)(AdobeAssetPSDFile *file))successBlock
            cancellationBlock:(void (^)(void))cancellationBlock
                   errorBlock:(void (^)(NSError *error))errorBlock;

#pragma mark PSD Preview

/**
 * DEPRECATED
 * Gets a read-only description of the PSD file from Adobe Creative Cloud.
 *
 * @param layerCompId Optionally, the id of a layer comp to apply before generating the preview. If nil
 * no layer comp will be explicitly applied. TODO -- NOT YET IMPLEMENTED
 * @param progressBlock Optionally, track the download progress of the composite representation.
 * @param completionBlock Optionally, get a reference to a PSD composite object for the composite representation when download is complete.
 * @param cancellationBlock Optionally, be notified of a cancellation on download.
 * @param errorBlock Optionally, be notified of an error.
 */

- (void)getPreviewWithAppliedLayerCompId:(NSNumber *)layerCompId
                              onProgress:(void (^)(double))progressBlock
                            onCompletion:(void (^)(AdobePSDPreview *psdPreview))completionBlock
                          onCancellation:(void (^)(void))cancellationBlock
                                 onError:(void (^)(NSError *error))errorBlock __deprecated_msg("Use downloadPreviewWithAppliedCompID:progressBlock:successBlock:cancellationBlock:errorBlock");

/**
 * Gets a read-only description of the PSD file from Adobe Creative Cloud.
 *
 * @param layerCompID       Optionally, the id of a layer comp to apply before generating the preview. If nil
 * no layer comp will be explicitly applied. TODO -- NOT YET IMPLEMENTED
 * @param progressBlock     Optionally, track the download progress of the composite representation.
 * @param successBlock      Optionally, get a reference to a PSD composite object for the composite representation when download is complete.
 * @param cancellationBlock Optionally, be notified of a cancellation on download.
 * @param errorBlock        Optionally, be notified of an error.
 *
 * @return An @c AdobeAssetAsyncRequest which can be used to control the cancellation of the request.
 */

- (AdobeAssetAsyncRequest *)downloadPreviewWithAppliedLayerCompID:(NSNumber *)layerCompID
                                                    progressBlock:(void (^)(double))progressBlock
                                                     successBlock:(void (^)(AdobePSDPreview *psdPreview))successBlock
                                                cancellationBlock:(void (^)(void))cancellationBlock
                                                       errorBlock:(void (^)(NSError *error))errorBlock;

#pragma mark PSD Composite Pull

/**
 * Create a PSD composite object for this Creative Cloud file and pull down its composite
 * representation asynchronously from the cloud. The returned PSD composite object
 * can then be used to inspect or modify the PSD file via its composite representation.
 *
 * @param path The path where the local composite is stored.
 * @param progressBlock Optionally, track the download progress of the composite representation.
 * @param completionBlock Optionally, get a reference to a PSD composite object for the composite representation when download is complete.
 * @param cancellationBlock Optionally, be notified of a cancellation on download.
 * @param errorBlock Optionally, be notified of an error.
 */
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
- (void)pullPSDCompositeAt:(NSString *)path
                onProgress:(void (^)(double))progressBlock
              onCompletion:(void (^)(AdobePSDComposite *psdComposite))completionBlock
            onCancellation:(void (^)(void))cancellationBlock
                   onError:(void (^)(NSError *error))errorBlock __deprecated; // AdobePSDComposite will be replaced by CloudPSD and/or AGC

- (void)pullMinimalPSDCompositeAt:(NSString *)path
                       onProgress:(void (^)(double))progressBlock
                     onCompletion:(void (^)(AdobePSDComposite *psdComposite))completionBlock
                   onCancellation:(void (^)(void))cancellationBlock
                          onError:(void (^)(NSError *error))errorBlock __deprecated; // AdobePSDComposite will be replaced by CloudPSD and/or AGC
#pragma clang diagnostic pop

/**
 * Cancel the rendition request.
 */
- (void)cancelPullPSDCompositeRequest __deprecated; // AdobePSDComposite will be replaced by CloudPSD and/or AGC

/**
 * Change the priority of the rendition request.
 *
 * @param priority The priority of the request.
 */
- (void)changePSDCompositePullRequestPriority:(NSOperationQueuePriority)priority __deprecated; // AdobePSDComposite will be replaced by CloudPSD and/or AGC

#pragma mark PSD Composite Push

/**
 * Cancel the push request.
 */
- (void)cancelPushPSDCompositeRequest __deprecated; // AdobePSDComposite will be replaced by CloudPSD and/or AGC

/**
 * Change the priority of the push request.
 *
 * @param priority The priority of the push request.
 */
- (void)changePushPSDCompositeRequestPriority:(NSOperationQueuePriority)priority __deprecated; // AdobePSDComposite will be replaced by CloudPSD and/or AGC

#pragma mark PSD using AGC workflow

/**
 * Cancel the create request.
 */
- (void)cancelCreatePSDViaAGCRequest __deprecated_msg("Control cancellation via createAssetAsyncRequest");

/**
 * Change the priority of the create request.
 *
 * @param priority The priority of the create request.
 */
- (void)changeCreatePSDViaAGCRequestPriority:(NSOperationQueuePriority)priority __deprecated_msg("Control reprioritization via createAssetAsyncRequest");

#pragma mark Renditions

/**
 * DEPRECATED
 * Get a rendition of a layer in the PSD asynchronously.
 *
 * @param layerID The ID of the layer for which a rendition should be generated. Pass nil to render the entire PSD.
 * @param layerCompID The ID of the layerComp which should be applied. Pass nil to apply the default layerComp.
 * @param type The type of rendition to request.
 * @param dimensions The dimensions of the rendition in 'points'.  The value gets adjusted to
 *              pixels depending on the screen resolution.  The largest of the dimensions' width and
 *              height sets the bounds for the rendition size (width and height).
 * @param priority The priority of the request.
 * @param progressBlock Optionally, track the upload progress.
 * @param completionBlock Get the rendition data, and notified if returned from local cache.
 * @param cancellationBlock Optionally, be notified of a cancellation on upload.
 * @param errorBlock Optionally, be notified of an error for a request.
 *
 * @return The token for the request that can be used to cancel the request or change its priority.
 */
- (id)getRenditionForLayer:(NSNumber *)layerID
             withLayerComp:(NSNumber *)layerCompID
                  withType:(AdobeAssetFileRenditionType)type
                  withSize:(CGSize)dimensions
              withPriority:(NSOperationQueuePriority)priority
                onProgress:(void (^)(double))progressBlock
              onCompletion:(void (^)(NSData *, BOOL))completionBlock
            onCancellation:(void (^)(void))cancellationBlock
                   onError:(void (^)(NSError *))errorBlock __deprecated_msg("downloadRenditionForLayerID:layerCompID:renditionType:dimensions:requestPriority:progressBlock:successBlock:cancellationBlock:errorBlock");

/**
 * Get a rendition of a layer in the PSD asynchronously.
 *
 * @param layerID           The ID of the layer for which a rendition should be generated. Pass nil to render the entire PSD.
 * @param layerCompID       The ID of the layerComp which should be applied. Pass nil to apply the default layerComp.
 * @param renditionType     The type of rendition to request.
 * @param dimensions        The dimensions of the rendition in 'points'.  The value gets adjusted to
 *              pixels depending on the screen resolution.  The largest of the dimensions' width and
 *              height sets the bounds for the rendition size (width and height).
 * @param priority          The priority of the request.
 * @param progressBlock     Optionally, track the upload progress.
 * @param successBlock      Get the rendition data, and notified if returned from local cache.
 * @param cancellationBlock Optionally, be notified of a cancellation on upload.
 * @param errorBlock        Optionally, be notified of an error for a request.
 *
 * @return An @c AdobeAssetAsyncRequest which can be used to control the cancellation of the request.
 */
- (AdobeAssetAsyncRequest *)downloadRenditionForLayerID:(NSNumber *)layerID
                                            layerCompID:(NSNumber *)layerCompID
                                          renditionType:(AdobeAssetFileRenditionType)renditionType
                                             dimensions:(CGSize)dimensions
                                        requestPriority:(NSOperationQueuePriority)priority
                                          progressBlock:(void (^)(double))progressBlock
                                           successBlock:(void (^)(NSData *data, BOOL fromCache))successBlock
                                      cancellationBlock:(void (^)(void))cancellationBlock
                                             errorBlock:(void (^)(NSError *error))errorBlock;

/**
 * Cancel the layer rendition request.
 *
 * @param requestToken The token of the request to cancel.
 */
- (void)cancelLayerRenditionRequest:(id)requestToken __deprecated_msg("Control cancellation through the AdobeAssetAsyncRequest");

/**
 * Change the priority of the layer rendition request.
 *
 * @param requestToken Token ID of the request to cancel.
 * @param priority The priority of the request.
 */
- (void)changeLayerRenditionRequestPriority:(id)requestToken
                            withNewPriority:(NSOperationQueuePriority)priority __deprecated_msg("Control reprioritization through the AdobeAssetAsyncRequest");

@end

#endif /* ifndef AdobeAssetPSDFileHeader */
