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

#ifndef AdobeAssetFileHeader
#define AdobeAssetFileHeader

#import <Foundation/Foundation.h>

#import <AdobeCreativeSDKAssetModelOSX/AdobeAsset.h>

@class AdobeAssetAsyncRequest;

/**
 * A utility to help determine if an AdobeAsset is an AdobeAssetFile.
 */
#define IsAdobeAssetFile(item) ([item isKindOfClass:[AdobeAssetFile class]])

/**
 * The content-types for which to request a rendition.
 */
typedef NS_ENUM (NSInteger, AdobeAssetFileRenditionType)
{
    /**
     * The JPEG file rendition type on the Creative Cloud
     */
    AdobeAssetFileRenditionTypeJPEG = 0,

    /**
     * The PNG file rendition type on the Creative Cloud
     */
    AdobeAssetFileRenditionTypePNG,

    /**
     * The PDF file rendition type on the Creative Cloud
     */
    AdobeAssetFileRenditionTypePDF,

    /**
     * The GIF file rendition type on the Creative Cloud
     */
    AdobeAssetFileRenditionTypeGIF,

    /**
     * The TIFF file rendition type on the Creative Cloud
     */
    AdobeAssetFileRenditionTypeTIFF,
};

/**
 * The filename collision policy (used during creation).
 */
typedef NS_ENUM (NSInteger, AdobeAssetFileCollisionPolicy)
{
    /**
     * Overwrite with a new version.
     */
    AdobeAssetFileCollisionPolicyOverwriteWithNewVersion,

    /**
     * Create a new file by appending a unique number.
     */
    AdobeAssetFileCollisionPolicyAppendUniqueNumber
};

#define FULL_SIZE_RENDITION       CGSizeZero
#define THUMBNAIL_SIZED_RENDITION CGSizeMake(250, 250)

@class AdobeAssetFolder;

/**
 * AdobeAssetFile represents a file and provides access to data about the file (type, size, etc).
 * It allows for reading and creating files in the Creative Cloud and can deliver a thumbnail rendition of an asset.
 */
@interface AdobeAssetFile : AdobeAsset <NSCopying, NSCoding>

/**
 * The current version of the file as a number.
 *
 * The currentVersion property returns the current version of a file as a number.
 */
@property (readonly, nonatomic, assign) NSUInteger currentVersion;

/**
 * The file size in bytes.
 */
@property (readonly, nonatomic, assign) long long fileSize;

/**
 * Content-MD5 value that can be used for Message Integrity Check validations.
 *
 * Note that this value is not a plain message-digest but a Base64-encoded binary md5 of the file
 * content as described in Section 14.15 of RFC-2616
 * http://tools.ietf.org/html/rfc2616#section-14.15
 */
@property (readonly, nonatomic, strong) NSString *md5Hash;

/**
 * Optional metadata for the file. For example, if the file is an image, the width and height
 * be specified here.
 */
@property (readonly, nonatomic, strong) NSDictionary *optionalMetadata;

/**
 * Whether a rendition can be generated for the file.
 *
 * The backing service cannot generate renditions for every conceivable file type, so callers
 * should check this property before attempting to fetch a rendition for this asset. A value
 * of @c YES true indicates that a rendition can be generated for this file.
 */
@property (readonly, nonatomic, assign, getter = isRenderable) BOOL renderable;

/**
 * Asset creation async request.
 */
@property (nonatomic, readonly, strong) AdobeAssetAsyncRequest *createAssetAsyncRequest;

/**
 * DEPRECTATED
 * Create and upload a file into the Adobe Creative Cloud asynchronously.
 * @note In the event of a naming collision, this API will create a new revision (version) of the file.
 *
 * @param name The name of the file.
 * @param parentFolder The enclosing folder of the file.
 * @param dataPath The local URL that stores the data for the file.
 * @param type The content-type of the file as a MIME type.
 * @param progressBlock Optionally track the upload progress.
 * @param completionBlock Optionally get an updated reference to the created file when complete.
 * @param cancellationBlock Optionally be notified of a cancellation on upload.
 * @param errorBlock Optionally be notified of an error.
 *
 * @return A placeholder pointer to the AdobeAssetFile.
 *
 * @see AdobeAssetMimeTypes
 */
