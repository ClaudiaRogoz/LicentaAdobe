/*************************************************************************
*
* ADOBE CONFIDENTIAL
* ___________________
*
*  Copyright 2014 Adobe Systems Incorporated
*  All Rights Reserved.
*
* NOTICE:  All information contained herein is, and remains
* the property of Adobe Systems Incorporated and its suppliers,
* if any.  The intellectual and technical concepts contained
* herein are proprietary to Adobe Systems Incorporated and its
* suppliers and are protected by trade secret or copyright law.
* Dissemination of this information or reproduction of this material
* is strictly forbidden unless prior written permission is obtained
* from Adobe Systems Incorporated.
**************************************************************************/

#ifndef AdobePhotoPrivateHeader
#define AdobePhotoPrivateHeader

@class AdobeCloud;

/**
* Exposes private helper methods and ivars to the different categories of AdobePhoto.
*/
@interface AdobePhoto ()

@property (readwrite, nonatomic, strong) NSString *internalID;
@property (readwrite, nonatomic, strong) NSString *GUID;
@property (readwrite, nonatomic, strong) NSString *href;
@property (readwrite, nonatomic, strong) NSString *baseHref;
@property (readwrite, nonatomic, strong) NSDate *creationDate;
@property (readwrite, nonatomic, strong) NSDate *modificationDate;
@property (readwrite, nonatomic, strong) AdobeCloud *cloud;
@property (readwrite, nonatomic, strong) NSDictionary *objectDescription;

@end

#endif
