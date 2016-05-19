/******************************************************************************
 *
 * ADOBE CONFIDENTIAL
 * ___________________
 *
 * Copyright 2015 Adobe Systems Incorporated
 * All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains the property of
 * Adobe Systems Incorporated and its suppliers, if any. The intellectual and
 * technical concepts contained herein are proprietary to Adobe Systems
 * Incorporated and its suppliers and are protected by trade secret or
 * copyright law. Dissemination of this information or reproduction of this
 * material is strictly forbidden unless prior written permission is obtained
 * from Adobe Systems Incorporated.
 ******************************************************************************/

/**************************************************************************
 * [PRIVATE BETA] CreativeSync enables seamless multi-app workflows via
 * the included APIs. If you have any questions, please contact us at
 * https://creativesdk.zendesk.com/hc/en-us/requests/new
 *************************************************************************/

#ifndef Adobe360WorkflowStorageHeader
#define Adobe360WorkflowStorageHeader

@class Adobe360Message;

/**
 * To access additional information from an Adobe360WorkflowStorageMessageInfo dictionary.
 */
extern NSString *const Adobe360WorkflowStorageUserID;
extern NSString *const Adobe360WorkflowStorageCloudID;
extern NSString *const Adobe360WorkflowStorageState;
extern NSString *const Adobe360WorkflowStorageTimestamp;

/**
 * Stored Adobe360Message additional information.
 */
typedef NSDictionary Adobe360WorkflowStorageMessageInfo;

/**
 * Adobe360WorkflowStorage state constants
 */
typedef NS_ENUM (NSUInteger, Adobe360WorkflowStorageStatus)
{
    Adobe360WorkflowStorageStatusNonExistent = 0,
    Adobe360WorkflowStorageStatusUnhandled   = 1,
    Adobe360WorkflowStorageStatusHandled     = 2,
    Adobe360WorkflowStorageStatusUnmanaged   = 3,
    Adobe360WorkflowStorageStatusInvalid     = 4,
    Adobe360WorkflowStorageStatusCorrupt     = 5,
};

@interface Adobe360WorkflowStorage : NSObject

// Adobe360WorkflowStorage version number.
@property (assign, nonatomic, readonly) NSUInteger versionNumber;


/**
 * The singleton object for the Adobe360WorkflowStorage.
 */
+ (Adobe360WorkflowStorage *)sharedStorage;

/**
 * Add a new message to the storage and set its state to Adobe360WorkflowStorageStatusUnhandled.  Also save the
 * current adobeID, the current cloudID, and a timestamp.
 *
 * This will call the handler on the main thread.
 *
 * @param message Adobe360Message to save.
 * @param userID the adobe profile ID of the user
 * @param cloudID the ID of the current cloud object
 * @param completionHandler Returns the messageID and an error, one of which is nil depending on the action status.
 *      The messageID can be used subsequently to manage the message.
 */
- (void)   addMessage:(Adobe360Message *)message
                 user:(NSString *)userID
                cloud:(NSString *)cloudID
    completionHandler:(void (^)(NSString *messageID, NSError *error))handler;

/**
 * Add a new message to the storage and set its state to Adobe360WorkflowStorageStatusUnhandled.  Also save the
 * current adobeID, the current cloudID, and a timestamp.
 *
 * @param message Adobe360Message to save.
 * @param userID the adobe profile ID of the user
 * @param cloudID the ID of the current cloud object
 * @param handlerQueue the NSOperationQueue used to call the completion handler.
 * @param completionHandler Returns the messageID and an error, one of which is nil depending on the action status.
 *      The messageID can be used subsequently to manage the message.
 */
- (void)   addMessage:(Adobe360Message *)message
                 user:(NSString *)userID
                cloud:(NSString *)cloudID
         handlerQueue:(NSOperationQueue *)queue
    completionHandler:(void (^)(NSString *messageID, NSError *error))handler;

/**
 * Get message status.  The message state is not changed.
 *
 * @param messageID The ID of the message to get a status from.
 * @return A Adobe360WorkflowStorageStatus enum value.
 */
- (Adobe360WorkflowStorageStatus)queryForMessage:(NSString *)messageID;

/**
 * Read a message including its additional information.  The method returns in the completion handler the Adobe360Message
 * and additional information corresponding to the messageID.
 * The message state is not changed.  The error is not nil if an error is detected, in particular if the message is invalid
 * (i.e, the userID or cloud are different from when the message was added).  The completion handler's error contains
 * additional information.
 * 
 * The completionHandler will be called on the main thread.
 *
 * @param messageID The ID of the message to read.
 * @param completionHandler Returns the message, additional message information, and an error.  An error condition is reported
 *      by a non-nil error argument.  The message will be nil if the message is invalid (i.e., if the message's adobeID and
 *      cloudID do not match the current values.
 */
- (void)  readMessage:(NSString *)messageID
    completionHandler:(void (^)(Adobe360Message *message, Adobe360WorkflowStorageMessageInfo *messageInfo, NSError *error))handler;

/**
 * Read a message including its additional information.  The method returns in the completion handler the Adobe360Message
 * and additional information corresponding to the messageID.
 * The message state is not changed.  The error is not nil if an error is detected, in particular if the message is invalid
 * (i.e, the userID or cloud are different from when the message was added).  The completion handler's error contains
 * additional information.
 *
 * @param messageID The ID of the message to read.
 * @param handlerQueue the NSOperationQueue used to call the completion handler.
 * @param completionHandler Returns the message, additional message information, and an error.  An error condition is reported
 *      by a non-nil error argument.  The message will be nil if the message is invalid (i.e., if the message's adobeID and
 *      cloudID do not match the current values.
 */
