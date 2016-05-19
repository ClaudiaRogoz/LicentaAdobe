/******************************************************************************
*
* ADOBE CONFIDENTIAL
* ___________________
*
* Copyright 2016 Adobe Systems Incorporated
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

#ifndef AdobeCoreLoggingHeader
#define AdobeCoreLoggingHeader

#import <AdobeCreativeSDKCoreOSX-Internal/AdobeCommonLogging.h>
#import <Foundation/Foundation.h>


//
// Core Logger must be enabled using verboseLogging and can be seen by First and Third party clients.
// Use LogDebug for outputting to the log with the guarantee that it will not be seen, except in DEBUG builds.
//


// Define as a macros so that __FILE__ and __LINE__ (in the CoreLog... macros) reflect the correct usage location.

// Core specific logging. Unfortunately the dupication here is necessary. Macros can't define macros.

#define CoreLogFatal(s, ...)                            do {                                                    CoreLog(Core, Critical, (s), ## __VA_ARGS__);           } while (0)
#define CoreLogError(s, ...)                            do {                                                    CoreLog(Core, Error, (s), ## __VA_ARGS__);           } while (0)
#define CoreLogWarn(s, ...)                             do {                                                    CoreLog(Core, Warning, (s), ## __VA_ARGS__);            } while (0)
#define CoreLogDebug(s, ...)                            do {                                                    CoreLog(Core, Debug, (s), ## __VA_ARGS__);           } while (0)
#define CoreLogTrace(s, ...)                            do {                                                    CoreLog(Core, Trace, (s), ## __VA_ARGS__);           } while (0)
AdobeLoggingDecl(Core);

#endif
