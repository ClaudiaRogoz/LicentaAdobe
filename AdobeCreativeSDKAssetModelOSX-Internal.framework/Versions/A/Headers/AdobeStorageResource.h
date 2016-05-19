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

#ifndef AdobeStorageResourceHeader
#define AdobeStorageResourceHeader

#import <Foundation/Foundation.h>

#import <AdobeCreativeSDKAssetModelOSX/AdobeCollaborationType.h>

@class AdobeCloud;

/**
* class AdobeStorageResource
* brief Represents a resource that resides on the server. Base class for AdobeStorageResourceItem and
* AdobeStorageResourceCollection.
*/
@interface AdobeStorageResource : NSObject<NSCopying>

/** The internal ID of this resource. */
@property (nonatomic) NSString *internalID;

/**
* The The href of the resource, i.e. its path relative to the service URL.
* Note: the href must be percent escaped to be valid.
*/
@property (nonatomic) NSString *href;

/**
* The name of this resource.
* Note: the name is not percent escaped so if used to build an href, you must
* account for this.
*/
@property (nonatomic) NSString *name;

/** The MIME content type of this resource. */
@property (nonatomic) NSString *type;

/** The etag of this resource. */
@property (nonatomic) NSString *etag;

/** The created timestamp of this resource on the server. */
@property (nonatomic) NSString *created;

/** The modified timestamp of this resource on the server. */
@property (nonatomic) NSString *modified;

/** Whether this resource is a collection */
@property (readonly) BOOL isCollection;

/** Whether this resource does not have write access. **/
@property (assign) BOOL readOnly;

/** The collaboration value associated with this resource */
@property (nonatomic, assign) AdobeCollaborationType collaboration;

/** The cloud the resource belongs to. */
@property (nonatomic) AdobeCloud *cloud;

@end

#endif