+ (AdobeAssetFile *)create:(NSString *)name
                  inFolder:(AdobeAssetFolder *)parentFolder
              withDataPath:(NSURL *)dataPath
                  withType:(NSString *)type
                onProgress:(void (^)(double fractionCompleted))progressBlock
              onCompletion:(void (^)(AdobeAssetFile *file))completionBlock
            onCancellation:(void (^)(void))cancellationBlock
                   onError:(void (^)(NSError *error))errorBlock __deprecated_msg("Use create:folder:dataPath:contentType:progressBlock:successBlock:cancellationBlock:errorBlock");

/**
 * Create and upload a file into the Adobe Creative Cloud asynchronously.
 * @note In the event of a naming collision, this API will create a new revision (version) of the file.
 *
 * @param name              The name of the file.
 * @param folder            The enclosing folder of the file.
 * @param dataPath          The local URL that stores the data for the file.
 * @param contentType       The content-type of the file. See @c AdobeAssetMimeTypes.
 * @param progressBlock     Optionally track the upload progress.
 * @param successBlock      Optionally get an updated reference to the created file when complete.
 * @param cancellationBlock Optionally be notified of a cancellation on upload.
 * @param errorBlock Optionally be notified of an error.
 *
 * Upload can be cancelled via the createAssetAsyncRequest property.
 *
 * @return A placeholder pointer to the AdobeAssetFile.
 *
 * @see AdobeAssetMimeTypes
 * @see AdobeAssetAsyncRequest
 */
+ (AdobeAssetFile *)create:(NSString *)name
                    folder:(AdobeAssetFolder *)folder
                  dataPath:(NSURL *)dataPath
               contentType:(NSString *)contentType
             progressBlock:(void (^)(double fractionCompleted))progressBlock
              successBlock:(void (^)(AdobeAssetFile *file))successBlock
         cancellationBlock:(void (^)(void))cancellationBlock
                errorBlock:(void (^)(NSError *error))errorBlock;

/**
 * DEPRECTATED
 * Create and upload a file into the Adobe Creative Cloud asynchronously.
 *
 * @param name The name of the file.
 * @param parentFolder The enclosing folder of the file.
 * @param dataPath The local URL that stores the data for the file.
 * @param type The content-type of the file as a MIME type.
 * @param policy The policy to enact if encountering a filename collision.
 * @param progressBlock Optionally track the upload progress.
 * @param completionBlock Optionally get an updated reference to the created file when complete.
 * @param cancellationBlock Optionally be notified of a cancellation on upload.
 * @param errorBlock Optionally be notified of an error.
 *
 * @return A placeholder pointer to the AdobeAssetFile.
 *
 * @see AdobeAssetMimeTypes
 */
+ (AdobeAssetFile *)create:(NSString *)name
                  inFolder:(AdobeAssetFolder *)parentFolder
              withDataPath:(NSURL *)dataPath
                  withType:(NSString *)type
       withCollisionPolicy:(AdobeAssetFileCollisionPolicy)policy
                onProgress:(void (^)(double fractionCompleted))progressBlock
              onCompletion:(void (^)(AdobeAssetFile *file))completionBlock
            onCancellation:(void (^)(void))cancellationBlock
                   onError:(void (^)(NSError *error))errorBlock __deprecated_msg("Use create:folder:dataPath:contentType:collisionPolicy:progressBlock:successBlock:cancellationBlock:errorBlock");

/**
 * Create and upload a file into the Adobe Creative Cloud asynchronously.
 * @note In the event of a naming collision, this API will create a new revision (version) of the file.
 *
 * @param name              The name of the file.
 * @param folder            The enclosing folder of the file.
 * @param dataPath          The local URL that stores the data for the file.
 * @param contentType       The content-type of the file. See @c AdobeAssetMimeTypes.
 * @param collisionPolicy   The policy to enact if encountering a filename collision.
 * @param progressBlock     Optionally track the upload progress.
 * @param successBlock      Optionally get an updated reference to the created file when complete.
 * @param cancellationBlock Optionally be notified of a cancellation on upload.
 * @param errorBlock Optionally be notified of an error.
 *
 * Upload can be cancelled via the createAssetAsyncRequest property.
 *
 * @return A placeholder pointer to the AdobeAssetFile.
 *
 * @see AdobeAssetMimeTypes
 * @see AdobeAssetAsyncRequest
 */
