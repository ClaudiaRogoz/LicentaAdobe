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

#ifndef AdobeSendToDesktopHeader
#define AdobeSendToDesktopHeader

/**
 * A string representing a key for the NSString name of the item to share.
 * The key/value pair is passed to sendMethod as part of the shareItem NSDictionary.
 * The name will be appended the ".PNG" extension when opened on the desktop app.
 */
extern NSString *const kAdobeSendToDesktopApplicationItemKeyName;

/**
 * A string representing a key for the UIImage of the shareItem.
 * The key/value pair is passed to sendMethod as part of the shareItem NSDictionary.
 */
extern NSString *const kAdobeSendToDesktopApplicationItemKeyImage;


/**
 * Specifies the desktop application the content will be sent to.
 */
typedef NS_ENUM (NSInteger, AdobeCreativeCloudApplication)
{
    /** Unknown */
    AdobeUnknownCreativeCloud = 0,
    /** Photoshop */
    AdobePhotoshopCreativeCloud,
    /** Illustrator */
    AdobeIllustratorCreativeCloud,
    /** InDesign */
    AdobeInDesignCreativeCloud
};

/**
 * Forward class declarations.
 */
@class AdobeAssetFile;


/**
 * Interface for sending assets to desktop applications. This lets an application send assets to the user's
 * desktop machine. Currently Adobe Photoshop, Illustrator, and InDesign are supported.
 */
@interface AdobeSendToDesktopApplication : NSObject

/**
 * Sends an UIImage object to the specified desktop application.  The object is opened as a file with the name provided
 * and the .PNG extnsion.  This is an asynchronous command.
 *
 * @param image The image to be sent to the desktop application.
 * @param application Destination application.
 * @param name The file name on the destination application.  The .PNG extension will be added.
 * @param successBlock Block to be executed on a successful send operation.
 * @param progressBlock Optionally track the upload progress.
 * @param cancellationBlock Optionally be notified of a cancellation on upload.
 * @param errorBlock Block to be executed when on error.
 *
 * @return  Request token.  It can be used to cancel or change the priority of the request.
 */
+ (id)   sendImage:(UIImage *)image
     toApplication:(AdobeCreativeCloudApplication)application
          withName:(NSString *)name
         onSuccess:(void (^)(void))successBlock
        onProgress:(void (^)(double fractionCompleted))progressBlock
    onCancellation:(void (^)(void))cancellationBlock
           onError:(void (^)(NSError *error))errorBlock;

/**
 * Sends an NSData object to the specified desktop application.  The object is opened as a file with the name and
 * extension provided.  This is an asynchronous command.
 * This method is intended for cases where the data to send is not already in a file, e.g., when downloading a file
 * from the web and saving it as NSData.  If the file is already on the Creative Cloud use sendAsset.  If the file
 * is local on the device, use sendLocalFile.
 *
 * @param data The data object to be sent to the desktop application.
 * @param mimeType The data object mime type.  For mime types known to the SDK, this will create the extension of
 * the file opened on the destination application.
 * @param application Destination application.
 * @param name The file name on the destination application.  It must include an extension consistent with the application.
 * @param successBlock Block to be executed on a successful send operation.
 * @param progressBlock Optionally track the upload progress.
 * @param cancellationBlock Optionally be notified of a cancellation on upload.
 * @param errorBlock Block to be executed when on error.
 *
 * @return  Request token.  It can be used to cancel or change the priority of the request.
 */
+ (id)    sendData:(NSData *)data
          withType:(NSString *)mimeType
     toApplication:(AdobeCreativeCloudApplication)application
          withName:(NSString *)name
         onSuccess:(void (^)(void))successBlock
        onProgress:(void (^)(double fractionCompleted))progressBlock
    onCancellation:(void (^)(void))cancellationBlock
           onError:(void (^)(NSError *error))errorBlock;

/**
 * Sends a Creative Cloud file to the specified desktop application.  The object is opened as a file with the same name
 * and extension as the source file.  This is an asynchronous command.
 *
 * @param asset The Creative Cloud asset to be sent to the desktop application.  For asset mimetypes known to the SDK
 * this will create the extension of the file opened on the destination application.
 * @param application Destination application.
 * @param name The name of the file when opened on the destination application.  It must include an extension consistent
 * with the application.  If name is nil, use the asset name.
 * @param successBlock Block to be executed on a successful send operation.
 * @param progressBlock Optionally track the upload progress.
 * @param cancellationBlock Optionally be notified of a cancellation on upload.
 * @param errorBlock Block to be executed when on error.
 *
 * @return  Request token.  It can be used to cancel or change the priority of the request.
 */
+ (id)   sendAsset:(AdobeAssetFile *)asset
     toApplication:(AdobeCreativeCloudApplication)application
          withName:(NSString *)name
         onSuccess:(void (^)(void))successBlock
        onProgress:(void (^)(double fractionCompleted))progressBlock
    onCancellation:(void (^)(void))cancellationBlock
           onError:(void (^)(NSError *error))errorBlock;

/**
 * Sends a local file to the specified desktop application.  The object is opened as a file with the same name
 * and extension as the source file.  This is an asynchronous command.
 *
 * @param filePath The local file to be sent to the desktop application.
 * @param fileType The mime type of the local file.  For mime types known to the SDK, this will create the extension of
 * the file opened on the destination application.
 * @param application Destination application.
 * @param name The name of the file when opened on the destination application.  It must include an extension consistent
 * with the application.  If name is nil, use the filePath.
 * @param successBlock Block to be executed on a successful send operation.
 * @param progressBlock Optionally track the upload progress.
 * @param cancellationBlock Optionally be notified of a cancellation on upload.
 * @param errorBlock Block to be executed when on error.
 *
 * @return  Request token.  It can be used to cancel or change the priority of the request.
 */
+ (id)sendLocalFile:(NSURL *)filePath
           withType:(NSString *)fileType
      toApplication:(AdobeCreativeCloudApplication)application
           withName:(NSString *)name
          onSuccess:(void (^)(void))successBlock
         onProgress:(void (^)(double fractionCompleted))progressBlock
     onCancellation:(void (^)(void))cancellationBlock
            onError:(void (^)(NSError *error))errorBlock;


/**
 * Cancel a send to desktop request.
 *
 * @param requestToken  The send to desktop request to be cancelled.
 */
+ (void)cancelSendToDesktopRequest:(id)requestToken;

/**
 * Change the priority of a send to desktop request.
 *
 * @param requestToken  The send to desktop request to be reprioritized.
 * @param priority  The request new priority.
 */
+ (void)changeSendToDesktopRequestPriority:(id)requestToken
                                  priority:(NSOperationQueuePriority)priority;


@end

#endif
