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

#ifndef AdobeDCXMutableManifestNodeHeader
#define AdobeDCXMutableManifestNodeHeader

#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeDCXManifestNode.h>

/**
* class AdobeDCXMutableManifestNode
* brief Represents a child node of a AdobeDCXManifest. Allows read and write access to
* its properties.
*
* Notice that AdobeDCXManifestNode doesn't give you access to the components or
* children of a node. But you can use it to manipulate the components and children
* via the AdobeDCXManifest.
*
*/
@interface AdobeDCXMutableManifestNode : AdobeDCXManifestNode

#pragma mark Initializers

/**
* brief Initializer
* param nodeId - the id of the node
* param name the name
*/
- (instancetype)initWithId:(NSString *)nodeId name:(NSString *)name;

/**
* brief Initializer
* param type the type
* param path the path
* param name the name
*/
- (instancetype)initWithType:(NSString *)type path:(NSString *)path name:(NSString *)name;

/**
* brief Initializer
* param nodeDict the dictionary to initialize with
* param parentPath  The parent path of the node.
* param parentId    The parent's id.
*/
- (instancetype)initWithDictionary:(NSMutableDictionary *)nodeDict parentPath:(NSString *)parentPath parentId:(NSString*)parentId;


#pragma mark Convenience methods

/**
* brief Constructs a mutable manifest node with the given type, path and name.
*
* param name The name of the new node.
*/
+ (instancetype)nodeWithType:(NSString *)type path:(NSString *)path name:(NSString *)name;

/**
* brief Constructs a mutable manifest node with the given name and a random id.
*
* param name The name of the new node.
*/
+ (instancetype)nodeWithName:(NSString *)name;

/**
* brief Constructs a mutable manifest node with the given id.
*
* param nodeId The id of the new node.
*/
+ (instancetype)nodeWithId:(NSString *)nodeId;



#pragma mark Properties

/** The name of the node. */
@property (nonatomic) NSString *name;

/** The path of the node. */
@property (nonatomic) NSString *path;

/** The type of the node. */
@property (nonatomic) NSString *type;

/** The id of the node. */
@property (nonatomic) NSString *nodeId;

/** The relationship of the node */
@property (nonatomic) NSString *relationship;

/**
* brief Sets the value for the named attribute key.
*
* param value The new value of the attribute. Must not be nil.
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
