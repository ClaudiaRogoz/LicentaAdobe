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

#ifndef AdobeETSSessionHeader
#define AdobeETSSessionHeader

#import <Foundation/Foundation.h>

extern NSString *AdobeETSTracingKey;

@class AdobeCloud;
@class AdobeNetworkHTTPService;
@class AdobeNetworkHTTPRequest;
@class AdobeNetworkHTTPResponse;

/**
* class AdobeETSSession
* brief A session for ETS analytics
*
* Implements a session through which clients can report ETS events. The event
* reporting methods are implemented to be as light-weight as possible. I.e. they just make a copy
* of any essential data and return. Everything else will happen on a seperate thread.
*
* The ETS session will not trigger any errors. It is a black box and makes no guarantees
* that the events will actually make it to the ETS service. In particular the session
* may be inactive due to an error creating the persistent store but its APIs will
* continue to behave as if everything is OK.
*
* Events get stored in a persistent queue and reported to the service in batches
* whenever the app has network connectivity.
*
* Using [AdobeETSSession sharedSession] clients can either report events after they have
* occurred using [session reportEventWithType:..]. Or if the event represents a longer
* operation they can create a event, update it multiple times and finalize it when it is
* done using createEventWithType:, updateEvent: and finalizeEvent: respectively.
*
* Each event-reporting API comes in two flavors that differ in the way the event data
* is provided. One version takes the data (an NSDictionary) as parameter whereas the other
* accepts a callback that returns the event. The advantage of the latter is that a) the
* callback gets called on a separate thread (thus minimizes the overhead on the main threa)
* and b) the data does not need to get generated if the session turns out to be inactive.
*
*/
@interface AdobeETSSession : NSObject

+ (AdobeETSSession *)sharedSession;

#pragma mark - Manage the Session

/**
* brief Type defining the signature of a completion handler for startWithCacheDirPath:.
*/
typedef void (^AdobeETSSessionStartCompletionHandler)(BOOL, NSError *);

/**
* brief Type defining the signature of a completion handler for stopWithCompletionHandler:.
*/
typedef void (^AdobeETSSessionStopCompletionHandler)();

/**
* brief Starts the session asynchronously.
*
* If this method fails then the session will be in an inactive mode. I.e. all its APIs are no-ops.
*
* You must not call start on a session that is active. If you need to change e.g. the service you must
* first stop the session.
*
* param cacheDirPath The path to a directory that the session's queue will use to persist itself to.
* param service The http service pointing to a valid ETS service instance.
* param handler Gets called upon completion.
*/
- (void)startWithCacheDirPath:(NSString *)cacheDirPath andHTTPService:(AdobeNetworkHTTPService *)service
completionHandler:(AdobeETSSessionStartCompletionHandler)handler;

/**
* brief Stops the session.
*/
- (void)stopWithCompletionHandler:(AdobeETSSessionStopCompletionHandler)handler;

/**
* Call this when the app is about to become inactive/be moved to the background.
*/
- (void)appWillBecomeInactive;

/**
* Call this when the app has become active/ been moved to the foreground.
*/
- (void)appHasBecomeActive;

/**
* Call this when the default clouds has changed.
*/
- (void)defaultCloudHasChanged;

/**
* Call this when the device has gone offline.
*/
- (void)deviceHasGoneOffline;

/**
* Call this when the device has gone online again.
*/
- (void)deviceHasGoneOnline;

/**
* Call this when the app logged out.  The logoutType determines whether the logout was explicit or
* unexpected (possibly due to reauthentication errors).
*/
- (void)loggedOut:(NSString *)logoutType;

/**
* Call this when the user logged in.
*/
- (void)loggedInAs:(NSString *)user;

/**
* Call this when a user signs up.
*/
- (void)signedUpAs:(NSString *)user;

/**
* Call this when one of the auth tokens is updated.  For example, if the access token expired or refreshed,
* of if a token is deleted.  Deleted tokens may lead to unexpected logouts.
*/
- (void)updateToken:(NSString *)actionType
expirationTime:(NSDate *)tokenExpiration
error:(NSError *)error;

/**
* Call this when an endpoint change is detected.
*/
- (void)endpointChangedFrom:(NSNumber *)oldEndpoint
to:(NSNumber *)newEndpoint
onKeychain:(NSString *)keychain;

