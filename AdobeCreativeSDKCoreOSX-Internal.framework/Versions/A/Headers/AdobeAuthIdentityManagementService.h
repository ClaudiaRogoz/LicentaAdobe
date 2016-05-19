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

#ifndef AdobeAuthIdentityMgmtHeader
#define AdobeAuthIdentityMgmtHeader

#import <AdobeCreativeSDKCoreOSX-Internal/AdobeAuthKeychain.h>

@class AdobeAuthSharedKeychain;

// Preserve enum values to prevent keychain migration issues.  If the environment value changes from
// one release to the other, the cached tokens will be deleted.
typedef NS_ENUM (NSInteger, AdobeAuthIMSEnvironment)
{
AdobeAuthIdentityManagementServiceUndefined = 0,
AdobeAuthIMSEnvironmentTestUS               = 1,
AdobeAuthIMSEnvironmentTestUS2              = 2,
AdobeAuthIMSEnvironmentStageUS              = 3,
AdobeAuthIMSEnvironmentProductionUS         = 4,
};

typedef NS_ENUM (NSInteger, AdobeAuthIMSInfoNeeded)
{
AdobeAuthIMSInfoNeededUnknownError = 0,
AdobeAuthIMSInfoNeededUsernameAndPassword,
AdobeAuthIMSInfoNeededAgeVerification,
AdobeAuthIMSInfoNeededTermsOfUse,
AdobeAuthIMSInfoNeededEmailVerification,
AdobeAuthIMSInfoNeededMultipleInformation
};

typedef NS_ENUM (NSInteger, AdobeAuthIMSGrantType)
{
AdobeAuthIMSGrantTypeDevice = 0,
AdobeAuthIMSGrantTypeAuthorization,
AdobeAuthIMSGrantTypeRefresh
};

typedef NS_ENUM (NSInteger, AdobeAuthIMSInteraction)
{
AdobeAuthIMSInteractionHeadless,
AdobeAuthIMSInteractionInteractive
};


extern NSString *const AdobeAuthIMSDisconnectedNotification;

@interface AdobeAuthIdentityManagementService : NSObject

@property (nonatomic, readonly, strong) NSString *accessToken;
@property (nonatomic, readonly, strong) NSString *adobeID;
@property (nonatomic, readonly, strong) NSString *deviceToken;
@property (nonatomic, readonly, strong) NSString *sharedDeviceToken;
@property (nonatomic, readonly, strong) NSString *refreshToken;
@property (nonatomic, readonly, strong) NSString *continuationToken;
@property (nonatomic, readonly, strong) NSString *touchIDToken;
@property (nonatomic, readonly, strong) NSDate *accessTokenExpirationTime;
@property (nonatomic, readonly, strong) NSDate *deviceTokenExpirationTime;
@property (nonatomic, readonly, strong) NSDate *sharedDeviceTokenExpirationTime;
@property (nonatomic, readonly, strong) NSDate *refreshTokenExpirationTime;
@property (nonatomic, readonly, strong) NSDate *touchIDTokenExpirationTime;
@property (nonatomic, readonly, strong) NSSet *entitlements;

@property (nonatomic, readonly, strong) NSString *imsHost;
@property (nonatomic, readwrite, strong) NSString *deviceID;

@property (nonatomic, readwrite, assign) AdobeAuthIMSEnvironment environment;

@property (nonatomic, readwrite, strong) NSString *deviceName;
@property (nonatomic, readwrite, strong) NSString *clientID;
@property (nonatomic, readwrite, strong) NSString *clientSecret;
@property (nonatomic, readwrite, strong) NSString *clientState;
@property (nonatomic, readwrite, strong) NSString *clientScope;

@property (nonatomic, readwrite, strong) AdobeAuthSharedKeychain *sharedAuthKeychain;

@property (nonatomic, readwrite, strong) NSString *username;
@property (nonatomic, readwrite, strong) NSString *password;

@property (nonatomic, readonly, strong) NSURL *signInURL;
@property (nonatomic, readonly, strong) NSURL *signUpURL;
@property (nonatomic, readonly, strong) NSURL *authURL;
@property (nonatomic, readonly, strong) NSURL *signOutURL;

@property (nonatomic, readwrite, assign) AdobeAuthIMSGrantType grantType;


+ (AdobeAuthIdentityManagementService *)sharedService;

+ (NSDictionary *)endpointString;

- (void)setAdditionalClientScopesWith:(NSArray *)scopeList;

- (void)fetchEntitlements;

- (void)resetLocalAuthState;

- (void)resetTouchIDToken;

- (void)prepareForDeviceTokenLogin:(NSString *)deviceToken;

- (void)completeDeviceTokenLogin:(NSString *)deviceToken;

- (void)  signIn:(AdobeAuthIMSInteraction)interaction
onSuccess:(void (^)(NSString *adobeID, NSString *accessToken))successBlock
onInfoNeeded:(void (^)(AdobeAuthIMSInfoNeeded info))infoBlock
onError:(void (^)(NSError *error))errorBlock;

- (void)signInWithAuthCode:(NSString *)code
onSuccess:(void (^)(NSString *adobeId, NSString *accessToken))successBlock
onError:(void (^)(NSError *error))errorBlock;

- (void)signInWithDeviceToken:(NSString *)deviceToken
onSuccess:(void (^)(NSString *adobeId, NSString *accessToken))successBlock
onError:(void (^)(NSError *error))errorBlock;

- (void)stuffCredentialsWithAccessToken:(NSString *)accessToken
withAdobeID:(NSString *)adobeID
withDisplayName:(NSString *)displayName
withFirstName:(NSString *)firstName
withLastName:(NSString *)lastName
withEmailAddress:(NSString *)emailAddress
withEmailVerified:(NSString *)emailVerified;

- (void)signOut:(void (^)(void))successBlock
onError:(void (^)(NSError *error))errorBlock;

// Version of signOut: that gives the option of keeping the shared device token.  The extension SDK relies on
// the shared device token to keep a consistent auth state with its host app.  Keeping the shared device token
// must be done only in the extension SDK.
- (void)signOut:(BOOL)keepSharedKeychain
success:(void (^)(void))successBlock
error:(void (^)(NSError *error))errorBlock;

@end

#endif /* ifndef AdobeAuthIdentityMgmtHeader */
