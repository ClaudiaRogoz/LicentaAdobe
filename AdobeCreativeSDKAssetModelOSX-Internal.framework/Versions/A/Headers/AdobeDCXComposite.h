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

#ifndef AdobeDCXCompositeHeader
#define AdobeDCXCompositeHeader

#import <Foundation/Foundation.h>
#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeStorageResource.h>

@class AdobeDCXCompositeBranch;
@class AdobeDCXCompositeMutableBranch;
@class AdobeDCXManifest;
@class AdobeDCXComponent;
@class AdobeDCXManifestNode;
@class AdobeDCXSyncGroupMonitor;
@class AdobeStorageResourceItem;
@class AdobeDCXMutableMetadata;
@class AdobeDCXController;

@protocol AdobeDCXTransferSessionProtocol;

typedef NS_ENUM (NSInteger, AdobeDCXLocalStorageScheme)
{
/** Local files for components are immutable and get stored under a file name that changes with
* each edit. Thus the client can modify the composite even while a push or pull operation is going on. */
AdobeDCXLocalStorageSchemeCopyOnWrite,
/** Local files are stored in separate directories under their respective paths. While a push or
* pull is going on clients must not modify a component without also changing its path. */
AdobeDCXLocalStorageSchemeDirectories
};

/**
* brief Represents a DCX composite.
*
* How to create/instantiate a composite
* ---------------------------------
*
* AdobeDCXComposite defines several constructor methods.
* Which one you should use depends on whether the composite already exists locally
* and/or on the server.
*
* If the composite exists locally (i.e. in local storage) you must use
* @see compositeStoredAt:usingController:withError: to instantiate the composite.
* This return a fully populated AdobeDCXComposite instance either from the instance
* cache or (if that doesn't exist) by reading and parsing the manifest file from local storage.
*
* Else, if the composite exists on server you must use
* @see newCompositeWithHref:andId:storedAt:usingController:withError: or
* @see newCompositeFromResource:storedAt:usingController:withError:
* Notice that the resulting AdobeDCXComposite is not yet fully functional since it
* doesn't have a manifest yet, however it can be used to pull the composite from the server.
*
* Else (the composite doesn't exist on either the server or locally yet) you need to use
* @see newCompositeWithName:type:href:andId:storedAt:usingController:withError: or
* @see newCompositeAsCopyOf:withName:type:href:andId:storedAt:usingController:andSession:withError:
*
* Branches
* ----------------
* The actual data of the composite (its components, metadata, child nodes, etc.) are accessible through
* its branches. The main branch is called 'current' and represents the last synced state of the composite
* with all additional local changes.
*
* After a successful call to AdobeDCXCompositeXfer's pullComposite: or pullMinimalComposite: the 'pulled'
* branch contains the data that was pulled from the service. 'current' remains untouched. If you have
* made changes to 'current' you can now merge those changes into 'pulled'. Either way you need to call
* resolvePullWithBranch:withError: in order to update 'current' from 'pulled' and dispose of 'pulled'.
*
* After a successful call to AdobeDCXCompositeXfer's pushComposite: the 'pushed' branch contain updates
* that stem from the push operation. Call acceptPushWithError: to merge the updated server state from the 'pushed'
* branch into the 'current' branch in memory and into the manifest file on disk, and to dispose of 'pushed'.
*
*
*/
@interface AdobeDCXComposite : NSObject

/**@}*/
#pragma mark - Factory Methods
/** name Factory Methods */
/**@{*/

/**
* brief Creates a composite from a local storage path and hooks it up to an instance of AdobeDCXController
* to coordinate its synchronization activities. Use for composites that already exist locally.
* Notice that this method will return an already existing instance of the same composite instead of creating a new one.
* Returns nil if the composite can't be read.
*
* param localStoragePath  Path of the local directory of the composite.
* param controller        Optional. The Controller object that will coordinate the synchronization activity of this composite.
*                          May be nil if the composite is not being used in conjunction with a controller or if it
*                          will be assigned at a later time via the composite's controller property.
* param errorPtr      Optional. Gets set if an error occurs while constructing the composite instance.
*/
+(instancetype)compositeStoredAt:(NSString *)localStoragePath
usingController:(AdobeDCXController *)controller
withError:(NSError **)errorPtr;


