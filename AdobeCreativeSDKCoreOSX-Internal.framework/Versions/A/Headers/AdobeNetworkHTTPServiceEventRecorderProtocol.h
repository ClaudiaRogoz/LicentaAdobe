/*************************************************************************
*
* ADOBE CONFIDENTIAL
* ___________________
*
*  Copyright 2013 Adobe Systems Incorporated
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

// Reviewed by rhorns on October 14, 2013

#ifndef AdobeNetworkHTTPServiceEventRecorderProtocolHeader
#define AdobeNetworkHTTPServiceEventRecorderProtocolHeader

#import <Foundation/Foundation.h>

@class AdobeNetworkHTTPServiceEvent;

/**
* brief Defines the set of properties and methods necessary for recording DMA analytics events.
*/
@protocol AdobeNetworkHTTPServiceEventRecorderProtocol <NSObject>

/** Allows the service to specify what version of the transfer algorithm is being used. */
@property NSString *algorithmVersion;

/**
* brief Allows the client to encode parameters into the version string that is being sent with
* each event.
*
* parameters A flat key/value list.
*/
- (void)setVersionStringParameters:(NSDictionary *)parameters;

/**
* brief Triggers a new session id to be generated and used in events going forward.
*/
- (void)generateSessionId;

/**
* brief Records an event.
*
* param event The event to record.
*/
- (void)recordHTTPServiceEvent:(AdobeNetworkHTTPServiceEvent *)event;

@end

#endif
