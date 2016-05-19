/******************************************************************************
*
* ADOBE CONFIDENTIAL
* ___________________
*
* Copyright 2014 Adobe Systems Incorporated
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

#ifndef AdobeLibraryManagerInternalHeader
#define AdobeLibraryManagerInternalHeader

#import <Foundation/Foundation.h>

@class AdobeCloud;
@class AdobeLibraryBookmark;

/**
* brief This class contains all the internal portions of AdobeLibraryManager, which have
* not been made public yet.
*/
@interface AdobeLibraryManager ()

/**
* The cloud instance the manager is currently syncing with.
*/
@property (readonly, nonatomic, strong) AdobeCloud *cloud;

/**
* brief An array of all the bookmarks for the current user.
*/
@property (readonly, copy) NSArray *bookmarks;

/**
* brief Startup the Adobe Library service.
*
* param rootFolder The root folder to use for storing libraries and their content.
* param cloud The cloud to which the libraries belong.
*					This is required unless the sync is disabled for the manager. (See AdobeLibraryManager syncEnabled synthesized set method.)
* param errorPtr An optional pointer to an error to receive startup error information.
*
* see AdobeLibraryManager.h for the syncEnabled synthesized set method.
*
* return An error object with the status of the startup operation.
*/
- (BOOL)startWithFolder:(NSString *)rootFolder
inCloud:(AdobeCloud *)cloud
andError:(NSError **)errorPtr;

/**
* brief Resolve the given element reference to a library and an element object if the element exists.
*
* param elementRef reference of an element that is requested to be resolved.
* param library pointer to the library object that the resolved element belongs to or nil if library cannnot be found.
* param element pointer to the element object that is represented with the given element reference or nil if element cannnot be found.
*/
- (void) resolveElementReference:(NSString *)elementRef
library:(AdobeLibraryComposite **)library
element:(AdobeLibraryElement **)element;

/**
* brief Add a new bookmark with the given id and url.
*/
- (AdobeLibraryBookmark *)addBookmark:(NSString *)bookmarkId withURL:(NSString *)url;

/**
* brief Remove the given bookmark.
*/
- (void)removeBookmark:(AdobeLibraryBookmark *)bookmark;

@end

#endif
