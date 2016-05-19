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
*
* THIS FILE IS PART OF THE CREATIVE SDK RESTRICTED API
*
******************************************************************************/

#ifndef AdobeUXAuthManagerRestrictedHeader
#define AdobeUXAuthManagerRestrictedHeader

#import <AdobeCreativeSDKCoreOSX-Internal/AdobeAuthEndpoint.h>
#import <AdobeCreativeSDKCoreOSX-Internal/AdobeAuthLoginDelegate.h>

@class AdobeAuthUserProfile;

/**
* The account switchability policy type. This type represents the policy for account switchability
* in a runtime activation of the SDK.
*
*/
typedef NS_ENUM (NSInteger, AdobeAuthAccountSwitchability)
{
/** Allow the account to be changed at runtime. */
AdobeAuthAccountSwitchabilitySwitchable = 0,

/** Prevent the account from being changed at runtime. */
AdobeAuthAccountSwitchabilityNonSwitchable,
};

/**
* Options to be passed throughout the authentication workflow.
*/
typedef NS_OPTIONS (NSUInteger, AdobeAuthOptions)
{
/** No options specified. */
AdobeAuthOptionsUnset               = 0,

/** Hide sign up options on sign in. */
AdobeAuthOptionsHideSignUpOnSignIn  = (1 << 0),

/**
* Embed authentication into your app (rather than a popup).
*
* Note: This option has been deprecated. Specifying this option has no effect.
*/
AdobeAuthOptionsUseEmbedded         = (1 << 1),

/** Show sign in options on sign up. */
AdobeAuthOptionsShowSignInOnSignUp  = (1 << 2)
};

typedef NS_OPTIONS (NSUInteger, AdobeAuthUIOption)
{
/**
* Completely hide the navigation bar.
*/
AdobeAuthUIOptionHideNavigationBar = 1 << 2,

/**
* Hide the navigation bar close button but leave the navigation bar visible.
*/
AdobeAuthUIOptionHideNavigationBarCloseButton = 1 << 3
};

typedef NSUInteger AdobeAuthUIOptionFlags;

/**
* Notification indicating that the environment (e.g., production, stage, etc.) changed.
*/
extern NSString *const AdobeAuthManagerEnvironmentChangedNotification;

/**
* This file declares an extension to the AdobeUXAuthManager class.
* It's purpose is to provide internal clients with functionality not intended for the
* public interface.
*/

@interface AdobeUXAuthManager ()

/**
* Authentication device id.
*
* @returns the authentication device id as an NSString *.
*
* @note <font color="red">This property is part of the restricted api.</font>
*/
@property (nonatomic, readonly, strong) NSString *deviceID;

/**
* Authentication device name.
*
* @returns the authentication device name as an NSString *.
*
* @note <font color="red">This property is part of the restricted api.</font>
*/
@property (nonatomic, readonly, strong) NSString *deviceName;

/**
* Authentication client id.
*
* @returns the authentication client id as an NSString *.
*
* @note <font color="red">This property is part of the restricted api.</font>
*/
@property (nonatomic, readonly, strong) NSString *clientID;

/**
* Authentication client secret.
*
* @returns the authentication client secret as an NSString *.
*
* @note <font color="red">This property is part of the restricted api.</font>
*/
@property (nonatomic, readonly, strong) NSString *clientSecret;

/**
* Returns the access token of the currently logged in user.
*
* @returns the access token of the currently logged in user as an NSString *, or nil if no user is authenticated.
*
* @note <font color="red">This property is part of the restricted api.</font>
*/
@property (nonatomic, readonly, strong) NSString *accessToken;

/**
* Returns the device token of the currently logged in user.
*
* @returns the device token of the currently logged in user as an NSString *, or nil if no user is authenticated.
*
* @note <font color="red">This property is part of the restricted api.</font>
*/
@property (nonatomic, readonly, strong) NSString *deviceToken;

/**
* Returns the adobe ID of the currently logged in user.
*
* @returns the adobe ID of the currently logged in user as an NSString *, or nil if no user is authenticated.
*
* @note <font color="red">This property is part of the restricted api.</font>
*/
@property (nonatomic, readonly, strong) NSString *adobeID;

