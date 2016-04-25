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


/* template paths */
#define DEF_PATH @"Defs"
#define RULES_PATH @"Rules"
#define SVG_TEMPLATE    @"SvgTemplate"
#define AGC_TEMPLATE    @"AGCTemplate"
#define XML2AGC_TEMPLATE    @"Xml2AgcTranslations"


/* files format */
#define SVG             @"svg"
#define JSON            @"json"
#define AGC             @"agc"

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




#define ARTBOARD_FILE_PREFIX    @"artboard-artboard"

#define SVG_INFO    @" d="
#define SVG_FILL    @"fill: "
#define SVG_INFO_LEN     4
#define SVG_FILL_LEN     7
#define SVG_INFO_END    @"\""
#define SVG_FILL_END    @";"


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
#define KEY         @"key"
#define BACKGROUND  @"backgroundColor"
#define COLORSPACE  @"colorSpace"
#define RGB         @"calibratedRGB"
#define SCENE       @"scene"
#define ISFONT      @"family"
#define SWITCH      @"switch"
#define SWITCH_TX   @"switch.transform.tx"
#define SWITCH_TY   @"switch.transform.ty"
#define RECTANGLE   @"rectangle"
#define FRAME_SIZE  @"frame"
#define VIEWSOURCE  @"viewSource"
#define META        @"meta"
#define UX          @"ux"
#define TEXT        @"text"
#define PLACEHOLDER @"placeholder"
#define RESOURCES   @"resources"
#define GROUP_ITEMS  @"groupItems"
#define VERSION     @"version"
#define IMAGEVIEW   @"imageView"
#define IMAGEVIEW_INV   @"imageView."
#define UID         @"uid"
#define LIST        @"list"
#define ART_SCENE   @"artboard"
#define SHAPE       @"shape"
#define LABEL       @"label"
#define SCALE       @"scale"

#define VERSION_AGC @"1.5.0"
#define HREF        @"href"
#define REF         @"ref"
#define GRAPHIC_CONTENT @"/resources/graphics/graphicContent.agc"
#define TEXTFIELD   @"textField"
#define TEXT_COLOR_R    @"textField.style.fill.color.value.r"
#define TEXT_COLOR_G    @"textField.style.fill.color.value.g"
#define TEXT_COLOR_B    @"textField.style.fill.color.value.b"
#define TEXT_COLOR_A    @"textField.style.fill.color.alpha"

#define FRAME_DOT   @"rect."
#define LENGTH_DOT  @"length."
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
#define SAVED_VALUE @"#"
#define SAVED_TEXT  @"#text"
#define GETMAX      @"$MAX"
#define PATH        @"$PATH"
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
#define FRAMED       @"$frame"


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
