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

#ifndef AdobeETSEventQueueHeader
#define AdobeETSEventQueueHeader

#import <Foundation/Foundation.h>

/**
* brief Persistent queue for ETS events.
*
* Uses CoreData to store ETS events in a Sqlite database.
*/
@interface AdobeETSEventQueue : NSObject

/**
* brief Type defining the signature of a data provider for a newly created event.
*/
typedef NSDictionary *(^EventDataProvider)();

/**
* brief Type defining the signature of a data updater for an existing created event.
*/
typedef NSDictionary *(^EventDataUpdater)(NSDictionary *existingData);

/**
* brief Type defining the signature of completion handler for a fetch of events.
* Should return YES if it has modified the objects and wants to save the changes.
*/
typedef BOOL (^FetchCompletionHandler)(NSArray *fetchedEvents, NSError *error);

/**
* brief Type defining the signature of completion handler for a fetch of events.
*/
typedef void (^CountCompletionHandler)(NSUInteger count, NSError *error);

/**
* brief Type defining the signature of a completion handler for event deletion.
*/
typedef void (^DeleteCompletionHandler)(NSError *error);

/**
* brief Starts the event queue. Will try to open the cached events database at
* cacheDirPath and create a new one if that fails.
*
* param cacheDirPath A path for a directory where the queue can store its events database.
* param errorPtr Will be set to an error if the database can't be opened or created.
* return YES on success
*/
- (BOOL)startWithCacheDirPath:(NSString*)cacheDirPath withError:(NSError**)errorPtr;

/**
* brief Asynchronously creates a new event and stores it in the queue.
*
* param eventId The id for the new event. Must be unique.
* param finalized Optional. If provided then the event is marked finalized with the given NSDate timestamp.
* param dataProvider Optional. If provided the dataProvider gets called before the event gets stored. It should
*                               return an NSDictionary containing the data for the event.
*/
- (void)queueEventWithId:(NSString*)eventId andFinalTimeStamp:(NSDate*)finalized
andDataProvider:(EventDataProvider)dataProvider;


/**
* brief Asynchronously updates an existing, unfinalized event and stores it in the queue.
*
* This method fails silently if the event with the given eventId either does not exist or is already finalized.
*
* param eventId The id for the event. Must be the eventId of an existing event that hasn't been finalized yet.
* param finalized Optional. If provided then the event is marked finalized with the given NSDate timestamp.
* param dataUpdater Optional. If provided the dataUpdater gets called before the event gets stored. It should
*                               return an NSDictionary containing the (updated) data for the event.
*/
- (void)updateEventWithId:(NSString*)eventId andFinalTimeStamp:(NSDate*)finalized andDataUpdater:(EventDataUpdater)dataUpdater;

/**
* brief Fetches the maxCount (or less) oldest finalized events and returns them to the handler.
*
* param maxCount Limits the maximum number of events returned by the fetch.
* param handler Gets called with the fetched events.
*/
- (void)fetch:(NSUInteger)maxCount oldestFinalizedEventsWithCompletionHandler:(FetchCompletionHandler)handler;

/**
* brief Returns the number of finalized events in the queue.
*
* param handler Gets called with the count.
*/
- (void) countFinalizedEventsWithCompletionHandler:(CountCompletionHandler)handler;

/**
* brief Returns the number of unfinalized events in the queue.
*
* param handler Gets called with the count.
*/
- (void)countUnfinalizedEventsWithCompletionHandler:(CountCompletionHandler)handler;

/**
* brief Fetches maxCount (or less) unfinalized events and returns them to the handler.
*
* param maxCount Limits the maximum number of events returned by the fetch.
* param handler Gets called with the fetched events.
*/
- (void)fetch:(NSUInteger)maxCount unfinalizedEventsWithCompletionHandler:(FetchCompletionHandler)handler;

/**
* brief Remove the given events from the queue.
*
* param events The events to remove.
* param handler Gets called when done.
*/
- (void)removeEvents:(NSArray*)events completionHandler:(DeleteCompletionHandler)handler;

/**
* brief Perform the goven block in the thread/sequential queue that this instance uses.
*/
- (void)performBlock:(void (^)(void))block;

@end

#endif
