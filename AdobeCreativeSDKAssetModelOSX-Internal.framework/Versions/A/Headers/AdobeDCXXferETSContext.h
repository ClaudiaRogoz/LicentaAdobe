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

#ifndef AdobeDCXXferETSContextHeader
#define AdobeDCXXferETSContextHeader

@class AdobeDCXComposite;
@class AdobeDCXManifest;
@class AdobeDCXComponent;
@class AdobeNetworkHTTPRequest;
@class AdobeNetworkHTTPResponse;

@protocol AdobeDCXTransferSessionProtocol;

@interface AdobeDCXXferETSContext : AdobeETSEventContext

#pragma mark - Component

-(NSString*)createXferHttpEventOfType:(NSString*)type forComponent:(AdobeDCXComponent*)component
urlRequest:(NSURLRequest*)request priority:(NSOperationQueuePriority)priority
andSession:(id<AdobeDCXTransferSessionProtocol>)session;

-(void)finalizeXferHttpEvent:(NSString*)etsEventId forComponent:(AdobeDCXComponent*)component
withResponse:(AdobeNetworkHTTPResponse*)response requestId:(NSString*)requestId
andError:(NSError*)error;

#pragma mark - Manifest

-(NSString*)createXferHttpEventOfType:(NSString*)type forManifest:(AdobeDCXManifest*)manifest
urlRequest:(NSURLRequest*)request priority:(NSOperationQueuePriority)priority
andSession:(id<AdobeDCXTransferSessionProtocol>)session;

-(void)finalizeXferHttpEvent:(NSString*)etsEventId forManifest:(AdobeDCXManifest*)manifest
withResponse:(AdobeNetworkHTTPResponse*)response requestId:(NSString*)requestId
size:(NSNumber*)manifestSize md5:(NSString*)md5 andError:(NSError*)error;

#pragma mark - Composite

-(NSString*)createXferHttpEventOfType:(NSString*)type forComposite:(AdobeDCXComposite*)composite
urlRequest:(NSURLRequest*)request priority:(NSOperationQueuePriority)priority
andSession:(id<AdobeDCXTransferSessionProtocol>)session;

-(void)finalizeXferHttpEvent:(NSString*)etsEventId forComposite:(AdobeDCXComposite*)composite
withResponse:(AdobeNetworkHTTPResponse*)response requestId:(NSString*)requestId
andError:(NSError*)error;

#pragma mark - Publication Record

-(NSString*)createXferHttpEventOfType:(NSString*)type forAssetId:(NSString*)assetId withContentType:(NSString*)contentType
urlRequest:(NSURLRequest*)request priority:(NSOperationQueuePriority)priority
andSession:(id<AdobeDCXTransferSessionProtocol>)session;

-(void)finalizeXferHttpEvent:(NSString*)etsEventId forAssetId:(NSString*)assetId
withResponse:(AdobeNetworkHTTPResponse*)response requestId:(NSString*)requestId
size:(NSNumber*)recordSize andError:(NSError*)error;

#pragma mark - Publication Artwork

-(NSString*)createXferHttpEventOfType:(NSString*)type forArtworkWithContentType:(NSString*)contentType
urlRequest:(NSURLRequest*)request priority:(NSOperationQueuePriority)priority
andSession:(id<AdobeDCXTransferSessionProtocol>)session;

-(void)finalizeXferHttpEvent:(NSString*)etsEventId forArtworkWithContentType:(NSString*)contentType
withResponse:(AdobeNetworkHTTPResponse*)response requestId:(NSString*)requestId
size:(NSNumber*)artworkSize md5:(NSString*)md5 andError:(NSError*)error;

@end

#endif
