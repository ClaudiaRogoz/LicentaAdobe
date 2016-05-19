/******************************************************************************
*
* ADOBE CONFIDENTIAL
* ___________________
*
* Copyright 2014 Adobe Systems Incorporated
* All Rights Reserved.
*
* NOTICE:  All information contained herein is, and remains the property of
* Adobe Systems Incorporated and its suppliers, if any. The intellectual and
* technical concepts contained herein are proprietary to Adobe Systems
* Incorporated and its suppliers and are protected by trade secret or
* copyright law. Dissemination of this information or reproduction of this
* material is strictly forbidden unless prior written permission is obtained
* from Adobe Systems Incorporated.
******************************************************************************/

#ifndef AdobeAuthBehanceLinkingHeader
#define AdobeAuthBehanceLinkingHeader

#ifndef DMALIB

#import <UIKit/UIKit.h>

typedef void (^LinkingSuccessBlock)  (void);
typedef void (^LinkingErrorBlock)    (NSError *error);
typedef void (^LinkingDismissBlock)  (NSError *error);


@interface AdobeAuthBehanceLinkingNavigationController : UINavigationController

@property (nonatomic, strong) NSURL *linkingUIURL;
@property (nonatomic, strong) UIViewController *hostingViewController;

@property (nonatomic, copy) LinkingSuccessBlock successBlock;
@property (nonatomic, copy) LinkingErrorBlock errorBlock;
@property (nonatomic, copy) LinkingDismissBlock dismissBlock;

@end

#endif // !DMALIB

#endif
