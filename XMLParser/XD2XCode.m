//
//  XMLGenerator.m
//  XMLParser
//
//  Created by crogoz on 07/04/16.
//  Copyright © 2016 crogoz. All rights reserved.
//

#import "XD2XCode.h"

#import <Foundation/Foundation.h>
#import <CoreData/CoreData.h>
#include "XDCreator.h"


@import AppKit;


@implementation XD2XCode

+ (void) readTemplateUsingXML:(NSString *)xdPath writeTo:(NSString*)outXmlPath {
    NSError *error;
    NSMutableDictionary *agcTemplate = [[NSMutableDictionary alloc] init];
    NSString *xmlPath = [[outXmlPath stringByDeletingLastPathComponent] stringByDeletingLastPathComponent];
    XD2XCode *gen = [[XD2XCode alloc] initWithError:&error];
    [gen initWithSchemas:XML_SCENE_X];
    [gen setXdPath:xdPath];
    [gen setXmlPath:xmlPath];
    [gen setOutXmlPath:outXmlPath];
    agcTemplate = [gen getXdDictionary];
    [gen getXmlForAgcObject:agcTemplate];
}

+(NSString *) generateXmlForTag:(NSDictionary*)agcDict xdPath:(NSString *)xdPath xmlPath:(NSString *)xmlPath sceneNo:(int) currentScene {
    NSError *error;
    XD2XCode *gen = [[XD2XCode alloc] initWithError:&error];
    [gen setXdPath:xdPath];
    [gen setXmlPath:xmlPath];
    [gen initWithSchemas:XML_SCENE_X  + WIDTH_XML_ARTBOARD_RETINA55 * 1.1 * currentScene];
    NSString *xmlTemplate = [gen getXmlForAgcObject:agcDict];
    if (!xmlTemplate) {
        NSLog(@"[ERROR] No translation can be achieved at the moment for %@", [agcDict objectForKey:TYPE]);
        return nil;
    }
    return xmlTemplate;
}

-(void) addChild:(NSMutableDictionary *)child to:(NSMutableDictionary **) agcDict{
    [[*agcDict objectForKey:CHILDREN ] addObject:child];
}

- (void) addArtboardsToAgc:(NSMutableDictionary **) agcDict usingPath:(NSString *) path{
    NSError *error;
    NSData *data = [NSData dataWithContentsOfFile:path];
    NSMutableDictionary *artboards =  [NSJSONSerialization JSONObjectWithData:data options:NSJSONReadingMutableContainers error:&error];
    id array = [artboards objectForKey:ARTBOARDS];
    [*agcDict setObject:array forKey:ARTBOARDS];
}

-(NSString *) appendPathComponents:(NSArray *) array topath:(NSString *) path {
    NSString *finalPath = [NSString stringWithFormat:@"%@", path];
    for (id component in array) {
        finalPath = [finalPath stringByAppendingPathComponent:component];
    }
    return finalPath;
}
- (NSMutableDictionary *) getXdDictionary {
    NSError *error;
    NSString *mainBundle = [self getProjHomePath];
    NSString *unzipped_xd = [mainBundle stringByAppendingPathComponent:XD_EXPORT_PATH];
    [Helper unzipXD:[self xdPath] atPath:unzipped_xd];
    NSMutableDictionary * agcTemplate = [[NSMutableDictionary alloc] init];
    NSString *artworkDir = [unzipped_xd stringByAppendingPathComponent:ARTWORK];
    NSMutableArray *findAllFiles = [Helper findAllFiles:GRAPHIC inPath:artworkDir];
    NSString *firstFile = [findAllFiles objectAtIndex:0];
    [findAllFiles removeObjectAtIndex:0];
    NSString *resources = [self appendPathComponents:@[ZIP_RESOURCES, GRAPHICS, GRAPHIC] topath:unzipped_xd];
    [self addArtboardsToAgc:&agcTemplate usingPath:resources];
    NSData *data = [NSData dataWithContentsOfFile:firstFile];
    agcTemplate =  [NSJSONSerialization JSONObjectWithData:data options:NSJSONReadingMutableContainers error:&error];
    [self addArtboardsToAgc:&agcTemplate usingPath:resources];
    for (id file in findAllFiles) {
        data = [NSData dataWithContentsOfFile:file];
        NSMutableDictionary *temp = [NSJSONSerialization JSONObjectWithData:data options:NSJSONReadingMutableContainers error:&error];
        id value = [[temp objectForKey:CHILDREN] objectAtIndex:0];
        [self addChild:[self deepCopy:value] to:&agcTemplate];
    }
    NSString *interactionsJson = [INTERACTIONS stringByAppendingPathComponent:[INTERACTIONS stringByAppendingPathExtension:JSON]];
    NSString *interactionsDir = [unzipped_xd stringByAppendingPathComponent:interactionsJson];
    data = [NSData dataWithContentsOfFile:interactionsDir];
    interactionsDict = [NSJSONSerialization JSONObjectWithData:data options:NSJSONReadingMutableContainers error:&error];
    homeArtboard = [interactionsDict objectForKey:START_ARTBOARD];
    return agcTemplate;
}

-(NSString *) getClipboardData {
     NSPasteboard *pasteboard = [NSPasteboard generalPasteboard];
     return [pasteboard stringForType:SPARKLERCLIPBOARD];
}

-(void) initWithSchemas:(long) sceneValue {
    NSError *error;
    NSBundle *thisBundle = [NSBundle bundleForClass:[self class]];
    NSString *def = [thisBundle pathForResource:DEF_PATH ofType:JSON];
    NSString *rule = [thisBundle pathForResource:RULES_PATH ofType:JSON];
    NSData *defData = [NSData dataWithContentsOfFile:def];
    NSData *ruleData = [NSData dataWithContentsOfFile:rule];
    NSMutableDictionary *defDictionary = [NSJSONSerialization JSONObjectWithData:defData options:NSJSONReadingMutableContainers error:&error];
    NSDictionary *ruleDictionary = [NSJSONSerialization JSONObjectWithData:ruleData options:NSJSONReadingMutableContainers error:&error];
    sceneOffset = sceneValue;
    [self releaseResources];
    [self initializeWithDefs:defDictionary rules:ruleDictionary];
}

- (void) releaseResources {
    NSString *mainBundle = [self getProjHomePath];
    NSString *unzipped_xd = [mainBundle stringByAppendingPathComponent:XD_EXPORT_PATH];
    NSLog(@"Removing %@ ....", unzipped_xd);
    [[NSFileManager defaultManager] removeItemAtPath:unzipped_xd error:nil];
}

-(NSString *) getProjHomePath {
    NSString *mainBundle = [[NSBundle mainBundle] bundlePath];
    for (int i = 0; i< PROJ_PATH; i++) {
        mainBundle = [mainBundle stringByDeletingLastPathComponent];
    }
    return mainBundle;
}

-(id) deepCopy:(id) object {
    return [NSKeyedUnarchiver unarchiveObjectWithData:[NSKeyedArchiver archivedDataWithRootObject: object]];
}

- (void) generateSVGFile:(NSString *)filePath FromLine:(NSString *)pathString usingViewBox: (NSString *) viewBox {
    NSError *error;
    NSString *svgTemplate = [[NSBundle mainBundle] pathForResource:LINE_TEMPLATE ofType:SVG];
    NSMutableString *path = [NSMutableString stringWithContentsOfFile:svgTemplate encoding:NSUTF8StringEncoding error:&error];
    NSRange range = [path rangeOfString:SVG_VIEWBOX];
    long start = range.location + SVG_FILL_LEN;
    start = range.location + [SVG_VIEWBOX length] + 1;
    long end = [path length] - start;
    NSRange finalRange = [path rangeOfString:SVG_INFO_END options:0 range:NSMakeRange(start, end)];
    [path replaceCharactersInRange:NSMakeRange(start, finalRange.location - start) withString:viewBox];
    /* translation replacement */
    range = [path rangeOfString:SVG_LINE];
    start = range.location + [SVG_LINE length];
    end = [path length] - start;
    finalRange = [path rangeOfString:SVG_END options:0 range:NSMakeRange(start, end)];
    [path replaceCharactersInRange:NSMakeRange(start, finalRange.location - start) withString:pathString];
    NSData *fileContents = [path dataUsingEncoding:NSUTF8StringEncoding];
    /* write to file */
    [[NSFileManager defaultManager] createFileAtPath:filePath
                                            contents:fileContents
                                          attributes:nil];
}

