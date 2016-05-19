/*************************************************************************
*
* ADOBE CONFIDENTIAL
* ___________________
*
* Copyright 2013 Adobe Systems Incorporated
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

// Reviewed by rhorns on October 11, 2013

#ifndef AdobeNetworkHTTPServiceDelegateHeader
#define AdobeNetworkHTTPServiceDelegateHeader

#import <Foundation/Foundation.h>

@class AdobeNetworkHTTPService;

/** Protocol for the AdobeNetworkHTTPService delegate. */

@protocol AdobeNetworkHTTPServiceDelegate <NSObject>

@required

/**
* If a request issued by an instance of AdobeNetworkHTTPService fails with an authentication
* error, the service will invoke this method on its delegate.
*
* @param service The service that encountered the authentication failure.
*
* @return If the delegate returns YES, then the authentication call will be retried after
* the queue is re-started. If it returns NO, then the original authentication call
* will return immediately with an error.
*
* Typically, a delegate should use this method to obtain a revised authentication token,
* and then inform the service of the revised token via AdobeNetworkHTTPService::setAuthToken:.
*
* When this method is called, the request queue for the given service will have been
* paused in order to avoid spamming the server with multiple requests for the same
* expired token. The client must arrange to set AdobeNetworkHTTPService::suspended to NO in order
* to restart requests.
*
* The delegate may set both the authToken and suspended state of the service during this
* call, or at any time after this call.
*
* AdobeNetworkHTTPService guarantees that it will call this method exactly once per token,
* assuming tokens are not recycled. It also guarantees that only one invocation will
* happen at a time. There are no guarantees as to which threasd invocation will occur on.
*
* @note You should check service::hasEncounteredTooManyAuthFailures to see if the service has
* encountered too many authentication failures in last five minutes.
*/
- (BOOL)HTTPServiceAuthenticationDidFail:(AdobeNetworkHTTPService *)service;

/**
* Gets called if the service got disconnected. This usually happens because it experienced too many
* recent failures (see AdobeNetworkHTTPSession for details).
*
* @param service The service that has been disconnected.
*/
- (void)HTTPServiceDidDisconnect:(AdobeNetworkHTTPService *)service;

/**
* Gets called when a SSL certificate comes back from the server. This is useful to allow the app
* to "pin" to a certificate (or set of certificates).
*
* @param remoteCertificate the certificate to inspect.
*
* @return YES if you want the connection to continue. NO if you want the connection to stop.
*/
- (BOOL)HTTPAllowConnectionToContinueWithCertificate:(SecCertificateRef)remoteCertificate;


@optional

/**
* Gets called on every successful operation to the service.  This implies that the device is online
* and there are no AdobeNetworkHTTPService conditions to stop service operation (e.g., the nework
* is not suspended or disconnected).  To reduce performance impact minimize the amount of work done
* in this method.
*
* @param service The service that is active.
*/
- (void)HTTPServiceIsActive:(AdobeNetworkHTTPService *)service;

@end

#endif
