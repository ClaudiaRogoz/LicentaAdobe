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

// Reviewed by rhorns on October 11, 2013

#ifndef AdobeNetworkHTTPServiceHeader
#define AdobeNetworkHTTPServiceHeader

#import <Foundation/Foundation.h>

@class AdobeNetworkHTTPResponse;
@class AdobeNetworkHTTPRequest;
@protocol AdobeNetworkHTTPBodyStreamFactory;

/** The number of units of work we add to each http request progress to account for misc
* work after completion and to avoid premature completion of a progress object if the request fails
* after send all its data. */
extern int64_t const AdobeNetworkHTTPProgressCompletionFudge;

/** Strings that may be used as keys for the 'options' dictionary that is an optional parameter of
* the getResponseFor... methods */

/** Corresponding value is a NSDate object identifying the minimum time to wait before sending request */
extern NSString *const AdobeNetworkOptNoSoonerThanDate;
/** Correponding value is an AdobeNetworkHTTPRequest object that is reused for the new request */
extern NSString *const AdobeNetworkOptReuseExistingRequest;

/** Corresponding value is a AdobeNetworkErrorResponse object that will contain ERD meta data */
extern NSString *const AdobeNetworkOptErrorResponseDocument;

/** If the 'options' dictionary contains a value for this key then the request will not be canceled
once it is in progress. */
extern NSString *const AdobeNetworkOptDisallowCancelOnceInProgress;

@protocol AdobeNetworkHTTPServiceDelegate;
@protocol AdobeNetworkHTTPServiceEventRecorderProtocol;

/**
* AdobeNetworkHTTPService represents a specific instance of a service, such as the CC storage service.
* It provides the base URI of the service, and allows any necessary customization.
*
* Service session objects, like AdobeStorageSession, are configured with one of
* these in order to connect to a specific environment, such as staging or production.
*
* ### Threading
*
* Methods on this class may be invoked on any thread. Instances of this manage one thread for
* each allowed concurrent request. (See setConcurrentRequest: count for information on this
* property.)
*/
@interface AdobeNetworkHTTPService : NSObject <NSURLSessionDataDelegate, NSURLSessionDownloadDelegate, NSURLSessionTaskDelegate, NSURLSessionDelegate>

/**
* Initializer for normal (non-background transfer) sessions.
*
* @param url The base url of the service, e.g., https://creative.adobe.com
* @param applicationName The name of the application.
* @param additionalHTTPHeaders Any kvp that are to be added to the HTTP headers.
*/
- (instancetype)initWithUrl:(NSURL *)url andApplication:(NSString *)applicationName additionalHTTPHeaders:(NSDictionary *)additionalHTTPHeaders;

/**
* Initializer for normal (non-background transfer) sessions.
*
* @param url                   The base url of the service, e.g., https://creative.adobe.com
* @param applicationName       The name of the application.
* @param userAgent             A custom user-agent string to use on all requests.
* @param additionalHTTPHeaders Any kvp that are to be added to the HTTP headers.
*/
- (instancetype)initWithUrl:(NSURL *)url application:(NSString *)applicationName userAgent:(NSString *)userAgent additionalHTTPHeaders:(NSDictionary *)additionalHTTPHeaders;

/**
* Designated initializer.
*
* @param url                   The base url of the service, e.g., https://creative.adobe.com
* @param applicationName       The name of the application.
* @param userAgent             A custom user-agent string to use on all requests.
* @param additionalHTTPHeaders Any kvp that are to be added to the HTTP headers.
* @param backgroundIdentifier  A unique string that can be used with an NSURLSession background configuration.
* @param sessionDelegate       An NSURLSessionDelegate used for retrieving files downloaded in the background. If set,
*                              block callbacks will be ignored and the caller is responsible for handling errors and
*                              response data via this delegate. If left nil, defaults to this instance of
*                              AdobeNetworkHTTPService--block callbacks will work as a result.
*
* @discussion NSURLSession only supports to/from file uploads/downloads for background tasks; data-only tasks are not
* supported. In addition, the block-based convenience methods can not be relied upon since the app's process may be
* killed entirely prior to background tasks completing. The aforementioned fact is the reason why this initializer
* parameterizes the NSURLSession's delegate.
* @see https://developer.apple.com/library/ios/documentation/Cocoa/Conceptual/URLLoadingSystem/Articles/UsingNSURLSession.html#//apple_ref/doc/uid/TP40013509-SW44
* for more details on NSURLSession background transfers.
*
* @return A newly initialized instance of AdobeNetworkHTTPService.
*/
- (instancetype)initWithUrl:(NSURL *)url
application:(NSString *)applicationName
userAgent:(NSString *)userAgent
additionalHTTPHeaders:(NSDictionary *)additionalHTTPHeaders
backgroundIdentifier:(NSString *)backgroundIdentifier
sessionDelegate:(id<NSURLSessionDelegate>)sessionDelegate NS_DESIGNATED_INITIALIZER;