- (void) generateSVGFile:(NSString *)filePath FromPath:(NSString *)pathString usingFill:(NSString *)hex
           usingViewBox:(NSString *) viewBox translation: (NSString *) translation {
    NSError *error;
    NSString *svgTemplate = [[NSBundle mainBundle] pathForResource:SVG_TEMPLATE ofType:SVG];
    NSMutableString *path = [NSMutableString stringWithContentsOfFile:svgTemplate encoding:NSUTF8StringEncoding error:&error];
    long len = [path length];
    /* color transformation */
    NSRange range = [path rangeOfString:SVG_FILL];
    long start = range.location + SVG_FILL_LEN;
    if ([hex isEqualToString:NONE])
        --start;
    long end = len - start;
    NSRange finalRange =  [path rangeOfString:SVG_FILL_END options:0 range:NSMakeRange(start, end)];
    [path replaceCharactersInRange:NSMakeRange(start, finalRange.location - start) withString:hex];
    /* path transformation */
    len = [path length];
    range = [path rangeOfString:SVG_INFO];
    start = range.location + SVG_INFO_LEN;
    end = len - start;
    finalRange = [path rangeOfString:SVG_INFO_END options:0 range:NSMakeRange(start, end)];
    [path replaceCharactersInRange:NSMakeRange(start, finalRange.location - start) withString:pathString];
    /* viewBox replacement */
    range = [path rangeOfString:SVG_VIEWBOX];
    start = range.location + [SVG_VIEWBOX length] + 1;
    end = [path length] - start;
    finalRange = [path rangeOfString:SVG_INFO_END options:0 range:NSMakeRange(start, end)];
    [path replaceCharactersInRange:NSMakeRange(start, finalRange.location - start) withString:viewBox];
    /* translation replacement */
    range = [path rangeOfString:SVG_TRANSLATE];
    start = range.location + [SVG_TRANSLATE length];
    end = [path length] - start;
    finalRange = [path rangeOfString:SVG_INFO_END options:0 range:NSMakeRange(start, end)];
    [path replaceCharactersInRange:NSMakeRange(start, finalRange.location - start) withString:translation];
    end = [path length] - start;
    NSData *fileContents = [path dataUsingEncoding:NSUTF8StringEncoding];
    NSLog(@"Writing to .... %@", filePath);
    /* write to file */
    [[NSFileManager defaultManager] createFileAtPath:filePath
                                            contents:fileContents
                                          attributes:nil];
}

-(void)initializeWithDefs:(NSDictionary*)defDict rules:(NSDictionary*)ruleDict {
    agcToXmlTemplate = [defDict mutableCopy];
    translationDict = [ruleDict mutableCopy];
    resourcesDict = [[NSMutableString alloc] init];
    uuidMap = [[NSMutableDictionary alloc] init];
    uuidViewMap = [[NSMutableDictionary alloc] init];
    uniqueList = [[NSMutableDictionary alloc] init];
    transformObjects = [[NSMutableDictionary alloc] init];
    transformObjects[SIZE] = [[NSMutableDictionary alloc] init];
    transformObjects[SIZE][XARTBOARD] = [NSNumber numberWithInt:1];
    transformObjects[SIZE][YARTBOARD] = [NSNumber numberWithInt:1];
    transformObjects[SCALE] = [[NSMutableDictionary alloc] init];
    transformObjects[SCALE][WIDTH] = [NSNumber numberWithInt:1];
    transformObjects[SCALE][HEIGHT] = [NSNumber numberWithInt:1];
    transformObjects[SCALE][FRAMED] = [NSNumber numberWithInt:1];
    transformObjects[SCALE][IMAGEVIEW] = [NSNumber numberWithInt:1];
    transformObjects[SCALE][TEXT_AREA] = [NSNumber numberWithInt:1];
    transformObjects[COLOR] = [[NSMutableDictionary alloc] init];
    transformObjects[COLOR][RED] = [NSNumber numberWithInt:1];
    transformObjects[COLOR][GREEN] = [NSNumber numberWithInt:1];
    transformObjects[COLOR][BLUE] = [NSNumber numberWithInt:1];
    sceneNo = 0;
    transformSize = true;
}

- (NSString *)hexStringForColor:(NSDictionary *)value {
    int r = [[value objectForKey:XML_RED] intValue];
    int g = [[value objectForKey:XML_GREEN] intValue];
    int b = [[value objectForKey:XML_BLUE] intValue];
    NSString *hexString=[NSString stringWithFormat:@"%02X%02X%02X", (int)(r ), (int)(g ), (int)(b )];
    return hexString;
}

-(NSString *) computeAgcTag: (NSString *) initValue dict:(NSDictionary *)agcDict {
    initValue = [initValue substringFromIndex:1];
    NSArray *array = [initValue componentsSeparatedByString:DOT];
    id value = agcDict;
    for (id key in array) {
        if ([key isEqualToString:COUNT]) {
            return [ NSString stringWithFormat:@"%d", (int)[value count]];
        }
        if ([key isEqualToString:LINES])
            value = [value objectAtIndex:0];
        else
            value = [value objectForKey:key];
    }
    if ([value isKindOfClass:[NSDictionary class]]) {
        /* only in case of color transformation to hex */
        return [self hexStringForColor:value];
    }
    return value;
}

-(NSString *) getDestinationFor:(NSString *) agcId interactions:(NSMutableDictionary *)interactions {
    return [[[[interactions objectForKey:agcId] objectAtIndex:0] objectForKey:PROPERTIES] objectForKey:DESTINATION];
}


- (NSString *) computeUUIDValue: (NSDictionary *) agcDict {
    //generate a random value; needed for id
    id interactions = [interactionsDict objectForKey:INTERACTIONS];
    NSString *uuid = [self getUniqueString];
    id agcId = [agcDict objectForKey:ID];
    if (agcId != nil) {
        [uuidMap setObject:uuid forKey:agcId];
    }
    if ([interactions objectForKey:agcId]) {
        transformInteraction = true;
        destinationId = [self getDestinationFor:agcId interactions:interactions];
    } else {
        transformInteraction = false;
    }
    return [self getUniqueString];
}

-(NSString *) computeMultilineLabel:(NSString *) initValue forDict:(NSDictionary *) agcDict {
    NSRange range = [initValue rangeOfString:GETMAX];
    NSArray *max2 = [[initValue substringFromIndex:range.location + GETMAX.length + 1] componentsSeparatedByString:SPACE];
    id first = [self computeValue:[max2 objectAtIndex:0] forDict:agcDict];
    id second = [self computeValue:[max2 objectAtIndex:1] forDict:agcDict];
    int ret = MAX([first intValue], [second intValue]);
    return [NSString stringWithFormat:@"%d", ret];
}

-(NSString *) computeLine:(NSString *) initValue forDict:(NSDictionary *) agcDict {
    NSString *pngName;
    NSRange range = [initValue rangeOfString:LINE];
    NSArray *paths = [[initValue substringFromIndex:range.location + LINE.length + 1] componentsSeparatedByString:SPACE];
    NSString *fileName = [self computeValue:[paths objectAtIndex:0] forDict:agcDict];
    NSString *fillColor = [self computeValue:[paths objectAtIndex:1] forDict:agcDict];
    NSString *stroke = [self computeValue:[paths objectAtIndex:2] forDict:agcDict];
    id transform = [agcDict objectForKey:[[paths objectAtIndex:3]substringFromIndex:1]];
    id shape = [agcDict objectForKey:[[paths objectAtIndex:4]substringFromIndex:1]];
    float x1 = [[shape objectForKey:X1] floatValue];
    float x2 = [[shape objectForKey:X2] floatValue];
    float y1 = [[shape objectForKey:Y1] floatValue];
    float y2 = [[shape objectForKey:Y2] floatValue];
    float box_mx = MIN(x1, x2);
    float box_my = MIN(y1, y2);
    float box_Mx = MAX(x1, x2);
    float box_My = MAX(y1, y2);
    if (box_Mx - box_mx == 0)
        box_Mx += [stroke intValue];
    if (box_My - box_my == 0)
        box_My += [stroke intValue];
    NSString *viewBox = [NSString stringWithFormat:@"%f %f %f %f", box_mx, box_my, box_Mx - box_mx, box_My - box_my];
    path_x = [[transform objectForKey:TX] intValue] + box_mx;
    path_y = [[transform objectForKey:TY] intValue] + box_my;
    path_width = box_Mx - box_mx;
    path_height =  box_My - box_my;
    NSString *style = [NSString stringWithFormat:@"stroke:#%@;stroke-width:%d", fillColor, [stroke intValue]];
    NSString *line = [NSString stringWithFormat:@"x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\"", x1, y1, x2, y2];
    NSString *pathLine = [NSString stringWithFormat:@"%@ style=\"%@\"",line, style];
    fileName = [[fileName stringByAppendingString:[Helper computeSha1:pathLine]] stringByAppendingPathExtension:SVG];
    fileName = [[self imagesPath] stringByAppendingPathComponent:fileName];
    if ([Helper fileExists:fileName]) {
        pngName = [Helper transformToPngFileName:fileName];
    } else {
        [self generateSVGFile:fileName FromLine:pathLine usingViewBox:viewBox];
        /* convert the svg file into a png file */
        pngName = [Helper convertSvgToPng:fileName withFill:fillColor strokeColor:fillColor strokeWidth:0 opacity:0];
    }
    return  pngName;
}


- (id) getXYFromPath:(NSString *) pathStr {
    return [[[[[[[[[pathStr componentsSeparatedByString:@"L"] componentsJoinedByString:@" "]
                           componentsSeparatedByString:@"M"] componentsJoinedByString:@" "]
                         componentsSeparatedByString:@"C"] componentsJoinedByString:@" "]
                       componentsSeparatedByString:@"Z"] componentsJoinedByString:@""]
                     componentsSeparatedByString:@" "];

}

