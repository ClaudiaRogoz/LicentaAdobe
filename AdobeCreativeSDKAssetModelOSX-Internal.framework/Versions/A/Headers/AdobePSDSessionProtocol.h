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

#ifndef AdobePSDSessionProtocolHeader
#define AdobePSDSessionProtocolHeader

#import <Foundation/Foundation.h>

@class AdobeDCXComposite;
@class AdobeDCXManifest;
@class AdobeStorageResourceItem;
@class AdobeNetworkHTTPRequest;

/** The generic completion handler for asynchronous resource-based ImageSession requests. */
typedef void (^AdobeDCXPSDResourceRequestCompletionHandler)(AdobeStorageResourceItem *, NSError *);

/**
* Defines the protocol that a session has to implement in order to be used as a session pulling
* a PSD manifest.
*/
@protocol AdobePSDSessionProtocol <NSObject>

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
*                      directory of the composite directory.
* param priority        The priority of the HTTP request.
* param queue           Optional parameter. If not nil queue determines the operation queue handler
*                      gets executed on.
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
@end

#endif
