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

#ifndef AdobeLibraryMutableRepHeader
#define AdobeLibraryMutableRepHeader

#import <Foundation/Foundation.h>

#import <AdobeCreativeSDKAssetModelOSX/AdobeLibraryRepresentation.h>

/**
* brief Mutable version of AdobeLibraryRepresentation.
*
* note This class has been deprecated.
* Create new representations by calling appendRepresentation or insertRepresentation in AdobeLibraryComposite.
* In the new APIs, you no longer create mutable versions of elements and representations.
* AdobeLibraryComposite is now the factory for elements and AdobeLibraryElement is the
* factory for representations. You can now modify the properties of an element or a
* representation directly and it is immediately reflected in the in-memory library composite
* that it belongs to.
*/
@interface AdobeLibraryMutableRepresentation : AdobeLibraryRepresentation

#pragma mark - Initializers

/**
* brief Initialize a newly allocated representation with the given content-type and purpose.
*
* param type			The content-type
* param relationship	The purpose of the representation. See AdobeLibraryRepresentation.h for
*                                                      built-in purpose values.
*
* return				The new representation.
*/
- (id)initWithContentType:(NSString *)type andRelationship:(NSString *)relationship;

/**
* brief Initialize a newly allocated representation with the given file, content-type, and purpose.
*
* param filePath		The path to local file to use
* param type			The content-type
* param relationship	The purpose of the representation. See AdobeLibraryRepresentation.h for
*                                                      built-in purpose values.
*
* return				The new representation.
*/
- (id)initWithFilePath:(NSString *)filePath contentType:(NSString *)type andRelationship:(NSString *)relationship;

/**
* brief Initialize a newly allocated representation with the given href, content-type, relationship, and external link
* option. If it is not added as an external link, note that the asset will be added to the library on the
* next sync. If it is added as an external link, the asset is not copied into the library, only the given
* sourceHref is copied and used to access the representation content.
*
* The asset will only be downloaded if it matches the filtering options for assets to be downloaded (or
* if manually requested). If it is downloaded, delegates should receive an elementWasAdded
* call when it has completed.
*
* param sourceHref		An absolute href to a file saved in Creative Cloud Storage.
* param type			The content-type
* param relationship	The purpose of the representation. See AdobeLibraryRepresentation.h for
* built-in purpose values.
* param externalLink  Whether or not to add this representation as an external link. If true,
* the asset is not copied into the library, only the given sourceHref is copied and used to access
* the representation content.
*
* return				The new representation.
*/
- (id)initWithSourceHref:(NSString *)sourceHref contentType:(NSString *)type andRelationship:(NSString *)relationship asExternalLink:(BOOL)externalLink;

#pragma mark - Convenience Constructors

/**
* brief Create a new representation with the given content-type.
*
* param type			The content-type
* param relationship	The purpose of the representation. See AdobeLibraryRepresentation.h for
*                                                      built-in purpose values.
*
* return				The new representation.
*/
+ (id)representationWithContentType:(NSString *)type andRelationship:(NSString *)relationship __deprecated;

/**
* brief Create a new representation with the given file.
*
* param filePath		The path to local file to use
* param type			The content-type
* param relationship	The purpose of the representation. See AdobeLibraryRepresentation.h for
*                                                      built-in purpose values.
*
* return				The new representation.
*/
+ (id)representationWithFilePath:(NSString *)filePath contentType:(NSString *)type andRelationship:(NSString *)relationship __deprecated;

/**
* Create a new representation with the given href, content-type, relationship, and external link
* option. If it is not added as an external link, note that the asset will be added to the library on the
* next sync. If it is added as an external link, the asset is not copied into the library, only the given
* sourceHref is copied and used to access the representation content.
*
* The asset will only be downloaded if it matches the filtering options for assets to be downloaded (or
* if manually requested). If it is downloaded, delegates should receive an elementWasAdded
* call when it has completed.
*
* param sourceHref		An absolute href to a file saved in Creative Cloud Storage.
* param type			The content-type
* param relationship	The purpose of the representation. See AdobeLibraryRepresentation.h for
* built-in purpose values.
* param externalLink  Whether or not to add this representation as an external link. If true,
* the asset is not copied into the library, only the given sourceHref is copied and used to access
* the representation content.
*
* return				The new representation.
*/
+ (id)representationWithSourceHref:(NSString *)sourceHref contentType:(NSString *)type andRelationship:(NSString *)relationship asExternalLink:(BOOL)externalLink __deprecated;

/**
* brief Same as above but without the asExternalLink option, for backward compatibility.
*/
+ (id)representationWithSourceHref:(NSString *)sourceHref contentType:(NSString *)type andRelationship:(NSString *)relationship __deprecated;

#pragma mark - Properties

/** The relationship of the representation. See AdobeLibraryRelationship.h for built-in values. */
@property (readwrite, nonatomic) NSString *relationship;

/** Whether or not this representation is a full size rendition of the element */
@property (readwrite, nonatomic, getter = isFullSize) BOOL fullSize;

/** The width of the representation. */
@property (readwrite, nonatomic) NSNumber *width;

/** The height of the representation. */
@property (readwrite, nonatomic) NSNumber *height;

/** The length of the content for this representation. Can only be set for external link representations. */
@property (readwrite, nonatomic) NSNumber *contentLength;

/**
* brief Set value for a given key on this representation.
*
* param value			The value to set with the key.
* param key				The key to use to set the value on the representation.
* param keyNamespace	The namespace to use with the key.
* param errorPtr		Gets set if an error occurs while setting the value.
*/
- (BOOL)setValue:(id)value forKey:(NSString *)key forNamespace:(NSString *)keyNamespace andError:(NSError **)errorPtr;

@end

#endif
