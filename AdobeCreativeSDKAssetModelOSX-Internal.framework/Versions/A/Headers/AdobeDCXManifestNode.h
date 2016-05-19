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

#ifndef AdobeDCXManifestNodeHeader
#define AdobeDCXManifestNodeHeader

#import <Foundation/Foundation.h>

@class AdobeDCXManifest;

/**
* class AdobeDCXManifestNode
* brief Represents a child node of a AdobeDCXManifest. Allows read-only access to
* its properties. If you want to modify a manifest node you need to create a
* mutable copy of it (e.g. copy = [node mutableCopy]).
*
* Notice that AdobeDCXManifestNode doesn't give you access to the components or
* children of a node. But you can use it to get the components and children
* from the AdobeDCXManifest.
*
*/
@interface AdobeDCXManifestNode : NSObject <NSMutableCopying>
{
@protected
NSMutableDictionary *_dict; /**< The underlying dictionary of the node. */
Boolean _isRoot;
AdobeDCXManifest __weak *_manifest;
}


#pragma mark Properties

/** The manifest the node is a part of. */
@property (nonatomic, readonly, weak) AdobeDCXManifest *manifest;

/** The name of the node. */
@property (nonatomic, readonly) NSString *name;

/** The unique path of the node relative to its parentPath. */
@property (nonatomic, readonly) NSString *path;

/** The absolute path defined by the node's enclosing nodes. */
@property (nonatomic, readonly) NSString *parentPath;

/** The id of the enclosing node. */
@property (nonatomic, readonly) NSString *parentId;

/** The unique absolute path of the node. Is nil if the node doesn't have a path property.*/
@property (nonatomic, readonly) NSString *absolutePath;

/** Whether the node is the root node. */
@property (nonatomic, readonly) Boolean isRoot;

/** The type of the node. */
@property (nonatomic, readonly) NSString *type;

/** The relationship of the node. */
@property (nonatomic, readonly) NSString *relationship;

/** The id of the node. */
@property (nonatomic, readonly) NSString *nodeId;

/** The dictionary that was used to construct this node. */
@property (nonatomic, readonly) NSDictionary *dict;

/** Indicates whether the node is a DCX element (i.e. has type and name properties) */
@property (nonatomic, readonly) BOOL isElement;

/**
* brief Returns the value of a named attribute of the node or nil if the attribute
* doesn't exist. Use this to access attributes
* that are not exposed as properties.
*
* param key The name of the attribute.
*
* return The value of the attribute.
*/
- (id)valueForKey:(NSString *)key;

/**
* brief The absolute index of the manifest node within the hierarchy for child nodes of the
* manifest.
*
* return The absolute index of the manifest node within the hierarchy for child nodes of the
* manifest. NSNotFound if the node is not a child of a manifest.
*/
- (NSUInteger)absoluteIndex;

@end

#endif
