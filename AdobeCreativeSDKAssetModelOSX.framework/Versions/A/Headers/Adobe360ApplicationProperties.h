/*************************************************************************
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
* suppliers and are protected by all applicable intellectual property 
* laws, including trade secret and copyright laws.
* Dissemination of this information or reproduction of this material
* is strictly forbidden unless prior written permission is obtained
* from Adobe Systems Incorporated.
**************************************************************************/

/************************************************************************** 
 * [PRIVATE BETA] CreativeSync enables seamless multi-app workflows via
 * the included APIs. If you have any questions, please contact us at
 * https://creativesdk.zendesk.com/hc/en-us/requests/new
 *************************************************************************/

#ifndef Adobe360ApplicationPropertiesHeader
#define Adobe360ApplicationPropertiesHeader

#ifndef DMALIB

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@class Adobe360Message;

extern NSString *const Adobe360ApplicationPropertyURLScheme;
extern NSString *const Adobe360ApplicationPropertyAccentColor;
extern NSString *const Adobe360ApplicationPropertyAccentContrastColor;
extern NSString *const Adobe360ApplicationPropertyAppGroup;

/**
 * A data model used to contain the necessary application
 * properties needed for the 360 workflow transport layer.
 * 
 * These can be based on build time parameters you supply to
 * your project or design items like accent color.
 */
@interface Adobe360ApplicationProperties : NSObject

/**
 * Initializes the application properties object with full control over
 * the properties.
 */
- (instancetype)initWithAppName:(NSString *)appName
                      urlScheme:(NSString *)urlScheme
                    accentColor:(UIColor *)accentColor
            accentContrastColor:(UIColor *)accentContrastColor
                       appGroup:(NSString *)appGroup;

/**
 * Obtains the url scheme used for the 360 workflow.
 *
 * This url scheme must be registered in the Info.plist
 * associated with the application.
 */
@property (nonatomic, readonly, copy) NSString *urlScheme;

/**
 * The localized name of the application.
 */
@property (nonatomic, readonly, copy) NSString *applicationName;

/**
 * The accent color defining the look-and-feel of the application.
 */
@property (nonatomic, readonly, strong) UIColor *accentColor;

/**
 * The corresponding contrast to the accent color for readability.
 * If the value/brightness of the accent color is low, this color must
 * dark for readability. If the accent color is dark, this color must be
 * light.
 */
@property (nonatomic, readonly, strong) UIColor *accentContrastColor;

/**
 * The shared app group (if any) that this app has been configured for.
 *
 * For optimal transport between all of your applications, it is best to 
 * build those applications with a shared app group value and provide it here.
 */
@property (nonatomic, readonly, copy) NSString *appGroup;

/**
 * Extracts an application properties object from the supplied message. This is useful in the 
 * secondary application to get the properties of the application that sent the message.
 *
 * @param message The message from which to extract the application properties.
 * @return The embedded properties that were within the message object.
 */
+ (Adobe360ApplicationProperties *)extractApplicationPropertiesFromMessage:(Adobe360Message *)message;

@end

#endif // !DMALIB

#endif
