/******************************************************************************
*
* ADOBE CONFIDENTIAL
* ___________________
*
* Copyright 2016 Adobe Systems Incorporated
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

#ifndef AdobeLibraryElementInternalHeader
#define AdobeLibraryElementInternalHeader

#import <Foundation/Foundation.h>

#import <AdobeCreativeSDKAssetModelOSX/AdobeLibraryElement.h>

@class AdobeDCXElement;

@interface AdobeLibraryElement ()

/**
* brief Creates and adds new representation with the given content-type.
*
* param type			The content-type
* param relationship	The purpose of the representation. See AdobeLibraryRepresentation.h for
*                                                      built-in purpose values.
* param errorPtr      Gets set if an error occurs while creating the new representation.
*
* return				The new representation.
*/
- (AdobeLibraryRepresentation *) addRepresentationWithContentType:(NSString *)type
withRelationship:(NSString *)relationship
withError:(NSError **)errorPtr;

/**
* Creates and adds a new representation with the given file or href, content-type, and relationship.
* You should only specify one of either filePath or sourceHref.
*
* For an href representaiton, you specify whether to add it as an external link or copy it into the
* library. If it is not added as an external link, the asset will be added to the library on the
* next sync. If it is added as an external link, the asset is not copied into the library, only the given
* sourceHref is copied and used to access the representation content.
*
* The asset will only be downloaded if it matches the filtering options for assets to be downloaded (or
* if manually requested). If it is downloaded, delegates should receive an elementWasAdded
* call when it has completed.
*
* param type			The content-type
* parma filePath      The path to the source file to be used for this representation.
* param sourceHref	An absolute href to a file saved in Creative Cloud Storage or an external service.
* param externalLink  Whether or not to add this representation as an external link. If true,
* the asset is not copied into the library, only the given sourceHref is copied and used to access
* the representation content.
* param relationship	The purpose of the representation. See AdobeLibraryRepresentation.h for
* built-in purpose values.
* param width         Optional. The width of the representation.
* param height        Optional. The height of the representation.
* param isFullSize    Whether or not this representation is a full size rendition of the element.
* param errorPtr      Gets set if an error occurs while creating the new representation.
*
* return				The new representation.
*/
- (AdobeLibraryRepresentation *) addRepresentationWithContentType:(NSString *)type
fromFile:(NSString *)filePath
fromHref:(NSString *)sourceHref
asExternalLink:(BOOL)externalLink
withRelationship:(NSString *)relationship
withWidth:(NSNumber *)width
withHeight:(NSNumber *)height
isFullSize:(BOOL)isFullSize
withError:(NSError **)errorPtr;

/**
* brief Remove a representation.
*
* param representation  The representation to remove.
* param errorPtr        Gets set if an error occurs while removing the representation.
*
* return                The removed representation.
*/
- (AdobeLibraryRepresentation *)removeRepresentation:(AdobeLibraryRepresentation *)representation withError:(NSError **)errorPtr;

/**
* brief Remove all representations.
*
* param errorPtr      Gets set if an error occurs while removing the representations.
*/
- (void)removeAllRepresentations:(NSError **)errorPtr;

/**
* brief Add a tag to this element.
*
* param tagValue The tag to add
*/
- (void)addTag:(NSString *)tagValue;

/**
* brief Add multiple tags to this element.
*
* param tagValue An array of NSString values to add
*/
- (void)addTags:(NSArray *)tagsToAdd;

/**
* brief Remove a tag from this element.
*
* param tagValue The tag to remove
*/
- (void)removeTag:(NSString *)tagValue;

/**
* brief Get an AdobeDCXElement for this library element. You must call releaseDCXElement
* when you are done with this object. For 360 workflows, ensure that your message has
* dispatched before releasing the element.
*
* param errorPtr An optional pointer to an error to receive any error information.
* return An AdobeDCXElement that represents this library element, or nil if unsuccessful.
*/
- (AdobeDCXElement *)getDCXElement:(NSError **)errorPtr;


/**
* brief Release the AdobeDCXElement obtained via a call to getDCXElement. For 360 workflows,
* ensure that your message has dispatched before releasing the element.
*
* param dcxElement The DCX element obtained from a call to getDCXElement.
* param errorPtr   An optional pointer to an error to receive any error information.
* return YES if successful, otherwise NO.
*/
- (BOOL)releaseDCXElement:(AdobeDCXElement *)dcxElement withError:(NSError **)errorPtr;

@end

#endif
