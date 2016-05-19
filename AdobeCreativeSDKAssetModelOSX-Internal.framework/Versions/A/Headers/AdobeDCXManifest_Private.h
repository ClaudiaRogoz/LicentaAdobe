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

#ifndef AdobeDCXManifestPrivateHeader
#define AdobeDCXManifestPrivateHeader

#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeDCXManifest.h>

@class AdobeDCXNode;

@interface AdobeDCXManifest ()

#pragma mark Initializers
/** name Initializers */
/**@{*/

/**
brief Designated initializer. Intitalizes a manifest from the contents of an
NSDictionary. Doesn't do any validation of the dictionary other than making
sure that it has a name and a type.

param dictionary NSDictionary derived from the JSON model of a manifest file.
param errorPtr Gets set if the dictionary passed in is invalid.
*/
- (id)initWithDictionary:(NSMutableDictionary*)dictionary withError:(NSError**)errorPtr;

/**
brief Initializes a manifest for a new empty composite.

param name The name of the composite represented by this manifest.
param type The mime type of the composite represented by this manifest.
*/
- (id)initWithName:(NSString*)name andType:(NSString*)type;

/**
brief Initializes a manifest from NSData containing the JSON model of a manifest file.

param data NSData representing the JSON model of a manifest file.
param errorPtr Gets set if the data cannot be parsed as valid JSON.
*/
- (id)initWithData:(NSData *)data withError:(NSError**)errorPtr;


/**@}*/
#pragma mark Storage
/** name Storage */
/**@{*/

/** The manifest in serialized form for local storage. */
- (NSData*) localData;

/** The manifest in serialized form for remote storage. */
- (NSData*) remoteData;

/** The manifest in serialized form for local snapshot storage. */
- (NSData*) snapshotData;

/**
brief Write the manifest to local storage.

param path The path of the file to write to.
param newSaveId YES if a new manifestSaveId field should be written to the manifest's local section
param errorPtr Gets set if something goes wrong.
*/
- (BOOL) writeToFile:(NSString*)path generateNewSaveId:(BOOL)newSaveId withError:(NSError**) errorPtr;

/**
brief Remove all service-related data from the manifest so that
it can be pushed again to the same or a different service.

Removes all service-related links, etags and the service identifier.
Removes any deleted components.
Sets states of composite and components to modified.

note This method doesn't rest the ids of the composite or its
child nodes/components. Thus if you push the composite to the same
service again you cannot push it to the same service as long as
the original composite still exists on that service. If you literally
want to push this composite as a duplicate of the original composite
you'll want to call resetIdentity instead.
*/
-(void) resetBinding;

/**
brief Assigns new ids to the composite and all of its child nodes and
components. Also removes service-related data from the manifest so that
it can be pushed again to the same or a different service.

Removes all service-related links, etags and the service identifier.
Removes any deleted components.
Generates new ids for the manifest, children and components.
Sets states of composite and components to modified.

param uuid  Optional.  If non-nil then specifies the new composite ID,
otherwise a new UUID is generated and asssigned.
*/
-(void) resetIdentityWithId:(NSString*)uuid;

/**@}*/
#pragma mark Convenience Constructor Methods
/** name Convenience Methods */
/**@{*/

/**
brief Creates a manifest for a new empty composite.

param name The name of the composite represented by this manifest.
param type The mime type of the composite represented by this manifest.
*/
+ (id)manifestWithName:(NSString*)name andType:(NSString*)type;

/**
brief Creates a manifest from a manifest file.

param path NSString containg the path of the manifest file to read and parse.
param errorPtr Gets set if the file cannot be read or the data from the file cannot be parsed as valid JSON.
*/
+ (id)manifestWithContentsOfFile:(NSString*)path withError:(NSError**)errorPtr;


/** Dictionary of all components keyed by component id. Component objects are of type AdobeDCXComponent.*/
@property (nonatomic, readonly) NSDictionary *allComponents;

/** Dictionary of all children keyed by node id. Children objects are of type AdobeDCXMutableManifestNode.*/
@property (nonatomic, readonly) NSDictionary *allChildren;

/** The modification time of the composite described in the manifest. */
@property (nonatomic, readwrite) NSString *modified;

@property (nonatomic, readonly) NSDictionary *unmanagedComponents;

/** The compositeId of the host composite when the manifest backs a pending element on a branch of that composite */
@property (nonatomic, readwrite) NSString *hostCompositeId;

/**@}*/
#pragma mark Components
/** name Components */
/**@{*/

/**
brief Returns the component with the given absolute path or nil.

param absPath The absolute path of the requested component.

return The component with the given absolute path or nil.
*/
-(AdobeDCXComponent*) componentWithAbsolutePath:(NSString*)absPath;

