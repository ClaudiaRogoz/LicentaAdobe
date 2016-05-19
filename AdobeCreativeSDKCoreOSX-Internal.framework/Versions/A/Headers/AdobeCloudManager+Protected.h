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

#ifndef AdobeCloudManagerProtectedHeader
#define AdobeCloudManagerProtectedHeader

#import <Foundation/Foundation.h>

@interface AdobeCloudManager (Protected)

- (void)refreshCloudsFromCache __deprecated_msg("This method is depracated. There is no need to "
"call this method any longer. Simply calling the "
"clouds property from AdobeCloudManager will now "
"populate the list of clouds from the cache.");

- (NSArray *)cloudsFromCache;

@end

#endif