- (void) getMinMaxXY:(id) maxMinPath minx:(float*) minx maxx:(float*) maxx miny:(float*)miny maxy:(float*) maxy {
    for (int i = 0; i< [maxMinPath count]; ) {
        if ([[maxMinPath objectAtIndex:i] isEqualToString:@""] &&
            i + 1 < [maxMinPath count] &&
            [[maxMinPath objectAtIndex:i + 1] isEqualToString:@""]) {
            i += 2;
            continue;
        } else if ([[maxMinPath objectAtIndex:i] isEqualToString:@""]) {
            i += 1;
            continue;
        }
        float x = [[maxMinPath objectAtIndex:i] floatValue];
        float y = [[maxMinPath objectAtIndex:i +1] floatValue];
        *minx = MIN(x, *minx);
        *maxx = MAX(x, *maxx);
        *miny = MIN(y, *miny);
        *maxy = MAX(y, *maxy);
        i += 2;
    }
}

-(NSString *) computePath:(NSString *) initValue forDict:(NSDictionary *) agcDict {
    NSRange range = [initValue rangeOfString:PATH];
    NSArray *paths = [[initValue substringFromIndex:range.location + PATH.length + 1] componentsSeparatedByString:SPACE];
    NSString *pathStr = [self computeValue:[paths objectAtIndex:0] forDict:agcDict];
    NSString *uniqName = [Helper computeSha1:pathStr];
    NSString *fileName = [[self computeValue:[paths objectAtIndex:1] forDict:agcDict] stringByAppendingString:uniqName];
    id type = [self computeValue:[paths objectAtIndex:2] forDict:agcDict];
    NSString *hexColor = [self computeValue:[paths objectAtIndex:3] forDict:agcDict];
    if ([type isEqualToString:NONE])
        hexColor = type;
    id transform = [agcDict objectForKey:[[paths objectAtIndex:4]substringFromIndex:1]];
    id strokeColor = [self computeValue:[paths objectAtIndex:5] forDict:agcDict];
    int colorWidth = [[self computeValue:[paths objectAtIndex:6]  forDict:agcDict] intValue];
    float opacity = [[self computeValue:[paths objectAtIndex:7] forDict:agcDict] floatValue];
    int transformTx = [[transform objectForKey:TX] intValue];
    int transformTy = [[transform objectForKey:TY] intValue];
    fileName = [fileName stringByAppendingFormat:@"%@%@", DOT, SVG];
    fileName = [[self imagesPath] stringByAppendingPathComponent:fileName];
    id maxMinPath = [self getXYFromPath:pathStr];
    float minx = INT_MAX - 1, maxx = INT_MIN + 1, miny = INT_MAX - 1, maxy = INT_MIN + 1;
    [self getMinMaxXY:maxMinPath minx:&minx maxx:&maxx miny:&miny maxy:&maxy];
    path_x = minx + transformTx;
    path_y = miny + transformTy;
    path_width = maxx - minx;
    path_height = maxy - miny;
    NSString *viewBox = [NSString stringWithFormat:@"%f %f %f %f", minx + transformTx - colorWidth/2, miny + transformTy - colorWidth/2, maxx - minx + colorWidth, maxy - miny + colorWidth];
    NSString *translate = [NSString stringWithFormat:@"(%d %d)", transformTx, transformTy];
    NSString *pngName;
    if ([Helper fileExists:fileName]) {
        pngName = [Helper transformToPngFileName:fileName];
    } else {
        [self generateSVGFile:fileName FromPath:pathStr usingFill:hexColor usingViewBox:viewBox translation: translate];
        /* convert the svg file into a png file */
        pngName = [Helper convertSvgToPng:fileName withFill:hexColor strokeColor:strokeColor strokeWidth:colorWidth opacity:opacity];
    }
    return  pngName;
}

-(NSString *) computeValue:(NSString *)initValue forDict:(NSDictionary *)agcDict {
    if ([initValue isEqualToString:RANDOM]) {
        //generate a random value; needed for id
        return [self computeUUIDValue:agcDict];
    } else if ([initValue hasPrefix:GETMAX]) {
        /* used for multiline labels */
        return [self computeMultilineLabel:initValue forDict:agcDict];
    } else if ([initValue hasPrefix:PATH]){
        return  [self computePath:initValue forDict:agcDict];
    } else if ([initValue hasPrefix:LINE]){
        return [self computeLine:initValue forDict:agcDict];
    } else if ([initValue isEqualToString:[NSString stringWithFormat:@"$%@", DESTINATION]]){
        return destinationId;
    } else if ([initValue hasPrefix:IMAGEID]){
        initValue = [initValue substringFromIndex:[IMAGEID length] + 1];
        NSString *mainBundle = [self getProjHomePath];
        NSString *unzipped_xd = [[mainBundle stringByAppendingPathComponent:XD_EXPORT_PATH] stringByAppendingPathComponent:RESOURCES];
        NSArray *listImages = [initValue componentsSeparatedByString:@" "];
        NSString *href = [self computeAgcTag:[listImages objectAtIndex:0] dict:agcDict];
        NSString *idImg = [self computeAgcTag:[listImages objectAtIndex:1]dict:agcDict];
        if ([Helper fileExists:href])
            return href;
        return [[unzipped_xd stringByAppendingPathComponent:idImg] stringByAppendingPathExtension:PNG];
    } else {
        //if it depends on an agc tag
        return [self computeAgcTag:initValue dict:agcDict];
    }
    return initValue;
}

-(NSArray *) splitVariable:(NSString*) varName {
    if ([varName hasPrefix:TOTRANSFORM]) {
        return [[varName substringFromIndex:1] componentsSeparatedByString:DOT];
    }
    return [NSArray arrayWithObjects:varName, nil];
}


-(NSString *) toString:(NSMutableDictionary *)dict name:(NSString*)varName isLeaf:(BOOL)leaf {
    NSArray *order = [dict objectForKey:TOSTRING];
    NSArray *betweenTags = [dict objectForKey:BETWEEN];
    if ([varName hasPrefix:TOTRANSFORM] && [translationDict objectForKey:varName])
        varName = [translationDict objectForKey:varName];
    NSMutableString *tagStr = [NSMutableString stringWithFormat:@"<%@", varName];
    for (id object in order) {
        id value = [dict objectForKey:object];
        if ([uuidMap objectForKey:value]) {
            value = [uuidMap objectForKey:value];
        }
        if ([value isKindOfClass:[NSString class]] && [value containsString:@" "]) {
            value = [NSString stringWithFormat:@"\"%@\"", value];
        }
        if ([value isKindOfClass:[NSDictionary class]]) {
            [tagStr appendFormat:@">"];
            value = [self toString:value name:object isLeaf:true];
            [tagStr appendFormat:@"%@", value];
            [tagStr appendFormat:@"</%@>", varName];
            return tagStr;
        } else
            [tagStr appendFormat:@" %@=%@", object, value];
    }
    if (leaf)
        [tagStr appendFormat:@"/>"];
    else
        [tagStr appendFormat:@">"];
    if (betweenTags) {
        for (id object in betweenTags) {
            [tagStr appendFormat:@"%@", [dict objectForKey:object]];
        }
        [tagStr appendFormat:STRINGTAG];
    }
    return tagStr;
}

-(void) mergeDefaultValues:(NSDictionary*)defaultDict withDict:(NSMutableDictionary **) initDict usingDict:(NSDictionary*) paramDict {
    if ([defaultDict count] > 0)
        for (id key in [defaultDict allKeys]) {
            NSString *value = [defaultDict objectForKey:key];
            [*initDict setObject:value forKey:key];
        }
    NSString *dependency = [[paramDict allKeys] objectAtIndex:0];
    paramDict = [paramDict objectForKey:dependency];
    for (id key in [*initDict allKeys]) {
        NSString *value = [*initDict objectForKey:key];
        BOOL toTransform = [value isKindOfClass:[NSString class]] && [value hasPrefix:TOTRANSFORM];
        if (toTransform && [paramDict objectForKey:key]) {
            [*initDict setObject:[paramDict objectForKey:key] forKey:key];
        }
    }
    
}

- (NSNumber *) getFrameSizeFromPath:(NSString *) value  dict:(NSMutableDictionary *)dictValue {
    if ([value hasPrefix:GETHEIGHT]) {
        int offset = (int)[GETHEIGHT length] + 1;
        NSString *path = [dictValue objectForKey:[value substringFromIndex:offset]];
        NSArray *array = [path componentsSeparatedByString:@" "];
        NSString *width = [array objectAtIndex:HEIGHT_IN_PATH];
        NSNumberFormatter *f = [[NSNumberFormatter alloc] init];
        f.numberStyle = NSNumberFormatterDecimalStyle;
        NSNumber *nr = [f numberFromString: width];
        float number = [self changeSize:[nr intValue] key:HEIGHT preserveRatio:false preserveOffset:false scale:true];
        return [NSNumber numberWithInt:number];
    }
    int offset = (int)[GETWIDTH length] + 1;
    NSString *path = [dictValue objectForKey:[value substringFromIndex:offset]];
    NSArray *array = [path componentsSeparatedByString:@" "];
    NSString *height = [array objectAtIndex:WIDTH_IN_PATH];
    NSNumberFormatter *f = [[NSNumberFormatter alloc] init];
    f.numberStyle = NSNumberFormatterDecimalStyle;
    NSNumber *nr = [f numberFromString: height];
    float number = [self changeSize:[nr intValue] key:WIDTH preserveRatio:false preserveOffset:false scale:true];
    return [NSNumber numberWithInt:number];
}

