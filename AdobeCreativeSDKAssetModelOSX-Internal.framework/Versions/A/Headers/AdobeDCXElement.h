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

@class AdobeDCXManifestNode;
@class AdobeDCXMutableManifestNode;
@class AdobeDCXNode;
@class AdobeDCXComponent;
@class AdobeDCXMetadata;
@class AdobeDCXMutableMetadata;

/**
* Provides a read/write interface to DCX element nodes that are associated with a composite
* branch, but which have independent local storage until the composite is updated by calling
* updateElement, or any element-specific changes are abandoned by calling abandonElement
* on the AdobeDCXCompositeMutableBranch to which they belong.
*/
@interface AdobeDCXElement : NSObject <NSCopying>

#pragma mark - Properties
/** The name of the element */
@property (nonatomic) NSString *name;

/** The mime type of the element */
@property (nonatomic) NSString *type;

/** The immutable root node of the element */
@property (nonatomic, readonly) AdobeDCXNode *root;

/**
* Is YES if the element has in-memory changes that haven't been updated in a composite branch yet
* by calling replaceElement or copyElement. */
@property (nonatomic, readonly) BOOL isDirty;

#pragma mark - Metadata

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
* brief Best effort attempt to update metadata for a component.
* Will create side-by-side metadata if necessary.
*/
- (BOOL)updateMetadata:(AdobeDCXMetadata *)metadata forComponent:(AdobeDCXComponent *)component withError:(NSError **)errorPtr;

/**
* brief Optimized way to add compomemt along with metadata. Will create side-by-side metadata if necessary.
* note This is not fully atomic since upon failure it can leave the input file with updated metadata.
*/
- (AdobeDCXComponent *)addComponent:(AdobeDCXComponent *)component
toNode:(AdobeDCXNode *)node
fromFile:(NSString *)sourceFile copy:(BOOL)copy
withMetadata:(AdobeDCXMetadata *)metadata
withError:(NSError **)errorPtr;


#pragma mark - Components
/** name Components */
/**@{*/

/**
* brief Returns the list of components for the specified node.
*
* param node    The node for which to return the list of components of. Can be nil in which case the
*              list of components of the root-level of the manifest will be returned.
*
* return        An NSArray of AdobeDCXComponent objects which can be empty if the provided node doesn't
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
* brief Locates the given component in the manifest and returns the parent AdobeDCXNode.
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

/**
* brief Add the file sourceFile as a component to the composite branch by copying or moving it to the
* appropriate location in local storage and adding it to the manifest. The compositeState of the
* manifest will be marked as modified but the changed manifest will not be written to
* local storage. Use commitChangesWithError: to persist your changes to local storage once
* your are done modifying the composite branch.
*
* param name        The name of the component.
* param componentId The id of the component. Can be nil in which case a UUID will be generated.
* param type        The type of the component.
* param rel         The relationship of the component. Can be nil.
* param path        The path of the component relative to the component directory. Must not be nil.
*                  Note that for local storage schemes other than AdobeDCXLocalStorageSchemeDirectories
*                  this path does not specify the actual path to the component on the local filesystem.
* param node        The child node to add the new component to. Can be nil.
* param sourceFile  The path of the asset file for the component. Must not be nil.
* param copy        If YES the file gets copied, if NO it gets moved and renamed.  Ignored if sourceFile
*                  refers to the current component location defined by the local storage scheme.
* param sourceHref  An absolute href to a file saved in Creative Cloud Storage.  May be nil only if sourceFile is not nil.
* refers to the current component location defined by the local storage scheme.
*
* param errorPtr    Gets set if an error occurs while copying the asset file.
*
* return            The new component.
*/
- (AdobeDCXComponent *)addComponent:(NSString *)name withId:(NSString *)componentId withType:(NSString *)type
withRelationship:(NSString *)rel withPath:(NSString *)path
toNode:(AdobeDCXNode *)node
fromFile:(NSString *)sourceFile copy:(BOOL)copy
fromHref:(NSString *)sourceHref
withError:(NSError **)errorPtr;



