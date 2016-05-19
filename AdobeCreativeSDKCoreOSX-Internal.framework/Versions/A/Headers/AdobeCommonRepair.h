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

#ifndef AdobeCommonRepairHeader
#define AdobeCommonRepairHeader

#import <Foundation/Foundation.h>

@interface AdobeCommonRepair : NSObject

/**
* Repairs locked files in the DCX directory for PSD extraction workflows.
* There is a bug in iOS 8.0 whereby such orphaned locked files can brick
* a device when an app with such files is deleted and then the device is
* restarted.
*/
+ (void)repairLockedDCXFilesForPSDWorkflows;

/**
* Utility method for clearing the read-only flag on all files within a
* directory tree. This is used internally by the repairLockedDCXFilesForPSDWorkflows
* method. It is exposed here because applications may need to perform similar
* repairs for their use of DCX composites directly.
*/
+ (BOOL)clearReadOnlyFlagsInDirectory:(NSString *)dirPath withError:(NSError **)errorPtr;

@end

#endif