- (BOOL) isOfTypeColor:(NSString *) key {
    return [[transformObjects objectForKey:COLOR] objectForKey:key] != nil;
}

-(BOOL) isOfTypeScale:(NSString *)key object:(NSString *) type {
    return [[transformObjects objectForKey:SCALE] objectForKey:key] && [[transformObjects objectForKey:SCALE] objectForKey:type];
}

-(BOOL) isOfTypeSize:(NSString *)key {
    return [[transformObjects objectForKey:SIZE] objectForKey:key] != nil;
}

-(BOOL) isOfTypeLine:(NSString *)value {
    return [value isEqualToString: LINE_X] || [value isEqualToString: LINE_Y]  || [value isEqualToString: LINE_WIDTH]  || [value isEqualToString: LINE_HEIGHT] ;
}

-(BOOL) isOfTypePath:(NSString *)value {
    return [value isEqualToString: PATH_X] || [value isEqualToString: PATH_Y]  || [value isEqualToString: PATH_WIDTH]  || [value isEqualToString: PATH_HEIGHT] ;
}

- (BOOL) isOfTypeLabel: (NSString *) value {
    return [value hasPrefix:GET_TYPE];
}

- (BOOL) isTextFrame:(NSString *) tvalue templateDict:(NSMutableDictionary *) objDict {
    return [tvalue isEqualToString:SIZE] && ![[objDict objectForKey:HEIGHT] isEqualToString:RAWTEXT];
}


- (BOOL) saveTextlength:(id) subRules {
    return ([subRules isKindOfClass:[NSMutableDictionary class]] && [subRules objectForKey:LEN]);

}

- (BOOL) isStyleType:(id) subRules {
    return ([subRules isKindOfClass:[NSMutableDictionary class]] && [subRules objectForKey:TYPE] &&
    [[subRules objectForKey:TYPE] isEqualToString:STYLE]);
}

- (BOOL) transformHeader:(NSArray*) keys {
    return ([keys count] == 1);
}

- (float) changeSize:(float) initValue key:(NSString *)key preserveRatio:(BOOL) preserveRatio preserveOffset: (BOOL) offset scale:(BOOL) scale{
    float translatedValue = initValue;
    if (!transformSize) {
        return translatedValue;
    }
    float xScaleFactor = ((float)widthXMLArtboard/WIDTH_XD_ARTBOARD_IPH6);
    float yScaleFactor = (float)heightXMLArtboard/HEIGHT_XD_ARTBOARD_IPH6;
    float widthScaleFactor = xScaleFactor;
    float heightScalefactor = yScaleFactor;
    float ratio = MIN(xScaleFactor,yScaleFactor);
    if (preserveRatio ) {
        widthScaleFactor = ratio;
        heightScalefactor = ratio;
    }
    if ([key isEqualToString:XARTBOARD]) {
        translatedValue = translatedValue - startXArtboard;
        translatedValue = translatedValue * xScaleFactor;
    } else if ([key isEqualToString:YARTBOARD]) {
        translatedValue = translatedValue - startYArtboard;
        translatedValue = translatedValue * yScaleFactor;
    } else if ([key isEqualToString:WIDTH]) {
        translatedValue = initValue * widthScaleFactor;
    } else if ([key isEqualToString:HEIGHT]) {
        translatedValue = initValue * heightScalefactor;
    }
    return MAX(1, translatedValue);
}

- (CGRect) computeTextFrame:(NSString *) label usingFontSize:(int) fontSize fontName:(NSString *)fontName fontMask:(NSUInteger) mask {

    
    float xScaleFactor = (float)widthXMLArtboard/WIDTH_XD_ARTBOARD_IPH6;
    if (textLines > 3)
        textLen = MIN((int)[label length], textLen * xScaleFactor);
    NSString *firstLine = [label substringToIndex:textLen];
    NSMutableParagraphStyle *style = [[NSParagraphStyle defaultParagraphStyle] mutableCopy];
    [style setLineBreakMode:NSLineBreakByWordWrapping];
    NSFontManager *fontManager = [NSFontManager sharedFontManager];
    NSFont *font = [fontManager fontWithFamily:fontName
                                              traits:mask
                                              weight:0
                                                size:fontSize];
    
    NSDictionary *attributes = @{NSFontAttributeName: font,
                                 NSParagraphStyleAttributeName: style};
    CGRect lineFrame = [firstLine boundingRectWithSize:CGSizeMake(600, 300)
                                               options:NSStringDrawingUsesLineFragmentOrigin
                                            attributes:attributes
                                               context:nil];
    float width = lineFrame.size.width;
    return [label boundingRectWithSize:CGSizeMake(width, CGFLOAT_MAX)
                                      options:NSStringDrawingUsesLineFragmentOrigin
                                   attributes:attributes
                                      context:nil];
}


- (NSNumber *) processPath:(NSString *)value ofType:(NSString *) key preserveRatio:(BOOL) preserveRatio{
    
    float initValue = 0;
    if ([value isEqualToString: PATH_X] || [value isEqualToString: LINE_X])
        initValue = path_x;
    else if ([value isEqualToString: PATH_Y] || [value isEqualToString: LINE_Y])
        initValue =path_y;
    else if ([value isEqualToString: PATH_WIDTH] || [value isEqualToString: LINE_WIDTH])
        initValue =path_width;
    else
        initValue =path_height;
    bool offset = false;
    bool aspectRatio = true;
    bool scale = true;
    if ([value isEqualToString: LINE_X] || [value isEqualToString: LINE_Y]) {
        offset = true;  aspectRatio = false;
    }
    if ([value isEqualToString: LINE_WIDTH] || [value isEqualToString: LINE_HEIGHT]) {
        scale = false;
        aspectRatio = false;
    }
    float translatedValue = [self changeSize:initValue key:key preserveRatio:aspectRatio preserveOffset:offset scale:scale];
    return [NSNumber numberWithFloat:translatedValue];
}

- (void) merge:(NSMutableDictionary *) dictValue withDict:(NSMutableDictionary **) objDict
   withDefDict:(NSMutableDictionary *)defaultDict forValue:(NSString *) value key:(NSString *) key type:(NSString *) type {

    if ([value hasPrefix:ADD_XOFFSET] || [value hasPrefix:ADD_YOFFSET]){
        id tvalue = [[self splitVariable:[value substringFromIndex:[ADD_YOFFSET length] + 1]]objectAtIndex:0];
        float initValue = [[dictValue objectForKey:tvalue] floatValue];
        if ([tvalue isEqualToString:TX]) {
            [dictValue setObject:[NSNumber numberWithFloat:initValue + xOffsetText] forKey:tvalue];
        } else {
            [dictValue setObject:[NSNumber numberWithFloat:initValue + yOffsetText] forKey:tvalue];
        }
        value = [NSString stringWithFormat:@"$%@",tvalue];
    }
    if (![value hasPrefix:TOTRANSFORM]) {
        [*objDict setValue:value forKey:key]; /* no need for transformation */
    } else if ([dictValue objectForKey:[[self splitVariable:value] objectAtIndex:0]]) {
        id tvalue = [[self splitVariable:value] objectAtIndex:0];
        if ([self isOfTypeSize:key]) {
            /* changing size here */
            float initValue = [[dictValue objectForKey:tvalue] floatValue];
            float translatedValue = [self changeSize:initValue key:key preserveRatio:false preserveOffset:false scale:true];
            [*objDict setValue:[NSNumber numberWithInt:translatedValue] forKey:key];
        } else {
            [*objDict setValue:[dictValue objectForKey:tvalue] forKey:key];
        }
        /* check if width/height needs to be computed (eg. text frame) */
        if ( [self isTextFrame:tvalue templateDict:*objDict]) {
            /* then we must compute the width/height of the text frame*/
            /* we have the height = text; width = fontSize; */
            [*objDict setValue:[dictValue objectForKey:tvalue] forKey:key];
            NSString *label = [*objDict objectForKey:HEIGHT];
            int fontSize = [[*objDict objectForKey:WIDTH] intValue];
            NSString *fontName = [dictValue objectForKey:ISFONT];
            NSString *fontStyle = [dictValue objectForKey: STYLE_VALUE];
            NSUInteger mask;
            if ([fontStyle isEqualToString:BOLD])
                mask = NSBoldFontMask;
            else if ([fontStyle isEqualToString:ITALIC])
                mask = NSItalicFontMask;
            else mask = 0;
            CGRect rect = [self computeTextFrame:label usingFontSize:fontSize fontName:fontName fontMask: mask];
            rect.size.width = ceil(rect.size.width);
            
            [*objDict setValue:[NSNumber numberWithFloat:rect.size.height] forKey:HEIGHT];
            [*objDict setValue:[NSNumber numberWithFloat:rect.size.width *1.2] forKey:WIDTH];
            if ([type isEqualToString:LABEL]) {
                /* move the frame up with fontSize */
                int initialYOffset = [[*objDict objectForKey:YARTBOARD] floatValue];
                [*objDict setObject:[NSNumber numberWithFloat:initialYOffset - fontSize] forKey:YARTBOARD];
            }
        }
        /*if we have a special operation to perform eg. getSize from path*/
    } else if ([value hasPrefix:GETHEIGHT] || [value hasPrefix:GETWIDTH]) {
        NSNumber *size = [self getFrameSizeFromPath:value dict:dictValue];
        [*objDict setObject:size forKey:key];
    } else if ([self isOfTypePath:value]) {
        [*objDict setObject:[self processPath:value ofType:key preserveRatio:true] forKey:key];
    } else if ([self isOfTypeLine:value]) {
        [*objDict setObject:[self processPath:value ofType:key preserveRatio:true] forKey:key];
    } else if ([self isOfTypeLabel:value]) {
        // TODO maybe
    } else {/* use default values */
        [*objDict setObject:[defaultDict objectForKey:key] forKey:key];
    }

}

