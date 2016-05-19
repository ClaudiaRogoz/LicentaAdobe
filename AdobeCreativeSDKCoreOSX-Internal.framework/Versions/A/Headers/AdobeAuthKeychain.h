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

#ifndef AdobeAuthKeychainHeader
#define AdobeAuthKeychainHeader

#import <Foundation/Foundation.h>

extern NSString *AdobeAuthKeychainGroupReverseDNSName;
extern NSString *AdobeAuthKeychainGroupName;

extern NSString *AdobeAuthKeychainAccessToken;
extern NSString *AdobeAuthKeychainDeviceToken;
extern NSString *AdobeAuthKeychainRefreshToken;
extern NSString *AdobeAuthKeychainContinuationToken;
extern NSString *AdobeAuthKeychainAccessTokenExpiration;
extern NSString *AdobeAuthKeychainDeviceTokenExpiration;
extern NSString *AdobeAuthKeychainRefreshTokenExpiration;
extern NSString *AdobeAuthKeychainEnvironmentIndicator;

extern NSString *AdobeAuthKeychainAuthenticated;
extern NSString *AdobeAuthKeychainLoggedInNotification;

extern NSString *AdobeAuthKeychainAdobeID;
extern NSString *AdobeAuthKeychainIsEnterprise;
extern NSString *AdobeAuthKeychainFullName;
extern NSString *AdobeAuthKeychainDisplayName;
extern NSString *AdobeAuthKeychainFirstName;
extern NSString *AdobeAuthKeychainLastName;
extern NSString *AdobeAuthKeychainEmailAddress;
extern NSString *AdobeAuthKeychainEmailVerified;
extern NSString *AdobeAuthKeychainPhoneNumber;
extern NSString *AdobeAuthKeychainCountryCode;
extern NSString *AdobeAuthKeychainUtcOffset;
extern NSString *AdobeAuthKeychainLanguages;
extern NSString *AdobeAuthKeychainDeveloperMode;

extern NSString *AdobeAuthKeychainEntitlements;

@interface AdobeAuthKeychain : NSObject

// Auth tokens
@property (nonatomic, readonly, strong) NSString *accessToken;
@property (nonatomic, readonly, strong) NSString *deviceToken;
@property (nonatomic, readonly, strong) NSString *refreshToken;
@property (nonatomic, readonly, strong) NSString *continuationToken;
@property (nonatomic, readonly, strong) NSDate *accessTokenExpiration;
@property (nonatomic, readonly, strong) NSDate *deviceTokenExpiration;
@property (nonatomic, readonly, strong) NSDate *refreshTokenExpiration;

// Authenticated state
@property (nonatomic, readonly, assign, getter = isAuthenticated) BOOL authenticated;
@property (nonatomic, readonly, assign) BOOL loggedInNotification;

// User profile
@property (nonatomic, readonly, strong) NSString *adobeID;
@property (nonatomic, readonly, strong) NSString *hashedAdobeID;
@property (nonatomic, readonly, strong) NSString *isEnterprise;
@property (nonatomic, readonly, strong) NSString *fullName;
@property (nonatomic, readonly, strong) NSString *displayName;
@property (nonatomic, readonly, strong) NSString *firstName;
@property (nonatomic, readonly, strong) NSString *lastName;
@property (nonatomic, readonly, strong) NSString *emailAddress;
@property (nonatomic, readonly, strong) NSString *emailVerified;
@property (nonatomic, readonly, strong) NSString *phoneNumber;
@property (nonatomic, readonly, strong) NSString *countryCode;
@property (nonatomic, readonly, strong) NSString *utcOffset;
@property (nonatomic, readonly, strong) NSArray *languages;
@property (nonatomic, readonly, strong) NSString *developerMode;

@property (nonatomic, readonly, strong) NSSet *entitlements;


+ (AdobeAuthKeychain *)sharedKeychain;

- (BOOL)updateOrAddKeyById:(NSString *)identifier withBoolean:(BOOL)value;
- (BOOL)updateOrAddKeyById:(NSString *)identifier withValue:(id)value;
- (BOOL)deleteKeyById:(NSString *)identifier;

- (void)resetTokens;
- (void)resetNonTouchIDTokens;
- (void)printContents;

@end

#endif /* ifndef AdobeAuthKeychainHeader */
