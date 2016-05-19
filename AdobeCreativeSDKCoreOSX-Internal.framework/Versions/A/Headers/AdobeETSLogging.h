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

#ifndef AdobeETSLoggingHeader
#define AdobeETSLoggingHeader

#import <AdobeCreativeSDKCoreOSX-Internal/AdobeCommonLogging.h>
#import <Foundation/Foundation.h>

// Define as a macros so that __FILE__ and __LINE__ (in the CoreLog... macros) reflect the correct usage location.

// ETS specific logging. Unfortunately the dupication here is necessary. Macros can't define macros.

#define ETSLogFatal(s, ...)                            do {                                                    CoreLog(ETS, Critical, (s), ## __VA_ARGS__);           } while (0)
#define ETSLogError(s, ...)                            do {                                                    CoreLog(ETS, Error, (s), ## __VA_ARGS__);           } while (0)
#define ETSLogWarn(s, ...)                             do {                                                    CoreLog(ETS, Warning, (s), ## __VA_ARGS__);            } while (0)
#define ETSLogDebug(s, ...)                            do {                                                    CoreLog(ETS, Debug, (s), ## __VA_ARGS__);           } while (0)
#define ETSLogTrace(s, ...)                            do {                                                    CoreLog(ETS, Trace, (s), ## __VA_ARGS__);           } while (0)
AdobeLoggingDecl(ETS);

#endif
