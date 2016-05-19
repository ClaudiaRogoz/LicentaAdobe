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

#ifndef AdobeAssetPackageRenderablePageProtocolHeader
#define AdobeAssetPackageRenderablePageProtocolHeader

#import <Foundation/Foundation.h>

#import <AdobeCreativeSDKAssetModelOSX/AdobeAssetFile.h>
#import <AdobeCreativeSDKAssetModelOSX/AdobeAssetPackagePages.h>

/**
* All package pages define the following options
*/
@protocol AdobeAssetPackageRenderablePageProtocol <NSObject>

- (AdobeAssetPackagePages *)package;

- (NSString *)name;

- (NSString *)GUID;

- (NSString *)type;

- (NSDate *)modificationDate;

- (instancetype)initWithName:(NSString *)name
page:(NSInteger)number
renditionComponent:(AdobeDCXComponent *)component
package:(AdobeAssetPackagePages *)package;

- (AdobeAssetAsyncRequest *)downloadRenditionWithType:(AdobeAssetFileRenditionType)type
dimensions:(CGSize)dimensions
requestPriority:(NSOperationQueuePriority)priority
progressBlock:(void (^)(double))progressBlock
successBlock:(void (^)(NSData *data, BOOL wasCached))successBlock
cancellationBlock:(void (^)(void))cancellationBlock
errorBlock:(void (^)(NSError *error))errorBlock;

@end

#endif /* ifndef AdobeAssetPackageRenderablePageProtocolHeader */