/**
* Start an SDK component (e.g., 360 Workflows, Stock Browser, Asset Browser, Market Asset Browser) typically
* from a component's icon.
*
* param component     SDK component.
*/
- (void)startSDKComponent:(NSString *)component;

/**
* Start an SDK component (e.g., 360 Workflows, Stock Browser, Asset Browser, Market Asset Browser) typically
* from a component's icon.  Include a context ID that can be used to correlate a sequence of events.  Client is
* responsible for using this context ID in subsequent correlated events.
*
* param component     SDK component.
* param contextID     ID to correlate a sequence of events.
*/
- (void)startSDKComponent:(NSString *)component
withContextID:(NSString *)contextID;

/**
* Close an SDK component (e.g., 360 Workflows, Stock Browser, Asset Browser, Market Asset Browser)
*
* param component         SDK component.
* param userCancelled     YES if user hit Cancel to close the component, NO otherwise.
*/
- (void)closeSDKComponent:(NSString *)component
userCancelled:(BOOL)userCancelled;

/**
* Select an application for a given SDK component.  This is usually triggered from the UI application list.
*
* param application   Target applicaton
* param component     SDK component.
*/
- (void)selectApplication:(NSString *)application
for:(NSString *)component;

/**
* Select an application for a given SDK component.  This is usually triggered from the UI application list.
* Give a context id and a sequence number to correlate to a sequence of events.
*
* param application       Target applicaton
* param applicationID     Target applicaton bundle ID
* param component         SDK component.
* param contextID         ID to correlate a sequnce of events.
* param sequenceNumber    Number in the sequence of events.
*/
- (void)selectApplication:(NSString *)application
appID:(NSString *)applicationID
for:(NSString *)component
context:(NSString *)contextID
sequence:(NSUInteger)sequenceNumber;

/**
* Log the app installed from the App Library.
*
* param application       Name of the app to install.
*/
- (void)openAppStoreFor:(NSString *)application
on:(NSString *)component;

/**
* Log the app installed from the App Library.
* Give a context id and a sequence number to correlate to a sequence of events.
*
* param application       Name of the app to install.
* param applicationID     Bundle ID of the app to install.
* param contextID         ID to correlate a sequnce of events.
* param sequenceNumber    Number in the sequence of events.
*/
- (void)openAppStoreFor:(NSString *)application
appID:(NSString *)applicationID
on:(NSString *)component
context:(NSString *)contextID
sequence:(NSUInteger)sequenceNumber;

/**
* Log a SendToDesktop event.
*
* param fileName      Name of the file to send.  Must include an extension (e.g., .JPEG, .PNG).
* param sendToApp     Application to send the file to.
* param isLocal       Whether file to send is local to the device.
* param fileSize      File size in bytes.
* param serviceURL    URL of the service receiving the send to desktop notifications.
*/
- (void)sendFile:(NSString *)fileName toApplication:(NSString *)sendToApp
local:(BOOL)isLocal size:(NSNumber *)fileSize service:(NSURL *)serviceURL;

/**
* Start a 360 workflow.  Log the outbound message from the primary to the secondary app that starts a 360 workflow.
* The workflow completion is marked by a complete 360 workflow event.
*
* param messageID         Identification for all events related a specific workflow.
* param type              Action type: edit, embed, capture.
* param subtype           More specific information about the event action.
* param targetApp         Secondary app, the workflow target.
* param sequenceNumber    Number in the sequence of events.
*/
- (void)start360WorkflowWithMessage:(NSString *)messageID
actionType:(NSString *)type
actionSubtype:(NSString *)subtype
targetApp:(NSString *)targetApp
targetAppID:(NSString *)targetAppID
sequence:(NSUInteger)sequencenNumber;

/**
* Start a 360 workflow on the secondary app.  The app could have been launched as part of the workflow or be already
* running.
*
* param messageID         Identification for all events related a specific workflow.
* param sequenceNumber    Number in the sequence of events.
* param sourceApp         Primary app, the workflow source.
*/
- (void)start360WorkflowSecondaryAppWithMessage:(NSString *)messageID
sequence:(NSUInteger)sequenceNumber
sourceApp:(NSString *)sourceApp;