/**
* brief Creates a composite from an href.
* Use for composites that do net yet exist locally but do exist on the server.
* Returns nil if the (optionally) provided localStoragePath is already in use by another
* instance of AdobeDCXComposite.
*
* param href              Path of the composite on the server.
* param compositeId       Optional. The id of the composite.
* param localStoragePath  Optional. A file path to an existing but empty local directory that will end up containing the
*                          composite's manifest and assets.
* param controller        Optional. The Controller object that will coordinate the synchronization activity of this composite.
*                          May be nil if the composite is not being used in conjunction with a controller or if it
*                          will be assigned at a later time via the composite's controller property.
* param errorPtr          Optional. Gets set if an error occurs while constructing the composite instance.
*/
+(instancetype)newCompositeWithHref:(NSString *)href
andId:(NSString *)compositeId
storedAt:(NSString *)localStoragePath
usingController:(AdobeDCXController *)controller
withError:(NSError **)errorPtr;

/**
* brief Creates a composite from an asset resource item as provided by the AdobeStorageAssetMonitor.
* Use for composites that do net yet exist locally but do exist on the server.
* Returns nil if the (optionally) provided localStoragePath is already in use by another
* instance of AdobeDCXComposite.
*
* param resource          An AdobeStorageResourceItem as provided by the AdobeStorageAssetMonitor.
* param localStoragePath  Optional. A file path to an existing but empty local directory that will end up containing the
*                          composite's manifest and assets.
* param controller        Optional. The Controller object that will coordinate the synchronization activity of this composite.
*                          May be nil if the composite is not being used in conjunction with a controller or if it
*                          will be assigned at a later time via the composite's controller property.
* param errorPtr          Optional. Gets set if an error occurs while constructing the composite instance.
*/
+ (instancetype)newCompositeFromResource:(AdobeStorageResourceItem *)resource storedAt:(NSString *)localStoragePath
usingController:(AdobeDCXController *)controller
withError:(NSError **)errorPtr;


/**
* brief Creates an empty composite and hooks it up to an instance of AdobeDCXController
* to coordinate its synchronization activities.  Use this if you construct a composite from scratch.
* The composite will not be saved to local storage so you must call commitChangesWithError before
* you can push it to the server.
* Returns nil if the (optionally) provided localStoragePath is already in use by another
* instance of AdobeDCXComposite.
*
* param name              The name of the new composite.
* param type              The mime type of the new composite.
* param href              Optional. Path of the composite on the server. May be nil if this path is not known at the time of
*                          creation.
* param compositeId       Optional. The id of the new composite. Can be nil in which case an id will be generated when
*                          writing the manifest.
* param localStoragePath  Optional. A file path to an existing but empty local directory that will end up containing the
*                          composite's manifest and assets.
* param controller        OptionalThe Controller object that will coordinate the synchronization activity of this composite.
*                          May be nil if the composite is not being used in conjunction with a controller or if it
*                          will be assigned at a later time via the composite's controller property.
* param errorPtr          Optional. Gets set if an error occurs while constructing the composite instance.
*/
+(instancetype)newCompositeWithName:(NSString *)name
type:(NSString *)type
href:(NSString *)href
andId:(NSString *)compositeId
storedAt:(NSString *)localStoragePath
usingController:(AdobeDCXController *)controller
withError:(NSError **)errorPtr;

/**
* Creates and returns a new composite object that is a copy of srcComposite.
* Returns nil if the provided localStoragePath is already in use by another
* instance of AdobeDCXComposite.
*
* param srcComposite      The composite to be copied
* param name              The name of the new composite. If nil then the name is copied from srcComposite.
* param type              The media type of the new composite. If nil then the type is copied from srcComposite.
* param href              Optional. Path of the new composite on the server. May be nil if this path is not known at the time of
*                          creation.
* param compositeId       Optional. The id of the new composite. Can be nil in which case an id will be generated when
*                          writing the manifest.
* param localStoragePath  Path of the local directory of the composite. Required.
* param controller        The Controller object that will coordinate the synchronization activity of the new composite.
*                          May be nil if the composite is not being used in conjunction with a controller or if it
*                          will be assigned at a later time via the composite's controller property.
* param srcSession        The transfer session to which the srcComposite is bound.  If not nil then the session
*                          is used to construct the srcHref of components in the new composite.
* param errorPtr          Gets set if an error occurs during the operation
*
* notes Only composites that use the standard CopyOnWrite local storage scheme may be duplicated using this method.
*      Hard links will be used when possible to efficiently create copies of local components.  Otherwise the
*      method will fall back to copying the bytes.  If the srcSession parameter has been specified, then the duplicated composite
*      will contain the 'srcHref' of the copied components, which can potentially be used to more efficiently push the
*      duplicated composite to the same service. Unmanaged componment UCIDS are copied verbatim.
*
*/
+(instancetype)newCompositeAsCopyOf:(AdobeDCXComposite *)srcComposite
withName:(NSString *)name
type:(NSString *)type
href:(NSString *)href
andId:(NSString *)compositeId
storedAt:(NSString *)localStoragePath
usingController:(AdobeDCXController *)controller
andSession:(id<AdobeDCXTransferSessionProtocol>)srcSession
withError:(NSError **)errorPtr;

