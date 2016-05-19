/*************************************************************************
*
* ADOBE CONFIDENTIAL
* ___________________
*
*  Copyright 2014 Adobe Systems Incorporated
*  All Rights Reserved.
*
* NOTICE:  All information contained herein is, and remains
* the property of Adobe Systems Incorporated and its suppliers,
* if any.  The intellectual and technical concepts contained
* herein are proprietary to Adobe Systems Incorporated and its
* suppliers and are protected by trade secret or copyright law.
* Dissemination of this information or reproduction of this material
* is strictly forbidden unless prior written permission is obtained
* from Adobe Systems Incorporated.
**************************************************************************/

#ifndef AdobeImageSessionHeader
#define AdobeImageSessionHeader

#import <Foundation/Foundation.h>

#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeAssetIllustratorManifest.h>
#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobePSDSessionProtocol.h>

@class AdobeAGCImageComponent;
@class AdobeAGCManifest;
@class AdobeCloudEndpoint;
@class AdobeImageOperation;
@class AdobeImageOutputParameters;
@class AdobeNetworkHTTPRequest;
@class AdobeNetworkHTTPService;
@class AdobeStorageResourceItem;

extern NSString *const AdobeSessionImageServiceTag;

/** A generic completion handler for asynchronous resource-based ImageSession data requests. */
typedef void (^AdobeImageResourceRequestCompletionHandler)(AdobeStorageResourceItem *resource, NSError *err);

/** A generic completion handler for asynchronous resource-based ImageSession data requests. */
typedef void (^AdobeImageRequestCompletionHandler)(AdobeImageOperation *operation, NSError *err);

/** The type of image adjustment to use in an image operation*/
typedef NS_ENUM (NSInteger, AdobeImageAdjustType)
{
AdobeImageFullAdjust /*does complete adjustment*/,
AdobeImageEyeLevelAdjust /*does only horizontal eye level adjustment*/,
AdobeImageNoPerspectiveAdjust /*does not correct for perspective distortion*/,
AdobeImageRectificationAdjust /*does only image rectification adjusting for camera rotation*/,
AdobeImageAdjustAll /*output matrix & optional images for all adjust values*/
};

/** The calibration mode to use in determining intrinsic camera parameters*/
typedef NS_ENUM (NSInteger, AdobeImageCalibrateType)
{
AdobeImageCalibrateAll /*calibrate both rotation and focal length*/,
AdobeImageCalibrateAllFixCop /*fixes rotation parameters and estimates focal length parameters*/,
AdobeImageCalibrateAllFixK/*fixes the focal length and estimates rotation parameters*/
};

/** The cropping mode to use in an image operation*/
typedef NS_ENUM (NSInteger, AdobeImageCropType)
{
AdobeImageNoCrop /*no Crop*/,
AdobeImageCropToFit /*crop to fit*/,
AdobeImageSmartFillCrop/*smart fill*/
};

/** The sorting used while outputing top crop suggestions*/
typedef NS_ENUM (NSInteger, AdobeImageAutoCropSortType)
{
AdobeImageSortOnAll /* Sort based on overall score */,
AdobeImageSortOnComposition /* Sort based on composition score */,
AdobeImageSortOnSaliency /* Sort based on saliency score */,
AdobeImageSortOnCutThrough /* Sort based on cutThrough score */
};

/** The fill mode to use in an image operation*/
typedef NS_ENUM (NSInteger, AdobeImageFillType)
{
AdobeImageRegularFill,
AdobeImageGBFill /*Fill with gain / bias*/,
AdobeImageGBLFill /*Fill with gain / bias and local search*/,
AdobeImageLBCFill /*Fill the whole with low boundary condition*/,
};

/** bit field to specify what type of rendition to export for each layer. Any combination of layers types can be specified */
typedef NS_OPTIONS (NSUInteger, AdobeImageExportLayerType)
{
AdobeImageExportLayerComposite            = (1 << 0),
AdobeImageExportLayerUnmasked            = (1 << 1),
AdobeImageExportLayerPixelMask            = (1 << 2),
AdobeImageExportLayerVectorMask            = (1 << 3)
};

/**
* The fit mode used to scale an image if height and width produce a different aspect ratio
* than the original image
*/
typedef NS_ENUM (NSInteger, AdobeImageFitType)
{
AdobeImageFit,
AdobeImageConstrain,
AdobeImageCrop,
AdobeImageWrap,
AdobeImageStretch,
AdobeImageHFit,
AdobeImageVFit
};

/**
* Provides an Objective-C binding of the Creative Cloud Image Service API.
* Must be initialized with an instance of AdobeNetworkHTTPService, which in turn provides the configuration
* necessary to speak to a specific CC environment (e.g., stage or production).
* See AdobeImageSession:initWithHTTPService.
*/

