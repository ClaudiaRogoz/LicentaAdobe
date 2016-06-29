//
//  XMLGenerator.h
//  XMLParser
//
//  Created by crogoz on 07/04/16.
//  Copyright © 2016 crogoz. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "Constants.h"
#include "Helper.h"


/**
 *  Parses AGC code; Generates XML tags for XCODE
 **/

typedef enum NSTextType : NSUInteger {
    kareaText,
    kpositionedText
} NSTextType;


@interface XD2XCode : NSObject
{
    /* translation schema between agc and xml
     * it is read from Defs.json */
    NSMutableDictionary *agcToXmlTemplate;
    
    /**
     * dictionary of id's used
     **/
    NSMutableDictionary *uniqueList;
    
    /* translation between xml_tag_name and agc_element_name
     * it is read from Rules.json
     **/
    NSMutableDictionary *translationDict;
    
    /* dictionary used for maintaining
     * the images resources (full path for each image)
     **/
    NSMutableString *resourcesDict;
    
    /* dictionary that maps attributes that need to be changed
     * eg. x, y (absolute <=> relative)
     **/
    NSMutableDictionary *transformObjects;
    
    /**
     * entry scene (id)
     **/
    NSString *homeArtboard;
    
    /* the start index for the current artboard */
    int startXArtboard;
    int startYArtboard;
    
    /* width and height of the scenes */
    int widthXDArtboard;
    int heightXDArtboard;
    
    int widthXMLArtboard;
    int heightXMLArtboard;
    
    /* current scene_number == artboard_number */
    int sceneNo;
    
    /* in case of multiline labels we need to know 
     * the length of the first row and the number of rows */
    int textLen;
    int textLines;
    
    float xOffsetText;
    float yOffsetText;
    
    /* needed for setting the initial storyboard */
    BOOL computed;
    
    /* for performance statistics */
    int noOfElements;
    
    /* used for interactions */
    NSMutableDictionary *uuidMap;
    
    /* dictionary that contains all the id's that need to be replaced*/
    NSMutableDictionary *uuidViewMap;
    
    /* entry = <source_id, destination_id> ; used for processing segues; */
    NSMutableDictionary *interactionsDict;
    
    /* if transformInteraction is true => from the last computed asset starts a segue,
     * the last asset needs to be translated into a button asset */
    bool transformInteraction;
    
    /* destination id for the current segue*/
    NSString *destinationId;
    
    /* when an asset's type is changed (into a button)
     * the size & offsets need to remain the same (no translation needed) */
    bool transformSize;
    
    /* used for assets whose type is temporary (starts with "$")*/
    NSString *changeType;
    
    /* used for paths (we obtain the size info from svg & png files,
     * the info is put into the "rect" tag ) */
    float path_x;
    float path_y;
    float path_width;
    float path_height;
    
    /* computes the offset of the scenes */
    int xmlSceneOffset;
    long sceneOffset;

}

/* XCode directory path*/
@property NSString *xmlPath;

/* Main.Storyboard's Full Path */
@property NSString *outXmlPath;

/* the path for the xd file */
@property NSString *xdPath;


/* entry point for the translation between XCode and XD */
+ (void)readTemplateUsingXML:(NSString *)xdPath writeTo:(NSString*)outXmlPath;

/* returns the xml representation for an agc dictionary given as parameter; the scene number must be specified */
+(NSString *) generateXmlForTag:(NSDictionary*)agcDict xdPath:(NSString *)xdPath xmlPath:(NSString *)xmlPath sceneNo:(int) currentScene;

- (id)initWithError:(NSError **)error;

/* init translations dictionaries */
- (void)initializeWithDefs:(NSDictionary*)defDict rules:(NSDictionary*)ruleDict;

/* transforms the value given as parameter "initValue" based on some special functions: GETMAX, RANDOM, ... */
- (NSString *) computeValue:(NSString *)initValue forDict:(NSDictionary *)agcDict;

/* splits the variable Name depending on $ and the hierarchy it represents */
- (NSArray *) splitVariable:(NSString*) varName;

/* converts a dictionary to xml file */
- (NSString *) toString:(NSMutableDictionary *)dict name:(NSString*)varName isLeaf:(BOOL)leaf;

/* merges a dictionary with the default dictionary */
- (void) mergeDefaultValues:(NSDictionary*)defaultDict withDict:(NSMutableDictionary **) initDict usingDict:(NSDictionary*) paramDict;

/* merges multiple dictionaries */
-(void) mergeDictionaries:(NSMutableDictionary **)objDict withDict:(NSMutableDictionary *)dictValue
              usingValues:(NSDictionary *)paramsValue type:(NSString *)type;

/* given the rule that need to be achieved, othe dependency and the */
-(NSMutableDictionary *) computeObjects:(NSString *)rule condition:(NSArray*)cond params:(NSDictionary *)dict
                                agcDict:agcParams type:(NSString *)type;

/* processes an agc dictionary based on the translation schema */
-(NSDictionary*) processTemplateDict:(NSMutableDictionary **) templateDict agcDict:(NSDictionary *)agcDict
                           finalDict:(NSMutableDictionary *)finalDict ofType:(NSString *) type;

/* uses the translations schemas to process the current dictionary */
-(NSDictionary*) processWholeXmlFromAgc:(NSDictionary *)agcDict;

/* adds a header and a footer for a given string*/
-(NSString *) surroundWithHeader:(NSString *) header footer:(NSString *) footer string:(NSString *)str;

/* transforms a dictionary object into an xml representation */
-(NSMutableString *) parseToString:(NSMutableString *)str dict:(NSDictionary *)dict name:(NSString *) name;

/* returns the xml representation for the XD project */
-(NSString*) getXmlForAgcObject:(NSDictionary*)typeAgcObject;


@end


