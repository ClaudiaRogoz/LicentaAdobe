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

/* uses "convert" program from ImageMagick to convert a svg to a png*/
+ (NSString *) convertSvgToPng:(NSString *) svgName withFill:(NSString *) hexColor strokeColor:(NSString *) stroke strokeWidth:(int )strokeWidth opacity:(float) opacity;

/* uses "convert" program from ImageMagick to convert a svg line to a png*/
+ (NSString *) convertSvgLineToPng:(NSString *) svgName withFill:(NSString *) hexColor;

/* returns the sha value of the string given as parameter */
+ (NSString*) computeSha1:(NSString*)input;

/* splits a temporary variable (variable strating with "$") using the dot separator */
+ (NSArray *) splitVariable:(NSString*) varName;

/* splits a variable using a delimitator given as parameter */
+ (NSArray *)splitVariable:(NSString *)key delimitator:(NSString *) variable;

/* splits a string using the dot separator */
+ (NSArray *)splitVariableForDot:(NSString *)varName;

/* returns an array of substrings (x1, x2, ..., xn) within the string x1.x2. ... .xn */
+ (NSArray *) getArrayProperties:(NSString *) property;

/* returns the value corresponding to the dictionary "dict" using the "key path" described by "properties"*/
+ (id) getValueForProperties:(NSArray *) properties inDict:(NSMutableDictionary *)dict;

/* returns the offsets of the "substring" in "string" */
+ (id) getAllOccurencesOf:(NSString*) substring in:(NSString *) string;

/* returns the first offset of the "substring" in "string" */
+ (id) getLastOccurencesOf:(NSString *)substring in:(NSString *)string fromOffset:(unsigned long) offset;

/* checks whether the given path already exists */
+ (BOOL) fileExists:(NSString *) pathForFile;

/* returns the name from the "svgName" with the ".png" path extension */
+ (NSString *) transformToPngFileName:(NSString *) svgName;

@end

#endif /* Helper_h */
