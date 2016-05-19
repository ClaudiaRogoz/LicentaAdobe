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

#ifndef AdobeDCXCompositePrivateHeader
#define AdobeDCXCompositePrivateHeader

#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeDCXComposite.h>

@class AdobeDCXManifest;
@class AdobeDCXElement;
@class AdobeDCXMutableManifestNode;

@protocol AdobeDCXLocalStorageProtocol;

@interface AdobeDCXComposite ()

#pragma mark - Properties

/** The AdobeDCXManifest. */
@property (readonly) AdobeDCXManifest* manifest;

@property (readonly) Class<AdobeDCXLocalStorageProtocol> localStorage;

@property (readwrite) NSString* committedCompositeState;

/**
brief The most recent time that current branch was committed to, or initialized from, the manifest file in local storage
*/
@property (atomic, readwrite) NSDate *currentBranchCommittedAtDate;

/** The localCommitted branch of the composite as it is persisted to local storage. Is nil if the
* composite doesn't yet exist locally.
*
* note This property has been deprecated because it should no longer be necessary to directly access
* the on-disk manifest now that the acceptPushWithError method will automatically and independently merge
* the server state from the pushed branch into both the current branch in memory as well as the manifest
* on disk.
*/
@property (nonatomic) AdobeDCXCompositeBranch *localCommitted;

#pragma mark - Initialization

/**
* brief Designated initializer. Used by the other initializers.
*
* param storagePath     Path of the local directory of the composite.
* param storageScheme   The scheme to be used to store the composite locally. @see AdobeDCXLocalStorageScheme
* param href            Path of the composite on the server.
* param compositeId     The id of the composite.
* param controller      The Controller object that will coordinate the synchronization activity of this composite.
*                      May be nil if the composite is not being used in conjunction with a controller or if it
*                      will be assigned at a later time via the composite's controller property.
* param errorPtr        Gets set if an error occurs while reading and parsing the manifest file.
*
* If a path is given the initializer will attempt to read/parse the manifest and fail if that doesn't
* succeed.
*/
- (instancetype)initWithStoragePath:(NSString*)storagePath andStorageScheme:(AdobeDCXLocalStorageScheme)storageScheme
andHref:(NSString*)href andId:(NSString*)compositeId
andController:(AdobeDCXController*)controller withError:(NSError**) errorPtr;

- (instancetype) initWithName:(NSString *)name andType:(NSString *)type andStoragePath:(NSString *)storagePath
andStorageScheme:(AdobeDCXLocalStorageScheme)storageScheme andId:(NSString*)compositeId;


/**
* brief Creates a composite from a manifest and a local path.
* Use for composites that already exist locally and whose manifest is already instantiated.
*
* param manifest          The current manifest object of the composite.
* param localStoragePath  Path of the local directory of the composite.
* param storageScheme     The scheme to be used to store the composite locally. @see AdobeDCXLocalStorageScheme
*/
+(instancetype) newCompositeFromManifest:(AdobeDCXManifest *)manifest storedAt:(NSString *)localStoragePath
usingStorageScheme:(AdobeDCXLocalStorageScheme)storageScheme
withError:(NSError **)errorPtr;

/** Expose the instance cache for testing purposes */
+(NSMapTable *)instanceCache;

#pragma mark - Branches

-(void) updateCurrentBranchWithManifest:(AdobeDCXManifest*)manifest updateCommittedAtDate:(BOOL)updateCommittedAt;
-(void) updatePulledBranchWithManifest:(AdobeDCXManifest*)manifest;
-(void) updatePushedBranchWithManifest:(AdobeDCXManifest*)manifest;
-(void) updateLocalBranch;
-(void) updateBaseBranch;

-(void) updateCurrentBranchCommittedDate;

/**
* brief Removes the pushed manifest if it exists and invalidates the pushed branch property of the composite
while preserving the push journal
*/
-(void) discardPushedManifest;

#pragma mark - Components

/**
brief Removes the given component from the given manifest.

param component   The component to remove.
param manifest    The manifest to remove the component from. If nil the manifest gets removed from
the current manifest.

return The component or nil if the component didn't exist within the composite.
*/
-(AdobeDCXComponent*) removeComponent:(AdobeDCXComponent*)component fromManifest:(AdobeDCXManifest*)manifest;