/**
* The base URL of this service, e.g., https://creative.adobe.com. All requests are
* resolved relative to this URL, although requests may contain absolute URLs.
*/
@property (nonatomic, readwrite, strong) NSURL *baseURL;

/**
* The number of requests that may be issued to this service in parallel.
* Must be in the range 1-5.
*
* This value can be modified for a service that is in use. Raising the number
* will cause any additional pending requests to be started immediately.
* Lowering the value will not affect already-issued requests, and will cause
* all pending requests to remain queued until the current operation count drops
* below the new limit.
*/
@property NSInteger concurrentRequestCount;

/**
* Whether or not issuing requests to this service is suspended. When the service
* is suspended, new requests can be made but they will only be added to the queue.
*/
@property (getter = isSuspended) BOOL suspended;

/** Set the authentication token to be used with all outgoing requests. */
@property (nonatomic, strong) NSString *authToken;

/**
* Whether or not the service is currently connected. A disconnected service will not try to send new
* requests to the server but rather let them fail with a AdobeStorageErrorServiceDisconnected error.
* A service starts out being connected and will disconnect once the number of recent errors have reached
* the threshold defined by recentErrorThresholdToDisconnect. When this happens the service delegate
* will be notified.
* The delegate then can call reconnect: in order to restart the service.
*/
@property (readonly, getter = isConnected) BOOL connected;

/**
* The number of recent errors that will make the service disconnect itself. Default is 5
*/
@property NSInteger recentErrorThresholdToDisconnect;

/**
* This is an array of NSTimeInterval values. The number and values of the entries determine how often
* and with what length of a delay (in seconds) a request that has failed with a 5xx response code
* will be retried before it fails. Default is @[@0.1, @1, @2] which makes the servive retry these
* requests three times with a delay of 0.1, 1, and 2 seconds on each successive attempt.
*/
@property NSArray *retryOn5xxDelays;

/**
* The primary delegate for this class; it is notified of any authentication
* failures that occur. Notice that this is a weak reference.
*/
@property (weak) id<AdobeNetworkHTTPServiceDelegate> delegate;

/**
* An optional event recorder delegate, implementing the AdobeNetworkHTTPServiceEventRecorderProtocol.
* When set, AdobeNetworkHTTPService will log an event for each HTTP request that's issued.
*/
@property id<AdobeNetworkHTTPServiceEventRecorderProtocol> eventRecorderDelegate;


/**
*  Invalidates this instance of AdobeNetworkHTTPService
*
*  @param shouldCancel If YES, cancels any currently pending requests and invalidates immediately. If NO, the service
*  will be invalidated once all currently pending requests have been made.
*  @note Once invalidated, this instance may no longer be used. Also note that if you pass NO and isSuspended == YES,
*  the service will not be able to invalidate until you set suspended back to NO, allowing queued requests to be flushed.
*/
- (void)invalidateServiceCancelingPendingRequests:(BOOL)shouldCancel;

/**
* Reconnects a disconnected service.
*/
- (void)reconnect;

/**
* Clear the request queue.
*/
- (void)clearQueuedRequests;

/**
* Tests to see if the authentication failure rate is too high.
*
* @return YES if there have been too many authentication failures in the last five minutes.
*/
- (BOOL)hasEncounteredTooManyAuthFailures;

/**
* /brief Issues the given request to this service asynchronously, no sooner than the specified time.
*
* @param request  The request to make.
* @param priority The initial priority of the request.
* @param options  An optional dictionary of additional request options - may be nil.
* See the AdobeNetworkOpt string constants for more details.
* @param handler  Upon completion, the specified handler is invoked; no guarantees are made as to which
*               thread it is invoked on.
*
* @return         A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the priority of
*               the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)getResponseForDataRequest:(NSURLRequest *)request
requestPriority:(NSOperationQueuePriority)priority
options:(NSDictionary *)options
completionHandler:(void (^)(AdobeNetworkHTTPResponse *))handler;

/**
* Issues the given request to this service synchronously, no sooner than the specified time.
*
* @param request The request to make.
* @param priority The priority of the request.
* @param options  An optional dictionary of additional request options - may be nil.
* See the AdobeNetworkOpt string constants for more details.
*
* @return The response.
*
* The request is subject to delay due to the maximum allowed number of concurrent requests, and if
* requests should be paused.
*
* Regardless of delays, this method blocks until the request completes. Upon completion, the service
* response is returned.
*/

- (AdobeNetworkHTTPResponse *)getResponseForDataRequest:(NSURLRequest *)request
requestPriority:(NSOperationQueuePriority)priority
options:(NSDictionary *)options;

