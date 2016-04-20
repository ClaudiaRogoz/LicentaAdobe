//
//  XMLReader.m
//  XMLParser
//
//  Created by crogoz on 05/03/16.
//  Copyright © 2016 crogoz. All rights reserved.
//

#include <CommonCrypto/CommonDigest.h>
#import "XMLReader.h"


@interface XMLReader (Internal)

- (id)initWithError:(NSError **)error;
- (NSDictionary *)objectWithData:(NSData *)data;

@end


@implementation XMLReader

#pragma mark -
#pragma mark Public methods








+ (NSDictionary *)dictionaryForXMLData:(NSData *)data resources:(NSString*)resourcesDir xdPath:(NSString*)xdPath outFile:(NSString *)out_file error:(NSError **)error
{
    XMLReader *reader = [[XMLReader alloc] initWithError:error];
    [reader setResourcesPath:resourcesDir];
    [reader setXdPath:xdPath];
    [reader setXmlPath:out_file];
    
    NSMutableDictionary *rootDictionary = [[reader objectWithData:data] mutableCopy];

    NSLog(@"ROOTDICTIONARY = %@", rootDictionary);


    NSString *finalArtboardName = [NSString stringWithFormat:ARTBOARDXML];
    [reader writeToFile:rootDictionary file:finalArtboardName];
    
    NSLog(@"Split\n");
    [reader splitArtboards:rootDictionary];
    
    
   // [reader monitorXDFile:xdPath];
    
    
    return rootDictionary;
}

