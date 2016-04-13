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
#define XMLHEADER   @"<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?><document type=\"com.apple.InterfaceBuilder3.CocoaTouch.Storyboard.XIB\" version=\"3.0\" toolsVersion=\"9532\" systemVersion=\"15E65\" targetRuntime=\"iOS.CocoaTouch\" propertyAccessControl=\"none\" useAutolayout=\"YES\" useTraitCollections=\"YES\" initialViewController=\"BYZ-38-t0r\"><dependencies><deployment identifier=\"iOS\"/><plugIn identifier=\"com.apple.InterfaceBuilder.IBCocoaTouchPlugin\" version=\"9530\"/></dependencies><scenes><!--View Controller--><scene sceneID=\"tne-QT-ifu\"><objects><viewController id=\"BYZ-38-t0r\" customClass=\"ViewController\" sceneMemberID=\"viewController\"><layoutGuides><viewControllerLayoutGuide type=\"top\" id=\"y3c-jy-aDJ"/><viewControllerLayoutGuide type="bottom" id="wfy-db-euE\"/></layoutGuides>"
#define XMLFOOTER   @"</viewController><placeholder placeholderIdentifier=\"IBFirstResponder\" id=\"tYr-Cr-j24\" userLabel=\"First Responder\" sceneMemberID=\"firstResponder\"/></objects><point key=\"canvasLocation\" x=\"2377\" y=\"429\"/></scene></scenes>"

#define XMLDOCUMENTFOOTER   @"</document>"

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
    NSMutableDictionary *resourcesDict;
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