/**
* Returns a set of product entitlement strings that the currently logged in user has access to. Currently, this set
* is implemented to only return "InDesign", "Photoshop" and "Illustrator".
*
* @returns the set of product entitlements, can return an empty set or nil if no user is authenticated.
*
* @note <font color="red">This property is part of the restricted api.</font>
*/
@property (nonatomic, readonly, strong) NSSet *entitlements;

/**
* The redirect URL to use during signin/signup.
*
* @returns the redirect URL.
*
* @note <font color="red">This property is part of the restricted api.</font>
*/
@property (nonatomic, strong) NSURL *redirectURL;

/**
* The login delegate for this class; It allows for some control over the user interaction.
* Notice that this is a weak reference.
*
* @note <font color="red">This property is part of the restricted api.</font>
*/
@property (weak) id<AdobeAuthLoginDelegate> loginDelegate;

/**
* Gets the authentication endpoint.
*
* @returns the authentication endpoint.
* @see AdobeAuthEndpoint
*
* @note <font color="red">This property is part of the restricted api.</font>
*/
@property (nonatomic, readonly, assign) AdobeAuthEndpoint endpoint;

/**
*  Indicates whether or not the UI Automation Test Server should be used.
*/
@property (nonatomic, assign) BOOL shouldUseUIAutomationTestServer;

/**
* Returns the account switchability policy for the SDK.
*
* @returns the AdobeAuthAccountSwitchability setting for the current runtime invocation of the SDK.
*
* @note <font color="red">This property is part of the restricted api.</font>
*/
@property (nonatomic, readonly, assign) AdobeAuthAccountSwitchability accountSwitchability;

/**
* Controls whether to display an alert when using the logoutMayAlert method.  It's disabled
* by default, but enabled internally when invoked through an UX class.  The client app is responsible
* for restoring the previous value.
*
* @note <font color="red">This property is part of the restricted api.</font>
*/
@property (nonatomic, readwrite, assign) BOOL showAlerts;

/**
* Reports whether this a 1st party (Adobe) or 3rd party (non-Adobe) application.
*
* @note <font color="red">This property is part of the restricted api.</font>
*/
@property (nonatomic, readwrite, assign, getter = isAdobeApplication) BOOL adobeApplication;

/**
* Reports whether running on an application extension or an application proper.
*
* @note <font color="red">This property is part of the restricted api.</font>
*/
@property (nonatomic, readwrite, assign, getter = isApplicationExtension) BOOL applicationExtension;


/**
* Sets the authentication endpoint for Creative Cloud Authentication.
*
* !!! *** !!! This method must not be used in production environments !!! *** !!!
* It should be used only in debug environments that require access to a staging or test authentication endpoint.
* This function should be called once upon application startup.
*
* @param endpoint The AdobeAuthEndpoint type of the Creative Cloud Servers to connect to.
*/
- (void)setAuthenticationEndpoint:(AdobeAuthEndpoint)endpoint;

/**
* Sets the authentication parameters for Creative Cloud Authentication.
*
* This method must be called once at application startup, typically in the application delegate.
* It must be called before any other authentication calls.
*
* This method does not initiate a login.  If needed, login is triggered when Creative Cloud
* services are accessed or when AdobeUXAuthManager login:onSuccess:onError is explicitly called.
*
* Applications that access private clouds must use this method, and not the public
* setAuthenticationParametersWithClientID:withClientSecret:.
*
* @param clientID The clientID as supplied to the application developer by Adobe
* @param clientSecret The client secret for the application as supplied to the application developer by Adobe
* @param clientState The client state as provided to IMS for collecting usage analytics. Clients should pass nil if they do not need sign-in/sign-up usage analytics.
* @param deviceID  Device identification that meets Adobe's security requirements
* @param options Options to pass into the authentication workflow.
* @param scopeList nil for the default scope or an NSArray of additional app specific scope NSStrings (advanced)
*/
- (void)setAuthenticationParametersWithClientID:(NSString *)clientID
withClientSecret:(NSString *)clientSecret
withClientState:(NSString *)clientState
withDeviceID:(NSString *)deviceID
withOptions:(AdobeAuthOptions)options
withAdditionalScopeList:(NSArray *)scopeList;