+ (AdobeAssetFile *)create:(NSString *)name
                    folder:(AdobeAssetFolder *)folder
                  dataPath:(NSURL *)dataPath
               contentType:(NSString *)contentType
           collisionPolicy:(AdobeAssetFileCollisionPolicy)collisionPolicy
             progressBlock:(void (^)(double fractionCompleted))progressBlock
              successBlock:(void (^)(AdobeAssetFile *file))successBlock
         cancellationBlock:(void (^)(void))cancellationBlock
                errorBlock:(void (^)(NSError *error))errorBlock;

/**
 * DEPRECTATED
 * Cancel the creation request.
 */
- (void)cancelCreationRequest __deprecated_msg("Control cancellation via createAssetAsyncRequest");

/**
 * DEPRECTATED
 * Change the priority of the upload. By default: NSOperationQueuePriorityNormal.
 *
 * @param priority The priority of the request.
 */
- (void)changeCreationRequestPriority:(NSOperationQueuePriority)priority __deprecated_msg("Control reprioritization via createAssetAsyncRequest");

/**
 * DEPRECTATED
 * Update a file onto the Adobe Creative Cloud asynchronously.
 *
 * @param dataPath The local URL that stores the data for the file.
 * @param type The content-type of the file.
 * @param progressBlock Optionally track the upload progress.
 * @param completionBlock Optionally get an updated reference to the created file when complete.
 * @param cancellationBlock Optionally be notified of a cancellation on upload.
 * @param errorBlock Optionally be notified of an error.
 */
- (void)    update:(NSURL *)dataPath
          withType:(NSString *)type
        onProgress:(void (^)(double fractionCompleted))progressBlock
      onCompletion:(void (^)(AdobeAssetFile *file))completionBlock
    onCancellation:(void (^)(void))cancellationBlock
           onError:(void (^)(NSError *error))errorBlock __deprecated_msg("Use update:contentType:progressBlock:successBlock:cancellationBlock:errorBlock");

/**
 * Update a file onto the Adobe Creative Cloud asynchronously.
 *
 * @param dataPath          The local URL that stores the data for the file.
 * @param contentType       The content-type of the file. See @c AdobeAssetMimeTypes.
 * @param progressBlock     Optionally track the upload progress.
 * @param successBlock      Optionally get an updated reference to the created file when complete.
 * @param cancellationBlock Optionally be notified of a cancellation on upload.
 * @param errorBlock        Optionally be notified of an error.
 *
 * @return An @c AdobeAssetAsyncRequest which can be used to control the cancellation of the request.
 *
 * @see AdobeAssetMimeTypes
 */
- (AdobeAssetAsyncRequest *)update:(NSURL *)dataPath
                       contentType:(NSString *)contentType
                     progressBlock:(void (^)(double fractionCompleted))progressBlock
                      successBlock:(void (^)(AdobeAssetFile *file))successBlock
                 cancellationBlock:(void (^)(void))cancellationBlock
                        errorBlock:(void (^)(NSError *error))errorBlock;

/**
 * DEPRECTATED
 * Cancel the update request.
 */
- (void)cancelUpdateReqest __deprecated_msg("Control cancellation through the AdobeAssetAsyncRequest");

/**
 * DEPRECTATED
 * Change the priority of the upload. By default: NSOperationQueuePriorityNormal.
 *
 * @param priority The priority of the request.
 */
- (void)changeUpdateRequestPriority:(NSOperationQueuePriority)priority __deprecated_msg("Control reprioritization through the AdobeAssetAsyncRequest");

/**
 * DEPRECTATED
 *  Refreshes the file's metadata.
 *
 *  @param completionBlock A completion block that notifies the caller when the refresh operation
 *                         has succeeded.
 *  @param errorBlock      An block that informs the caller of any error that may have occurred
 *                         while refreshing.
 */
- (void)refresh:(void (^)(AdobeAssetFile *file))completionBlock
        onError:(void (^)(NSError *error))errorBlock __deprecated_msg("Use refresh:cancellationBlock:errorBlock");

