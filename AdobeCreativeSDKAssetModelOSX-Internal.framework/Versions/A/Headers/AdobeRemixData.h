/*************************************************************************
*
* ADOBE CONFIDENTIAL
* ___________________
*
*  Copyright 2013 Adobe Systems Incorporated
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

#ifndef AdobeRemixDataHeader
#define AdobeRemixDataHeader

#import <Foundation/Foundation.h>

// License Types

// http://creativecommons.org/licenses/by/4.0/
extern NSString *const AdobeRemixLicenseAttribution;

// http://creativecommons.org/licenses/by-sa/4.0/
extern NSString *const AdobeRemixLicenseShareAlike;

// http://creativecommons.org/licenses/by-nd/4.0/
extern NSString *const AdobeRemixLicenseNoDerivatives;

// http://creativecommons.org/licenses/by-nc/4.0/
extern NSString *const AdobeRemixLicenseNonCommercial;

// http://creativecommons.org/licenses/by-nc-sa/4.0/
extern NSString *const AdobeRemixLicenseNonCommercialShareAlike;

// http://creativecommons.org/licenses/by-nc-nd/4.0/
extern NSString *const AdobeRemixLicenseNonCommercialNoDerivatives;

@interface AdobeRemixData : NSObject

-(instancetype) initWithOriginURL:(NSString*)originURL manageUIURL:(NSString*)manageUIURL
licenseType:(NSString *)licenseType attributionURL:(NSString *)attributionURL
attributionName:(NSString *)attributionName;

@property (nonatomic, readwrite) NSString *originURL;
@property (nonatomic, readwrite) NSString *manageUIURL;

@property (nonatomic, readwrite) NSString *licenseType;
@property (nonatomic, readwrite) NSString *attributionURL;
@property (nonatomic, readwrite) NSString *attributionName;

@end

#endif
