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

#ifndef AdobeAssetErrorHeader
#define AdobeAssetErrorHeader

/**
 * The domain for Adobe Asset errors. When NSErrors are delivered to AdobeAsset code blocks, the
 * domain property of the NSError will be set to the value of this string constant when the NSError
 * is an AdobeAsset error.
 */
extern NSString *const AdobeAssetErrorDomain;

/**
 * Error codes for the AdobeAssetErrorDomain domain.
 */
typedef NS_ENUM (NSInteger, AdobeAssetErrorCode)
{
    /**
     * A response from the server did not match its anticipated form and therefore
     * could not be processed.
     *
     * This could be caused by an unexpected HTTP response code or missing/malformed data.
     * Typically this indicates a (temporary) problem with the server or the network.
     *
     * The userInfo property of the error often contains additional information via
     * the AdobeNetworkRequestURLKey, AdobeNetworkResponseDataKey, AdobeNetworkHTTPStatusKey,
     * AdobeErrorResponseHeadersKey and NSUnderlyingErrorKey keys.
     */
    AdobeAssetErrorUnexpectedResponse = 2,

    /**
     * Both the local copy and the copy on the server have been modified. This error can happen
     * when trying to push local changes to an asset on the server.
     */
    AdobeAssetErrorConflictingChanges = 7,

    /**
     * Reading from a file has failed. This error can happen when a file fails to upload because it
     * can't be found or read.
     */
    AdobeAssetErrorFileReadFailure = 8,

    /**
     * Writing to a file has failed. This error can happen when a file fails to download because it
     * can't be written to local storage.
     */
    AdobeAssetErrorFileWriteFailure = 9,

    /**
     * An upload has failed because it would have exceeded the quota on the account
     */
    AdobeAssetErrorExceededQuota = 10,

    /**
     * An attempt was made to use an empty JSON payload.
     */
    AdobeAssetErrorMissingJSONData = 11,

    /**
     * The data returned by the server does not match the requested type. This error typically
     * occurs when requesting a rendition of a file type that does not have one, e.g., a .JSON or
     * .DMG file.
     */
    AdobeAssetErrorUnsupportedMedia = 12,

    /**
     * An attempt was made to reference a server asset using a URL that is not compatible with the
     * service on which the request was made
     */
    AdobeAssetErrorWrongEndpoint = 13,

    /**
     * The requested action or component isn't allowed by the entitlements defined for the
     * currently logged in user. This error typically occurs when attempting to access a service
     * that is not enabled by the user's account administrator.
     */
    AdobeAssetErrorNotEntitledToService = 14,

    /**
     * Unsupported feature on this endpoint.
     */
    AdobeAssetErrorUnsupportedOnEndpoint = 15
};

#endif /* ifndef AdobeAssetErrorHeader */
