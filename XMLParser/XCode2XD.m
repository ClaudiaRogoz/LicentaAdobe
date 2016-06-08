//
//  XMLReader.m
//  XMLParser
//
//  Created by crogoz on 05/03/16.
//  Copyright © 2016 crogoz. All rights reserved.
//

#include <CommonCrypto/CommonDigest.h>
#import "XCode2XD.h"


@interface XCode2XD (Internal)

- (id)initWithError:(NSError **)error;
- (NSDictionary *)objectWithData:(NSData *)data;

@end


@implementation XCode2XD

#pragma mark -
#pragma mark Public methods


+ (NSDictionary *)dictionaryForXMLData:(NSData *)data resources:(NSString*)resourcesDir outFile:(NSString *)out_file xdPath:(NSString *) xdPath error:(NSError **)error
{
    XCode2XD *reader = [[XCode2XD alloc] initWithError:error];
    resourcesDir = [resourcesDir stringByAppendingPathComponent:STORYBOARD];
    
    [reader setResourcesPath:resourcesDir];
    [reader setXdPath:xdPath];
    
    [reader setXmlPath:out_file];
    
    NSMutableDictionary *rootDictionary = [[reader objectWithData:data] mutableCopy];
    NSMutableDictionary *interactions = [rootDictionary objectForKey:INTERACTIONS];
    NSMutableDictionary *idMap = [rootDictionary objectForKey:IDMAP];
    [rootDictionary removeObjectForKey:INTERACTIONS];
    [rootDictionary removeObjectForKey:IDMAP];
    
    //NSLog(@"interactions = %@ %@", interactions, idMap);
    NSString *finalArtboardName = [NSString stringWithFormat:ARTBOARDXML];
    [reader writeToFile:rootDictionary file:finalArtboardName computeSha:-1];
    [reader splitArtboards:rootDictionary interactions:interactions idMap:idMap];
    
    /* writes hashDict & offsetDict to a hidden file; needed for sync */
    NSString *hashFile = [NSString stringWithFormat:@"%@/%@%@%@",PREV_ART_PATH, HASH_PATH, DOT, JSON];
    NSString *offsetFile = [NSString stringWithFormat:@"%@/%@%@%@",PREV_ART_PATH, OFFSET_PATH, DOT, JSON];
    NSMutableDictionary *offsets = [reader getOffset];
    int length = (int)[[offsets allKeys] count];
    [offsets setObject:[reader getLastScene] forKey:[NSString stringWithFormat:@"%d", length + 1]];
    [reader writeToFile:[reader getHashdict] file:hashFile computeSha:-1];
    [reader writeToFile:offsets file:offsetFile computeSha:-1];
    
    return rootDictionary;
}

- (NSNumber *) getLastScene {
   
    NSString *allScenes = [NSString stringWithContentsOfFile:[self resourcesPath] encoding:NSASCIIStringEncoding error:NULL];
    NSRange range = [allScenes rangeOfString:@"</scenes>" ];
    lastScene = (unsigned long)range.location - 2;
    return [NSNumber numberWithLong:lastScene];

}
- (NSMutableDictionary *) getOffset {
    return offsetXmlFile;
}
- (NSMutableDictionary *) getHashdict {
    return hashArtboards;
}

-(NSString*) computeSha1:(NSString*)input
{
    const char *cstr = [input cStringUsingEncoding:NSUTF8StringEncoding];
    NSData *data = [NSData dataWithBytes:cstr length:input.length];
    
    uint8_t digest[CC_SHA1_DIGEST_LENGTH];
    
    CC_SHA1(data.bytes, (CC_LONG)data.length, digest);
    
    NSMutableString* output = [NSMutableString stringWithCapacity:CC_SHA1_DIGEST_LENGTH * 2];
    
    for(int i = 0; i < CC_SHA1_DIGEST_LENGTH; i++)
        [output appendFormat:@"%02x", digest[i]];
    
    return output;
    
}

