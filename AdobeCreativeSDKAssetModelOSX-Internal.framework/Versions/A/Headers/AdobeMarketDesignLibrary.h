/******************************************************************************
*
* ADOBE CONFIDENTIAL
* ___________________
*
* Copyright 2014 Adobe Systems Incorporated
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

#ifndef AdobeMarketDesignLibraryHeader
#define AdobeMarketDesignLibraryHeader

#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeDCXComposite.h>
#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeDCXTransferSessionProtocol.h>
#import <AdobeCreativeSDKAssetModelOSX/AdobeLibraryDelegate.h>

@class AdobeCloud;
@class AdobeLibraryComposite;

typedef NSArray AdobeLibraryComposites;

extern NSString *const AdobeMarketDesignLibrarySyncStartedNotification;
extern NSString *const AdobeMarketDesignLibrarySyncFinishedNotification;
extern NSString *const AdobeMarketLibraryManagerWillStartNotification;

@interface AdobeMarketDesignLibrary : NSObject < AdobeLibraryDelegate >

@property (nonatomic, strong) AdobeCloud *cloud;
@property (nonatomic, readonly, assign, getter=isStarted) BOOL started;
@property (nonatomic, readonly, assign) BOOL librariesLoaded;

+ (AdobeMarketDesignLibrary *)sharedDesignLibrary;

- (BOOL)startup;
- (void)shutdownAndClearLocalFiles:(BOOL)clearFiles;
- (void)sync;

- (AdobeLibraryComposites *)libraries;
- (AdobeLibraryComposite *)createLibraryWithName:(NSString *)name andError:(NSError **)error;
- (void)deleteLibrary:(AdobeLibraryComposite *)library andError:(NSError **)error;

@end

#endif
