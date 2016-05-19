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

#ifndef AdobeETSConstantsHeader
#define AdobeETSConstantsHeader

#import <Foundation/Foundation.h>

#pragma mark - Event Types

extern NSString *const AdobeETSEventTypeAppActive;
extern NSString *const AdobeETSEventTypeAppCancelAndReturn;
extern NSString *const AdobeETSEventTypeAppCancelAndStay;
extern NSString *const AdobeETSEventTypeAppCapture;
extern NSString *const AdobeETSEventTypeAppCaptureMany;
extern NSString *const AdobeETSEventTypeAppChange;
extern NSString *const AdobeETSEventTypeAppColorFilter;
extern NSString *const AdobeETSEventTypeAppComplete;
extern NSString *const AdobeETSEventTypeAppCreate;
extern NSString *const AdobeETSEventTypeAppDelete;
extern NSString *const AdobeETSEventTypeAppDownload;
extern NSString *const AdobeETSEventTypeAppDuplicate;
extern NSString *const AdobeETSEventTypeAppEdit;
extern NSString *const AdobeETSEventTypeAppEmbed;
extern NSString *const AdobeETSEventTypeAppEmbedMany;
extern NSString *const AdobeETSEventTypeAppEndpointChange;
extern NSString *const AdobeETSEventTypeAppExtract;
extern NSString *const AdobeETSEventTypeAppFilter;
extern NSString *const AdobeETSEventTypeAppInactive;
extern NSString *const AdobeETSEventTypeAppInstall;
extern NSString *const AdobeETSEventTypeAppLaunch;
extern NSString *const AdobeETSEventTypeAppLicense;
extern NSString *const AdobeETSEventTypeAppLogin;
extern NSString *const AdobeETSEventTypeAppLogout;
extern NSString *const AdobeETSEventTypeAppOffline;
extern NSString *const AdobeETSEventTypeAppOnline;
extern NSString *const AdobeETSEventTypeAppOpen;
extern NSString *const AdobeETSEventTypeAppOrientationFilter;
extern NSString *const AdobeETSEventTypeAppPick;
extern NSString *const AdobeETSEventTypeAppPreview;
extern NSString *const AdobeETSEventTypeAppProfile;
extern NSString *const AdobeETSEventTypeAppReauthenticate;
extern NSString *const AdobeETSEventTypeAppSave;
extern NSString *const AdobeETSEventTypeAppSaveAndReturn;
extern NSString *const AdobeETSEventTypeAppSaveAndStay;
extern NSString *const AdobeETSEventTypeAppSavePreview;
extern NSString *const AdobeETSEventTypeAppSearch;
extern NSString *const AdobeETSEventTypeAppSelectApp;
extern NSString *const AdobeETSEventTypeAppSend;
extern NSString *const AdobeETSEventTypeAppSignup;
extern NSString *const AdobeETSEventTypeAppSort;
extern NSString *const AdobeETSEventTypeAppStart;
extern NSString *const AdobeETSEventTypeAppStartSecondaryApp;
extern NSString *const AdobeETSEventTypeAppStore;
extern NSString *const AdobeETSEventTypeAppToken;
extern NSString *const AdobeETSEventTypeAppUnknown;
extern NSString *const AdobeETSEventTypeAppUpdate;
extern NSString *const AdobeETSEventTypeAppView;
extern NSString *const AdobeETSEventTypeCloudChanged;

extern NSString *const AdobeETSEventTypeAnalyticsOverflow;
extern NSString *const AdobeETSEventTypeAnalyticsSubmission;

extern NSString *const AdobeETSEventTypeHTTPAsyncPoll;

#pragma mark - Event Property Keys

extern NSString *const AdobeETSEventPropertyGuid;
extern NSString *const AdobeETSEventPropertyUser;
extern NSString *const AdobeETSEventPropertyCloud;
extern NSString *const AdobeETSEventPropertyContext;
extern NSString *const AdobeETSEventPropertyContextSequence;
extern NSString *const AdobeETSEventPropertyType;
extern NSString *const AdobeETSEventPropertySubtype;
extern NSString *const AdobeETSEventPropertyStart;
extern NSString *const AdobeETSEventPropertyEnd;
extern NSString *const AdobeETSEventPropertyWorkflow;
extern NSString *const AdobeETSEventPropertyCategory;
extern NSString *const AdobeETSEventPropertyOffline;
extern NSString *const AdobeETSEventPropertyDevice;
extern NSString *const AdobeETSEventPropertySession;
extern NSString *const AdobeETSEventPropertyError;
extern NSString *const AdobeETSEventPropertyNewEndpoint;
extern NSString *const AdobeETSEventPropertyPreviousEndpoint;
extern NSString *const AdobeETSEventPropertyKeychain;
extern NSString *const AdobeETSEventPropertyTokenExpiration;