/**
* Complete a 360 workflow on the secondary app.
*
* param messageID         Identification for all events related a specific workflow.
* param type              More specific information about the event action.
* param sourceApp         Primary app, the workflow source.
* param sequenceNumber    Number in the sequence of events.
*/
- (void)respond360WorkflowForMessage:(NSString *)messageID
actionType:(NSString *)type
sourceApp:(NSString *)sourceApp
sequence:(NSUInteger)sequenceNumber;

/**
* Complete a 360 workflow.  Primary app received completion notification.
*
* param messageID         Identification for all events related a specific workflow.
* param sequenceNumber    Number in the sequence of events.
*/
- (void)complete360WorkflowForMessage:(NSString *)messageID
sequence:(NSUInteger)sequenceNumber;

/**
* View App Library event
*
* param sortType      App Library sort type.
* param category      App Library category.
*/
- (void)viewAppLibrarySortedBy:(NSString *)sortType
category:(NSString *)category;

/**
* Log the app opened from the App Library.
*
* param appName       Name of the app to open.
*/
- (void)openAppLibraryApp:(NSString *)appName;

/**
* Log a "search Market Asset Browser" event.
*
* param query         Search keyword.
* param category      Market Asset Browser category.
*/
- (void)searchMarketAssetsUsing:(NSString *)query
category:(NSString *)category;

/**
* Log a "view Market Asset Browser" event.
*
* param action        action.
* param sortType      sort type.
* param category      category.
*/
- (void)viewMarketAssetsForAction:(NSString *)action
sortOrder:(NSString *)sortType
category:(NSString *)category;

/**
* Log a "download market asset" event.
*
* param view          View (grid/asset) downloading market asset from.
*/
- (void)downloadMarketAssetFrom:(NSString *)view;

/**
* Log a "view Market Asset Browser user profile" event.
*
* param sortType      Market Asset Browser sort type.
* param category      Market Asset Browser category.
*/
- (void)viewMarketAssetUserProfile;

/**
* View Stock Asset Browser.
*
* param action        Action that triggered the view.
* param sortType      Stock Asset Browser sort type.
* param filter        Stock Asset Browser filter.
* param orientation   Media orientation.  E.g., portrait, landscape, etc.
* param keyword       Stock Asset Browser search keyword.
*/
- (void)viewStockAssetsForAction:(NSString *)action
sortedBy:(NSString *)sortType
filter:(NSString *)filter
orientation:(NSString *)orientation
search:(NSString *)keyword;

/**
* Select an item from the Stock Asset browser.
*
* param action        Action: preview, license, or open.
* param view          View: grid or asset.
* param assetID       Asset ID
* param name          Asset name
* param type          Asset type
*/
- (void)selectStockAssetFor:(NSString *)action
on:(NSString *)view
assetID:(NSUInteger)assetID
assetName:(NSString *)name
assetType:(NSString *)type;

/**
* Extracting layers from a psd file
*
* param psdName       the name of the psd file.
* param error         error extracting psd file if there is any
*/
- (void)extractLayersFromPSDFile:(NSString *)psdName
error:(NSError *)error;

/**
* Send the selected layers in an extracted psd file
*
* param psdName           the name of the psd file.
* param numberOfLayers    number of layers being selected
*/
- (void)sendPSDLayersAfterExtraction:(NSString *)psdName
numberOfLayers:(NSUInteger)numberOfLayers;

/**
* Download a Typekit font to use locally on the device
*
* param componentName     The name of the component that the user is downloading font from
*                              either typekit_font_browser or typekit_font_picker
* param fontName          The name of the downloaded font such as FiraSans-Italic
* param error             error downloading font if there is any
*/
- (void)downloadTypekitFont:(NSString *)componentName
fontName:(NSString *)fontName
error:(NSError *)error;

/**
* Download Typekit fonts from a font family to use locally on the device
*
* param componentName     The name of the component that the user is downloading the fonts from
*                              either typekit_font_browser or typekit_font_picker
* param familyName        The name of the font family such as FiraSans
* param error             error downloading font if there is any
*/
- (void)downloadTypekitFontFamily:(NSString *)componentName
familyName:(NSString *)familyName
error:(NSError *)error;