/**
* brief Add an unmanaged component to the composite branch. The compositeState of the
* manifest will be marked as modified but the changed manifest will not be written to
* local storage. Use commitChangesWithError: to persist your changes to local storage once
* your are done modifying the composite branch.
*
* Note: When using unmanaged components, make sure to implement and register the ComponentManagerProtocol
* param name        The name of the component.
* param componentId The id of the component. Can be nil in which case a UUID will be generated.
* param type        The type of the component.
* param rel         The relationship of the component. Can be nil.
* param path        The path of the component relative to the component directory. Must not be nil.
*                  Note that for local storage schemes other than AdobeDCXLocalStorageSchemeDirectories
*                  this path does not specify the actual path to the component on the local filesystem.
* param node        The child node to add the new component to. Can be nil.
* param UCID        The UCID string that you want to associate with the the new component.
* param sourceHref  An absolute, URI-encoded href to a file saved in Creative Cloud Storage.  May be nil only if UCID is not nil.
*
* param errorPtr    Gets set if an error occurs while copying the asset file.
*
* return            The new component.
*/
- (AdobeDCXComponent *)addComponent:(NSString *)name withId:(NSString *)componentId withType:(NSString *)type
withRelationship:(NSString *)rel withPath:(NSString *)path
toNode:(AdobeDCXNode *)node
withUCID:(NSString *)UCID
fromHref:(NSString *)sourceHref
withError:(NSError **)errorPtr;


/**
* brief Add the file sourceFile as a component to the composite branch by copying or moving it to the
* appropriate location in local storage and adding it to the manifest.  If specified, sourceHref identifies
* the server resource that can provide the component, although the resource will not be accessed until
* the composite is pushed or the component is explicitly downloaded.
* At least one of the sourceFile and sourceHref parameters must be specified. If both sourceFile and sourceHref
* are specified then they are expected to refer to the same file although this is not verified.
* The compositeState of the manifest will be marked as modified but the changed manifest will not be written to
* local storage. Use commitChangesWithError: to persist your changes to local storage once
* your are done modifying the composite branch.
*
* param component   The component object.
* param node        The child node to add the new component to. Can be nil.
* param sourceFile  The path of the asset file for the component. May be nil only if sourceHref is not nil.
* Note that for local storage schemes other than AdobeDCXLocalStorageSchemeDirectories
* this path does not specify the actual path to the component on the local filesystem.
*
* param copy        If YES the file gets copied, if NO it gets moved and renamed.  Ignored if sourceFile
* refers to the current component location defined by the local storage scheme.
*
* param sourceHref  An absolute, URI-encoded href to a file saved in Creative Cloud Storage.  May be nil only if sourceFile is not nil.
* param errorPtr    Gets set if an error occurs while copying the asset file.
*
* return            The new component.
*/
- (AdobeDCXComponent *)addComponent:(AdobeDCXComponent *)component
toNode:(AdobeDCXNode *)node
fromFile:(NSString *)sourceFile copy:(BOOL)copy
fromHref:(NSString *)sourceHref
withError:(NSError **)errorPtr;

/**
* brief Add an unmanaged component to the composite branch. If specified, sourceHref identifies
* the server resource that can provide the component, although the resource will not be accessed until
* the composite is pushed or the component is explicitly downloaded.
* At least one of the UCID and sourceHref parameters must be specified.
* The compositeState of the manifest will be marked as modified but the changed manifest will not be written to
* local storage. Use commitChangesWithError: to persist your changes to local storage once
* your are done modifying the composite branch.
*
* Note: When using unmanaged components, make sure to implement and register the ComponentManagerProtocol.
* param component   The component object.
* param node        The child node to add the new component to. Can be nil.
* param UCID  The path of the asset file for the component. May be nil only if sourceHref is not nil.
*
*
* param sourceHref  An absolute href to a file saved in Creative Cloud Storage.  May be nil only if sourceFile is not nil.
* param errorPtr    Gets set if an error occurs while copying the asset file.
*
* return            The new component.
*/
- (AdobeDCXComponent*) addComponent:(AdobeDCXComponent*)componentToAdd
toNode:(AdobeDCXNode *)node
fromHref:(NSString*)sourceHref
withUCID:(NSString*)UCID
withError:(NSError**)errorPtr;

/**
* brief Update the the component by copying or moving sourceFile to the appropriate location
* in local storage and updating the component record. The compositeState of the
* manifest will be marked as modified but the changed manifest will not be written to
* local storage. Use commitChangesWithError: to persist your changes to local storage once
* your are done modifying the composite.
*
* param component   The component.
* param sourceFile  The asset file for the component. Can be nil in which case only the properties of
*                  the component will be updated.
* param copy        If YES the file gets copied, if NO it gets moved and renamed.
* param errorPtr    Gets set if an error occurs while copying the asset file.
*
* return            The updated component.
*/
- (AdobeDCXComponent *)updateComponent:(AdobeDCXComponent *)component
fromFile:(NSString *)sourceFile copy:(BOOL)copy
withError:(NSError **)errorPtr;

