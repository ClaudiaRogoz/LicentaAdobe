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

#ifndef AdobeDCXCompositeBranchDepHeader
#define AdobeDCXCompositeBranchDepHeader

#import <AdobeCreativeSDKAssetModelOSX-Internal/AdobeDCXCompositeBranch.h>

@interface AdobeDCXCompositeBranch ()

/** The immutable root node of the underlying manifest. */
@property (nonatomic, readonly) AdobeDCXManifestNode *rootNode;

/**
* brief Returns the metadata for an element, creating it if necessary.
*/
- (AdobeDCXMetadata *)metadataForElement:(AdobeDCXManifestNode *)elementNode __deprecated;

/**
* brief Returns the list of components for the specified child node.
*
* param node  The node for which to return the list of components of. Can be nil in which case the
*              list of components of the root-level of the manifest will be returned.
*
* return      An NSArray of AdobeDCXComponent objects which can be empty if the provided node doesn't
*              have any components.
*/
- (NSArray *)getComponentsOf:(AdobeDCXManifestNode *)node __deprecated;

/**
* brief Locates the given component in the manifest and returns the parent AdobeDCXManifestNode.
* Returns nil if not found.
*
* param component The component to return the parent for.
*
* return The AdobeDCXManifestNode that is the parent of component. Returns nil if not found.
*/
- (AdobeDCXManifestNode *)findParentOfComponent:(AdobeDCXComponent *)component __deprecated;

/**
* brief Get the list of child nodes for the specified node.
*
* param node The node for which to return the list of child nodes.  Can be nil in which case the
* list of children of the root-level of the manifest will be returned.
*
* return An NSArray of AdobeDCXManifestNode objects which can be empty if the provided node doesn't
* have any children.
*/
- (NSArray *)getChildrenOf:(AdobeDCXManifestNode *)node __deprecated;

/**
* brief Returns the child node with the given id or nil if it node doesn't exist.
*
* param componentId The id of the requested child node.
*
* return The child node with the given id or nil if it doesn't exist.
*/
- (AdobeDCXManifestNode *)getChildWithId:(NSString *)nodeId __deprecated;

/**
* brief Returns the child node with the given absolute path or nil.
*
* param absPath The absolute path of the requested child node.
*
* return The child node with the given absolute path or nil.
*/
- (AdobeDCXManifestNode *)getChildWithAbsolutePath:(NSString *)absPath __deprecated;

/**
* brief Locates the given child node in the manifest and returns its parent the parent AdobeDCXManifestNode.
* Returns nil if not found.
*
* param component The component to return the parent for.
*
* return The AdobeDCXManifestNode that is the parent of child. Returns nil if not found.
*/
- (AdobeDCXManifestNode *)findParentOfChild:(AdobeDCXManifestNode *)node foundIndex:(NSUInteger *)index __deprecated;

@end

#endif