/**
 *  Refreshes the file's metadata.
 *
 *  @param successBlock         A block that notifies the caller when the refresh operation has succeeded.
 *  @param cancellationBlock    Optionally be notified of a cancellation on upload.
 *  @param errorBlock           An block that informs the caller of any error that may have occurred
 *                              while refreshing.
 *
 * @return An @c AdobeAssetAsyncRequest which can be used to control the cancellation of the request.
 */
- (AdobeAssetAsyncRequest *)refresh:(void (^)(AdobeAssetFile *file))successBlock
                  cancellationBlock:(void (^)(void))cancellationBlock
                         errorBlock:(void (^)(NSError *error))errorBlock;

/**
 * DEPRECTATED
 * Archive the specified file asynchronously. It does not permanently delete the file from the cloud.
 * There is no API to expunge nor restore the file from the archive as of this time.
 *
 * @param completionBlock Optionally be notified when complete.
 * @param errorBlock Optionally be notified of an error.
 */
- (void)archive:(void (^)(void))completionBlock
        onError:(void (^)(NSError *error))errorBlock __deprecated_msg("Use archive:errorBlock");

/**
 * Archive the specified file asynchronously. It does not permanently delete the file from the cloud.
 * There is no API to expunge nor restore the file from the archive as of this time.
 *
 * @param successBlock  Optionally be notified when complete.
 * @param errorBlock    Optionally be notified of an error.
 */
- (void)archive:(void (^)(void))successBlock
     errorBlock:(void (^)(NSError *error))errorBlock;

/*
 * Whether this asset can stream video.
 */
- (BOOL)canStreamVideo;

/**
 * DEPRECTATED
 * Get a rendition of the file asynchronously.
 *
 * If renditions are not supported for this type of asset, the completion block will
 * be called with 'data' set to nil. Callers should check the isRenderable property
 * before making this call.
 *
 * @param type The type of rendition to request.
 * @param dimensions The dimensions of the rendition in 'points'.  The value gets adjusted to
 *      pixels depending on the screen resolution.  The largest of the dimensions' width and
 *      height sets the bounds for the rendition size (width and height).
 * @param priority The priority of the request.
 * @param progressBlock Optionally track the download progress.
 * @param completionBlock Get the rendition data, and notified if returned from local cache.
 * @param cancellationBlock Optionally be notified of a cancellation on upload.
 * @param errorBlock Optionally be notified of an error.
 *
 * @warning Note that renditions may be created by third-party applications and therefore may be
 *          unsafe. Applications may wish to perform validation on the rendition data to ensure it
 *          is in the proper format.
 */
- (void)getRenditionWithType:(AdobeAssetFileRenditionType)type
                    withSize:(CGSize)dimensions
                withPriority:(NSOperationQueuePriority)priority
                  onProgress:(void (^)(double fractionCompleted))progressBlock
                onCompletion:(void (^)(NSData *data, BOOL fromCache))completionBlock
              onCancellation:(void (^)(void))cancellationBlock
                     onError:(void (^)(NSError *error))errorBlock __deprecated_msg("Use downloadRenditionWithType:dimensions:progressBlock:successBlock:cancellationBlock:errorBlock");

/**
 * Get a rendition of the file asynchronously.
 *
 * If renditions are not supported for this type of asset, the completion block will
 * be called with 'data' set to nil. Callers should check the isRenderable property
 * before making this call.
 *
 * @param type              The type of rendition to request.
 * @param dimensions        The dimensions of the rendition in 'points'.  The value gets adjusted to
 *      pixels depending on the screen resolution.  The largest of the dimensions' width and
 *      height sets the bounds for the rendition size (width and height).
 * @param priority          The priority of the request.
 * @param progressBlock     Optionally track the download progress.
 * @param successBlock      Get the rendition data, and notified if returned from local cache.
 * @param cancellationBlock Optionally be notified of a cancellation on upload.
 * @param errorBlock        Optionally be notified of an error.
 *
 * @return An @c AdobeAssetAsyncRequest which can be used to control the transfer priority and cancellation of the request.
 *
 * @warning Note that renditions may be created by third-party applications and therefore may be
 *          unsafe. Applications may wish to perform validation on the rendition data to ensure it
 *          is in the proper format.
 *
 * @see AdobeAssetFileRenditionType
 */