- (void) addShaForString:(NSString *)jsonString artboardNo:(int)nr {
  
    NSString *jsonSha = [self computeSha1:jsonString];
    [hashArtboards setObject:[NSNumber numberWithInt:nr] forKey:jsonSha];
    
}

- (void) writeToFile:(NSDictionary*)xmlDictionary file:(NSString*) file computeSha:(int)sha {
    
    NSError *error;
    NSData *jsonData = [NSJSONSerialization dataWithJSONObject:xmlDictionary
                                                       options:NSJSONWritingPrettyPrinted
                                                         error:&error];
    
    if (! jsonData) {
        NSLog(@"Got an error: %@", error);
    } else {
        NSString *jsonString = [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
        
        NSString *mainBundle = [self getProjHomePath];
        
        NSString *outFile = [NSString stringWithFormat:@"%@/.%@", mainBundle, file];
        
        [[NSFileManager defaultManager] createFileAtPath:outFile contents:nil attributes:nil];
        [jsonString writeToFile:outFile atomically:YES encoding:NSUTF8StringEncoding error:nil];
        if (sha != -1) {
            [self addShaForString:jsonString artboardNo:sha];
        }
    }
}

-(NSString *) getProjHomePath {

    NSString *mainBundle = [[NSBundle mainBundle] bundlePath];
    for (int i = 0; i< PROJ_PATH; i++) {
        mainBundle = [mainBundle stringByDeletingLastPathComponent];
    }
    return mainBundle;
}

- (void) computeDict:(NSString *) name scene:(NSArray *) place_start dict:(NSMutableDictionary ** ) ids {
    id artboardList = *ids;
    
    if ([*ids objectForKey:[place_start firstObject]]) {
        artboardList = [*ids objectForKey:[place_start firstObject]];
    } else {
        artboardList = [[NSMutableDictionary alloc] init];
    }
   // NSLog(@"Set %@ %@", name, [place_start lastObject]);
    [artboardList setObject:name forKey:[place_start lastObject]];
    [*ids setObject:artboardList forKey:[place_start firstObject]];
}

- (NSMutableDictionary *) computeSegues:(NSMutableDictionary *) interactions usingIdMap:(NSMutableDictionary *) idMap {

    NSMutableDictionary *ids = [[NSMutableDictionary alloc] init];
    
   for (id start in interactions) {
        id end = [interactions objectForKey:start];
        NSArray *place_start = [idMap objectForKey:start];
        NSArray *place_end =[idMap objectForKey:end];
       
       [self computeDict:start scene:place_start dict:&ids];
       [self computeDict:end scene:place_end dict:&ids];
       
   }

    return ids;
}

- (void) getChildrenForArtbaord:(NSMutableDictionary **) dict {
    *dict = [[[[*dict objectForKey:CHILDREN] objectAtIndex:0]objectForKey:ART_SCENE] objectForKey:CHILDREN];
}


- (void) addTo:(NSMutableDictionary **) dict ids:(NSMutableDictionary *) idScenes {
    
    for (id scene in idScenes) {
        
        int currentScene = [scene intValue];
        id sceneId = [[idScenes objectForKey:scene] objectForKey:[NSNumber numberWithInt:0]];
        if (sceneId)
            [[[*dict objectForKey:CHILDREN] objectAtIndex:currentScene - 1] setObject:sceneId forKey:ID];
    }
    

}

- (NSMutableArray *)splitArtboards:(NSDictionary *)dictionary interactions:(NSMutableDictionary *) interactions idMap:(NSMutableDictionary *) idMap {

    NSMutableArray *rootArray = [[NSMutableArray alloc] init];
    NSMutableDictionary *segues = [self computeSegues:interactions usingIdMap:idMap];
    NSArray *place_start = [idMap objectForKey:homeArtboard];
    [self computeDict:homeArtboard scene:place_start dict:&segues];
    
    NSMutableDictionary *artboardsD = [dictionary objectForKey:ARTBOARDS];
    [self addTo:&dictionary ids:segues];

    [XDCreator createResourcesContent:artboardsD xdPath: [self xdPath]];
    [XDCreator createInteractionContent:interactions xdPath:[self xdPath] homeArtboard:homeArtboard];
    [XDCreator createMimetype:[self xdPath]];
    [XDCreator createManifest:[dictionary mutableCopy] xdPath:[self xdPath]];
    
    NSString *mainBundle = [self getProjHomePath];
    NSError *error;
    int nr = 1;
    
    for (id key in [artboardsD allKeys]) {
        
        NSMutableDictionary *tempArray = [self deepCopy: dictionary];
        NSString *artboardName = [NSString stringWithFormat:@"%@/%@%d%@%@",PREV_ART_PATH, ARTBOARD_FILE_PREFIX, nr, DOT, AGC];
        
        id children =  [[dictionary objectForKey:CHILDREN] objectAtIndex:(nr -1)];
        
        [tempArray setObject:[[NSMutableArray alloc] init] forKey:CHILDREN];
        [[tempArray objectForKey:CHILDREN] addObject:children];
        
        id currentScene = [segues objectForKey:[NSNumber numberWithInt:nr]];
        for (id assetOffset in currentScene) {
            id assetId = [currentScene objectForKey:assetOffset];
            
            if ([assetOffset intValue] != 0) {
                [[[[[[tempArray objectForKey:CHILDREN] objectAtIndex:0]objectForKey:ART_SCENE] objectForKey:CHILDREN] objectAtIndex:[assetOffset intValue] - 1] setObject:assetId forKey:ID];
            }
            
        }
        
        [XDCreator createArtworkContent:tempArray artboardNo:nr xdPath:[self xdPath]];
        id artboardNo = [artboardsD objectForKey:key];
        [tempArray  setValue:[[NSMutableDictionary alloc] init] forKey:ARTBOARDS];
        [[tempArray objectForKey:ARTBOARDS]  setValue:artboardNo forKey:key];
        
        /* create a temp directory where all the prev artboards can be stored */
        /* used for sync */
        NSString *artboardDirPath = [mainBundle stringByAppendingPathComponent:[NSString stringWithFormat:@".%@",PREV_ART_PATH]];
        if (![[NSFileManager defaultManager] fileExistsAtPath:artboardDirPath]) {
            BOOL success = [[NSFileManager defaultManager] createDirectoryAtPath:artboardDirPath withIntermediateDirectories:NO attributes:nil error:&error];
            
            if (success == false) {
                NSLog(@"[ERROR] cannot create path %@", [mainBundle stringByAppendingPathComponent:PREV_ART_PATH]);
                return nil;
            }
        }
        
        [self writeToFile:tempArray file:artboardName computeSha:nr];
        nr++;
    }
    
    [Helper createXdFile:[self xdPath]];
    
    [XDCreator releaseStorage:[self xdPath]];
    
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
    hashArtboards = [[NSMutableDictionary alloc] init];
    objectOffset = [[NSMutableDictionary alloc] init];
    interactionsDict = [[NSMutableDictionary alloc] init];
    idMapping = [[NSMutableDictionary alloc] init];
    
    sceneNo = 0;
    xmlOffset = 0;
    counterArtboards = 1;
    insertedRoot = false;
    hasAView = false;
    viewEnded = false;
    
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
        //NSLog(@"InteractionsDict = %@", interactionsDict);
        //NSLog(@"idMapping = %@", idMapping);
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
        [resultDict setObject:interactionsDict forKey:INTERACTIONS];
        [resultDict setObject:idMapping forKey:IDMAP];
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
    
    //NSLog(@"[XY] = %d %d", widthXMLArtboard, heightXMLArtboard);
    if ([[inheritanceStack lastObject] isEqualToString:CHILDREN]) {
        
        /* all artboards must have the same size in a single app */
        widthXMLArtboard = [[*attrScaleDict objectForKey:WIDTH] intValue];
        heightXMLArtboard = [[*attrScaleDict objectForKey:HEIGHT] intValue];
        return;
    }

    float xScaleFactor = (float)WIDTHIPH6/widthXMLArtboard;
    float yScaleFactor = (float)HEIGHTIPH6/heightXMLArtboard;
    if (widthXMLArtboard == 0) {
        xScaleFactor = 1;
    }
    if (heightXMLArtboard == 0)
        yScaleFactor = 1;
   // NSLog(@"XY = %d %d", widthXMLArtboard, heightXMLArtboard);
    for (id value in arrayWithSize) {
        float scaledValue = [[*attrScaleDict objectForKey:value] floatValue];
        //NSLog(@"ScaledValue = %f %d %f %f", scaledValue, sceneNo, xScaleFactor, yScaleFactor);
        if ([value isEqualToString:XARTBOARD]) {
            
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

-(id) deepCopy:(id) object {
    
    return [NSKeyedUnarchiver unarchiveObjectWithData:[NSKeyedArchiver archivedDataWithRootObject: object]];
    
}

-(NSNumber *)convertToNumber:(id) tempValue {

    NSNumber *nr = [[NSNumber alloc] init];
    if ([tempValue intValue])
        nr = [NSNumber numberWithInt:[tempValue intValue]];
    else if ([tempValue floatValue])
        nr = [NSNumber numberWithFloat:[tempValue floatValue]];
    else if ([tempValue isKindOfClass:[NSString class]] &&
             ([tempValue isEqualToString:@"0.0"] || [tempValue isEqualToString:@"0"]))
        nr = [NSNumber numberWithInt:0];
    else
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

    NSMutableDictionary *shapeAttr = [self deepCopy:attributes[RECTANGLE]];
    
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
    [attributes setObject:[NSNumber numberWithInt:textSize] forKey:SAVED_POINTSIZE];
    //NSLog(@"Text = %@", text);
    
    if ([text isKindOfClass:[NSNumber class]]) {
        NSNumber *nr = [NSNumber numberWithInt:[text intValue]];
        text = [nr stringValue];
    }
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


- (void) processImage:(NSDictionary *)attributeDict attributes:(NSMutableDictionary **) correctAttr {
    NSString *directory = [[[self resourcesPath] stringByDeletingLastPathComponent] stringByDeletingLastPathComponent];
    NSString *imageName = [Helper findFile: [attributeDict objectForKey:ISIMAGE] inPath:directory];
    NSArray *strings = [[xml2agcDictionary objectForKey:IMAGEVIEW_INV] componentsSeparatedByString:DOT];
    
    
    id value = *correctAttr;
    for (id key in [strings subarrayWithRange:NSMakeRange(0, [strings count] -1)]){
        value = [value objectForKey:key];
        
    }
    
    /* generate random values for uid */
    int num = arc4random() % 1000000;
    [value setObject:imageName forKey:[strings lastObject]];
    
    NSImage *image = [[NSImage alloc]initWithContentsOfFile:imageName];
    
    if (image == nil) {
        NSLog(@"[ERROR]Image %@ is nil", imageName);
    }
    
    [value setObject:[NSNumber numberWithInt:image.size.width] forKey:WIDTH];
    [value setObject:[NSNumber numberWithInt:image.size.height] forKey:HEIGHT];
    
    value = [[value objectForKey:META] objectForKey:UX];
    
    [value setObject: [NSString stringWithFormat:@"%d", num] forKey:UID];

}

-(void)transformAttributesForElement:(NSString *)elementName attributeDict:(NSMutableDictionary*)attributeDict
                           childDict:(NSMutableDictionary *)childDict parentDict:(NSMutableDictionary**)parentDict
{
    
    NSMutableDictionary *correctAttr = [self deepCopy:attributes[elementName]];
   
    //First level attributes
    for (id key in attributes[elementName]){
        
        id value = [attributes[elementName] objectForKey:key];
        
        if ([value isKindOfClass:[NSString class]]){
            if ([[value substringToIndex:1] isEqualToString:TOTRANSFORM]){
                
                NSInteger i = [value length] -1;
                value = [value substringWithRange:NSMakeRange(1, i)];
                
                NSString *tempSaved = [NSString stringWithFormat:@"%@%@", SAVED_VALUE, value];
                
                id tempValue = nil;
                if ([value isEqualToString:TEXT] && attributeDict[value]) {
                    tempValue = attributeDict[value];
                    //NSLog(@"Set for %@", tempValue);
                } else if (!attributeDict[value])
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
            
            NSString *directory = [[[self resourcesPath] stringByDeletingLastPathComponent] stringByDeletingLastPathComponent];
            NSString *imageName = [Helper findFile: [attributeDict objectForKey:ISIMAGE] inPath:directory];
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
                NSLog(@"[ERROR]Image %@ is nil", imageName);
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
        id lastObject =  [self deepCopy: [dictionaryStack lastObject]];
        
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
    //NSLog(@"ChildDict = %@ %@", dictionaryStack, childDict);
    [dictionaryStack addObject:childDict];

}

-(void)createDictionaryForElement:(NSString *) elementName attributes:(NSMutableDictionary *) attributeDict parentDict:( NSMutableDictionary *)parentDict{

    /* Create the child dictionary for the new element, and initilaize it with the attributes */
    NSMutableDictionary *childDict = [NSMutableDictionary dictionary];
    
    NSMutableDictionary* tempDict = [[NSMutableDictionary alloc] init];
    tempDict[HREF] = GRAPHIC_CONTENT;

    if (![xml2agcDictionary objectForKey:elementName] && [elementName isEqualToString:XML_STATE] && [attributeDict objectForKey:ISIMAGE] != nil) {
        //NSLog(@"dictionaryStack %@", dictionaryStack);
        id transform = [[dictionaryStack lastObject] objectForKey:TRANSFORM];
        id frame_size = [attributes objectForKey:FRAME_SIZE];
        //NSLog(@"STATE = %@ %@", [dictionaryStack lastObject], [attributes objectForKey:FRAME_SIZE]);
        id tx = [transform objectForKey:TX];
        id ty = [transform objectForKey:TY];
        NSMutableDictionary *dict = [self deepCopy:[attributes objectForKey:IMAGEVIEW]];
        id value = [dict objectForKey:TRANSFORM];
        [value setObject:tx forKey:TX];
        [value setObject:ty forKey:TY];
        value = [dict objectForKey:SHAPE];
        [value setObject:[frame_size objectForKey:WIDTH] forKey:WIDTH];
        [value setObject:[frame_size objectForKey:HEIGHT] forKey:HEIGHT];
        value = [[[dict objectForKey:STYLE] objectForKey:FILL] objectForKey:PATTERN];
    
        [self processImage:attributeDict attributes:&dict];
        //[value setObject:[attributeDict objectForKey:ISIMAGE] forKey:HREF];
        parentDict = dict;
        //NSLog(@"Stack = %@", dict);
       
    }
    
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
            
            NSMutableDictionary *shapeAttr = [self deepCopy:attributes[BACKGROUND]];
            
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

    if ([elementName isEqualToString:DOCUMENT]) {
        homeArtboard = [attributeDict objectForKey:HOME_ARTBOARD];
    
    }
    
    if ([elementName isEqualToString:SEGUE] && [attributeDict objectForKey:DESTINATION]) {
        
        [interactionsDict setObject:[attributeDict objectForKey:DESTINATION] forKey:lastId];
    }

    if ([attributeDict objectForKey:ID]) {
        lastId = [attributeDict objectForKey:ID];
        //TODO!! here extend with the other subViews types
        if ([elementName isEqualToString:BUTTON] || [elementName isEqualToString:LABEL] || [elementName isEqualToString:IMAGEVIEW] ||
            [elementName isEqualToString:IMAGEVIEW] || [elementName isEqualToString:TEXTFIELD]) {
            ++childScene;

            [idMapping setObject:@[[NSNumber numberWithInt:sceneNo], [NSNumber numberWithInt:childScene]] forKey:lastId];
        } else if ([elementName isEqualToString:VIEW_CONTROLLER]) {

            [idMapping setObject:@[[NSNumber numberWithInt:sceneNo], [NSNumber numberWithInt:0]] forKey:lastId];
        }
    }
    
    NSString *tagName = [NSString stringWithFormat:@"<%@ ", elementName];
    /*initializes things for a neaw mutableString */
    if ([elementName isEqualToString:STRING] || [elementName isEqualToString:MUTABLE_STRING]){
        attributes[SAVED_TEXT] = [[NSString alloc] init];

    }
    if ([elementName isEqualToString:LABEL]) {
        attributes[SAVED_LINES] = [attributeDict objectForKey:NO_LINES];
        //NSLog(@"Text = %@\n Parent=%@ \n Inhgerit %@", [attributeDict objectForKey:@"text"], [dictionaryStack lastObject], [inheritanceStack lastObject]);
    }
    if ([elementName isEqualToString:VIEW]) {
        if (!hasAView)
            hasAView = true;
        else {
            [inheritanceStack addObject:CHILDREN];
            return;
        }
    }
    
    if ([elementName isEqualToString:SCENE]) {
        sceneNo++;
        childScene = 0;
        NSData *find = [tagName dataUsingEncoding:NSUTF8StringEncoding];
        unsigned long start = xmlOffset + 1;
        unsigned long end = [xmlData length];
        
        NSRange range = [xmlData rangeOfData:find options:0 range:NSMakeRange(start, end -start)];
        
        NSMutableArray *arr = [offsetXmlFile objectForKey:[NSNumber numberWithInt:sceneNo]];
        [arr addObject:[NSNumber numberWithLong: range.location]];
        xmlOffset = (unsigned long)range.location;
        hasAView = false;
        [offsetXmlFile setObject: [NSNumber numberWithLong:xmlOffset] forKey:[NSString stringWithFormat:@"%d", sceneNo]];
    }

    
    [self scaleAttrDict:&attributeDict attribute:elementName];
    
    /* Get the dictionary for the current level in the stack */
    NSMutableDictionary *parentDict = [dictionaryStack lastObject];
    
    //NSLog(@"[%@] ParentDict = %@", elementName, parentDict);
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

-(int) isLiteral:(unichar) value {

    return value != ' ' || value == '\n' || value == '\t';
}

- (void) setTextAttributes:(NSArray *)strings numberOfLines:(int) nLines textValue:(NSString *)textValue
                      dict:(NSMutableDictionary **) parentDict length:(int) length{
    long from = 0;
    
    NSFont *font = [NSFont systemFontOfSize:[attributes[SAVED_POINTSIZE]intValue]];
    
    CGRect idealFrame = [textValue boundingRectWithSize:CGSizeMake(CGFLOAT_MAX, CGFLOAT_MAX)
                                                options:NSStringDrawingUsesLineFragmentOrigin
                                             attributes:@{ NSFontAttributeName:font }
                                                context:nil];
    int yOffset = idealFrame.size.height;
    for (int i = 0; i<nLines; i++) {
        id value = *parentDict;
        for (id key in [strings subarrayWithRange:NSMakeRange(1, [strings count] - 2)]){
            if ([value isKindOfClass:[NSMutableDictionary class]])
            value = [value objectForKey: key];
            else
            value = value[i][key][0][0]; // For lines only
        }
        NSArray *fromTo = [[strings lastObject] componentsSeparatedByString:TOTRANSFORM];
        
        long to = from + length;
        long left = to;
        long right = to;
        while (left > 0 && [self isLiteral:[textValue characterAtIndex:left - 1]] ) {
            left--;
        }
        
        while (right <= textValue.length && [self isLiteral:[textValue characterAtIndex:right - 1]] ) {
            right++;
        }
        
        to = (left < right && left != 0) ? left : right;
        
        /* set from-to offsets */
        [value setObject:[NSNumber numberWithLong:from] forKey:[fromTo firstObject]];
        [value setObject:[NSNumber numberWithLong:to] forKey:[fromTo objectAtIndex:1]];
        [value setObject:[NSNumber numberWithLong:yOffset * i] forKey:[fromTo lastObject]];
        
        from = to;
    }

}

-(void) processTextFields:(NSString *)textValue name:(NSString *)elementName attributes:(NSMutableDictionary **)parentDict {

    //NSLog(@"Process textValue = %@ %@", textValue, elementName);
    if (!([elementName isEqualToString:TEXTFIELD] || [elementName isEqualToString:LABEL] || [elementName isEqualToString:BUTTON_TEXT])) {
        return;
    }
    
    if ([textValue isKindOfClass:[NSNumber class]]) {
        NSNumber *nr = [NSNumber numberWithInt:[textValue intValue]];
        textValue = [nr stringValue];
    }
    
    NSArray *strings = [[xml2agcDictionary objectForKey:LENGTH_DOT] componentsSeparatedByString:DOT];
    
    long length = textValue.length;
    id numberOfLines = attributes[SAVED_LINES];
    int nLines = 1;
    
    if (attributes[SAVED_LINES]) {
        nLines = [numberOfLines intValue];
        NSArray *newParagraphs = [[xml2agcDictionary objectForKey:PARAGRAPHS_DOT] componentsSeparatedByString:DOT];
        id value = *parentDict;
        
        for (id key in newParagraphs) {
            if ([value isKindOfClass:[NSMutableDictionary class]])
            value = [value objectForKey:key];
            else
            value = [value objectAtIndex:[key intValue]];
        }
        for (int paragraph=1; paragraph < [numberOfLines intValue]; paragraph++) {
            NSMutableDictionary *newPara = [self deepCopy:[xml2agcDictionary objectForKey:SAVED_LINES]];
            [value addObject:newPara];
            
        }
        
        /* the length of a line should be ~length */
        length = length / [attributes[SAVED_LINES] intValue];
        length = length * WIDTH_XD_ARTBOARD/ WIDTH_XML_ARTBOARD;
    }
    
    [self setTextAttributes:strings
              numberOfLines:nLines
                  textValue:textValue
                       dict:parentDict
                     length:(int)length];

}

-(void) processDefaultValues:(NSMutableDictionary*)def dict:(NSMutableDictionary **)parentDict{
    for(id key in def){
        
        NSArray *strings = [key componentsSeparatedByString:DOT];
        
        id value = *parentDict;
        
        for (id key1 in [strings subarrayWithRange:NSMakeRange(1, [strings count] - 2)]){
            value = [value objectForKey:key1];
        }
        
        id tempValue = [value objectForKey:[strings lastObject]];
        
        if (![tempValue isKindOfClass:[NSNumber class]] && [tempValue isKindOfClass:[NSString class]] && [[tempValue substringToIndex:1] isEqualToString:TOTRANSFORM]){
            
            [value setObject:[def objectForKey:key] forKey:[strings lastObject]];
        }
        
    }


}

-(BOOL) processSwitchFrame:(NSString *)elementName {
    
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
        return true;
    }
    return false;
}

- (void) insertObjects:(NSString *)elementName {
    
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


}

- (void) replaceText:(NSString *)elementName textValue:(NSString **)textValue dict:(NSMutableDictionary**) parentDict {

    NSString *tempReplace = [NSString stringWithFormat:@"%@%@", SAVED_VALUE, elementName];
    
    if ([elementName isEqualToString:LABEL]){
        tempReplace = [NSString stringWithFormat:@"%@%@", SAVED_VALUE, xml2agcDictionary[elementName]];
    }

    
    for (id key in xml2agcDictionary[tempReplace]){
        
        NSArray *strings = [key componentsSeparatedByString:DOT];
        
        
        id value = *parentDict;
        
        for (id key1 in [strings subarrayWithRange:NSMakeRange(1, [strings count] - 2)]){
            
            value = [value objectForKey:key1];
            
        }
        *textValue = [attributes objectForKey:[xml2agcDictionary[tempReplace] objectForKey:key]];
        
        id valueForKey = [attributes objectForKey:[xml2agcDictionary[tempReplace] objectForKey:key]];
        if (!valueForKey) {
            valueForKey = @"";
        }
        
        [value setObject:valueForKey forKey:[strings lastObject]];
    }
    
    
    id agcElement = [xml2agcDictionary objectForKey:elementName];
    if ([[xml2agcDictionary objectForKey:agcElement] isEqualToString:LIST]){
        
        NSInteger counter = [dictionaryStack count];
        id prevParent = dictionaryStack[counter - 2];
        [prevParent addEntriesFromDictionary:*parentDict];
    }

}

- (void)parser:(NSXMLParser *)parser didEndElement:(NSString *)elementName namespaceURI:(NSString *)namespaceURI qualifiedName:(NSString *)qName
{
    
    if ([elementName isEqualToString:SWITCH]) {
        [inheritanceStack removeObject:SWITCH];
        return;
        
    }
    if ([elementName isEqualToString:VIEW]) {
        if (!viewEnded)
            viewEnded = true;
        else {
            [inheritanceStack removeLastObject];
            return;
        }
    }
    if ([elementName isEqualToString:SCENE]) {
        viewEnded = false;
        hasAView = false;
        
        
    }
    
    if ([xml2agcDictionary[elementName] isEqualToString:ART_SCENE]) {
        
        NSString *artboardNo = [NSString stringWithFormat:@"artboard%d", counterArtboards++] ;
        [[dictionaryStack lastObject] setObject:artboardNo forKey:REF];
        
    }
    
    BOOL ret = [self processSwitchFrame:elementName];
    if (ret)
        return;
    
    /* replace all $"smth" values with default ones */
    NSMutableDictionary *parentDict = [dictionaryStack lastObject];
    NSString *textValue = nil;
    [self replaceText:elementName textValue:&textValue dict:&parentDict];
    
    /* create paragraphs (if needed) */
    [self processTextFields:textValue name:elementName attributes:&parentDict];

    //default Values
    id name = elementName;
    if ([elementName isEqualToString:LABEL])
        name =xml2agcDictionary[elementName];
    id def = [defaultValues objectForKey:name];
    [self processDefaultValues:def dict:&parentDict];
    
    [self insertObjects:elementName];
    
    
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
    NSString *newString;
    if (string != nil) /* we have a string tag (multiline label)*/ {
        newString = [string stringByReplacingOccurrencesOfString:@"  " withString:@""];
        newString = [newString stringByReplacingOccurrencesOfString:@" " withString:@""];
        newString = [newString stringByReplacingOccurrencesOfString:@"\n" withString:@""];
        
        if ([newString length]) {
            NSString *prevSavedText = attributes[SAVED_TEXT];
            
            if (prevSavedText) {
                NSString *tmp = string;
                string = [prevSavedText stringByAppendingString:tmp];
            }
            
            [attributes setObject:string forKey:SAVED_TEXT];
            [textInProgress appendString:string];
        }
        
    }

}

- (void)parser:(NSXMLParser *)parser parseErrorOccurred:(NSError *)parseError
{
    
}

@end