/**@}*/
#pragma mark - Properties
/** name Properties */
/**@{*/

/** The local storage directory for this composite.
* note Use setLocalStoragePath:witError to modify it. */
@property (readonly) NSString *localStoragePath;

/** Fails if path is in use by an active instance. */
-(BOOL) setLocalStoragePath:(NSString *)path withError:(NSError **)errorPtr;

/** The href path (on the server) of this composite.
* note You can only set this on an unbound composite. I.e. you need to call resetBinding: or resetIdentity:
* before you can assign a new href to a composite. */
@property NSString *href;

/** The id of this composite. */
@property NSString *compositeId;

/** Is YES if the composite is bound to a specific composite on the server. */
@property (nonatomic, readonly) BOOL isBound;

/** The collaboration state of the composite resource on the server.
* note Maintaining this property is the responsibility of the client and it should
* only be updated in response to monitor:assetWasAdded and monitor:assetWasUpdated messages
* received via the AdobeDCXSyncGroupMonitorDelegate interface.  Important: changing
* this property does not have any effect on the actual collaboration setting on the server.
*/
@property (nonatomic) AdobeCollaborationType collaborationType;

/** Is this composite read-only.
* note Maintaining this propery is a responsibility of the client. DCX does not restrict
* its API to not work for a read only library.
**/
@property (nonatomic) BOOL readOnly;

/** brief The metadata for the curent composite branch, if any.
* If there is no metadata in the current branch, metadata will be created based on the
* information in the manifest unless property initializeMetadataFromManifest is NO.
*/
@property (nonatomic, readonly) AdobeDCXMutableMetadata *metadata;

@property (nonatomic, readwrite) BOOL initializeMetadataFromManifest;

/** Controls whether unused local components are cleaned up automatically in a background thread
* Defaults to YES.  If set to NO then the client is responsible for calling removeUnusedLocalFiles
*/
@property (nonatomic, readwrite) BOOL autoRemoveUnusedLocalFiles;

/** When using a local storage scheme such as AdobeDCXLocalStorageSchemeCopyOnWrite that
* treats component files as immutable, this property controls whether the DCX library sets a file system
* attribute (NSFileImmutable on iOS) on the file to enforce this condition.  Defaults to YES when
* using AdobeDCXLocalStorageSchemeCopyOnWrite.
*
* NOTE: This was changed to be a readonly property to prevent application logic from changing the
* NEW DEFAULT VALUE OF NO, which was a change made to avoid bricking iOS 8 devices when uninstalling
* apps with locked files.
**/
@property (nonatomic, readonly) BOOL lockImmutableComponents;

/** The state of the composite that has been committed (saved) to local storage.
*  The string will be one of AdobeDCXAssetStateUnmodified, AdobeDCXAssetStateModified,
*  AdobeDCXAssetStatePendingDelete, AdobeDCXAssetStateCommittedDelete, or nil if the
*  composite has not been committed yet.
*
*  Note: to obtain the in-memory composite state, use the compositeState property of
*  the 'current' branch.
*/
@property (nonatomic, readonly) NSString *committedCompositeState;

/**@}*/
#pragma mark - Synchronization
/** name Synchronization */
/**@{*/

/** An instance of AdobeDCXController that observes changes to the synchronization phase of
* this composite and coordinates the synchronization activity for the composite with the
* application via the AdobeDCXControllerDelegate interface.  May be nil if the composite has not
* been associated with any controller.  This property is intended to be write-once and will throw
* a NSInvalidArgumentException if it is assigned to a new value.
*/
@property (nonatomic, weak, readwrite) AdobeDCXController *controller;

/**@}*/
#pragma mark - Branches
/** name Branches */
/**@{*/

