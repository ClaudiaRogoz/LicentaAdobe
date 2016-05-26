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
#define RESOURCESDICT   @"ResourcesValue"
#define META_TEMPLATE   @"MetadataTemplate"

/* files format */
#define SVG             @"svg"
#define JSON            @"json"
#define AGC             @"agc"
#define XML             @"xml"
#define XCODEPROJ       @"xcodeproj"
#define ARTBOARD_FILE_PREFIX    @"artboard-artboard"
#define ARTBOARD_PREFIX_ @"artboard-"

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

/* temporary paths */
#define PROJ_PATH   4
#define RESOURCES_PATH  @"Resources"
#define XD_UNZIP_PATH      @".unzipped_xd"
#define XD_EXPORT_PATH     @".export_xd"
#define PREV_ART_PATH   @"prev_artboards"
#define HASH_PATH       @"hashArtboards"
#define OFFSET_PATH     @"offsetArtboards"
#define UNZIP_PATH  @"/usr/bin/unzip"
#define ZIP_PATH    @"/usr/bin/zip"
#define OPEN_PATH   @"/usr/bin/open"
#define BUILD_PATH       @"Build"
#define GRAPHIC_CONTENT @"/resources/graphics/graphicContent.agc"
#define GRAPHIC         @"graphicContent.agc"
#define DS_STORE        @".DS_Store"

#define GRAPHICS    @"graphics"

/* args for app */
#define HELP    "-h"
#define EXPORT  "-e"
#define IMPORT  "-i"
#define SYNC    "-sync"

/*args for creating xd file*/
#define ZIP_RECURSIVE   @"-r"
#define ZIP_DIR         @"--no-dir-entries"
#define ZIP_ARTWORK   @"artwork/"
#define ZIP_INTERACTIONS    @"interactions/"
#define ZIP_META    @"META-INF/" 
#define ZIP_MIME    @"mimetype"
#define ZIP_RESOURCES   @"resources/"
#define ZIP_MANIFEST    @"manifest"

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
#define DEFAULT_GROUP   @"defaultGroup"

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
#define COMPONENTS  @"components"
#define ARTBOARD    @"view"
#define TOSTRING    @"toString"
#define STRING      @"string"
#define HEADER      @"header"
#define SUBTAGS     @"subtags"
#define SUBVIEWS    @"subviews"
#define ISIMAGE     @"image"
#define WIDTH       @"width"
#define HEIGHT      @"height"
#define NAME        @"name"
#define LEN         @"len"
#define ORDER       @"order"
#define IMAGE_RESOURCE  @"$image"
#define BETWEEN     @"inBetween"
#define GROUP       @"group"
#define TYPE        @"type"
#define ARTBOARDS   @"artboards"
#define ARTWORK     @"artwork"
#define VIEWPORT       @"viewportHeight"
#define FIRST_ARTBOARD  @"artboard1"
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
#define PARAGRAPHS_DOT  @"paragraphs."
#define UID         @"uid"
#define ID          @"id"
#define LIST        @"list"
#define ART_SCENE   @"artboard"
#define SHAPE       @"shape"
#define LABEL       @"label"
#define SCALE       @"scale"
#define INTERACTIONS    @"interactions"
#define VERSION_AGC @"1.5.0"
#define VERSION_INTERACTIONS    @"0.3"
#define HREF        @"href"
#define REF         @"ref"

/*used for metadata creation */
#define CREATEDATE  @"CreateDate="
#define MODIFYDATE  @"ModifyDate="
#define METADATADATE    @"MetadataDate="
#define WHENDATE        @"when="
#define DOC_ID      @"DocumentID="
#define ORIG_LID    @"OriginalDocumentID="
#define INST_ID     @"InstanceID="
#define INSTANCE_ID @"instanceID="

#define MANIFEST    @"manifest"
#define PATH_MANIFEST   @"PathManifest"
#define META_INF    @"META-INF"
#define METADATA    @"metadata.xml"


#define TEXTFIELD   @"textField"
#define TEXT_COLOR_R    @"textField.style.fill.color.value.r"
#define TEXT_COLOR_G    @"textField.style.fill.color.value.g"
#define TEXT_COLOR_B    @"textField.style.fill.color.value.b"
#define TEXT_COLOR_A    @"textField.style.fill.color.alpha"
#define CHILDREN_SUBVIEWS   @"children.0.artboard.children"

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
#define SAVED_LINES @"#numberOfLines"
#define SAVED_POINTSIZE @"#pointSize"
#define NO_LINES    @"numberOfLines"
#define GETMAX      @"$MAX"
#define PATH        @"$PATH"
#define GETWIDTH    @"$GETWIDTH"
#define GETHEIGHT   @"$GETHEIGHT"
#define GETX        @"$x"
#define GETY        @"$y"
#define WIDTH_IN_PATH   7
#define HEIGHT_IN_PATH  8
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
#define MUTABLE_STRING  @"mutableString"
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
#define FILE_SIZE       @"$LENGTH"
#define ARTBOARD_PREFIX @"$ARTBOARD_PREFIX"

/* artboards's sizes */
#define WIDTH_XML_ARTBOARD    600
#define HEIGHT_XML_ARTBOARD   600
#define WIDTH_XD_ARTBOARD     375
#define HEIGHT_XD_ARTBOARD    667

#define PBXPROJ_IMAGE_NAME  @"name = "
#define PBXPROJ_IMAGE_PATH  @"; path = "
#define DELIMITER           @";"
#define PREV_PATH           @"../"

#define EPS 3 // just an epsilon value for pointSize calc

/* constants used for iphone6 artboards
 * TODO: update for each artboard
 */
#define OFFSETBOARD 400
#define WIDTHIPH6 375
#define HEIGHTIPH6 667
#define SPARKLERCLIPBOARD   @"com.adobe.sparkler.design"
#define MIMETYPE_CONTENT            @"application/vnd.adobe.sparkler.project+dcx"
#define MIMETYPE            @"mimetype"
#define ARTBOARDXML         @"artboardFromXml.agc"


#endif /* Constants_h */
