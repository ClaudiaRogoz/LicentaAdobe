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

// Reviewed by rhorns on October 11, 2013

#ifndef AdobeStorageResourceItemHeader
#define AdobeStorageResourceItemHeader

#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeStorageResource.h>

/**
* class AdobeStorageResourceItem
* brief Represents an individual resource that resides on the server.
*/
@interface AdobeStorageResourceItem : AdobeStorageResource<NSCopying>

/**
* brief Creates a resource pointing to an href.
*
* param href The path of the resource on the server.  The caller is responsible for properly percent-escaping
* the path components.  See RFC 3986 specifications, sections 2.2 and 2.3.
*
* return The newly created resource.
*/
+ (id)resourceFromHref:(NSString *)href;

/**
* brief Percent-espace characters in an asset name
*
* param asset Input string, typically a path component to a resource on the server.  Characters other
* than "unreserved" (ALPHA | DIGIT | - | . | _ | ~) are percent-escaped.  See RFC 3986 spec, Section 2.3.
*
* return Updated asset string
*/
+ (NSString *)escapeAssetName:(NSString *)asset;

/**
* brief Validate asset name
*
* param asset Input string, typically a path component to a resource on the server.  The method validates that
* the string conforms to the server naming conventions.  The method expects an unescaped asset name string.
*
* return Whether the asset input string is valid.
*/
+ (BOOL)validAssetName:(NSString *)asset;

/**
* brief Creates a resource pointing to an asset which is part of a sync group.
*
* param assetName     The name of the asset.
* param syncGroupName The name of the sync group containing the asset
*
* return The newly created resource.
*/
+ (id)resourceFromAssetName:(NSString *)assetName andSyncGroupName:(NSString *)syncGroupName;

/**
* Initialize a resource object from data on disk, plus a known content type.
* Typically, the content type is recorded in the associated manifest.
*
* param path the path of the file
* param type the content type
* param errorPtr the error to set
*/
+ (id)resourceWithContentsOfFile:(NSString *)path andContentType:(NSString *)type withError:(NSError **)errorPtr;

/**
* Initialize a resource object from JSON data with a default content type of "application/json"
*
* param jsonData the json data
* param errorPtr the error to set
*/
+ (id)resourceWithJSONData:(id)jsonData withError:(NSError **)errorPtr;

/**
* Initialize a resource object from JSON data.
*
* param jsonData the json data
* param type the content type
* param errorPtr the error to set
*/
+ (id)resourceWithJSONData:(id)jsonData andContentType:(NSString *)type withError:(NSError **)errorPtr;


/** The bytes that compose this resource. */
@property (nonatomic) NSData *data;

/** The path to the local file representing the resource. */
@property (nonatomic) NSString *path;

/** The MD5 hash of this resource. */
@property (nonatomic) NSString *md5;

/** The content length of this resource. */
@property (nonatomic) NSNumber *length;

/** The version number of this resource. */
@property (nonatomic) NSString *version;

/** Whether this resource is renderable */
@property (nonatomic, getter = isRenderable) BOOL renderable;

/** Optional metadata of this resource. */
@property (nonatomic) NSDictionary *optionalMetadata;

@end

#endif
