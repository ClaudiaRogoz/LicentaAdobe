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

#ifndef Adobe360ContextHeader
#define Adobe360ContextHeader

#import <Foundation/Foundation.h>

@class Adobe360CloudAssetReference;

/**
 * Adobe360Context is a mutable object that describes the application, user, and project contexts associated
 * with the inputs or outputs contained within a 360 workflow message
 */
@interface Adobe360Context : NSObject <NSCopying>

@property (strong, nonatomic) NSString *appName;
@property (strong, nonatomic) NSString *userEntityRef;
@property (strong, nonatomic) Adobe360CloudAssetReference *projectRef;
@property (strong, nonatomic) Adobe360CloudAssetReference *libraryRef;

/**
 * \brief Constructs an Adobe360Context object
 */
+ (instancetype)contextWithAppName:(NSString *)appName
                              user:(NSString *)userEntityRef
                           project:(Adobe360CloudAssetReference *)projectRef
                           library:(Adobe360CloudAssetReference *)libraryRef;

@end

#endif
