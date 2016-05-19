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

#ifndef AdobePhotoCollectionProtectedHeader
#define AdobePhotoCollectionProtectedHeader

@interface AdobePhotoCollection (Protected)

- (id)initWithName:(NSString *)name
catalog:(AdobePhotoCatalog *)catalog;

- (id)initWithName:(NSString *)name
guid:(NSString *)guid
catalog:(AdobePhotoCatalog *)catalog;

- (id)initWithGUID:(NSString *)guid
catalog:(AdobePhotoCatalog *)catalog;

+ (AdobePhotoCollection *)create:(NSString *)name
guid:(NSString *)guid
catalog:(AdobePhotoCatalog *)catalog
successBlock:(void (^)(AdobePhotoCollection *collection))successBlock
errorBlock:(void (^)(NSError *error))errorBlock;

- (BOOL)updateFromData:(NSData *)data
catalog:(AdobePhotoCatalog *)catalog
error:(NSError **)errorPtr;

- (BOOL)updateFromDictionary:(NSDictionary *)data
catalog:(AdobePhotoCatalog *)catalog
error:(NSError **)errorPtr;

@end

#endif /* ifndef AdobePhotoCollectionProtectedHeader */