@interface AdobeImageSession : AdobeCloudServiceSession <AdobePSDSessionProtocol>

/**
* brief Legacy service endpoint.
*/
+ (AdobeCloudEndpoint *)serviceEndpoint;

/**
* brief Automatically finds out top crop candidates for the specified image
*
* param image           The input image for the autoCrop operation.
*
* param numSuggestions  specifies number of suggested crop rectangles. If perAspectRatio is true, then t
*
* param faceDetect      enables or disables use of face detection when suggestion automatic crop rectangles.
* With face detection enabled automatic crop would keep faces in the cropped regions.
*
* param aspectRatios    Each crop suggestions will have one of specified aspect ratios.
*
* param perAspectRatio  If we have numSuggestions="4" and 7 aspect Ratios on total, we'll get 28 crop suggestions, 4 for each given aspect Ratio, in order. If its false, we get 4 suggestions, which could be from one or more of these aspect ratios, based on scores
*
* parqam sortType       The sorting used while outputing top crop suggestions
*
* param output          If 'none', no results are generated. Otherwise, crop suggestion rectangles and their scores are outputted.
*
* param priority        The relative priority of the HTTP request.
*
* param queue           If not nil queue determines the operation queue handler gets executed on.
*
* param handler         Called when the upload has finished, failed or if it has been cancelled.
*
* return                A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*
*/

- (AdobeNetworkHTTPRequest *)autoCrop:(AdobeStorageResourceItem *)image
numSuggestions:(int)numSuggestions
detectFaces:(BOOL)detectFaces
aspectRatios:(NSArray *)aspectRatios
perAspectRatio:(BOOL)perAspectRatio
sortType:(AdobeImageAutoCropSortType)sortType
output:(AdobeImageOutputParameters *)outputParameters
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionHandler:(AdobeImageRequestCompletionHandler)handler;


/**
* brief Calculates an autotone correction for the specified image and optionally applies it.
*
* param image        The input image for the autotone operation.
*
* param faceDetect   Search for faces and take them into account in the operation.
*
* param exportCurve  If true, the autotone curve data will be available as an array of 256 numbers
*                   in the response data, under the key 'autotoneLUT'.
*
* param output       If 'none', curve is not applied and image is not generated. Otherwise, the curve
*                   is applied and the output is either downloaded or available by reference, as specified.
*
* param priority     The relative priority of the HTTP request.
*
* param queue        If not nil queue determines the operation queue handler gets executed on.
*
* param handler      Called when the upload has finished, failed or if it has been cancelled.
*
* return             A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
*                   priority of the request and to cancel it.
*
*/

- (AdobeNetworkHTTPRequest *)autoTone:(AdobeStorageResourceItem *)image
detectFaces:(BOOL)detectFaces
exportCurve:(BOOL)exportCurve
output:(AdobeImageOutputParameters *)outputParameters
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionHandler:(AdobeImageRequestCompletionHandler)handler;


/**
* brief Calculates a leveling transformation for the specified image and optionally applies it.
*
* param image       The input image for the upright operation.
*
* param adjust      The type of Image adjustment to use.
*
* param calibrate    The calibration mode to use in determining intrinsic camera parameters: 3-D rotation and effective x and y focal lengths.
*
* param focalLength  Focal length of camera lens.
*
* param faceDetect   enables or disables use of face detection when doing upright correction.
* With face detection enabled upright correction will try to minimize distortion of face regions in the image.
*
* parqam crop       The cropping mode to use.
*
* param output       If 'none', upright is not applied and image is not generated. Otherwise,
* the upright is applied and the output is either downloaded or available by reference, as specified.
*
* param priority     The relative priority of the HTTP request.
*
* param queue        If not nil queue determines the operation queue handler gets executed on.
*
* param handler      Called when the upload has finished, failed or if it has been cancelled.
*
* return             A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*
*/

- (AdobeNetworkHTTPRequest *)upright:(AdobeStorageResourceItem *)image
adjust:(AdobeImageAdjustType)adjust
calibrate:(AdobeImageCalibrateType)calibrate
focalLength:(float)focalLength
detectFaces:(BOOL)detectFaces
crop:(AdobeImageCropType)crop
output:(AdobeImageOutputParameters *)outputParameters
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionHandler:(AdobeImageRequestCompletionHandler)handler;