/**
* brief Update the unmanaged component with a new UCID. The compositeState of the
* manifest will be marked as modified but the changed manifest will not be written to
* local storage. Use commitChangesWithError: to persist your changes to local storage once
* your are done modifying the composite.
* Note: When using unmanaged components, make sure to implement and register the ComponentManagerProtocol.
*
* param component   The component.
* param UCID        The UCID string that you want to associate with the the component.
* param errorPtr    Gets set if an error occurs while copying the asset file.
*
* return            The updated component.
* note              Updating the component with UCID makes it an unmanaged component. If it was previously a managed component then
the earlier file associated the managed storage might get garbage collected.
*/
- (AdobeDCXComponent *)updateComponent:(AdobeDCXComponent *)component
withUCID:(NSString *)UCID
withError:(NSError **)errorPtr;

/** Moves the existing component to a different child node.
*
* param component   The component to move.
* param node        The node to move the component to. If nil the component will get moved to the root level.
* param errorPtr    Gets set in the case of a failure.
*
* return            The moved AdobeDCXComponent or nil in the case of a failure.
*
* note Component must already exist within the branch.
*/
- (AdobeDCXComponent *)moveComponent:(AdobeDCXComponent *)component toNode:(AdobeDCXNode *)node
withError:(NSError **)errorPtr;

/** Copies the existing component from a different composite branch to the specified
* child node. Fails if it already exists in this branch.
*
* param component   The component to copy.
* param branchOrElement The branch or element that contains the component. May be a branch on either the same or a different composite.
* param node        The node to copy the component to. If nil the component will get copied to the root level.
* param errorPtr    Gets set in the case of a failure.
*
* return            The copied AdobeDCXComponent or nil in the case of a failure.
*/
- (AdobeDCXComponent *)copyComponent:(AdobeDCXComponent *)component from:(id)branchOrElement
toNode:(AdobeDCXNode *)node withError:(NSError **)errorPtr;


/** Copies the existing component from a different composite branch to the specified
* child node. Assigns newPath to the path property of the component and also assigns a new id to it.
*
* param component   The component to copy.
* param branchOrElement The branch or element that contains the component. May be a branch on either the same or a different composite.
* param node        The node to copy the component to. If nil the component will get copied to the root level.
* param newPath     The new path for the component.
* param errorPtr    Gets set in the case of a failure.
*
* return            The copied AdobeDCXComponent or nil in the case of a failure.
*/
- (AdobeDCXComponent *)copyComponent:(AdobeDCXComponent *)component from:(id)branchOrElement
toNode:(AdobeDCXNode *)node newPath:(NSString *)newPath
withError:(NSError **)errorPtr;


/**
* brief Replaces the component with the same id as the specified component from a different composite branch.  Fails if
* it the component doesn't exist in this branch.
*
* param component   The component from another branch
* param branchOrElement The branch or element that contains the component. May be a branch on either the same or a different composite.
* param errorPtr    Gets set in the case of a failure.
*
* return            The copied AdobeDCXComponent or nil in the case of a failure.
*/
- (AdobeDCXComponent *)replaceComponent:(AdobeDCXComponent *)component from:(id)branchOrElement
withError:(NSError **)errorPtr;

/**
* brief Removes the component from the branch.
*
* param component   The component to remove.
*
* return            The removed component.
*/
- (AdobeDCXComponent *)removeComponent:(AdobeDCXComponent *)component;

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
* brief Locates the given child node in the manifest and returns its parent the parent AdobeDCXNode.
* Returns nil if not found.
*
* param component The component to return the parent for.
*
* return The AdobeDCXNode that is the parent of child. Returns nil if not found.
*/
- (AdobeDCXNode *)findParentOfNode:(AdobeDCXNode *)node foundIndex:(NSUInteger *)index;

/**
* brief Appends a new child node with the specified properties at the end of the list of children of parent.
*
* param name      The name of the new node.  Optional - may be nil.
* param nodeId    The unique id of the new node. Optional - may be nil, in which case a UUID will be generated automatically.
* param type      The media type associated with the data stored at this child node. Optional - may be nil.
* param path      The logical path associated with the node within the composite. Optional - may be nil.
* param parentNode  The node to add the child node to. Optional - may be be nil, in which case the node will be added
*                  to the list of children at the root of the manifest.
* param errorPtr  Gets set in the event of an error
* return          The newly appended node or nil if an error occurss
*/
- (AdobeDCXNode *)appendNode:(NSString *)name withId:(NSString *)nodeId withType:(NSString *)type withPath:(NSString *)path
toParent:(AdobeDCXNode *)parentNode withError:(NSError **)errorPtr;