- (AdobeAssetAsyncRequest *)downloadRenditionWithType:(AdobeAssetFileRenditionType)type
                                           dimensions:(CGSize)dimensions
                                      requestPriority:(NSOperationQueuePriority)priority
                                        progressBlock:(void (^)(double fractionCompleted))progressBlock
                                         successBlock:(void (^)(NSData *data, BOOL fromCache))successBlock
                                    cancellationBlock:(void (^)(void))cancellationBlock
                                           errorBlock:(void (^)(NSError *error))errorBlock;

/**
 * DEPRECTATED
 * Get a rendition of a page from a multi-paged file asynchronously.
 *
 * If renditions are not supported for this type of asset, the completion block will
 * be called with 'data' set to nil. Callers should check the isRenderable property
 * before making this call.
 *
 * @param type The type of rendition to request.
 * @param dimensions The dimensions of the rendition in 'points'.  The value gets adjusted to
 *      pixels depending on the screen resolution.  The largest of the dimensions' width and
 *      height sets the bounds for the rendition size (width and height).
 * @param page The page to get the rendition for.
 * @param priority The priority of the request.
 * @param progressBlock Optionally track the download progress.
 * @param completionBlock Get the rendition data, and notified if returned from local cache.
 * @param cancellationBlock Optionally be notified of a cancellation on upload.
 * @param errorBlock Optionally be notified of an error.
 */
- (void)getRenditionWithType:(AdobeAssetFileRenditionType)type
                    withSize:(CGSize)dimensions
                     forPage:(NSUInteger)page
                withPriority:(NSOperationQueuePriority)priority
                  onProgress:(void (^)(double fractionCompleted))progressBlock
                onCompletion:(void (^)(NSData *data, BOOL fromCache))completionBlock
              onCancellation:(void (^)(void))cancellationBlock
                     onError:(void (^)(NSError *error))errorBlock __deprecated_msg("Use downloadRenditionWithType:dimensions:page:progressBlock:successBlock:cancellationBlock:errorBlock");

/**
 * Get a rendition of a page from a multi-paged file asynchronously.
 *
 * If renditions are not supported for this type of asset, the completion block will
 * be called with 'data' set to nil. Callers should check the isRenderable property
 * before making this call.
 *
 * @param type              The type of rendition to request.
 * @param dimensions        The dimensions of the rendition in 'points'.  The value gets adjusted to
 *      pixels depending on the screen resolution.  The largest of the dimensions' width and
 *      height sets the bounds for the rendition size (width and height).
 * @param page The page to get the rendition for.
 * @param priority          The priority of the request.
 * @param progressBlock     Optionally track the download progress.
 * @param successBlock      Get the rendition data, and notified if returned from local cache.
 * @param cancellationBlock Optionally be notified of a cancellation on upload.
 * @param errorBlock        Optionally be notified of an error.
 *
 * @return An @c AdobeAssetAsyncRequest which can be used to control the transfer priority and cancellation of the request.
 *
 * @warning Note that renditions may be created by third-party applications and therefore may be
 *          unsafe. Applications may wish to perform validation on the rendition data to ensure it
 *          is in the proper format.
 *
 * @see AdobeAssetFileRenditionType
 */
- (AdobeAssetAsyncRequest *)downloadRenditionWithType:(AdobeAssetFileRenditionType)type
                                           dimensions:(CGSize)dimensions
                                                 page:(NSUInteger)page
                                      requestPriority:(NSOperationQueuePriority)priority
                                        progressBlock:(void (^)(double fractionCompleted))progressBlock
                                         successBlock:(void (^)(NSData *data, BOOL fromCache))successBlock
                                    cancellationBlock:(void (^)(void))cancellationBlock
                                           errorBlock:(void (^)(NSError *error))errorBlock;

/**
 * DEPRECTATED
 * Cancel the rendition request.
 */
- (void)cancelRenditionRequest __deprecated_msg("Control cancellation through the AdobeAssetAsyncRequest");

/**
 * DEPRECTATED
 * Change the priority of the rendition request.
 *
 * @param priority The priority of the request.
 */
- (void)changeRenditionRequestPriority:(NSOperationQueuePriority)priority __deprecated_msg("Control repriotization through the AdobeAssetAsyncRequest");

