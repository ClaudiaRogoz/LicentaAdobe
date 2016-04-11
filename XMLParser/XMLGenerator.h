//
//  XMLGenerator.h
//  XMLParser
//
//  Created by crogoz on 07/04/16.
//  Copyright © 2016 crogoz. All rights reserved.
//

#import <Foundation/Foundation.h>


#define DEF_PATH @"XMLParser/Defs.json"
#define RULES_PATH @"XMLParser/Rules.json"
#define TEST_PATH @"XMLParser/TestGenerator.json"

#define RANDOM @"$rand"
#define SCENENO @"$sceneNo"
#define SUBVIEWNO @"$subviewNo"
#define DEFAULT @"default"
#define ARTBOARDSCENE @"$artboardsceneNo"
#define RULES       @"rules"
#define ARTBOARD    @"view"
#define TOSTRING    @"toString"
#define HEADER      @"header"
#define SUBTAGS     @"subtags"
#define SUBVIEWS    @"subviews"
/**
 *  Parses AGC code; Generates XML tags for XCODE
 **/

@interface XMLGenerator : NSObject
{
    /* translation schema between agc and xml 
     * it is read from Defs.json */
    NSMutableDictionary *agcToXmlTemplate;
    
    /* translation between xml_tag_name and agc_element_name
     * it is read from Rules.json
     **/
    NSMutableDictionary *translationDict;
    //NSMutableDictionary *uniqueIds;
    
    /* current scene_number == artboard_number */
    int sceneNo;
}

/* agc & xml file paths */
@property NSString *xmlPath;
@property NSString *agcPath;


- (id)initWithError:(NSError **)error;

+ (void)readTemplate;

@end


