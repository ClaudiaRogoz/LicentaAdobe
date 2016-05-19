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

#ifndef AdobePublicationRecordProtocolHeader
#define AdobePublicationRecordProtocolHeader

#import <Foundation/Foundation.h>

@protocol AdobePublicationRecordProtocol <NSObject>

-(BOOL)stageResourcesAt:(NSString*)resourcesStageDirectoryPath withError:(NSError**)errorPtr;

-(NSDictionary*)getDataForCreationWithError:(NSError**)errorPtr;

-(NSDictionary*)getDataForUpdateWithError:(NSError**)errorPtr;

@end

#endif