- (void) writeToFile:(NSDictionary*)xmlDictionary file:(NSString*) file {
    
    NSError *error;
    NSData *jsonData = [NSJSONSerialization dataWithJSONObject:xmlDictionary
                                                       options:NSJSONWritingPrettyPrinted // Pass 0 if you don't care about the readability of the generated string
                                                         error:&error];
    
    if (! jsonData) {
        NSLog(@"Got an error: %@", error);
    } else {
        NSString *jsonString = [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
        
        NSArray *paths = NSSearchPathForDirectoriesInDomains
        (NSDocumentDirectory, NSUserDomainMask, YES);
        NSString *documentsDirectory = [paths objectAtIndex:0];
        NSString *outFile = [NSString stringWithFormat:@"%@/%@", documentsDirectory, file];
        NSLog(@"Writing to file %@", outFile);
        [[NSFileManager defaultManager] createFileAtPath:outFile contents:nil attributes:nil];
        [jsonString writeToFile:outFile atomically:YES encoding:NSUTF8StringEncoding error:nil];
        
    }
}

- (NSMutableArray *)splitArtboards:(NSDictionary *)dictionary {
    NSMutableArray *rootArray = [[NSMutableArray alloc] init];
    
    NSMutableDictionary *artboardsD = [dictionary objectForKey:@"artboards"];
    int nr = 1;
    for (id key in [artboardsD allKeys]) {
        NSMutableDictionary *tempArray = [NSKeyedUnarchiver unarchiveObjectWithData:[NSKeyedArchiver archivedDataWithRootObject: dictionary]];
        id artboardNo = [artboardsD objectForKey:key];
        [tempArray  setValue:[[NSMutableDictionary alloc] init] forKey:@"artboards"];
        [[tempArray objectForKey:@"artboards"]  setValue:artboardNo forKey:key];
        
        id children =  [[dictionary objectForKey:@"children"] objectAtIndex:(nr -1)];
        
        [tempArray setObject:[[NSMutableArray alloc] init] forKey:@"children"];
        [[tempArray objectForKey:@"children"] addObject:children];
        
        NSString *artboardName = [NSString stringWithFormat:@"artboard-artboard%d.agc", nr];
        [self writeToFile:tempArray file:artboardName];
        nr++;
    }
    
    
    
    return rootArray;
    
}

#pragma mark -
#pragma mark Parsing


- (id)initWithError:(NSError **)error
{
    return self;
}

- (void)dealloc
{
    
}

- (NSMutableDictionary *)objectWithData:(NSData *)data
{
    
    dictionaryStack = [[NSMutableArray alloc] init];
    textInProgress = [[NSMutableString alloc] init];
    inheritanceStack = [[NSMutableArray alloc] init];
    attributes = [[NSMutableDictionary alloc] init];
    toInsertObjects = [[NSMutableArray alloc] init];
    //artboards = [[NSMutableArray alloc] init];
    
    //exportScaleStack = [[NSMutableArray alloc] init];
    
    sceneNo = 0;
    
    xmlData = [data mutableCopy];
    xmlOffset = 0;
    
    counterArtboards = 1;
    //TODO eventually read from file (XML ??? )
    insertedRoot = false;
    
    xml2agcDictionary = [[NSMutableDictionary alloc] init];
    xml2agcDictionary[@"scenes"] = @"children";
    xml2agcDictionary[@"scene"] = @"artboard2";
    xml2agcDictionary[@"viewController"] = @"artboard";
    xml2agcDictionary[@"imageView"] = @"imageView";
    xml2agcDictionary[@"view"] = @"children";
    xml2agcDictionary[@"textField"] =@"textField";
    xml2agcDictionary[@"label"] = @"textField";
    xml2agcDictionary[@"switch"] = @"Button";
    
    xml2agcDictionary[@"children"] = @"list";
    xml2agcDictionary[@"children1"] = @"list";
    xml2agcDictionary[@"paragraphs"] = @"list";
    
    //for type = "shape"
    
    
    xml2agcDictionary[@"textField."][@"name"] = @"text";
    
    
    //inverted index for bottom-up inheritance
    xml2agcDictionary[@"imageView."] = @"style.fill.pattern.href";
    xml2agcDictionary[@"rect."] = [[NSMutableDictionary alloc] init];
    xml2agcDictionary[@"rect."][@"x"] = @"textField.transform.tx"; //TODO Dictionary based on type (textField only) -> make dictionary of {textfield: transform.x; label: ....x}
    xml2agcDictionary[@"rect."][@"y"] = @"textField.transform.ty";
    
    //TODO1 eventually transfer to xml2agcDictionary [@"rect."] !!!
    xml2agcDictionary[@"switch."] = [[NSMutableDictionary alloc] init];
    xml2agcDictionary[@"switch."][@"rect"] = [[NSMutableDictionary alloc] init];
    xml2agcDictionary[@"switch."][@"rect"][@"x"] = @"switch.transform.tx";
    xml2agcDictionary[@"switch."][@"rect"][@"y"] = @"switch.transform.ty";
    
    
    xml2agcDictionary[@"switch."][@"color"] = [[NSMutableDictionary alloc] init];
    xml2agcDictionary[@"switch."][@"color"][@"onTintColor"] = [[NSMutableDictionary alloc] init];
    
    xml2agcDictionary[@"rect."][@"width"] = [[NSMutableDictionary alloc] init];
    xml2agcDictionary[@"rect."][@"width"][@"rect"] = @"rect.shape.width"; //TODO Dictionary based on type (textField only) -> make dictionary of {textfield: transform.x; label: ....x}
    xml2agcDictionary[@"rect."][@"width"][@"text"] = @"textField.shape.width";
    xml2agcDictionary[@"rect."][@"width"][@"shape"] = @"imageView.style.fill.pattern.width";
    
    xml2agcDictionary[@"rect."][@"height"] = [[NSMutableDictionary alloc] init];
    xml2agcDictionary[@"rect."][@"height"][@"text"]= @"textField.shape.height";
    xml2agcDictionary[@"rect."][@"height"][@"rect"]= @"rect.shape.height";
    xml2agcDictionary[@"rect."][@"height"][@"shape"] = @"imageView.style.fill.pattern.height";
    
    xml2agcDictionary[@"color."] = [[NSMutableDictionary alloc] init];
    xml2agcDictionary[@"color."][@"red"] = @"textField.style.fill.color.value.r";
    xml2agcDictionary[@"color."][@"green"] = @"textField.style.fill.color.value.g";
    xml2agcDictionary[@"color."][@"blue"] = @"textField.style.fill.color.value.b";
    xml2agcDictionary[@"color."][@"alpha"] = @"textField.style.fill.color.alpha";
    xml2agcDictionary[@"fontDescription."] = [[NSMutableDictionary alloc] init];
    xml2agcDictionary[@"fontDescription."][@"pointSize"] = @"textField.style.font.size";
    xml2agcDictionary[@"length."] = @"textField.text.paragraphs.lines.to";
    //mapping between attr from parent tag -> attr to siblings tag (top -> down ) eg name and rawtext from textField
    // used for didEndElement
    xml2agcDictionary[@"#textField"] = [[NSMutableDictionary alloc] init];
    xml2agcDictionary[@"#textField"][@"textField.text.rawText"] = @"#text";
    
    //default values template!!!
    defaultValues = [[NSMutableDictionary alloc] init];
    defaultValues[@"textField"] = [[NSMutableDictionary alloc] init];
    defaultValues[@"textField"][@"textField.style.fill.color.value.r"] = [NSNumber numberWithInt:0];
    defaultValues[@"textField"][@"textField.style.fill.color.value.g"] = [NSNumber numberWithInt:0];
    defaultValues[@"textField"][@"textField.style.fill.color.value.b"] = [NSNumber numberWithInt:0];
    defaultValues[@"textField"][@"textField.style.fill.color.alpha"] = [NSNumber numberWithInt:1];
    
    // custom templates for agc representation
    attributes = [[NSMutableDictionary alloc] init];
    attributes[@"artboard"] = [[NSMutableDictionary alloc] init]; //TODO style -> background color from color tag (inherits view)
    attributes[@"artboard"][@"ref"] = @"artboard1";
    
    attributes[@"textField"] = [[NSMutableDictionary alloc] init];
    attributes[@"textField"][@"type"] = @"text";
    attributes[@"textField"][@"name"] = @"$text"; //TODO update with ID!!!
    attributes[@"textField"][@"transform"] = [[NSMutableDictionary alloc] init];
    attributes[@"textField"][@"transform"][@"a"] = [NSNumber numberWithInt:1];
    attributes[@"textField"][@"transform"][@"b"] = [NSNumber numberWithInt:0];
    attributes[@"textField"][@"transform"][@"c"] = [NSNumber numberWithInt:0];
    attributes[@"textField"][@"transform"][@"d"] = [NSNumber numberWithInt:1];
    attributes[@"textField"][@"transform"][@"tx"] = @"$rect.x"; // TODO transform based of outer shape(rectangle) -> look for attributes -> textAlignment in testField -> center/ left/right
    attributes[@"textField"][@"transform"][@"ty"] = @"$rect.y";
    attributes[@"textField"][@"style"] = [[NSMutableDictionary alloc] init];
    attributes[@"textField"][@"style"][@"fill"] = [[NSMutableDictionary alloc] init];
    attributes[@"textField"][@"style"][@"fill"][@"type"] = @"solid"; // ?? fontDescription pointsize ???
    attributes[@"textField"][@"style"][@"fill"][@"color"] = [[NSMutableDictionary alloc] init];
    attributes[@"textField"][@"style"][@"fill"][@"color"][@"mode"] = @"RGB";
    attributes[@"textField"][@"style"][@"fill"][@"color"][@"value"] = [[NSMutableDictionary alloc] init];
    attributes[@"textField"][@"style"][@"fill"][@"color"][@"value"][@"r"] = @"$color.red";
    attributes[@"textField"][@"style"][@"fill"][@"color"][@"value"][@"g"] = @"$color.green";
    attributes[@"textField"][@"style"][@"fill"][@"color"][@"value"][@"b"] = @"$color.blue";
    attributes[@"textField"][@"style"][@"fill"][@"color"][@"alpha"] = @"$color.alpha";
    attributes[@"textField"][@"style"][@"font"] = [[NSMutableDictionary alloc] init];
    attributes[@"textField"][@"style"][@"font"][@"postscriptName"] = @"HelveticaNeue"; //TODO hardcodare => default properties
    attributes[@"textField"][@"style"][@"font"][@"family"] = @"Helvetica Neue";
    attributes[@"textField"][@"style"][@"font"][@"style"] = @"Regular";
    attributes[@"textField"][@"style"][@"font"][@"size"] = @"$fontDescription.pointSize";
    attributes[@"textField"][@"text"] = [[NSMutableDictionary alloc] init];
    attributes[@"textField"][@"text"][@"rawText"] = @"#text";
    
    attributes[@"rectangle"] = [[NSMutableDictionary alloc] init];
    attributes[@"rectangle"][@"type"] = @"shape";
    attributes[@"rectangle"][@"transform"] = [[NSMutableDictionary alloc] init];
    attributes[@"rectangle"][@"transform"][@"a"] = [NSNumber numberWithInt:1];
    attributes[@"rectangle"][@"transform"][@"b"] = [NSNumber numberWithInt:0];
    attributes[@"rectangle"][@"transform"][@"c"] = [NSNumber numberWithInt:0];
    attributes[@"rectangle"][@"transform"][@"d"] = [NSNumber numberWithInt:1];
    attributes[@"rectangle"][@"transform"][@"tx"] = @"$rect.x";
    attributes[@"rectangle"][@"transform"][@"ty"] = @"$rect.y";
    attributes[@"rectangle"][@"style"] = [[NSMutableDictionary alloc] init];
    attributes[@"rectangle"][@"style"][@"fill"] = [[NSMutableDictionary alloc] init];
    attributes[@"rectangle"][@"style"][@"fill"][@"type"] = @"solid"; // ?? fontDescription pointsize ???
    attributes[@"rectangle"][@"style"][@"fill"][@"color"] = [[NSMutableDictionary alloc] init];
    attributes[@"rectangle"][@"style"][@"fill"][@"color"][@"mode"] = @"RGB";
    attributes[@"rectangle"][@"style"][@"fill"][@"color"][@"value"] = [[NSMutableDictionary alloc] init];
    attributes[@"rectangle"][@"style"][@"fill"][@"color"][@"value"][@"r"] = @"$color.red";
    attributes[@"rectangle"][@"style"][@"fill"][@"color"][@"value"][@"g"] = @"$color.green";
    attributes[@"rectangle"][@"style"][@"fill"][@"color"][@"value"][@"b"] = @"$color.blue";
    attributes[@"rectangle"][@"shape"] = [[NSMutableDictionary alloc] init];
    attributes[@"rectangle"][@"shape"][@"type"] = @"rect";
    attributes[@"rectangle"][@"shape"][@"x"] = [NSNumber numberWithInt:0];
    attributes[@"rectangle"][@"shape"][@"y"] = [NSNumber numberWithInt:0];
    attributes[@"rectangle"][@"shape"][@"width"] = @"$rect.width";
    attributes[@"rectangle"][@"shape"][@"height"] = @"$rect.height";
    
    attributes[@"path"] = [[NSMutableDictionary alloc] init];
    attributes[@"path"][@"type"] = @"shape";
    attributes[@"path"][@"transform"] = [[NSMutableDictionary alloc] init];
    attributes[@"path"][@"transform"][@"a"] = [NSNumber numberWithInt:1];
    attributes[@"path"][@"transform"][@"b"] = [NSNumber numberWithInt:0];
    attributes[@"path"][@"transform"][@"c"] = [NSNumber numberWithInt:0];
    attributes[@"path"][@"transform"][@"d"] = [NSNumber numberWithInt:1];
    attributes[@"path"][@"transform"][@"tx"] = @"$rect.x";
    attributes[@"path"][@"transform"][@"ty"] = @"$rect.y";
    attributes[@"path"][@"style"] = [[NSMutableDictionary alloc] init];
    attributes[@"path"][@"style"][@"fill"] = [[NSMutableDictionary alloc] init];
    attributes[@"path"][@"style"][@"fill"][@"type"] = @"solid"; // ?? fontDescription pointsize ???
    attributes[@"path"][@"style"][@"fill"][@"color"] = [[NSMutableDictionary alloc] init];
    attributes[@"path"][@"style"][@"fill"][@"color"][@"mode"] = @"RGB";
    attributes[@"path"][@"style"][@"fill"][@"color"][@"value"] = [[NSMutableDictionary alloc] init];
    attributes[@"path"][@"style"][@"fill"][@"color"][@"value"][@"r"] = @"$color.red";
    attributes[@"path"][@"style"][@"fill"][@"color"][@"value"][@"g"] = @"$color.green";
    attributes[@"path"][@"style"][@"fill"][@"color"][@"value"][@"b"] = @"$color.blue";
    attributes[@"path"][@"shape"] = [[NSMutableDictionary alloc] init];
    attributes[@"path"][@"shape"][@"type"] = @"path";
    attributes[@"path"][@"shape"][@"path"] = @"";
    attributes[@"path"][@"style"][@"stroke"] = [[NSMutableDictionary alloc] init];
    attributes[@"path"][@"style"][@"stroke"][@"color"] = [[NSMutableDictionary alloc] init];
    attributes[@"path"][@"style"][@"stroke"][@"color"][@"mode"] = @"RGB";
    attributes[@"path"][@"style"][@"stroke"][@"color"][@"value"] = [[NSMutableDictionary alloc] init];
    attributes[@"path"][@"style"][@"stroke"][@"color"][@"value"][@"r"] = @"$color.red";
    attributes[@"path"][@"style"][@"stroke"][@"color"][@"value"][@"g"] = @"$color.green";
    attributes[@"path"][@"style"][@"stroke"][@"color"][@"value"][@"b"] = @"$color.blue";
    attributes[@"path"][@"style"][@"stroke"][@"type"] = @"solid";
    attributes[@"path"][@"style"][@"stroke"][@"width"] = @"$justAValue";
    attributes[@"path"][@"visualBounds"] = [[NSMutableDictionary alloc] init];
    attributes[@"path"][@"visualBounds"][@"x"] = @"$rect.x";
    attributes[@"path"][@"visualBounds"][@"y"] = @"$rect.y";
    attributes[@"path"][@"visualBounds"][@"width"] = @"$rect.width";
    attributes[@"path"][@"visualBounds"][@"height"] = @"$rect.height";
    
    attributes[@"imageView"] = [[NSMutableDictionary alloc] init];
    attributes[@"imageView"][@"type"] = @"shape";
    attributes[@"imageView"][@"transform"] = [NSKeyedUnarchiver unarchiveObjectWithData:[NSKeyedArchiver archivedDataWithRootObject: attributes[@"rectangle"][@"transform"]]];
    attributes[@"imageView"][@"style"] = [[NSMutableDictionary alloc] init];
    attributes[@"imageView"][@"style"][@"fill"] = [[NSMutableDictionary alloc] init];
    attributes[@"imageView"][@"style"][@"fill"][@"type"] = @"pattern";
    attributes[@"imageView"][@"style"][@"fill"][@"pattern"] = [[NSMutableDictionary alloc] init];
    attributes[@"imageView"][@"style"][@"fill"][@"pattern"][@"width"] = @"$justAValue";
    attributes[@"imageView"][@"style"][@"fill"][@"pattern"][@"height"] = @"$justAValue";
    attributes[@"imageView"][@"style"][@"fill"][@"pattern"][@"href"] = @"$image"; // TODO add resourcesPath
    attributes[@"imageView"][@"style"][@"fill"][@"pattern"][@"meta"] = [[NSMutableDictionary alloc] init];
    attributes[@"imageView"][@"style"][@"fill"][@"pattern"][@"meta"][@"ux"] = [[NSMutableDictionary alloc] init];
    attributes[@"imageView"][@"style"][@"fill"][@"pattern"][@"meta"][@"ux"][@"uid"] = @"$rand";
    
    attributes[@"imageView"][@"shape"] = [[NSMutableDictionary alloc] init];
    attributes[@"imageView"][@"shape"][@"type"] = @"rect";
    attributes[@"imageView"][@"shape"][@"x"] = [NSNumber numberWithInt:0];
    attributes[@"imageView"][@"shape"][@"y"] = [NSNumber numberWithInt:0];
    attributes[@"imageView"][@"shape"][@"width"] = @"$rect.width";
    attributes[@"imageView"][@"shape"][@"height"] = @"$rect.height";
    
    attributes[@"textField"][@"text"][@"frame"] = [[NSMutableDictionary alloc] init];
    attributes[@"textField"][@"text"][@"frame"][@"type"] = @"positioned";
    attributes[@"textField"][@"text"][@"paragraphs"] = [[NSMutableArray alloc] init];
    
    attributes[@"backgroundColor"] = [[NSMutableDictionary alloc] init];
    attributes[@"backgroundColor"][@"style"] = [[NSMutableDictionary alloc] init];
    attributes[@"backgroundColor"][@"style"][@"fill"] = [[NSMutableDictionary alloc] init];
    attributes[@"backgroundColor"][@"style"][@"fill"][@"type"] = @"solid"; // ?? fontDescription pointsize ???
    attributes[@"backgroundColor"][@"style"][@"fill"][@"color"] = [[NSMutableDictionary alloc] init];
    attributes[@"backgroundColor"][@"style"][@"fill"][@"color"][@"mode"] = @"RGB";
    attributes[@"backgroundColor"][@"style"][@"fill"][@"color"][@"value"] = [[NSMutableDictionary alloc] init];
    attributes[@"backgroundColor"][@"style"][@"fill"][@"color"][@"value"][@"r"] = @"$color.red";
    attributes[@"backgroundColor"][@"style"][@"fill"][@"color"][@"value"][@"g"] = @"$color.green";
    attributes[@"backgroundColor"][@"style"][@"fill"][@"color"][@"value"][@"b"] = @"$color.blue";
    
    attributes[@"meta"] = [[NSMutableDictionary alloc] init];
    attributes[@"meta"][@"ux"] = [[NSMutableDictionary alloc] init];
    attributes[@"meta"][@"ux"][@"groupItems"] =  [NSNumber numberWithBool:false];
    
    attributes[@"viewSource"] = [[NSMutableDictionary alloc] init];
    attributes[@"viewSource"][@"x"] = [NSNumber numberWithInt:0];
    attributes[@"viewSource"][@"y"] = [NSNumber numberWithInt:0];
    attributes[@"viewSource"][@"width"] = 0;
    attributes[@"viewSource"][@"height"] = [NSNumber numberWithInt:667]; //TODO change for any Artboard type -> for now Iphone 6
    
    attributes[@"resources"] = [[NSMutableDictionary alloc] init];
    attributes[@"resources"][@"gradients"] = [[NSMutableDictionary alloc] init];
    attributes[@"resources"][@"clipPaths"] = [[NSMutableDictionary alloc] init];
    
    attributes[@"frame"] = [[NSMutableDictionary alloc] init];
    
    objectOffset[@"<imageView"] = [NSNumber numberWithInt: 1];
    objectOffset[@"<label"] = [NSNumber numberWithInt: 1];
    objectOffset[@"<textField"] = [NSNumber numberWithInt: 1];
    objectOffset[@"<switch"] = [NSNumber numberWithInt: 1];
    
    NSMutableDictionary *lines = [[NSMutableDictionary alloc] init];
    NSMutableArray *line = [[NSMutableArray alloc] init];
    NSMutableDictionary *dict = [[NSMutableDictionary alloc] init];
    dict[@"x"] = [NSNumber numberWithInt:0];
    dict[@"y"] = [NSNumber numberWithInt:0];
    dict[@"from"] = [NSNumber numberWithInt:0];
    dict[@"to"] = [NSNumber numberWithInt:11];
    NSMutableArray *temp = [[NSMutableArray alloc]init];
    [temp addObject:dict];
    [line addObject:temp];
    [lines setObject:line forKey:@"lines"];
    
    attributes[@"textField"][@"text"][@"paragraphs"] = [[NSMutableArray alloc] init];
    [attributes[@"textField"][@"text"][@"paragraphs"] addObject: lines];
    
    offsetXmlFile = [[NSMutableDictionary alloc] init];
    
    [dictionaryStack addObject:[NSMutableDictionary dictionary]];
    
    // Parse the XML
    NSXMLParser *parser = [[NSXMLParser alloc] initWithData:data];
    //parser.delegate = self;
    [parser setDelegate:self];
    BOOL success = [parser parse];
    
    // Return the stack's root dictionary on success
    if (success)
    {
        
        id type = [dictionaryStack objectAtIndex:0];
        [type  setObject:[[NSMutableDictionary alloc] init] forKey:@"artboards"];
        //TODO5.03 added here these 3 -> check if export still works
        [type  setObject:[attributes objectForKey:@"viewSource"] forKey:@"viewSource"];
        [type  setObject:[attributes objectForKey:@"meta"] forKey:@"meta"];
        [type  setObject:[attributes objectForKey:@"resources"] forKey:@"resources"];
        id sources = [type objectForKey:@"viewSource"];
        //id viewSource =
        type = [type objectForKey:@"artboards"];
        NSLog(@"Success = %d", counterArtboards);
        int width = 375;
        int height = 667;
        //int offsetX = 400;
        int x = 0;
        
        for (int i = 1; i< counterArtboards; i++){
            NSMutableString *artboardNo = [NSMutableString stringWithFormat:@"artboard%d", i];
            NSMutableString *iphoneNo = [NSMutableString stringWithFormat:@"iPhone 6 – %d", i];
            [type  setObject:[[NSMutableDictionary alloc] init] forKey:artboardNo];
            [[type objectForKey:artboardNo] setObject:[NSNumber numberWithInt: width] forKey:@"width"];
            [[type objectForKey:artboardNo] setObject:[NSNumber numberWithInt: height] forKey:@"height"];
            [[type objectForKey:artboardNo] setObject:[NSNumber numberWithInt: x] forKey:@"x"];
            [[type objectForKey:artboardNo] setObject:[NSNumber numberWithInt: 0] forKey:@"y"];
            [[type objectForKey:artboardNo] setObject:iphoneNo forKey:@"name"];
            x = x + OFFSETBOARD;
        }
        
        //TODO add viewSource
        
        [sources setObject:[NSNumber numberWithInt:x] forKey:@"width"];
        NSMutableDictionary *resultDict = [dictionaryStack objectAtIndex:0];
        return resultDict;
    }
    
    return nil;
}

// functions that scales & updates x based on artboards and import
- (void) scaleAttrDict:(NSMutableDictionary **) attrScaleDict attribute:(NSString *)elementName{
    //don't bother for tags != <rect>
    if (![elementName isEqualToString:@"rect"])
        return;
    
    if ([[inheritanceStack lastObject] isEqualToString:@"children"]) {
        // axiom: all artboards must have the same size in a single app
        widthXMLArtboard = [[*attrScaleDict objectForKey:@"width"] intValue];
        heightXMLArtboard = [[*attrScaleDict objectForKey:@"height"] intValue];
        return;
        
    }
    int x = [[*attrScaleDict objectForKey:@"x"] intValue];
    int y = [[*attrScaleDict objectForKey:@"y"]intValue];
    int width = [[*attrScaleDict objectForKey:@"width"] intValue];
    int height = [[*attrScaleDict objectForKey:@"height"]intValue];
    
    float xScaleFactor = (float)WIDTHIPH6/widthXMLArtboard;
    float yScaleFactor = (float)HEIGHTIPH6/heightXMLArtboard;
    NSLog(@"x = %d ;y  = %d ;width = %d; height = %d", x, y, width, height);
    NSArray *arrayWithSize = [NSArray arrayWithObjects:@"x", @"width", @"y", @"height", nil];
    for (id value in arrayWithSize) {
        float scaledValue = [[*attrScaleDict objectForKey:value] floatValue];
        if ([value isEqualToString:@"x"] ) {
            NSLog(@"Scena este = %d %d", sceneNo, (sceneNo -1) * OFFSETBOARD);
            scaledValue = scaledValue * xScaleFactor+ (sceneNo -1) * OFFSETBOARD;
        }
        else if ([value isEqualToString:@"width"])
            scaledValue = scaledValue * xScaleFactor;
        else
            scaledValue = scaledValue * yScaleFactor;
    
        NSLog(@"Update %@ with %f", value, scaledValue);
        [*attrScaleDict setValue:[NSNumber numberWithFloat:scaledValue] forKey:value];
    }
}

#pragma mark -
#pragma mark NSXMLParserDelegate methods

- (void)parser:(NSXMLParser *)parser didStartElement:(NSString *)elementName namespaceURI:(NSString *)namespaceURI qualifiedName:(NSString *)qName attributes:(NSMutableDictionary *)attributeDict
{
    attributeDict = [attributeDict mutableCopy];
    NSString *tagName = [NSString stringWithFormat:@"<%@", elementName];
    
    //updates width/height/x/y
    if (objectOffset[tagName] != nil){
        
        NSData *find = [tagName dataUsingEncoding:NSUTF8StringEncoding];
        unsigned long start = xmlOffset + 1;
        unsigned long end = [xmlData length];
        
        NSRange range = [xmlData rangeOfData:find options:0 range:NSMakeRange(start, end -start)];
        //NSLog(@"For = %@ %d %d", elementName, range.location, range.length);
        NSMutableArray *arr = [offsetXmlFile objectForKey:[NSNumber numberWithInt:sceneNo]];
        [arr addObject:[NSNumber numberWithLong: range.location]];
        xmlOffset = (unsigned long)range.location;
        //NSLog(@"Start = %d %d", xmlOffset, start);
        
    }
    
    if ([elementName isEqualToString:@"scene"]) {
        sceneNo++;
        [offsetXmlFile setObject: [[NSMutableArray alloc] init] forKey:[NSNumber numberWithInt:sceneNo]];
        
    }
    
    [self scaleAttrDict:&attributeDict attribute:elementName];
    
    // Get the dictionary for the current level in the stack
    NSMutableDictionary *parentDict = [dictionaryStack lastObject];
    //NSString *nameInit = elementName;
    
    if ([elementName isEqualToString:@"switch"]){
        
        NSString *buttonPath = [[NSBundle mainBundle] pathForResource:xml2agcDictionary[elementName] ofType:@"agc"];
        NSError * error=nil;;
        
        NSString *jsonString = [NSString stringWithContentsOfFile:buttonPath encoding:NSUTF8StringEncoding error:&error];
        NSData * jsonData = [jsonString dataUsingEncoding:NSUTF8StringEncoding];
        NSMutableDictionary * parsedData = [NSJSONSerialization JSONObjectWithData:jsonData options:NSJSONReadingMutableContainers error:&error];
        
        //NSLog(@"Button parent = %@", parentDict);
        [parentDict[@"children"] addObject:parsedData];
        [inheritanceStack addObject:@"switch"];
        
        return;
    }
    
    // Create the child dictionary for the new element, and initilaize it with the attributes
    NSMutableDictionary *childDict = [NSMutableDictionary dictionary];
    
    
    NSMutableDictionary* tempDict = [[NSMutableDictionary alloc] init];
    tempDict[@"href"] = @"/resources/graphics/graphicContent.agc";
    
    if (![xml2agcDictionary objectForKey:elementName]) {
        
        //check whether the attr are needed
        NSString *entry = [NSString stringWithFormat:@"%@.", elementName];
        if (![xml2agcDictionary objectForKey:entry])
            return;
        
        if ([elementName isEqualToString: @"rect"]) {
            //save frame for label/textfield
            NSArray *keys =[NSArray arrayWithObjects:@"x", @"y", @"width", @"height", nil];
            NSLog(@"My parent is %@", inheritanceStack);
            
            if ([[inheritanceStack lastObject] isEqualToString:@"children"]) {
                // axiom: all artboards must have the same size in a single app
                widthXMLArtboard = [[attributeDict objectForKey:@"width"] intValue];
                heightXMLArtboard = [[attributeDict objectForKey:@"height"] intValue];
                
            }
            
            for (id attr in keys){
                
                if ([attributeDict[attr] intValue] || [attributeDict[attr] floatValue])
                    attributes[@"frame"][attr] = [NSNumber numberWithFloat:[attributeDict[attr] floatValue]];
                
                attributes[@"frame"][attr] = attributeDict[attr];
                
            }
            
        }
        
        if ([elementName isEqualToString:@"color"] && [[inheritanceStack lastObject] isEqualToString:@"switch"]) {
            int red = [[attributeDict objectForKey:@"red"] floatValue] * 255;
            int green = [[attributeDict objectForKey:@"green"] floatValue] * 255;
            int blue = [[attributeDict objectForKey:@"blue"] floatValue] * 255;
            NSLog(@"Set color to %d %d %d", red, green, blue);
            NSLog(@"Switch parent = %@", [dictionaryStack lastObject]);
            return;
        }
        
        // when there is a tag with the key backgroundColor; add new rectangle with the spec colors
        if ([elementName isEqualToString: @"color"] && [[attributeDict objectForKey:@"key"] isEqualToString:@"backgroundColor"] && [[inheritanceStack lastObject] intValue]) {
            
            NSMutableDictionary *shapeAttr = [NSKeyedUnarchiver unarchiveObjectWithData:[NSKeyedArchiver archivedDataWithRootObject: attributes[@"rectangle"]]];
            
            NSString *str = [NSString stringWithFormat:@"%@.", elementName];
            
            
            for (id key1 in [xml2agcDictionary objectForKey:str]){
                NSArray *strings = [[xml2agcDictionary[str] objectForKey:key1] componentsSeparatedByString:@"."];
                
                id value = shapeAttr;
                for (id key in [strings subarrayWithRange:NSMakeRange(1, [strings count] - 2)]) {
                    value = [value objectForKey:key];
                    
                }
                
                id tempValue = [attributeDict objectForKey:key1];
                
                if ([tempValue intValue])
                    tempValue = [NSNumber numberWithInt:[tempValue intValue]];
                else if ([tempValue floatValue])
                    tempValue = [NSNumber numberWithFloat:[tempValue floatValue]];
                else if ([tempValue isEqualToString:@"0.0"] || [tempValue isEqualToString:@"0"])
                    tempValue = [NSNumber numberWithInt:0];
                float x = [tempValue floatValue];
                int y = x * 255;
                [value setObject:[NSNumber numberWithInt:y] forKey:[strings lastObject]];
                
            }
            
            id size = [attributes objectForKey:@"frame"];
            
            for (id key1 in xml2agcDictionary[@"rect."]){
                
                NSArray *strings;
                if ([[xml2agcDictionary[@"rect."] objectForKey:key1] isKindOfClass:[NSMutableDictionary class]]) {
                    
                    strings = [[[xml2agcDictionary[@"rect."] objectForKey:key1] objectForKey:@"rect" ]componentsSeparatedByString:@"."];
                    
                }
                else
                    strings = [[xml2agcDictionary[@"rect."] objectForKey:key1] componentsSeparatedByString:@"."];
                
                
                id value = shapeAttr;
                for (id key in [strings subarrayWithRange:NSMakeRange(1, [strings count] - 2)]) {
                    value = [value objectForKey:key];
                    
                }
                
                id tempValue = [size objectForKey:key1];
                
                if ([tempValue intValue])
                    tempValue = [NSNumber numberWithInt:[tempValue intValue]];
                else if ([tempValue floatValue])
                    tempValue = [NSNumber numberWithFloat:[tempValue floatValue]];
                else if ([tempValue isEqualToString:@"0.0"] || [tempValue isEqualToString:@"0"])
                    tempValue = [NSNumber numberWithInt:0];
                    
                [value setObject:tempValue forKey:[strings lastObject]];
                
            }
            
            
            [toInsertObjects addObject: shapeAttr];
            
            return;
            
        } else if ([elementName isEqualToString: @"color"] && [[attributeDict objectForKey:@"key"] isEqualToString:@"backgroundColor"] &&
                   [[attributeDict objectForKey:@"colorSpace" ] isEqualToString:@"calibratedRGB"]){
            
            NSString *entry = [NSString stringWithFormat:@"%@.", elementName];
            
            NSMutableDictionary *shapeAttr = [NSKeyedUnarchiver unarchiveObjectWithData:[NSKeyedArchiver archivedDataWithRootObject: attributes[@"backgroundColor"]]];
            
            for (id key in xml2agcDictionary[entry]){
                id value = shapeAttr;
                NSArray *strings = [[xml2agcDictionary[entry] objectForKey:key] componentsSeparatedByString:@"."];
                
                for (id key1 in [strings subarrayWithRange:NSMakeRange(1, [strings count] - 2)]) {
                    value = [value objectForKey:key1];
                    
                }
                
                float tempValue = [[attributeDict objectForKey:key] floatValue];
                int rgb = tempValue * 255;
                
                [value setObject:[NSNumber numberWithInt:rgb] forKey:[strings lastObject]];
                
            }
            
            [toInsertObjects addObject:shapeAttr];
            
            return;
        }
        
        bool ok = false;
        for (id key in xml2agcDictionary[entry]){
            
            NSArray *strings;
            
            if ([[xml2agcDictionary[entry] objectForKey:key] isKindOfClass:[NSMutableDictionary class]]) {
                
                NSString *parent = [parentDict objectForKey:@"type"];
                
                if (parent)
                    strings = [[[xml2agcDictionary[entry] objectForKey:key] objectForKey: parent] componentsSeparatedByString:@"."];
                else {
                    ok = true;
                    return;
                    
                }
            }
            else {
                strings = [[xml2agcDictionary[entry] objectForKey:key] componentsSeparatedByString:@"."];
            }
            
            id value = parentDict;
            
            for (id key1 in [strings subarrayWithRange:NSMakeRange(1, [strings count] - 2)]){
                value = [value objectForKey: key1];
                
            }
            
            if (![attributeDict objectForKey:key])
                continue;
            
            
            id tempValue = [attributeDict objectForKey:key];
            
            if ([tempValue intValue])
                tempValue = [NSNumber numberWithInt:[tempValue intValue]];
            else if ([tempValue floatValue])
                tempValue = [NSNumber numberWithFloat:[tempValue floatValue]];
            
            if ([attributeDict objectForKey:key] && [elementName isEqualToString:@"color"]){
                //transform to RGB values!!!!
                float x = [tempValue floatValue];
                int y = x * 255;
                tempValue = [NSNumber numberWithInt: y];
                
            } else if ([attributeDict objectForKey:key] && [elementName isEqualToString:@"fontDescription"] && [[inheritanceStack lastObject] intValue]){
                
                NSString *text = attributes[@"#text"];
                float width = [[[attributes objectForKey:@"frame"] objectForKey:@"width"] floatValue];
                float height = [[[attributes objectForKey:@"frame"] objectForKey:@"height"] floatValue];
                float x = [[[attributes objectForKey:@"frame"] objectForKey:@"x"] floatValue];
                float y = [[[attributes objectForKey:@"frame"] objectForKey:@"y"] floatValue];
                CGSize frameSize = CGSizeMake(width, height);
                int textSize = [tempValue intValue];
                NSFont *font = [NSFont systemFontOfSize:textSize];
                
                CGRect idealFrame = [text boundingRectWithSize:frameSize
                                                       options:NSStringDrawingUsesLineFragmentOrigin
                                                    attributes:@{ NSFontAttributeName:font }
                                                       context:nil];
                
                float x_pos =(width - idealFrame.size.width) /2;
                float y_pos =(height - idealFrame.size.height) /2;
                
                x_pos = x_pos + x;
                y_pos = y_pos + y + textSize;
                
                id tempDict = parentDict;
                
                tempDict = [tempDict objectForKey:@"transform"];
                
                [tempDict setObject:[NSNumber numberWithFloat:x_pos] forKey:@"tx"];
                [tempDict setObject:[NSNumber numberWithFloat:y_pos] forKey:@"ty"];
                
                [value setObject:tempValue forKey:[strings lastObject]];
                return;
            }
            if (!ok){
                if([ [value objectForKey:[strings lastObject]] isKindOfClass:[NSString class] ] &&
                   [[ [value objectForKey:[strings lastObject]] substringToIndex:1] isEqualToString:@"$"])
                    [value setObject:tempValue forKey:[strings lastObject]];
                else if ([value objectForKey:@"href"]) {
                    //if it is an image -> update width & height
                    
                    id value = parentDict;
                    value = [value objectForKey:@"shape"];
                    
                    float weight = [[attributeDict objectForKey:@"width"] floatValue];
                    float height = [[attributeDict objectForKey:@"height"] floatValue];
                    
                    [value setObject:[NSNumber numberWithFloat:weight] forKey:@"width"];
                    [value setObject:[NSNumber numberWithFloat:height]  forKey:@"height"];
                }
            }
        }
        
        return;
    }
    else if (!insertedRoot){
        [parentDict setObject: @"1.5.0" forKey:@"version"];
        [parentDict setObject: tempDict  forKey:@"resources"];
        [parentDict setObject: tempDict  forKey:@"artboards"];
        
        insertedRoot = true;
    }
    
    
    elementName = [xml2agcDictionary objectForKey:elementName];
    //NSLog(@"ElementName = %@ for %@", elementName, nameInit);
    NSMutableDictionary *correctAttr = [NSKeyedUnarchiver unarchiveObjectWithData:[NSKeyedArchiver archivedDataWithRootObject: attributes[elementName]]];
    ;
    //First level attributes
    for (id key in attributes[elementName]){
        
        id value = [attributes[elementName] objectForKey:key];
        
        if ([value isKindOfClass:[NSString class]]){
            if ([[value substringToIndex:1] isEqualToString:@"$"]){
                
                NSInteger i = [value length] -1;
                value = [value substringWithRange:NSMakeRange(1, i)];
                
                NSString *tempSaved = [NSString stringWithFormat:@"#%@", value];
                id tempValue = nil;
                if ([value isEqualToString:@"text"] && attributeDict[value])
                    tempValue = attributeDict[value];
                
                else if (!attributeDict[value])
                    tempValue = attributeDict[@"placeholder"];
                
                if ([tempValue intValue] )
                    tempValue = [NSNumber numberWithInt:[tempValue intValue]];
                else if ([tempValue floatValue]){
                    tempValue = [NSNumber numberWithFloat:[tempValue floatValue]];
                }
                attributes[tempSaved] = tempValue;
                correctAttr[key] = tempValue;
                
            }
            //TODO transfrom for lower levels; propagate attributes
        } else if ([elementName isEqualToString:@"imageView"] && [key isEqualToString:@"style"]){
            
            NSString *imageName = [NSString stringWithFormat:@"%@%@",
                                   [self resourcesPath], [attributeDict objectForKey:@"image"]];
            NSArray *strings = [[xml2agcDictionary objectForKey:@"imageView."] componentsSeparatedByString:@"."];
            
            id value = correctAttr;
            for (id key in [strings subarrayWithRange:NSMakeRange(0, [strings count] -1)]){
                value = [value objectForKey:key];
                
            }
            
            //generate random values for uid ...
            int num = arc4random() % 1000000;
            [value setObject:imageName forKey:[strings lastObject]];
            
            NSImage *image = [[NSImage alloc]initWithContentsOfFile:imageName];
            
            if (image == nil) {
                NSLog(@"[ERROR]Image is nil");
            }
            
            [value setObject:[NSNumber numberWithInt:image.size.width] forKey:@"width"];
            [value setObject:[NSNumber numberWithInt:image.size.height] forKey:@"height"];
            
            value = [[value objectForKey:@"meta"] objectForKey:@"ux"];
            
            [value setObject: [NSString stringWithFormat:@"%d", num] forKey:@"uid"];
        }
    }
    
    [childDict addEntriesFromDictionary:correctAttr];
    
    if ([xml2agcDictionary objectForKey:[inheritanceStack lastObject]] &&
        [[xml2agcDictionary objectForKey:[inheritanceStack lastObject]] isEqual: @"list"]){
        elementName = [[NSString alloc] initWithFormat:@"%d",counterCh++];
        id lastObject =  [NSKeyedUnarchiver unarchiveObjectWithData:[NSKeyedArchiver archivedDataWithRootObject: [dictionaryStack lastObject]]];
        
        if ([[inheritanceStack lastObject] isEqualToString: @"children"] && ![childDict objectForKey:@"type"]){
            [childDict setObject:@"artboard" forKey:@"type"];
        }
        
        NSMutableArray *array = nil;
        if (![lastObject isKindOfClass:[NSMutableArray class]] && [lastObject count] == 0 ){
            array = [NSMutableArray array];
            [array addObject:childDict];
            
            [parentDict setObject:array forKey:[inheritanceStack lastObject]];
        }
        else {
            
            array = (NSMutableArray *) [lastObject objectForKey:[inheritanceStack lastObject]];
            
            [array addObject: childDict];
            [parentDict setObject:array forKey:[inheritanceStack lastObject]];
            
        }
        
    }else   [parentDict setObject:childDict forKey:elementName];
    
    
    [inheritanceStack addObject:elementName];
    
    [dictionaryStack addObject:childDict];
}

- (void)parser:(NSXMLParser *)parser didEndElement:(NSString *)elementName namespaceURI:(NSString *)namespaceURI qualifiedName:(NSString *)qName
{
    
    
    if ([elementName isEqualToString:@"switch"]) {
        [inheritanceStack removeObject:@"switch"];
        return;
        
    }
    
    if ([xml2agcDictionary[elementName] isEqualToString:@"artboard"]) {
        
        NSString *artboardNo = [NSString stringWithFormat:@"artboard%d", counterArtboards++] ;
        [[dictionaryStack lastObject] setObject:artboardNo forKey:@"ref"];
        
    }
    
    
    if ([elementName isEqualToString:@"rect"] && [[inheritanceStack lastObject] isEqualToString:@"switch"]){
        
        id value = [[[dictionaryStack lastObject] objectForKey:@"children"] lastObject];
        
        
        NSArray *strings = [@"switch.transform.tx" componentsSeparatedByString:@"."];
        
        for (id key in [strings subarrayWithRange:NSMakeRange(1, [strings count] -2)]) {
            value = [value objectForKey:key];
        }
        
        id frame = [attributes objectForKey:@"frame"];
        [value setObject:[frame objectForKey:@"x"] forKey:[strings lastObject]];
        
        strings = [@"switch.transform.ty" componentsSeparatedByString:@"."];
        frame = [attributes objectForKey:@"frame"];
        
        [value setObject:[frame objectForKey:@"y"] forKey:[strings lastObject]];
        
        return;
        
    }
    
    //replace all $"smth" values with default ones
    
    NSString *tempReplace = [NSString stringWithFormat:@"#%@", elementName];
    
    if ([elementName isEqualToString:@"label"]){
        tempReplace = [NSString stringWithFormat:@"#%@", xml2agcDictionary[elementName]];
    }
    
    NSMutableDictionary *parentDict = [dictionaryStack lastObject];
    NSString *textValue = nil;
    for (id key in xml2agcDictionary[tempReplace]){
        
        
        NSArray *strings = [key componentsSeparatedByString:@"."];
        
        
        id value = parentDict;
        
        for (id key1 in [strings subarrayWithRange:NSMakeRange(1, [strings count] - 2)]){
            
            value = [value objectForKey:key1];
            
        }
        textValue = [attributes objectForKey:[xml2agcDictionary[tempReplace] objectForKey:key]];
        [value setObject:[attributes objectForKey:[xml2agcDictionary[tempReplace] objectForKey:key]] forKey:[strings lastObject]];
    }
    
    
    id agcElement = [xml2agcDictionary objectForKey:elementName];
    if ([[xml2agcDictionary objectForKey:agcElement] isEqualToString:@"list"]){
        
        NSInteger counter = [dictionaryStack count];
        id prevParent = dictionaryStack[counter - 2];
        [prevParent addEntriesFromDictionary:parentDict];
    }
    
    if ([elementName isEqualToString:@"textField"] || [elementName isEqualToString:@"label"]){
        
        NSArray *strings = [[xml2agcDictionary objectForKey:@"length."] componentsSeparatedByString:@"."];
        
        id value = parentDict;
        for (id key in [strings subarrayWithRange:NSMakeRange(1, [strings count] - 2)]){
            if ([value isKindOfClass:[NSMutableDictionary class]])
                value = [value objectForKey: key];
            else
                value = value[0][key][0][0]; // For lines only
            
        }
        
        [value setObject:[NSNumber numberWithLong:textValue.length] forKey:[strings lastObject]];
        
    }
    
    //default Values
    id name = elementName;
    if ([elementName isEqualToString:@"label"])
        name =xml2agcDictionary[elementName];
    
    id def = [defaultValues objectForKey:name];
    for(id key in def){
        
        NSArray *strings = [key componentsSeparatedByString:@"."];
        
        id value = parentDict;
        
        for (id key1 in [strings subarrayWithRange:NSMakeRange(1, [strings count] - 2)]){
            value = [value objectForKey:key1];
        }
        
        id tempValue = [value objectForKey:[strings lastObject]];
        
        if (![tempValue isKindOfClass:[NSNumber class]] && [tempValue isKindOfClass:[NSString class]] && [[tempValue substringToIndex:1] isEqualToString:@"$"]){
            
            [value setObject:[def objectForKey:key] forKey:[strings lastObject]];
        }
        
    }
    
    if ([toInsertObjects count] && [elementName isEqualToString:@"view"]) {
        
        id prevParent = [dictionaryStack objectAtIndex:2];
        
        [prevParent addEntriesFromDictionary:[toInsertObjects objectAtIndex:0]];
        [toInsertObjects removeLastObject];
        
    }
    
    //insert Objects from toInsertObjects
    if ([elementName isEqualToString:@"textField"] || [elementName isEqualToString:@"label"] ) {
        for (id key in toInsertObjects){
            NSInteger counter = [dictionaryStack count];
            id prevParent = dictionaryStack[counter - 2];
            
            [[prevParent objectForKey:@"children" ] insertObject:key atIndex:0];
            
        }
        
        [toInsertObjects removeLastObject];
        
    }
    
    
    // Set the text property
    if ([textInProgress length] > 0)
    {
        // Reset the texts
        textInProgress = [[NSMutableString alloc] init];
    }
    
    if ([xml2agcDictionary objectForKey:elementName]){
        // Pop the current dict
        [dictionaryStack removeLastObject];
        
        [inheritanceStack removeLastObject];
        
    }
    
}

- (void)parser:(NSXMLParser *)parser foundCharacters:(NSString *)string
{
    
    // Build the text value
    [textInProgress appendString:string];
}

- (void)parser:(NSXMLParser *)parser parseErrorOccurred:(NSError *)parseError
{
    
}

@end
