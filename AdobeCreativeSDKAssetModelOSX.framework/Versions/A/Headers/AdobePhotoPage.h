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

#ifndef AdobePhotoPageHeader
#define AdobePhotoPageHeader

#import <Foundation/Foundation.h>

/**
 * AdobePhotoPage is the page value used in the listing of an AdobePhotoCollection.
 *
 */
@interface AdobePhotoPage : NSObject <NSCopying, NSCoding>

/**
 * A utility to test the equlity of two AdobePhotoPage.
 *
 * @param page The AdobePhotoPage to test against.
 *
 * @returns True if the pages are the same.
 */
- (BOOL)isEqualToPage:(AdobePhotoPage *)page;

@end

#endif
