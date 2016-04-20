//
//  XMLReader.h
//  XMLParser
//
//  Created by crogoz on 05/03/16.
//  Copyright © 2016 crogoz. All rights reserved.
//


#import <Foundation/Foundation.h>

#import "Constants.h"


@import AppKit;


@interface XMLReader : NSObject <NSXMLParserDelegate>
{
    NSMutableArray *dictionaryStack;
    
    
    /** stack representing inheritance tree with regards to tags
     * eg. <label attr = ....>
     *          <color attr=.../>
     *      </label>
     * label is the parent of color
     * needed for setting the right attributes
     **/
    NSMutableArray *inheritanceStack;
    
    /**
     * used when an object in xcode is represented in xd
     * as two or more objects; 
     * eg. A label/textfield with background color is represented in
     * xd as a textfield & rectangle
     **/
    NSMutableArray *toInsertObjects;
    
    /* gathers the content for the current element 
     * see: https://developer.apple.com/library/ios/documentation/Cocoa/Conceptual/XMLParsing/Articles/HandlingElements.html
     **/
    NSMutableString *textInProgress;
    
    /**
     *  dictionary representing the correlation between xml and agc
     **/
    NSMutableDictionary *xml2agcDictionary;
    
    /**
     * ditionary with correlations between variables & defaultValues
     */
    NSMutableDictionary *defaultValues;
    
    
    //NSMutableDictionary *invertedDictionary;
    
    /**
     * json template for agc elements written as a mutableDictionary
     **/
    NSMutableDictionary *attributes;
    
    /**
     * offsets of tags in the xml file; needed for sync
     **/
    NSMutableDictionary *offsetXmlFile;
 
    /**
     *  which objects to monitor;
     *  used for sync
     **/
    NSMutableDictionary *objectOffset;
    
    /* width/height of xcode artboards and xd artboards */
    int widthXMLArtboard;
    int heightXMLArtboard;
    int widthAgcArtboard;
    int heightAgcArtboard;
    
    /* number of scenes == number of artboards */
    int sceneNo;
    NSData *xmlData;
    unsigned long xmlOffset;
    
    BOOL insertedRoot;
    int counterArtboards;
    int counterCh;
    
    
}

/* where we find all external resources: eg. images */
@property NSString *resourcesPath;
@property NSString *xdPath;
@property NSString *xmlPath;

/* -----------------------PUBLIC method------------------------*/

/* used for xml2agc parsing */
+ (NSDictionary *)dictionaryForXMLData:(NSData *)data resources:(NSString*)resourcesDir xdPath:(NSString *)path outFile:(NSString *)out_file error:(NSError **)errorPointer;

/* -----------------------PRIVATE methods----------------------*/

/* splits a single agc file  into several agc files, each with one artboard; 
 * needed for sync
 * PARAMS:
 *      dictionary: the initial dictionary that needs to be split
 **/
- (NSMutableArray *)splitArtboards:(NSDictionary *)dictionary;

/**
 * writes an xmlDictionary to agcFile
 * PARAMS:
 *      xmlDictionary:  the dictioanry that needs to be written
 *      file:           the agc file path
 **/
- (void) writeToFile:(NSDictionary*)xmlDictionary file:(NSString*) file;


@end
