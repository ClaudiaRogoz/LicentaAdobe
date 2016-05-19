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

/**************************************************************************
 * [PRIVATE BETA] CreativeSync enables seamless multi-app workflows via
 * the included APIs. If you have any questions, please contact us at
 * https://creativesdk.zendesk.com/hc/en-us/requests/new
 *************************************************************************/

#ifndef Adobe360CloudAssetReferenceHeader
#define Adobe360CloudAssetReferenceHeader

/**
 * \brief Adobe360CloudAssetReference is a mutable object that describes the identity and cloud-affiliation
 * of a server asset that is referenced within an Adobe360Message
 */
@interface Adobe360CloudAssetReference : NSObject <NSCopying>

@property (strong, nonatomic) NSString *href;
@property (strong, nonatomic) NSString *name;
@property (strong, nonatomic) NSString *cloudName;
@property (strong, nonatomic) NSString *cloudHref;

+ (instancetype)cloudAssetReferenceWithHref:(NSString *)href
                                       name:(NSString *)name
                                  cloudName:(NSString *)cloudName
                                  cloudHref:(NSString *)cloudHref;

@end

#endif
