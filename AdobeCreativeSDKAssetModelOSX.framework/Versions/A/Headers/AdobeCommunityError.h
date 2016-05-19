/*************************************************************************
 *
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
 * suppliers and are protected by trade secret or copyright law.
 * Dissemination of this information or reproduction of this material
 * is strictly forbidden unless prior written permission is obtained
 * from Adobe Systems Incorporated.
 **************************************************************************/

#ifndef AdobeCommunityErrorHeader
#define AdobeCommunityErrorHeader

/** The domain for Adobe Community errors.  When NSErrors are delivered to AdobeCommunity code blocks,
 *  the domain property of the NSError will be set to the value of this string constant when
 *  the NSError is an AdobeCommunity error.
 */
extern NSString *const AdobeCommunityErrorDomain;

/**
 * Error codes for the AdobePhotoErrorDomain domain.
 */
typedef NS_ENUM (NSInteger, AdobeCommunityErrorCode)
{
    /**
     * A response from the server did not match its anticipated form and therefore
     * could not be processed.
     *
     * This could be caused by an unexpected HTTP response code or missing/malformed data.
     * Typically this indicates a (temporary) problem with the server or the network.
     *
     * The userInfo property of the error often contains additional information via
     * the AdobeNetworkRequestURLKey, AdobeNetworkResponseDataKey, AdobeNetworkHTTPStatusKey, AdobeErrorResponseHeadersKey
     * and NSUnderlyingErrorKey keys.
     */
    AdobeCommunityErrorUnexpectedResponse = 2,

    /**
     * Reading from a file has failed. This error can happen when a file fails to upload because it
     * can't be found or read.
     */
    AdobeCommunityErrorFileReadFailure = 8,

    /**
     * Writing to a file has failed. This error can happen when a file fails to download because it
     * can't be written to local storage.
     */
    AdobeCommunityErrorFileWriteFailure = 9,

    /**
     * An attempt was made to use an empty JSON payload.
     */
    AdobeCommunityErrorMissingJSONData = 11,

    /**
     * The requested action or component isn't allowed by the entitlements defined for the
     * currently logged in user. This error typically occurs when attempting to access a service
     * that is not enabled by the user's account administrator.
     */
    AdobeCommunityErrorNotEntitledToService = 14,
    
    /**
     * The requested action or component isn't allowed by the entitlements defined for the
     * currently logged in user. This error typically occurs when attempting to access a service
     * that is not enabled by the user's account administrator.
     */
    AdobeCommunityErrorInvalidPublicationRecord = 15
};

#endif
