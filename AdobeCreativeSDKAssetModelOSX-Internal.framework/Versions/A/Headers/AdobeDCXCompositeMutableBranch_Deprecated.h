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

#ifndef AdobeDCXCompositeMutableBranchDepHeader
#define AdobeDCXCompositeMutableBranchDepHeader

#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeDCXCompositeMutableBranch.h>

@interface AdobeDCXCompositeMutableBranch ()

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
toChild:(AdobeDCXManifestNode *)node
fromFile:(NSString *)sourceFile copy:(BOOL)copy
fromHref:(NSString *)sourceHref
withError:(NSError **)errorPtr __deprecated;

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
toChild:(AdobeDCXManifestNode *)node
withUCID:(NSString *)UCID
fromHref:(NSString *)sourceHref
withError:(NSError **)errorPtr __deprecated;

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
toChild:(AdobeDCXManifestNode *)node
fromFile:(NSString *)sourceFile copy:(BOOL)copy
fromHref:(NSString *)sourceHref
withError:(NSError **)errorPtr __deprecated;

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
toChild:(AdobeDCXManifestNode *)node
fromHref:(NSString*)sourceHref
withUCID:(NSString*)UCID
withError:(NSError**)errorPtr __deprecated;

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
- (AdobeDCXComponent *)moveComponent:(AdobeDCXComponent *)component toChild:(AdobeDCXManifestNode *)node
withError:(NSError **)errorPtr __deprecated;

/** Copies the existing component from a different composite branch to the specified
* child node. Fails if it already exists in this branch.
*
* param component   The component to copy.
* param branch      The branch that contains the component. May be a branch on either the same or a different composite.
* param node        The node to copy the component to. If nil the component will get copied to the root level.
* param errorPtr    Gets set in the case of a failure.
*
* return            The copied AdobeDCXComponent or nil in the case of a failure.
*/
- (AdobeDCXComponent *)copyComponent:(AdobeDCXComponent *)component from:(AdobeDCXCompositeBranch *)branch
toChild:(AdobeDCXManifestNode *)node withError:(NSError **)errorPtr __deprecated;

/** Copies the existing component from a different composite branch to the specified
* child node. Assigns newPath to the path property of the component and also assigns a new id to it.
*
* param component   The component to copy.
* param branch      The branch that contains the component. May be a branch on either the same or a different composite.
* param node        The node to copy the component to. If nil the component will get copied to the root level.
* param newPath     The new path for the component.
* param errorPtr    Gets set in the case of a failure.
*
* return            The copied AdobeDCXComponent or nil in the case of a failure.
*/
- (AdobeDCXComponent *)copyComponent:(AdobeDCXComponent *)component from:(AdobeDCXCompositeBranch *)branch
toChild:(AdobeDCXManifestNode *)node newPath:(NSString *)newPath
withError:(NSError **)errorPtr __deprecated;

/** Updates the existing component from a different branch of the same composite in place. Fails if
* it the component doesn't exist in this branch.
*
* param component   The component to copy.
* param branch      The branch that contains the component. Must be a branch on the same composite.
* param errorPtr    Gets set in the case of a failure.
*
* return            The copied AdobeDCXComponent or nil in the case of a failure.
* note This method has been replaced by replaceComponent:from:withError.
*/
- (AdobeDCXComponent *)updateComponent:(AdobeDCXComponent *)component from:(AdobeDCXCompositeBranch *)branch
withError:(NSError **)errorPtr __deprecated;

/**
* brief Update the node specified by node.
*
* param node    The node to update.
*
* return        The updated node.
*
* warning This method makes a shallow copy of the dictionary backing the manifest node in order to
* incorporate it into the manifest. It is the caller's responsibility to avoid multipe components
* sharing the same deeper nested data.
*/
- (AdobeDCXManifestNode *)updateChild:(AdobeDCXManifestNode *)node withError:(NSError **)errorPtr __deprecated;

/**
* brief Add node as a new child node at the end of the list of children of parent node.
*
* param node        The node to add.
* param parentNode  The node to add the child node to. Can be nil in which case the node will be added
*                  to the list of children at the root of the manifest.
* return            The added node.
*
* warning This method makes a shallow copy of the dictionary backing the manifest node in order to
* incorporate it into the manifest. It is the caller's responsibility to avoid multipe components
* sharing the same deeper nested data.
*/
- (AdobeDCXManifestNode *)addChild:(AdobeDCXManifestNode *)node toParent:(AdobeDCXManifestNode *)parentNode
withError:(NSError **)errorPtr __deprecated;


/**
* brief Insert node as a new child node into the list of children of parent node at the given index.
*
* param node        The node to insert.
* param parentNode  The node whose children list to insert the child node into. Can be nil in which
*                  case the node will be inserted into the list of children at the root of the manifest.
* param index       The index where to add this child node.
*
* return            The inserted child.
*
* warning This method makes a shallow copy of the dictionary backing the manifest node in order to
* incorporate it into the manifest. It is the caller's responsibility to avoid multipe components
* sharing the same deeper nested data.
*/
- (AdobeDCXManifestNode *)insertChild:(AdobeDCXManifestNode *)node parent:(AdobeDCXManifestNode *)parentNode
atIndex:(NSUInteger)index withError:(NSError **)errorPtr __deprecated;


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
- (AdobeDCXManifestNode *)moveChild:(AdobeDCXManifestNode *)node toParent:(AdobeDCXManifestNode *)parentNode
toIndex:(NSUInteger)index withError:(NSError **)errorPtr __deprecated;