/**
* brief         Calculates and applies deblur for input image.
*
* param image        The input image for the autotone operation.
*
* param noiseLevel	 noise level [0-3]. A value of 0 causes auto calculation by deblur
*
* param kernelSize	kernel size. A value of 0 causes auto calculation by deblur
*
* param maxKernels	Maximum number of result images.
*
* param output       Deblur is applied and the output is either downloaded or available by reference, as specified. Value 'none' not allowed.
*
* param priority     The relative priority of the HTTP request.
*
* param queue        If not nil queue determines the operation queue handler gets executed on.
*
* param handler      Called when the upload has finished, failed or if it has been cancelled.
*
* return             A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*
*/

- (AdobeNetworkHTTPRequest *)deblur:(AdobeStorageResourceItem *)image
noiseLevel:(int)noiseLevel
kernelSize:(int)kernelSize
maxKernels:(int)maxKernels
kernelIndex:(int)kernelIndex
optimized:(BOOL)optimized
output:(AdobeImageOutputParameters *)outputParameters
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionHandler:(AdobeImageRequestCompletionHandler)handler;

/**
* brief Performs a content aware fill which requires an input mask in addition to the input image.
*
* param image        The input image for the autotone operation.
*
* param maskImage    The input image of CAF mask.
*
* param fillType	 Specify the type of content-aware fill.
*
* param output       If 'none', does not output final output. Otherwise, auto fill
* is applied and the output is either downloaded or available by reference, as specified.
*
* param nnfOutput	 If 'none', do not output the intermediate NNF data file.  Otherwise, the nnf file is either downloaded or available by reference, as specified. Patchmatch can use this information to generate the final output result.
*
* param priority     The relative priority of the HTTP request.
*
* param queue        If not nil queue determines the operation queue handler gets executed on.
*
* param handler      Called when the upload has finished, failed or if it has been cancelled.
*
* return             A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*
*/

- (AdobeNetworkHTTPRequest *)contentAwareFill:(AdobeStorageResourceItem *)image
maskImage:(AdobeStorageResourceItem *)mask
fillType:(AdobeImageFillType)fillType
output:(AdobeImageOutputParameters *)outputParameters
nnfOutput:(AdobeImageOutputParameters *)nnfOutput
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionHandler:(AdobeImageRequestCompletionHandler)handler;

/**
* brief Generates a description of the PSD file in form of a dictionary that is derived from Graphite
* JSON data for the given PSD.
*
* param psd         The PSD file to describe.
*
* param layerCompId Applies LayerComp based upon ID
*
* param output      Specifies whether to downloaded the result or store on server.
*
* param priority    The relative priority of the HTTP request.
*
* param queue       If not nil queue determines the operation queue handler gets executed on.
*
* param handler     Called when the upload has finished, failed or if it has been cancelled.
*
* return            A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
*                  priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)describePSD:(AdobeStorageResourceItem *)psd
layerCompId:(NSNumber *)layerCompId
output:(AdobeImageOutputParameters *)outputParameters
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionHandler:(AdobeImageRequestCompletionHandler)handler;

#pragma mark DCX

/**
* brief Converts the PSD at psdHref into a composite at compositeHref and returns the manifest resource.
*
* param resource        A resource describing the manifest on the server.
* param psdHref         The href of the PSD on the server.
* param compositeHref   The href where the resulting composite should be stored. This is the parent directory
*                      of the composite directory.
* param priority        The priority of the HTTP request.
* param errorPtr        An optional pointer to an NSError object that will be set in case of an error.
*
* return                On success the updated resource for the manifest. Nil on failure.
*/
- (AdobeStorageResourceItem *)getManifest:(AdobeStorageResourceItem *)resource
fromPSDAt:(NSString *)psdHref
andCompositeAt:(NSString *)compositeHref
requestPriority:(NSOperationQueuePriority)priority
withError:(NSError **)errorPtr;