-(void) mergeDictionaries:(NSMutableDictionary **)objDict withDict:(NSMutableDictionary *)dictValue
              usingValues:(NSDictionary *)paramsValue type:(NSString *)type {
    
    
    NSMutableDictionary *defaultDict = [*objDict objectForKey:DEFAULT];
    id allKeys = [*objDict allKeys];
    if ([*objDict objectForKey:ORDER])
        allKeys = [*objDict objectForKey:ORDER];
    for (id key in allKeys) {
        id value = [*objDict objectForKey:key];
        if ([value isKindOfClass:[NSString class]] && [value hasPrefix:TOTRANSFORM]) {
            value = [dictValue objectForKey:[value substringFromIndex:1]];
            if (value) {
                if ([self isOfTypeColor:key]) {
                    /* change the color */
                    float color;
                    if ([value floatValue] > 1)
                        color = [value floatValue] / 255;
                    else color = [value floatValue];
                    [*objDict setObject:[NSString stringWithFormat:@"%f", color] forKey:key];
                    continue;
                }
                if ([self isOfTypeScale:key object:type]) {
                    float initValue = [value floatValue];
                    float translatedValue = [self changeSize:initValue key:key preserveRatio:false preserveOffset:false scale:true];
                    [*objDict setObject:[NSNumber numberWithFloat:translatedValue] forKey:key];
                    continue;
                }
                [*objDict setObject:value forKey:key];
            } else {
                /* use values specified from agc */
                value = [paramsValue objectForKey:key];
                if (!value)
                    continue;
                [self merge:dictValue withDict:objDict withDefDict:defaultDict forValue:value key:key type:type];
            }
        } else if ([value isKindOfClass:[NSDictionary class]] && ![key isEqualToString:DEFAULT]) {
            id value = [*objDict objectForKey:key];
            [self mergeDictionaries:&value withDict:dictValue usingValues:[dictValue objectForKey:DEFAULT] type:key];
        }
    }
}

-(id) getShapeType:(id)type object:(id)object {
    if ([type isKindOfClass:[NSDictionary class]]) {
        for (id key in [type allKeys]) {
            id value = [object mutableCopy];
            id subType = [type objectForKey:key];
            NSArray *gotoTag = [key componentsSeparatedByString:DOT];
            for (id elem in [gotoTag subarrayWithRange:NSMakeRange(0, [gotoTag count] -1)]) {
                value = [value objectForKey:elem];
            }
            if (![value isEqualToString:[gotoTag lastObject]])
                continue;
            if ([subType isKindOfClass:[NSString class]]) {
                return subType;
            }
            for (id subKey in subType) {
                id subValue = [object mutableCopy];
                id subSubType = [subType objectForKey:subKey];
                gotoTag = [subKey componentsSeparatedByString:DOT];
                for (id elem in [gotoTag subarrayWithRange:NSMakeRange(0, [gotoTag count] -1)]) {
                    subValue = [subValue objectForKey:elem];
                }
                if (![subValue isEqualToString:[gotoTag lastObject]]) {
                    continue;
                } else {
                    type = subSubType;
                    break;
                }
            }
            break;
        }
    }
    return type;
}

-(void) getViewSize:(NSDictionary *)groupFrame minx:(int*)minx miny:(int*)miny maxx:(int*)maxx maxy:(int*)maxy maxh:(int*)maxh maxw:(int*)maxw {
    
    int x = [[groupFrame objectForKey:XARTBOARD] intValue];
    int y = [[groupFrame objectForKey:YARTBOARD] intValue];
    int w = [[groupFrame objectForKey:WIDTH] intValue];
    int h = [[groupFrame objectForKey:HEIGHT] intValue];
    *minx = MIN(x, *minx);
    *miny = MIN(y, *miny);
    if (x + w >= *maxx) {
        *maxx = x + w;
        *maxw = w;
    }
    if ( y + h >= *maxy) {
        *maxy = y + h;
        *maxh = h;
    }
}

-(void) updateGroupOffsets:(NSMutableArray**)viewSubviews minx:(int) minx miny:(int)miny {
    
    for (id keyObject in *viewSubviews) {
        id name = [[keyObject allKeys] objectAtIndex:0];
        id frame = [[[keyObject objectForKey:name ] objectForKey:RULES] objectForKey:FRAME];
        int x = [[frame objectForKey:XARTBOARD] intValue];
        x = x - minx;
        int y = [[frame objectForKey:YARTBOARD] intValue];
        y = y - miny;
        [frame setObject:[NSNumber numberWithInt:x] forKey:XARTBOARD];
        [frame setObject:[NSNumber numberWithInt:y] forKey:YARTBOARD];
    }
}

-(void) processGroup:(NSDictionary *)object newObjDict:(NSDictionary *)newObjDict subviews:(NSMutableArray **) viewSubviews finalDict:(NSMutableDictionary *)finalDict
                minx:(int*) minx miny:(int *) miny maxx:(int*)maxx maxy:(int*)maxy maxh:(int *)maxh maxw:(int *)maxw {
    
    for (id key in object) {
        id type = [translationDict objectForKey:[key objectForKey:TYPE]];
        if (!type)
            continue;
        type = [self getShapeType:type object:key];
        if (![type isKindOfClass:[NSString class]])
            continue;
        NSMutableDictionary *typeObjDict = [self deepCopy:[newObjDict objectForKey:type]];
        if ([type isEqualToString:GROUP]) {
            NSMutableDictionary *finalDict = [self deepCopy:[agcToXmlTemplate objectForKey:SUBVIEWS]];
            NSMutableDictionary *newObj = [self deepCopy:finalDict];
            NSMutableArray* arrayObj = [[NSMutableArray alloc] init];
            [self computeGroup:newObj agcDict:key finalDict:finalDict retDict:&arrayObj
                          minx:minx miny:miny maxx: maxx maxy:maxy maxh: maxh maxw: maxw];
            *viewSubviews = [[*viewSubviews arrayByAddingObjectsFromArray:arrayObj] mutableCopy];
            continue;
        }
        [self processTemplateDict:&typeObjDict agcDict:key finalDict:finalDict ofType:type];
        id groupFrame = [[typeObjDict objectForKey:RULES] objectForKey:FRAME];
        [self getViewSize:groupFrame minx:minx miny:miny maxx:maxx maxy:maxy maxh:maxh maxw:maxw];
        NSMutableDictionary *subViewDict = [[NSMutableDictionary alloc] init ];
        [subViewDict setObject:typeObjDict forKey:type];
        [*viewSubviews addObject:subViewDict];
    }
    
}

-(NSMutableArray *) computeSubView:(NSMutableArray *) subview {
    
    int minx = 060, miny = 600, maxx = 0, maxy = 0, maxw = 0, maxh = 0;
    for (id keyObject in subview) {
        id name = [[keyObject allKeys] objectAtIndex:0];
        id frame = [[[keyObject objectForKey:name ] objectForKey:RULES] objectForKey:FRAME];
        int x = [[frame objectForKey:XARTBOARD] intValue];
        int y = [[frame objectForKey:YARTBOARD] intValue];
        int w = [[frame objectForKey:WIDTH] intValue];
        int h = [[frame objectForKey:HEIGHT] intValue];
        if (x <= minx)  {
            minx = x;
        }
        if (y <= miny) {
            miny = y;
        }
        if (x + w >= maxx) {
            maxx = x + w;
            maxw = w;
        }
        if ( y + h >= maxy) {
            maxy = y + h;
            maxh = h;
        }
    }
    NSMutableArray *frame = [[NSMutableArray alloc] init];
    [frame addObject:[NSNumber numberWithInt:minx]];
    [frame addObject:[NSNumber numberWithInt:miny]];
    [frame addObject:[NSNumber numberWithInt:maxw]];
    [frame addObject:[NSNumber numberWithInt:maxh]];
    return frame;
}