/**
brief Locates the given component in the manifest and returns its parent which is either
a AdobeDCXManifestNode or the AdobeDCXManifest. Returns nil if not found.

param component The component to return the parent for.

return The given component in the manifest and returns AdobeDCXManifestNode. Returns nil if not found.
*/
-(AdobeDCXManifestNode*) findParentOfComponent:(AdobeDCXComponent*)component;

/**
brief Get the list of components at the root of the manifest

return An NSArray of AdobeDCXComponent objects.
*/
-(NSArray*) components;

/**
brief Get the list of components for the specified child node.

param node The node for which to return the list of components of.

return An NSArray of AdobeDCXComponent objects.
*/
-(NSArray*) componentsOfChild:(AdobeDCXManifestNode*)node;

/**
brief Update the component specified by component.

param component The component to update.
param errorPtr Optional. Gets set to an error on failure.

return The updated AdobeDCXComponent.

warning This method makes a shallow copy of the dictionary backing
the component in order to incorporate it into the manifest. It is the
caller's responsibility to avoid multipe components sharing the same
deeper nested data.
*/
-(AdobeDCXComponent*) updateComponent:(AdobeDCXComponent*)component withError:(NSError**)errorPtr;

/** Add component as a new component to the root-level component list of the manifest.

param component The component to add.
param sourceManifest The source manifest of the component being added
param newPath Optional new path.
param errorPtr Optional. Gets set to an error on failure.

return The added AdobeDCXComponent.

warning This method makes a shallow copy of the dictionary backing
the component in order to incorporate it into the manifest. It is the
caller's responsibility to avoid multipe components sharing the same
deeper nested data.
*/
-(AdobeDCXComponent*) addComponent:(AdobeDCXComponent*)component fromManifest:(AdobeDCXManifest*)sourceManifest
newPath:(NSString*)newPath withError:(NSError**)errorPtr;

/** Add component as a new component to a specific child node in the manifest.

param component The component to add.
param sourceManifest The source manifest of the component being added
param node The node to add the component to.
param newPath Optional new path.
param errorPtr Optional. Gets set to an error on failure.

return The added AdobeDCXComponent.

warning This method makes a shallow copy of the dictionary backing
the component in order to incorporate it into the manifest. It is the
caller's responsibility to avoid multipe components sharing the same
deeper nested data.
*/
-(AdobeDCXComponent*) addComponent:(AdobeDCXComponent*)component fromManifest:(AdobeDCXManifest*)sourceManifest
toChild:(AdobeDCXManifestNode*)node newPath:(NSString*)newPath withError:(NSError**)errorPtr;

-(AdobeDCXComponent*) replaceComponent:(AdobeDCXComponent *)component fromManifest:(AdobeDCXManifest*)sourceManifest withError:(NSError**)errorPtr;

/** Moves the existing component to a different child node.

param component The component to move.
param node The node to move the component to.

return The moved AdobeDCXComponent.

note Component must already exist within the manifest.
*/
-(AdobeDCXComponent*) moveComponent:(AdobeDCXComponent*)component toChild:(AdobeDCXManifestNode *)node
withError:(NSError**)errorPtr;

/** Convenience method to modify the modification state of the component.

param component The component.
param modified Whether the component's state should be modified (YES) or unmodified (NO)

return The updated AdobeDCXComponent.
*/
-(AdobeDCXComponent*) setComponent:(AdobeDCXComponent*)component modified:(BOOL)modified;

/**
brief Returns YES if the component's asset is bound to a resource on the server.

param component The component.
*/
-(BOOL) componentIsBound:(AdobeDCXComponent*)component;

/** Removes the component from the manifest

param component The component to remove.

return The deleted AdobeDCXComponent.
*/
-(AdobeDCXComponent*) removeComponent:(AdobeDCXComponent*)component;

/** Removes all components from the manifest and its children
*/
-(void) removeAllComponents;

/** Removes all components from the manifest root level
*/
-(void) removeAllComponentsFromRoot;

/**
Removes all components from the specified child node.

param node the node to remove components from
*/
-(void) removeAllComponentsFromChild:(AdobeDCXManifestNode*)node;

/**
brief Inserts all components descended from the manifest node into resultArray

param node        A manifest node
param resultArray A mutable array into which to insert the resulting components
*/
- (void) componentsDescendedFromParent:(AdobeDCXManifestNode *)node intoArray:(NSMutableArray*)resultArray;

/**@}*/
#pragma mark Children (AdobeDCXManifestNode)
/** name Children (AdobeDCXManifestNode) */
/**@{*/

