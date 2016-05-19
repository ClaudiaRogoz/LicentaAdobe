/******************************************************************************
*
* ADOBE CONFIDENTIAL
* ___________________
*
* Copyright 2015 Adobe Systems Incorporated
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

#ifndef AdobeAuthLoggingHeader
#define AdobeAuthLoggingHeader

#import <AdobeCreativeSDKCoreOSX-Internal/AdobeCommonLogging.h>
#import <Foundation/Foundation.h>

// Define as a macros so that __FILE__ and __LINE__ (in the CoreLog... macros) reflect the correct usage location.

// Auth specific logging. Unfortunately the dupication here is necessary. Macros can't define macros.

#define AuthLogFatal(s, ...)                            do {                                                    CoreLog(Auth, Critical, (s), ## __VA_ARGS__);           } while (0)
#define AuthLogError(s, ...)                            do {                                                    CoreLog(Auth, Error, (s), ## __VA_ARGS__);           } while (0)
#define AuthLogWarn(s, ...)                             do {                                                    CoreLog(Auth, Warning, (s), ## __VA_ARGS__);            } while (0)
#define AuthLogDebug(s, ...)                            do {                                                    CoreLog(Auth, Debug, (s), ## __VA_ARGS__);           } while (0)
#define AuthLogTrace(s, ...)                            do {                                                    CoreLog(Auth, Trace, (s), ## __VA_ARGS__);           } while (0)
AdobeLoggingDecl(Auth);

//
// The class this category is added to is created in the AdobeLoggingDecl
//
@interface AdobeAuthLogging(Auth)
+ (NSString *)displayToken:(NSString *)token;
+ (NSString *)decodeToken:(NSString *)token;
@end

#endif
