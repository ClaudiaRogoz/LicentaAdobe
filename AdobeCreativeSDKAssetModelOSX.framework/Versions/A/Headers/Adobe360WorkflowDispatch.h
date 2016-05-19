/*************************************************************************
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
* suppliers and are protected by all applicable intellectual property 
* laws, including trade secret and copyright laws.
* Dissemination of this information or reproduction of this material
* is strictly forbidden unless prior written permission is obtained
* from Adobe Systems Incorporated.
**************************************************************************/

/**************************************************************************
 * [PRIVATE BETA] CreativeSync enables seamless multi-app workflows via
 * the included APIs. If you have any questions, please contact us at
 * https://creativesdk.zendesk.com/hc/en-us/requests/new
 *************************************************************************/

#ifndef Adobe360WorkflowDispatchHeader
#define Adobe360WorkflowDispatchHeader

#import <Foundation/Foundation.h>

@class Adobe360Message;
@class Adobe360MessageBuilder;
@class Adobe360WorkflowAction;
@class Adobe360ApplicationProperties;

extern NSString *const Adobe360WorkflowActionInitiatedNotification;
extern NSString *const Adobe360WorkflowActionCompletedNotification;
extern NSString *const Adobe360WorkflowActionCanceledNotification;
extern NSString *const Adobe360WorkflowActionErrorNotification;

extern NSString *const Adobe360MessageNotificationUserInfoKey;

extern NSString *const Adobe360MessageResponseTypeError;
extern NSString *const Adobe360MessageResponseTypeCanceled;
extern NSString *const Adobe360MessageResponseTypeComplete;


/**
 * This will be the lowest level integration point of the workflow. 
 * It's responsible for setting up and implementing the transport across the 
 * application boundary. 
 *
 * The integrating application will be utilizing this from the application delegate level to process the URLs 
 * and send the appropriate notifications.
 *
 * This can also be utilized directly in addition to the Adobe360WorkflowStorage and Adobe360WorkflowActionDataSource 
 * to support explicit actions and/or custom UI without the use
 * the use of the view controllers for workflows.
 * 
 * @see Adobe360WorkflowStorage
 * @see Adobe360WorkflowActionDataSource
 */
@interface Adobe360WorkflowDispatch : NSObject

/**
 * Returns the singleton Adobe360WorkflowDispatch.
 */
+ (instancetype)sharedDispatch;

/**
 * The application properties for the current application. For the 
 * dispatch to work correctly, this must be populated by the integrating application.
 * 
 * @see Adobe360ApplicationProperties
 */
@property (nonatomic, strong) Adobe360ApplicationProperties *currentAppProperties;

/**
 * The NSOperationQueue that the dispatch object will use for asynchronous calls.
 * All handlers will be called using the dispatch_queue_t's thread.
 *
 * The default value of this will be [NSOperationQueue mainQueue].
 *
 * @param operationQueue The NSOperationQueue for all asynchronous processing
 */
@property (nonatomic, strong) NSOperationQueue *asynchronousOperationQueue;

/**
 * A utility routine for creating and populating a message builder object
 * based on an action. This will set up the state needed to perform the 
 * transport across the application boundary and roundtrip the message back.
 *
 * This utility can be used by a primary application that would like to 
 * avoid using the Adobe360ActionViewController.
 *
 * @param action The action to convert into the message.
 * @return The message builder ready to initiate that action.
 * @see Adobe360MessageBuilder
 * @see Adobe360WorkflowAction
 */
+ (Adobe360MessageBuilder *)messageBuilderFromWorkflowAction:(Adobe360WorkflowAction *)action;


/**
 * A utility routine for creating and populating a complete message builder response
 * from the initial message. This will set up the state needed to send this reply
 * across the application boundary. This message builder can be edited 
 * to add the outputs and other response state before dispatching.
 *
 * This utility can be used by a secondary application that would like to
 * avoid using the Adobe360StatusBarViewController.
 *
 * @param message The initial message to create the response for. This will be 
 * supplied in the Adobe360WorkflowActionInitiatedNotification notification sent by
 * this dispatch object.
 * @return The completed response message builder.
 * @see Adobe360MessageBuilder
 * @see Adobe360Message
 */
+ (Adobe360MessageBuilder *)completedMessageBuilderFromInitialMessage:(Adobe360Message *)message;

