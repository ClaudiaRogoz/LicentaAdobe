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

#ifndef AdobeLibraryCompositeHeader
#define AdobeLibraryCompositeHeader

#import <Foundation/Foundation.h>

#import <AdobeCreativeSDKAssetModelOSX/AdobeCollaborationType.h>

@class AdobeLibraryElement;
@class AdobeLibraryRepresentation;
@class AdobeLibraryElementFilter;
@class UIImage;

@protocol AdobeLibraryDelegate;

/**
 * This is the main class that represents a library aka library composite.
 * A library composite contains elements which are represented by AdobeLibraryElement.
 *
 * Library creation and deletion should be done via AdobeLibraryManager. See
 * newLibraryWithName and deleteLibraryWithId on AdobeLibraryManager.
 */
@interface AdobeLibraryComposite : NSObject

#pragma mark - Properties

/** The collaboration state of the library (private, shared by user, or shared with user) **/
@property (readonly, nonatomic) AdobeCollaborationType collaboration;

/** Whether or not this library is read only **/
@property (readonly, nonatomic) BOOL readOnly;

/** Whether or not this is a public library. */
@property (readonly, nonatomic) BOOL isPublic;

/** The creation time of the library (time interval in seconds since 1970). */
@property (readonly, nonatomic) NSTimeInterval created;

/** Whether or not this library has changes that have not been synced to the server. */
@property (readonly, nonatomic) BOOL hasUnsyncedChanges;

/** Whether or not this library is pending deletion on the next sync. */
@property (readonly, nonatomic) BOOL isPendingDelete;

/** The unique identifier of the library composite. */
@property (readonly, nonatomic) NSString *libraryId;

/**
 * Last modification time of the library (time interval in seconds since 1970).
 * This is only updated if the library is commited.
 */
@property (readonly, nonatomic) NSTimeInterval modified;

/**
 * The name of the library composite. It is nil if the library has not been initialized properly.
 * Any leading or trailing whitespace is removed, and the name must contain at least one
 * non-whitespace character.
 */
@property (readwrite, nonatomic) NSString *name;

#pragma mark - Getters

/**
 * \brief Getter for the library composite version.
 *
 * \return library composite version
 */
- (NSInteger)getVersion;

#pragma mark - Element access

/**
 * \brief The number of elements in the library composite which match the types
 *         specified in the elementTypesFilter startup option for the given delegate.
 *
 * \param delegate The delegate which is requesting the element count.
 *
 * \return the number of elements in the library composite.
 */
- (NSUInteger)countElements:(id<AdobeLibraryDelegate>)delegate;

/**
 * \brief The list of elements in the library composite. This will only
 *              return elements that are of one of the types specified in the
 *              elementTypesFilter startup option for the given delegate.
 *
 * \param delegate The delegate which is requesting the elements.
 *
 * \return An array that contains the elements in the library composite.
 */
- (NSArray *)elements:(id<AdobeLibraryDelegate>)delegate;

/**
 * \brief Get elements in the library using a filter. This will do a case-insensitive
 * search on the criteria in the given filter. The filter can specify whether
 * to match ALL or ANY of the criteria specified.@see AdobeLibraryElementFilter
 *
 * \param filter The search filter for finding elements.
 * \param delegate The delegate which is requesting the elements.
 *
 * \returns an array of elements representing the results of the search.
 */
- (NSArray *)elementsWithFilter:(AdobeLibraryElementFilter *)filter forDelegate:(id<AdobeLibraryDelegate>)delegate;

/**
 * \brief Get an element with the specified id.
 *
 * \param elementId The id for the element to retrieve.
 *
 * \return the element requested or nil if an element with the given id is not found.
 */
- (AdobeLibraryElement *)elementWithId:(NSString *)elementId;

/**
 * \brief The list of all elements in the library composite regardless of
 * any of the startup filter options specified.
 *
 * \return An array that contains all the elements in the library composite.
 */
- (NSArray *)allElements;

/**
 * \brief The number of total elements in the library composite, regardless of
 * any of the startup filter options specified.
 *
 * \return the total number of elements in the library composite.
 */
