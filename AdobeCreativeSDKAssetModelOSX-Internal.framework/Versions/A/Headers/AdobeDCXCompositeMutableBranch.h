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

#ifndef AdobeDCXCompositeMutableBranchHeader
#define AdobeDCXCompositeMutableBranchHeader

#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeDCXCompositeBranch.h>

@class AdobeDCXMutableMetadata;

/**
* Gives read-write access to the DOM of a specific branch of a composite.
*/
@interface AdobeDCXCompositeMutableBranch : AdobeDCXCompositeBranch


/** The name of the composite described in the manifest. */
@property (nonatomic) NSString *name;

/** The mime type of the composite described in the manifest. */
@property (nonatomic) NSString *type;

/** The links of the manifest. */
@property (nonatomic) NSDictionary *links;

/** The state of the composite. */
@property (nonatomic, readonly) NSString *compositeState;

/** The etag of the composite branch. Can be nil for a new composite. */
@property (nonatomic) NSString *etag;

/** Is YES if the branch has in-memory changes that haven't been committed to local storage yet. */
@property (nonatomic, readonly) BOOL isDirty;

/**
* brief Sets the value for the named attribute key.
*
* param value The new value of the attribute. Must not be nil.
* param key The name of the attribute.
*/
- (void)setValue:(id)value forKey:(NSString *)key;

/**
* brief Removes a named attribute from the branch. Use this to remove attributes
* that are not exposed as separate properties.
*
* param key The name of the attribute.
*/
- (void)removeValueForKey:(NSString *)key;

/**
* brief Marks the composite for deletion by setting its compositeState property to AdobeDCXAssetStatePendingDelete
*
* note Throws an NSInternalInconsistencyException if the current compositeState is AdobeDCXAssetStateCommittedDelete,
* which indicates that the composite has already been deleted from the server
*/
- (void)markCompositeForDeletion;

#pragma mark - Components
/** name Components */
/**@{*/

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

/** Moves the existing component to a different child node on the same branch
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

/** Copies the existing component from a different composite branch or element to the specified
* child node. Fails if it already exists in this branch.
*
* param component   The component to copy.
* param branchOrElement  The branch or element that contains the component. May be a branch on either the same or a different composite.
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
* param branchOrElement  The branch or element containing the component. May be a branch on either the same or a different composite.
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
* brief Appends a new child node with the specified properties at the end of the list of children of parent.
*
* param name      The name of the new node.  Optional - may be nil.
* param nodeId    The unique id of the new node. Optional - may be nil, in which case a UUID will be generated automatically.
* param type      The media type associated with the data stored at this child node. Optional - may be nil.
* param path      The logical path associated with the node within the composite. Optional - may be nil.
* param parentNode  The node to add the child node to. Optional - may be be nil, in which case the node will be added
*                  to the list of children at the root of the manifest.
* param errorPtr    Gets set in the event of an error
* return            The newly appended node or nil if an error occurss
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
* brief Moves a node from its current parent/index to a new parent/index on the same composite branch.
*
* param node        The node to move.
* param parentNode  The node whose children list to move the child node to. Can be nil in which
*                  case the node will be move to the list of children at the root of the manifest.
* param index       The index where to add this child node.
* param errorPtr    Gets set in the event of an error
*
* return            The moved child.
*
* note              node must already be a child node of the branch.
*/
- (AdobeDCXNode *)moveNode:(AdobeDCXNode *)node toParent:(AdobeDCXNode *)parentNode
toIndex:(NSUInteger)index withError:(NSError **)errorPtr;

/**
* brief Copies the node including all its components and sub nodes to the specified parent/index.
*  Assigns the given newPath as the path, and newId as the nodeId, of the new child node and
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
*  Assigns the given newPath as the path, and newId as the nodeId, of the new child node and
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

/** Removes the node from the manifest.
*
* param node The node to remove.
*
* return The removed child as a AdobeDCXNode that has been disconnected from the branch
*/
- (AdobeDCXNode *)removeNode:(AdobeDCXNode *)node;

/**@}*/
#pragma mark - Storage
/** name Storage */
/**@{*/

/**
* brief Writes the manifest of the composite branch to local storage.
*
* Returns YES if the manifest is successfully written (or if the manifest is not written
* because the composite's manifestPath is nil); NO if an error occurs.
*
* param errorPtr Gets set if an error occurs while writing the manifest file.
*
* return YES on success.
*/
- (BOOL)writeManifestTo:(NSString *)path withError:(NSError **)errorPtr;

/**@}*/
#pragma mark - Metadata
/** name Metadata */
/**@{*/

/** The branch's metadata as a mutable object */
@property (nonatomic, readonly) AdobeDCXMutableMetadata *mutableMetadata;

/**
* brief Return metadata for an element, creating it if necessary.
* This can result in the creation of a new component.
* The metadata can be saved by calling [metadata saveInCompositeBranch:branch withError:&error].
* The element node must have a name property, otherwise an NSInternalInconsistencyException exception
* will be thrown.
*/
-(AdobeDCXMutableMetadata*) getOrCreateMetadataForElementNode:(AdobeDCXNode*)elementNode withError:(NSError**)errorPtr;

/**
* brief Copies the metadata from the source branch to this branch.
*/
- (BOOL)copyMetadataFrom:(AdobeDCXCompositeBranch *)srcBranch withError:(NSError **)errorPtr;