/**
* Download the font family list metadata from the server based on filter query for the current user
*
* param query                 The filter query to get font family list metadata from the server
* param numberOfFontFamilies  The number of font families being downloaded
* param error                 error if there is any
*/
- (void)downloadTypekitFontFamilyListMetadata:(NSString *)query
numberOfFontFamilies:(NSInteger)numberOfFontFamilies
error:(NSError *)error;

/**
* Remove a synced font from the device, this also un-sync a font for this user
*
* param fontName          The name of the font
* param error             error if there is any
*/
- (void)removeTypekitSyncedFont:(NSString *)fontName
error:(NSError *)error;

/**
* View font details for a family name
*
* param familyName        The family name that we are viewing font details from
*                              font details include variations, classification, foundry, etc...
* param error             error if there is any
*/
- (void)viewTypekitFontFamilyDetails:(NSString *)familyName
error:(NSError *)error;


/**
* log ETS event for Color
*
* param eventType     such as change, save, edit, etc
* param colorUIName   nil or any UI item such as color-wheel, color-RGB etc
* param contentType   any of the color type such as: color-slider, color-swatch, color-theme, etc
* param contentName   such as hexString for color (#ffffff), theme name for color-theme, library name for color-library, etc
* param error         error, if there is any
*/

- (void)logETSEventForColorWithEventType:(NSString *)eventType
colorUIName:(NSString *)colorUIName
contentType:(NSString *)contentType
contentName:(NSString *)contentName
error:(NSError *)error;

#pragma mark - Properties

/**
* Whether the session is active. Notice that an inactive ETS session will
* appear to be working correctly, i.e. you can call any of its event reporting
* methods without triggering any errors.
*/
@property (nonatomic, readonly) BOOL isActive;

/**
* The client ID of the application.
*/
@property (atomic, copy) NSString *clientId;

/**
* The user (Adobe ID).
*/
@property (atomic, copy) NSString *user;

/**
* The cloud the application currently has access to.
*/
@property (atomic, copy) AdobeCloud *cloud;

/**
* A dictionary containing properties that should be part of all new events.
*/
@property (atomic, copy) NSDictionary *dataForNewEvents;

/**
* brief Type defining the signature of a data provider for a newly created event.
*/
typedef NSDictionary *(^AdobeETSEventDataProvider)();

#pragma mark - Event Reporting

/**
* brief Creates a new unfinalized event with the given type and data and returns its id.
*
* The new event is stored in the persistent queue and is left in an unfinalized state.
* It needs to get finalized before it can get send to the service.
*
* param eventType     A string describing the type of the event.
* param initialData   A dictionary containing the initial data for the event. Can be nil.
*/
- (NSString *)createEventWithType:(NSString *)eventType andData:(NSDictionary *)initialData;

/**
* brief Creates a new unfinalized event with the given type and data and returns its id.
*
* The new event is stored in the persistent queue and is left in an unfinalized state.
* It needs to get finalized before it can get send to the service.
*
* param eventType     A string describing the type of the event.
* param dataProvider  A block providing the initial data for the event. Can be nil.
*/
- (NSString *)createEventWithType:(NSString *)eventType andDataProvider:(AdobeETSEventDataProvider)dataProvider;


/**
* brief Adds data to the existing, unfinalized event as specified by the eventId param.
*
* Fails silently if the event is not known or if it has already been finalized.
*
* param eventId   The id of an existing, unfinalized event.
* param data      A dictionary containing the data for the event. Notice that it gets
*                  merged into the existing data for the event.
*/
- (void)updateEvent:(NSString *)eventId withData:(NSDictionary *)data;


/**
* brief Adds data to the existing, unfinalized event as specified by the eventId param.
*
* Fails silently if the event is not known or if it has already been finalized.
*
* param eventId   The id of an existing, unfinalized event.
* param dataProvider  A block providing the new data for the event. Notice that it gets
*                  merged into the existing data for the event.
*/
- (void)updateEvent:(NSString *)eventId withDataProvider:(AdobeETSEventDataProvider)dataProvider;


/**
* brief Finalizes the given event
*
* Fails silently if the event is not known or if it has already been finalized.
*
* param eventId   The id of an existing, unfinalized event.
* param data      A dictionary containing new data for the event. Notice that it gets
*                  merged into the existing data for the event. Can be nil.
*/
- (void)finalizeEvent:(NSString *)eventId withData:(NSDictionary *)data;


