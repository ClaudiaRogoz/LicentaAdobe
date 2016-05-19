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

// Reviewed by rhorns on October 10, 2013

#ifndef AdobeDCXComponentHeader
#define AdobeDCXComponentHeader

#import <Foundation/Foundation.h>

@class AdobeDCXManifest;

/**
* class AdobeDCXComponent
* brief Wrapper for a component in a AdobeDCXManifest. Notice that this is an immutable
* object. If you want to modify a component you need to create a mutable copy
* (e.g. copy = [component mutableCopy]).
*/
@interface AdobeDCXComponent : NSObject <NSMutableCopying> {
@protected
NSDictionary *_dict;     /**< The underlying dictionary of the component. */
}


#pragma mark Initializers

/**
* brief Initializes with a dictionary containing the properties of the component.
* This initializer is used when constructing a component from a parsed manifest.
* Notice that the initializer doesn't check the dictionary for validity.
*
* param compDict    The NSDictionary containing the properties of the component.
* param manifest    The AdobeDCXManifest that conatins the component.
* param parentPath  The paren path of the component.
* param parentId    The id of the parent node.
*/
- (id)initWithDictionary:(NSDictionary *)compDict andManifest:(AdobeDCXManifest *)manifest parentPath:(NSString *)parentPath parentId:(NSString*)parentId;


#pragma mark Convenience methods

/**
* brief Constructs a component from a dictionary containing the properties of the component.
* This method is used by AdobeDCXManifest when constructing one of its components.
* Notice that the method doesn't check the dictionary for validity.
*
* param compDict    The NSDictionary containing the properties of the component.
* param manifest    The AdobeDCXManifest that conatins the component.
* param parentPath  The paren path of the component.
* param parentId    The id of the parent node.
*/
+ (id)componentFromDictionary:(NSDictionary *)compDict andManifest:(AdobeDCXManifest *)manifest parentPath:(NSString *)parentPath parentId:(NSString*)parentId;



#pragma mark Properties

/** The manifest the component is a part of. */
@property (nonatomic, readonly, weak) AdobeDCXManifest *manifest;

/** The unique identifier of the component. */
@property (nonatomic, readonly) NSString *componentId;

/** The unique path of the component relative to its parentPath. */
@property (nonatomic, readonly) NSString *path;

/** The absolute path defined by the component's enclosing nodes. */
@property (nonatomic, readonly) NSString *parentPath;

/** The id of the parent node. */
@property (nonatomic, readonly) NSString *parentId;

/** The unique absolute path of the component. */
@property (nonatomic, readonly) NSString *absolutePath;

/** The name of the component. */
@property (nonatomic, readonly) NSString *name;

/** The relationship type of the component. */
@property (nonatomic, readonly) NSString *relationship;

/** The mime type of the component's asset file. */
@property (nonatomic, readonly) NSString *type;

/** List of links keyed by link type. Can be nil. */
@property (nonatomic, readonly) NSDictionary *links;

/** The AdobeDCXAssetState of the component. */
@property (nonatomic, readonly) NSString *state;

/** The etag of the manifest asset on the server. */
@property (nonatomic, readonly) NSString *etag;

/** The md5 hash of the manifest asset on the server. */
@property (nonatomic, readonly) NSString *md5;

/** The version of the manifest asset on the server. */
@property (nonatomic, readonly) NSString *version;

/** The content length of the manifest asset on the server. */
@property (nonatomic, readonly) NSNumber *length;

/** The width of the component. */
@property (nonatomic, readonly) NSNumber *width;

/** The height of the component. */
@property (nonatomic, readonly) NSNumber *height;

/** Is YES if the component is bound to a specific resource on the server. */
@property (nonatomic, readonly) BOOL isBound;

/** The dictionary that was used to construct this component. */
@property (nonatomic, readonly) NSDictionary *dict;


#pragma mark Methods

/**
* brief Returns a named attribute of the component. Use this to access attributes
* that are not exposed as separate properties.
*
* param key The name of the attribute.
*/
- (id)valueForKey:(NSString *)key;

@end

#endif
