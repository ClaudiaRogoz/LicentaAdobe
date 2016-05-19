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

#ifndef AdobeLibraryElementHeader
#define AdobeLibraryElementHeader

#import <Foundation/Foundation.h>

@class AdobeLibraryRepresentation;

/**
 * Represents an element in a library composite.
 */
@interface AdobeLibraryElement : NSObject <NSMutableCopying>

#pragma mark Properties

/** The creation time of the element (time interval in seconds since 1970). */
@property (readonly, nonatomic) NSTimeInterval created;

/** The unique identifier of the element. */
@property (readonly, nonatomic) NSString *elementId;

/** Last modification time of the element (time interval in seconds since 1970). */
@property (readonly, nonatomic) NSTimeInterval modified;

/** The name of the element. */
@property (readwrite, nonatomic) NSString *name;

/** The type of the asset element, e.g. 'application/vnd.adobe.element.color', 'application/vnd.adobe.element.image' */
@property (readonly, nonatomic) NSString *type;

/** The tags for this element, An array of strings. */
@property (readonly, nonatomic, copy) NSArray *tags;

/** The representations for this element, an array of AdobeLibraryRepresentation. */
@property (readonly, nonatomic, copy) NSArray *representations;

/** The primary representation or nil if no primary representation exists */
@property (readonly, nonatomic) AdobeLibraryRepresentation *primaryRepresentation;

#pragma mark Methods

/**
 * \brief Get the representation with the given id.
 *
 * \param repId   The id of the representation to retrieve.
 *
 * \return    The representation or nil if it doesn't exist.
 */
- (AdobeLibraryRepresentation *)representationWithId:(NSString *)repId;

/**
 * \brief Get the first representation of the given content-type for the element.
 *
 * \param contentType The content-type for the representation to retrieve.
 *
 * \return    The representation or nil if no representation for the given content-type.
 */
- (AdobeLibraryRepresentation *)firstRepresentationOfType:(NSString *)contentType;

@end

#endif
