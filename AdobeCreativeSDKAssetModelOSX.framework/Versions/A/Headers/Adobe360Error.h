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

/**************************************************************************
 * [PRIVATE BETA] CreativeSync enables seamless multi-app workflows via
 * the included APIs. If you have any questions, please contact us at
 * https://creativesdk.zendesk.com/hc/en-us/requests/new
 *************************************************************************/

#ifndef Adobe360ErrorHeader
#define Adobe360ErrorHeader

#import <Foundation/Foundation.h>

/** The domain for 360-related errors */
extern NSString *const Adobe360ErrorDomain;

/**
 * \brief Error codes for the 360 error domain.
 */
typedef NS_ENUM (NSInteger, Adobe360ErrorCode)
{
    /**
     * \brief The manifest could not be read from local file system.
     */
    Adobe360ErrorManifestReadFailure = 0,

    /**
     * \brief The asynchronous operation was canceled by the client.
     */
    Adobe360ErrorOperationCanceled = 1,

    /**
     * \brief A path is invalid.
     */
    Adobe360ErrorInvalidPath = 2,

    /**
     * \brief The underlying message representation is invalid.
     */
    Adobe360ErrorInvalidMessageData = 3,

    /**
     * \brief A message with an unsupported format version was encountered.
     */
    Adobe360ErrorUnknownMessageFormatVersion = 4,

    /**
     * \brief The requested asset is not contained within this message.
     */
    Adobe360ErrorUnknownAssetName = 5,

    /**
     * \brief The requested asset was missing from the location referenced by this message.
     */
    Adobe360ErrorMissingAsset = 6,

    /**
     * \brief The requested asset does not have an independent location on the file system
     *
     * Use the writeAssetWithName:toPath:withError method to write the asset's data to a
     * file path of your choice.
     */
    Adobe360ErrorAssetFileDoesNotExist = 7,

    /**
     * \brief The archive file or data was invalid
     */
    Adobe360ErrorArchiveInvalid = 8,

    /**
     * \brief An error occurred while creating the archive file
     */
    Adobe360ErrorArchiveCreateFailed = 9,

    /**
     * \brief An error occurred while writing to the filesystem during an archive operation
     */
    Adobe360ErrorArchiveWriteFailed = 10,

    /**
     * \brief An error occurred while reading from the filesystem during an archive operation
     */
    Adobe360ErrorArchiveReadFailed = 11,
    
    /**
     * \brief An out-of-memory error occurred while preparing and sending the message.
     */
    Adobe360ErrorOutOfMemory = 12,
    
    /**
     * \brief The error when server fails to return any action registry data.
     */
    Adobe360ErrorActionRegistryDataEmpty = 13,
    
    /**
     * \brief Unable to copy one or more components referenced from an AdobeDCXElement asset
     */
    Adobe360ErrorIncompleteElement = 14,
    
    /**
     * \brief An Adobe360Asset has a data property that references an unsupported type
     */
    Adobe360ErrorUnsupportedAssetDataType =15,
    
    /**
     * \brief The request Adobe360Asset does not have the requested representation
     */
    Adobe360ErrorIncorrectAssetDataType = 16,
    
    /**
     * \brief The named input or output was an array where a scalar value was expected, or vice versa
     */
    Adobe360ErrorScalarVectorMismatch  = 17,
    
};

#endif
