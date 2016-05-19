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

#ifndef AdobeNetworkBackgroundTransferHeader
#define AdobeNetworkBackgroundTransferHeader

#import <Foundation/Foundation.h>

@protocol AdobeNetworkBackgroundTransferManagerDelegate <NSObject>
@optional

/**
*  Informs the delegate that a download task has completed in the background. The file at fileURL must be opened or
*  copied immediately upon receipt of this method.
*
*  @param identifier The background configuration identifier for the underlying NSURLSession
*  @param fileURL    The temporary URL from which the file may be opened or copied.
*  @param error      An error or nil on success.
*/
- (void)backgroundDownloadCompletedForSessionWithIdentifier:(NSString *)identifier
temporaryFileURL:(NSURL *)fileURL
error:(NSError *)error;

/**
*  Informs the delegate that an upload completed in the background.
*
*  @param url        The remote URL to which the file was uploaded
*  @param identifier The background configuration identifier for the underlying NSURLSession
*  @param error      An error or nil on success.
*/
- (void)backgroundUploadToURL:(NSURL *)url completedForSessionWithIdentifier:(NSString *)identifier
error:(NSError *)error;

/**
*  Called when all background tasks for a given session have completed. Useful for performing any final cleanup before
*  the system suspends the app.
*
*  @param identifier The identfiier of the underlying NSURLSession.
*/
- (void)allBackgroundTasksCompletedForSessionWithIdentifier:(NSString *)identifier;

@end

@interface AdobeNetworkBackgroundTransferManager : NSObject

@property (nonatomic, weak) id<AdobeNetworkBackgroundTransferManagerDelegate>delegate;
@property (nonatomic, assign) BOOL enableBackgroundTransfers;
+ (instancetype)sharedManager;

+ (BOOL)isCreativeSDKBackgroundIdentifier:(NSString *)identifier;

- (void)unRegisterSessionWithIdentifier:(NSString *)identifier;
- (NSURLSession *)backgroundSessionWithConfiguration:(NSURLSessionConfiguration *)configuration delegate:(id <NSURLSessionDelegate>)delegate delegateQueue:(NSOperationQueue *)queue;
- (void)invalidateSessionWithIdentifierIfNecessary:(NSString *)identifier;

- (void)handleBackgroundEventsForSessionWithIdentifier:(NSString *)identifier
completionHandler:(void (^)(void))completionHandler;

- (void)finishHandlingEventsForSessionWithIdentifier:(NSString *)sessionIdentifier;

@end

#endif
