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

#ifndef AdobeCommonUtilsHeader
#define AdobeCommonUtilsHeader

#import <Foundation/Foundation.h>

@interface AdobeCommonUtils : NSObject

typedef void (^HashCompletionHandler)(NSString *, unsigned long long, NSError *);

+ (id)JSONObjectWithData:(NSData *)data
options:(NSJSONReadingOptions)opt
error:(NSError **)errorPtr;

+ (NSString *)generateUUID;

+ (NSUInteger)currentMemoryUsage;

+ (BOOL)doesClass:(Class)subClass decendFromClass:(Class)baseClass;

+ (void)hashOfData:(NSData *)data completionHandler:(HashCompletionHandler)handler;

+ (void)hashOfFile:(NSString *)filePath completionHandler:(HashCompletionHandler)handler;

+ (NSString *)hashOfString:(NSString *)string hexEncoding:(BOOL)hexEncoding;

+ (NSString *)timeInLocalZone:(NSDate *)time;

+ (NSDate *)convertStringToDate:(NSString *)inputStrDate;

+ (BOOL)moveFileAtomicallyFrom:(NSString *)sourcePath
to:(NSString *)destPath
error:(NSError **)errorPtr;

+ (NSString *)localizedStringForKey:(NSString *)key
bundleClassName:(NSString *)className
bundleSelectorName:(NSString *)selectorName
fallbackString:(NSString *)fallback;

@end

#endif