/**
* Downloads a file to the given path asynchronously, no sooner than the specified time.
*
* @param request  The request to make.
* @param path     A path including file name that determines where the file will be saved. An existing
*               file at the same location will be overriden.
* @param priority The initial priority of the request.
* @param options  An optional dictionary of additional request options - may be nil.
* See the AdobeNetworkOpt string constants for more details.
* @param handler  Upon completion, the specified handler is invoked; no guarantees are made as to which
*               thread it is invoked on.
*
* @return         A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the priority of
*               the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)getResponseForDownloadRequest:(NSURLRequest *)request toPath:(NSString *)path
requestPriority:(NSOperationQueuePriority)priority
options:(NSDictionary *)options
completionHandler:(void (^)(AdobeNetworkHTTPResponse *))handler;

/**
* Downloads a file to the given path asynchronously, no sooner than the specified time,
* with request body provided by an input stream.
*
* @param request  The request to make.
* @param bodyStreamFactory The request body stream factory
* @param path     A path including file name that determines where the file will be saved. An existing
*              file at the same location will be overriden.
* @param priority The initial priority of the request.
* @param options  An optional dictionary of additional request options - may be nil.
* See the AdobeNetworkOpt string constants for more details.
* @param handler  Upon completion, the specified handler is invoked; no guarantees are made as to which
*                  thread it is invoked on.
*
* @return         A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the priority of
* the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)getResponseForDownloadRequest:(NSURLRequest *)request
withBodyStreamFactory:(id<AdobeNetworkHTTPBodyStreamFactory>)bodyStreamFactory
toPath:(NSString *)path
requestPriority:(NSOperationQueuePriority)priority
options:(NSDictionary *)options
completionHandler:(void (^)(AdobeNetworkHTTPResponse *))handler;

/**
* Downloads a file to the given path synchronously, no sooner than the specified time.
*
* Regardless of delays, this method blocks until the requset completes. Upon completion the
* service response is returned.
*
* @param request  The requst to make.
* @param path     A path including file name that determines where the file will be saved. An
*                 existing file at the same location will be overriden.
* @param priority The initial priority of the request.
* @param options  An optional dictionary of additional request options - may be nil.
* See the AdobeNetworkOpt string constants for more details.
*
* @return The response.
*/
- (AdobeNetworkHTTPResponse *)getResponseForDownloadRequest:(NSURLRequest *)request
toPath:(NSString *)path
requestPriority:(NSOperationQueuePriority)priority
options:(NSDictionary *)options;

/**
* Uploads the file at the given path asynchronously.
*
* @param request  The request to make.
* @param path     A path specifying the file to upload.
* @param priority The initial priority of the request.
* @param options  An optional dictionary of additional request options - may be nil.
* See the AdobeNetworkOpt string constants for more details.
* @param handler  Upon completion, the specified handler is invoked; no guarantees are made as to which
*               thread it is invoked on.
*
* @return         A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the priority of
*               the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)getResponseForUploadRequest:(NSURLRequest *)request fromPath:(NSString *)path
requestPriority:(NSOperationQueuePriority)priority
options:(NSDictionary *)options
completionHandler:(void (^)(AdobeNetworkHTTPResponse *))handler;

/**
* Uploads the file at the given path synchronously.
*
* Regardless of delays, this method blocks until the request completes. Upon completion the
* service response is returned.
*
* @param request  The request to make.
* @param path     A path specifying the file to upload.
* @param priority The initial priority of the request.
* @param options  An optional dictionary of additional request options - may be nil.
* See the AdobeNetworkOpt string constants for more details.
*
* @return The response
*/
- (AdobeNetworkHTTPResponse *)getResponseForUploadRequest:(NSURLRequest *)request
fromPath:(NSString *)path
requestPriority:(NSOperationQueuePriority)priority
options:(NSDictionary *)options;

/**
* Uploads data from the input stream created by the bodyStreamFactory asynchronously.
*
* @param request  The request to make.
* @param bodyStreamFactory The request body stream factory
* @param priority The initial priority of the request.
* @param options  An optional dictionary of additional request options - may be nil.
* See the AdobeNetworkOpt string constants for more details.
* @param handler  Upon completion, the specified handler is invoked; no guarantees are made as to which
*               thread it is invoked on.
*
* @return         A AdobeNetworkHTTPRequest object that can be used to track progress, adjust the priority of
*               the request and to cancel it.
*/

- (AdobeNetworkHTTPRequest *)getResponseForUploadRequest:(NSURLRequest *)request
withBodyStreamFactory:(id<AdobeNetworkHTTPBodyStreamFactory>)bodyStreamFactory
requestPriority:(NSOperationQueuePriority)priority
options:(NSDictionary *)options
completionHandler:(void (^)(AdobeNetworkHTTPResponse *))handler;

@end

#endif
