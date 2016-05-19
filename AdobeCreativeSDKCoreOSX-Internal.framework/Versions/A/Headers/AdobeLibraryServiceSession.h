/*************************************************************************
*
* ADOBE CONFIDENTIAL
* ___________________
*
*  Copyright 2015 Adobe Systems Incorporated
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

#ifndef AdobeLibraryServiceSessionHeader
#define AdobeLibraryServiceSessionHeader

#import <Foundation/Foundation.h>

#import <AdobeCreativeSDKCoreOSX-Internal/AdobeCloudServiceSession.h>

@class AdobeNetworkHTTPRequest;
@class AdobeNetworkHTTPService;

/**
* Provides an Objective-C binding of the Library Service API.
* Must be initialized with an instance of AdobeNetworkHTTPService, which in turn provides the configuration
* necessary to speak to a specific CC environment (e.g., stage or production).
* See AdobeLibraryServiceSession:initWithHTTPService.
*/
@interface AdobeLibraryServiceSession : AdobeCloudServiceSession

/**
* Returns an AdobeLibrarySession singleton initialize with endpoint and user token
*/
+ (AdobeLibraryServiceSession *)sharedSession;

/**
* Create a new library.
*
* @param name              The name of the library.
* @param priority          The relative priority of the HTTP request.
* @param queue             If not nil queue determines the operation queue handler gets executed on.
* @param completionBlock   Called when the creation has finished or failed.
*
* @return An AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)createLibrary:(NSString *)libraryName
priority:(NSOperationQueuePriority)priority
handlerQueue:(NSOperationQueue *)queue
completionBlock:(void (^)(NSString *libraryID, NSError *error))completionBlock;

/**
* Get the libraries for the logged in user.
*
* @param priority          The relative priority of the HTTP request.
* @param comparator        Optionally supply a sorting mechanism for the results.
* @param queue             If not nil queue determines the operation queue handler gets executed on.
* @param completionBlock   Called when the fetch has finished or failed.
*
* @return An AdobeNetworkHTTPRequest object that can be used to track progress, adjust the
* priority of the request and to cancel it.
*/
- (AdobeNetworkHTTPRequest *)librariesWithPriority:(NSOperationQueuePriority)priority
sort:(NSComparator)comparator
handlerQueue:(NSOperationQueue *)queue
completionBlock:(void (^)(NSArray *libraries, BOOL changed, NSError *error))completionBlock;

// temporary until we grab the endpoints from the cloud object
- (void)refreshEndpoint;

@end

#endif /* ifndef AdobeLibraryServiceSessionHeader */
