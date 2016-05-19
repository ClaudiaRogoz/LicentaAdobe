/*************************************************************************
*
* ADOBE CONFIDENTIAL
* ___________________
*
*  Copyright 2014 Adobe Systems Incorporated
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

// Reviewed by rhorns on October 8, 2013

#ifndef AdobeDCXConstantsPrivateHeader
#define AdobeDCXConstantsPrivateHeader

#import <Foundation/Foundation.h>

/** name Manifest Keys
Keys used in a manifest.
*/
/**@{*/

/** The 'id' key */
extern NSString *const AdobeDCXIdManifestKey;
/** The 'name' key */
extern NSString *const AdobeDCXNameManifestKey;
/** The 'type' key */
extern NSString *const AdobeDCXTypeManifestKey;
/** The 'created' key */
extern NSString *const AdobeDCXCreatedManifestKey;
/** The 'modified' key */
extern NSString *const AdobeDCXModifiedManifestKey;
/** The 'state' key */
extern NSString *const AdobeDCXStateManifestKey;
/** The 'etag' key */
extern NSString *const AdobeDCXEtagManifestKey;
/** The 'path' key */
extern NSString *const AdobeDCXPathManifestKey;
/** The 'rel' key */
extern NSString *const AdobeDCXRelationshipManifestKey;
/** The 'width' key */
extern NSString *const AdobeDCXWidthManifestKey;
/** The 'height' key */
extern NSString *const AdobeDCXHeightManifestKey;
/** The 'components' collection */
extern NSString *const AdobeDCXComponentsManifestKey;
/** The 'children' collection */
extern NSString *const AdobeDCXChildrenManifestKey;
/** The '_links' collection */
extern NSString *const AdobeDCXLinksManifestKey;
/** The content length in a manifest */
extern NSString *const AdobeDCXLengthManifestKey;
/** The md5 checksum in a manifest */
extern NSString *const AdobeDCXMD5ManifestKey;
/** The version number in a manifest */
extern NSString *const AdobeDCXVersionManifestKey;

/** A place to store local data */
extern NSString *const AdobeDCXLocalDataManifestKey;
/** The version of the format of the local node */
extern NSString *const AdobeDCXLocalVersionManifestKey;
/** The local storage asset id of a component */
extern NSString *const AdobeDCXLocalStorageAssetIdMapManifestKey;
/** A place to maintain Unmanaged Components UCIDs */
extern NSString *const AdobeDCXLocalStorageUnmanagedComponentsManifestKey;
/** A mapping of component ID to source href for components requiring a server-to-server file copy */
extern NSString *const AdobeDCXComponentsPendingServerCopyManifestKey;
/** The href of the composite */
extern NSString *const AdobeDCXCompositeHrefManifestKey;
/** The etag of the manifest */
extern NSString *const AdobeDCXManifestEtagManifestKey;
/** The version of the manifest */
extern NSString *const AdobeDCXManifestVersionManifestKey;
/** The collaboration type of the composite on the server */
extern NSString *const AdobeDCXCollaborationManifestKey;
/** Is the composite read only **/
extern NSString *const AdobeDCXReadOnlyManifestKey;
/** A unique ID generated for each save of the manifest file */
extern NSString *const AdobeDCXManifestSaveIdManifestKey;
/** The version of the manifest file format in use */
extern NSString *const AdobeDCXManifestFormatVersionManifestKey;

/** The mime type of a manifest */
extern NSString *const AdobeDCXManifestType;

// ETS events
extern NSString *const AdobeDCXEventTypePush;
extern NSString *const AdobeDCXEventTypeUploadComponent;
extern NSString *const AdobeDCXEventTypeCopyComponent;
extern NSString *const AdobeDCXEventTypeComponentGetHead;
extern NSString *const AdobeDCXEventTypeUploadManifest;
extern NSString *const AdobeDCXEventTypeManifestGetHead;
extern NSString *const AdobeDCXEventTypeDeleteComposite;
extern NSString *const AdobeDCXEventTypeCreateComposite;

extern NSString *const AdobeDCXEventTypePull;
extern NSString *const AdobeDCXEventTypePullMinimal;
extern NSString *const AdobeDCXEventTypeDownloadComponents;
extern NSString *const AdobeDCXEventTypeDownloadComponent;
extern NSString *const AdobeDCXEventTypeDownloadManifest;

extern NSString *const AdobeDCXEventTypePublishComposite;
extern NSString *const AdobeDCXEventTypeCreatePublicationRecord;
extern NSString *const AdobeDCXEventTypeUpdatePublicationRecord;
extern NSString *const AdobeDCXEventTypeGetPublicationRecord;
extern NSString *const AdobeDCXEventTypeUploadPublicationArtwork;
extern NSString *const AdobeDCXEventTypeRemixComposite;

// ETS properties
extern NSString *const AdobeDCXEventPropertyComponentCountTotal;
extern NSString *const AdobeDCXEventPropertyComponentBytesTotal;
extern NSString *const AdobeDCXEventPropertyComponentCountModified;
extern NSString *const AdobeDCXEventPropertyComponentBytesModified;
extern NSString *const AdobeDCXEventPropertyComponentCountNew;
extern NSString *const AdobeDCXEventPropertyComponentBytesNew;
extern NSString *const AdobeDCXEventPropertyComponentCountUploaded;
extern NSString *const AdobeDCXEventPropertyComponentBytesUploaded;
extern NSString *const AdobeDCXEventPropertyComponentCountCopied;
extern NSString *const AdobeDCXEventPropertyComponentBytesCopied;
extern NSString *const AdobeDCXEventPropertyComponentCountDownloaded;
extern NSString *const AdobeDCXEventPropertyComponentBytesDownloaded;
extern NSString *const AdobeDCXEventPropertyComponent;
extern NSString *const AdobeDCXEventPropertyPriority;
extern NSString *const AdobeDCXEventPropertyComposite;
extern NSString *const AdobeDCXEventPropertyMediaType;
extern NSString *const AdobeDCXEventPropertyAssetId;

/**@}*/

/** name Other
*/
/**@{*/

/** The name for the manifest in a document collection */
extern NSString *const AdobeDCXManifestName;

/** Types of asset collaboration / sharing */
extern NSString *const AdobeDCXCollaborationTypePrivate;
extern NSString *const AdobeDCXCollaborationTypeSharedByUser;
extern NSString *const AdobeDCXCollaborationTypeSharedWithUser;

/**@}*/

#endif