- (NSUInteger)countAllElements;

/**
 * \brief Same as elementsWithFilter except it will apply the given filter
 * to all elements regardless of any of the startup filter options specified.
 *
 * \param filter The search filter for finding elements.
 *
 * \returns an array of elements representing the results of the search.
 */
- (NSArray *)allElementsWithFilter:(AdobeLibraryElementFilter *)filter;

/**
 * \brief Remove the given element from the library composite. This will also remove all representations
 * for this element from the library composite.
 *
 * \param element     The element to remove.
 * \param errorPtr    Gets set if an error occurs while removing the element.
 *
 * \return the removed element
 */
- (AdobeLibraryElement *)removeElement:(AdobeLibraryElement *)element andError:(NSError **)errorPtr;

#pragma mark - Representations

/**
 * \brief Get the representation with the given id.
 *
 * \param repId   The id of the representation to retrieve.
 *
 * \return    The representation or nil if it doesn't exist.
 *
 * \note This method has been deprecated, use representationWithId on AdobeLibraryElement instead.
 */
- (AdobeLibraryRepresentation *)representationWithId:(NSString *)repId __deprecated;

/**
 * \brief Returns the representations of the given element.
 *
 * \param element The element for which to retrieve the representations.
 *
 * \return an array that contains the representations of the given element.
 *
 * \note This method has been deprecated, use element.representations instead.
 */
- (NSArray *)representationsForElement:(AdobeLibraryElement *)element __deprecated;

/**
 * \brief Get the first representation of the given content-type for the element.
 *
 * \param contentType The content-type for the representation to retrieve.
 * \param element     The element for which to retrieve the representation.
 *
 * \return    The representation or nil if no representation for the given content-type.
 *
 * \note This method has been deprecated, use [AdobeLibraryRepresentation firstRepresentationOfType].
*/
- (AdobeLibraryRepresentation *)firstRepresentationOfType:(NSString *)contentType forElement:(AdobeLibraryElement *)element __deprecated;

/**
 * \brief Get the primary representation of the given element.
 *
 * \param element     The element for which to retrieve the primary representation.
 *
 * \return    The primary representation or nil if no primary representation exists or if
 *                      the element does not exist.
 *
 * \note This method has been deprecated, use element.primaryRepresentation instead.
 */
- (AdobeLibraryRepresentation *)primaryRepresentationForElement:(AdobeLibraryElement *)element __deprecated;

/**
 * \brief Get the path of the file representing the content for the given representation.
 *
 * \param representation	The representation to get the file path for.
 * \param queue			Optional parameter. If not nil determines the operation queue completion and error blocks get executed on.
 * \param completionBlock The block that gets called with the file path in case of success.
 * \param errorBlock      The block that gets called with the error object in case of error.
 *
 * \return NO if this representation does not contain a file, otherwise YES.
 *
 * \note This method has been deprecated, use getContentPath on the representation instead.
 */
- (BOOL)filePathForRepresentation:(AdobeLibraryRepresentation *)representation handlerQueue:(NSOperationQueue *)queue onComplete:(void (^)(NSString *path))completionBlock onError:(void (^)(NSError *error))errorBlock __deprecated;

/**
 * \brief Return whether or not the file for the given representation exists locally.
 *              This does not mean the current local file is necessarily in sync with the latest version
 *              on the server.
 * \param representation	The representation to check.
 * \return YES if this representation's file exists locally, otherwise NO.
 */
- (BOOL)haveLocalFileForRepresentation:(AdobeLibraryRepresentation *)representation;

/**
 * \brief Get the remote url for the representation's content. Valid only for file based
 * representations, including externally linked representations.
 *
 * \return an NSURL with the url for the representation's content
 *
 * \note This method has been deprecated, use representation.contentURL instead.
 */
- (NSURL *) getContentURLForRepresentation:(AdobeLibraryRepresentation *)representation __deprecated;

#pragma mark - Renditions

