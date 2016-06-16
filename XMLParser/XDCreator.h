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

/* prepares the storage & computes the contents needed for artwork directory 
 * returns the sha1 value of the artboard dictioonary */
+ (NSString*) createArtworkContent:(NSMutableDictionary *) artboard artboardNo:(int) artNo xdPath:(NSString *) xdPath;

/* prepares the storage & computes the contents needed for interactions directory */
+ (void) createInteractionContent:(NSMutableDictionary *) interactions xdPath:(NSString *) xdPath homeArtboard:(NSString *) homeArtboard;

/* prepares the storage & computes the contents needed for mimetype directory */
+ (void) createMimetype:(NSString *) xdPath;

/* prepares the storage & computes the contents needed for a new Xd app */
+ (NSString *) createStorage:(NSArray *) list usingXDPath:(NSString *)xdPath;

/* prepares the storage & computes the contents needed for manifest */
+ (void) createManifest:(NSMutableDictionary *) dict xdPath:(NSString *) xdPath;

/* "destructor" for storage */
+ (void) releaseStorage:(NSString *) xdPath;

/* writes a dictionary to a json/agc file; also computes SHA1 for the new content of path */
+ (NSString *) writeData:(NSMutableDictionary *) dict toPath:(NSString *) path withSha:(BOOL)sha;


@property NSString *xdPath;


@end



#endif /* XDCreator_h */