/**
 * DEPRECTATED
 * Download the data for the file asynchronously.
 *
 * The downloaded bits for the file will be stored in memory as they arrive from the network. If
 * the file being downloaded is large, this method could use a significant amount of memory, which
 * could potentially cause your application to be terminated. It is recommended to only use this
 * method for downloading small files. For downloading files of any arbitrary size consider using
 * @c downloadToPath:withPriority:onProgress:completion:cancellation:error: which stores the
 * downloaded bits in a temporary file on disk.
 *
 * @param priority          The priority of the request.
 * @param progressBlock     Optionally track the upload progress.
 * @param completionBlock   Get the rendition data, and notified if returned from local cache.
 * @param cancellationBlock Optionally be notified of a cancellation on upload.
 * @param errorBlock        Optionally be notified of an error.
 *
 * @see downloadToPath:withPriority:onProgress:completion:cancellation:error:
 */
- (void)   getData:(NSOperationQueuePriority)priority
        onProgress:(void (^)(double fractionCompleted))progressBlock
      onCompletion:(void (^)(NSData *data, BOOL fromCache))completionBlock
    onCancellation:(void (^)(void))cancellationBlock
           onError:(void (^)(NSError *error))errorBlock __deprecated_msg("Use downloadData:progressBlock:successBlock:cancellationBlock:errorBlock");

/**
 * Download the data for the file asynchronously.
 *
 * The downloaded bits for the file will be stored in memory as they arrive from the network. If
 * the file being downloaded is large, this method could use a significant amount of memory, which
 * could potentially cause your application to be terminated. It is recommended to only use this
 * method for downloading small files. For downloading files of any arbitrary size consider using
 * @c downloadToPath:withPriority:onProgress:completion:cancellation:error: which stores the
 * downloaded bits in a temporary file on disk.
 *
 * @param priority          The priority of the request.
 * @param progressBlock     Optionally track the upload progress.
 * @param successBlock      Get the rendition data, and notified if returned from local cache.
 * @param cancellationBlock Optionally be notified of a cancellation on upload.
 * @param errorBlock        Optionally be notified of an error.
 *
 * @return An @c AdobeAssetAsyncRequest which can be used to control the transfer priority and cancellation of the request.
 *
 * @see downloadToPath:requestPriority:progressBlock:successBlock:cancellationBlock:errorBlock:
 */
- (AdobeAssetAsyncRequest *)downloadData:(NSOperationQueuePriority)priority
                           progressBlock:(void (^)(double fractionCompleted))progressBlock
                            successBlock:(void (^)(NSData *data, BOOL fromCache))successBlock
                       cancellationBlock:(void (^)(void))cancellationBlock
                              errorBlock:(void (^)(NSError *error))errorBlock;

/**
 * DEPRECTATED
 * Cancel the data request.
 */
- (void)cancelDataRequest __deprecated_msg("Control cancellation through the AdobeAssetAsyncRequest");

/**
 * DEPRECTATED
 * Change the priority of the data request.
 *
 * @param priority The priority of the request.
 */
- (void)changeDataRequestPriority:(NSOperationQueuePriority)priority __deprecated_msg("Control repriotization through the AdobeAssetAsyncRequest");

/**
 * Download the file to the specified path asynchronously.
 *
 * Use this method if the receiver is a large file and wouldn't fit into memory while the bits are
 * being downloaded. In general this method should be used instead of
 * @c getData:onProgress:onCompletion:onCancellation:onError:
 *
 * Once the download task has been created the priority of the underlying HTTP request can be
 * changed using the @c changeDownloadToPathRequestPriority: method. The download action can also
 * be cancelled using the @c cancelDownloadToPathRequest method.
 *
 * Note that the specified location will contain the data bits @em after all the bits have arrived
 * from the network. During the download process, iOS keeps the downloaded bits in an internal disk
 * cache.
 *
 * @param filePath              File system path where to download the file.
 * @param priority              Priority of the download task. To change the priority of the
 *                              request after creation use the
 *                              @c changeDownloadToPathRequestPriority: method.
 * @param progressHandler       Progress handler for observing the progress of the download
 *                              process. Specify @c NULL to omit the block.
 * @param completionHandler     Handler for when the download process has completed. A ponter to
 *                              the receiver is returned for convenience. When this block has been
 *                              executed, the file data has been fully downloaded and is available
 *                              at the specified @c filePath argument.
 * @param cancellationHandler   Cancellation handler in the case where the download request has been
 *                              cancelled. Specify @c NULL to omit.
 * @param errorHandler          Error handler to respond to any errors. Specify @c NULL to omit.
 *
 * @see getData:onProgress:onCompletion:onCancellation:onError:
 * @see cancelDownloadToPathRequest
 * @see changeDownloadToPathRequestPriority:
 */
