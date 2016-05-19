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

#ifndef Adobe360WorkflowDispatchProtectedHeader
#define Adobe360WorkflowDispatchProtectedHeader

#ifndef DMALIB

#import <Foundation/Foundation.h>

@interface Adobe360WorkflowDispatch (Protected)

/**
* Override the maximum allowable bytes allowed by the in-memory transport option.
*
* To use a percentage of RAM, you can set this to some fraction of
* [NSProcessInfo processInfo].physicalMemory.
*
* By default, this is 100MB.
*
* @param maxFileSizeInBytes The maximum message size in bytes allowed.
*/
- (void)setInMemoryTransportMaximumMessageSize:(unsigned long long)maxMessageInBytes;

@end

#endif // !DMALIB

#endif
