//
//  Constants.h
//  XMLParser
//
//  Created by crogoz on 14/04/16.
//  Copyright © 2016 crogoz. All rights reserved.
//

#ifndef Constants_h
#define Constants_h

#define STORYBOARD  @"Base.lproj/Main.storyboard"
#define DEF_PATH @"Defs"
#define RULES_PATH @"Rules"

/* Test files */
#define TEST_PATH @"XMLParser/TestGenerator.json"
#define TEST2_PATH @"Test2LabelsInAgcGenerator.json"
#define TESTDROP_PATH @"TestDropFile.json"
#define TESTIL_PATH    @"TestImageLabels.json"
#define TESTMUL_PATH    @"TestMultiple.json"
#define TESTPARA_PATH   @"TestParagraphs.json"
#define TESTPARAGROUP_PATH  @"TestParaGroup.json"
#define TESTTGS_PATH         @"TestTextGroupShapes.json"
#define TESTTEXT_PATH       @"TestTextGroup.json"
#define TESTMULTTEXT_PATH       @"TestMulText"
#define TESTBIGIMG      @"TestBigImage"
#define JSON            @"json"

#define RANDOM @"$rand"
#define SCENENO @"$sceneNo"
#define SUBVIEWNO @"$subviewNo"

#define DEFAULT @"default"

#define ARTBOARDSCENE @"$artboardsceneNo"
#define LINES       @"$lineListNo"
#define LINESDICT   @"$lineNo"
#define COUNT       @"$count"
#define STYLE       @"$style"
#define TEXT_PARAGRAPH  @"$text.paragraphs"
#define TEXT_LINES      @"$text.paragraphs.$lineListNo.lines"

#define LINE_VALUE  @"lines"
#define STYLE_VALUE @"style"
#define SIZE        @"size"
#define VIEW        @"view"
#define RULES       @"rules"
#define CHILDREN    @"children"
#define ARTBOARD    @"view"
#define TOSTRING    @"toString"
#define HEADER      @"header"
#define SUBTAGS     @"subtags"
#define SUBVIEWS    @"subviews"
#define ISIMAGE     @"image"
#define WIDTH       @"width"
#define HEIGHT      @"height"
#define NAME        @"name"
#define LEN         @"len"
#define ORDER       @"order"
#define BETWEEN     @"inBetween"
#define GROUP       @"group"
#define TYPE        @"type"
#define ARTBOARDS   @"artboards"
#define TRANSFORM   @"transform"
#define TX          @"tx"
#define TY          @"ty"
#define FRAME       @"rect"


#define COLOR       @"color"
#define RED         @"red"
#define GREEN       @"green"
#define BLUE        @"blue"

#define NOT         @"NOT"
#define SPACE       @" "

/* Fonts */
#define REGULAR     @"Regular"
#define ITALIC      @"Italic"
#define BOLD        @"Bold"

#define FONT_DESCR @"fontDescription"
#define FONT_SYSTEM @"system"
#define FONT_ITALIC @"italicSystem"
#define FONT_BOLD   @"boldSystem"


#define DOT         @"."
#define TO          @"to"
#define RAWTEXT     @"$rawText"
#define RAWTEXT_VALUE   @"rawText"
#define TOTRANSFORM @"$"
#define GETMAX      @"$MAX"
/* XML2AGC const */
#define FRAME_X    @"$rect.x"
#define FRAME_Y    @"$rect.y"
#define COLOR_RED     @"$color.red"
#define COLOR_GREEN     @"$color.green"
#define COLOR_BLUE  @"$color.blue"
#define FONT_POINT  @"$fontDescription.pointSize"

/* initial offset for xml scene */
#define XML_SCENE_X 2377
#define XML_SCENE_Y 429

#define XML_OFFSET_X    644

/* template for headers */
#define STRINGTAG   @"</mutableString>"
#define XMLRESOURCES   @"<resources>"
#define XMLRESOURCESF  @"</resources>"
#define XMLHEADERA   @"<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?><document type=\"com.apple.InterfaceBuilder3.CocoaTouch.Storyboard.XIB\" version=\"3.0\" toolsVersion=\"9532\" systemVersion=\"15E65\" targetRuntime=\"iOS.CocoaTouch\" propertyAccessControl=\"none\" useAutolayout=\"YES\" useTraitCollections=\"YES\" initialViewController="
#define XMLHEADERB  @"><dependencies><deployment identifier=\"iOS\"/><plugIn identifier=\"com.apple.InterfaceBuilder.IBCocoaTouchPlugin\" version=\"9530\"/></dependencies><scenes>"
#define XMLFOOTERA   @"</viewController><placeholder placeholderIdentifier=\"IBFirstResponder\" id="
#define XMLFOOTERB   @" userLabel=\"First Responder\" sceneMemberID=\"firstResponder\"/></objects><point key=\"canvasLocation\" x="
#define XMLFOOTERC   @" y="
#define XMLFOOTERD   @"/></scene>"

#define SCENEHEADERA @"<!--View Controller--><scene sceneID="
#define SCENEHEADERB @"><objects><viewController id="
#define SCENEHEADERC @" customClass=\"ViewController\" sceneMemberID=\"viewController\"><layoutGuides><viewControllerLayoutGuide type=\"top\" id="
#define SCENEHEADERD @"/><viewControllerLayoutGuide type=\"bottom\" id="
#define SCENEHEADERE @"/></layoutGuides>"

#define XMLSUBVIEWS         @"\n<subviews>"
#define XMLSUBVIEWSF        @"\n</subviews>"
#define XMLSCENESF          @"</scenes>"
#define XMLVIEWF            @"</view>"
#define XMLDOCUMENTF   @"</document>"
#define XARTBOARD       @"x"
#define YARTBOARD       @"y"

/* artboards's sizes */
#define WIDTHXMLARTBOARD    600
#define HEIGHTXMLARTBOARD   600
#define WIDTHXDARTBOARD     375
#define HEIGHTXDARTBOARD    667


#define EPS 3 // just an epsilon value for pointSize calc

/* constants used for iphone6 artboards
 * TODO: update for each artboard
 */
#define OFFSETBOARD 400
#define WIDTHIPH6 375
#define HEIGHTIPH6 667
#define SPARKLERCLIPBOARD   @"com.adobe.sparkler.design"
#define ARTBOARDXML         @"artboardFromXml.agc"

#endif /* Constants_h */