-(void) computeGroup:(NSMutableDictionary *)newObjDict agcDict:(NSMutableDictionary*)object finalDict:(NSMutableDictionary*)finalDict retDict:(NSMutableArray**)objDict
    minx:(int*) minx miny:(int *) miny maxx:(int*)maxx maxy:(int*)maxy maxh:(int *)maxh maxw:(int *)maxw {
    
    NSMutableDictionary *viewDict = [self deepCopy:[newObjDict objectForKey:VIEW]];
    NSMutableArray *viewSubviews = [[NSMutableArray alloc] init];
    [self processTemplateDict:&viewDict agcDict:object finalDict:finalDict ofType:GROUP];
    int offsetGroupX = 0, offsetGroupY = 0;
    id transformGroup = [object objectForKey:TRANSFORM];
    if(transformGroup) {
        offsetGroupX = [[transformGroup objectForKey:TX] intValue] - startXArtboard;
        offsetGroupY = [[transformGroup objectForKey:TY] intValue] - startYArtboard;
    }
    id frameRules = [viewDict objectForKey:RULES];
    id sizeFrame = [frameRules objectForKey:FRAME];
    id colorTag = [[agcToXmlTemplate objectForKey:SUBTAGS] objectForKey:COLOR];
    id defaultColor = [self deepCopy:[colorTag objectForKey:DEFAULT_GROUP]];
    id colorToString = [self deepCopy:[colorTag objectForKey:TOSTRING]];
    int prevWidth = widthXDArtboard;
    int prevHeight = heightXDArtboard;
    widthXDArtboard = widthXMLArtboard;
    heightXDArtboard = heightXMLArtboard;
    int prevX = startXArtboard;
    int prevY = startYArtboard;
    startXArtboard = 0;
    startYArtboard = 0;
    [self processGroup:[[object objectForKey:GROUP] objectForKey:CHILDREN]
            newObjDict:newObjDict subviews:&viewSubviews
             finalDict:finalDict minx:minx miny:miny maxx:maxx maxy:maxy maxh:maxh maxw:maxw];
    
    widthXDArtboard = prevWidth;
    heightXDArtboard = prevHeight;
    startXArtboard = prevX;
    startYArtboard = prevY;
    int widthFrame = *maxx - *minx;
    int heightFrame = *maxy - *miny;
    [sizeFrame setObject:[NSNumber numberWithInt:offsetGroupX + *minx] forKey:XARTBOARD];
    [sizeFrame setObject:[NSNumber numberWithInt:offsetGroupY + *miny] forKey:YARTBOARD];
    [sizeFrame setObject:[NSNumber numberWithInt:widthFrame] forKey:WIDTH];
    [sizeFrame setObject:[NSNumber numberWithInt:heightFrame] forKey:HEIGHT];
    [defaultColor setObject:colorToString forKey:TOSTRING];
    [frameRules setObject:defaultColor forKey:COLOR];
    [self updateGroupOffsets:&viewSubviews minx:*minx miny:*miny];
    [[viewDict objectForKey:RULES ] setObject:viewSubviews forKey:SUBVIEWS];
    NSMutableDictionary *subViewTmp = [[NSMutableDictionary alloc] init ];
    [subViewTmp setObject:viewDict forKey:VIEW];
    [*objDict addObject:subViewTmp];
}

-(NSString *) convertFont:(NSString *)styleFont {
    
    id translatedStyle;
    if ([styleFont isEqualToString:REGULAR])
        translatedStyle = FONT_SYSTEM;
    else if ([styleFont isEqualToString:ITALIC])
        translatedStyle = FONT_ITALIC;
    else if ([styleFont isEqualToString:BOLD])
        translatedStyle = FONT_BOLD;
    else translatedStyle = FONT_SYSTEM; /* use default system font for other xd fonts */
    return translatedStyle;
}

- (int) getWidthXML {
    /*we transform Iphone6 XD scenes into Iphone XCode 5.5inch */
    return WIDTH_XML_ARTBOARD_RETINA55;
}

- (int) getHeightXML {
    /*we transform Iphone6 XD scenes into Iphone XCode 5.5inch */
    return HEIGHT_XML_ARTBOARD_RETINA55;
}

-(void) getDict:(id *)values fromConditions:(NSArray*)goToAgc {
    
    for (id key in goToAgc) {
        id nodeValue;
        if ([key hasPrefix:TOTRANSFORM] && [key isEqualToString:SCENENO]) {
            nodeValue = [*values objectAtIndex:sceneNo];
        } else if ([key hasPrefix:TOTRANSFORM] && [key isEqualToString:ARTBOARDSCENE]) {
            NSString *artboard = [NSString stringWithFormat:@"artboard%d", sceneNo +1];
            nodeValue = [*values objectForKey:artboard];
            /* obtain the startX and startY for the current scene */
            startXArtboard = [[nodeValue objectForKey:XARTBOARD] intValue];
            startYArtboard = [[nodeValue objectForKey:YARTBOARD] intValue];
            widthXDArtboard = [[nodeValue objectForKey:WIDTH] intValue];
            heightXDArtboard = [[nodeValue objectForKey:HEIGHT] intValue];
            widthXMLArtboard = [self getWidthXML];
            heightXMLArtboard = [self getHeightXML];
            xmlSceneOffset = widthXMLArtboard * 1.1;
        } else if ([key hasPrefix:TOTRANSFORM] && [key isEqualToString:LINES]){
            nodeValue = [*values objectAtIndex:0];
        } else if ([key hasPrefix:TOTRANSFORM] && [key isEqualToString:LINESDICT]){
            nodeValue = [*values objectForKey:[NSNumber numberWithInt:0]];
        } else {
            nodeValue = [*values objectForKey:key];
        }
        *values = nodeValue;
    }
}

-(void) copyDict:(NSDictionary*) defaultType toDict:(NSMutableDictionary **) genericDict {
    for (id key in [defaultType allKeys]) {
        [*genericDict setObject:[defaultType objectForKey:key] forKey:key];
    }
}


- (void) computeTextObject:(id)dictValue dependency:(NSString*) condition forDict:(NSMutableDictionary **) objDict {
    int counter = (int)[dictValue count];
    textLines = MAX(counter, [[*objDict objectForKey:LEN] intValue]);
    [*objDict setObject:[NSNumber numberWithInt:textLines] forKey:LEN];
    id tmp = dictValue;
    id firstLine;
    if (textLines == counter && [condition isEqualToString:TEXT_LINES]) {
        firstLine = [[[tmp objectAtIndex:0] objectAtIndex:0]objectForKey:TO];
        textLen = [firstLine intValue];
        xOffsetText = [[[[tmp objectAtIndex:0] objectAtIndex:0]objectForKey:XARTBOARD] floatValue];
        yOffsetText = [[[[tmp objectAtIndex:0] objectAtIndex:0]objectForKey:YARTBOARD] floatValue];
    } else if (textLines == counter && [condition isEqualToString:TEXT_PARAGRAPH]) {
        tmp = [[tmp objectAtIndex:0] objectForKey:LINE_VALUE];
        textLen = 0;
        bool set = false;
        for (id temp in tmp) {
            firstLine = [[temp objectAtIndex:0]objectForKey:TO];
            if (!set) {
                xOffsetText = [[[temp objectAtIndex:0] objectForKey:XARTBOARD] floatValue];
                yOffsetText = [[[temp objectAtIndex:0] objectForKey:YARTBOARD] floatValue];
                set = true;
            }
            if (textLen < [firstLine intValue])
                textLen = [firstLine intValue];
        }
    }
}

- (void) processGroupElements:(id)object addTo:(id *)objDict {
    id transformGroup = [object objectForKey:TRANSFORM];
    startXArtboard = startXArtboard - [[transformGroup objectForKey:TX] intValue];
    startYArtboard = startYArtboard - [[transformGroup objectForKey:TY] intValue];
    id groupChildren = [[object objectForKey:GROUP] objectForKey:CHILDREN];
    id groupObjDict = [Helper deepCopy:[agcToXmlTemplate objectForKey:SUBVIEWS]];
    [self processAgcScenes:&groupObjDict forDict:groupChildren];
    startXArtboard = startXArtboard + [[transformGroup objectForKey:TX] intValue];
    startYArtboard = startYArtboard + [[transformGroup objectForKey:TY] intValue];
    for (id childGroup in groupObjDict)
        [*objDict addObject:childGroup];
}

- (void) processAgcScenes:(id*) objDict forDict:(NSMutableDictionary *) dictValue {
    NSMutableDictionary *finalDict = [Helper deepCopy:[agcToXmlTemplate objectForKey:SUBVIEWS]];
    NSMutableDictionary *newObjDict = [Helper deepCopy:[*objDict mutableCopy]];
    *objDict = [[NSMutableArray alloc] init];
    for (id object in dictValue) {
        /* obtain the type of each object
         * get the corresponding template*/
        id type = [translationDict objectForKey:[object objectForKey:TYPE]];
        if (!type)
            continue;
        /* we need to check several rules in order to decide which is the type of an object
         * esp for type = shape
         **/
        type = [self getShapeType:type object:object];
        if (![type isKindOfClass:[NSString class]])
            continue;
        NSMutableDictionary *typeObjDict = [Helper deepCopy:[newObjDict objectForKey:type]];
        if ([type isKindOfClass:[NSString class]] && [type isEqualToString:GROUP]) {
            [self processGroupElements:object addTo:objDict];
            continue;
        }
        [self processTemplateDict:&typeObjDict agcDict:object finalDict:finalDict ofType:type];
        NSMutableDictionary *subViewDict = [[NSMutableDictionary alloc] init ];
        [subViewDict setObject:typeObjDict forKey:changeType];
        [*objDict addObject:subViewDict];
    }
}

