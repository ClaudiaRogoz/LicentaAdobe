/******************************************************************************
*
* ADOBE CONFIDENTIAL
* ___________________
*
* Copyright 2013 Adobe Systems Incorporated
* All Rights Reserved.
*
* NOTICE:  All information contained herein is, and remains the property of
* Adobe Systems Incorporated and its suppliers, if any. The intellectual and
* technical concepts contained herein are proprietary to Adobe Systems
* Incorporated and its suppliers and are protected by trade secret or
* copyright law. Dissemination of this information or reproduction of this
* material is strictly forbidden unless prior written permission is obtained
* from Adobe Systems Incorporated.
*
* THIS FILE IS PART OF THE CREATIVE SDK PUBLIC API
*
******************************************************************************/

#ifndef AdobeAuthEndpointHeader
#define AdobeAuthEndpointHeader

/**
*
* AdobeAuthEndpoint is an enumerated type that specifies the type of Adobe Creative Cloud
* endpoint that should be used by the application.  It allows the application to programmatically
* control whether it talks to test, staging or production Creative Cloud servers.
*
* See AdobeUXAuthManager
*
*/
typedef NS_ENUM (NSInteger, AdobeAuthEndpoint)
{
/** The undefined endpoint - do not use */
AdobeAuthEndpointUndefined = 0,
/** Production servers in the United States */
AdobeAuthEndpointProductionUS = 1,
/** Staging servers in the United States */
AdobeAuthEndpointStageUS = 2,
/** CloudLabs servers in the United States */
AdobeAuthEndpointCloudLabsUS = 3,   // CloudLabs endpoint for the Image and Storage Services, all other endpoints are Stage.
/** Internal Testing server in the United States */
AdobeAuthEndpointTestUS = 4
};

@interface AdobeAuthEndpointStrings : NSObject

+ (NSDictionary *)endpointString;

@end

#endif /* ifndef AdobeAuthEndpointHeader */