extern NSString *const AdobeETSEventPropertyClientId;
extern NSString *const AdobeETSEventPropertyAppName;
extern NSString *const AdobeETSEventPropertyAppVersion;
extern NSString *const AdobeETSEventPropertyPlatform;
extern NSString *const AdobeETSEventPropertyDeviceType;
extern NSString *const AdobeETSEventPropertyOSVersion;
extern NSString *const AdobeETSEventPropertyAppStoreId;

extern NSString *const AdobeETSEventPropertyConsumerClientId;
extern NSString *const AdobeETSEventPropertyConsumerName;
extern NSString *const AdobeETSEventPropertyConsumerVersion;
extern NSString *const AdobeETSEventPropertyConsumerPlatform;
extern NSString *const AdobeETSEventPropertyConsumerDevice;
extern NSString *const AdobeETSEventPropertyConsumerOSVersion;
extern NSString *const AdobeETSEventPropertyConsumerAppStoreId;

extern NSString *const AdobeETSEventPropertyCancelReason;
extern NSString *const AdobeETSEventPropertyExpectedError;
extern NSString *const AdobeETSEventPropertyDeactivationCounter;
extern NSString *const AdobeETSEventPropertyOfflineCounter;

extern NSString *const AdobeETSEventPropertyContentId;
extern NSString *const AdobeETSEventPropertyContentName;
extern NSString *const AdobeETSEventPropertyContentType;
extern NSString *const AdobeETSEventPropertyContentSize;
extern NSString *const AdobeETSEventPropertyContentExtension;

extern NSString *const AdobeETSEventPropertyUiApplicationName;
extern NSString *const AdobeETSEventPropertyUiViewType;
extern NSString *const AdobeETSEventPropertyUiSearchKeyword;
extern NSString *const AdobeETSEventPropertyUiFilter;
extern NSString *const AdobeETSEventPropertyUiOrientation;
extern NSString *const AdobeETSEventPropertyUiSortOrder;

extern NSString *const AdobeETSEventPropertyFrameworkName;
extern NSString *const AdobeETSEventPropertyFrameworkVersion;
extern NSString *const AdobeETSEventPropertyComponentName;
extern NSString *const AdobeETSEventPropertyComponentVersion;
extern NSString *const AdobeETSEventPropertyServiceName;
extern NSString *const AdobeETSEventPropertyServiceVersion;
extern NSString *const AdobeETSEventPropertyServiceAPIName;
extern NSString *const AdobeETSEventPropertyServiceAPIVersion;

extern NSString *const AdobeETSEventPropertyNumEvents;
extern NSString *const AdobeETSEventPropertyNumEventsPending;
extern NSString *const AdobeETSEventPropertyNumEventsReported;
extern NSString *const AdobeETSEventPropertyNumEventsDiscarded;
extern NSString *const AdobeETSEventPropertyNumEventsRejected;
extern NSString *const AdobeETSEventPropertyByteCountSent;
extern NSString *const AdobeETSEventPropertyByteCountUncompressed;

extern NSString *const AdobeETSEventPropertyHttpVerb;
extern NSString *const AdobeETSEventPropertyHttpStatus;
extern NSString *const AdobeETSEventPropertyHttpRequestId;
extern NSString *const AdobeETSEventPropertyHttpPriority;
extern NSString *const AdobeETSEventPropertyHttpDurationRequest;
extern NSString *const AdobeETSEventPropertyHttpDurationQueue;
extern NSString *const AdobeETSEventPropertyHttpContentMd5;
extern NSString *const AdobeETSEventPropertyHttpContentLength;
extern NSString *const AdobeETSEventPropertyHttpContentType;
extern NSString *const AdobeETSEventPropertyHttpRetryOf;
extern NSString *const AdobeETSEventPropertyHttpNetwork;
extern NSString *const AdobeETSEventPropertyHttpCloud;
extern NSString *const AdobeETSEventPropertyHttpDelay;

#pragma mark - Event Category Values

extern NSString *const AdobeETSEventCategoryCSDK;

#pragma mark - Event Property Values

extern NSString *const AdobeETSEventCancelReasonStale;
extern NSString *const AdobeETSEventCancelReasonUser;

extern NSString *const AdobeETSEventHttpNetworkNone;
extern NSString *const AdobeETSEventHttpNetworkWifi;
extern NSString *const AdobeETSEventHttpNetworkWwan;

#pragma mark - Environment Component Values