/**
* brief Copies the node including all its components and sub nodes from the specified composite branch
* to the specified parent/index. Fails if the node already exists in this branch.
*
* param node        The node to copy.
* param branch      The branch containing the node. May be on the same or a different composite.
* param parentNode  The node whose children list to copy the child node to. Can be nil in which
*                  case the node will be copied to the list of children at the root of the manifest.
* param index       The index where to add this child node.
* param errorPtr    Gets set in the case of a failure.
*
* return            The copied child or nil in the case of a failure.
*/
- (AdobeDCXManifestNode *)copyChild:(AdobeDCXManifestNode *)node from:(AdobeDCXCompositeBranch *)branch
toParent:(AdobeDCXManifestNode *)parentNode toIndex:(NSUInteger)index
withError:(NSError **)errorPtr __deprecated;

/**
* brief Copies the node including all its components and sub nodes from the specified composite branch
* to the specified parent/index. Assigns the given newPath as the path of the new
* child node and ensures that all copied sub-nodes and components get new ids if the path has changed
* or if we are copying between different composites.
*
* param node        The node to copy.
* param branch      The branch containing the node. May be on the same or a different composite.
* param parentNode  The node whose children list to copy the child node to. Can be nil in which
*                  case the node will be copied to the list of children at the root of the manifest.
* param index       The index where to add this child node.
* param newPath     The new path for the child node.
* param errorPtr    Gets set in the case of a failure.
*
* return            The copied child or nil in the case of a failure.
*
* note copyChild may only be called on composites using the copy-on-write local storage scheme.
*
* This function has been deprecated and is replaced by copyChild:from:toParent:toIndex:withPath:withId:withError
*/
- (AdobeDCXManifestNode *)copyChild:(AdobeDCXManifestNode *)node from:(AdobeDCXCompositeBranch *)branch
toParent:(AdobeDCXManifestNode *)parentNode toIndex:(NSUInteger)index
withPath:(NSString *)newPath withError:(NSError **)errorPtr __deprecated;

/**
* brief Copies the node including all its components and sub nodes from the specified composite branch
* to the specified parent/index. Assigns the given newPath as the path, and newId as the nodeId, of the new
* child node and ensures that all copied sub-nodes and components get new ids if the path or nodeId has changed
* or if we are copying between different composites.
*
* param node        The node to copy.
* param branch      The branch containing the node. May be on the same or a different composite.
* param parentNode  The node whose children list to copy the child node to. Can be nil in which
*                  case the node will be copied to the list of children at the root of the manifest.
* param index       The index where to add this child node.
* param newPath     Optional. The new path for the child node.
* param newId       Optional. The new id for the child node.
* param errorPtr    Gets set in the case of a failure.
*
* return            The copied child or nil in the case of a failure.
*
*/
- (AdobeDCXManifestNode *)copyChild:(AdobeDCXManifestNode *)node from:(AdobeDCXCompositeBranch *)branch
toParent:(AdobeDCXManifestNode *)parentNode toIndex:(NSUInteger)index
withPath:(NSString *)newPath withId:(NSString*)newId withError:(NSError **)errorPtr __deprecated;

/**
* brief Updates the node including all its components and sub nodes from the specified branch of the
* same composite. Fails if the node doesn't exist in this branch.
*
* param node        The node to update. Must be a node from branch.
* param branch      The branch containing the node. Must be on the same composite.
* param errorPtr    Gets set in the case of a failure.
*
* return            The updated child node or nil in the case of a failure.
*
* note  This method has been replaced by replaceComponent:from:withError.
*/
- (AdobeDCXManifestNode *)updateChild:(AdobeDCXManifestNode *)node from:(AdobeDCXCompositeBranch *)branch
withError:(NSError **)errorPtr  __deprecated;

/** Removes the node from the manifest.
*
* param node The node to remove.
*
* return The removed child as a AdobeDCXManifestNode.
*/
- (AdobeDCXManifestNode *)removeChild:(AdobeDCXManifestNode *)node__deprecated;


/**
* brief Optimized way to add component along with metadata. Will create side-by-side metadata if necessary.
* This is not fully atomic since upon failure it can leave the input file with updated metadata.
*/
- (AdobeDCXComponent *)addComponent:(AdobeDCXComponent *)component
toChild:(AdobeDCXManifestNode *)node
fromFile:(NSString *)sourceFile copy:(BOOL)copy
withMetadata:(AdobeDCXMetadata *)metadata
withError:(NSError **)errorPtr __deprecated;

/**
* brief Return metadata for an element, creating it if necessary.
* This can result in the creation of a new component.
* The metadata can be saved by calling [metadata saveInCompositeBranch:branch withError:&error].
* The element node must have a name property, otherwise an NSInternalInconsistencyException exception
* will be thrown.
*/
- (AdobeDCXMutableMetadata *)getOrCreateMetadataForElement:(AdobeDCXManifestNode *)elementNode withError:(NSError **)errorPtr __deprecated;


@end

#endif
