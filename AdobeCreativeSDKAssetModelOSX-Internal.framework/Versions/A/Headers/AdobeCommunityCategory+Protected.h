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
******************************************************************************/

#ifndef AdobeCommunityCategoryProtectedHeader
#define AdobeCommunityCategoryProtectedHeader

@class AdobeCloud;

@interface AdobeCommunityCategory (Protected)

- (instancetype)initWithData:(NSDictionary *)data
baseURL:(NSURL *)url
cloud:(AdobeCloud *)cloud;

- (void)updateWithData:(NSDictionary *)data;

+ (void)categoriesForCommunityID:(NSString *)communityID
cloud:(AdobeCloud *)cloud
priority:(NSOperationQueuePriority)priority
successBlock:(void (^)(NSArray *))successBlock
errorBlock:(void (^)(NSError *))errorBlock;

@end

#endif