/**
 * \brief Get the path to an element's rendition for a particular size.
 * This method will return a rendition in the following order:
 *
 *      1) First check the local cache for a rendition of the requested size.
 *      2) Next it will check for a representation that has been marked as a rendition with the given size.
 *      3) After it will find any representation that can be used to generate a rendition and generate one using Adobe's imaging service.
 *      4) Returns NO if all the above methods failed to find a suitable rendition.
 *
 * \param elementId       the id of the element for which to get the rendition.
 * \param size            the size of the requested rendition (ignored if fullSize is specified)
 * \param fullSize        whether or not the full size rendition is requested
 * \param queue			Optional parameter. If not nil determines the operation queue completion and error blocks get executed on.
 * \param completionBlock The block that gets called with the file path in case of success.
 * \param errorBlock      The block that gets called with the error object in case of error.
 *
 * \return YES if this rendition can be found or generated for the element, otherwise NO.
 */
- (BOOL)getRenditionPath:(NSString *)elementId withSize:(NSUInteger)size isFullSize:(BOOL)fullSize handlerQueue:(NSOperationQueue *)queue onCompletion:(void (^)(NSString *))completionBlock onError:(void (^)(NSError *))errorBlock;

/**
 * \brief Get the path to an element's rendition for a particular size from the local cache.
 * This method will only check the local cache for a rendition of the requested size.
 *
 * \param elementId       the id of the element for which to get the rendition.
 * \param size            the size of the requested rendition (ignored if fullSize is specified)
 * \param fullSize        whether or not the full size rendition is requested
 * \param errorPtr		An optional pointer to an error object that gets set in case of an error.
 *
 * \return the path if this rendition can be found in the local cache, otherwise nil.
 */
- (NSString *)getRenditionPathFromCache:(NSString *)elementId withSize:(NSUInteger)size isFullSize:(BOOL)fullSize withError:(NSError **)errorPtr;

/**
 * \brief Set a rendition cache for a particular size using a file path. Use this after changing
 * content to avoid the delay of having the server generate the rendition.
 *
 * \param elementId       the id of the element for which to set the rendition path.
 * \param filePath        the path of the file representing the content for the given representation.
 * \param size            the size of the given rendition (ignored if fullSize is specified)
 * \param fullSize        whether or not the rendition represented with the path is full size
 * \param copy            whether or not to copy the rendition from the given path to renditions
 *                      folder. The rendition won't be copied if this is set to true.
 * \param errorPtr        Gets set if an error occurs while setting the rendition.
 *
 * \return YES if this rendition can be set for the element, otherwise NO.
 */
- (BOOL)setRenditionCache:(NSString *)elementId withFilePath:(NSString *)filePath withSize:(NSUInteger)size isFullSize:(BOOL)fullSize copy:(BOOL)copy andError:(NSError **)errorPtr;

/**
 * \brief Set a rendition cache for a particular size using image data. Use this after changing
 * content to avoid the delay of having the server generate the rendition.
 *
 * \param elementId       the id of the element for which to set the rendition path.
 * \param image           the UIImage to be cached.
 * \param fullSize        whether or not the rendition represented with the path is full size
 * \param errorPtr        Gets set if an error occurs while setting the rendition.
 *
 * \return YES if this rendition can be set for the element, otherwise NO.
 */
- (BOOL)setRenditionCache:(NSString *)elementId withImage:(UIImage *)image isFullSize:(BOOL)fullSize andError:(NSError **)errorPtr;

#pragma mark overall

/**
 * \brief Reverts changes to the library and sets it to the state as present in the cloud.
 *
 * \param queue		  Optional parameter. If not nil determines the operation queue completion and error blocks get executed on.
 * \param completionBlock The block that gets called in case of success.
 * \param errorBlock      The block that gets called with the error object in case of error.
 *
 * \return YES on success/no changes required; NO if a file system error occurs or if this library is local.
 *
 * \note An application that calls this method must be careful to ensure that the library is not used,
 * and until after the completion handler is called.
 *
 */
- (void)revertUnsyncedChanges:(NSOperationQueue *)handlerQueue onComplete:(void (^)(void))completionBlock onError:(void (^)(NSError *error))errorBlock;

@end

#endif
