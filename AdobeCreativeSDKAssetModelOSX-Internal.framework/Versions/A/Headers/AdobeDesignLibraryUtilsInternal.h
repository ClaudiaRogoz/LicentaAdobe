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

#ifndef AdobeDesignLibraryUtilsInternalHeader
#define AdobeDesignLibraryUtilsInternalHeader

#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeLibraryInternal.h>

#import <Foundation/Foundation.h>

extern NSString *const AdobeDesignLibraryColorElementType;
extern NSString *const AdobeDesignLibraryColorThemeElementType;
extern NSString *const AdobeDesignLibraryCharacterStyleElementType;
extern NSString *const AdobeDesignLibraryBrushElementType;
extern NSString *const AdobeDesignLibraryImageElementType;
extern NSString *const AdobeDesignLibraryLayerStyleElementType;
extern NSString *const AdobeDesignLibraryPattenElementType;

@interface AdobeDesignLibraryRepresentationSource : NSObject

/** The source URL for representation asset */
@property (nonatomic, readwrite) NSURL * sourceURL;

/** The content-type for the asset specified in the sourceURL */
@property (nonatomic, readwrite) NSString * contentType;

/** The width of the content */
@property (nonatomic, readwrite) NSUInteger width;

/** The height of the content */
@property (nonatomic, readwrite) NSUInteger height;

/** The content length */
@property (nonatomic, readwrite) NSUInteger contentLength;

@end

@interface AdobeDesignLibraryStockData : NSObject

/** The asset id for this stock asset */
@property (nonatomic, readwrite) NSInteger assetId;

/** The type of license, "Standard" or "Extended", if this asset is licensed. "Standard" is used if nil. */
@property (nonatomic, readwrite) NSString * licenseType;

/** Optional. The stock transaction id for this asset - returned by the stock API when a stock asset is purchased. */
@property (nonatomic, readwrite) NSString * stockId;

/** The query string used to find this asset */
@property (nonatomic, readwrite) NSString * query;

@end

/*
* A helper class that exposes methods to add specific type of elements to libraries and to get data from representations
*/
@interface AdobeDesignLibraryUtils ()

/**
* Adds a brush element to the given design library
*
* param primaryBrush	URL of the source image to add to the new element. Local file URL only is supported for now.
* param contentType		The content type of the primary brush file.
* param brushFiles		A dictionary of alternate brush files to be added to the new brush element. The content type
* should be the key and the file URL (NSURL) for each alternate brush is the value.
* Can be nil for no alternate brush files.
* param name			Name to use for this element
* param library			The library to which to add the new element
* param errPtr			Optional pointer to an NSError that gets set in case of an error
*
* return            The new element
*/
+ (AdobeLibraryElement *)addBrushWithPrimary:(NSURL *)primaryBrush contentType:(NSString *)contentType alternateBrushes:(NSDictionary *)brushFiles name:(NSString *)name library:(AdobeLibraryComposite *)library error:(NSError **)errPtr;


/**
* Adds a color element to the given design library
*
* param data        Color data to use for this element
* param name        Name to use for this element
* param library     The library to which to add the new element
* param errPtr      Optional pointer to an NSError that gets set in case of an error
*
* return            The new element
*/
+ (AdobeLibraryElement *)addColor:(NSDictionary *)data name:(NSString *)name library:(AdobeLibraryComposite *)library error:(NSError **)errPtr;

/**
* Adds a color theme element to the given design library
*
* param data        Color theme data to use for this element
* param name        Name to use for this element
* param library     The library to which to add the new element
* param errPtr      Optional pointer to an NSError that gets set in case of an error
*
* return            The new element
*/
+ (AdobeLibraryElement *)addColorTheme:(NSDictionary *)data name:(NSString *)name library:(AdobeLibraryComposite *)library error:(NSError **)errPtr;

/**
* Adds a color element to the given design library.
*
* param data        Color data to use for this element
* param name        Name to use for this element
* param library     The library to which to add the new element
* param errPtr      Optional pointer to an NSError that gets set in case of an error
*
* return            The new element
*/
+ (AdobeLibraryElement *)addCharacterStyle:(NSDictionary *)data name:(NSString *)name library:(AdobeLibraryComposite *)library error:(NSError **)errPtr;

