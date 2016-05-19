/*************************************************************************
*
* ADOBE CONFIDENTIAL
* ___________________
*
*  Copyright 2015 Adobe Systems Incorporated
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

#import <Foundation/Foundation.h>

@class AdobeDCXManifest;

/**
* class AdobeDCXNode
* brief Represents a child node of an AdobeDCXBranch, AdobeDCXMutableBranch or AdobeDCXElement.
* Allows write access to its properties if it refers to a node in a mutable branch.
*
* Notice that AdobeDCXManifestNode doesn't give you access to the components or
* children of a node. But you can use it to manipulate the components and children
* via the AdobeDCXMutableBranch or AdobeDCXElement classes.
*
*/
@interface AdobeDCXNode : NSObject

#pragma mark Properties

/** The name of the node. */
@property (nonatomic) NSString *name;

/** The type of the node. */
@property (nonatomic) NSString *type;

/** The relationship of the node. */
@property (nonatomic) NSString *relationship;

/** The unique path of the node relative to its parentPath.
note Use the setPathWithError method to set the path property.*/
@property (nonatomic, readonly) NSString *path;

/** The absolute path defined by the node's enclosing nodes. */
@property (nonatomic, readonly) NSString *parentPath;

/** The unique absolute path of the node. Is nil if the node doesn't have a path property.*/
@property (nonatomic, readonly) NSString *absolutePath;

/** Whether the node is the root node. */
@property (nonatomic, readonly) BOOL isRoot;

/** Indicates whether the node is a DCX element (i.e. has type and name properties) */
@property (nonatomic, readonly) BOOL isElement;

/** The id of the node. */
@property (nonatomic, readonly) NSString *nodeId;

/** Returns an array of keys for all custom properties that have been set via setValue:ForKey on this object */
@property (nonatomic, readonly, copy) NSArray *customKeys;

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
* brief Sets the value for the named attribute key.
*
* param value The new value of the attribute. Must not be nil.
* param key The name of the attribute.
*/
- (void)setValue:(id)value forKey:(NSString*)key;

/**
* brief Removes a named attribute from the component. Use this to remove attributes
* that are not exposed as separate properties.
*
* param key The name of the attribute.
*/
- (void)removeValueForKey:(NSString*)key;

/**
brief Sets the logical path associated with the node in the DCX DOM

param path  The relative path of the node
param errorPtr  Contains error information in the event that path is illegal or colides with
an existing absolute path, if the node is hosted on a branch or element.

return YES if successful; NO if an error occurs
*/
- (BOOL)setPath:(NSString *)path withError:(NSError **)errorPtr;

@end


