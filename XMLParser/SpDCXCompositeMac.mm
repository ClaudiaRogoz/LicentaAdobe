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
#import "SpDCXCompositeMac.h"

// DCX Nodes and node paths
static NSString* const kArtworkNode = @"artwork";
static NSString* const kArtworkPath = @"/artwork";
static NSString* const kInteractionsNode = @"interactions";
static NSString* const kInteractionsPath = @"/interactions";
static NSString* const kPasteboardNode = @"pasteboard";
static NSString* const kPasteboardPath = @"/artwork/pasteboard";
static NSString* const kResourcesNode = @"resources";
static NSString* const kResourcesPath = @"/resources";
static NSString* const kAppIconName = @"appIcon";
static NSString* const kAppIconPath = @"appIcon.png";

// DCX Components
static NSString* const kAGCComponent = @"graphicContent.agc";
static NSString* const kPasteboardComponent = @"pasteboardComponent";
static NSString* const kInteractionsComponent = @"interactions.json";

// DCX Relation Constants
static NSString* const kRelPrimary = @"primary";
static NSString* const kRelRendition = @"rendition";

// Sparkler private JSON properties
static NSString* const kPropVersion = @"uxdesign#version";
static NSString* const kPropProtoVersion = @"uxdesign#prototypeVersion";
static NSString* const kPropType = @"uxdesign#type";
static NSString* const kPropSpriteData = @"uxdesign#spriteData";
static NSString* const kPropBounds = @"uxdesign#bounds";
static NSString* const kPropViewport = @"uxdesign#viewport";

// DCX path names
static NSString* const kArtboardPrefix = @"artboard-";
static NSString* const kGraphicsNode = @"graphics";

// Sparkler specific Content Types
static NSString* const kSVGOMGContentType = @"application/vnd.adobe.graphical-object-model";
static NSString* const kSparklerDCXContentType = @"application/vnd.adobe.sparkler.project+dcx";
static NSString* const kSparklerProtoContentType = @"application/vnd.adobe.uxdesign.prototype+dcx";
static NSString* const kAGCContentType = @"application/vnd.adobe.agc+dcx";
static NSString* const kInteractionsContentType = @"application/vnd.adobe.uxdesign.interactions+json";
static NSString* const kPNGContentType = @"image/png";

// Storage service constants
static NSString* const kServiceAPIKey = @"CometDesktop1";
static NSString* const kStorageServiceApplicationName = @"Adobe Comet";

@implementation SpDCXCompositeMac

- (int) addArtboardNode:(const char*) artboardId params:(struct ArtboardParams) params
{
    NSError* error = nil;
    AdobeDCXCompositeMutableBranch* current = m_composite.current;
    AdobeDCXNode* artboardNode = [self getArtboardNode: artboardId];

    if (artboardNode) {
        return -1;
    }

    AdobeDCXNode* newNode = [current appendNode:[NSString stringWithUTF8String:params.name]
                                         withId:nil
                                       withType:nil
                                       withPath:[NSString stringWithFormat:@"%@%@", kArtboardPrefix, [NSString stringWithUTF8String:artboardId]]
                                       toParent:[current getNodeWithAbsolutePath:kArtworkPath]
                                      withError:&error];
    
    if (error != nil) {
        return -1;
    }

    // Process the viewport size if viewportHeight is defined. viewportWidth is optional, as its only relevant for prototype DCX.
    if (params.viewportHeight > 0) {
        NSMutableDictionary* viewportProps = [NSMutableDictionary new];
        viewportProps[@"height"] = @(params.viewportHeight);
        if (params.viewportWidth > 0) {
            viewportProps[@"width"] = @(params.viewportWidth);
        }
        [newNode setValue:viewportProps forKey:kPropViewport];
    }

    [newNode setValue:@{@"x": @(params.x),
                        @"y": @(params.y),
                        @"width": @(params.width),
                        @"height": @(params.height)}
               forKey:kPropBounds];

    return 1;
}


- (AdobeDCXNode*) getArtboardNode: (const char*) nodePath
{
    AdobeDCXCompositeMutableBranch* current = m_composite.current;
    NSString* absoluteArtboardPath = [NSString stringWithFormat:@"%@/%@%@",
                                      kArtworkPath, kArtboardPrefix, [NSString stringWithUTF8String:nodePath]];

    return [current getNodeWithAbsolutePath:absoluteArtboardPath];
}

- (int) addArtboardComponent:(const char*) artboardId path: (const char*) filePath params:( struct ComponentParams) params
{
    NSError* error = nil;
    AdobeDCXCompositeMutableBranch* current = m_composite.current;

    AdobeDCXNode* artboardNode = [ self getArtboardNode: artboardId];
    if (!artboardNode) {
        return -1;
    }

    AdobeDCXNode* targetNode = artboardNode;
    if (params.isAGCComponent) {
        // For AGC content DCX requires us to have an (ideally self contained) subtree.
        AdobeDCXNode* agcElement = [current getNodeWithAbsolutePath:[NSString stringWithFormat:@"%@/graphics", artboardNode.absolutePath]];
        if (!agcElement) {
            agcElement = [current appendNode:kGraphicsNode
                                      withId:nil
                                    withType:nil
                                    withPath:kGraphicsNode
                                    toParent:artboardNode
                                   withError:&error];
            if (error != nil) {
                return -1;
            }
        }
        targetNode = agcElement;
    }
    
    [current addComponent:artboardNode.name
                   withId:nil
                 withType:[NSString stringWithUTF8String:params.type]
         withRelationship:[NSString stringWithUTF8String:params.rel]
                 withPath:[NSString stringWithUTF8String:params.componentPath]
                  toNode:targetNode
                 fromFile:[NSString stringWithUTF8String:filePath]
                     copy:NO
                 fromHref:nil
                withError:&error];

    if (error != nil) {
        return -1;
    }

    return 1;
}

@end
