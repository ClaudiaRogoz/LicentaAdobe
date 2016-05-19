/******************************************************************************
*
* ADOBE CONFIDENTIAL
* ___________________
*
* Copyright 2013 Adobe Systems Incorporated
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

#ifndef AdobeAuthSignInNavHeader
#define AdobeAuthSignInNavHeader

#ifndef DMALIB

#import <UIKit/UIKit.h>

@class AdobeAuthSignInViewController;
@class AdobeUXAuthManager;

typedef void (^AuthSignInNavSuccessBlock) (NSString *adobeID, NSString *accessToken);
typedef void (^AuthSignInNavErrorBlock)   (NSError *error);
typedef void (^AuthSignInNavDismissBlock) (NSError *error);

@interface AdobeAuthSignInNavigationController : UINavigationController

@property (nonatomic, strong) AdobeAuthSignInViewController *rootViewController;

@property (nonatomic, strong) AdobeUXAuthManager *manager;
@property (nonatomic, strong) UIViewController *hostingViewController;

@property (nonatomic, assign) BOOL defaultToSignUp;
@property (nonatomic, assign) BOOL hideSignUpOnSignIn;
@property (nonatomic, assign) BOOL showSignInOnSignUp;
@property (nonatomic, assign) BOOL shouldHideNavigationBar;
@property (nonatomic, assign) BOOL shouldHideNavigationBarCloseButton;

@property (nonatomic, copy) AuthSignInNavSuccessBlock successBlock;
@property (nonatomic, copy) AuthSignInNavErrorBlock errorBlock;
@property (nonatomic, copy) AuthSignInNavDismissBlock dismissBlock;

@end

#endif // !DMALIB

#endif