/**
* brief Finalizes the given event
*
* Fails silently if the event is not known or if it has already been finalized.
*
* param eventId   The id of an existing, unfinalized event.
* param dataProvider  A block providing the new data for the event. Notice that it gets
*                  merged into the existing data for the event. Can be nil.
*/
- (void)finalizeEvent:(NSString *)eventId withDataProvider:(AdobeETSEventDataProvider)dataProvider;


/**
* brief Creates and reports a new finalized event with the given type and data.
*
* This is a shortcut for calling createEventWithType: immediately followed by
* a call to finalizeEvent:.
*
* param eventType A string describing the type of the event.
* param data      A dictionary containing the data for the event. Can be nil.
*/
- (void)reportEventWithType:(NSString *)eventType andData:(NSDictionary *)data;


/**
* brief Creates and reports a new finalized event with the given type and data.
*
* This is a shortcut for calling createEventWithType: immediately followed by
* a call to finalizeEvent:.
*
* param eventType A string describing the type of the event.
* param dataProvider  A block providing the data for the event. Can be nil.
*/
- (void)reportEventWithType:(NSString *)eventType andDataProvider:(AdobeETSEventDataProvider)dataProvider;


#pragma mark - Data Helpers

/**
* brief Populates the given data dictionary from the given arguments.  Used typically to populate the
*        fields common to all ETS events.
*
* param data          Optional. Existing mutable dictionary to annotate.
*                      Method creates and returns a new data dictionary if none is provided.
* param sdk           Optional. A string describing the SDK.
* param sdkVersion    Optional. A string describing the version(s) of the SDK.
* param os            Optional. A string describing the OS.
* param osVersion     Optional. A string describing the version of the OS.
* param deviceId      Optional. A unique identifier for the device.
* param deviceType    Optional. A string describing the type of the device.
* param appName       Optional. A string describing the application.
* param appBundleId   Optional. A string describing the application bundle
* param appVersion    Optional. A string describing the version of the app.
*
* return The annotated data dictionary.
*/
+ (NSMutableDictionary *)eventData:(NSMutableDictionary *)data
sdk:(NSString *)sdk
sdkVersion:(NSString *)sdkVersion
os:(NSString *)os
osVersion:(NSString *)osVersion
deviceID:(NSString *)deviceId
deviceType:(NSString *)deviceType
appName:(NSString *)appName
appBundleID:(NSString *)appBundleId
appVersion:(NSString *)appVersion;

/**
* brief Populates the given data dictionary with properties from the given error.
*
* param data      Optional. Existing mutable dictionary to annotate.
*                  Method creates and returns a new data dictionary if none is provided.
* param error     The error.
*
* return The annotated data dictionary.
*/
+ (NSMutableDictionary *)eventData:(NSMutableDictionary *)data withError:(NSError *)error isExpected:(BOOL)expected;

/**
* brief Populates the given data dictionary with properties from the given reason for cancelation.
*
* param data      Optional. Existing mutable dictionary to annotate.
*                  Method creates and returns a new data dictionary if none is provided.
* param reason    The reason why the event was canceled.
*
* return The annotated data dictionary.
*/
+ (NSMutableDictionary *)eventData:(NSMutableDictionary *)data withCancelReason:(NSString *)reason;

/**
* brief Populates the given data dictionary with properties from the given HTTP request and response.
*
* param data      Optional. Existing mutable dictionary to annotate.
*                  Method creates and returns a new data dictionary if none is provided.
* param request   The HTTP request.
* param response  Optional. The HTTP response.
*
* return The annotated data dictionary.
*/
+ (NSMutableDictionary *)eventData:(NSMutableDictionary *)data withHttpRequest:(AdobeNetworkHTTPRequest *)request andResponse:(AdobeNetworkHTTPResponse *)response;

/**
* brief Populates the given data dictionary with properties for a child event
*
* param data      Optional. Existing mutable dictionary to annotate.
*                  Method creates and returns a new data dictionary if none is provided.
* param context   The id of the context/parent event.
* param sequence  If > 0: the sequence number of the event within its context
*
* return The annotated data dictionary.
*/
+ (NSMutableDictionary *)eventData:(NSMutableDictionary *)data withContext:(NSString *)context
andSequence:(NSUInteger)sequence;

@end

#endif /* ifndef AdobeETSSessionHeader */