/** The different branches of the composite. A branch can be nil if it doesn't exist in local storage. */

/** The mutable current branch of the composite (including any in-memory changes). Is nil if the
* composite doesn't yet exist locally. */
@property (nonatomic, readonly) AdobeDCXCompositeMutableBranch *current;

/** The pulled branch of the composite. Is nil if the composite doesn't have a pending pull. */
@property (nonatomic, readonly) AdobeDCXCompositeBranch *pulled;

/** The pushed branch of the composite. Is nil if the composite doesn't have a pending push. */
@property (nonatomic, readonly) AdobeDCXCompositeBranch *pushed;

/** The base branch of the composite. Is nil if the composite doesn't exist either locally (never
* been pulled) or on the server (never been pushed).
*/
@property (nonatomic, readonly) AdobeDCXCompositeBranch *base;

/**
* brief Makes the provided merged branch the current branch of the composite in memory and on disk,
* discards the pulled branch on disk, and updates the base branch.
*
* param branch          The merged branch to be promoted to the new current branch.  May be nil, in
* which case the pulled branch is copied directly.
* param errorPtr        Gets set to an NSError if something goes wrong.
*
* return         YES on success.
*
* note The merged branch should be the result of merging the pulled branch with the current branch,
* and the merged branch should originate by copying either the pulled or current branch.
*
* note If the controller property of the composite is non-nil, then the associated AdobeDCXController
* will process any errors that result from calling this method and will inform the client via the
* controller:requestsClientHandleError:... method on its delegate in addition to setting the
* errorPtr upon return from this call.
*/
- (BOOL)resolvePullWithBranch:(AdobeDCXCompositeMutableBranch *)branch withError:(NSError **)errorPtr;


/**
* brief Accepts the result of a successful push operation by merging the server state in the resulting pushed
* branch into the current branch in memory and into the manifest file on disk,
* updating the base branch to be the pushed branch, and ultimately discarding the pushed branch.
* This method is a no-op and returns YES in the event that no pushed branch exists.
*
* param errorPtr        Gets set to an NSError if something goes wrong.
*
* return                YES on success.
*
* note This method should only be used on composites that have been created to use the copy-on-write local
* storage scheme.
*
* note If the controller property of the composite is non-nil, then the associated AdobeDCXController
* will process any errors that result from calling this method and will inform the client via the
* controller:requestsClientHandleError:... method on its delegate in addition to setting the
* errorPtr upon return from this call.
*/
- (BOOL)acceptPushWithError:(NSError **)errorPtr;

/**
* brief Discards last pulled-down branch of the composite. Is a no-op if there isn't such a branch.
*
* param errorPtr Gets set to an NSError if something goes wrong.
*
* return YES on success.
*/
- (BOOL)discardPulledBranchWithError:(NSError **)errorPtr;


/**
* brief Discards the branch from the last push(es). Is a no-op if there isn't such branch.
*
* param errorPtr Gets set to an NSError if something goes wrong.
*
* return YES on success.
*/
- (BOOL)discardPushedBranchWithError:(NSError **)errorPtr;


/**
* brief Discards in-memory changes to the current branch that have not been committed to disk.
*
* param queue     An NSOperationQueue the identifies the thread on which the completion handler will be called
* param handler   A completion handler block that is invoked once the operation has been completed
*
* return YES on success; NO if a file system error occurs or if the current branch has never been committed to local storage
*
* note An application that calls this method must be careful to ensure that the current branch is not used or modified until
* after the completion handler is called.
*/
- (void)revertCurrentBranchWithHandlerQueue:(NSOperationQueue*)queue
completionHandler:(void(^)(BOOL success, NSError *error))handler;


/**
* brief Replaces the current branch with the base branch in memory and on local storage.
*
* param queue     An NSOperationQueue the identifies the thread on which the completion handler will be called
* param handler   A completion handler block that is invoked once the operation has been completed
*
* return YES on success; NO if a file system error occurs or if there is no base branch
*
* note An application that calls this method must be careful to ensure that the current branch is not used,
* and the base branch is not modified, until after the completion handler is called.
*/
- (void)revertCurrentBranchToBaseWithHandlerQueue:(NSOperationQueue*)queue
completionHandler:(void(^)(BOOL success, NSError *error))handler;


/**@}*/
#pragma mark - Local Storage
/** name Storage */
/**@{*/