/**
 * A utility routine for creating and populating a canceled message builder response
 * from the initial message. This will set up the state needed to send this reply
 * across the application boundary. This message builder can be edited
 * to add the outputs and other response state before dispatching.
 *
 * This utility can be used by a secondary application that would like to
 * avoid using the Adobe360StatusBarViewController.
 *
 * @param message The initial message to create the response for. This will be
 * supplied in the Adobe360WorkflowActionInitiatedNotification notification sent by
 * this dispatch object.
 * @return The canceled response message builder.
 * @see Adobe360MessageBuilder
 * @see Adobe360Message
 */
+ (Adobe360MessageBuilder *)canceledMessageBuilderFromInitialMessage:(Adobe360Message *)message;

/** 
 * Used in the integrating application's UIApplicationDelegate object. This is used to determine whether
 * the URL supplied is a well formed 360 workflow URL.
 *
 * @param url The url to verify.
 * @return YES if the url is a well-formed 360 Workflow inter-application message.
 */
- (BOOL)canProcessURL:(NSURL *)url;

/**
 * Used in the integrating application's UIApplicationDelegate object. This used to convert the 360 Workflow 
 * URL into an Adobe360Message object. This will utilize NSNotificationCenter and send a notification containing
 * the message object back to your application.
 *
 * Additionally, the message will be passed back to your completion handler in case you are not in a position to
 * handle the notifications. The message will be nil if the message could not be processed.
 *
 * @param url The url to verify.
 * @param completetionHandler A completion handler for determining when the message preparation is complete. May be nil.
 * @return An NSProgress object tracking the progress of the url processing and message creation.
 */
- (NSProgress *)processURL:(NSURL *)url completionHandler:(void (^)(Adobe360Message *message, NSError *error))handler;

/** 
 * Primarily used by the workflow 360 UX elements; however, this routine can be called explicitly by the integrating application
 * when initiating the workflow UX.
 *
 * @param messageBuilder A message builder object constructed using one of the above routines.
 * @param urlScheme The url scheme of the receiving application.
 * @param completionHandler The completion handler to be called upon sending of the message or error.
 * @return An NSProgress object tracking the progress of the url processing and message sending.
 */
- (NSProgress *)dispatchMessage:(Adobe360MessageBuilder *)messageBuilder urlScheme:(NSString *)urlScheme completionHandler:(void (^)(BOOL success, NSError *error))handler;

/**
 * Primarily used by the workflow 360 UX elements; however, this routine can be called explicitly by the integrating application
 * when initiating the workflow UX.
 *
 * @param messageBuilder A message builder object constructed using one of the above routines. Must not be nil.
 * @param urlScheme The url scheme of the receiving application. Must not be nil.
 * @param appGroup The app group supported by the receiving application. Can be nil.
 * @param completionHandler The completion handler to be called upon sending of the message or error. May be nil.
 * @return An NSProgress object tracking the progress of the url processing and message sending.
 */
- (NSProgress *)dispatchMessage:(Adobe360MessageBuilder *)messageBuilder urlScheme:(NSString *)urlScheme appGroup:(NSString *)appGroup completionHandler:(void (^)(BOOL success, NSError *error))handler;

/**
 * Primarily used by the workflow 360 UX elements; however, this routine can be called explicitly by the integrating application
 * when responding to an existing message without using the workflow UX.
 *
 * @param messageBuilder A message builder object constructed using one of the above routines. Must not be nil.
 * @param completionHandler The completion handler to be called upon sending of the message or error. May be nil.
 * @return An NSProgress object tracking the progress of the url processing and message sending.
 */
- (NSProgress *)respondWithMessage:(Adobe360MessageBuilder *)messageBuilder completionHandler:(void (^)(BOOL success, NSError *error))handler;

/**
 * A routine to return a diagnostic string useful for debugging issues while developing
 * against the 360 Workflow API.
 *
 * It uses the current state of the dispatch object and the details in the message to
 * diagnose whether the message is safe to send.
 *
 * This is meant to be a purely debug routine and should not be used for any dynamic decisions.
 *
 * @param messageBuilder The message builder object to test.
 * @return A detailed log of warnings about the current state of the dispatch and message
 */
- (NSString *)diagnosticReportStringForMessage:(Adobe360MessageBuilder *)messageBuilder;

/**
 * A routine to pre-download all the action registries and app icons then put them in cache
 * This should be called as soon as the app is launched,
 *     that way when 360 is launched there is no delay in displaying the app icons
 */
- (void)preloadActionRegistriesAndAppIcons;

@end

#endif