extern NSString *const AdobeETSEnvironmentComponent360Workflow;
extern NSString *const AdobeETSEnvironmentComponentAppLibraryBrowser;
extern NSString *const AdobeETSEnvironmentComponentAssetBrowser;
extern NSString *const AdobeETSEnvironmentComponentAssetHeadless;
extern NSString *const AdobeETSEnvironmentComponentAuth;
extern NSString *const AdobeETSEnvironmentComponentCloudPicker;
extern NSString *const AdobeETSEnvironmentComponentColor;
extern NSString *const AdobeETSEnvironmentComponentDCX;
extern NSString *const AdobeETSEnvironmentComponentGeneral;
extern NSString *const AdobeETSEnvironmentComponentMarketAssetBrowser;
extern NSString *const AdobeETSEnvironmentComponentPSDExtraction;
extern NSString *const AdobeETSEnvironmentComponentSendToDesktop;
extern NSString *const AdobeETSEnvironmentComponentShareMenu;
extern NSString *const AdobeETSEnvironmentComponentStockBrowser;
extern NSString *const AdobeETSEnvironmentComponentTypekitFontBrowser;
extern NSString *const AdobeETSEnvironmentComponentTypekitFontPicker;
extern NSString *const AdobeETSEnvironmentComponentUnknown;

#pragma mark - Content Type Values

extern NSString *const AdobeETSContentTypeCCFile;
extern NSString *const AdobeETSContentTypeLocalFile;
extern NSString *const AdobeETSContentTypePSDLayer;
extern NSString *const AdobeETSContentTypeTypekitFont;
extern NSString *const AdobeETSContentTypeTypekitFontFamily;
extern NSString *const AdobeETSContentTypeTypekitFontFamilyMetadata;

#pragma mark - Sort Order Values

extern NSString *const AdobeETSSortOrderFeatured;
extern NSString *const AdobeETSSortOrderDownloaded;
extern NSString *const AdobeETSSortOrderHighestRanked;
extern NSString *const AdobeETSSortOrderMostRecent;
extern NSString *const AdobeETSSortOrderRelevance;
extern NSString *const AdobeETSSortOrderUndiscovered;

#pragma mark - Filter Values

extern NSString *const AdobeETSFilterAll;
extern NSString *const AdobeETSFilterBrushes;
extern NSString *const AdobeETSFilterCapture;
extern NSString *const AdobeETSFilterCommunity;
extern NSString *const AdobeETSFilterDesign;
extern NSString *const AdobeETSFilterForPlacement;
extern NSString *const AdobeETSFilterIcons;
extern NSString *const AdobeETSFilterIllustrator;
extern NSString *const AdobeETSFilterPatterns;
extern NSString *const AdobeETSFilterPhotos;
extern NSString *const AdobeETSFilterPresentation;
extern NSString *const AdobeETSFilterStorage;
extern NSString *const AdobeETSFilterUserInterfaces;
extern NSString *const AdobeETSFilterVectors;
extern NSString *const AdobeETSFilterVideo;

#pragma mark - Orientation Values

extern NSString *const AdobeETSOrientationAll;
extern NSString *const AdobeETSOrientationSquare;
extern NSString *const AdobeETSOrientationPanoramic;
extern NSString *const AdobeETSOrientationLandscape;
extern NSString *const AdobeETSOrientationPortrait;

#pragma mark - View Type Values

extern NSString *const AdobeETSViewTypeAsset;
extern NSString *const AdobeETSViewTypeGrid;
extern NSString *const AdobeETSViewTypeList;

#pragma mark - Token Type Values

extern NSString *const AdobeETSTokenTypeExpireAccess;
extern NSString *const AdobeETSTokenTypeRefreshAccess;
extern NSString *const AdobeETSTokenTypeDeleteRefresh;
extern NSString *const AdobeETSTokenTypeDeleteDevice;
extern NSString *const AdobeETSTokenTypeDeleteSharedDevice;

#pragma mark - Logout Type Values

extern NSString *const AdobeETSLogoutTypeUserInitiated;
extern NSString *const AdobeETSLogoutTypeTokenDeleted;
extern NSString *const AdobeETSLogoutTypeEndpointChanged;

#pragma mark - Color UI Types
extern NSString *const AdobeETSColorUICMYK;
extern NSString *const AdobeETSColorUIHistory;
extern NSString *const AdobeETSColorUILibrary;
extern NSString *const AdobeETSColorUIRGB;
extern NSString *const AdobeETSColorUIWheel;

extern NSString *const AdobeETSColorTypeHistoryAll;
extern NSString *const AdobeETSColorTypeLibraryName;
extern NSString *const AdobeETSColorTypePicker;
extern NSString *const AdobeETSColorTypeScheme;
extern NSString *const AdobeETSColorTypeSlider;
extern NSString *const AdobeETSColorTypeSwatch;
extern NSString *const AdobeETSColorTypeTheme;


#endif /* ifndef AdobeETSConstantsHeader */