/**
Adds the existing component from sourceManifest to destManifest.

param component       The component which must exist in sourceManifest.
param sourceManifest  The manifest of the component.
param sourceComposite The composite of the component.
param node            The child node to add the new component to. Can be nil.
param destManifest    The manifest the component should be added to.
param replaceExisting If a component with the same ID exists, remove it before adding
param newPath         Optional new path.
param errorPtr        Gets set if an error occurs.

return The newly added component or nil if an error occurs.

note This method does not remove the component from sourceManifest.

note IMPORTANT: This version of addComponent may only be called on composites using the
CopyOnWrite local storage scheme.
*/
-(AdobeDCXComponent*) addComponent:(AdobeDCXComponent*)component
fromManifest:(AdobeDCXManifest*)sourceManifest
ofComposite:(AdobeDCXComposite*)sourceComposite
toChild:(AdobeDCXManifestNode*)node
ofManifest:(AdobeDCXManifest*)destManifest
replaceExisting:(BOOL)replaceExisting
newPath:(NSString*)newPath
withError:(NSError**)errorPtr;


#pragma mark - Components

/**
Adds the existing child node from sourceManifest to destManifest.

param node            The node to add which must exist in sourceManifest.
param sourceManifest  The manifest of the node.
param sourceComposite The composite of the node.
param parentNode      The parent node to add the new child to. Can be nil.
param destManifest    The manifest the node should be added to.
param replaceExisting Whether to replace an existing node.
param newPath         Optional new path.
param newId           Optional new ID.
param errorPtr        Gets set if an error occurs.

return The newly added child node or nil if an error occurs.

note This method does not remove the child node from sourceManifest.

note IMPORTANT: This version of addChild may only be called on composites using the
CopyOnWrite local storage scheme.

*/
-(AdobeDCXMutableManifestNode*) addChild:(AdobeDCXManifestNode *)node
fromManifest:(AdobeDCXManifest *)sourceManifest
ofComposite:(AdobeDCXComposite*)sourceComposite
to:(AdobeDCXManifestNode *)parentNode
atIndex:(NSUInteger)index
ofManifest:(AdobeDCXManifest *)destManifest
replaceExisting:(BOOL)replaceExisting
newPath:(NSString*)newPath
newId:(NSString*)newId
withError:(NSError **)errorPtr;

#pragma mark - Storage

/**
brief Used by the pull logic to give the local storage scheme an opportunity to
verify, edit or insert its local storage-related data into a pulled manifest before
it is stored.

param targetManifest The manifest to update.
param sourceManifests Array of manifests that have existing storage data.
*/
-(void) updateLocalStorageDataInManifest:(AdobeDCXManifest *)targetManifest fromManifestArray:(NSArray *)sourceManifests;

/**
brief Returns YES if the storage scheme of the composite requires component assets to be immutable.

return YES if the storage scheme requires component assets to be immutable.
*/
-(BOOL) localComponentAssetsAreImmutable;

/** The file path of the manifest of the current local composite.
Notice that this file might not yet/anymore exist. */
@property (readonly) NSString* currentManifestPath;

/** The file path of the pulled manifest.
Notice that this file might not yet/anymore exist. */
@property (readonly) NSString* pulledManifestPath;

/** The file path of the base copy of the pulled manifest.
Notice that this file might not yet/anymore exist. */
@property (readonly) NSString* pulledManifestBasePath;

/** The file path of the pushed manifest.
Notice that this file might not yet/anymore exist. */
@property (readonly) NSString* pushedManifestPath;

/** The file path of the base copy of the pushed manifest.
Notice that this file might not yet/anymore exist. */
@property (readonly) NSString* pushedManifestBasePath;

/** The file path of a previously uploaded or downloaded manifest that can be used to diff  local and remote versions. */
@property (readonly) NSString* baseManifestPath;

/** The file path for the composite's push journal.
Notice that this file might not yet/anymore exist. */
@property (readonly) NSString* pushJournalPath;

/** The manifest of an active push operation for this composite. */
@property (readwrite) AdobeDCXManifest* activePushManifest;

/** A set of in-memory manifests for active snapshot operations and elements. */
@property (readonly) NSSet *activeManifests;

/** The set of component files that are currently being copied or moved into the components directory
and may not yet have updated timestamps.  Retrieves a copy in a thread-safe manner. */
@property (readonly) NSSet *inflightLocalComponentFiles;

/** Thread-safe methods to add and remove a component path to the list of inflight components. */
-(void) addPathToInflightLocalComponents:(NSString*)destinationPath;
-(void) removePathFromInflightLocalComponents:(NSString*)destinationPath;

/** Thread-safe methods to add and remove manifests to our dynamic list of those that are asynchronously being written to snapshots. */
-(void) addManifestToActiveSnapshots:(AdobeDCXManifest*)manifest;
-(void) removeManifestFromActiveSnapshots:(AdobeDCXManifest *)manifest;

-(void) requestDeletionOfUnsusedLocalFiles;

-(AdobeDCXManifest *) copyCommittedManifestWithError:(NSError **)errorPtr;

@end

#endif
