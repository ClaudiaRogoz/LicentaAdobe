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

#ifndef AdobeDCXCompositeBranchHeader
#define AdobeDCXCompositeBranchHeader

#import <Foundation/Foundation.h>

@class AdobeDCXManifestNode;
@class AdobeDCXNode;
@class AdobeDCXComponent;
@class AdobeDCXMetadata;
@class AdobeDCXMutableMetadata;
@class AdobeDCXElement;

/**
* Gives read-only access to the DOM of a specific branch of a composite.
*/

@interface AdobeDCXCompositeBranch : NSObject <NSMutableCopying>

/** The name of the composite described in the manifest. */
@property (nonatomic, readonly) NSString *name;

/** The mime type of the composite described in the manifest. */
@property (nonatomic, readonly) NSString *type;

/** The links of the manifest. */
@property (nonatomic, readonly) NSDictionary *links;

/** The state of the composite. */
@property (nonatomic, readonly) NSString *compositeState;

/** The etag of the composite branch. Can be nil for a branch that has never been pushed. */
@property (nonatomic, readonly) NSString *etag;

/** The server version of the composite branch.
* Can be nil for a branch that has never been pushed or was last pushed prior to the addition of this property.
*/
@property (nonatomic, readonly) NSString *version;

/** The immutable root node of the underlying manifest. */
@property (nonatomic, readonly) AdobeDCXNode *root;

/** A set containing AdobeDCXElement objects that are currently connected to this branch. */
@property (nonatomic, readonly) NSSet *pendingElements;
/**
* brief The metadata for this composite branch
* Returns the metadata associated with this branch, reading from the metadata component if necessary and
* returning nil if there is no metadata component.
* Contrast with the same method on AdobeDCXComposite which will initialize missing metadata from the manifest.
*/
@property (nonatomic, readonly) AdobeDCXMetadata *metadata;

/**
* brief The metadata for a component.
* Returns the metadata for a component if present, nil otherwise.
* This will return the side-by-side metadata if present and otherwise will try to load metadata from the
* component's contents
*/
- (AdobeDCXMetadata *)metadataForComponent:(AdobeDCXComponent *)component withError:(NSError **)errorPtr;

/**
* brief The metadata for a component, creating initial minimal metadata if not present.
*/
- (AdobeDCXMutableMetadata *)getOrCreateMetadataForComponent:(AdobeDCXComponent *)component withError:(NSError **)errorPtr;

/**
* brief Returns the metadata for an element, creating it if necessary.
*/
- (AdobeDCXMetadata *)metadataForElementNode:(AdobeDCXNode *)elementNode;

/**
* brief Returns the value of a named attribute of the node or nil if the attribute
* doesn't exist. Use this to access attributes that are not exposed as properties.
*
* param key The name of the attribute.
*
* return The value of the attribute.
*/
- (id)valueForKey:(NSString *)key;

#pragma mark - Components
/** name Components */
/**@{*/

/**
* brief Returns the list of components for the specified child node.
*
* param node  The node for which to return the list of components of. Can be nil in which case the
*              list of components of the root-level of the manifest will be returned.
*
* return      An NSArray of AdobeDCXComponent objects which can be empty if the provided node doesn't
*              have any components.
*/
- (NSArray *)getComponentsOfNode:(AdobeDCXNode *)node;

/**
* brief Returns the component with the given id or nil if it doesn't exist.
*
* param componentId     The id of the requested component.
*
* return                The component with the given id or nil if it doesn't exist.
*/
- (AdobeDCXComponent *)getComponentWithId:(NSString *)componentId;

/**
* brief Returns the component with the given absolute path or nil.
*
* param absPath The absolute path of the requested component.
*
* return The component with the given absolute path or nil.
*/
- (AdobeDCXComponent *)getComponentWithAbsolutePath:(NSString *)absPath;

/**
* brief Locates the given component in the manifest and returns the parent AdobeDCXManifestNode.
* Returns nil if not found.
*
* param component The component to return the parent for.
*
* return The AdobeDCXNode that is the parent of component. Returns nil if not found.
*/
- (AdobeDCXNode *)findParentNodeOfComponent:(AdobeDCXComponent *)component;

/**
* brief         Returns the list of all components referred to by the manifest of this composite branch.
*
* return        An NSArray of AdobeDCXComponent objects which can be empty if the composite does not have any components.
*/
- (NSArray *)getAllComponents;



/**
* brief Returns the file path of the local file asset of the given component in the composite branch.
*
* param component   The component to get the path for.
* param errorPtr    Optional pointer to an NSError that gets set if the path of the component is invalid.
*
* return            The file path of the local file asset of the given component or nil if it hasn't been pulled
* yet or if it is not valid (errorPtr != nil).
*/
- (NSString *)pathForComponent:(AdobeDCXComponent *)component withError:(NSError **)errorPtr;


/**@}*/
#pragma mark - Child Nodes
/** name Child Nodes */
/**@{*/

/**
* brief Get the list of child nodes for the specified node.
*
* param node The node for which to return the list of child nodes.  Can be nil in which case the
* list of children of the root-level of the manifest will be returned.
*
* return An NSArray of AdobeDCXNode objects which can be empty if the provided node doesn't
* have any children.
*/
- (NSArray *)getChildrenOfNode:(AdobeDCXNode *)node;

/**
* brief Returns the child node with the given id or nil if it node doesn't exist.
*
* param componentId The id of the requested child node.
*
* return The child node with the given id or nil if it doesn't exist.
*/
- (AdobeDCXNode *)getNodeWithId:(NSString *)nodeId;

/**
* brief Returns the child node with the given absolute path or nil.
*
* param absPath The absolute path of the requested child node.
*
* return The child node with the given absolute path or nil.
*/
- (AdobeDCXNode *)getNodeWithAbsolutePath:(NSString *)absPath;

/**
* brief Locates the given child node in the manifest and returns its parent the parent AdobeDCXManifestNode.
* Returns nil if not found.
*
* param component The component to return the parent for.
*
* return The AdobeDCXNode that is the parent of child. Returns nil if not found.
*/
- (AdobeDCXNode *)findParentOfNode:(AdobeDCXNode *)node foundIndex:(NSUInteger *)index;

#pragma mark - Renditions

/**
* brief Returns a rendition component or element node associated with the specified node, if it exists, that has the minimum dimensions and matches
* at least one of the accepted media types
*
* param node  The node that is used as the root of the item with the associated rendition.  Defaults to using the root node if this parameter is nil.
* param minWidth  The minimum width of the returned rendition component. Optional - may be nil.
* param minHeight The minimum height of the returned rendtion component. Optional - may be nil.
* param acceptedTypes An array of accepted media types.  Wildcards are not supported and string comparision is case-insensitive when matching media types.
*
* return An AdobeDCXComponent or AdobeDCXNode object that represents the rendition, or nil if none can be found that matches any of the acceptedTypes.
*
* note This method will attempt to return the smallest rendition that satifies minHeight and minWidth.  If neither minHeight or minWidth are specified, or if those minimum
* dimensions cannot be achieved, then the largest rendition that matches one the accepted media will be returned.
*/
- (id)getRenditionAtNode:(AdobeDCXNode*)node withMinWidth:(NSNumber*)minWidth withMinHeight:(NSNumber*)minHeight acceptedMediaTypes:(NSArray*)acceptedTypes;

/**@}*/

@end

#endif