/**
* brief Best effort attempt to update metadata for a component.
* Will create side-by-side metadata if necessary.
*/
- (BOOL)updateMetadata:(AdobeDCXMetadata *)metadata forComponent:(AdobeDCXComponent *)component withError:(NSError **)errorPtr;

/**
* brief Optimized way to add component along with metadata. Will create side-by-side metadata if necessary.
* This is not fully atomic since upon failure it can leave the input file with updated metadata.
*/
- (AdobeDCXComponent *)addComponent:(AdobeDCXComponent *)component
toNode:(AdobeDCXNode *)node
fromFile:(NSString *)sourceFile copy:(BOOL)copy
withMetadata:(AdobeDCXMetadata *)metadata
withError:(NSError **)errorPtr;


/**@}*/

#pragma mark - Elements
/** name Elements */
/**@{*/

/**
* brief Returns the element with the specified absolute path or nil if not found.
*
* param absPath The absolute path of the element
*
* return AdobeDCXElement object
*
* note The branch keeps track of pending element objects.  You must either call
* updateElement or abandonElement when you are done with it so that the branch can
* update its data and perform any necessary clean-up tasks.
**/
- (AdobeDCXElement *)getElementWithAbsolutePath:(NSString *)absPath withError:(NSError **)errorPtr;

/**
* brief Returns the element with the specified node ID or nil if not found.
*
* param nodeId The ID of the element node
*
* return AdobeDCXElement object
*
* note The branch keeps track of pending element objects.  You must either call
* updateElement or abandonElement when you are done with it so that the branch can
* update its data and perform any necessary clean-up tasks.
**/
- (AdobeDCXElement *)getElementWithId:(NSString *)nodeId withError:(NSError **)errorPtr;

/**
* brief Creates and appends new element node at the end of the list of the parentNode's children
*
* param name  The name of the new element
* param elementId The ID of the new element.  If nil then the element will be assigned a new UUID.
* param type  The content type of the new element
* param path  The path of the new element
* param parentNode    The node to add the element node to. If nil then the node will be added
*                      to the list of children at the root of the manifest.
* return      An AdobeDCXElement object rooted at the newly inserted element node
*/
- (AdobeDCXElement *)appendElement:(NSString *)name
withId:(NSString *)elementId
withType:(NSString *)type
withPath:(NSString *)path
toParent:(AdobeDCXNode *)parentNode
withError:(NSError **)errorPtr;


/**
* brief Creates and inserts a new element node at the specified index in the parentNode's children
*
* param name  The name of the new element
* param elementId The ID of the new element.  If nil then the element will be assigned a new UUID.
* param type  The content type of the new element
* param path  The path of the new element
* param parentNode    The node to add the element node to. If nil then the node will be added
*                      to the list of children at the root of the manifest.
* param index If less than or equal to the number of children then the node will be inserted at index;
*              otherwise it will be added at the end.
* return      An AdobeDCXElement object rooted at the newly inserted element node
*/
- (AdobeDCXElement *)insertElement:(NSString *)name
withId:(NSString *)elementId
withType:(NSString *)type
withPath:(NSString *)path
toParent:(AdobeDCXNode *)parentNode
atIndex:(NSInteger)index
withError:(NSError **)errorPtr;

/**
* brief Updates the branch by replacing the element in the branch that share the specified element's id.
* Resets the element's isDirty flag to NO.
*
* param element An AdobeDCXElement object that is currently connected a valid composite branch
* param error   Populated with an error object in that even that the function fails due to error
*
* return The AdobeDCXNode object that corresponds to the updated element in this branch
*
* note We recommend reusing the existing element if subsequent modifications are expected
* since constructing AdobeDCXElement objects can be relatively expensive.
*/
- (AdobeDCXNode *)replaceElement:(AdobeDCXElement *)element withError:(NSError **)errorPtr;

/**
* brief Updates the branch by copying the specified element to the specified parent/index.
*  Assigns the given newPath as the path, and newId as the nodeId, of the new child node and
* ensures that all copied sub-nodes and components get new ids if the path or nodeId has changed
* or if we are copying between different composites.
*
* param element     The source node on another branch or element that will be copied to this branch
* param parentNode  The node whose children list to copy the child node to. Can be nil in which
*                  case the node will be copied to the list of children at the root of the manifest.
* param index       The index where to add this child node.
* param newPath     Optional. The new path for the newly created node
* param newId       Optional. The new id for the newly created node
* param errorPtr    Gets set in the case of a failure.
*
* return            An AdobeDCXElement object that is rooted at the node that results from copying the element into this branch
* note We recommended to reusing the existing element if subsequent modifications are expected
* since constructing AdobeDCXElement objects can be relatively expensive.  Also note that, unlike replaceElement, copyElement
* does not reset the elements isDirty flag.
*/
- (AdobeDCXNode *)copyElement:(AdobeDCXElement *)element toParent:(AdobeDCXNode *)parentNode toIndex:(NSUInteger)index
withPath:(NSString *)newPath withId:(NSString*)newId withError:(NSError **)errorPtr;

/**
* brief Disconnects an element that is hosted on this branch and allows its local storage to be garbage collected.
*
* param element  The element that will be disconnected from this branch
*
* return YES if the element is successfully disconnected; NO if an error occurs
*
* note   Subsequent attempts to use the object will result in an NSInternalInconsistency exception
*/
- (BOOL)abandonElement:(AdobeDCXElement *)element withError:(NSError **)errorPtr;

/**@}*/



@end

#endif
