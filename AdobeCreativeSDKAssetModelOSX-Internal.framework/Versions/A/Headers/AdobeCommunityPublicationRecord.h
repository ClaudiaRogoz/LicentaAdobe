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

#ifndef AdobeCommunityPublicationRecordHeader
#define AdobeCommunityPublicationRecordHeader

#import <Foundation/Foundation.h>

#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobePublicationRecordProtocol.h>

@interface AdobeCommunityPublicationRecord : NSObject <AdobePublicationRecordProtocol>

-(instancetype) initWithTitle:(NSString*)title;
-(instancetype) initWithCommunityId:(NSString*)communityId andTitle:(NSString*)title;

/** The community ID where the asset should get published. Is required for a first time
* publish operation. Optional/gets ignored for an update. */
@property (nonatomic, readwrite) NSString *communityId;

/** Specifies the path to a local file that should be used as the artwork for the
* published asset. If the copy param is false then the publish operation takes
* ownership of the file. If not it makes a copy.
* note Calling this method will override any assignment previously made to the artworkComponentId property.
*/
-(void)setArtworkFile:(NSString*)artworkFilePath copy:(BOOL)copy contentType:(NSString*)type;

/** Specifies a dcx component to be used as the artwork. This is only valid when publishing a composite.
* note Setting this property will override any artwork file previously set with the setArtworkFile: method.*/
@property (nonatomic, readwrite) NSString *artworkComponentId;

/** The title of the published asset. */
@property (nonatomic, readwrite) NSString *title;

/** Read-only: The resource path of the existing artwork file. */
@property (nonatomic, readonly) NSString *artwork;

/** Read-only: The resource verison of the existing artwork file. */
@property (nonatomic, readonly) NSString *artworkVersion;

/** Optional: An alias for the published asset. */
@property (nonatomic, readwrite) NSString *alias;

/** Optional: An NSArray of NSStrings which represent the tags for the published asset. */
@property (nonatomic, readwrite, copy) NSArray *tags;

/** Optional: A textual description of the published asset. */
@property (nonatomic, readwrite) NSString *desc;

/** Optional: The id of a category defined in the community. */
@property (nonatomic, readwrite) NSString *categoryId;

/** Optional: An NSArray of NSStrings which represent the subcategories of the asset. */
@property (nonatomic, readwrite, copy) NSArray *subCategoryIds;

/** Optional: An NSArray of NSStrings which represent the ids of the creators of the asset. */
@property (nonatomic, readwrite, copy) NSArray *creatorIds;

/** Whether the asset is discoverable. Default: NO */
@property (nonatomic, readwrite) BOOL discoverable;

/** Optional: An object containing custom metadata. Must be of a type that can be put into an NSDictionary. */
@property (nonatomic, readwrite, copy) id custom;

@end

#endif
