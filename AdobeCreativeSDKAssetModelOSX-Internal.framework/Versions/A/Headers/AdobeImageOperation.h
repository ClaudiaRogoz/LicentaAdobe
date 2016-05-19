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

#ifndef AdobeImageOperationHeader
#define AdobeImageOperationHeader

#import <Foundation/Foundation.h>

/**
* class AdobeImageOperation
*/
@interface AdobeImageOperation : NSObject

/** options */
@property (nonatomic) NSDictionary *options;

/** results */
@property (nonatomic) NSDictionary *results;

/** Inputs. Keys are input names; values are AdobeStorageResourceItem or array of AdobeStorageResourceItem. */
@property (nonatomic) NSDictionary *inputs;

/** Components. An array of AdobeStorageResourceItem. */
@property (nonatomic) NSArray *components;

/** Ouput dispositions. Keys are output names; values are AdobeImageOutputParameters. (No arrays!) */
@property (nonatomic) NSDictionary *outputDispositions;

/** Outputs. Keys are output names; values are AdobeStorageResourceItem or array of AdobeStorageResourceItem. */
@property (nonatomic) NSDictionary *outputs;

@end

#endif
