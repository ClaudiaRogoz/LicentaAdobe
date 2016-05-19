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

#ifndef AdobeCommonLoggingHeader
#define AdobeCommonLoggingHeader

#import <Foundation/Foundation.h>

typedef NS_ENUM (NSInteger, AdobeCommonLoggingLevel)
{
AdobeCommonLoggingLevelEmergency,
AdobeCommonLoggingLevelAlert,
AdobeCommonLoggingLevelCritical,
AdobeCommonLoggingLevelError,
AdobeCommonLoggingLevelWarning,
AdobeCommonLoggingLevelNotice,
AdobeCommonLoggingLevelInformation,
AdobeCommonLoggingLevelDebug,
AdobeCommonLoggingLevelTrace
};


#define CoreLog(groupName, level, ...)         [[Adobe##groupName##Logging sharedLogger]          logLevel: AdobeCommonLoggingLevel##level          group: #groupName          forFile: __FILE__          forLine: __LINE__          withFormat: __VA_ARGS__]
// NSLog() is discouraged in Release builds because NSLog output is saved in the Apple System Log.  Prior
// to iOS 7 all applications installed on the device have the ability to read and search the Apple System
// Log and extract potentially sensitive information. With iOS 7 this has partially been addressed.
// Applications can only access their own logs.  However these logs are not encrypted and therefore are
// vulnerable to physical attacks on the device.  Instead, use one of the following macros.  The macros
// are enabled only on Debug builds.

#ifdef DEBUG

#define LogFatal(...) CoreLog(Common, Critical,  __VA_ARGS__)
#define LogError(...) CoreLog(Common, Error, __VA_ARGS__)
#define LogWarn(...)  CoreLog(Common, Warning, __VA_ARGS__)
#define LogInfo(...)  CoreLog(Common, Information, __VA_ARGS__)
#define LogDebug(...) CoreLog(Common, Debug, __VA_ARGS__)
#define LogTrace(...) CoreLog(Common, Trace, __VA_ARGS__)

#else

#define LogFatal(...)
#define LogError(...)
#define LogWarn(...)
#define LogInfo(...)
#define LogDebug(...)
#define LogTrace(...)

#endif


// Macro declares the logger for a module (should be invoked in the header file with the module name)

// NSUserDefaults key for logging.
// Applications that want to control module-specific logging must support this key.  They must return a BOOL.

#define AdobeLoggingDecl(name) @interface Adobe##name##Logging : AdobeCommonLogging     + (Adobe##name##Logging *)sharedLogger; @end

// Macro implements the logger for a module (should be invoked in a .m file, with the module name)

#define AdobeLoggingImpl(name) const NSString *AdobeCommonLoggingVerbose##name = @"keyAdobeCreativeSDK" #name "LoggingEnable"; const NSString *AdobeCommonLoggingLevel##name = @"keyAdobeCreativeSDK" #name "LoggingLevel"; @implementation Adobe##name##Logging + (Adobe##name##Logging *)sharedLogger {    static dispatch_once_t once;     static Adobe##name##Logging *sharedLogger = nil;        dispatch_once(&once, ^{        sharedLogger = [[Adobe##name##Logging alloc] init];         [sharedLogger readLogStateFromPrefs];     });         return sharedLogger; }- (void)readLogStateFromPrefs {     [self readLogStateFromPrefs:AdobeCommonLoggingVerbose##name levelKey:AdobeCommonLoggingLevel##name]; }@end


@interface AdobeCommonLogging : NSObject

+ (AdobeCommonLogging *)sharedLogger;

- (void)logLevel:(AdobeCommonLoggingLevel)level
group:(char *)group
forFile:(char *)sourceFile
forLine:(int)lineNumber
withFormat:(NSString *)format, ...;

- (void)changeLogLevel:(AdobeCommonLoggingLevel)level;

+ (NSUInteger)logLevelForUserDefault:(NSString *)logLevel;

- (void)readLogStateFromPrefs:(const NSString *)verboseEnableKey levelKey:(const NSString *)levelKey;

- (void)readLogStateFromPrefs;

- (AdobeCommonLoggingLevel)currentLogLevel;

@property (nonatomic) BOOL verboseLogging;

@end

#endif