/**
* Adds a new Adobe Stock element with the given content type. Stock elements are created with
* externally linked representations for the comp and licensed asset. The rendition is copied
* into the library.
*
* param elementType       The type of stock element. Currently only support
*                              AdobeDesignLibraryImageElementType or AdobeDesignLibraryVideoElementType.
* param name              The name for the new element.
* param library           The library to add the element to.
* param licensedAsset     The licensed asset source, must not specify a local file url. Pass in nil if the stock item is not licensed.
* param compAsset         The comp asset source, must not specify a local file url. Required.
* param renditionAsset    The rendition asset source. May be a local file url or a source href url.
* param stockData         The stock data, see AdobeDesignLibraryStockData above.
* param errPtr            Optional pointer to an NSError that gets set in case of an error
*
* return                  The new stock element or nil if an error occurred.
*/
+ (AdobeLibraryElement *)addAdobeStockElementOfType:(NSString *)elementType
name:(NSString *)name
library:(AdobeLibraryComposite *)library
licensedAsset:(AdobeDesignLibraryRepresentationSource *)licensedAsset
compAsset:(AdobeDesignLibraryRepresentationSource *)compAsset
renditionAsset:(AdobeDesignLibraryRepresentationSource *)renditionAsset
stockData:(AdobeDesignLibraryStockData *)stockData
error:(NSError **)errPtr;

/**
* Updates an existing Adobe Stock element to include licensing information.
*
* param stockElement      An existing stock element to update.
* param library           The library to add the element to.
* param licensedAsset     The licensed asset source, must not specify a local file url.
* param stockData         The stock data, see AdobeDesignLibraryStockData above.
* param errPtr            Optional pointer to an NSError that gets set in case of an error
*
* return                  The new stock element or nil if an error occurred.
*/
+ (AdobeLibraryElement *)updateAdobeStockElement:(AdobeLibraryElement *)stockElement
library:(AdobeLibraryComposite *)library
licensedAsset:(AdobeDesignLibraryRepresentationSource *)licensedAsset
compAsset:(AdobeDesignLibraryRepresentationSource *)compAsset
renditionAsset:(AdobeDesignLibraryRepresentationSource *)renditionAsset
stockData:(AdobeDesignLibraryStockData *)stockData
error:(NSError **)errPtr;

/**
* Updates all Adobe Stock elements in all libraries to include licensing information.
* This will search all libraries for elements that have a stock asset id equal to the one
* specified in the stockData parameter, and update them to the licensing information provided
* in the licensedAsset parameter. Note that if an error occurs while updating any element,
* an error is returned in the errPtr given and the entire operation is aborted.
*
* param licensedAsset     The licensed asset source, must not specify a local file url.
* param stockData         The stock data, see AdobeDesignLibraryStockData above.
* param errPtr            Optional pointer to an NSError that gets set in case of an error
*
* return                  The number of elements updated.
*/
+ (NSUInteger)licenseAdobeStockElements:(AdobeDesignLibraryRepresentationSource *)licensedAsset
compAsset:(AdobeDesignLibraryRepresentationSource *)compAsset
renditionAsset:(AdobeDesignLibraryRepresentationSource *)renditionAsset
stockData:(AdobeDesignLibraryStockData *)stockData
error:(NSError **)errPtr;

/**
* Get the asset ID for the Adobe Stock asset associated with this element, or 0 if this
* is not an Adobe Stock asset.
*
* param element   The element to get the asset id for.
* param library   The library composite containing the element.
*
* return          The asset ID of the stock asset, or 0 if this is not an Adobe Stock element.
*/
+ (NSInteger)getStockAssetIdForElement:(AdobeLibraryElement *)element inLibrary:(AdobeLibraryComposite *)library;

/**
* Return whether or not the given element is a licensed Adobe Stock element. Note that this
* method does NOT check if the current user has purchased a license, just if the element
* has been purchased by at least one user with write access to this library.
*
* param element   The element to check.
* param library   The library composite containing the element.
*
* return          YES if this is a licensed Adobe Stock element, otherwise NO.
*/
+ (BOOL)getIsLicensedForStockElement:(AdobeLibraryElement *)element inLibrary:(AdobeLibraryComposite *)library;

/**
* Returns the file URL for the given Brush element and the content type
*
* param element         Brush element
* param contentType     The content type for the requested file
* param library         The library that contains this element
* param queue			Optional parameter. If not nil determines the operation queue completion and error blocks get executed on.
* param completionBlock Completetion block that gets called with the file path in case of success
* param errorBlock      Error block that gets called in case of an error
*/
+ (BOOL)getBrushFilePathForElement:(AdobeLibraryElement *)element contentType:(NSString *)contentType library:(AdobeLibraryComposite *)library handlerQueue:(NSOperationQueue *)queue onComplete:(void (^)(NSString *path))completionBlock onError:(void (^)(NSError *error))errorBlock;

/**
* Returns the character style data for the given character style element
*
* param element     Character style element
* param library     The library that contains this element
* return            The character style data for the given character style element
*/
+ (NSDictionary *)getCharacterStyleDataForElement:(AdobeLibraryElement *)element inLibrary:(AdobeLibraryComposite *)library;

/**
* Returns the color data for the given color element
*
* param element     Color representation
* param library     The library that contains this element
* return            The color data for the given color element
*/
+ (NSDictionary *)getColorDataForElement:(AdobeLibraryElement *)element inLibrary:(AdobeLibraryComposite *)library;

@end

#endif
