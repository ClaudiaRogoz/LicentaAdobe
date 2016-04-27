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


    NSString *finalArtboardName = [NSString stringWithFormat:ARTBOARDXML];
    [reader writeToFile:rootDictionary file:finalArtboardName];
    
    [reader splitArtboards:rootDictionary];
    
    
    return rootDictionary;
}

- (void) writeToFile:(NSDictionary*)xmlDictionary file:(NSString*) file {
    
    NSError *error;
    NSData *jsonData = [NSJSONSerialization dataWithJSONObject:xmlDictionary
                                                       options:NSJSONWritingPrettyPrinted
                                                         error:&error];
    
    if (! jsonData) {
        NSLog(@"Got an error: %@", error);
    } else {
        NSString *jsonString = [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
        NSString *mainBundle = [[NSBundle mainBundle] bundlePath];
        
        NSString *outFile = [NSString stringWithFormat:@"%@/.%@", mainBundle, file];
        
        [[NSFileManager defaultManager] createFileAtPath:outFile contents:nil attributes:nil];
        [jsonString writeToFile:outFile atomically:YES encoding:NSUTF8StringEncoding error:nil];
        
    }
}

- (NSMutableArray *)splitArtboards:(NSDictionary *)dictionary {
    
    NSMutableArray *rootArray = [[NSMutableArray alloc] init];
    NSMutableDictionary *artboardsD = [dictionary objectForKey:ARTBOARDS];
    NSString *mainBundle = [[NSBundle mainBundle] bundlePath];
    NSError *error;
    int nr = 1;
    
    for (id key in [artboardsD allKeys]) {
        
        NSMutableDictionary *tempArray = [NSKeyedUnarchiver unarchiveObjectWithData:[NSKeyedArchiver archivedDataWithRootObject: dictionary]];
        
        id artboardNo = [artboardsD objectForKey:key];
        [tempArray  setValue:[[NSMutableDictionary alloc] init] forKey:ARTBOARDS];
        [[tempArray objectForKey:ARTBOARDS]  setValue:artboardNo forKey:key];
        
        id children =  [[dictionary objectForKey:CHILDREN] objectAtIndex:(nr -1)];
        
        [tempArray setObject:[[NSMutableArray alloc] init] forKey:CHILDREN];
        [[tempArray objectForKey:CHILDREN] addObject:children];
        
        
        /* create a temp directory where all the prev artboards can be stored */
        /* used for sync */
        [[NSFileManager defaultManager] createDirectoryAtPath:[mainBundle stringByAppendingPathComponent:PREV_ART_PATH] withIntermediateDirectories:NO attributes:nil error:&error];
        
        NSString *artboardName = [NSString stringWithFormat:@"%@/%@%d%@%@", PREV_ART_PATH, ARTBOARD_FILE_PREFIX, nr, DOT, AGC];
        
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

-(void) initAllData {
    
    dictionaryStack = [[NSMutableArray alloc] init];
    textInProgress = [[NSMutableString alloc] init];
    inheritanceStack = [[NSMutableArray alloc] init];
    attributes = [[NSMutableDictionary alloc] init];
    toInsertObjects = [[NSMutableArray alloc] init];
    
    sceneNo = 0;
    xmlOffset = 0;
    counterArtboards = 1;
    insertedRoot = false;
    
    NSError *error;
    
    /* xml2agc translations */
    NSBundle *thisBundle = [NSBundle bundleForClass:[self class]];
    NSString *dictStr = [thisBundle pathForResource:XML2AGC_TEMPLATE ofType:JSON];
    NSData *dictData = [NSData dataWithContentsOfFile:dictStr];
    xml2agcDictionary = [NSJSONSerialization JSONObjectWithData:dictData options:NSJSONReadingMutableContainers error:&error];
    
    /* agc template */
    NSString *def = [thisBundle pathForResource:AGC_TEMPLATE ofType:JSON];
    NSData *defData = [NSData dataWithContentsOfFile:def];
    attributes = [NSJSONSerialization JSONObjectWithData:defData options:NSJSONReadingMutableContainers error:&error];
    
    /* default values template */
    defaultValues = [[NSMutableDictionary alloc] init];
    defaultValues[TEXTFIELD] = [[NSMutableDictionary alloc] init];
    defaultValues[TEXTFIELD][TEXT_COLOR_R] = [NSNumber numberWithInt:0];
    defaultValues[TEXTFIELD][TEXT_COLOR_G] = [NSNumber numberWithInt:0];
    defaultValues[TEXTFIELD][TEXT_COLOR_B] = [NSNumber numberWithInt:0];
    defaultValues[TEXTFIELD][TEXT_COLOR_A] = [NSNumber numberWithInt:1];
    
    /*TODO remove*/
    objectOffset[@"<scene"] = [NSNumber numberWithInt: 1];
    
    offsetXmlFile = [[NSMutableDictionary alloc] init];
    
    [dictionaryStack addObject:[NSMutableDictionary dictionary]];


}

- (NSMutableDictionary *)objectWithData:(NSData *)data
{
    
    
    [self initAllData];
    
    xmlData = [data mutableCopy];
    
    /* Parse the XML */
    NSXMLParser *parser = [[NSXMLParser alloc] initWithData:data];
    
    [parser setDelegate:self];
    BOOL success = [parser parse];
    
    /* Return the stack's root dictionary on success */
    if (success)
    {
        
        id type = [dictionaryStack objectAtIndex:0];
        [type  setObject:[[NSMutableDictionary alloc] init] forKey:ARTBOARDS];
        [type  setObject:[attributes objectForKey:VIEWSOURCE] forKey:VIEWSOURCE];
        [[[type objectForKey:META] objectForKey:UX] setObject:[NSNumber numberWithBool:false] forKey:GROUP_ITEMS];
        [type  setObject:[attributes objectForKey:META] forKey:META];
        [type  setObject:[attributes objectForKey:RESOURCES] forKey:RESOURCES];
        id sources = [type objectForKey:VIEWSOURCE];
       
        type = [type objectForKey:ARTBOARDS];
        
        int width = 375;
        int height = 667;
        
        int x = 0;
        
        for (int i = 1; i< counterArtboards; i++){
            NSMutableString *artboardNo = [NSMutableString stringWithFormat:@"artboard%d", i];
            NSMutableString *iphoneNo = [NSMutableString stringWithFormat:@"iPhone 6 – %d", i];
            [type  setObject:[[NSMutableDictionary alloc] init] forKey:artboardNo];
            [[type objectForKey:artboardNo] setObject:[NSNumber numberWithInt: width] forKey:WIDTH];
            [[type objectForKey:artboardNo] setObject:[NSNumber numberWithInt: height] forKey:HEIGHT];
            [[type objectForKey:artboardNo] setObject:[NSNumber numberWithInt: x] forKey:XARTBOARD];
            [[type objectForKey:artboardNo] setObject:[NSNumber numberWithInt: 0] forKey:YARTBOARD];
            [[type objectForKey:artboardNo] setObject:iphoneNo forKey:NAME];
            x = x + OFFSETBOARD;
        }
        
        [sources setObject:[NSNumber numberWithInt:x] forKey:WIDTH];
        NSMutableDictionary *resultDict = [dictionaryStack objectAtIndex:0];
        return resultDict;
    }
    
    return nil;
}

/* scales & updates x based on artboards and import data */
- (void) scaleAttrDict:(NSMutableDictionary **) attrScaleDict attribute:(NSString *)elementName{
    
    NSArray *arrayWithSize = [NSArray arrayWithObjects:XARTBOARD, WIDTH,YARTBOARD, HEIGHT, nil];
    
    /* don't bother for tags != <rect> */
    if (![elementName isEqualToString:FRAME])
        return;
    
    if ([[inheritanceStack lastObject] isEqualToString:CHILDREN]) {
        
        /* all artboards must have the same size in a single app */
        widthXMLArtboard = [[*attrScaleDict objectForKey:WIDTH] intValue];
        heightXMLArtboard = [[*attrScaleDict objectForKey:HEIGHT] intValue];
        return;
    }

    float xScaleFactor = (float)WIDTHIPH6/widthXMLArtboard;
    float yScaleFactor = (float)HEIGHTIPH6/heightXMLArtboard;
    
    for (id value in arrayWithSize) {
        float scaledValue = [[*attrScaleDict objectForKey:value] floatValue];
        if ([value isEqualToString:XARTBOARD] ) {
            
            scaledValue = scaledValue * xScaleFactor+ (sceneNo -1) * OFFSETBOARD;
        }
        else if ([value isEqualToString:WIDTH])
            scaledValue = scaledValue * xScaleFactor;
        else
            scaledValue = scaledValue * yScaleFactor;
    
        [*attrScaleDict setValue:[NSNumber numberWithFloat:scaledValue] forKey:value];
    }
}

#pragma mark -
#pragma mark NSXMLParserDelegate methods

-(void) saveFrame:(NSMutableDictionary *)attributeDict {

    /* save frame for label/textfield */
    NSArray *keys =[NSArray arrayWithObjects:XARTBOARD, YARTBOARD, WIDTH, HEIGHT, nil];
    
    
    if ([[inheritanceStack lastObject] isEqualToString:CHILDREN]) {
        // axiom: all artboards must have the same size in a single app
        widthXMLArtboard = [[attributeDict objectForKey:WIDTH] intValue];
        heightXMLArtboard = [[attributeDict objectForKey:HEIGHT] intValue];
        
    }
    
    for (id attr in keys){
        
        if ([attributeDict[attr] intValue] || [attributeDict[attr] floatValue])
            attributes[FRAME_SIZE][attr] = [NSNumber numberWithFloat:[attributeDict[attr] floatValue]];
        
        attributes[FRAME_SIZE][attr] = attributeDict[attr];
        
    }

}

-(NSNumber *)convertToNumber:(id) tempValue {

    NSNumber *nr = [[NSNumber alloc] init];
    if ([tempValue intValue])
        nr = [NSNumber numberWithInt:[tempValue intValue]];
    else if ([tempValue floatValue])
        nr = [NSNumber numberWithFloat:[tempValue floatValue]];
    else if ([tempValue isEqualToString:@"0.0"] || [tempValue isEqualToString:@"0"])
        nr = [NSNumber numberWithInt:0];
    
    return nr;

}

-(void)transformAgcColor:(NSString *)entry  searchAttr:(NSMutableDictionary *)searchAttr dictAttr:(NSMutableDictionary *)attributeDict {

    for (id key1 in [xml2agcDictionary objectForKey:entry]){
        NSArray *strings = [[xml2agcDictionary[entry] objectForKey:key1] componentsSeparatedByString:@"."];
        
        id value = searchAttr;
        for (id key in [strings subarrayWithRange:NSMakeRange(1, [strings count] - 2)]) {
            value = [value objectForKey:key];
            
        }
        
        id tempValue = [attributeDict objectForKey:key1];
        NSNumber *number = [self convertToNumber:(id) tempValue];
        
        float x = [number floatValue];
        int y = x * 255;
        [value setObject:[NSNumber numberWithInt:y] forKey:[strings lastObject]];
        
    }

}

-(void)createAgcFrameForElement:(NSString *)elementName attributes:(NSMutableDictionary *)attributeDict {

    NSMutableDictionary *shapeAttr = [NSKeyedUnarchiver unarchiveObjectWithData:[NSKeyedArchiver archivedDataWithRootObject: attributes[RECTANGLE]]];
    
    NSString *entry = [NSString stringWithFormat:@"%@.", elementName];
    
    [self transformAgcColor:entry searchAttr:shapeAttr dictAttr:attributeDict];
    
    id size = [attributes objectForKey:FRAME_SIZE];
    
    for (id key1 in xml2agcDictionary[FRAME_DOT]){
        
        NSArray *strings;
        if ([[xml2agcDictionary[FRAME_DOT] objectForKey:key1] isKindOfClass:[NSMutableDictionary class]]) {
            
            strings = [[[xml2agcDictionary[FRAME_DOT] objectForKey:key1] objectForKey:FRAME ]componentsSeparatedByString:DOT];
            
        }
        else
            strings = [[xml2agcDictionary[FRAME_DOT] objectForKey:key1] componentsSeparatedByString:DOT];
        
        
        id value = shapeAttr;
        for (id key in [strings subarrayWithRange:NSMakeRange(1, [strings count] - 2)]) {
            value = [value objectForKey:key];
            
        }
        
        id tempValue = [size objectForKey:key1];
        
        NSNumber *number = [self convertToNumber:(id) tempValue];
        [value setObject:number forKey:[strings lastObject]];
        
    }
    
    
    [toInsertObjects addObject: shapeAttr];

}

-(NSDictionary*) getIdealFrameForPointSize:(id) tempValue {

    NSMutableDictionary *offset = [[NSMutableDictionary alloc] init];
    NSString *text = attributes[SAVED_TEXT];
    float width = [[[attributes objectForKey:FRAME_SIZE] objectForKey:WIDTH] floatValue];
    float height = [[[attributes objectForKey:FRAME_SIZE] objectForKey:HEIGHT] floatValue];
    float x = [[[attributes objectForKey:FRAME_SIZE] objectForKey:XARTBOARD] floatValue];
    float y = [[[attributes objectForKey:FRAME_SIZE] objectForKey:YARTBOARD] floatValue];
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
    
    [offset setObject:[NSNumber numberWithFloat:x_pos] forKey:XARTBOARD];
    [offset setObject:[NSNumber numberWithFloat:y_pos] forKey:YARTBOARD];
    
    return  offset;
}

-(void)replaceTemplateValuesForEntry:(NSString *)elementName parentDict:(NSMutableDictionary *)parentDict
                           attribDict:(NSMutableDictionary *)attributeDict {
    
    bool ok = false;
    NSString *entry = [NSString stringWithFormat:@"%@.", elementName];
    
    for (id key in xml2agcDictionary[entry]){
        
        NSArray *strings;
        
        if ([[xml2agcDictionary[entry] objectForKey:key] isKindOfClass:[NSMutableDictionary class]]) {
            
            NSString *parent = [parentDict objectForKey:TYPE];
            
            if (parent)
                strings = [[[xml2agcDictionary[entry] objectForKey:key] objectForKey: parent] componentsSeparatedByString:DOT];
            else {
                ok = true;
                return;
            }
        }
        else {
            strings = [[xml2agcDictionary[entry] objectForKey:key] componentsSeparatedByString:DOT];
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
        
        if ([attributeDict objectForKey:key] && [elementName isEqualToString:COLOR]){
            //transform to RGB values!!!!
            float x = [tempValue floatValue];
            int y = x * 255;
            tempValue = [NSNumber numberWithInt: y];
            
        } else if ([attributeDict objectForKey:key] && [elementName isEqualToString:FONT_DESCR] && [[inheritanceStack lastObject] intValue]) {
            
            NSDictionary *pos = [self getIdealFrameForPointSize:tempValue];
            id tempDict = parentDict;
            
            tempDict = [tempDict objectForKey:TRANSFORM];
            
            [tempDict setObject:[pos objectForKey:XARTBOARD] forKey:TX];
            [tempDict setObject:[pos objectForKey:YARTBOARD] forKey:TY];
            
            [value setObject:tempValue forKey:[strings lastObject]];
            return;
        }
        if (!ok){
            if([ [value objectForKey:[strings lastObject]] isKindOfClass:[NSString class] ] &&
               [[ [value objectForKey:[strings lastObject]] substringToIndex:1] isEqualToString:TOTRANSFORM])
                [value setObject:tempValue forKey:[strings lastObject]];
            else if ([value objectForKey:HREF]) {
                //if it is an image -> update width & height
                
                id value = parentDict;
                value = [value objectForKey:SHAPE];
                
                float weight = [[attributeDict objectForKey:WIDTH] floatValue];
                float height = [[attributeDict objectForKey:HEIGHT] floatValue];
                
                [value setObject:[NSNumber numberWithFloat:weight] forKey:WIDTH];
                [value setObject:[NSNumber numberWithFloat:height]  forKey:HEIGHT];
            }
        }
    }


}

-(void)transformAttributesForElement:(NSString *)elementName attributeDict:(NSMutableDictionary*)attributeDict
                           childDict:(NSMutableDictionary *)childDict parentDict:(NSMutableDictionary**)parentDict
{
    
    NSMutableDictionary *correctAttr = [NSKeyedUnarchiver unarchiveObjectWithData:[NSKeyedArchiver archivedDataWithRootObject: attributes[elementName]]];
    ;
    //First level attributes
    for (id key in attributes[elementName]){
        
        id value = [attributes[elementName] objectForKey:key];
        
        if ([value isKindOfClass:[NSString class]]){
            if ([[value substringToIndex:1] isEqualToString:TOTRANSFORM]){
                
                NSInteger i = [value length] -1;
                value = [value substringWithRange:NSMakeRange(1, i)];
                
                NSString *tempSaved = [NSString stringWithFormat:@"%@%@", SAVED_VALUE, value];
                id tempValue = nil;
                if ([value isEqualToString:TEXT] && attributeDict[value])
                    tempValue = attributeDict[value];
                
                else if (!attributeDict[value])
                    tempValue = attributeDict[PLACEHOLDER];
                
                if ([tempValue intValue] )
                    tempValue = [NSNumber numberWithInt:[tempValue intValue]];
                else if ([tempValue floatValue]){
                    tempValue = [NSNumber numberWithFloat:[tempValue floatValue]];
                }
                attributes[tempSaved] = tempValue;
                correctAttr[key] = tempValue;
                
            }
            /* transfrom for lower levels; propagate attributes */
        } else if ([elementName isEqualToString:IMAGEVIEW] && [key isEqualToString:STYLE_VALUE]){
            
            NSString *imageName = [NSString stringWithFormat:@"%@%@",
                                   [self resourcesPath], [attributeDict objectForKey:ISIMAGE]];
            NSArray *strings = [[xml2agcDictionary objectForKey:IMAGEVIEW_INV] componentsSeparatedByString:DOT];
            
            id value = correctAttr;
            for (id key in [strings subarrayWithRange:NSMakeRange(0, [strings count] -1)]){
                value = [value objectForKey:key];
                
            }
            
            /* generate random values for uid */
            int num = arc4random() % 1000000;
            [value setObject:imageName forKey:[strings lastObject]];
            
            NSImage *image = [[NSImage alloc]initWithContentsOfFile:imageName];
            
            if (image == nil) {
                NSLog(@"[ERROR]Image is nil");
            }
            
            [value setObject:[NSNumber numberWithInt:image.size.width] forKey:WIDTH];
            [value setObject:[NSNumber numberWithInt:image.size.height] forKey:HEIGHT];
            
            value = [[value objectForKey:META] objectForKey:UX];
            
            [value setObject: [NSString stringWithFormat:@"%d", num] forKey:UID];
        }
    }
    
    [childDict addEntriesFromDictionary:correctAttr];
    
    if ([xml2agcDictionary objectForKey:[inheritanceStack lastObject]] &&
        [[xml2agcDictionary objectForKey:[inheritanceStack lastObject]] isEqual: LIST]){
        elementName = [[NSString alloc] initWithFormat:@"%d",counterCh++];
        id lastObject =  [NSKeyedUnarchiver unarchiveObjectWithData:[NSKeyedArchiver archivedDataWithRootObject: [dictionaryStack lastObject]]];
        
        if ([[inheritanceStack lastObject] isEqualToString: CHILDREN] && ![childDict objectForKey:TYPE]){
            [childDict setObject:ART_SCENE forKey:TYPE];
        }
        
        NSMutableArray *array = nil;
        if (![lastObject isKindOfClass:[NSMutableArray class]] && [lastObject count] == 0 ){
            array = [NSMutableArray array];
            [array addObject:childDict];
            
            [*parentDict setObject:array forKey:[inheritanceStack lastObject]];
        }
        else {
            
            array = (NSMutableArray *) [lastObject objectForKey:[inheritanceStack lastObject]];
            
            [array addObject: childDict];
            [*parentDict setObject:array forKey:[inheritanceStack lastObject]];
            
        }
        
    }else   [*parentDict setObject:childDict forKey:elementName];

    [inheritanceStack addObject:elementName];
    
    [dictionaryStack addObject:childDict];

}

-(void)createDictionaryForElement:(NSString *) elementName attributes:(NSMutableDictionary *) attributeDict parentDict:( NSMutableDictionary *)parentDict{

    /* Create the child dictionary for the new element, and initilaize it with the attributes */
    NSMutableDictionary *childDict = [NSMutableDictionary dictionary];
    
    NSMutableDictionary* tempDict = [[NSMutableDictionary alloc] init];
    tempDict[HREF] = GRAPHIC_CONTENT;
    
    if (![xml2agcDictionary objectForKey:elementName]) {
        
        /* check if the attr are needed */
        NSString *entry = [NSString stringWithFormat:@"%@.", elementName];
        
        if (![xml2agcDictionary objectForKey:entry])
            return;
        
        if ([elementName isEqualToString: FRAME]) {
            [self saveFrame:attributeDict];
        }
        
        if ([elementName isEqualToString:COLOR] && [[inheritanceStack lastObject] isEqualToString:SWITCH]) {
            return;
        }
        
        /* when there is a tag with the key backgroundColor; add new rectangle with the spec colors */
        if ([elementName isEqualToString: COLOR] && [[attributeDict objectForKey:KEY] isEqualToString:BACKGROUND] &&
                            [[inheritanceStack lastObject] intValue]) {
            
            [self createAgcFrameForElement:elementName attributes:attributeDict];
            return;
            
        /* when we use background for artboard */
        } else if ([elementName isEqualToString: COLOR] && [[attributeDict objectForKey:KEY] isEqualToString:BACKGROUND] &&
                   [[attributeDict objectForKey:COLORSPACE] isEqualToString:RGB]){
            
            NSString *entry = [NSString stringWithFormat:@"%@.", elementName];
            
            NSMutableDictionary *shapeAttr = [NSKeyedUnarchiver unarchiveObjectWithData:[NSKeyedArchiver archivedDataWithRootObject: attributes[BACKGROUND]]];
            
            [self transformAgcColor:entry searchAttr:shapeAttr dictAttr:attributeDict];
            
            [toInsertObjects addObject:shapeAttr];
            
            return;
        }
        
        [self replaceTemplateValuesForEntry:elementName parentDict:parentDict attribDict:attributeDict];

        return;
    }
    else if (!insertedRoot){
        [parentDict setObject: VERSION_AGC forKey:VERSION];
        [parentDict setObject: tempDict  forKey:RESOURCES];
        [parentDict setObject: tempDict  forKey:ARTBOARDS];
        
        insertedRoot = true;
    }

    elementName = [xml2agcDictionary objectForKey:elementName];
    
    [self transformAttributesForElement:elementName attributeDict:attributeDict childDict:childDict parentDict:&parentDict];

}

- (void)parser:(NSXMLParser *)parser didStartElement:(NSString *)elementName namespaceURI:(NSString *)namespaceURI qualifiedName:(NSString *)qName attributes:(NSMutableDictionary *)attributeDict
{
    attributeDict = [attributeDict mutableCopy];
    NSString *tagName = [NSString stringWithFormat:@"<%@", elementName];
    
    /* updates width/height/x/y */
    if (objectOffset[tagName] != nil){
        
        NSData *find = [tagName dataUsingEncoding:NSUTF8StringEncoding];
        unsigned long start = xmlOffset + 1;
        unsigned long end = [xmlData length];
        
        NSRange range = [xmlData rangeOfData:find options:0 range:NSMakeRange(start, end -start)];
        
        NSMutableArray *arr = [offsetXmlFile objectForKey:[NSNumber numberWithInt:sceneNo]];
        [arr addObject:[NSNumber numberWithLong: range.location]];
        xmlOffset = (unsigned long)range.location;
    }
    
    if ([elementName isEqualToString:SCENE]) {
        sceneNo++;
        [offsetXmlFile setObject: [[NSMutableArray alloc] init] forKey:[NSNumber numberWithInt:sceneNo]];
        
    }
    
    [self scaleAttrDict:&attributeDict attribute:elementName];
    
    /* Get the dictionary for the current level in the stack */
    NSMutableDictionary *parentDict = [dictionaryStack lastObject];
    
    /* if the current element is a switch, just copy the code and move on to its attributes */
    if ([elementName isEqualToString:SWITCH]){
        
        NSString *buttonPath = [[NSBundle mainBundle] pathForResource:xml2agcDictionary[elementName] ofType:AGC];
        NSError * error=nil;;
        
        NSString *jsonString = [NSString stringWithContentsOfFile:buttonPath encoding:NSUTF8StringEncoding error:&error];
        NSData * jsonData = [jsonString dataUsingEncoding:NSUTF8StringEncoding];
        NSMutableDictionary * parsedData = [NSJSONSerialization JSONObjectWithData:jsonData options:NSJSONReadingMutableContainers error:&error];
        
        
        [parentDict[CHILDREN] addObject:parsedData];
        [inheritanceStack addObject:SWITCH];
        
        return;
    }
    
    [self createDictionaryForElement:(NSString *) elementName
                          attributes:(NSMutableDictionary *)attributeDict
                          parentDict:( NSMutableDictionary *)parentDict];
    
  
}

- (void)parser:(NSXMLParser *)parser didEndElement:(NSString *)elementName namespaceURI:(NSString *)namespaceURI qualifiedName:(NSString *)qName
{
    
    
    if ([elementName isEqualToString:SWITCH]) {
        [inheritanceStack removeObject:SWITCH];
        return;
        
    }
    
    if ([xml2agcDictionary[elementName] isEqualToString:ART_SCENE]) {
        
        NSString *artboardNo = [NSString stringWithFormat:@"artboard%d", counterArtboards++] ;
        [[dictionaryStack lastObject] setObject:artboardNo forKey:REF];
        
    }
    
    
    if ([elementName isEqualToString:FRAME] && [[inheritanceStack lastObject] isEqualToString:SWITCH]){
        
        id value = [[[dictionaryStack lastObject] objectForKey:CHILDREN] lastObject];
        
        
        NSArray *strings = [SWITCH_TX componentsSeparatedByString:DOT];
        
        for (id key in [strings subarrayWithRange:NSMakeRange(1, [strings count] -2)]) {
            value = [value objectForKey:key];
        }
        
        id frame = [attributes objectForKey:FRAME_SIZE];
        [value setObject:[frame objectForKey:XARTBOARD] forKey:[strings lastObject]];
        
        strings = [SWITCH_TY componentsSeparatedByString:DOT];
        frame = [attributes objectForKey:FRAME_SIZE];
        
        [value setObject:[frame objectForKey:YARTBOARD] forKey:[strings lastObject]];
        
        return;
        
    }
    
    /* replace all $"smth" values with default ones */
    
    NSString *tempReplace = [NSString stringWithFormat:@"%@%@", SAVED_VALUE, elementName];
    
    if ([elementName isEqualToString:LABEL]){
        tempReplace = [NSString stringWithFormat:@"%@%@", SAVED_VALUE, xml2agcDictionary[elementName]];
    }
    
    NSMutableDictionary *parentDict = [dictionaryStack lastObject];
    NSString *textValue = nil;
    for (id key in xml2agcDictionary[tempReplace]){
        
        
        NSArray *strings = [key componentsSeparatedByString:DOT];
        
        
        id value = parentDict;
        
        for (id key1 in [strings subarrayWithRange:NSMakeRange(1, [strings count] - 2)]){
            
            value = [value objectForKey:key1];
            
        }
        textValue = [attributes objectForKey:[xml2agcDictionary[tempReplace] objectForKey:key]];
        [value setObject:[attributes objectForKey:[xml2agcDictionary[tempReplace] objectForKey:key]] forKey:[strings lastObject]];
    }
    
    
    id agcElement = [xml2agcDictionary objectForKey:elementName];
    if ([[xml2agcDictionary objectForKey:agcElement] isEqualToString:LIST]){
        
        NSInteger counter = [dictionaryStack count];
        id prevParent = dictionaryStack[counter - 2];
        [prevParent addEntriesFromDictionary:parentDict];
    }
    
    if ([elementName isEqualToString:TEXTFIELD] || [elementName isEqualToString:LABEL]){
        
        NSArray *strings = [[xml2agcDictionary objectForKey:LENGTH_DOT] componentsSeparatedByString:DOT];
        
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
    if ([elementName isEqualToString:LABEL])
        name =xml2agcDictionary[elementName];
    
    id def = [defaultValues objectForKey:name];
    for(id key in def){
        
        NSArray *strings = [key componentsSeparatedByString:DOT];
        
        id value = parentDict;
        
        for (id key1 in [strings subarrayWithRange:NSMakeRange(1, [strings count] - 2)]){
            value = [value objectForKey:key1];
        }
        
        id tempValue = [value objectForKey:[strings lastObject]];
        
        if (![tempValue isKindOfClass:[NSNumber class]] && [tempValue isKindOfClass:[NSString class]] && [[tempValue substringToIndex:1] isEqualToString:@"$"]){
            
            [value setObject:[def objectForKey:key] forKey:[strings lastObject]];
        }
        
    }
    
    if ([toInsertObjects count] && [elementName isEqualToString:VIEW]) {
        
        id prevParent = [dictionaryStack objectAtIndex:2];
        
        [prevParent addEntriesFromDictionary:[toInsertObjects objectAtIndex:0]];
        [toInsertObjects removeLastObject];
        
    }
    
    /* insert Objects from toInsertObjects */
    if ([elementName isEqualToString:TEXTFIELD] || [elementName isEqualToString:LABEL] ) {
        for (id key in toInsertObjects){
            NSInteger counter = [dictionaryStack count];
            id prevParent = dictionaryStack[counter - 2];
            
            [[prevParent objectForKey:CHILDREN ] insertObject:key atIndex:0];
            
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