/**
* brief Update or create a PSD along with its composite representation from an in-memory manifest
* asynchronously.
*
* param psdHref         The href of the PSD on the server.
* param resource        The manifest resource to upload.
* param compositeHref   The href where the resulting composite is/should be stored. This is the parent
* directory of the composite directory.
* param priority        The priority of the HTTP request.
* param queue           Optional parameter. If not nil queue determines the operation queue handler
* gets executed on.
* param handler         Called when the upload has finished or failed.
*
* note On success reosurce gets copied, updated with the new etag, version, length, md5 values and
* passed to the completion handler.
*
* return          A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)updatePSDAt:(NSString *)psdHref
withManifest:(AdobeStorageResourceItem *)resource
andCompositeAt:(NSString *)compositeHref
overwriteExisting:(BOOL)overwrite
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionHandler:(AdobeDCXPSDResourceRequestCompletionHandler)handler;


/**
* brief Asynchronously create an Illustrator file from an array of AdobeStorageResourceItems.
*
* param outputAI         Describes the location of the resulting file.
* param images          An array of AdobeStorageResourceItems of type SVG, JPEG, or PNG to create the
* Illustrator file.
* param priority        The priority of the HTTP request.
* param queue           Optional parameter. If not nil queue determines the operation queue handler
* gets executed on.
* param handler         Called when the upload has finished or failed.
*
* return          A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)createAI:(AdobeImageOutputParameters *)outputAI
withImages:(NSArray *)images
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionHandler:(AdobeImageRequestCompletionHandler)handler;


/**
* brief Returns a rendition from a PSD file
*
* param image       The PSD whose rendition is being requested
*
* param layerID     Specific PSD layer to be rendered
*                      if ID refers to a layer group then composite of group is returned
*                      if nil then entire PSD is rendered
*
* param scale       Scale of returned image
*
* param width       Max width of image
*
* param height      Max height of image
*
* param fitMode     Describes how image is scaled to fit width and height if aspect ratio differs from the original image
*
* param crop        NOT SUPPORTED YET
*
* param layerCompIndex  Applies LayerComp based upon index.  Legal values are 0..n where n is less than the number of layer comps in the PSD.  Applying layer LayerComp defines the visible layers before rendering.
*
* param layerCompID     Applies LayerComp based upon ID.  Ignored if layerCompIndex is specified.
*
* param layerCompName   Applies LayerComp based upon name.  Ignored if layerCompIndex or layerCompID are defined.
*
* param layerIDs    Defines the list of layers that are visible.  Al unspecified layers will be invisible.  Parent layers of specific children will also be visible.  Ignored if layerCompIndex, layerCompID, or layerCompName are defined.
*
* param output      Describes output options for the resulting rendition.
*
* param priority    The relative priority of the HTTP request.
*
* param queue       If not nil queue determines the operation queue handler gets executed on.
*
* param handler     Called when the upload has finished, failed or if it has been cancelled.
*
* return            A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request andcancel it.
*
*/
- (AdobeNetworkHTTPRequest *)render:(AdobeStorageResourceItem *)image
layerID:(NSNumber *)layer
layerName:(NSString *)layerName
scale:(NSNumber *)scale
width:(NSNumber *)width
height:(NSNumber *)height
fitMode:(AdobeImageFitType *)fit
crop:(NSArray *)crop
layerCompIndex:(NSNumber *)layerCompIndex
layerCompID:(NSNumber *)layerCompID
layerCompName:(NSString *)layerCompName
layerIDs:(NSArray *)layerIDs
layerTypes:(AdobeImageExportLayerType)exportLayerTypes
output:(AdobeImageOutputParameters *)outputParameters
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionHandler:(AdobeImageRequestCompletionHandler)handler;

#pragma mark AGC
#ifndef DMALIB

/**
* brief Asynchronously create an AI (Illustrator) file as specified by a AGC manifest.
*
* param output          The output file.
* param manifest        The AGC manifest used to create the AI file on Adobe Creative Cloud.
* param imageComponents An array of AdobeAGCImageComponent objects.
* Only image/jpg and image/png are supported content types.
* param overwrite       In the case of a new AI file, whether it should overwrite an already existing
* composite.
* param priority        The priority of the HTTP request.
* param queue           Optional parameter. If not nil queue determines the operation queue handler
* gets executed on.
* param handler         Called when the upload has finished or failed.
*
* return          A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)createAI:(AdobeStorageResourceItem *)output
agcManifest:(AdobeAGCManifest *)manifest
imageComponents:(NSArray *)imageComponents
overwrite:(BOOL)overwrite
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionHandler:(AdobeImageResourceRequestCompletionHandler)handler;

/**
* brief Asynchronously create a PSD (Photoshop) file as specified by a AGC manifest.
*
* param output          The output file.
* param manifest        The AGC manifest used to create the PSD file on Adobe Creative Cloud.
* param imageComponents An array of AdobeAGCImageComponent objects.
* Only image/jpg and image/png are supported content types.
* param overwrite       In the case of a new PSD file, whether it should overwrite an already existing
* composite.
* param priority        The priority of the HTTP request.
* param queue           Optional parameter. If not nil queue determines the operation queue handler
* gets executed on.
* param handler         Called when the upload has finished or failed.
*
* return          A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)createPSD:(AdobeStorageResourceItem *)output
agcManifest:(AdobeAGCManifest *)manifest
imageComponents:(NSArray *)imageComponents
overwrite:(BOOL)overwrite
requestPriority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionHandler:(AdobeImageResourceRequestCompletionHandler)handler;

#endif // DMALIB

@end

#endif
