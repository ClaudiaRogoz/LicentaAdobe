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

#ifndef AdobeLibraryCompositeInternalHeader
#define AdobeLibraryCompositeInternalHeader

#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeStorageResource.h>
#import <Foundation/Foundation.h>

@class AdobeDCXElement;
@class AdobeLibraryElement;
@class AdobeLibraryRepresentation;
@class AdobeLibraryElementFilter;
@class AdobeLibraryMutableElement;
@class AdobeLibraryMutableRepresentation;

/**
* brief This class contains all the mutable portions of AdobeLibraryComposite, which have
* not been made public yet. This first public release will only allow 3rd parties to read
* a library and add some very specific element types via the utility class AdobeDesignLibraryUtils.
*/
@interface AdobeLibraryComposite ()

#pragma mark - Operations

/**
* brief Call to begin a batch of library operations. The operations happened
* after this call will not be commited until the endChangesWithError is called.
*/
- (void)beginChanges;

/**
* brief Call to end a batch of library operations and commit them. It commits
* all the operations happened since the last beginChanges call.
*
* param errorPtr   Gets set if an error occurs while commiting changes.
*/
- (BOOL)endChangesWithError:(NSError **)errorPtr;

/**
* brief Discard any uncommitted changes. This will essentially reload the library
*              from the file system, throwing away any changes. All changes since the last endChanges
*              call will be discarded regardless of the number of nested beginChanges calls.
* return Returns YES if successful, otherwise NO.
*/
- (BOOL)discardChanges;

#pragma mark - Element access

/**
* brief Get a unique reference string for the given element. This reference string can be used anytime to
*        retrieve the given element object.
*
* param element The element for which to retrieve the reference.
*
* return a unique reference string that represents the given element.
*/
- (NSString *) getElementReference:(AdobeLibraryElement *)element;

/**
* brief Adds a new element in the library composite with the given name and type.
*
* param name       The name of the new element.
* param type       The type of the new element.
* param errorPtr   Gets set if an error occurs while adding the element.
*
* return the newly added/updated element
*/
- (AdobeLibraryElement *) addElement:(NSString *)name withType:(NSString *)type withError:(NSError **)errorPtr;

/**
* brief Inserts a new element in the library composite at the given index position.
*
* param name       The name of the new element.
* param type       The type of the new element.
* param index		 The index where to insert the element. This index is based on the number of elements for this particular delegate based on its requested element types.
* param delegate	 The delegate that wishes to insert the element.
* param errorPtr   Gets set if an error occurs while inserting the element.
*
* return the newly inserted element if successful, otherwise nil
*/
- (AdobeLibraryElement *) insertElement:(NSString *)name withType:(NSString *)type atIndex:(NSUInteger)index forDelegate:(id<AdobeLibraryDelegate>)delegate withError:(NSError **)errorPtr;

/**
* brief Move the given element after another specified element.
*
* param element			The element to move.
* param afterElement	The element to move the element after, nil to move to the front.
* param errorPtr		Gets set if an error occurs while moving the element.
*
* return the updated element
*/
- (AdobeLibraryElement *)moveElement:(AdobeLibraryElement *)element afterElement:(AdobeLibraryElement *)afterElement andError:(NSError **)errorPtr;

/**
* brief Move the given element before another specified element.
*
* param element			The element to move.
* param beforeElement	The element to move the element before, nil to move to the end.
* param errorPtr		Gets set if an error occurs while moving the element.
*
* return the updated element
*/
- (AdobeLibraryElement *)moveElement:(AdobeLibraryElement *)element beforeElement:(AdobeLibraryElement *)beforeElement andError:(NSError **)errorPtr;

/**
* brief Copies an element from the given library. This will perform a deep copy and will
*        copy all of the element's representations.
*
* param element       The element to copy.
* param sourceLibrary The source library, may be nil in which case the source library is this library.
* param errorPtr      Gets set if an error occurs when copying the element.
*
* return the new element.
*/
- (AdobeLibraryElement *)copyElement:(AdobeLibraryElement *)element fromLibrary:(AdobeLibraryComposite *)sourceLibrary andError:(NSError **)errorPtr;

/**
* brief Adds a new element in the library composite fromt he given AdobeDCXElement.
* The DCX element must represent an underlying AdobeLibraryElement.
*
* param dcxElement    The DCX element that represents the library element to add to the library.
* param errorPtr      Gets set if an error occurs while adding the element.
*
* return the newly added element
*/
- (AdobeLibraryElement *) addElementWithDCXElement:(AdobeDCXElement *)dcxElement withError:(NSError **)errorPtr;
@end

#endif