/**
* Specifying options for the authentication UI.
*
* @param flag A bitmask of options for the authentication UI based on @c AdobeAuthUIOptions
*/
- (void)setAuthenticationUIOptions:(AdobeAuthUIOptionFlags)flags;

#ifndef DMALIB
/**
* Used to show the sign up page to get an Adobe credential.
*
* @param viewController the parent view to host the signup view.
* @param animate YES to present/hide the sign up view with an aniamation
* @param successBlock to be notified when the sign up process is complete
* @param errorBlock to be notified when an error has occurred during the sign up process.
*/
- (void)promptForSignUp:(UIViewController *)viewController
animate:(BOOL)animate
onSuccess:(void (^)(AdobeAuthUserProfile *profile))successBlock
onError:(void (^)(NSError *error))errorBlock;
#endif // !DMALIB

/**
* Used to supply a pre-validated IMS access token and user info to the creative SDK
*
* @param accessToken the previously authenticated IMS access token
* @param adobeID the adobeID of the user for which the accessToken was issued
* @param displayName the display name (full name) of the user for which the accessToken was issued
* @param firstName the first name of the user for which the accessToken was issued
* @param lastName the last name of the user for which the accessToken was issued
* @param emailAddress the email address of the user for which the accessToken was issued
* @param emailVerified whether or not the email address has been verified, acceptable values are "true" and "false"
*
* @note Use this function to supply credentials to the Creative SDK using your own pre-authenticated IMS access token.
* This function allows the IMS token and user info to the Creative SDK.
* You must first call setAuthenticationParametersWithClientID with the actual parameters used by the client managed
* authentication for the accessToken passed in.
* <font color="red"><b>This function is a stop-gap workaround until IMS social login is redesigned.</b></font>
*
* @note <font color="red">This property is part of the restricted api.</font>
*/
- (void)stuffCredentialsWithAccessToken:(NSString *)accessToken
withAdobeID:(NSString *)adobeID
withDisplayName:(NSString *)displayName
withFirstName:(NSString *)firstName
withLastName:(NSString *)lastName
withEmailAddress:(NSString *)emailAddress
withEmailVerified:(NSString *)emailVerified;

/**
* Logs in the user using a device token. This method will not create a view for interactive loging.
* Instead if the device token cannot be used for login, the method will execute the errorBlock.
* The method will also execute the errorBlock if the user is already authenticated.
*
* @param deviceToken the device token for login
* @param successBlock the block of code that gets called upon login success
* @param errorBlock the block of code that gets called upon login failure
* @note This call is not explicity needed to be called. If authentication is required, it will be called later.
*/
- (void)loginWithDeviceToken:(NSString *)deviceToken
success:(void (^)(AdobeAuthUserProfile *profile))successBlock
error:(void (^)(NSError *error))errorBlock;

/**
* Logs out the currently logged in user from an application extension.  This method preserves the authentication
* state shared between the extension and its containing application.  The method is typically called from the
* extension before logging in.  The method will execute the errorBlock if called on the non-extension version
* of the Foundation SDK.
*
* @param successBlock the block of code that gets called upon logout success
* @param errorBlock the block of code that gets called upon logout failure
*/
- (void)logoutExtension:(void (^)(void))successBlock
onError:(void (^)(NSError *error))errorBlock;

/**
* Logs out the currently logged in user, presenting an alert before logging out.  Presenting the alert
* is controlled by the showAlerts property.
*
* @param alertMessage alert message
* @param additionalMessage alert additional message
* @param successBlock the block of code that gets called upon logout success
* @param errorBlock the block of code that gets called upon logout failure
*
* @note <font color="red">This method is part of the restricted api.</font>
*/
- (void)logoutMayAlert:(NSString *)alertMessage
additionalInfo:(NSString *)additionalMessage
onSuccess:(void (^)(void))successBlock
onError:(void (^)(NSError *error))errorBlock;

