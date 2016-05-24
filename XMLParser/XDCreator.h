//
//  XDCreator.h
//  XDXCodeTranslator
//
//  Created by crogoz on 19/05/16.
//  Copyright © 2016 crogoz. All rights reserved.
//


#ifndef XDCreator_h
#define XDCreator_h
#import <Foundation/Foundation.h>
#include "XDCreator.h"
#include "Constants.h"

@interface XDCreator : NSObject {

    NSString *docId;
    NSString *instId;

    NSString *artboardNumber;
}

+ (void) createResourcesContent:(NSMutableDictionary *) artboards xdPath:(NSString *) xdPath;
+ (void) createArtworkContent:(NSMutableDictionary *) artboard artboardNo:(int) artNo xdPath:(NSString *) xdPath;
+ (void) createInteractionContent:(NSMutableDictionary *) interactions xdPath:(NSString *) xdPath;
+ (void) createMimetype:(NSString *) xdPath;
+ (NSString *) createStorage:(NSArray *) list usingXDPath:(NSString *)xdPath;
+ (void) createManifest:(NSMutableDictionary *) dict xdPath:(NSString *) xdPath;
+ (void) releaseStorage:(NSString *) xdPath;

@property NSString *xdPath;


@end



#endif /* XDCreator_h */
