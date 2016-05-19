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
*
**************************************************************************/

#ifndef AdobeNetworkHTTPBodyStreamHeader
#define AdobeNetworkHTTPBodyStreamHeader

#import <Foundation/Foundation.h>

/** The AdobeNetworkHTTPBodyStreamFactory protocol is used in NSURLConnectionDelegate interfaces that implement the URLSession:task:needNewBodyStream method.
* The latter method is invoked in case retransmission of a re    uest is required*/

@protocol AdobeNetworkHTTPBodyStreamFactory <NSObject>

/** Create a new body stream */
- (NSInputStream *)createNewBodyStream;

/** Body stream length*/
- (long)getContentLength;

@end

#endif