/**
* Logs out the currently logged in user, presenting an alert before logging out.  Presenting the alert
* is controlled by the showAlerts property.  This method is deprecated.  Use
* logoutMayAlert:additionalInfo:onSuccess:onError instead.
*
* @param alertMessage alert message
* @param additionalMessage alert additional message
* @param successBlock the block of code that gets called upon logout success
* @param errorBlock the block of code that gets called upon logout failure
*
* @note <font color="red">This method is part of the restricted api.</font>
*/
- (void)logoutWithAlert:(NSString *)alertMessage
additionalInfo:(NSString *)additionalMessage
onSuccess:(void (^)(void))successBlock
onError:(void (^)(NSError *error))errorBlock
__deprecated_msg("Use logoutMayAlert:additionalInfo:onSuccess:onError instead");

/**
* Refresh access token if it has expired or is within 5 minutes of expiration.
*
* @param successBlock the block of code that gets called upon reauthentication success
* @param errorBlock the block of code that gets called upon reauthentication failure
*
* @note <font color="red">This method is part of the restricted api.</font>
*/
- (void)refreshAccess:(void (^)(AdobeAuthUserProfile *profile))successBlock
onError:(void (^)(NSError *error))errorBlock;

/**
* Refresh access token independent of its expiration state.
*
* @param successBlock the block of code that gets called upon reauthentication success
* @param errorBlock the block of code that gets called upon reauthentication failure
*
* @note <font color="red">This method is part of the restricted api.</font>
*/
- (void)forceRefreshAccess:(void (^)(AdobeAuthUserProfile *profile))successBlock
onError:(void (^)(NSError *error))errorBlock;

/**
* Specify if the account can be changed during runtime.
*
* @param switchability the option to specify switchability.
*
* @note <font color="red">This method is part of the restricted api.</font>
*/
- (void)setAccountSwitchability:(AdobeAuthAccountSwitchability)switchability;

/**
* Checks whether we have a valid access token.
*/
- (BOOL)hasValidAccessToken;

/**
*  Checks whether there is a device token in the shared keychain.
*
*  @return YES if a token exists, otherwise, NO.
*/
- (BOOL)hasSharedDeviceToken;

/**
* Synchronously checks to see if we are authenticated, and if not calls the error block.
*
* @param errorBlock the block of code that gets called upon an unautheticated user
* @param message the message to post if the error block is nil
*
* @return return NO if authenticated, YES if not authenticated
*/
- (BOOL)checkAndCallErrorIfNotAuthenticated:(void (^)(NSError *error))errorBlock
withMessage:(NSString *)message;

/**
* Synchronously checks to see if we have a valid accessToken, and if not calls the error block.
*
* @param errorBlock the block of code that gets called upon an unautheticated user
* @param message the message to post if the error block is nil
*
* @return return NO if there is an accessToken, YES if no accessToken
*/
- (BOOL)checkAndCallErrorIfInvalidAccessToken:(void (^)(NSError *error))errorBlock
withMessage:(NSString *)message;

/**
* Synchronously check an authentication condition and call the error block with
* AdobeAuthErrorCodeUserCredentialsRequired if false.
*
* @param condition the condition to check
* @param message the message to post if the error block is nil
* @param errorBlock the block of code that gets called upon a false condition
*
* @return return YES if condition is true, NO otherwise
*/
- (BOOL)checkIfTrueAndCallErrorIfNot:(BOOL)condition
message:(NSString *)message
errorBlock:(void (^)(NSError *))errorBlock;

/**
* Setup a timer to retry reauthentication.  This method is intended for SDK internal use.
* Client applications should not use this timer explicitly.
*
* @param interval timer interval in seconds.
*
* @note <font color="red">This method is part of the restricted api.</font>
*/
- (void)setupReauthenticateTimer:(NSTimeInterval)interval;

/**
* Stop the reauthentication timer.  This method is intended for SDK internal use.
* Client applications should not use this timer explicitly.
*
* @note <font color="red">This method is part of the restricted api.</font>
*/
- (void)stopReauthenticateTimer;

+ (BOOL)refuseSSLCertificateIfBogusCharlesProxy:(SecCertificateRef)remoteCertificate;

@end

#endif /* ifndef AdobeUXAuthManagerRestrictedHeader */