/**
* brief Insert node as a new child node with the specified properties into the list of children of parent node at the given index.
*
* param name      The name of the new node.  Optional - may be nil.
* param nodeId    The unique id of the new node. Optional - may be nil, in which case a UUID will be generated automatically.
* param type      The media type associated with the data stored at this child node. Optional - may be nil.
* param path      The logical path associated with the node within the composite. Optional - may be nil.
* param parentNode  The node to add the child node to. Optional - may be be nil, in which case the node will be added
*                  to the list of children at the root of the manifest.
* param index       The index where to add this child node.

* param errorPtr    Gets set in the event of an error
* return            The newly appended node or nil if an error occurss
*/
- (AdobeDCXNode *)insertNode:(NSString *)name withId:(NSString *)nodeId withType:(NSString *)type withPath:(NSString *)path
toParent:(AdobeDCXNode *)parentNode atIndex:(NSUInteger)index withError:(NSError **)errorPtr;

/**
* brief Moves a node from its current parent/index to a new parent/index.
*
* param node        The node to move.
* param parentNode  The node whose children list to move the child node to. Can be nil in which
*                  case the node will be move to the list of children at the root of the manifest.
* param index       The index where to add this child node.
*
* return            The moved child.
*
* note              node must already be a child node of the branch.
*/
- (AdobeDCXNode *)moveNode:(AdobeDCXNode *)node toParent:(AdobeDCXNode *)parentNode
toIndex:(NSUInteger)index withError:(NSError **)errorPtr;

/**
* brief Copies the node including all its components and sub nodes to the specified parent/index.
* description Assigns the given newPath as the path, and newId as the nodeId, of the new child node and
* ensures that all copied sub-nodes and components get new ids if the path or nodeId has changed
* or if we are copying between different composites.
*
* param node        The source node on another branch or element that will be copied to this branch
* param parentNode  The node whose children list to copy the child node to. Can be nil in which
*                  case the node will be copied to the list of children at the root of the manifest.
* param index       The index where to add this child node.
* param errorPtr    Gets set in the case of a failure.
*
* return            The copied child or nil in the case of a failure.
*
* note The source node must refer to a node that exists on another branch or element.
*/
- (AdobeDCXNode *)copyNode:(AdobeDCXNode *)node toParent:(AdobeDCXNode *)parentNode toIndex:(NSUInteger)index
withError:(NSError **)errorPtr;

/**
* brief Copies the node including all its components and sub nodes to the specified parent/index.
* description Assigns the given newPath as the path, and newId as the nodeId, of the new child node and
* ensures that all copied sub-nodes and components get new ids if the path or nodeId has changed
* or if we are copying between different composites.
*
* param node        The source node on another branch or element that will be copied to this branch
* param parentNode  The node whose children list to copy the child node to. Can be nil in which
*                  case the node will be copied to the list of children at the root of the manifest.
* param index       The index where to add this child node.
* param newPath     Optional. The new path for the child node.
* param newId       Optional. The new id for the child node.
* param errorPtr    Gets set in the case of a failure.
*
* return            The copied child or nil in the case of a failure.
*
* note The source node must refer to a node that exists on another branch or element.
*/
- (AdobeDCXNode *)copyNode:(AdobeDCXNode *)node toParent:(AdobeDCXNode *)parentNode toIndex:(NSUInteger)index
withPath:(NSString *)newPath withId:(NSString*)newId withError:(NSError **)errorPtr;

/**
* brief Replaces the node with the same ID on this branch, including all its components and sub nodes.
*
* param node        The source node that replaces the node that shares the same ID on this branch
* param errorPtr    Gets set in the case of a failure.
*
* return            The node that was replaced in this branch or nil in the case of a failure.
*
* note The replacement node must refer to a node that exists on another branch or element.
*/
- (AdobeDCXNode *)replaceNode:(AdobeDCXNode *)node withError:(NSError **)errorPtr;

/**
* brief Removes the node from the manifest.
*
* param node The node to remove.
*
* return The removed child as a AdobeDCXNode.
*/
- (AdobeDCXNode *)removeNode:(AdobeDCXNode *)node;

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
