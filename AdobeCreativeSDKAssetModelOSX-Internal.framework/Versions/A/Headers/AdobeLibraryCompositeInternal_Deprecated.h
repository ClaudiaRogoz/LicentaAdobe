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

#ifndef AdobeLibraryCompositeInternal_Deprecated_h
#define AdobeLibraryCompositeInternal_Deprecated_h

#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeLibraryCompositeInternal.h>

/**
* brief This class contains all the deprecated methods of AdobeLibraryComposite. In the new
* APIs, you no longer create mutable versions of elements and representations. AdobeLibraryComposite
* is now the factory for elements and AdobeLibraryElement is the factory for representations.
* You can now modify the properties of an element or a representation directly and it is
* immediately reflected in the in-memory library composite that it belongs to.
*/
@interface AdobeLibraryComposite ()

/**
* brief Adds the given element in the library composite.
*
* param element    The element to add.
* param errorPtr   Gets set if an error occurs while adding the element.
*
* return the newly added/updated element
*
* note This method has been deprecated, use the new addElement:withType:withError: method instead.
*/
- (AdobeLibraryElement *)addElement:(AdobeLibraryElement *)element andError:(NSError **)errorPtr __deprecated;

/**
* brief Inserts the given element in the library composite at the given index position.
*
* param element    The element to insert.
* param index		 The index where to insert the element. This index is based on the number of elements for this particular delegate based on its requested element types.
* param delegate	 The delegate that wishes to insert the element.
* param errorPtr   Gets set if an error occurs while inserting the element.
*
* return the updated element
*
* note This method has been deprecated, use the new insertElement:withType:atIndex:forDelegate:withError: method instead.
*/
- (AdobeLibraryElement *)insertElement:(AdobeLibraryElement *)element atIndex:(NSUInteger)index forDelegate:(id<AdobeLibraryDelegate>)delegate andError:(NSError **)errorPtr __deprecated;

/**
* brief Updates the properties of an element.
*
* param element     The modified element to update.
* param errorPtr    Gets set if an error occurs while updating the element.
*
* return the updated element
*
* note This method has been deprecated, you can now just make the changes to an AdobeLibraryElement directly.
*/
- (AdobeLibraryElement *)updateElement:(AdobeLibraryMutableElement *)element andError:(NSError **)errorPtr __deprecated;

/**
* brief Add a representation.
*
* param representation	The representation to add.
* param element         The element to add the representation to.
* param errorPtr        Gets set if an error occurs while adding the representation.
*
* return				The new representation.
*
* note This method has been deprecated, use the addRepresentation method on AdobeLibraryElement method instead.
*/
- (AdobeLibraryRepresentation *)addRepresentation:(AdobeLibraryMutableRepresentation *)representation toElement:(AdobeLibraryElement *)element andError:(NSError **)errorPtr __deprecated;

/**
* brief Remove a representation.
*
* param representation	The representation to remove.
* param errorPtr        Gets set if an error occurs while removing the representation.
*
* return				The removed representation.
*
* note This method has been deprecated, use the removeRepresentation method on AdobeLibraryElement method instead.
*/
- (AdobeLibraryRepresentation *)removeRepresentation:(AdobeLibraryRepresentation *)representation andError:(NSError **)errorPtr __deprecated;

/**
* brief Updates the representation.
*
* param representation	The modified representation.
* param errorPtr         Gets set if an error occurs while updating the representation.
*
* return				The updated representation.
*
* note This method has been deprecated, you can now just make the changes to an AdobeLibraryRepresentation directly.
*/
- (AdobeLibraryRepresentation *)updateRepresentation:(AdobeLibraryMutableRepresentation *)representation andError:(NSError **)errorPtr __deprecated;

@end

#endif /* AdobeLibraryCompositeInternal_Deprecated_h */
