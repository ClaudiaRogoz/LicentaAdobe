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
*
**************************************************************************/

#ifndef AdobeAuthLoginDelegateHeader
#define AdobeAuthLoginDelegateHeader

@protocol AdobeAuthLoginDelegate <NSObject>

/**
* Called just before the user will be prompted with UI to login.
*
* @return YES to let the UI appear, NO to handle it yourself at some other point.
*/
- (BOOL)promptUserWithLoginUI;


@optional
/**
* Called when the SDK is about to dismiss the parent viewController.  See login: and promptForSignup: in
* AdobeUXAuthManager.  If not implemented, the SDK will dismiss the parent viewController.
*
* @return NO to let the SDK dismiss the view controller, YES to handle it yourself at some other point.
*/
- (BOOL)handleDismissLoginUI;

@end

#endif
