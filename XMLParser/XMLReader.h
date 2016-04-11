//
//  XMLReader.h
//  XMLParser
//
//  Created by crogoz on 05/03/16.
//  Copyright © 2016 crogoz. All rights reserved.
//


#import <Foundation/Foundation.h>
#define EPS 3 // just an epsilon value for pointSize calc

/* constants used for iphone6 artboards 
 * TODO: update for each artboard
 */
#define OFFSETBOARD 400
#define WIDTHIPH6 375
#define HEIGHTIPH6 667
#define SPARKLERCLIPBOARD   @"com.adobe.sparkler.design"
#define ARTBOARDXML         @"artboardFromXml.agc"

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
     * rules needed for agc2xml export;
     * using these rules we obtain the type of the agc element
     **/
    NSMutableDictionary *exportAgc;
    
    /**
     * offsets of tags in the xml file; needed for sync
     **/
    NSMutableDictionary *offsetXmlFile;
    
    /**
     *  which objects to monitor;
     *  used for sync
     **/
    NSMutableDictionary *objectOffset;
    
    
    /**
     *  temp variable used for textField/label; 
     * we have to propagate the text name for lower tags
     * TODO: integrate in attributes
     **/
    NSString *tempText;
    
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


/**
 *  sync algorithm; monitors a file given as parameter
 *  PARAMS:
 *      path:   the path for the xd file
 **/
- (void) monitorXDFile:(NSString*) path;

/**
 *  compares 2 Artboards;
 *  returns $diff (as a dictionary) between the old dictioanry and the new dictionary 
 *  PARAMS:
 *      first: old dictionary
 *      second: new dictionary
 *      jsonArtboards: template dictioanry
 *      offsetGroupDict:   offset dictionary
 **/
- (NSMutableDictionary*) compare2Artboards:(NSArray *) first dict2:(NSArray *) second artboard_info:(NSMutableDictionary *)jsonArtboards offsetGroup:(NSMutableDictionary *)offsetGroupDict numberGroup:(NSNumber *) nr;


/**
 *  checks whether 2 dictionaries are equal; the difference is given as a 
 * dictionary in `trList` variable
 **/
- (bool) checkAreEqual:(NSDictionary *)prev prevDict:(NSDictionary *)newD attr:(NSDictionary*)currAttr outList:(NSMutableDictionary**)trList equal:(BOOL) eq json_info:(NSDictionary *) jsonInfo;


/**
 *  updates the XML file with the modified values
 *  used for sync
 *  PARAMS:
 *      tags: dictionary with variables and their equivalent values
 *      tagNo: the number of the current scene
 *      offset_scene: the updated offsets after the modifications
 **/
- (void) updateXMLfile:(NSDictionary *)tags tagNo:(NSNumber *)n offsetScene:(NSNumber **) offset_scene;

/**
 *  merges an xml tag with it's subtags; 
 *  used for sync
 **/
- (NSString *) appendModifiedString:(NSMutableDictionary *)dict minTagOffset:(NSNumber **)tagOffset;

@end
