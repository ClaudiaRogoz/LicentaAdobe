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

#ifndef AdobeLibraryDelegateHeader
#define AdobeLibraryDelegateHeader

#import <Foundation/Foundation.h>

#if defined(DMALIB) && defined(TARGET_OS_OSX)
#import <AdobeCreativeSDKCoreOSX/AdobeCreativeSDKCoreOSX.h>
#endif

#import <AdobeCreativeSDKAssetModelOSX/AdobeLibraryComposite.h>

@class AdobeLibraryElement;

/**
 * The possible values for the download policy.
 */
typedef NS_ENUM (NSInteger, AdobeLibraryDownloadPolicyType)
{
    /** Only download the manifest during sync. Assets and renditions are downloaded when requested. */
    AdobeLibraryDownloadPolicyTypeManifestOnly = 0,

    /** Download the manifest and renditions. Assets can be downloaded on request. */
    AdobeLibraryDownloadPolicyTypeManifestAndRenditions = 1,

    /** Download all - manifest, renditions, and all assets */
    AdobeLibraryDownloadPolicyTypeManifestRenditionsAndAssets = 2
};

/**
 * The options used when starting AdobeLibraryManager.
 * \see AdobeLibraryManager.h for the startupWithOptions method.
 */
@interface AdobeLibraryDelegateStartupOptions : NSObject<NSCopying>

/**
 * Optional. The content types to auto-download. Valid only when autoDownloadPolicy is
 * AdobeLibraryDownloadPolicyTypeManifestRenditionsAndAssets
 */
@property (copy, nonatomic) NSArray *autoDownloadContentTypes;

/**
 * The auto-download policy type, see AdobeLibraryDownloadPolicyType.
 * The default is AdobeLibraryDownloadPolicyTypeManifestOnly.
 */
@property (nonatomic) AdobeLibraryDownloadPolicyType autoDownloadPolicy;
/**
 * The automatic sync interval in seconds where changes are synced with the storage service.
 * The default value is 60.0 seconds. Any attempt to set the update frequency to a value lower than the
 * allowed minimum of 60.0 seconds will result in it being set to the minimum value.
 */
@property (nonatomic) NSTimeInterval autoSyncInterval;

/**
 * Specifies whether or not assets that have been downloaded locally should be auto-synced or not.
 * Has no effect when the autoDownloadPolicy is AdobeLibraryDownloadPolicyTypeManifestRenditionsAndAssets
 * since everything is always synced in that case. Default is YES.
 */
@property (nonatomic) BOOL autoSyncDownloadedAssets;

/**
 * REQUIRED. Global filter for filtering what element types to sync and retrieve in all related methods.
 * The library will only return elements with these types when accessing it. Also, when this is specified,
 * only elements of these types will be downloaded when the download policy is set
 * to AdobeLibraryDownloadPolicyTypeManifestAndRenditions or AdobeLibraryDownloadPolicyTypeManifestRenditionsAndAssets.
 */
@property (copy, nonatomic) NSArray *elementTypesFilter;

/**
 * Optional. The rendition sizes to generate (if needed) and auto-download. Valid only when autoDownloadPolicy is
 * AdobeLibraryDownloadPolicyTypeManifestAndRenditions or AdobeLibraryDownloadPolicyTypeManifestRenditionsAndAssets.
 *
 * This should be a map of element types to an array of sizes to download. To specify a wildcard for the element
 * type the key can be set to "*". That array of rendition sizes will be used for any element type that does not
 * have a specific entry. A value of 0 means a full size rendition.
 *
 * If this property is set to nil, no renditions will be auto-downloaded or generated during sync.
 *
 * Examples:
 *      renditionsSize[@"application/vnd.adobe.element.brush+dcx"] = @[@50,@100];
 *      renditionsSize[@"application/vnd.adobe.element.image+dcx"] = @[@"0"];
 *      renditionsSize[@"*"] = @[@50,@100];
 *
 * \see [AdobeLibraryComposite getRenditionPath:withSize:isFullSize:handlerQueue:onCompletion:onError:] for information on how renditions are obtained.
 *
 */