-(void) computeSeguesObjects:(id *) objDict {
    id tempSegue = [*objDict objectForKey:SEGUE];
    id segue = [self deepCopy:tempSegue];
    for (id key in [segue allKeys]) {
        if (![[segue objectForKey:key] isKindOfClass:[NSString class]] || ![[segue objectForKey:key] hasPrefix:TOTRANSFORM])
            continue;
        id value = [self computeValue:[segue objectForKey:key] forDict:[[NSDictionary alloc] init]];
        [tempSegue setObject:value forKey:key];
    }
}

- (id) getCorrespondingTemplate:(NSString *) rule {
    id objDict;
    if ([rule isEqualToString:SUBVIEWS])
        objDict = [Helper deepCopy:[agcToXmlTemplate objectForKey:SUBVIEWS]];
    else {
        objDict = [Helper deepCopy:[[agcToXmlTemplate objectForKey:SUBTAGS] objectForKey:rule]];
    }
    return objDict;
}

-(NSMutableDictionary *) computeObjects:(NSString *)rule condition:(NSArray*)cond params:(NSDictionary *)dict
                                agcDict:agcParams type:(NSString *)type {
    id objDict = [self getCorrespondingTemplate:rule];
    if (!cond && [rule isEqualToString:CONNECTIONS]) {
        [self computeSeguesObjects:&objDict];
    }
    if (!cond) {
        return objDict;
    }
    for (id condition in cond) {
        id values = agcParams;
        NSArray *goToAgc = [self splitVariable:condition];
        [self getDict:&values fromConditions:goToAgc];
        NSMutableDictionary *dictValue = values;
        BOOL isEmpty = ([dictValue count] == 0);
        if (isEmpty && !dictValue) {
            [self mergeDefaultValues:[objDict objectForKey:DEFAULT] withDict:&objDict usingDict:dict];
            return objDict;
        } else if (isEmpty) {
            return nil;
        } else {
            id subRules = [dict objectForKey:condition];
            if ([self saveTextlength:subRules]) {
                [self computeTextObject:dictValue dependency:condition forDict:&objDict];
                continue;
            }
            if ([self isStyleType:subRules]) {
                id styleFont = [dictValue objectForKey:STYLE_VALUE];
                id translatedStyle = [self convertFont:styleFont];
                [[dict objectForKey:condition] setObject:translatedStyle forKey:TYPE];
            }
            if (![dictValue isKindOfClass:[NSArray class]]) {
                [self mergeDictionaries:&objDict withDict:dictValue usingValues:[dict objectForKey:condition] type:type];
            }
            else {
                [self processAgcScenes:&objDict forDict:dictValue];
            }
        }
    }
    return objDict;
}


- (void) transformIntoButton:(NSMutableDictionary **) templateDict usingTemplate:(NSMutableDictionary *) button ofType:(NSString *) type{
    transformSize = false;
    [self processTemplateDict:templateDict agcDict:button finalDict:button ofType:type];
    transformSize = true;
}

-(void) processInteractions:(id*) templateDict type:(NSString *) type {
    if (transformInteraction) {
        id value = *templateDict;
        id button = [[agcToXmlTemplate objectForKey:BUTTON_SEGUE] objectForKey:type];
        if (button) {
            id genericButton = [[self deepCopy:button] objectForKey:BUTTON];
            [self transformIntoButton: &genericButton usingTemplate:value ofType:BUTTON];
            *templateDict = genericButton;
            changeType = BUTTON;
        } 
    } else {
        changeType = type;
    }
}

- (NSMutableDictionary *) processHeader:(NSMutableDictionary *)rulesDict rule:(NSString *)rule usingDict:(NSDictionary *)agcDict type:(NSString*)type {
    id cond;
    if ([rulesDict count] == 0)
        cond = nil;
    else if ([rulesDict objectForKey:ORDER])
        cond = [rulesDict objectForKey:ORDER];
    else
        cond = [rulesDict allKeys];
    return [self computeObjects:rule condition:cond params:rulesDict agcDict:agcDict type:type];
    
}

-(void) processRules:(NSArray *)keys template:(id*) templateDict rulesDict:(id)rulesDict agcDict:(NSDictionary *)agcDict {
    id val = *templateDict;
    for (id key in [keys subarrayWithRange:NSMakeRange(0, [keys count] -1)]) {
        val = [val objectForKey:key];
    }
    NSString* value = [self computeValue:rulesDict forDict:agcDict];
    if ([[value componentsSeparatedByString:@" "] count] == 1) {
        id hasValue = [val objectForKey:[keys lastObject]];
        if (hasValue && [hasValue intValue]){
            int max = MAX([hasValue intValue], [value intValue]);
            [val setObject:[NSNumber numberWithInt:max] forKey:[keys lastObject]];
        }
        else [val setObject:value forKey:[keys lastObject]];
    } else {
        NSString *stringValue = [NSString stringWithFormat:@"\"%@\"", value];
        [val setObject:stringValue forKey:[keys lastObject]];
    }

}

-(NSDictionary*) processTemplateDict:(NSMutableDictionary **) templateDict agcDict:(NSDictionary *)agcDict
                           finalDict:(NSMutableDictionary *)finalDict ofType:(NSString *) type {
    noOfElements++;
    NSMutableDictionary *rulesInitDict = [*templateDict objectForKey:RULES];
    NSMutableDictionary *rulesTempDict = [rulesInitDict mutableCopy];
    NSArray *keys;
    NSMutableDictionary *rulesDict, *mergeDict;
    id rulesByOrder;
    if ([rulesTempDict objectForKey:ORDER])
        rulesByOrder = [rulesTempDict objectForKey:ORDER];
    else rulesByOrder = rulesTempDict;
    for (id rule in rulesByOrder) {
        keys = [self splitVariable:rule];
        if ([self transformHeader:keys]) {
            rulesDict = [rulesTempDict objectForKey:rule];
            if ([rulesDict isKindOfClass:[NSArray class]])
                continue;
            mergeDict = [self processHeader:rulesDict rule:rule usingDict:agcDict type:type];
            if (mergeDict != nil) {
                [rulesInitDict setObject:mergeDict forKey:rule];
            }
        } else {
            [self processRules:keys template:templateDict rulesDict:[rulesTempDict objectForKey:rule] agcDict:agcDict];
        }
    }
    [self processInteractions:templateDict type:type];
    return finalDict;
}

-(NSDictionary*) processWholeXmlFromAgc:(NSDictionary *)agcDict {
    NSMutableDictionary *finalDict = [NSKeyedUnarchiver unarchiveObjectWithData:[NSKeyedArchiver archivedDataWithRootObject: [agcToXmlTemplate objectForKey:CONTENT]]];
    NSMutableDictionary *viewDict = [finalDict objectForKey:ARTBOARD];
    return [self processTemplateDict:&viewDict agcDict:agcDict finalDict:finalDict ofType:VIEW];
}

/* in case of whole file translation => extend with header and footer */
-(NSString *) surroundWithHeader:(NSString *) header footer:(NSString *) footer string:(NSString *)str {
    return [NSString stringWithFormat:@"%@\n%@\n%@", header, str, footer];
}

- (NSString *) imagesPath {
    return [[self xmlPath] stringByAppendingPathComponent:RESOURCES_PATH];
}

-(void) copyImage:(NSImage *)image toProject:(NSString *)fileName {
    NSString *resourcesXmlRes = [self imagesPath];
    NSString *resourcesXmlProj = [resourcesXmlRes stringByAppendingPathComponent:fileName];
    if ([Helper fileExists:resourcesXmlProj]) {
        return;
    }
    NSLog(@"Writing image at %@ %@", [self xmlPath], resourcesXmlProj);
    BOOL isDir;
    NSError *error;
    if (![[NSFileManager defaultManager] fileExistsAtPath:resourcesXmlRes
                                              isDirectory:&isDir]) {
        [[NSFileManager defaultManager] createDirectoryAtPath:[[self xmlPath] stringByAppendingPathComponent:RESOURCES_PATH] withIntermediateDirectories:NO attributes:nil error:&error];
    }
    NSBitmapImageRep *imgRep = (NSBitmapImageRep *)[[image representations] objectAtIndex: 0];
    NSData *data = [imgRep representationUsingType: NSPNGFileType properties: @{}];
    [data writeToFile: resourcesXmlProj atomically: NO];
}

-(void) processImage:(id) dict key:(id) key {
    id attr = [dict objectForKey:key];
    if ([attr isKindOfClass:[NSDictionary class]] && [attr objectForKey:ISIMAGE]) {
        /* add image in the resources tag */
        NSString * href = [attr objectForKey:ISIMAGE];
        /* find width and height for image */
        NSImage *image;
        if ([[NSFileManager defaultManager] fileExistsAtPath:href])
            image = [[NSImage alloc]initWithContentsOfFile:href];
        else if ([[NSFileManager defaultManager] fileExistsAtPath:[href stringByDeletingPathExtension]])
            image = [[NSImage alloc]initWithContentsOfFile:[href stringByDeletingPathExtension]];
        /* create an image Tag using subTags */
        NSMutableDictionary *imageDict = [[[agcToXmlTemplate objectForKey:SUBTAGS] objectForKey:ISIMAGE] mutableCopy];
        NSString *theFileName = [href lastPathComponent];
        imageDict[NAME] = theFileName;
        imageDict[WIDTH] = [NSString stringWithFormat:@"%f", image.size.width];
        imageDict[HEIGHT] = [NSString stringWithFormat:@"%f", image.size.height];
        NSArray *rootarray = [[self xmlPath] componentsSeparatedByString:@"/"];
        rootarray = [rootarray subarrayWithRange:NSMakeRange(0, [rootarray count] -2)];
        if (image) {
            [self copyImage:image toProject:theFileName];
        } else {
            NSLog(@"[ERROR] Cannot find image at path %@;\nExport as png from XD.", href);
            [self copyImage:image toProject:theFileName];
        }
        NSString *str = [self toString:imageDict name:ISIMAGE isLeaf:TRUE];
        id header = [dict objectForKey:HEADER];
        id state = [dict objectForKey:STATE];
        if (header)
            [header  setObject:theFileName forKey:ISIMAGE];
        if (state)
            [state setObject:theFileName forKey:ISIMAGE];
        /* insert this tag into resourcesDict
         * only if this resource was not prev added */
        if ([resourcesDict rangeOfString:str].location == NSNotFound) {
            [resourcesDict appendString:str];
        }
    }
}

