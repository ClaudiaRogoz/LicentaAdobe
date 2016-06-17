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
    NSMutableDictionary *uniqueList;
    /* translation between xml_tag_name and agc_element_name
     * it is read from Rules.json
     **/
    NSMutableDictionary *translationDict;
    
    /* dictionary used for maintaining
     * the images resources
     **/
    NSMutableString *resourcesDict;
    
    /* dictionary that maps attributes that need to be changed
     * eg. x, y (absolute <=> relative)
     **/
    NSMutableDictionary *transformObjects;
    
    NSMutableArray *inheritanceColor;
    
    NSMutableArray *scaleImage;
    
    NSString *homeArtboard;
    /* the start index for the current artboard */
    int startXArtboard;
    int startYArtboard;
    int scaleNo;
    
    int widthXDArtboard;
    int heightXDArtboard;
    
    int widthXMLArtboard;
    int heightXMLArtboard;
    
    /* current scene_number == artboard_number */
    int sceneNo;
    
    /* in case of multiline labels we need to know 
     * the length f the first row and the number of rows */
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
    NSMutableDictionary *uuidViewMap;
    NSMutableDictionary *interactionsDict;
    
    bool transformInteraction;
    NSString *destinationId;
    
    bool transformSize;
    NSString *changeType;
    
    /* used for path (we obtain the size info from svg & png files,
     * the info is put into the "rect" tag ) */
    float path_x;
    float path_y;
    float path_width;
    float path_height;
    
    NSTextType textType;
    
    int xmlSceneOffset;

}

/* agc & xml file paths */
@property NSString *xmlPath;
@property NSString *outXmlPath;
@property NSString *xdPath;
@property NSString *agcPath;

+ (void)readTemplateUsingXML:(NSString *)xdPath writeTo:(NSString*)outXmlPath;
+(NSString *) generateXmlForTag:(NSDictionary*)agcDict xdPath:(NSString *)xdPath xmlPath:(NSString *)xmlPath;

- (id)initWithError:(NSError **)error;

/* init translations dictionaries */
- (void)initializeWithDefs:(NSDictionary*)defDict rules:(NSDictionary*)ruleDict;


- (NSString *) computeValue:(NSString *)initValue forDict:(NSDictionary *)agcDict;

/* splits the variable Name depending on $ and hierarchy */
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
-(NSDictionary*) processTemplateDict:(NSMutableDictionary **) templateDict agcDict:(NSDictionary *)agcDict
                           finalDict:(NSMutableDictionary *)finalDict ofType:(NSString *) type;
-(NSDictionary*) processWholeXmlFromAgc:(NSDictionary *)agcDict;
-(NSString *) surroundWithHeader:(NSString *) header footer:(NSString *) footer string:(NSString *)str;
-(NSMutableString *) parseToString:(NSMutableString *)str dict:(NSDictionary *)dict name:(NSString *) name;
-(NSString*) getXmlForAgcObject:(NSDictionary*)typeAgcObject;


@end