- (void)downloadToPath:(NSString *)filePath
          withPriority:(NSOperationQueuePriority)priority
            onProgress:(void (^)(double fractionCompleted))progressHandler
            completion:(void (^)(AdobeAssetFile *assetFile))completionHandler
          cancellation:(void (^)(void))cancellationHandler
                 error:(void (^)(NSError *error))errorHandler;

/**
 * Download the file to the specified path asynchronously.
 *
 * Use this method if the receiver is a large file and wouldn't fit into memory while the bits are
 * being downloaded. In general this method should be used instead of
 * @c getData:onProgress:onCompletion:onCancellation:onError:
 *
 * Once the download task has been created the priority of the underlying HTTP request can be
 * changed using the @c changeDownloadToPathRequestPriority: method. The download action can also
 * be cancelled using the @c cancelDownloadToPathRequest method.
 *
 * Note that the specified location will contain the data bits @em after all the bits have arrived
 * from the network. During the download process, iOS keeps the downloaded bits in an internal disk
 * cache.
 *
 * @param filePath              File system path where to download the file.
 * @param priority              Priority of the download task. To change the priority of the
 *                              request after creation use the
 *                              @c changeDownloadToPathRequestPriority: method.
 * @param progressBlock         Progress block for observing the progress of the download
 *                              process. Specify @c NULL to omit the block.
 * @param successBlock          Block for when the download process has completed. A ponter to
 *                              the receiver is returned for convenience. When this block has been
 *                              executed, the file data has been fully downloaded and is available
 *                              at the specified @c filePath argument.
 * @param cancellationBlock     Cancellation block in the case where the download request has been
 *                              cancelled. Specify @c NULL to omit.
 * @param errorBlock            Error block to respond to any errors. Specify @c NULL to omit.
 *
 * @return An @c AdobeAssetAsyncRequest which can be used to control the transfer priority and cancellation of the request.
 *
 * @see data:progressBlock:successBlock:cancellationBlock:errorBlock:
 */
- (AdobeAssetAsyncRequest *)downloadToPath:(NSString *)filePath
                           requestPriority:(NSOperationQueuePriority)priority
                             progressBlock:(void (^)(double fractionCompleted))progressBlock
                              successBlock:(void (^)(AdobeAssetFile *assetFile))successBlock
                         cancellationBlock:(void (^)(void))cancellationBlock
                                errorBlock:(void (^)(NSError *error))errorBlock;

/**
 * DEPRECTATED
 * Cancel the request created by calling the
 * @c downloadToPath:withPriority:onProgress:completion:cancellation:error: method.
 *
 * @see downloadToPath:withPriority:onProgress:completion:cancellation:error:
 */
- (void)cancelDownloadToPathRequest __deprecated_msg("Control cancellation through the AdobeAssetAsyncRequest");

/**
 * DEPRECTATED
 * Change the priority of the download to file request.
 *
 * @param priority The new priority of the request.
 *
 * @see downloadToPath:withPriority:onProgress:completion:cancellation:error:
 */
- (void)changeDownloadToPathRequestPriority:(NSOperationQueuePriority)priority __deprecated_msg("Control reprioritization through the AdobeAssetAsyncRequest");

/**
 * Set the version of the Cloud File.
 *
 * @param version The version to set as the current version of the Cloud File.
 */
- (void)setVersion:(NSUInteger)version;

/**
 * A utility to test the equality of two AdobeAssetFiles.
 *
 * @param file the AdobeAssetFile to test against.
 */
- (BOOL)isEqualToFile:(AdobeAssetFile *)file;

@end

#endif /* ifndef AdobeAssetFileHeader */
