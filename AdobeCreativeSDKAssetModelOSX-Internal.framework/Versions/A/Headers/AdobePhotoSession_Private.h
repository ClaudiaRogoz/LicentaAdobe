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

#ifndef AdobePhotoSessionPrivateHeader
#define AdobePhotoSessionPrivateHeader

#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobePhotoSession.h>

extern NSString *const AdobePhotoSessionCacheID;

@class AdobeNetworkHTTPRequest;
@class AdobeNetworkHTTPResponse;
@class AdobePhoto;

/**
* Exposes private helper methods and ivars to the different categories of AdobePhotoSession.
*/
@interface AdobePhotoSession ()

/**
* Construct a mutable URL request for the given resource.
*
* @param resource        The resource to construct the request for.
* @param method          The HTTP method to use. E.g. @"GET", @"PUT"
* @param setContentType  Determines whether the resource's content type should be copied to the Content-Type
*                      header of the request.
*
*
* @returns               The newly constructed URL request.
*/
- (NSMutableURLRequest *)requestFor:(AdobePhoto *)resource
method:(NSString *)method
contentType:(BOOL)setContentType;


/**
* Construct a mutable URL request for the given resource.  Same as above method except for the
* addition of the setOrdinal argument
*
* @param resource        The resource to construct the request for.
* @param method          The HTTP method to use. E.g. @"GET", @"PUT"
* @param setContentType  Determines whether the resource's content type should be copied to the Content-Type
* header of the request.
* @param xUpdateValues   An array of string to be included in the optional X-Update header field
* @param ignoreCache     Instruct the OS network stack not to return cached HTTP responses for this request
*
* @returns               The newly constructed URL request.
*/
- (NSMutableURLRequest *)requestFor:(AdobePhoto *)resource
method:(NSString *)method
contentType:(BOOL)setContentType
xUpdateValues:(NSArray *)xUpdateValues
ignoreCache:(BOOL)ignoreCache;


/**
* Starts an asynchronous request using the proper method for the request.
*
* @param request  The request to get the response for.
* @param path     The file to upload from or download to. Can be nil.
* @param data     The data to upload. Can be nil. Ignored if path is set.
* @param priority The prioprity of the HTTP request.
* @param handler  Called when the upload has finished or failed.
*/
- (AdobeNetworkHTTPRequest *)responseFor:(NSMutableURLRequest *)request
streamToOrFrom:(NSString *)path
data:(NSData *)data
requestPriority:(NSOperationQueuePriority)priority
completionHandler:(void (^)(AdobeNetworkHTTPResponse *response))handler;

/**
* @param cloud The cloud the entitlements are linked to.
*
* @returns An error if not allowed.
*/
- (NSError *)checkEntitlements;

/**
* Constructs an error for the response.
*
* @param response The response.
* @param path     Optional file path which will be recorded in the error.
* @param details  Optional string that will be recorded in the error.
*
* @returnsThe newly constructed error.
*/
- (NSError *)errorFromResponse:(AdobeNetworkHTTPResponse *)response
path:(NSString *)path details:(NSString *)details;

/**
* Calls handler on the given queue if that is not nil. Otherwise calls handler directly.
*
* @param handler  The completion handler to call.
* @param queue    The queue to call the completion handler on. Can be nil.
* @param data     The resource to pass to the handler. Can be nil.
* @param error    The error to pass to the handler. Can be nil.
*/
- (void)callCompletionHandler:(AdobePhotoDataRequestCompletionHandler)handler
queue:(NSOperationQueue *)queue
data:(NSData *)data
error:(NSError *)error;

/**
* Calls handler on the given queue if that is not nil. Otherwise calls handler directly.
*
* @param handler  The completion handler to call.
* @param queue    The queue to call the completion handler on. Can be nil.
* @param filePath The resource to pass to the handler. Can be nil.
* @param error    The error to pass to the handler. Can be nil.
*/
- (void)callCompletionHandler:(AdobePhotoDataRequestToFileCompletionHandler)handler
queue:(NSOperationQueue *)queue
filePath:(NSString *)filePath
error:(NSError *)error;

/**
* Calls handler on the given queue if that is not nil. Otherwise calls handler directly.
*
* @param handler  The completion handler to call.
* @param queue    The queue to call the completion handler on. Can be nil.
* @param catalog  The resource to pass to the handler. Can be nil.
* @param error    The error to pass to the handler. Can be nil.
*/
- (void)callCompletionHandler:(AdobePhotoCatalogRequestCompletionHandler)handler
queue:(NSOperationQueue *)queue
catalog:(AdobePhotoCatalog *)catalog
error:(NSError *)error;

/**
* Calls handler on the given queue if that is not nil. Otherwise calls handler directly.
*
* @param handler  The completion handler to call.
* @param queue    The queue to call the completion handler on. Can be nil.
* @param catalogs The resource to pass to the handler. Can be nil.
* @param error    The error to pass to the handler. Can be nil.
*/
- (void)callCompletionHandler:(AdobePhotoCatalogsRequestCompletionHandler)handler
queue:(NSOperationQueue *)queue
catalogs:(AdobePhotoCatalogs *)catalogs
error:(NSError *)error;

/**
* Calls handler on the given queue if that is not nil. Otherwise calls handler directly.
*
* @param handler    The completion handler to call.
* @param queue      The queue to call the completion handler on. Can be nil.
* @param collection The resource to pass to the handler. Can be nil.
* @param error      The error to pass to the handler. Can be nil.
*/
- (void)callCompletionHandler:(AdobePhotoCollectionRequestCompletionHandler)handler
queue:(NSOperationQueue *)queue
collection:(AdobePhotoCollection *)collection
error:(NSError *)error;

/**
* Calls handler on the given queue if that is not nil. Otherwise calls handler directly.
*
* @param handler     The completion handler to call.
* @param queue       The queue to call the completion handler on. Can be nil.
* @param collections The resource to pass to the handler. Can be nil.
* @param error      The error to pass to the handler. Can be nil.
*/
- (void)callCompletionHandler:(AdobePhotoCollectionsRequestCompletionHandler)handler
queue:(NSOperationQueue *)queue
collections:(AdobePhotoCollections *)collections
error:(NSError *)error;

/**
* Calls handler on the given queue if that is not nil. Otherwise calls handler directly.
*
* @param handler  The completion handler to call.
* @param queue    The queue to call the completion handler on. Can be nil.
* @param asset    The resource to pass to the handler. Can be nil.
* @param error    The error to pass to the handler. Can be nil.
*/
- (void)callCompletionHandler:(AdobePhotoAssetRequestCompletionHandler)handler
queue:(NSOperationQueue *)queue
asset:(AdobePhotoAsset *)asset
error:(NSError *)error;

/**
* Calls handler on the given queue if that is not nil. Otherwise calls handler directly.
*
* @param handler  The completion handler to call.
* @param queue    The queue to call the completion handler on. Can be nil.
* @param assets   The resource to pass to the handler. Can be nil.
* @param error    The error to pass to the handler. Can be nil.
*/
- (void)callCompletionHandler:(AdobePhotoAssetsRequestCompletionHandler)handler
queue:(NSOperationQueue *)queue
assets:(AdobePhotoAssets *)assets
error:(NSError *)error;

@end

#endif /* ifndef AdobePhotoSessionPrivateHeader */
