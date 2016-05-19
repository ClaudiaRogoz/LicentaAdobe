/*************************************************************************
*
* ADOBE CONFIDENTIAL
* ___________________
*
*  Copyright 2013 Adobe Systems Incorporated
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

#ifndef AdobeStorageSessionPrivateHeader
#define AdobeStorageSessionPrivateHeader

#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeStorageSession.h>

extern const NSInteger DEFAULT_202_DELAY_SECS;

@class AdobeNetworkHTTPRequest;
@class AdobeStorageResource;
@class AdobeNetworkHTTPResponse;
@class AdobeStorageModel;
@class AdobeETSEventContext;

/**
* brief Exposes private helper methods and ivars to the different categories of AdobeStorageCCSession.
*/
@interface AdobeStorageSession ()

/**
* brief Construct a mutable URL request for the given resource.
*
* param resource        The resource to construct the request for.
* param method          The HTTP method to use. E.g. @"GET", @"PUT"
* param etagHeaderField If not nil and if the resource has an etag property it will be copied to
*                      this header field of the request.
* param setContentType  Determines whether the resource's content type should be copied to the Content-Type
*                      header of the request.
*
* return                The newly constructed URL request.
*/
- (NSMutableURLRequest *)requestFor:(AdobeStorageResource *)resource
withMethod:(NSString *)method
etagHeaderField:(NSString *)etagHeaderField
setContentType:(BOOL)setContentType;


/**
* brief Construct a mutable URL request for the given resource.  Same as above method except for the
* addition of the link argument
*
*
* param resource        The resource to construct the request for.
* param method          The HTTP method to use. E.g. @"GET", @"PUT"
* param etagHeaderField If not nil and if the resource has an etag property it will be copied to
* this header field of the request.
* param setContentType  Determines whether the resource's content type should be copied to the Content-Type
* header of the request.
* param link            Link header argument
*
* return                The newly constructed URL request.
*/
- (NSMutableURLRequest *)requestFor:(AdobeStorageResource *)resource
withMethod:(NSString *)method
etagHeaderField:(NSString *)etagHeaderField
setContentType:(BOOL)setContentType
link:(NSString *)linkHeader;


/**
* brief Construct a mutable URL request for the given resource.  Same as the first requestFor method above
* except for the addition of the xUpdateValues and ignoreCache arguments
*
* param resource        The resource to construct the request for.
* param method          The HTTP method to use. E.g. @"GET", @"PUT"
* param etagHeaderField If not nil and if the resource has an etag property it will be copied to
* this header field of the request.
* param setContentType  Determines whether the resource's content type should be copied to the Content-Type
* header of the request.
* param xUpdateValues   An array of string to be included in the optional X-Update header field
* param ignoreCache     Instruct the OS network stack not to return cached HTTP responses for this request
*
* return                The newly constructed URL request.
*/
- (NSMutableURLRequest *)requestFor:(AdobeStorageResource *)resource
withMethod:(NSString *)method
etagHeaderField:(NSString *)etagHeaderField
setContentType:(BOOL)setContentType
xUpdateValues:(NSArray *)xUpdateValues
ignoreCache:(BOOL)ignoreCache;


/**
* brief Starts an asynchronous request using the proper method for the request.
*
* param request  The request to get the response for.
* param path     The file to upload from or download to. Can be nil.
* param data     The data to upload. Can be nil. Ignored if path is set.
* param priority The priority of the HTTP request.
* param handler  Called when the upload has finished or failed.
*/
- (AdobeNetworkHTTPRequest *)getResponseFor:(NSMutableURLRequest *)request
streamToOrFrom:(NSString *)path
data:(NSData *)data
requestPriority:(NSOperationQueuePriority)priority
completionHandler:(void (^)(AdobeNetworkHTTPResponse *response))handler;


