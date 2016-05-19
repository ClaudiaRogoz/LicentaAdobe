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

#ifndef AdobeDCXCompositeDepHeader
#define AdobeDCXCompositeDepHeader

#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeDCXComposite.h>

@interface AdobeDCXComposite ()

/** The local storage directory for this composite. */
@property NSString *path __deprecated;

#pragma mark - Initializers (deprecated)
/** name Initializers */
/**@{*/

/**
* brief Initializer with local path and an instance of AdobeDCXController used to
* coordinate the synchronization activities of this object. Use for composites that already exist locally.
*
* param path            Path of the local directory of the composite.
* param controller      The Controller object that will coordinate the synchronization activity of this composite.
*                      May be nil if the composite is not being used in conjunction with a controller or if it
*                      will be assigned at a later time via the composite's controller property.
* param errorPtr        Gets set if an error occurs while reading and parsing the manifest file.
*
* Will attempt to read/parse the manifest and fail if that doesn't succeed.
*/
- (instancetype)initWithPath:(NSString *)path andController:(AdobeDCXController *)controller withError:(NSError **)errorPtr __deprecated;

/**
* brief Initializer with href and id. Use for composites that do net yet exist locally but do exist on
* the server.
*
* param href            Path of the composite on the server.
* param compositeId     The id of the composite.
* param controller      The Controller object that will coordinate the synchronization activity of this composite.
*                      May be nil if the composite is not being used in conjunction with a controller or if it
*                      will be assigned at a later time via the composite's controller property.
*/
- (instancetype)initWithHref:(NSString *)href andId:(NSString *)compositeId andController:(AdobeDCXController *)controller __deprecated;

/**
* brief Initializer for an empty new composite that is attached to an instance of AdobeDCXController used to
* coordinate the synchronization activities of this object.  Use this if you construct a composite from scratch.
* The composite will not be saved to local storage so you must call commitChangeWithError:
* before you can push it to the server.
*
* param name            The name of the new composite.
* param type            The mime type of the new composite.
* param path            Path of the local directory of the composite.
* param compositeId     The id of the composite.
* param href            Path of the composite on the server. May be nil if href is not yet known.
* param controller      The Controller object that will coordinate the synchronization activity of this composite.
*                      May be nil if the composite is not being used in conjunction with a controller or if it
*                      will be assigned at a later time via the composite's controller property.
*/
- (instancetype)initWithName:(NSString *)name andType:(NSString *)type andPath:(NSString *)path andId:(NSString *)compositeId
andHref:(NSString *)href andController:(AdobeDCXController *)controller __deprecated;


/**@}*/
#pragma mark - Convenience Factory Methods (deprecated)
/** name Convenience Factory Methods */
/**@{*/

/**
* brief Creates a composite from a local path and hooks it up to an instance of AdobeDCXController
* to coordinate its synchronization activities. Use for composites that already exist locally.
*
* param path            Path of the local directory of the composite.
* param controller      The Controller object that will coordinate the synchronization activity of this composite.
*                      May be nil if the composite is not being used in conjunction with a controller or if it
*                      will be assigned at a later time via the composite's controller property.
* param errorPtr        Gets set if an error occurs while reading and parsing the manifest file.
*
* Will attempt to read/parse the manifest and fail if that doesn't succeed.
*/
+ (instancetype)compositeFromPath:(NSString *)path andController:(AdobeDCXController *)controller withError:(NSError **)errorPtr __deprecated;

/**
* brief Creates a composite from an href.
* Use for composites that do net yet exist locally but do exist on the server.
*
* param href            Path of the composite on the server.
* param compositeId     The id of the composite.
* param path            A file path to an existing but empty local directory that will end up containing the
* composite's manifest and assets.
* param controller      The Controller object that will coordinate the synchronization activity of this composite.
*                      May be nil if the composite is not being used in conjunction with a controller or if it
*                      will be assigned at a later time via the composite's controller property.
*/
+ (instancetype)compositeFromHref:(NSString *)href andId:(NSString *)compositeId andPath:(NSString *)path andController:(AdobeDCXController *)controller __deprecated;

/**
* brief Creates a composite from an asset resource item as provided by the AdobeStorageAssetMonitor.
* Use for composites that do net yet exist locally but do exist on the server.
*
* param resource        An AdobeStorageResourceItem as provided by the AdobeStorageAssetMonitor.
* param path A          file path to an existing but empty local directory that will end up containing the
* composite's manifest and assets.
* param controller      The Controller object that will coordinate the synchronization activity of this composite.
*                      May be nil if the composite is not being used in conjunction with a controller or if it
*                      will be assigned at a later time via the composite's controller property.
*/
+ (instancetype)compositeFromResource:(AdobeStorageResourceItem *)resource andPath:(NSString *)path andController:(AdobeDCXController *)controller __deprecated;

/**
* brief Creates an empty composite and hooks it up to an instance of AdobeDCXController
* to coordinate its synchronization activities.  Use this if you construct a composite from scratch.
* The composite will not be saved to local storage so you must call commitChangesWithError before
* you can push it to the server.
*
* param name            The name of the new composite.
* param type            The mime type of the new composite.
* param path            Path of the local directory of the composite.
* param compositeId     The id of the new composite. Can be nil in which case an id will be generated when
*                      writing the manifest.
* param href            Path of the composite on the server. May be nil if this path is not known at the time of
*                      creation.
* param controller      The Controller object that will coordinate the synchronization activity of this composite.
*                      May be nil if the composite is not being used in conjunction with a controller or if it
*                      will be assigned at a later time via the composite's controller property.
*/
+ (instancetype)compositeWithName:(NSString *)name andType:(NSString *)type andPath:(NSString *)path
andId:(NSString *)compositeId andHref:(NSString *)href andController:(AdobeDCXController *)controller __deprecated;

/**
* Creates and returns a new composite object that is a copy of srcComposite
*
* param srcComposite    The composite to be copied
* param srcSession      The transfer session to which the srcComposite is bound.  If not nil then the session
*                      is used to construct the srcHref of components in the new composite.
* param name            The name of the new composite. If nil then the name is copied from srcComposite.
* param type            The mime type of the new composite. If nil then the type is copied from srcComposite.
* param path            Path of the local directory of the composite. Required.
* param compositeId     The id of the new composite. Can be nil in which case an id will be generated when
*                      writing the manifest.
* param href            Path of the composite on the server. May be nil if this path is not known at the time of
*                      creation.
* param controller      The Controller object that will coordinate the synchronization activity of the new composite.
*                      May be nil if the composite is not being used in conjunction with a controller or if it
*                      will be assigned at a later time via the composite's controller property.
* param errorPtr        Gets set if an error occurs during the operation
*
* notes Only composites that use the standard CopyOnWrite local storage scheme may be duplicated using this method.
*      Hard links will be used when possible to efficiently create copies of local components.  Otherwise the
*      method will fall back to copying the bytes.  If the srcSession parameter has been specified, then the duplicated composite
*      will contain the 'srcHref' of the copied components, which can potentially be used to more efficiently push the
*      duplicated composite to the same service. Unmanaged componment UCIDS are copied verbatim.
*
*/
+(instancetype)newCompositeAsCopyOf:(AdobeDCXComposite *)srcComposite
usingSession:(id<AdobeDCXTransferSessionProtocol>)srcSession
withName:(NSString *)name
andType:(NSString *)type
andPath:(NSString *)path
andId:(NSString *)compositeId
andHref:(NSString *)href
andController:(AdobeDCXController *)controller
withError:(NSError **)errorPtr __deprecated;

@end

#endif
