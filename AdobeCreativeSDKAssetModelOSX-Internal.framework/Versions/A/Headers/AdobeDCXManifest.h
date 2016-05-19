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

// Reviewed by rhorns on October 10, 2013

#ifndef AdobeDCXManifestHeader
#define AdobeDCXManifestHeader

#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeStorageResource.h>
#import <Foundation/Foundation.h>

@class AdobeDCXManifestNode;
@class AdobeDCXMutableComponent;
@class AdobeDCXMutableManifestNode;
@class AdobeStorageResourceItem;
@class AdobeDCXComponent;

/**
* class AdobeDCXManifest
* brief Represents and manages a manifest of a composite.
*/
@interface AdobeDCXManifest : NSObject <NSCopying>


/**@}*/
#pragma mark Properties
/** name Properties */
/**@{*/

/** The id of the composite described in the manifest. */
@property (nonatomic) NSString *compositeId;

/** The name of the composite described in the manifest. */
@property (nonatomic) NSString *name;

/** The mime type of the composite described in the manifest. */
@property (nonatomic) NSString *type;

/** The links of the manifest. */
@property (nonatomic) NSDictionary *links;

/** The state of the composite. */
@property (nonatomic) NSString *compositeState;

/** The etag of the manifest asset on the server. */
@property (nonatomic) NSString *etag;

/** The version of the manifest asset on the server.
* note This property is currently only set when pulling a published composite from CP. */
@property (nonatomic) NSString *version;

/** The href of the composite on the server. */
@property (nonatomic) NSString *compositeHref;

/** Is YES if the manifest has in-memory changes that haven't been committed to local storage yet. */
@property (nonatomic) BOOL isDirty;

/** Is YES if the manifest is bound to a specific composite on the server. */
@property (nonatomic, readonly) BOOL isBound;

/** The collaboration type of the composite resource on the server. */
@property (nonatomic) AdobeCollaborationType collaborationType;

/** Is YES if the composite is marked read only. */
@property (nonatomic) BOOL readOnly;

/** A unique ID that is updated whenever the writeToFile method is called
* with the generateNewSaveId parameter set to YES.
*/
@property (nonatomic, readonly) NSString *saveId;

/** Reference to the root node of the manifest */
@property (nonatomic, readonly) AdobeDCXMutableManifestNode *rootNode;

/**
* brief Returns the value of a named attribute of the node or nil if the attribute
* doesn't exist. Use this to access attributes
* that are not exposed as properties.
*
* param key The name of the attribute.
*
* return The value of the attribute.
*/
- (id)valueForKey:(NSString *)key;

/**
* brief Sets the value for the named attribute key.
*
* param value The new value of the attribute. Must not be nil.
* param key The name of the attribute.
*/
- (void)setValue:(id)value forKey:(NSString *)key;

/**
* brief Removes a named attribute from the manifest. Use this to remove attributes
* that are not exposed as separate properties.
*
* param key The name of the attribute.
*/
- (void)removeValueForKey:(NSString *)key;

@end

#endif
