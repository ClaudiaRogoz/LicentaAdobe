/******************************************************************************
*
* ADOBE CONFIDENTIAL
* ___________________
*
* Copyright 2015 Adobe Systems Incorporated
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
******************************************************************************/

#ifndef Adobe360MessageBuilderPrivateHeader
#define Adobe360MessageBuilderPrivateHeader

extern NSString *const Adobe360AnalyticsDataSequenceID;
extern NSString *const Adobe360AnalyticsDataSequenceNumber;

@interface Adobe360MessageBuilder ()

// Reserved for analytics data.
@property (strong, nonatomic, readwrite) NSMutableDictionary *analyticsReservedData;

@end

#endif
