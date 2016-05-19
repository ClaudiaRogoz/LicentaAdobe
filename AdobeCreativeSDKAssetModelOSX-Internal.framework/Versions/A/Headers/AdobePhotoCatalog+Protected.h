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

#ifndef AdobePhotoCatalogProtectedHeader
#define AdobePhotoCatalogProtectedHeader

@class AdobeCloud;

@interface AdobePhotoCatalog (Protected)

- (id)initWithName:(NSString *)name
cloud:(AdobeCloud *)cloud;

- (id)initWithName:(NSString *)name
guid:(NSString *)guid
cloud:(AdobeCloud *)cloud;

- (id)initWithGUID:(NSString *)guid
cloud:(AdobeCloud *)cloud;

- (BOOL)updateFromData:(NSData *)data
error:(NSError **)errorPtr;

- (BOOL)updateFromDictionary:(NSDictionary *)data
error:(NSError **)errorPtr;

+ (AdobePhotoCatalog *)create:(NSString *)name
type:(AdobePhotoCatalogType)type
cloud:(AdobeCloud *)cloud
successBlock:(void (^)(AdobePhotoCatalog *catalog))successBlock
errorBlock:(void (^)(NSError *error))errorBlock;

+ (void)listOfType:(AdobePhotoCatalogType)type
cloud:(AdobeCloud *)cloud
successBlock:(void (^)(NSArray *))successBlock
errorBlock:(void (^)(NSError *))errorBlock;

@end

#endif /* ifndef AdobePhotoCatalogProtectedHeader */