/**
* brief Starts an asynchronous request using the proper method for the request.
*
* param request  The request to get the response for.
* param path     The file to upload from or download to. Can be nil.
* param data     The data to upload. Can be nil. Ignored if path is set.
* param priority The priority of the HTTP request.
* param options  The options for the http request.
* param handler  Called when the upload has finished or failed.
*/
- (AdobeNetworkHTTPRequest *)getResponseFor:(NSMutableURLRequest *)request
streamToOrFrom:(NSString *)path
data:(NSData *)data
requestPriority:(NSOperationQueuePriority)priority
options:(NSDictionary*)options
completionHandler:(void (^)(AdobeNetworkHTTPResponse *response))handler;

/**
* Gets the response of the specified request synchronously.
*
* Regardless of delays, this method blocks until HTTP request has completed.
*
* @param request  The request to get the response for.
* @param path     The file to upload from or download to. Can be @c nil.
* @param data     The data to upload. Can be @c nil. Ignored if @c path is set.
* @param priority The priority of the HTTP request.
*
* @return The response
*/
- (AdobeNetworkHTTPResponse *)getResponseFor:(NSMutableURLRequest *)request
streamToOrFrom:(NSString *)path
data:(NSData *)data
requestPriority:(NSOperationQueuePriority)priority;


/**
* brief Asynchronously handles a 202 response for a data request by polling its designated href according to the specified retry interval
*
* param response    The 202 response returned by the original request
* param request     The original data request
* param defaultSecsToWaitForRetry   Time to wait before sending the next if the 202 response does not include a 'retry-after' header
* param etsContext    Optional. If provided method will emit ETS event for any polling requests.
* param handler     A block to call upon request completion
*
*/
- (void)    handle202Response:(AdobeNetworkHTTPResponse *)response
forDataRequest:(AdobeNetworkHTTPRequest *)request
defaultSecsToWaitForRetry:(NSUInteger)retryAfter
etsContext:(AdobeETSEventContext*)etsContext
completionHandler:(void (^)(AdobeNetworkHTTPResponse *response))handler;


/**
* brief Constructs an error for the response.
*
* param response The response.
* param path     Optional file path which will be recorded in the error.
* param details  Optional string that will be recorded in the error.
*
* return The newly constructed error.
*/
- (NSError *)errorFromResponse:(AdobeNetworkHTTPResponse *)response andPath:(NSString *)path details:(NSString *)details;

/**
* Calls handler on the given queue if that is not nil. Otherwise calls handler directly.
*
* param handler  The completion handler to call.
* param queue    The queue to call the completion handler on. Can be nil.
* param data     The resource to pass to the handler. Can be nil.
* param error    The error to pass to the handler. Can be nil.
*/
- (void)callCompletionHandler:(AdobeStorageDataRequestCompletionHandler)handler onQueue:(NSOperationQueue *)queue
withData:(NSData *)data andError:(NSError *)error;

/**
* Calls handler on the given queue if that is not nil. Otherwise calls handler directly.
*
* param handler  The completion handler to call.
* param queue    The queue to call the completion handler on. Can be nil.
* param resource The resource to pass to the handler. Can be nil.
* param error    The error to pass to the handler. Can be nil.
*/
- (void)callCompletionHandler:(AdobeStorageResourceRequestCompletionHandler)handler onQueue:(NSOperationQueue *)queue
withResource:(AdobeStorageResourceItem *)resource andError:(NSError *)error;


/**
* Calls handler on the given queue if that is not nil. Otherwise calls handler directly.
*
* param handler  The completion handler to call.
* param queue    The queue to call the completion handler on. Can be nil.
* param resource The resource to pass to the handler. Can be nil.
* param error    The error to pass to the handler. Can be nil.
*/
- (void)callCompletionHandler:(AdobeStorageCollectionRequestCompletionHandler)handler onQueue:(NSOperationQueue *)queue
withCollection:(AdobeStorageResourceCollection *)collection andError:(NSError *)error;

@end

#endif