/**
brief Returns the child node with the given absolute path or nil.

param absPath The absolute path of the requested child node.

return The child node with the given absolute path or nil.
*/
-(AdobeDCXManifestNode*) childWithAbsolutePath:(NSString*)absPath;

/**
brief Locates the given child node in the manifest and returns its parent which is either
a AdobeDCXManifestNode or the AdobeDCXManifest. Returns nil if not found.

param component The component to return the parent for.

return The given component in the manifest and returns AdobeDCXManifestNode. Returns nil if not found.
*/
-(AdobeDCXManifestNode*) findParentOfChild:(AdobeDCXManifestNode*)node foundIndex:(NSUInteger*)index;

/**

brief Get the list of child nodes at the root of the manifest

return An NSArray of AdobeDCXManifestNode objects.
*/
-(NSArray*) children;

/**
brief Get the list of child nodes for the specified node.

param node The node for which to return the list of child nodes.

return An NSArray of AdobeDCXManifestNode objects.
*/
-(NSArray*) childrenOf:(AdobeDCXManifestNode*)node;

/**
brief Update the node specified by node.

param node The node to update.

return The updated child as a AdobeDCXMutableManifestNode.

warning This method makes a shallow copy of the dictionary backing
the manifest node in order to incorporate it into the manifest. It is the
caller's responsibility to avoid multipe components sharing the same
deeper nested data.
*/
-(AdobeDCXMutableManifestNode*) updateChild:(AdobeDCXManifestNode*)node withError:(NSError**)errorPtr;

/** Add node as a new child node to the manifest.

param node The node to add.

return The added child as a AdobeDCXMutableManifestNode.

warning This method makes a shallow copy of the dictionary backing
the manifest node in order to incorporate it into the manifest. It is the
caller's responsibility to avoid multipe components sharing the same
deeper nested data.
*/
-(AdobeDCXMutableManifestNode*) addChild:(AdobeDCXManifestNode*)node withError:(NSError**)errorPtr;

/** Add node as a new child node to a node in the manifest.

param node The node to add.
param parentNode The node to add the child node to.

return The added child as a AdobeDCXMutableManifestNode.

warning This method makes a shallow copy of the dictionary backing
the manifest node in order to incorporate it into the manifest. It is the
caller's responsibility to avoid multipe components sharing the same
deeper nested data.
*/
-(AdobeDCXMutableManifestNode*) addChild:(AdobeDCXManifestNode*)node toParent:(AdobeDCXManifestNode*)parentNode
withError:(NSError**)errorPtr;

/** Insert node as a new child node to the manifest at the specified index.

param node The node to add.
param index The index where to add this child node.

return The added child as a AdobeDCXMutableManifestNode.

warning This method makes a shallow copy of the dictionary backing
the manifest node in order to incorporate it into the manifest. It is the
caller's responsibility to avoid multipe components sharing the same
deeper nested data.
*/
-(AdobeDCXMutableManifestNode*) insertChild:(AdobeDCXManifestNode*)node atIndex:(NSUInteger)index
withError:(NSError**)errorPtr;

/** Insert node as a new child node to a node in the manifest at the specified index.

param node The node to add.
param parentNode The node to add the child node to.
param index The index where to add this child node.

return The added child as a AdobeDCXMutableManifestNode.

warning This method makes a shallow copy of the dictionary backing
the manifest node in order to incorporate it into the manifest. It is the
caller's responsibility to avoid multipe components sharing the same
deeper nested data.
*/
-(AdobeDCXMutableManifestNode*) insertChild:(AdobeDCXManifestNode*)node parent:(AdobeDCXManifestNode*)parentNode
atIndex:(NSUInteger)index withError:(NSError**)errorPtr;

/** Insert the complete node from a different manifest of the same composite as a new child node to
a node in the manifest at the specified index.

param node            The node to add.
param parentNode      The node to add the child node to.
param index           The index where to add this child node.
param replaceExisting If YES then the existing node will get replaced (parentNode and index will get ignored)
param newPath         Optional. The new path for the node.
param newId           Optional. The new path for the node.
param addedComponents Optional NSMutableArray of the new components that have been added.
param removedComponents Optional NSMutableArray of the component that have been removed.
param errorPtr        Gets set to an error if something goes wrong.

return The added child as a AdobeDCXMutableManifestNode.

warning This method makes a shallow copy of the dictionary backing
the manifest node in order to incorporate it into the manifest. It is the
caller's responsibility to avoid multipe components sharing the same
deeper nested data.
*/
-(AdobeDCXMutableManifestNode*) insertChild:(AdobeDCXManifestNode*)node fromManifest:(AdobeDCXManifest*)manifest
parent:(AdobeDCXManifestNode*)parentNode atIndex:(NSUInteger)index
replaceExisting:(BOOL)replaceExisting
newPath:(NSString *)newPath
newId:(NSString *)newChildId
forceNewIds:(BOOL)forceNewIds
addedComponents:(NSMutableArray *)addedComponents
addedComponentOrgIds:(NSMutableArray *)addedComponentOrgIds
removedComponents:(NSMutableArray *)removedComponents
withError:(NSError**)errorPtr;

