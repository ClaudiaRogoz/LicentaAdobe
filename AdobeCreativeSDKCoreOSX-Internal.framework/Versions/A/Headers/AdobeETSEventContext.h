/*************************************************************************
*
* ADOBE CONFIDENTIAL
* ___________________
*
* Copyright 2015 Adobe Systems Incorporated
* All Rights Reserved.
*
* NOTICE: All information contained herein is, and remains
* the property of Adobe Systems Incorporated and its suppliers,
* if any. The intellectual and technical concepts contained
* herein are proprietary to Adobe Systems Incorporated and its
* suppliers and are protected by trade secret or copyright law.
* Dissemination of this information or reproduction of this material
* is strictly forbidden unless prior written permission is obtained
* from Adobe Systems Incorporated.
**************************************************************************/

#ifndef AdobeETSEventContextHeader
#define AdobeETSEventContextHeader

#import <Foundation/Foundation.h>

@class AdobeETSEvent;

/**
* brief Type defining the signature of a data provider for a newly created context event.
*/
typedef NSDictionary *(^AdobeETSContextEventDataProvider)();

/**
* brief Provides methods to report ETS events that will be marked as belonging to the same context and will
* be stamped with the correct context sequence number.
*/
@interface AdobeETSEventContext : NSObject

-(instancetype)initWithContextEventType:(NSString*)contextEventType andDataProvider:(AdobeETSContextEventDataProvider)dataProvider;
-(void)closeContextWithDataProvider:(AdobeETSContextEventDataProvider)dataProvider;

-(void)reportEventWithType:(NSString*)eventType andDataProvider:(AdobeETSContextEventDataProvider)dataProvider;
-(NSString*)createEventWithType:(NSString*)eventType andDataProvider:(AdobeETSContextEventDataProvider)dataProvider;
-(void)updateEvent:(NSString*)eventId withDataProvider:(AdobeETSContextEventDataProvider)dataProvider;
-(void)finalizeEvent:(NSString*)eventId withDataProvider:(AdobeETSContextEventDataProvider)dataProvider;

@end

#endif
