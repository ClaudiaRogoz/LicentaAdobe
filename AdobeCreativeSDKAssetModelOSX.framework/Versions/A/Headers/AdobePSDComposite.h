/******************************************************************************
 *
 * ADOBE CONFIDENTIAL
 * ___________________
 *
 * Copyright 2014 Adobe Systems Incorporated
 * All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains the property of
 * Adobe Systems Incorporated and its suppliers, if any. The intellectual and
 * technical concepts contained herein are proprietary to Adobe Systems
 * Incorporated and its suppliers and are protected by trade secret or
 * copyright law. Dissemination of this information or reproduction of this
 * material is strictly forbidden unless prior written permission is obtained
 * from Adobe Systems Incorporated.
 ******************************************************************************/

#ifndef AdobePSDCompositeHeader
#define AdobePSDCompositeHeader

#import <Foundation/Foundation.h>

// Import CoreGraphics for iOS and ApplicationServices for Mac OS X
#if defined(__IPHONE_OS_VERSION_MIN_REQUIRED)
#import <CoreGraphics/CoreGraphics.h>
#else
#import <ApplicationServices/ApplicationServices.h>
#endif

#import <AdobeCreativeSDKAssetModelOSX/AdobePSDCompositeBranch.h>

@class AdobePSDCompositeMutableBranch;


/**
 * AdobePSDComposite provides a composite representation of a cloud-based PSD document.
 * It can work with existing PSDs on the Creative Cloud or new ones created by the application.
 */
__deprecated // AdobePSDComposite will be replaced by CloudPSD and/or AGC
@interface AdobePSDComposite : NSObject

/** The different branches of the PSD composite. A branch can be nil if it doesn't exist in local storage. */

/** The current branch of the composite. Is nil if the composite doesn't yet exist locally. */
@property (nonatomic) AdobePSDCompositeMutableBranch *current;

/** The href of the original PSD file in the cloud. */
@property (nonatomic) NSString *psdHref;

/** The pulled branch of the composite. Is nil if the composite doesn't have a pending pull. */
@property (nonatomic) AdobePSDCompositeBranch *pulled;

/** The pushed branch of the composite. Is nil if the composite doesn't have a pending push. */
@property (nonatomic) AdobePSDCompositeBranch *pushed;


#pragma mark - Convenience Constructors

/**
 * Creates a new PSD composite object. Use this constructor for a PSD that doesn't have a
 * local presence yet but does exist in the cloud.
 *
 * \param psdHref     The location of the original PSD document on the server.
 * \param path        The path to an empty or non-existing directory in local storage that will hold
 *                  the local data of the PSD composite.
 *
 * \return            The newly created PSD composite.
 */
+ (id)compositeWithPSDHref:(NSString *)psdHref andPath:(NSString *)path;


/**
 * Creates a new PSD composite object. Use this constructor for a new empty PSD that doesn't
 * exist in Creative Cloud or local storage.
 *
 * \param name    The name of the new PSD composite.
 * \param path    The path to an empty or non-existing directory in local storage that will hold
 *              the local data of the PSD composite.
 * \param bounds  The bounding rectangle of the PSD composite.
 *
 * \return            The newly created PSD composite.
 */
+ (id)compositeWithName:(NSString *)name andPath:(NSString *)path andBounds:(CGRect)bounds;


/**
 * Creates a new PSD composite object. Use this constructor for a PSD composite that already
 * exists in local storage.
 *
 * \param path     The location of the PSD on the local device.
 * \param errorPtr Gets set if an error occurs.
 * \return            The newly created PSD composite or nil in case of a failure.
 */
+ (id)compositeWithPath:(NSString *)path andError:(NSError **)errorPtr;

#pragma mark - Initialization

/**
 * Initializes a newly allocated PSD composite. Use this initializer for a PSD that doesn't have a
 * local presence yet but does exist in the cloud.
 *
 * \param psdHref     The location of the original PSD document on the server.
 * \param path        The path to an empty or non-existing directory in local storage that will hold
 *                  the local data of the PSD composite.
 *
 * \return            The initialized PSD composite
 */
- (id)initWithPSDHref:(NSString *)psdHref andPath:(NSString *)path;

/**
 * Initializes a newly allocated PSD composite. Use this initializer for a new empty PSD that doesn't
 * exist in either cloud or local storage.
 *
 * \param name    The name of the new PSD composite.
 * \param path    The path to an empty or non-existing directory in local storage that will hold
 *              the local data of the PSD composite.
 * \param bounds  The bounding rect of the PSD composite.
 *
 * \return        The initialized PSD composite
 */
- (id)initWithName:(NSString *)name andPath:(NSString *)path andBounds:(CGRect)bounds;

/**
 * Initializes a newly allocated PSD composite. Use this initializer for a PSD composite that already
 * exists in local storage.
 *
 * \param path        The path to an empty or non-existing directory in local storage that will hold
 *                  the local data of the PSD composite.
 * \param errorPtr    Gets set in case of a failure when reading the composite from local storage.
 *
 * \return            The initialized PSD composite or nil in case of a failure.
 */
- (id)initWithPath:(NSString *)path andError:(NSError **)errorPtr;


#pragma mark - Storage

/**
 * \brief Writes the manifest of the PSD composite to local storage.
 *
 * \param errorPtr Gets set if an error occurs while writing the manifest file.
 *
 * \return YES on success.
 */
- (BOOL)commitChangesWithError:(NSError **)errorPtr;

/**
 * Deletes the local data of the PSD composite.
 *
 * \param errorPtr    Gets set if an error occurs.
 *
 * \return            YES on success.
 */
- (BOOL)removeLocalStorage:(NSError **)errorPtr;

#pragma mark - Branches

/**
 * \brief Makes the previously pulled branch of the PSD composite the current branch.
 * Is a no-op if there isn't such a version. Also updates the base manifest.
 *
 * \param errorPtr Gets set to an NSError if something goes wrong.
 *
 * \return YES on success.
 */
- (BOOL)resolvePulledBranchWithError:(NSError **)errorPtr;


/**
 * \brief Accepts the result of a successful push operation by merging the server state in the resulting pushed
 * branch into the current branch in memory and into the manifest file on disk,
 * updating the base branch to be the pushed branch, before ultimately discarding the pushed branch.
 *
 * \param errorPtr        Gets set to an NSError if something goes wrong.
 *
 * \return                YES on success.
 *
 * \note This method should only be used on composites that have been created to use the copy-on-write local
 * storage scheme.
 */
- (BOOL)acceptPushWithError:(NSError **)errorPtr;

@end

#endif