-(NSMutableString *) parseToString:(NSMutableString *)str dict:(NSDictionary *)dict name:(NSString *) name{
    NSMutableString* tmp = [NSMutableString stringWithFormat:@""];
    /* now we only have to translate the currentDict */
    for (id key in [dict objectForKey:TOSTRING]) {
        id attr = [dict objectForKey:key];
        [self processImage:dict key:key];
        if ([key isEqualToString:RULES]) {
            [tmp appendString:[self parseToString:tmp dict:attr name:key]] ;
        } else if ([key isEqualToString:HEADER]) {
            /* create a new top tag with dict[allKeys] objeectAtIndex[0] */
            [ tmp appendString: [self toString:attr name:name isLeaf:FALSE]];
        } else if ([key isEqualToString:SUBVIEWS]){
            [tmp appendString:XMLSUBVIEWS];
            for (id subview in attr) {
                if ([subview isKindOfClass:[NSString class]])
                    break;
                NSString *name = [[subview allKeys] objectAtIndex:0];
                NSMutableDictionary *dict = [subview objectForKey:name];
                NSMutableString *str = [self parseToString:tmp dict:dict name:name];
                if ([name hasPrefix:TOTRANSFORM] && [translationDict objectForKey:name])
                    name = [translationDict objectForKey:name];
                NSString* subFooter = [NSString stringWithFormat:@"\n</%@>", name];
                [str appendString:subFooter];
                [tmp appendString: str];
            }
            [tmp appendString:XMLSUBVIEWSF];
        } else if ([key isEqualToString:CONNECTIONS]) {
            [tmp appendString:[NSString stringWithFormat:@"<%@>", key]];
            [tmp appendString:[self toString:[[dict objectForKey:key] objectForKey:SEGUE ]  name:SEGUE isLeaf:YES]];
            [tmp appendString:[NSString stringWithFormat:@"</%@>", key]];
        } else if ([[agcToXmlTemplate objectForKey:SUBTAGS] objectForKey:key]){
            BOOL inBetween = [[[agcToXmlTemplate objectForKey:SUBTAGS] objectForKey:key]objectForKey:BETWEEN] == nil;
            /* just an ordinary leaf tag; create a tag with the given attributes */
            NSString *ret = [self toString:attr name:key isLeaf:inBetween];
            [ tmp appendString: [NSString stringWithFormat:@"\n\t%@", ret]];
        }
    }
    return tmp;
}

- (NSString *) getUniqueString {
    NSString *uid = [[NSUUID UUID] UUIDString];
    while ([uniqueList objectForKey:uid]) {
        uid = [[NSUUID UUID] UUIDString];
    }
    [uniqueList setObject:[NSNumber numberWithInt:1] forKey:uid];
    return uid;

}
-(bool) generateSceneHeaderUsingString:(NSMutableString **)finalString withInitialArtboard:(NSString*) initialArtboard
                           sceneOffset:(long)offset isInitialSet:(bool) setInitial dictionary:(NSDictionary *)dict sceneId: (id) sceneId {
    [*finalString appendString: SCENEHEADERA];
    [*finalString appendString: [self getUniqueString]];
    [*finalString appendString: SCENEHEADERB];
    if ([sceneId isEqualToString:homeArtboard]) {
        [*finalString appendString: initialArtboard];
        if (sceneId != nil)
            [uuidViewMap setObject:initialArtboard forKey:sceneId];
        setInitial = true;
    }
    else {
        id sceneID = [self getUniqueString];
        [*finalString appendString: sceneID];
        if (sceneId != nil) {
            [uuidViewMap setObject:sceneID forKey:sceneId];
        }
    }
    [*finalString appendString: SCENEHEADERC];
    [*finalString appendString: [self getUniqueString]];
    [*finalString appendString: SCENEHEADERD];
    [*finalString appendString: [self getUniqueString]];
    [*finalString appendString: SCENEHEADERE];
    id content = [self parseToString:*finalString dict:dict name: ARTBOARD];
    [*finalString appendString: content];
    [*finalString appendString: XMLVIEWF];
    [*finalString appendString:XMLFOOTERA];
    [*finalString appendString: [self getUniqueString]];
    [*finalString appendString:XMLFOOTERB];
    [*finalString appendFormat:@"%lu", offset];
    [*finalString appendString:XMLFOOTERC];
    [*finalString appendFormat:@"%d", XML_SCENE_Y];
    [*finalString appendString:XMLFOOTERD];
    return true;
}

-(void) writeXmlString:(NSString *) xmlString {
    NSError *err;
    NSData *data = [xmlString dataUsingEncoding:NSUTF8StringEncoding];
    NSXMLDocument *doc = [[NSXMLDocument alloc] initWithData:data options:NSXMLDocumentTidyXML error:&err];
    NSData* xmlData = [doc XMLDataWithOptions:NSXMLNodePrettyPrint];
    //[xmlData writeToFile:@"/Users/crogoz/Desktop/here.xml" atomically:YES];
    if ([self outXmlPath])
        [xmlData writeToFile:[self outXmlPath] atomically:YES];
}

- (NSArray *) sortUid {
    NSMutableArray *values = [[uuidViewMap allKeys] mutableCopy];
    return [values sortedArrayUsingFunction:comparatorFunction context:nil];
}

NSInteger comparatorFunction(id num1, id num2, void *context) {
    num1 = [num1 substringFromIndex:[NODE length]];
    num2 = [num2 substringFromIndex:[NODE length]];
    int v1 = [num1 intValue];
    int v2 = [num2 intValue];
    if (v1 < v2)
        return NSOrderedDescending;
    else if (v1 > v2)
        return NSOrderedAscending;
    else
        return NSOrderedSame;
}

- (NSString *) replaceConnections:(NSString *) xmlString {
    NSString *newString = [self deepCopy:xmlString];
    id allKeys = [self sortUid];
    for (id node in allKeys) {
        newString = [newString stringByReplacingOccurrencesOfString:node withString:[uuidViewMap objectForKey:node]];
    }
    return newString;
}

-(NSString*) getXmlForAgcObject:(NSDictionary*)typeAgcObject {
    NSMutableString *xmlGen = [NSMutableString stringWithFormat:@""];
    NSMutableString *finalString;
    NSDictionary *dict;
    NSMutableString *stringFooter = [NSMutableString stringWithFormat:XMLSCENESF];
    NSString *initialArtboard, *resources, *xmlHeader, *xmlFile;
    BOOL setInitial = false;
    int artboardsNo;
    // it was given the whole dictionary to process => goto @"content"; type = "view"
    artboardsNo = (int)[[typeAgcObject objectForKey:ARTBOARDS] count];
    initialArtboard = [self getUniqueString];
    setInitial = false;
    while (sceneNo < artboardsNo) {
        finalString = [[NSMutableString alloc] init];
        dict = [[self processWholeXmlFromAgc:typeAgcObject] objectForKey: ARTBOARD];
        id sceneId = [[[typeAgcObject objectForKey:CHILDREN] objectAtIndex:sceneNo] objectForKey:ID];
        sceneOffset = sceneOffset + xmlSceneOffset;
        setInitial = [self generateSceneHeaderUsingString:&finalString
                                      withInitialArtboard:initialArtboard
                                              sceneOffset:sceneOffset
                                             isInitialSet:setInitial
                                               dictionary:dict
                                                 sceneId : sceneId];
        [xmlGen appendString:finalString];
        ++sceneNo;
    }
    NSLog(@"There are %d artboards and ~ %d properties computed", sceneNo, noOfElements);
    if ([resourcesDict length]) {
        /* append resources */
        resources = [NSString stringWithFormat:@"%@\n%@\n%@",XMLRESOURCES, resourcesDict, XMLRESOURCESF];
        [stringFooter appendString:resources];
    }
    [stringFooter appendFormat:@"\n%@", XMLDOCUMENTF];
    xmlHeader =  [self surroundWithHeader:XMLHEADERA footer:XMLHEADERB string:initialArtboard];
    xmlFile = [self surroundWithHeader:xmlHeader footer:stringFooter string:xmlGen];
    xmlFile = [self replaceConnections:xmlFile];
    [self writeXmlString:xmlFile];
    return xmlGen;
}

- (id)initWithError:(NSError **)error {
    return self;
}

@end