/** Moves the existing child node to the manifest at the specified index.

param node        The node to move.
param index       The index where to move this child to.
param errorPtr    Gets set to an error if something goes wrong.

return            The moved child as a AdobeDCXMutableManifestNode.
*/
-(AdobeDCXMutableManifestNode*) moveChild:(AdobeDCXManifestNode*)node toIndex:(NSUInteger)index
withError:(NSError**)errorPtr;

/** Moves the existing child node to a node in the manifest at the specified index.

param node        The node to move.
param parentNode  The node to move the child node to.
param index       The index where to move this child node to.
param errorPtr    Gets set to an error if something goes wrong.

return            The moved child as a AdobeDCXMutableManifestNode.

*/
-(AdobeDCXMutableManifestNode*) moveChild:(AdobeDCXManifestNode*)node toParent:(AdobeDCXManifestNode*)parentNode
toIndex:(NSUInteger)index withError:(NSError**)errorPtr;

/** Removes the node from the manifest.

param node The node to remove.
param removedComponents Optional NSMutableArray of the component that have been removed.

return The removed child as a AdobeDCXManifestNode.
*/
-(AdobeDCXManifestNode*) removeChild:(AdobeDCXManifestNode*)node removedComponents:(NSMutableArray*)removedComponents;

/** Removes all children from the manifest.
param removedComponents Optional NSMutableArray of the component that have been removed.
*/
-(void) removeAllChildrenWithRemovedComponents:(NSMutableArray*)removedComponents;

/** Removes all children from the child node.

param node The node to remove all children from.
param removedComponents Optional NSMutableArray of the component that have been removed.

*/
-(void) removeAllChildrenFromParent:(AdobeDCXManifestNode*)node removedComponents:(NSMutableArray*)removedComponents;

/** Returns the AdobeDCXNode object associated with the specified nodeId */
-(AdobeDCXNode *) dcxNodeWithId:(NSString *)nodeId;

/** Returns the AdobeDCXNode object assoicated with the specified absolute path */
-(AdobeDCXNode *) dcxNodeWithAbsolutePath:(NSString *)path;

/**
brief A date formatter for dates in the manifest
*/
+ (NSDateFormatter*)dateFormatter;

/**
Parses RFC3339 dates as they appear in the manifest.
*/
+ (NSDate *)parseDate:(NSString*)dateStr;

/**
brief The absolute index of the manifest node within the hierarchy for child nodes of the
manifest.

param node The manifest node of

return The absolute index of the manifest node within the hierarchy for child nodes of the
manifest. NSNotFound if the node is not a child of this manifest.
*/
-(NSUInteger) absoluteIndexOf:(AdobeDCXManifestNode*)node;

-(NSMutableArray*) verifyIntegrityWithLogging:(BOOL)doLog withBranchName:(NSString*)name;

/**
brief Returns the source href, if any, of a component that should perform a server-to-server
copy in order to create its server resource during a subsequent push operation.

param component The component being inspected

return An href to be used as the source for a server to server copy
*/

-(NSString*) sourceHrefOfComponent:(AdobeDCXComponent*)component;

-(void) setUCID:(NSString*)UCID forComponent:(AdobeDCXComponent*)component;

-(NSString*) UCIDOfComponent:(AdobeDCXComponent*)component;

/**
brief Sets the source href to be used for a subsequent server to server copy during a push
operation that will populate the component's corresponding server resource.
*/
-(void) setSourceHref:(NSString*)sourceHref forComponent:(AdobeDCXComponent*)component;

/**
brief This returns an Array of elements which is specific to the Manifest dictionary.
These are the values which will be used to construct the manifest dictionary. These will also
be consulted when constructing Root Node of the manifest (i.e. these props will NOT be included in
the root node dictionary )
*/
+ (NSArray*) manifestSpecificProperties;

/**
* brief Returns an array of keys that may not be used for the custom properties of a manifest node
*/
+ (NSArray *)reservedNodePropertyKeys;

+(void) updateUnmanagedComponentsOf:(AdobeDCXManifest*)targetManifest fromManifest:(AdobeDCXManifest*)sourceManifest;

@end

#endif
