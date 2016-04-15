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
#define TEST2_PATH @"Test2LabelsInAgcGenerator.json"
#define TESTDROP_PATH @"TestDropFile.json"
#define TESTIL_PATH    @"TestImageLabels.json"
#define TESTMUL_PATH    @"TestMultiple.json"

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
#define ISIMAGE     @"image"
#define WIDTH       @"width"
#define HEIGHT      @"height"
#define NAME        @"name"
#define XMLRESOURCES   @"<resources>"
#define XMLRESOURCESF  @"</resources>"
#define XMLHEADER   @"<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?><document type=\"com.apple.InterfaceBuilder3.CocoaTouch.Storyboard.XIB\" version=\"3.0\" toolsVersion=\"9532\" systemVersion=\"15E65\" targetRuntime=\"iOS.CocoaTouch\" propertyAccessControl=\"none\" useAutolayout=\"YES\" useTraitCollections=\"YES\" initialViewController=\"BYZ-38-t0r\"><dependencies><deployment identifier=\"iOS\"/><plugIn identifier=\"com.apple.InterfaceBuilder.IBCocoaTouchPlugin\" version=\"9530\"/></dependencies><scenes><!--View Controller--><scene sceneID=\"tne-QT-ifu\"><objects><viewController id=\"BYZ-38-t0r\" customClass=\"ViewController\" sceneMemberID=\"viewController\"><layoutGuides><viewControllerLayoutGuide type=\"top\" id=\"y3c-jy-aDJ\"/><viewControllerLayoutGuide type=\"bottom\" id=\"wfy-db-euE\"/></layoutGuides>"
#define XMLFOOTER   @"</viewController><placeholder placeholderIdentifier=\"IBFirstResponder\" id=\"tYr-Cr-j24\" userLabel=\"First Responder\" sceneMemberID=\"firstResponder\"/></objects><point key=\"canvasLocation\" x=\"2377\" y=\"429\"/></scene></scenes>"

#define XMLSUBVIEWS         @"\n<subviews>"
#define XMLSUBVIEWSF        @"\n</subviews>"
#define XMLDOCUMENTF   @"</document>"
#define XARTBOARD       @"x"
#define YARTBOARD       @"y"




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
    
    /* dictionary used for maintaining
     * the images resources
     **/
    NSMutableString *resourcesDict;
    
    /* dictionary that maps attributes that need to be changed
     * eg. x, y (absolute <=> relative)
     **/
    NSMutableDictionary *transformObjects;
    
    /* the start index for the current artboard */
    int startXArtboard;
    int startYArtboard;
    
    /* current scene_number == artboard_number */
    int sceneNo;
}

/* agc & xml file paths */
@property NSString *xmlPath;
@property NSString *agcPath;

+ (void)readTemplateUsingXML:(NSString *)xmlPath;

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
-(void) mergeDictionaries:(NSMutableDictionary **)objDict withDict:(NSMutableDictionary *)dictValue usingValues:(NSDictionary *)paramsValue;

/* given the rule that need to be achieved, othe dependency and the */
-(NSMutableDictionary *) computeObjects:(NSString *)rule condition:(NSArray*)cond params:(NSDictionary *)dict agcDict:agcParams;
-(NSDictionary*) processTemplateDict:(NSMutableDictionary **) templateDict agcDict:(NSDictionary *)agcDict finalDict:(NSMutableDictionary *)finalDict;
-(NSDictionary*) processWholeXmlFromAgc:(NSDictionary *)agcDict;
-(NSString *) surroundWithHeader:(NSString *) header footer:(NSString *) footer string:(NSString *)str;
-(NSMutableString *) parseToString:(NSMutableString *)str dict:(NSDictionary *)dict name:(NSString *) name;
-(NSString*) getXmlForAgcObject:(NSDictionary*)typeAgcObject;
-(void) generateXmlForTag:(NSDictionary*)agcDict;

@end


