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

#ifndef AdobeAGCManifestHeader
#define AdobeAGCManifestHeader

#import <Foundation/Foundation.h>

/**
* class AdobeAGCManifest
* brief Represents and manages the manifest of an Adobe Graphics Composite.
*/
@interface AdobeAGCManifest : NSObject <NSCopying>

@property (nonatomic, readonly, strong) NSData *data;
@property (nonatomic, readonly, strong) NSString *contentType;

- (instancetype)initWithData:(NSData *)data;

@end

#endif
