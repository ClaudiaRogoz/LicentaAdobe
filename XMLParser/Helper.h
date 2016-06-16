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

/* writes a dictionary to an .agc/.json file; also, if sha is True, 
 * it also computes the sha value of the file*/
+ (void) writeToFile:(NSDictionary*)xmlDictionary file:(NSString*) file computeSha:(int)sha
                hash:(NSMutableDictionary *) hashArtboards;


/* obtains the root directory of the current app*/
+ (NSString *) getProjHomePath;

/* creates a deepcopy of an element given as parameter*/
+ (id) deepCopy:(id) object;

/* creates an XD file at the path given as parameter;
 * creates the internal structure of the XD file (artwork/, mimetype, manifest ...)*/
+ (void) createXdFile:(NSString *) xdPath;

/* returns the absolute path of a file */
+ (NSString *)findFile:(NSString *)name inPath:(NSString *) initPath;

/* unzipps an XD file at a path given as parameter*/
+ (void) unzipXD:(NSString *)path atPath:(NSString*) unzipped_xd;

/* returns all the files in a given directory */
+ (NSMutableArray *) findAllFiles: (NSString *)name inPath:(NSString *) initPath;

+ (NSString *) convertSvgToPng:(NSString *) svgName withFill:(NSString *) hexColor strokeColor:(NSString *) stroke strokeWidth:(int )strokeWidth opacity:(float) opacity;
+ (NSString *) convertSvgLineToPng:(NSString *) svgName withFill:(NSString *) hexColor;
+ (NSString*) computeSha1:(NSString*)input;
+ (NSArray *) splitVariable:(NSString*) varName;
+ (BOOL) checkPathExists:(NSString *) absolutePath;

+ (NSArray *)splitVariable:(NSString *)key delimitator:(NSString *) variable;
+ (NSArray *)splitVariableForDot:(NSString *)varName;
+ (NSArray *) getArrayProperties:(NSString *) property;

+ (id) getValueForProperties:(NSArray *) properties inDict:(NSMutableDictionary *)dict;
+ (id) getAllOccurencesOf:(NSString*) substring in:(NSString *) string;
+ (id) getLastOccurencesOf:(NSString *)substring in:(NSString *)string fromOffset:(unsigned long) offset;

@end

#endif /* Helper_h */