/** The file path for client-specific data belonging to the composite. The files in this directory
* will be ignored by the DCX logic. Notice that this directory might not yet exist. */
@property (readonly) NSString *clientDataPath;

/**
* brief Commits the manifest of the composite to local storage.
*
* Returns YES if the manifest is successfully written (or if the manifest is not written
* because the composite's manifestPath is nil); NO if an error occurs.
*
* param errorPtr Gets set if an error occurs while writing the manifest file.
*
* return YES on success.
*/
- (BOOL)commitChangesWithError:(NSError **)errorPtr;

/**
* brief Deletes the directory at the path of the composite with all its contents.
*
* param errorPtr Gets set if an error occurs.
*
* return YES on success.
*/
- (BOOL)removeLocalStorage:(NSError **)errorPtr;

/**
* brief Deletes unused local files such as components that are no longer referenced by any branch of the composite.
*
* This method is only required to be called when the client has set the autoRemoveUnusedLocalFiles property to NO
* and only when using the AdobeDCXLocalStorageSchemeCopyOnWrite storage scheme is used.  Since the
* AdobeDCXLocalStorageDirectores scheme does not generate any unused local files, this method will have no effect
* when that scheme is in use.
*
* param errorPtr Gets set if an error occurs.
*
* return NSNumber object containing an unsigned long long values with the total number of bytes freed
* as a result of removing the files.
*
* note Returns a non-nil NSNumber if any files were successfully removed OR if no error has
* occurred.
*/
- (NSNumber *)removeUnusedLocalFilesWithError:(NSError **)errorPtr;

/**
* brief Deletes the local files for the specified unmodified components that are referenced from the
* current or base branches of this composite.
*
* An AdobeDCXErrorCannotRemoveModifiedComponent error will be generated for any components that exist
* in the 'current' branch (in memory or on disk) whose state is currently set to AdobeDCXAssetStateModified
*
* param componentIDs    An array of component IDs
* param errorList       An optional pointer to an array that will be set to a list of any errors that prevent
* the successful removal of one or more of the specified components
*
* return The number of bytes freed by removing the files as a result of calling this method.
*
* note A number will always be returned from this method so the caller should check the errorList
* parameter to determine if any errors prevented the entire operation from completing successfully.
*/
- (NSNumber *)removeLocalFilesForComponentsWithIDs:(NSArray *)componentIDs errorList:(NSArray **)errorListPtr;

/**
* brief Returns the number of bytes of local storage consumed by the composite
*
* return A NSNumber object containing an unsigned long long value
*
* note This method does not include files that are managed directly by the application (e.g. files saved in clientdata)
*/
- (NSNumber *)localStorageBytesConsumed;

/**@}*/
#pragma mark - Reset
/** name Reset */
/**@{*/


/**
* brief Remove all service-related data from the current branch so that
* it can be pushed again to the same or a different service.
*
* Removes all service-related links, etags and the service identifier.
* Removes any deleted components.
* Sets states of composite and components to modified.
*
* note This method doesn't reset the ids of the composite or its child nodes/components.
* Thus you cannot push it to the same service as long as the original composite still exists on that
* service. If you do want to push this composite as a duplicate of the original composite
* you'll want to call resetIdentityWithId instead.
*/
- (void)resetBinding;


/**
* brief Generates and assigns a new unique composite ID to the current branch. Also removes service-related data from the manifest so that
* it can be pushed again to the same or a different service.
*
* Removes all service-related links, etags, etc.
* Removes any deleted components.
* Generates new a ID for the composite.
* Sets states of composite and components to modified.
*
* note This method has been deprecated and replaced with resetIdentityWithId
*/
- (void)resetIdentity __deprecated;


/**
* brief Assigns a new composite ID to the current branch. Also removes service-related data from the manifest so that
* it can be pushed again to the same or a different service.
*
* Removes all service-related links, etags, etc.
* Removes any deleted components.
* Sets states of composite and components to modified.

param uuid  If not nil, then uuid becomes the new compositeId.  The string is expected to be a UUID.
If nil, then a new UUID is generated and assigned to compositeId.
*/

- (void)resetIdentityWithId:(NSString *)uuid;

/**@}*/
#pragma mark Metadata
/** name Metadata */
/**@{*/

/** brief Create metadata for a rendition. */

- (AdobeDCXMutableMetadata *)createMetadataForRenditionWithType:(NSString *)type;

/**@}*/

@end

#endif