- (void)  readMessage:(NSString *)messageID
         handlerQueue:(NSOperationQueue *)queue
    completionHandler:(void (^)(Adobe360Message *message, Adobe360WorkflowStorageMessageInfo *messageInfo, NSError *error))handler;

/**
 * Update message, typically with the request's response.  The method returns in the completion handler the previous
 * Adobe360Message corresponding to the messageID.  The message state is updated to Adobe360WorkflowStorageStatusHandled.
 * The message is nil if an error is detected, in particular if the message is invalid (i.e, the userID or cloud are
 * different from when the message was added).  The completion handler's error contains additional information.
 *
 * @param messageID The ID of the message to update.
 * @param newMessage New message to insert in the storage.
 * @param completionHandler Returns the previous message and an error, one of which is nil depending on the action status.
 *      The message will be nil if the message is invalid (i.e., if the message's adobeID and cloudID do not match the
 *      current values.
 */
- (void)updateMessage:(NSString *)messageID
              message:(Adobe360Message *)newMessage
    completionHandler:(void (^)(Adobe360Message *message, NSError *error))handler;

/**
 * Update message, typically with the request's response.  The method returns in the completion handler the previous
 * Adobe360Message corresponding to the messageID.  The message state is updated to Adobe360WorkflowStorageStatusHandled.
 * The message is nil if an error is detected, in particular if the message is invalid (i.e, the userID or cloud are
 * different from when the message was added).  The completion handler's error contains additional information.
 *
 * @param messageID The ID of the message to update.
 * @param newMessage New message to insert in the storage.
 * @param handlerQueue the NSOperationQueue used to call the completion handler.
 * @param completionHandler Returns the previous message and an error, one of which is nil depending on the action status.
 *      The message will be nil if the message is invalid (i.e., if the message's adobeID and cloudID do not match the
 *      current values.
 */
- (void)updateMessage:(NSString *)messageID
              message:(Adobe360Message *)newMessage
         handlerQueue:(NSOperationQueue *)queue
    completionHandler:(void (^)(Adobe360Message *message, NSError *error))handler;

/**
 * Stop managing message.  Set the message state to Adobe360WorkflowStorageUnamanged.  The method returns in the
 * completion handler the current Adobe360Message.
 *
 * The completionHandler will be called on the main thread.
 *
 * @param messageID The ID of the message to unmanage.
 * @param completionHandler Returns the current message and an error, one of which is nil depending on the action status.
 *      The message will be nil if the message is invalid (i.e., if the message's adobeID and cloudID do not match the
 *      current values.
 */
- (void)unmanageMessage:(NSString *)messageID
      completionHandler:(void (^)(Adobe360Message *message, NSError *error))handler;

/**
 * Stop managing message.  Set the message state to Adobe360WorkflowStorageUnamanged.  The method returns in the
 * completion handler the current Adobe360Message.
 *
 * The completionHandler will be called on the main thread.
 *
 * @param messageID The ID of the message to unmanage.
 * @param handlerQueue the NSOperationQueue used to call the completion handler.
 * @param completionHandler Returns the current message and an error, one of which is nil depending on the action status.
 *      The message will be nil if the message is invalid (i.e., if the message's adobeID and cloudID do not match the
 *      current values.
 */
- (void)unmanageMessage:(NSString *)messageID
           handlerQueue:(NSOperationQueue *)queue
      completionHandler:(void (^)(Adobe360Message *message, NSError *error))handler;

/**
 * Delete message.  Remove message from the storage independent of the message state.
 * The method returns NO to indicate an error.  errorPtr contains additional information.
 *
 * @param messageID The ID of the message to delete.
 * @param errorPtr Error pointer with additional information if return value is NO.
 * @return Indication whether operation succeeded.
 */
- (BOOL)deleteMessage:(NSString *)messageID
                error:(NSError **)errorPtr;

/**
 * Get all messages.
 *
 * @param errorPtr Pointer with additional error information.
 * @return An NSDictionary of methodID / message status pairs for all saved messages.  The dictionary includes invalid
 *      messages (i.e., those whose adobeID or cloudID don't match the current values).  nil indicates the
 *      storage is empty or an error occurred.
 */
- (NSDictionary *)allMessages:(NSError **)errorPtr;

/**
 * Return an array of messageIDs that match the given status.  Invalid messages (i.e., messages whose adobeID and cloudID
 * are different from the current values) are not reported unless the status argument is Adobe360WorkflowStorageInvalid.
 * A non-nil errorPtr reports an error.
 *
 * @param status Report messages with this status.
 * @param errorPtr Pointer with additional error information.
 * @return An arry of message IDs that match the given status.  nil indicates no messages with given status
 *      exist or an error occurred.
 */
- (NSArray *)messagesWithStatus:(Adobe360WorkflowStorageStatus)status
                          error:(NSError **)errorPtr;

/**
 * Return an array of messageIDs older than the given date.  Invalid messages are also reported.  A non-nil errorPtr
 * reports an error.
 *
 * @param cutoffDate Report messages older than this date.
 * @param errorPtr Pointer with additional error information.
 * @return An arry of message IDs older than the given date.  nil indicates no messages with given status
 *      exist or an error occurred.
 */
- (NSArray *)messagesOlderThan:(NSDate *)cutoffDate
                         error:(NSError **)errorPtr;

/**
 * Delete all entries in the storage.  Messages are deleted independent of the messages state.
 * The method returns NO to indicate an error.  errorPtr contains additional information.
 *
 * @param errorPtr Error pointer with additional information if return value is NO.
 * @return Indication whether operation succeeded.
 */
- (BOOL)deleteAllMessages:(NSError **)errorPtr;

@end

#endif
