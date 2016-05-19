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

#ifndef AdobeDCXPublishSessionProtocolHeader
#define AdobeDCXPublishSessionProtocolHeader

#import <Foundation/Foundation.h>

@protocol AdobePublicationRecordProtocol;
@class AdobeNetworkHTTPRequest;
@class AdobeDCXCompositeBranch;

typedef void (^AdobeDCXPublishHrefCompletionHandler)(NSString *href, NSError *error);

/**
* Defines the protocol that a session has to implement in order to be used as a session for the
* publish methods of AdobeDCXCompositeXfer.
*/
@protocol AdobeDCXPublishSessionProtocol <NSObject>

/**
* brief Given the composite and publication record returns the composite href that can be used to for (re-)publishing.
* Returns a request object only if it actually needs to make a request. Otherwise it returns nil.
*/
-(AdobeNetworkHTTPRequest*)getPublishHrefOfComposite:(AdobeDCXComposite *)composite
fromPublicationRecord:(id<AdobePublicationRecordProtocol>)publicationRecord
andPreviouslyPublishedComposite:(AdobeDCXComposite *)prevPublishedComposite
requestPriority:(NSOperationQueuePriority)priority
etsContext:(AdobeDCXXferETSContext*)etsContext
handlerQueue:(NSOperationQueue *)queue
completionHandler:(AdobeDCXPublishHrefCompletionHandler)handler;

-(AdobeNetworkHTTPRequest*)publishCompositeUploadedTo:(NSString*)resourcesHref
ofType:(NSString*)compositeType
withPublicationRecordData:(NSDictionary*)pubRecordData
requestPriority:(NSOperationQueuePriority)priority
etsContext:(AdobeDCXXferETSContext*)etsContext
handlerQueue:(NSOperationQueue *)queue
completionHandler:(AdobeDCXPublishHrefCompletionHandler)handler;

-(AdobeNetworkHTTPRequest*)updateCompositePublishedAt:(NSString*)assetHref
withPublicationRecordData:(NSDictionary*)pubRecordData
requestPriority:(NSOperationQueuePriority)priority
etsContext:(AdobeDCXXferETSContext*)etsContext
handlerQueue:(NSOperationQueue *)queue
completionHandler:(AdobeDCXPublishHrefCompletionHandler)handler;

typedef void (^AdobeDCXPublicationRecordDataCompletionHandler)(NSDictionary *pubRecordData, NSError *error);

- (AdobeNetworkHTTPRequest *)updatePublicationRecordData:(NSDictionary *)pubRecordData
withPushedCompositeBranch:(AdobeDCXCompositeBranch*)pushedBranch
requestPriority:(NSOperationQueuePriority)priority
etsContext:(AdobeDCXXferETSContext*)etsContext
handlerQueue:(NSOperationQueue *)queue
completionHandler:(AdobeDCXPublicationRecordDataCompletionHandler)handler;

@optional
-(NSString*)getPublishedAssetIdFromAssetHref:(NSString*)href;

@end

#endif
