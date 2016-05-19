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

#ifndef AdobePhotoProtectedHeader
#define AdobePhotoProtectedHeader

@class AdobePhotoSession;

extern NSString *const AdobePhotoCoderKeyGUID;
extern NSString *const AdobePhotoCoderKeyHref;
extern NSString *const AdobePhotoCoderKeyBaseHref;
extern NSString *const AdobePhotoCoderKeyName;
extern NSString *const AdobePhotoCoderKeyCreationDate;
extern NSString *const AdobePhotoCoderKeyModificationDate;
extern NSString *const AdobePhotoCoderKeyCloud;

@interface AdobePhoto (Protected)

- (id)init;

- (AdobePhotoSession *)session;

@end

#endif
