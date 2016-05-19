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

#ifndef AdobeDesignLibraryHeader
#define AdobeDesignLibraryHeader

#import <AdobeCreativeSDKAssetModelOSX/AdobeLibraryComposite.h>
#import <AdobeCreativeSDKAssetModelOSX/AdobeLibraryElement.h>

#import <Foundation/Foundation.h>

@class UIColor;

extern NSString *const AdobeDesignLibraryColorElementType;
extern NSString *const AdobeDesignLibraryColorThemeElementType;
extern NSString *const AdobeDesignLibraryCharacterStyleElementType;
extern NSString *const AdobeDesignLibraryParagraphStyleElementType;
extern NSString *const AdobeDesignLibraryBrushElementType;
extern NSString *const AdobeDesignLibraryImageElementType;
extern NSString *const AdobeDesignLibraryLayerStyleElementType;
extern NSString *const AdobeDesignLibraryLookElementType;
extern NSString *const AdobeDesignLibraryVideoElementType;
extern NSString *const AdobeDesignLibrary3DElementType;
extern NSString *const AdobeDesignLibraryPatternElementType;
extern NSString *const AdobeDesignLibraryTemplateElementType;

/*
 *  A helper class that exposes methods to add specific type of elements to libraries and to get data from elements
 */
@interface AdobeDesignLibraryUtils : NSObject

/**
 * Adds an image element to the given library
 *
 * \param image       URL of the source image to add to the new element. Local file URL only is supported for now.
 * \param name        Name to use for this element
 * \param library     The library to which to add the new element
 * \param errPtr      Optional pointer to an NSError that gets set in case of an error
 *
 * \return            The new element
 */
+ (AdobeLibraryElement *)addImage:(NSURL *)image name:(NSString *)name library:(AdobeLibraryComposite *)library error:(NSError **)errPtr;

/**
 * Adds an RGB color element to the given library
 *
 * \param rgbColor    RGB Color data to use for this element
 * \param name        Name to use for this element
 * \param library     The library to which to add the new element
 * \param errPtr      Optional pointer to an NSError that gets set in case of an error
 *
 * \return            The new element
 */
+ (AdobeLibraryElement *)addRGBColor:(UIColor *)rgbColor name:(NSString *)name library:(AdobeLibraryComposite *)library error:(NSError **)errPtr;

/**
 * Adds a representation which is a rendition for the given element.
 *
 * \param renditionFile	The image file that is the rendition for this element. Local file URL is only supported in the current implementation.
 * \param contentType     The content type of the given rendition file
 * \param element         The element to add this this rendition representation to.
 * \param library			The library which contains the given element.
 * \param width			The width of the given rendition. (Optional)
 * \param height			The height of the given rendition. (Optional)
 * \param fullSize        Whether or not the rendition represented with the path is full size. (Optional)
 * \param errPtr			Optional pointer to an NSError that gets set in case of an error
 */
+ (AdobeLibraryRepresentation *)addRendition:(NSURL *)renditionFile
                                 contentType:(NSString *)contentType
                                   toElement:(AdobeLibraryElement *)element
                                     library:(AdobeLibraryComposite *)library
                                       width:(NSUInteger)width
                                      height:(NSUInteger)height
                                  isFullSize:(BOOL)fullSize
                                       error:(NSError **)errPtr;

/**
 * Returns the available representation content types for the given element
 *
 * \param element     The element for which to return the available representation content types
 * \param library     The library that contains the element
 *
 * \return            The unique list of available representation content types
 */
+ (NSArray *)getRepresentationTypesForElement:(AdobeLibraryElement *)element library:(AdobeLibraryComposite *)library;

/**
 * Returns the file URL for the given Image element and the content type
 *
 * \param element         Image element
 * \param contentType     The content type for the requested file
 * \param library         The library that contains this element
 * \param queue			Optional parameter. If not nil determines the operation queue completion and error blocks get executed on.
 * \param completionBlock Completetion block that gets called with the file path in case of success
 * \param errorBlock      Error block that gets called in case of an error
 */
+ (BOOL)getImageFilePathForElement:(AdobeLibraryElement *)element
                       contentType:(NSString *)contentType
                           library:(AdobeLibraryComposite *)library
                      handlerQueue:(NSOperationQueue *)queue
                        onComplete:(void (^)(NSString *path))completionBlock
                           onError:(void (^)(NSError *error))errorBlock;


/**
 * Returns the RGB color for the given color element
 *
 * \param colorElement	Color element
 * \param library			The library which the element belongs
 *
 * \return                The rgb color for the given color element, or nil if none
 */
+ (UIColor *)getRGBColorForElement:(AdobeLibraryElement *)colorElement inLibrary:(AdobeLibraryComposite *)library;


/**
 * Returns the RGB color for the given color element
 *
 * \param colorThemeElement	Color element
 * \param library			The library which the element belongs
 *
 * \return                  Array of 5 rgb colors for the given color element, or nil if none
 */

+ (NSArray<UIColor *> *)getRGBColorThemeForElement:(AdobeLibraryElement *)colorTheme inLibrary:(AdobeLibraryComposite *)library;

@end

#endif
