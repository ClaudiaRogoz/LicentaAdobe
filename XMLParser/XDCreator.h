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


/* prepares the storage & computes the contents needed for resources directory */
+ (void) createResourcesContent:(NSMutableDictionary *) artboards xdPath:(NSString *) xdPath;

/* prepares the storage & computes the contents needed for artwork directory */
+ (void) createArtworkContent:(NSMutableDictionary *) artboard artboardNo:(int) artNo xdPath:(NSString *) xdPath;

/* prepares the storage & computes the contents needed for interactions directory */
+ (void) createInteractionContent:(NSMutableDictionary *) interactions xdPath:(NSString *) xdPath;

/* prepares the storage & computes the contents needed for mimetype directory */
+ (void) createMimetype:(NSString *) xdPath;

/* prepares the storage & computes the contents needed for a new Xd app */
+ (NSString *) createStorage:(NSArray *) list usingXDPath:(NSString *)xdPath;

/* prepares the storage & computes the contents needed for manifest */
+ (void) createManifest:(NSMutableDictionary *) dict xdPath:(NSString *) xdPath;

/* "destructor" for storage */
+ (void) releaseStorage:(NSString *) xdPath;

/* writes a dictionary to a json/agc file*/
+ (void) writeData:(NSMutableDictionary *) dict toPath:(NSString *) path;


@property NSString *xdPath;


@end



#endif /* XDCreator_h */
