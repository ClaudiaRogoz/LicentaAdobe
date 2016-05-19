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

#ifndef AdobeLibraryMutableElementHeader
#define AdobeLibraryMutableElementHeader

#import <Foundation/Foundation.h>

#import <AdobeCreativeSDKAssetModelOSX/AdobeLibraryElement.h>

/**
* brief Mutable version of AdobeLibraryElement.
*
* note This class has been deprecated.
* Create new elements by calling addElement or insertElement in AdobeLibraryComposite. In the new
* APIs, you no longer create mutable versions of elements and representations. AdobeLibraryComposite
* is now the factory for elements and AdobeLibraryElement is the factory for representations.
* You can now modify the properties of an element or a representation directly and it is
* immediately reflected in the in-memory library composite that it belongs to.
*/
@interface AdobeLibraryMutableElement : AdobeLibraryElement

#pragma mark Initializers

/**
* brief Initialize a newly allocated element with the given name and type.
*
* param name    The name of the new element.
* param type    The type of the new element.
*
* return        The new element.
*
* note This class has been deprecated. Create new elements by calling appendElement or insertElement in AdobeLibraryComposite.
*/
- (id)initWithName:(NSString *)name andType:(NSString *)type __deprecated;

#pragma mark Convenience Constructors

/**
* brief Create a new element with the given name and type.
*
* param name    The name of the new element.
* param type    The type of the new element.
*
* return        The new element.
*
* note This class has been deprecated. Create new elements by calling appendElement or insertElement in AdobeLibraryComposite.
*/
+ (id)elementWithName:(NSString *)name andType:(NSString *)type __deprecated;

#pragma mark Properties

/** The name of the element. */
@property (readwrite, nonatomic) NSString *name;

#pragma mark Methods

/**
* brief Add a tag to this element.
*
* param tagValue The tag to add
*
* note This class has been deprecated. Create new elements by calling appendElement
* or insertElement in AdobeLibraryComposite, and perform setters directly on the element.
*/
- (void)addTag:(NSString *)tagValue __deprecated;

/**
* brief Add multiple tags to this element.
*
* param tagValue An array of NSString values to add
*
* note This class has been deprecated. Create new elements by calling appendElement
* or insertElement in AdobeLibraryComposite, and perform setters directly on the element.
*/
- (void)addTags:(NSArray *)tagsToAdd __deprecated;

/**
* brief Remove a tag from this element.
*
* param tagValue The tag to remove
*
* note This class has been deprecated. Create new elements by calling appendElement
* or insertElement in AdobeLibraryComposite, and perform setters directly on the element.
*/
- (void)removeTag:(NSString *)tagValue __deprecated;

@end

#endif
