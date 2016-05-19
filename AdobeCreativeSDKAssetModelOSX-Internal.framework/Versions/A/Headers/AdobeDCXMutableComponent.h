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

#ifndef AdobeDCXMutableComponentHeader
#define AdobeDCXMutableComponentHeader

#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeDCXComponent.h>

@class AdobeStorageResourceItem;
@class AdobeDCXManifest;

/**
* class AdobeDCXMutableComponent
* brief Mutable version of AdobeDCXComponent.
*/
@interface AdobeDCXMutableComponent : AdobeDCXComponent

#pragma mark Convenience methods

/**
* brief Constructs a mutable component.
*
* param componentId         The unique identifier of the component.
* param path                The path of the component relative to its parent node
* param name                The name of the component.
* param type                The mime type of the component's asset file.
* param relationship        The relationship type of the component's asset file.
*
* note  When using the AdobeDCXLocalStorageCopyOnWrite local storage scheme, the path does not
* refer to the actual file path of the component on disk.  However, if the path contains a valid
* file extension then this will be preserved when constructing the file's actual path on disk.
*/
+ (id)componentWithId:(NSString *)componentId path:(NSString *)path name:(NSString *)name
type:(NSString *)type relationship:(NSString *)relationship;


#pragma mark Initializers

/**
* brief Designated initializer. Creates new mutable dictionary containing the properties
* that are being passed in via the parameter.
*
* param componentId The unique identifier of the component.
* param path The path of the component relative to its parent node
* param name The name of the component.
* param type The mime type of the component's asset file.
* param links The links of the component.
* param state The AdobeDCXAssetState of the component.
*/
- (id)initWithId:(NSString *)componentId path:(NSString *)path name:(NSString *)name type:(NSString *)type
links:(NSDictionary *)links state:(NSString *)state;

/**
* brief Initializes with a mutable dictionary containing the properties of the component.
* Notice that the initializer doesn't check the dictionary for validity.
*
* param compDict    The NSMutableDictionary containing the properties of the component.
* param manifest    The AdobeDCXManifest that conatins the component.
* param parentPath  The paren path of the component.
* param parentId    The id of its parent.
*
* note  When using the AdobeDCXLocalStorageCopyOnWrite local storage scheme, the path does not
* refer to the actual file path of the component on disk.  However, if the path contains a valid
* file extension then this will be preserved when constructing the file's actual path on disk.
*/
- (id)initWithDictionary:(NSMutableDictionary *)compDict andManifest:(AdobeDCXManifest *)manifest
parentPath:(NSString *)parentPath parentId:(NSString*)parentId;


#pragma mark Properties

// Override the properties as mutable.

/** The unique identifier of the component. */
@property (nonatomic) NSString *componentId;

/** The unique path of the component relative to its parentPath. */
@property (nonatomic) NSString *path;

/** The name of the component. */
@property (nonatomic) NSString *name;

/** The mime type of the component's asset file. */
@property (nonatomic) NSString *type;

/** The relationship type of the component. */
@property (nonatomic) NSString *relationship;

/** List of links keyed by link type. */
@property (nonatomic) NSMutableDictionary *links;

/** The AdobeDCXAssetState of the component. */
@property (nonatomic) NSString *state;

/** The etag of the manifest asset on the server. */
@property (nonatomic) NSString *etag;

/** The md5 hash of the manifest asset on the server. */
@property (nonatomic) NSString *md5;

/** The version of the manifest asset on the server. */
@property (nonatomic) NSString *version;

/** The content length of the manifest asset on the server. */
@property (nonatomic) NSNumber *length;

/** The width of the component. */
@property (nonatomic) NSNumber *width;

/** The height of the component. */
@property (nonatomic) NSNumber *height;


#pragma mark Methods

/**
* brief Sets a named attribute of the component. Use this to modify attributes
* that are not exposed as separate properties.
*
* param value The new value of the attribute.
* param key The name of the attribute.
*/
- (void)setValue:(id)value forKey:(NSString *)key;

/**
* brief Removes a named attribute from the component. Use this to remove attributes
* that are not exposed as separate properties.
*
* param key The name of the attribute.
*/
- (void)removeValueForKey:(NSString *)key;

@end

#endif
