//
//  Helper.h
//  XDXCodeTranslator
//
//  Created by crogoz on 19/05/16.
//  Copyright © 2016 crogoz. All rights reserved.
//

#ifndef Helper_h
#define Helper_h
#include <CommonCrypto/CommonDigest.h>
#include "Constants.h"

@interface Helper : NSObject {


}

+ (void) writeToFile:(NSDictionary*)xmlDictionary file:(NSString*) file computeSha:(int)sha
                hash:(NSMutableDictionary *) hashArtboards;
+ (NSString *) getProjHomePath;
+ (id) deepCopy:(id) object;
+ (void) createXdFile:(NSString *) xdPath;
+ (NSString *)findFile:(NSString *)name inPath:(NSString *) initPath;
+ (void) unzipXD:(NSString *)path atPath:(NSString*) unzipped_xd;
+ (NSMutableArray *) findAllFiles: (NSString *)name inPath:(NSString *) initPath;

@end

#endif /* Helper_h */
