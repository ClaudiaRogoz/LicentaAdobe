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

#ifndef AdobeLibraryServiceItemHeader
#define AdobeLibraryServiceItemHeader

#import <Foundation/Foundation.h>

typedef NS_ENUM (NSInteger, AdobeLibraryServiceItemState)
{
AdobeLibraryServiceItemStateUnknown = 0,
AdobeLibraryServiceItemStateNormal,
AdobeLibraryServiceItemStateArchived,
};

typedef NS_ENUM (NSInteger, AdobeLibraryServiceCollaborationState)
{
AdobeLibraryServiceCollaborationStateUnknown = 0,
AdobeLibraryServiceCollaborationStateSharedByUser,
AdobeLibraryServiceCollaborationStateSharedWithUser,
};

typedef NSArray AdobeLibraryServiceItems;

/**
* AdobeLibraryServiceItem represents a library and provides access to data about the library (type, size, etc).
* It allows for reading and creating libraries in the Creative Cloud.
*/
@interface AdobeLibraryServiceItem : NSObject<NSCopying, NSCoding>

/**
* The creation date of the item.
*/
@property (readonly, nonatomic, strong) NSDate *creationDate;

/**
* The modification date of the item.
*/
@property (readonly, nonatomic, strong) NSDate *modificationDate;

/**
* The etag of the item.
*/
@property (readonly, nonatomic, strong) NSString *etag;

/**
* The unique identifier of the item.
*/
@property (readonly, nonatomic, strong) NSString *GUID;

/**
* The name of the item.
*/
@property (readonly, nonatomic, strong) NSString *name;

/**
* The number of elements.
*/
@property (readonly, nonatomic, assign) NSInteger numberOfElements;

/**
* The state of the item.
*/
@property (readonly, nonatomic, assign) AdobeLibraryServiceItemState libraryState;

/**
* The collaboration state of the item.
*/
@property (readonly, nonatomic, assign) AdobeLibraryServiceCollaborationState collaborationState;

/**
* Create a library.
*
* @param successBlock   Called when the creation has succeeded.
* @param errorBlock     Called when the creation has failed.
*/
+ (void)  create:(NSString *)libraryName
successBlock:(void (^)(AdobeLibraryServiceItem *libraryItem))successBlock
errorBlock:(void (^)(NSError *error))errorBlock;

/**
* Get the libraries for the logged in user.
*
* @param successBlock   Called when the creation has succeeded.
* @param errorBlock     Called when the creation has failed.
*/
+ (void)libraries:(void (^)(AdobeLibraryServiceItems *libraries, BOOL changedSinceLastQuery))successBlock
errorBlock:(void (^)(NSError *error))errorBlock;

@end

#endif /* ifndef AdobeLibraryServiceItemHeader */
