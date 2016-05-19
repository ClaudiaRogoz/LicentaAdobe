/*************************************************************************
*
* ADOBE CONFIDENTIAL
* ___________________
*
*  Copyright 2015 Adobe Systems Incorporated
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

#ifndef AdobeAGCImageComponentHeader
#define AdobeAGCImageComponentHeader

#import <Foundation/Foundation.h>

@class AdobeAssetFile;

typedef NSArray AdobeAGCImageComponents;

/**
* class AdobeAGCImageComponent
* brief Represents an image component of an Adobe Graphics Composite.
*/
@interface AdobeAGCImageComponent : NSObject <NSCopying>

@property (nonatomic, readonly, strong) NSString *href;
@property (nonatomic, readonly, strong) NSData *data;
@property (nonatomic, readonly, strong) AdobeAssetFile *file;
@property (nonatomic, readonly, strong) NSString *contentType;

- (instancetype)initWithData:(NSData *)data
href:(NSString *)href
contentType:(NSString *)contentType;

- (instancetype)initWithFile:(AdobeAssetFile *)file;

@end

#endif
