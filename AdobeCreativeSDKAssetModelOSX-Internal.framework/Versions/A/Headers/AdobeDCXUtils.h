/*************************************************************************
*
* ADOBE CONFIDENTIAL
* ___________________
*
*  Copyright 2014 Adobe Systems Incorporated
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

#ifndef AdobeDCXUtilsHeader
#define AdobeDCXUtilsHeader

#import <Foundation/Foundation.h>

#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeDCXComposite.h>

@interface AdobeDCXUtils : NSObject

/**
* brief Looks at the files stored at path and tries to determine which local storage scheme is being
* used.
*
* param path A directory file path for a composite.
*
* return The storage scheme in use. Defaults to AdobeDCXLocalStorageSchemeCopyOnWrite.
*/
+ (AdobeDCXLocalStorageScheme)guessLocalStorageSchemeOfCompositeAtPath:(NSString *)path;

/**
* brief Creates a copy of a composite using a new local storage scheme
*
* param srcScheme   The local storage scheme used by the source composite
* param srcPath     The local path containing the source composite
* param destScheme  The local storage scheme to be used by the destination composite
* param destPath    The local path where the destination composite should be created
* param preserveSource  Indicates whether the integrity of the composite at srcPath should be maintained.
* If set to NO then this routine may move, rather than copy, source component files to their new location.
* param errorPtr    A pointer to an error object that will contain a reason for failure
*
* note This method only converts the manifests for the current branch and the base branch, and copies or moves
* the components in the current branch since base versions of components are not supported in the Directories
* local storage scheme). Any in-progress pushes and pulls will be ignored and will not be present in the new
* copy of the composite.
*
* return YES if successful; NO if not
*/
+ (BOOL)convertLocalStorageScheme:(AdobeDCXLocalStorageScheme)srcScheme
ofCompositeAtPath:(NSString *)srcPath
toStorageScheme:(AdobeDCXLocalStorageScheme)destScheme
atDestinationPath:(NSString *)destPath
preserveSourceComponents:(BOOL)preserveSource
withError:(NSError **)errorPtr;

/**
* brief Returns YES if the given string is a valid path property for a DCX component or node.
*
* A path is valid if all of its components (derived by splitting it with the forward
* slash / as a separator) fulfill these criteria:
* - it must be 1 to 255 characters long
* - it must not end with a . (dot)
* - it must not contain any of the following characters
*  o U+0022 " QUOTATION MARK
*  o U+002A * ASTERISK
*  o U+002F / SOLIDUS
*  o U+003A : COLON
*  o U+003C < LESS-THAN SIGN
*  o U+003E > GREATER-THAN SIGN
*  o U+003F ? QUESTION MARK
*  o U+005C  REVERSE SOLIDUS
*  o The C0 controls, U+0000 through U+001F and U+007F
*
* param path The string to verify.
*
* return YES if the given string is a valid path property for a DCX component or node.
*/
+ (BOOL)isValidPath:(NSString *)path;

/**
* brief Checks absolute paths to see that they do not start with /mimetype or /manifest
*
* param absPath The path to verify.  If it does not start with a '/', absPath returns NO
*
* return YES if the path is safe, NO otherwise
*/
+ (BOOL)isValidAbsPath:(NSString *)absPath;

@end

#endif
