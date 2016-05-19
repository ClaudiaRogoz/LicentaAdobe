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

#ifndef AdobeAnalyticsSDKReporterHeader
#define AdobeAnalyticsSDKReporterHeader

#import <Foundation/Foundation.h>

#pragma mark Generic and Global Event Properties and Values

// Generic ADB Event Properties
extern NSString *const AdobeAnalyticsKeyADB_EventName;
extern NSString *const AdobeAnalyticsKeyADB_EventAction;
extern NSString *const AdobeAnalyticsKeyADB_EventType;
extern NSString *const AdobeAnalyticsKeyADB_PageName;

// Properties Set for All Creaitve SDK Events
extern NSString *const AdobeAnalyticsKeyADB_ClientId;
extern NSString *const AdobeAnalyticsKeyADB_ProfileId;
extern NSString *const AdobeAnalyticsKeyADB_SDKsUtilized;

// Creative SDK's "isSDKUtilized" Value
extern NSString *const AdobeAnalyticsSDKUtilizedCreativeSDK;

// Profile Id for Unknown User
extern NSString *const AdobeAnalyticsProfileIdUnknown;

// Generic Y/N Values
extern NSString *const AdobeAnalyticsValueYes;
extern NSString *const AdobeAnalyticsValueNo;

#pragma mark Analytics Event: Auth Step

// adb.event.eventInfo.eventName
extern NSString *const AdobeAnalyticsEventNameAuthStep;

// auth report : adb.event.eventInfo.eventAction
extern NSString *const AdobeAnalyticsAuthReportLoginStart;
extern NSString *const AdobeAnalyticsAuthReportValidAuthToken;
extern NSString *const AdobeAnalyticsAuthReportExpiredAuthToken;
extern NSString *const AdobeAnalyticsAuthReportMissingAuthToken;
extern NSString *const AdobeAnalyticsAuthReportLoginAttempt;
extern NSString *const AdobeAnalyticsAuthReportLoginSuccess;
extern NSString *const AdobeAnalyticsAuthReportLoginCancel;
extern NSString *const AdobeAnalyticsAuthReportLoginFailure;
extern NSString *const AdobeAnalyticsAuthReportLogoutAttempt;
extern NSString *const AdobeAnalyticsAuthReportLogoutSuccess;
extern NSString *const AdobeAnalyticsAuthReportLogoutCancel;
extern NSString *const AdobeAnalyticsAuthReportLogoutFailure;

// auth status : adb.user.profile.attributes.authStatus
extern NSString *const AdobeAnalyticsKeyADB_AuthStatus;
extern NSString *const AdobeAnalyticsAuthStatusLoggedInOnline;
extern NSString *const AdobeAnalyticsAuthStatusLoggedInOffline;
extern NSString *const AdobeAnalyticsAuthStatusLoggedOutOnline;
extern NSString *const AdobeAnalyticsAuthStatusLoggedOutOffline;

#pragma mark Analytics Event: Registration Step

// adb.event.eventInfo.eventName
extern NSString *const AdobeAnalyticsEventNameRegStep;

// registration report : adb.event.eventInfo.eventAction
extern NSString *const AdobeAnalyticsRegReportSignupStart;
extern NSString *const AdobeAnalyticsRegReportSignupSuccess;
extern NSString *const AdobeAnalyticsRegReportSignupCancel;
extern NSString *const AdobeAnalyticsRegReportSignupFailure;

// registration status : adb.user.profile.attributes.regStatus
extern NSString *const AdobeAnalyticsKeyADB_RegStatus;
extern NSString *const AdobeAnalyticsRegStatusNotRegistered;
extern NSString *const AdobeAnalyticsRegStatusGuestAccount;
extern NSString *const AdobeAnalyticsRegStatusAdobeAccountFree;
extern NSString *const AdobeAnalyticsRegStatusAdobeAccountPaid;

#pragma mark Analytics Event: Pen Connect

// adb.event.eventInfo.eventName
extern NSString *const AdobeAnalyticsEventNamePenConnect;

#pragma mark Analytics Event: Sharing Action

// adb.event.eventInfo.eventName
extern NSString *const AdobeAnalyticsEventNameSharingAction;