@property (copy, nonatomic) NSDictionary *renditionSizes;

/**
 * Specifies whether or not bookmarked libraries should be synced and returned in the list of libraries.
 * Default is YES.
 */
@property (nonatomic) BOOL includeBookmarkedLibraries;

@end

/**
 * Defines the interface for a delegate that can be passed to AdobeLibraryManager#startupWithOptions
 */
@protocol AdobeLibraryDelegate <NSObject>

/**
 * An optional list of library composite Id's for which you want assets to be downloaded during sync.
 * If this option is not specified all libraries assets will be synced during sync operations based on the other
 * asset syncing options. If this is specified, assets files and renditions will be downloaded (based on other
 * asset/rendition filters) only for these libraries.
 */
@property (readonly, nonatomic) NSArray *assetDownloadLibraryFilter;

/**
 * Specifies whether or not assets that have been downloaded locally should be auto-synced or not.
 * Has no effect when the autoDownloadPolicy is AdobeLibraryDownloadPolicyTypeManifestRenditionsAndAssets
 * since everything is always synced in that case. If this property is set to NO, when an asset is updated
 * on the server, it will be downloaded when the asset path is requested via filePathForRepresentation.
 */
@property (readonly, nonatomic) BOOL autoSyncDownloadedAssets;

/**
 * The NSOperation queue identifying the thread on which the delegate methods are called.
 */
@property (readonly, strong, nonatomic) NSOperationQueue *libraryQueue;

/**
 * Specifies whether the service should automatically sync with the cloud storage service whenever changes are
 * commited. More specifically, on any call to [AdobeCompositeLibrary endChangesWithError] - which is also implicitly
 * called when there is no call to [AdobeCompositeLibrary beginChanges]. Also sync when true on any call to create a
 * new library or delete one.
 */
@property (readonly, nonatomic) BOOL syncOnCommit;

@optional

/**
 * \brief Called when an element of a library is updated during sync.
 *
 * \param library     The library composite that contains the element.
 * \param elementId   The id of the element that was updated.
 */
- (void)library:(AdobeLibraryComposite *)library elementWasUpdated:(NSString *)elementId;

/**
 * \brief Called when an element of a library is added during sync.
 *
 * \param library     The library composite that contains the element.
 * \param elementId   The id of the element that was added.
 */
- (void)library:(AdobeLibraryComposite *)library elementWasAdded:(NSString *)elementId;

/**
 * \brief Called when an element of a library is removed during sync.
 *
 * \param library     The library composite that contains the element
 * \param elementId   The id of the element that was removed.
 */
- (void)library:(AdobeLibraryComposite *)library elementWasRemoved:(NSString *)elementId;

/**
 * \brief Called when a library is updated during sync.
 *
 * \param library     The library that was updated.
 */
- (void)libraryWasUpdated:(AdobeLibraryComposite *)library;

/**
 * \brief Called when a library is added during sync.
 *
 * \param library     The library that was added.
 */
- (void)libraryWasAdded:(AdobeLibraryComposite *)library;

/**
 * \brief Called when a library is deleted during sync.
 *
 * \param libraryId     The id of the library that was deleted.
 */
- (void)libraryWasDeleted:(NSString *)libraryId;

/**
 * \brief Called when the current user has been removed from a shared library during sync.
 *
 * \param libraryId     The id of the library that was unshared.
 * \param libraryName	  The name of the library that was unshared.
 */
- (void)libraryWasUnshared:(NSString *)libraryId andLibraryName:(NSString *)libraryName;

