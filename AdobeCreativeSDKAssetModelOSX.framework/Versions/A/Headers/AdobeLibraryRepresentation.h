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

#ifndef AdobeLibraryRepHeader
#define AdobeLibraryRepHeader

#import <Foundation/Foundation.h>

/**
 * Indicates that the representation is a rendition. That is, a representation that is derivable from, and is visually similar to the primary representation. For example, a flattened PNG version of a PSD would be a rendition representation.
 */
extern NSString *const AdobeLibraryRepresentationRelationshipTypeRendition;

/**
 * The main representation - this should be the highest-fidelity form of the element, and is considered the most 'truthful' version of the element. For example, an image added from Photoshop would use a PSD as its primary representation, whereas one added from Illustrator would use an AI file.
 */
extern NSString *const AdobeLibraryRepresentationRelationshipTypePrimary;

/**
 * Indicates that this is an alternate representation. A representation that is not derivable from the primary representation, but stores alternative, or auxiliary data. This should be used sparingly.
 */
extern NSString *const AdobeLibraryRepresentationRelationshipTypeAlternate;

/** Old names with misspelling in them, now deprecated */
extern NSString *const AdobeLibraryRepresenationRelationshipTypePrimary __deprecated;
extern NSString *const AdobeLibraryRepresenationRelationshipTypeAlternate __deprecated;
extern NSString *const AdobeLibraryRepresenationRelationshipTypeRendition __deprecated;

/**
 * Represents a representation of a library element.
 */
@interface AdobeLibraryRepresentation : NSObject <NSMutableCopying>

/** The application that created this representation. */
@property (readonly, nonatomic) NSString *application;

/** Whether or not this representation is a full size rendition of the element */
@property (readwrite, nonatomic, getter = isFullSize) BOOL fullSize;

/** The width of the representation. */
@property (readwrite, nonatomic) NSNumber *width;

/** The height of the representation. */
@property (readwrite, nonatomic) NSNumber *height;

/** The md5 hash of the asset on the server if this is a file based representation, otherwise nil. */
@property (readonly, nonatomic) NSString *md5;

/** The unique identifier of the representation. */
@property (readonly, nonatomic) NSString *representationId;

/** The content-type of the representation. */
@property (readonly, nonatomic) NSString *type;

/** The relationship of the representation. See above for built-in values. */
@property (readwrite, nonatomic) NSString *relationship;

/** The length of the content for this representation. Only valid for file based representations. */
@property (readwrite, nonatomic) NSNumber *contentLength;

/** The specified order of this representation. */
@property (readonly, nonatomic) NSNumber *order;

/**
 * The remote url for the representation's content. Valid only for file based
 * representations, including externally linked representations.
 */
@property (readonly, nonatomic, getter=getContentURL) NSURL *contentURL;

/**
 * Returns a boolean indicating whether the representation is an external link. If true, this means that the content
 * for the representation is not embedded in the DCX; instead, it's downloaded from an external URL.
 *
 * To create a representation that's an external link, call AdobeLibraryRepresentation#representationWithSourceHref, passing
 * YES for the externalLink parameter.
 */
@property (readonly, nonatomic, getter = isExternalLink) BOOL externalLink;

/**
 * \brief Returns the value for the property identified by a given key.
 *
 * \param key             The key of the value to search for.
 * \param keyNamespace    The namespace for the key.
 *
 * \return returns the value of the property identified by the key and namespace.
 */
- (id)valueForKey:(NSString *)key forNamespace:(NSString *)keyNamespace;

/**
 * \brief Set value for a given key on this representation.
 *
 * \param value			The value to set with the key.
 * \param key			The key to use to set the value on the representation.
 * \param keyNamespace	The namespace to use with the key.
 * \param errorPtr		Gets set if an error occurs while setting the value.
 */
- (BOOL)setValue:(id)value forKey:(NSString *)key forNamespace:(NSString *)keyNamespace andError:(NSError **)errorPtr;

/**
 * \brief Returns whether or not this representation is of the requested type or
 *              of a type that is compatible with the requested type.
 *
 * \param requestedType	The type to check this representation for.
 *
 * \return whether or not this representation is compatible with the requested type.
 */
- (BOOL)isCompatibleType:(NSString *)requestedType;

/**
 * \brief Get the path of the file representing the content for this representation.
 *
 * \param handlerQueue	  If not nil determines the operation queue completion and error blocks get executed on.
 * \param completionBlock The block that gets called with the file path in case of success.
 * \param errorBlock      The block that gets called with the error object in case of error.
 *
 * \return NO if this representation does not contain a file, otherwise YES.
 */
- (BOOL)getContentPath:(NSOperationQueue *)handlerQueue onComplete:(void (^)(NSString *path))completionBlock onError:(void (^)(NSError *error))errorBlock;

/**
 * \brief Return whether or not the file for this representation exists locally.
 *              This does not mean the current local file is necessarily in sync with the latest version
 *              on the server.
 * \return YES if this representation's file exists locally, otherwise NO.
 */
- (BOOL)haveLocalFile;

@end

#endif