// share report : adb.event.eventInfo.eventAction
extern NSString *const AdobeAnalyticsShareTypeProductShares;
extern NSString *const AdobeAnalyticsShareTypeProductSaves;
extern NSString *const AdobeAnalyticsShareTypeContentPublishes;
extern NSString *const AdobeAnalyticsShareTypeContentDownloads;
extern NSString *const AdobeAnalyticsShareTypeComments;
extern NSString *const AdobeAnalyticsShareTypeProjectURLShares;
extern NSString *const AdobeAnalyticsShareTypeSocialShares;
extern NSString *const AdobeAnalyticsShareTypePublishSuccess;
extern NSString *const AdobeAnalyticsShareTypePublishFailure;
extern NSString *const AdobeAnalyticsShareTypePublishUXStart;
extern NSString *const AdobeAnalyticsShareTypePublishUXCancel;

// share target : adb.event.eventInfo.type
extern NSString *const AdobeAnalyticsShareTargetFacebook;
extern NSString *const AdobeAnalyticsShareTargetTwitter;
extern NSString *const AdobeAnalyticsShareTargetPinterest;
extern NSString *const AdobeAnalyticsShareTargetYouTube;
extern NSString *const AdobeAnalyticsShareTargetCameraRoll;
extern NSString *const AdobeAnalyticsShareTargetPhotoshop;
extern NSString *const AdobeAnalyticsShareTargetIllustrator;
extern NSString *const AdobeAnalyticsShareTargetMessage;
extern NSString *const AdobeAnalyticsShareTargetEmail;
extern NSString *const AdobeAnalyticsShareTargetInstagram;
extern NSString *const AdobeAnalyticsShareTargetBehanceProject;
extern NSString *const AdobeAnalyticsShareTargetBehanceWIP;
extern NSString *const AdobeAnalyticsShareTargetPremierePro;
extern NSString *const AdobeAnalyticsShareTargetCreativeCloud;
extern NSString *const AdobeAnalyticsShareTargetCCV;
extern NSString *const AdobeAnalyticsShareTargetPrint;
extern NSString *const AdobeAnalyticsShareTargetCopyUrlToClipboard;
extern NSString *const AdobeAnalyticsShareTargetInDesign;
extern NSString *const AdobeAnalyticsShareTargetLightroom;
extern NSString *const AdobeAnalyticsShareTargetPDF;
extern NSString *const AdobeAnalyticsShareTargetMuse;

/**
* brief A convenience wrapper class that for sending "Creative SDK" analytic events.
*
* The AdobeAnalyticsSDKReporter class will automatically add all "Creative SDK" fields
* that can and must be included for every event type. It automatically grabs the
* AdobeAnalyticsSession singleton instance, adds the required fields to the 'data'
* passed in from the caller, and then passes the event and its data on to the analytics
* session.
*/
@interface AdobeAnalyticsSDKReporter : NSObject

#pragma mark Auth Event Tracking Methods

/**
* brief Reports an "auth step" event.
*/
+ (void)trackAuthStep:(NSString *)authStep adobeID:(NSString *)adobeID;

/**
* brief Reports a "registration step" event (i.e., signup).
*/
+ (void)trackRegStep:(NSString *)regStep adobeID:(NSString *)adobeID;

#pragma mark Sharing Event Tracking Methods

+ (void)trackSharingAction:(NSString *)shareType shareTarget:(NSString *)shareTarget;

#pragma mark Generic Event Tracking Methods

/**
* brief Reports the data for an analytics "state" event customized for the Creative SDK.
*
* param state The name of the state event being reported.
* param data The data associated with the action.
*/
+ (void)trackState:(NSString *)state data:(NSDictionary *)data;

/**
* brief Reports the data for an analytics "action" event customized for the Creative SDK.
*
* param action The name of the action event being reported.
* param data The data associated with the action.
*/
+ (void)trackAction:(NSString *)action data:(NSDictionary *)data;

/**
* brief Reports the data for an analytics "timed action start" event customized for the Creative SDK.
*
* param action The name of the timed action event being reported.
* param data The data associated with the action.
*/
+ (void)trackTimedActionStart:(NSString *)action data:(NSDictionary *)data;

/**
* brief Reports the data for an analytics "timed action update" event customized for the Creative SDK.
*
* param action The name of the timed action event being reported.
* param data The data associated with the action.
*/
+ (void)trackTimedActionUpdate:(NSString *)action data:(NSDictionary *)data;

/**
* brief Reports the data for an analytics "timed action end" event customized for the Creative SDK.
*
* param action The name of the timed action event being reported.
* param block If you provide block, you will have access to the final time values and be
* able to manipulate data prior to sending the final hit. If you provide block, you must
* return YES to send a hit. Passing in nil for block sends the final hit.
*/
+ (void)trackTimedActionEnd:(NSString *)action logic:(BOOL (^) (NSTimeInterval inAppDuration,
NSTimeInterval totalDuration,
NSMutableDictionary *data))block;

@end

#endif
