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

#ifndef AdobeCommunityProtectedHeader
#define AdobeCommunityProtectedHeader

@class AdobeCloud;

@interface AdobeCommunity (Protected)

- (instancetype)initWithCommunityID:(NSString *)communityID
cloud:(AdobeCloud *)cloud;

/**
* Get assets in a community objects asynchronously.
*
* @param priority          The priority of the request.
* @param categoryClass     The class type to be returned. The class must be (or extend) AdobeCommunityCategory.
*                          Pass nil to specify AdobeCommunityCategory.
* @param successBlock      Returns an array of AdobeCommunityCategories.
* @param errorBlock        Optionally be notified of an error.
*/
- (void)categoriesWithPriority:(NSOperationQueuePriority)priority
class:(Class)categoryClass
successBlock:(void (^)(NSArray *))successBlock
errorBlock:(void (^)(NSError *))errorBlock;

@end

#endif