/**
 * \brief Called when a library is about to be deleted during sync. The library with the specified id
 * was deleted on the server. Clients can decide whether this library should be deleted locally also
 * or not by returning YES or NO from this method. If this method is not implemented by the delegate,
 * the default behavior is to delete the local library as well.
 *
 * Note that if a client returns NO, meaning they wish to keep the library and re-upload it to the
 * server, they must ensure that any elements they wish to recover do not have missing representation
 * files. Any elements that have missing representation files will be removed from the library. By just
 * returning NO without re-generating any representations with missing files, only edited items should
 * remain in the recovered library, as well as any elements that have no files associated with them.
 *
 * \param libraryId     The id of the library that is about to be deleted.
 *
 * \return YES to delete the library locally as well, NO to keep it and re-upload it during a sync.
 */
- (BOOL)libraryPreDelete:(NSString *)libraryId;

/**
 * \brief Called when a library that has unsynched changes has been turned into a readonly library.
 * The library changes are about to be lost from the local copy during sync. Clients can decide whether
 * the changes in the local copy are to be preserved or deleted. By default
 * all unsynched changes are lost when the library is synched.
 *
 * Note that if returns a valid library, it is a reponsibility of the client to make sure that the content in the library
 * is complete and is not missing any representations.
 * If the returned library is read only, the changes are not added and get deleted.
 * Any elements that have missing representation files will be removed from the library. By just
 * returning NO without re-generating any representations with missing files, only edited items should
 * remain in the recovered library, as well as any elements that have no files associated with them.
 *
 * \param libraryId     The id of the library that is about to be made read only.
 *
 * \return the libraryId of the library to add the modified items to.
 */
-(NSString*)libraryPreReadabilityChange:(NSString *)libraryId;

/**
 * \brief Called when AdobeLibraryManager starts syncing.
 */
- (void)syncStarted;

/**
 * \brief Called when a sync is completed.
 */
- (void)syncFinished;

/**
 * \brief Called when sync is now available due to network status change.
 *
 * \param networkStatus new network status that caused the sync to be available.
 *
 */
- (void)syncAvailable:(AdobeNetworkStatus)networkStatus;

/**
 * \brief Called when sync is unavailable/disabled due to network status change.
 *
 * \param networkStatus new network status that caused the sync to be unavailable.
 *
 */
- (void)syncUnavailable:(AdobeNetworkStatus)networkStatus;

/**
 * \brief Called to notify clients when there is a progress during syncing a library.
 *
 * \param library         The library for which the progress has been made during sync.
 * \param percentComplete The percentage that is completed for the given library during the active sync.
 */
- (void)library:(AdobeLibraryComposite *)library onSyncProgress:(NSNumber *)percentComplete;

/**
 * \brief Called to notify clients when there is an error during syncing a library.
 *
 * The possible errors are:
 *
 * The following errors are sent to clients as soon as they occur. (No retry)
 * AdobeLibraryError#AdobeLibraryErrorSyncNotEnabled
 * AdobeLibraryError#AdobeLibraryErrorSyncNotAvailableDueToNetwork
 * AdobeLibraryError#AdobeLibraryErrorSyncNotAvailableDueToUserSession
 *
 * The following errors are sent to clients after the sync manager reaches the maximum allowed retry count
 * per sync for the corresponding library or component. The sync manager puts the corresponding library or component
 * back to the sync queue without sending an error if that number has not been reached. Clients should build their
 * retry logic accordingly. @see ADOBE_LIBRARY_MAXIMUM_RETRY_COUNT
 *
 * AdobeLibraryError#AdobeLibraryErrorSyncWriteFailure
 * AdobeLibraryError#AdobeLibraryErrorSyncUnexpectedError
 * AdobeNetworkError#AdobeNetworkErrorCancelled
 * AdobeNetworkError#AdobeNetworkErrorServiceDisconnected
 * AdobeNetworkError#AdobeNetworkErrorOffline
 * AdobeNetworkError#AdobeNetworkErrorNetworkFailure
 * AdobeAssetError#AdobeAssetErrorFileReadFailure
 *
 * \param library The library for which the error has been occurred during sync.
 * \param error   The error object.
 */
- (void)library:(AdobeLibraryComposite *)library onSyncError:(NSError *)error;

@end

#endif
