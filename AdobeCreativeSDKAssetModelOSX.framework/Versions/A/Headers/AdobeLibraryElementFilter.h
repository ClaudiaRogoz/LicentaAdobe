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

#ifndef AdobeLibraryElementFilterHeader
#define AdobeLibraryElementFilterHeader

#import <Foundation/Foundation.h>

/**
 * Represents a filter that is used to search/filter elements in a library composite.
 */
@interface AdobeLibraryElementFilter : NSObject

/** The filter to use for the content types of the element's representations . If this is set, the element must have at least one representation with ANY of the specified content types in order to pass the filter. */
@property (copy, nonatomic) NSArray *contentTypes;

/** YES to match any criteria defined in this filter, NO to match all. (Default value is NO) */
@property (nonatomic) BOOL matchAny; //

/** The filter to use for the element name. If this is set, the element name must contain the specified string to pass the filter. */
@property (copy, nonatomic) NSString *name;

/** The filter to use for the element type. If this is set, the element type must be equal to this in order to pass the filter. */
@property (copy, nonatomic) NSString *type;

@end

#endif
