/*************************************************************************
*
* ADOBE CONFIDENTIAL
* ___________________
*
*  Copyright 2013 Adobe Systems Incorporated
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
**************************************************************************/

#ifndef AdobeStorageFileUtilsHeader
#define AdobeStorageFileUtilsHeader

#import <Foundation/Foundation.h>

/**
* brief File-related utilities.
*/
@interface AdobeStorageFileUtils : NSObject

/**
* brief Moves a file atomically to a new path, replacing an already existing file. Create the
* necessary directories.
*
* param sourcePath The file to move.
* param destPath The destination path.
* param errorPtr Gets set to an error if something goes wrong.
*
* return YES if successful.
*/

+ (BOOL)moveFileAtomicallyFrom:(NSString *)sourcePath to:(NSString *)destPath withError:(NSError **)errorPtr;

+ (BOOL)copyFileAtomicallyFrom:(NSString *)sourcePath to:(NSString *)destPath withError:(NSError **)errorPtr;

/**
* brief Updates the modification date of the file at filePath
*
* param filePath    The path to the file whose mod date should get updated.
* param errorPtr    Gets set to an error if something goes wrong.
*
* return            YES if successful.
*/

+ (BOOL)touch:(NSString *)filePath withError:(NSError **)errorPtr;

/**
* brief Makes the file at filePath read-only.
*
* param filePath The path to the file that should become read-only.
* param errorPtr Gets set to an error if something goes wrong.
*
* return YES if successful.
*/

+ (BOOL)setReadOnly:(NSString *)filePath withError:(NSError **)errorPtr;

/**
* brief Clears the read-only flag of the file at filePath.
*
* param filePath The path to the file that should no longer be read-only.
* param errorPtr Gets set to an error if something goes wrong.
*
* return YES if successful.
*/
+ (BOOL)clearReadOnly:(NSString *)filePath withError:(NSError **)errorPtr;


/**
* brief Clears the read-only flag of any item contained in path.
*
* param dirPath The path to the directory that should no longer be read-only.
* param errorPtr Gets set to an error if something goes wrong.
*
* return YES if successful.
*/
+ (BOOL)recursivelyClearAnyReadOnlyFlagsInDirectory:(NSString *)dirPath withError:(NSError **)errorPtr;

@end

#endif
