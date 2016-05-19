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

#ifndef AdobeDCXComponentManagerProtocolHeader
#define AdobeDCXComponentManagerProtocolHeader

#import <Foundation/Foundation.h>

@class AdobeDCXComponent;
@class AdobeDCXComposite;

typedef void (^ReadyWithFileWithError)(NSString* filePath, NSError* error);
typedef void (^ReadyWithFileWithUCIDWithError) (NSString* filePath, NSString* newUCID, NSError* error);


/**
* Defines a protocol that a Component Manager has to implement, in order to be used as a manager which knows how handle
* the push and pull of component files.
*/
@protocol AdobeDCXComponentManagerProtocol <NSObject>


/**
* brief Request the download location and the new UCID of the component.
*
* param component         : The component whose file is being downloaded
* param composite         : The composite of the component being pulled/downloaded.
* param UCID              : The unmamnaged component identifer, if present, of the component.
* param completionHander  : Handler that will be called when the delegate is ready with the download location and UCID
*
* return void
*
* note: This delegate method will be called for each component that needs to be downloaded because it has been
* modified on the server or does not have a local file. The implemenation should examine the component properties
* and if provided the UCID and determine if the component should stay/become unmanaged and if so should it get downloaded.
* It commnucates this logic back to the pull logic via the completion hander, with the two pieces of information
*  :filePath and newUCID
* if newUCID is nil: the component gets downloaded as a regular managed component, local unmanaged component mapping is updated
* if newUCID is not nil:
*      if downloadTo is nil: the file does not get downloaded, the local unmanaged component is updated with newUCID
*      if downloadTo is not nil: the file gets downloaded to downloadTo location, the local unmanaged component is updated with newUCID
*                              Once the file is downloaded, the didDownloadComponent delegate method gets called
*
* The client can choose to return the same UCID as provided the in the argument as newUCID, or return a new one depending on the client logic.
*
* The completionHandler can be called synchronously or asynchronously. The ongoing pull/download will be waiting on the completionHandler
* to be called. If the completionHandler is not called from the delegate implementation, the download/pull will not complete.
* An error provided in the completionHandler will cause the pull/download to fail
*
* If the client calls the completion handler with an error, there the pull mechanism will not make invoke didDownloadComponent.
* In other words the didDownloadComponent callback will be made if for the completionHandler invocation (UCID != nil &&  downloadTo != nil && error == nil )
*/
-(void) requestFileToDownloadComponent:(AdobeDCXComponent*)component
ofComposite:(AdobeDCXComposite*)composite
withUCID:(NSString*)UCID
withCompletionHandler:(ReadyWithFileWithUCIDWithError) completionHandler;

/**
* brief Inform the delegate of completion of download of component file w/o error

* param component       : The component for which the download actions completed.
* param composite       : The composite of the component being pulled/downloaded.
* param UCID            : The UCID of the component
* param downloadError   : Any error that might have occurred during downloading
* return  void
*
* note The method is for information only. The pull mechanism calls this if the download completed, with an error if there was any.
* e.g. The delegate can use this method for cleanup of any temp files.
*/
-(void) didDownloadComponent:(AdobeDCXComponent*)component
ofComposite:(AdobeDCXComposite*)composite
withUCID:(NSString*)UCID
withError:(NSError*)downloadError;


/**
* brief Request the file to upload the component from.
*
* param component           : The component being uploaded as a part of the push operation
* param composite           : The composite of the component being uploaded
* param UCId                : The UCID of the component being uploaded.
* param completionHandler   : The handler that will be called when the delegate is ready with upload location
*
* note This delegate method gets called during pushComposite whenever the push algorithm encounters a modified or
* new component that has a UCID but no sourceHref. The delegate must make the completionHandler with uploadFrom file path
* or an error.
*
* The completionHandler can be called synchronously or asynchronously. The ongoing push/upload will be waiting on the completionHandler
* to be called. If the completionHandler is not called from the delegate implementation, the upload/push will not complete.
* An error provided in the completionHandler will cause the push/upload to fail.
*
* If the client calls the completion handler with an error, there the push mechanism will not make invoke didDownloadComponent.
* In other words the didUploadComponent callback will be made if for the completionHandler invocation, error == nil
*/
-(void) requestFileToUploadComponent:(AdobeDCXComponent*)component
ofComposite:(AdobeDCXComposite*)composite
withUCID:(NSString*)UCID
withCompletionHandler:(ReadyWithFileWithError) completionHandler;

/**
* brief Notify the delegate that the upload file has completed w/o error.
*
* param component       : The component for which the upload actions completed.
* param composite       : The composite of the component being pushed.
* param UCID            : The UCID of the component
* param downloadError   : Any error that might have occurred during uploading
*
* note This method can be used to clean up any temp files which were used for uploading.
*/
-(void) didUploadComponent:(AdobeDCXComponent*)component
ofComposite:(AdobeDCXComposite*)composite
withUCID:(NSString*)UCID
FromFile:(NSString*)filePath
withError:(NSError*)uploadError;
@end

#endif
