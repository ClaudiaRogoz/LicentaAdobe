/*************************************************************************
*
* ADOBE CONFIDENTIAL
* ___________________
*
* Copyright 2015 Adobe Systems Incorporated
* All Rights Reserved.
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

@class AdobeNetworkHTTPRequest;

@protocol AdobeNetworkHTTPAsyncRequestDelegate <NSObject>

- (BOOL)supportsProgress:(NSString *)guid;

@end

/** Protected extensions to AdobeNetworkHTTPAsyncRequest. */
@interface AdobeNetworkHTTPAsyncRequest (Protected)

- (instancetype)initWithObserver:(NSObject *)observer;

- (instancetype)initWithRequest:(AdobeNetworkHTTPRequest *)request
observer:(NSObject *)observer;

- (void)updateRequest:(AdobeNetworkHTTPRequest *)request;

- (void)setup;
- (void)teardown;

@end

@interface AdobeNetworkHTTPAsyncRequest ()

@property (nonatomic, readwrite, strong) AdobeNetworkHTTPRequest *request;

@end
