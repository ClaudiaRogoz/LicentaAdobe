/*************************************************************************
*
* ADOBE CONFIDENTIAL
* ___________________
*
* Copyright 2015 Adobe Systems Incorporated
* All Rights Reserved.
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

#ifndef AdobeS3ChunkedBodyStreamFactoryHeader
#define AdobeS3ChunkedBodyStreamFactoryHeader

#import <Foundation/Foundation.h>
#import <AdobeCreativeSDKCoreOSX-Internal/AdobeNetworkHTTPBodyStreamFactory.h>

@interface AdobeS3ChunkedBodyStreamFactory : NSObject<AdobeNetworkHTTPBodyStreamFactory>

+ (id)bodyStreamFactoryWithInputFilePath:(NSString *)inputFilePath
length:(NSNumber *)length
date:(NSDate *)date
scope:(NSString *)scope
kSigning:(NSData *)kSigning
headerSignature:(NSString *)headerSignature;
/** Create a new body stream */
- (NSInputStream *)createNewBodyStream;

/** Body stream length*/
- (long)getContentLength;

@end

#endif
