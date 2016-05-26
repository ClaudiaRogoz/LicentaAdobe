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



+ (void)readTemplateUsingXML:(NSString *)xdPath writeTo:(NSString*)outXmlPath
{
    NSError *error;
    NSMutableDictionary *agcTemplate = [[NSMutableDictionary alloc] init];
    NSString *xmlPath = [[outXmlPath stringByDeletingLastPathComponent] stringByDeletingLastPathComponent];
    XD2XCode *gen = [[XD2XCode alloc] initWithError:&error];

    [gen initWithSchemas];
    [gen setXdPath:xdPath];
    [gen setXmlPath:xmlPath];
    [gen setOutXmlPath:outXmlPath];
    
    agcTemplate = [gen getXdDictionary];
    [gen getXmlForAgcObject:agcTemplate];
    
    
}

+(NSString *) generateXmlForTag:(NSDictionary*)agcDict {
    
    NSError *error;
    
    XD2XCode *gen = [[XD2XCode alloc] initWithError:&error];
    [gen initWithSchemas];
    
    NSString *xmlTemplate = [gen getXmlForAgcObject:agcDict];
    
    if (!xmlTemplate) {
        NSLog(@"[ERROR] No translation can be achieved at the moment for %@", [agcDict objectForKey:TYPE]);
        return nil;
    }
    
    
    return xmlTemplate;
}

-(void) addChild:(NSMutableDictionary *)child to:(NSMutableDictionary **) agcDict atIndex:(int) nr{

    [[*agcDict objectForKey:CHILDREN ] insertObject:child atIndex:nr];
}

- (void) addArtboardsToAgc:(NSMutableDictionary **) agcDict usingPath:(NSString *) path{
    
    NSError *error;
    NSData *data = [NSData dataWithContentsOfFile:path];
    NSMutableDictionary *artboards =  [NSJSONSerialization JSONObjectWithData:data options:NSJSONReadingMutableContainers error:&error];
    //NSLog(@"SortedKeys = %@", [artboards objectForKey:ARTBOARDS]);
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
    NSLog(@"findAllFIkes = %@", findAllFiles);
    NSData *data = [NSData dataWithContentsOfFile:firstFile];
    agcTemplate =  [NSJSONSerialization JSONObjectWithData:data options:NSJSONReadingMutableContainers error:&error];
    int scene = 1;
    for (id file in findAllFiles) {
        
        data = [NSData dataWithContentsOfFile:file];
        NSMutableDictionary *temp = [NSJSONSerialization JSONObjectWithData:data options:NSJSONReadingMutableContainers error:&error];
        id value = [[temp objectForKey:CHILDREN] objectAtIndex:0];
        NSString *artboardNo = [[value objectForKey:ART_SCENE] objectForKey:REF];
        int number = [[artboardNo substringFromIndex:[ART_SCENE length]] intValue];
        
        [self addChild:[self deepCopy:value] to:&agcTemplate atIndex:number -1];
        [sceneMapping setObject:[NSNumber numberWithInt:scene] forKey:[NSNumber numberWithInt:number -1]];
        scene ++;
    }

    NSString *resources = [self appendPathComponents:@[ZIP_RESOURCES, GRAPHICS, GRAPHIC] topath:unzipped_xd];
    [self addArtboardsToAgc:&agcTemplate usingPath:resources];

    return agcTemplate;
}

-(NSString *) getClipboardData {
     NSPasteboard *pasteboard = [NSPasteboard generalPasteboard];
     return [pasteboard stringForType:SPARKLERCLIPBOARD];
}

-(void) initWithSchemas {
    
    NSError *error;
    
    NSBundle *thisBundle = [NSBundle bundleForClass:[self class]];
    NSString *def = [thisBundle pathForResource:DEF_PATH ofType:JSON];
    NSString *rule = [thisBundle pathForResource:RULES_PATH ofType:JSON];
    NSData *defData = [NSData dataWithContentsOfFile:def];
    
    NSData *ruleData = [NSData dataWithContentsOfFile:rule];
    
    NSMutableDictionary *defDictionary = [NSJSONSerialization JSONObjectWithData:defData options:NSJSONReadingMutableContainers error:&error];
    
    NSDictionary *ruleDictionary = [NSJSONSerialization JSONObjectWithData:ruleData options:NSJSONReadingMutableContainers error:&error];
    
    [self releaseResources];
    [self initializeWithDefs:defDictionary rules:ruleDictionary];
    
    
}

- (void) releaseResources {
    
    NSString *mainBundle = [self getProjHomePath];
    NSString *unzipped_xd = [mainBundle stringByAppendingPathComponent:XD_EXPORT_PATH];
    NSLog(@"Removing %@ ....", unzipped_xd);
    NSLog(@"%hhd", [[NSFileManager defaultManager] removeItemAtPath:unzipped_xd error:nil]);
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

-(void) generateSVGFile:(NSString *)filePath FromPath:(NSString *)pathString usingFill:(NSString *)hex{
    
    NSError *error;
    NSString *svgTemplate = [[NSBundle mainBundle] pathForResource:SVG_TEMPLATE ofType:SVG];
    NSMutableString *path = [NSMutableString stringWithContentsOfFile:svgTemplate encoding:NSUTF8StringEncoding error:&error];
    long len = [path length];
    
    /* color transformation */
    
    NSRange range = [path rangeOfString:SVG_FILL];
    long start = range.location + SVG_FILL_LEN;
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
    
    NSData *fileContents = [path dataUsingEncoding:NSUTF8StringEncoding];
    
    /* write to file */
    [[NSFileManager defaultManager] createFileAtPath:filePath
                                            contents:fileContents
                                          attributes:nil];
    
    
    
}

-(void)initializeWithDefs:(NSDictionary*)defDict rules:(NSDictionary*)ruleDict {
    agcToXmlTemplate = [defDict mutableCopy];
    translationDict = [ruleDict mutableCopy];
    resourcesDict = [[NSMutableString alloc] init];
    scaleImage = [[NSMutableArray alloc] init];
    inheritanceColor = [[NSMutableArray alloc] init];
    sceneMapping = [[NSMutableDictionary alloc] init];
    
    scaleNo = 0;
    
    transformObjects = [[NSMutableDictionary alloc] init];
    transformObjects[SIZE] = [[NSMutableDictionary alloc] init];
    transformObjects[SIZE][XARTBOARD] = [NSNumber numberWithInt:1];
    transformObjects[SIZE][YARTBOARD] = [NSNumber numberWithInt:1];
    
    transformObjects[SCALE] = [[NSMutableDictionary alloc] init];
    transformObjects[SCALE][WIDTH] = [NSNumber numberWithInt:1];
    transformObjects[SCALE][HEIGHT] = [NSNumber numberWithInt:1];
    transformObjects[SCALE][FRAMED] = [NSNumber numberWithInt:1];
    transformObjects[SCALE][IMAGEVIEW] = [NSNumber numberWithInt:1];
    
    transformObjects[COLOR] = [[NSMutableDictionary alloc] init];
    transformObjects[COLOR][RED] = [NSNumber numberWithInt:1];
    transformObjects[COLOR][GREEN] = [NSNumber numberWithInt:1];
    transformObjects[COLOR][BLUE] = [NSNumber numberWithInt:1];
    
    sceneNo = 0;
    
    
    
}

- (NSString *)hexStringForColor:(NSDictionary *)value {
    CGFloat red = [[value objectForKey:RED] floatValue] /255;
    CGFloat green = [[value objectForKey:GREEN] floatValue] /255;
    CGFloat blue = [[value objectForKey:BLUE] floatValue] /255;
    
    NSColor *color = [NSColor colorWithRed:red
                                     green:green
                                      blue:blue
                                     alpha:1];
    
    const CGFloat *components = CGColorGetComponents(color.CGColor);
    CGFloat r = components[0];
    CGFloat g = components[1];
    CGFloat b = components[2];
    
    NSString *hexString=[NSString stringWithFormat:@"%02X%02X%02X", (int)(r * 255), (int)(g * 255), (int)(b * 255)];
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
        return [self hexStringForColor:(NSDictionary*)value];
    }
    
    return value;

}

-(NSString *) computeValue:(NSString *)initValue forDict:(NSDictionary *)agcDict {
    
    
    if ([initValue isEqualToString:RANDOM]) {
        //generate a random value; needed for id
        return [[NSUUID UUID] UUIDString];
        
    } else if ([initValue hasPrefix:GETMAX]) {
        
        /* used for multiline labels */
        NSRange range = [initValue rangeOfString:GETMAX];
        NSArray *max2 = [[initValue substringFromIndex:range.location + GETMAX.length + 1] componentsSeparatedByString:SPACE];
        
        id first = [self computeValue:[max2 objectAtIndex:0] forDict:agcDict];
        id second = [self computeValue:[max2 objectAtIndex:1] forDict:agcDict];
        int ret = MAX([first intValue], [second intValue]);
        
        return [NSString stringWithFormat:@"%d", ret];
        
    } else if ([initValue hasPrefix:PATH]){
        
        NSRange range = [initValue rangeOfString:PATH];
        NSArray *paths = [[initValue substringFromIndex:range.location + PATH.length + 1] componentsSeparatedByString:SPACE];
        
        NSString *pathStr = [self computeValue:[paths objectAtIndex:0] forDict:agcDict];
        NSString *fileName = [self computeValue:[paths objectAtIndex:1] forDict:agcDict];
        NSString *hexColor = [self computeValue:[paths objectAtIndex:2] forDict:agcDict];
        
        fileName = [fileName stringByAppendingFormat:@"%@%@", DOT, SVG];
        
        [self generateSVGFile:fileName FromPath:pathStr usingFill:hexColor];
        
        return  fileName;
        
    } else {
        //if it depends on an agc tag
        return [self computeAgcTag:initValue dict:agcDict];
    }
    
    return initValue;
    
}

-(NSArray *) splitVariable:(NSString*) varName {
    
    if ([varName hasPrefix:@"$"]) {
        return [[varName substringFromIndex:1] componentsSeparatedByString:@"."];
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
        [tagStr appendFormat:@" %@=%@", object, [dict objectForKey:object]];
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
        if (toTransform) {
            
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
        float number = [self changeSize:[nr intValue] key:HEIGHT];
        return [NSNumber numberWithInt:number];
        
    }

    int offset = (int)[GETWIDTH length] + 1;
    NSString *path = [dictValue objectForKey:[value substringFromIndex:offset]];
    NSArray *array = [path componentsSeparatedByString:@" "];
    NSString *height = [array objectAtIndex:WIDTH_IN_PATH];
    NSNumberFormatter *f = [[NSNumberFormatter alloc] init];
    f.numberStyle = NSNumberFormatterDecimalStyle;
    NSNumber *nr = [f numberFromString: height];
    float number = [self changeSize:[nr intValue] key:WIDTH];
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

- (BOOL) isTextFrame:(NSString *) tvalue templateDict:(NSMutableDictionary *) objDict {
    return [tvalue isEqualToString:SIZE] && ![[objDict objectForKey:HEIGHT] isEqualToString:RAWTEXT];
}

- (float) changeSize:(float) initValue key:(NSString *)key {
    
    float translatedValue = initValue;
    float xScaleFactor = (float)WIDTH_XML_ARTBOARD/WIDTH_XD_ARTBOARD;
    float yScaleFactor = (float)HEIGHT_XML_ARTBOARD/HEIGHT_XD_ARTBOARD;
    if ([key isEqualToString:XARTBOARD]) {
        translatedValue = initValue - startXArtboard;
        translatedValue = translatedValue * xScaleFactor;
    }
    else if ([key isEqualToString:YARTBOARD]) {
        translatedValue = initValue - startYArtboard;
        translatedValue = translatedValue * yScaleFactor;
    } else if ([key isEqualToString:WIDTH]) {
        translatedValue = initValue * xScaleFactor;
    }
    else if ([key isEqualToString:HEIGHT]) {
        translatedValue = initValue * yScaleFactor;
    }

    return translatedValue;
}

- (CGRect) computeTextFrame:(NSString *) label usingFontSize:(int) fontSize {
    
    NSString *firstLine = [label substringToIndex:textLen];
    
    NSMutableParagraphStyle *style = [[NSParagraphStyle defaultParagraphStyle] mutableCopy];
    [style setLineBreakMode:NSLineBreakByWordWrapping];
    
    NSDictionary *attributes = @{NSFontAttributeName: [NSFont systemFontOfSize:fontSize],
                                 NSParagraphStyleAttributeName: style};
    
    CGRect lineFrame = [firstLine boundingRectWithSize:CGSizeMake(CGFLOAT_MAX, CGFLOAT_MAX)
                                               options:NSStringDrawingUsesLineFragmentOrigin
                                            attributes:attributes
                                               context:nil];
    
    float width = lineFrame.size.width  + 0.1 * lineFrame.size.width;
    return [label boundingRectWithSize:CGSizeMake(width, CGFLOAT_MAX)
                                      options:NSStringDrawingUsesLineFragmentOrigin
                                   attributes:attributes
                                      context:nil];


}

- (void) merge:(NSMutableDictionary *) dictValue withDict:(NSMutableDictionary **) objDict
   withDefDict:(NSMutableDictionary *)defaultDict forValue:(NSString *) value key:(NSString *) key {
    
    
    if (![value hasPrefix:TOTRANSFORM]) {
        [*objDict setValue:value forKey:key]; /* no need for transformation */
    } else if ([dictValue objectForKey:[[self splitVariable:value] objectAtIndex:0]]) {
        
        id tvalue = [[self splitVariable:value] objectAtIndex:0];
        
        if ([self isOfTypeSize:key]) {
            /* changing size here */
            
            float initValue = [[dictValue objectForKey:tvalue] floatValue];
            float translatedValue = [self changeSize:initValue key:key];
            
            [*objDict setValue:[NSNumber numberWithInt:translatedValue] forKey:key];
        } else {
            [*objDict setValue:[dictValue objectForKey:tvalue] forKey:key];
            
        }
        
        /* check if width/height needs to be computed (eg. text frame) */
        if ( [self isTextFrame:tvalue templateDict:*objDict]) {
            
            /* then we must compute the width/height of the text frame*/
            /*FIX ME: assumed that the text font is the NSFont */
            /* we have the height = text; width = fontSize; */
            
            [*objDict setValue:[dictValue objectForKey:tvalue] forKey:key];
            
            NSString *label = [*objDict objectForKey:HEIGHT];
            int fontSize = [[*objDict objectForKey:WIDTH] intValue];
            
            CGRect rect = [self computeTextFrame:label usingFontSize:fontSize];
            
            [*objDict setValue:[NSNumber numberWithFloat:rect.size.height] forKey:HEIGHT];
            [*objDict setValue:[NSNumber numberWithFloat:rect.size.width + 0.1 * rect.size.width] forKey:WIDTH];
            
        }
        
        /*if we have a special operation to perform eg. getSize from path*/
    } else if ([value hasPrefix:GETHEIGHT] || [value hasPrefix:GETWIDTH]) {
        NSNumber *size = [self getFrameSizeFromPath:value dict:dictValue];
        [*objDict setObject:size forKey:key];
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
                    
                    float color = [value floatValue] / 255;
                    [*objDict setObject:[NSString stringWithFormat:@"%f", color] forKey:key];
                    continue;
                }
                
                if ([self isOfTypeScale:key object:type]) {
                    
                    float initValue = [value floatValue];
                    float translatedValue = [self changeSize:initValue key:key];
                    [*objDict setObject:[NSNumber numberWithFloat:translatedValue] forKey:key];
                    continue;
                }
                [*objDict setObject:value forKey:key];
                
            } else {
                /* use values specified from agc */
                value = [paramsValue objectForKey:key];
                
                if (!value)
                    continue;
                
                [self merge:dictValue withDict:objDict withDefDict:defaultDict forValue:value key:key];
                
            }
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
                
                if (![subValue isEqualToString:[gotoTag lastObject]])
                    continue;
                
                else {
                    
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
    if (x <= *minx)  {
        *minx = x;
    }
    if (y <= *miny) {
        *miny = y;
    }
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
    widthXDArtboard = WIDTH_XML_ARTBOARD;
    heightXDArtboard = HEIGHT_XML_ARTBOARD;
    int prevX = startXArtboard;
    int prevY = startYArtboard;
    startXArtboard = 0;
    startYArtboard = 0;
    
    NSMutableArray *viewSubviews = [[NSMutableArray alloc] init];
    
    [self processGroup:[[object objectForKey:GROUP] objectForKey:CHILDREN]
            newObjDict:newObjDict
              subviews:&viewSubviews
             finalDict:finalDict
                  minx:minx
                  miny:miny
                  maxx:maxx
                  maxy:maxy
                  maxh:maxh
                  maxw:maxw];
    
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

-(NSMutableDictionary *) computeObjects:(NSString *)rule condition:(NSArray*)cond params:(NSDictionary *)dict
                                agcDict:agcParams type:(NSString *)type {
    
    
    id objDict;
    if ([rule isEqualToString:SUBVIEWS])
        objDict = [NSKeyedUnarchiver unarchiveObjectWithData:[NSKeyedArchiver archivedDataWithRootObject:[agcToXmlTemplate objectForKey:SUBVIEWS]]];
    else {
        
        objDict = [NSKeyedUnarchiver unarchiveObjectWithData:[NSKeyedArchiver archivedDataWithRootObject:[[agcToXmlTemplate objectForKey:SUBTAGS] objectForKey:rule]]];
    }
    
    // now changing based on params
    if (!cond) {
        //just generate the tag; no other transformations are needed
        return objDict;
    }
    //get values from agc in order to transfer them into xml
    for (id condition in cond) {
        id values = agcParams;
        
        NSArray *goToAgc = [self splitVariable:condition];
        [self getDict:&values fromConditions:goToAgc];
        
        NSMutableDictionary *dictValue = values;
        BOOL isEmpty = ([dictValue count] == 0);
        if (isEmpty && !dictValue) {
            //use default values!!!
            
            [self mergeDefaultValues:[objDict objectForKey:DEFAULT] withDict:&objDict usingDict:dict];
            return objDict;
            
        } else if (isEmpty) {
            //no subview found
            return nil;
            
        } else {
            
            id subRules = [dict objectForKey:condition];
            
            if ([subRules isKindOfClass:[NSMutableDictionary class]] && [subRules objectForKey:LEN]) {
                
                int counter = (int)[dictValue count];
                
                textLines = MAX(counter, [[objDict objectForKey:LEN] intValue]);
                
                [objDict setObject:[NSNumber numberWithInt:textLines] forKey:LEN];
                
                
                id tmp = dictValue;
                id firstLine;
                
                if (textLines == counter && [condition isEqualToString:TEXT_LINES]) {
                    firstLine = [[[tmp objectAtIndex:0] objectAtIndex:0]objectForKey:TO];
                    textLen = [firstLine intValue];
                } else if (textLines == counter && [condition isEqualToString:TEXT_PARAGRAPH]) {
                    tmp = [[tmp objectAtIndex:0] objectForKey:LINE_VALUE];
                    firstLine = [[[tmp objectAtIndex:0] objectAtIndex:0]objectForKey:TO];
                    textLen = [firstLine intValue];
                }
                
                continue;
            }
            if ([subRules isKindOfClass:[NSMutableDictionary class]] && [subRules objectForKey:TYPE] &&
                [[subRules objectForKey:TYPE] isEqualToString:STYLE]) {
                
                id styleFont = [dictValue objectForKey:STYLE_VALUE];
                id translatedStyle = [self convertFont:styleFont];
                
                [[dict objectForKey:condition] setObject:translatedStyle forKey:TYPE];
                
                
            }
            if (![dictValue isKindOfClass:[NSArray class]]) {
                
                [self mergeDictionaries:&objDict withDict:dictValue usingValues:[dict objectForKey:condition] type:type];
                
            }
            else {
                
                
                NSMutableDictionary *finalDict = [NSKeyedUnarchiver unarchiveObjectWithData:[NSKeyedArchiver archivedDataWithRootObject: [agcToXmlTemplate objectForKey:SUBVIEWS]]];
                NSMutableDictionary *newObjDict = [NSKeyedUnarchiver unarchiveObjectWithData:[NSKeyedArchiver archivedDataWithRootObject: [objDict mutableCopy]]];
                objDict = [[NSMutableArray alloc] init];
                
                
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
                    
                    NSMutableDictionary *typeObjDict = [NSKeyedUnarchiver unarchiveObjectWithData:[NSKeyedArchiver archivedDataWithRootObject: [newObjDict objectForKey:type]]];
                    
                    
                    if ([type isKindOfClass:[NSString class]] && [type isEqualToString:GROUP]) {
                        int minx = 600, miny = 600, maxx = 0, maxy = 0, maxw = 0, maxh = 0;
                        [self computeGroup:newObjDict agcDict:object finalDict:finalDict retDict:&objDict
                         minx:&minx miny:&miny maxx: &maxx maxy:&maxy maxh: &maxh maxw: &maxw];
                        
                        continue;
                    }
                    
                    [self processTemplateDict:&typeObjDict agcDict:object finalDict:finalDict ofType:type];
                    
                    NSMutableDictionary *subViewDict = [[NSMutableDictionary alloc] init ];
                    [subViewDict setObject:typeObjDict forKey:type];
                    [objDict addObject:subViewDict];
                }
                
            }
        }
        
        
    }
    return objDict;
    
    
    
}

-(NSDictionary*) processTemplateDict:(NSMutableDictionary **) templateDict agcDict:(NSDictionary *)agcDict
                           finalDict:(NSMutableDictionary *)finalDict ofType:(NSString *) type {
    
    noOfElements++;
    NSMutableDictionary *rulesInitDict = [*templateDict objectForKey:RULES];
    NSMutableDictionary *rulesTempDict = [rulesInitDict mutableCopy];
    NSArray *keys, *cond;
    NSMutableDictionary *rulesDict, *mergeDict;
    NSString *value, *stringValue;
    id rulesByOrder, val;
    
    
    /* if an order is specified => follow it
     * otherwis use the default enumerator */
    if ([rulesTempDict objectForKey:ORDER])
        rulesByOrder = [rulesTempDict objectForKey:ORDER];
    else rulesByOrder = rulesTempDict;
    
    for (id rule in rulesByOrder) {
        
        keys = [self splitVariable:rule];
        if ([keys count] == 1) {
            
            //goto "subviews" dictionary
            rulesDict = [rulesTempDict objectForKey:rule];
            
            if ([rulesDict isKindOfClass:[NSArray class]])
                continue;
            
            if ([rulesDict count] == 0)
                cond = nil;
            else if ([rulesDict objectForKey:ORDER])
                cond = [rulesDict objectForKey:ORDER];
            else
                cond = [rulesDict allKeys];
            
            mergeDict = [self computeObjects:rule condition:cond params:[rulesTempDict objectForKey:rule] agcDict:agcDict type:type];
            
            if (mergeDict != nil) {
                
                [rulesInitDict setObject:mergeDict forKey:rule];
                
            }
            
        } else {
            
            val = *templateDict;
            
            for (id key in [keys subarrayWithRange:NSMakeRange(0, [keys count] -1)]) {
                val = [val objectForKey:key];
            }
            
            value = [self computeValue:[rulesTempDict objectForKey:rule] forDict:agcDict];
            
            if ([[value componentsSeparatedByString:@" "] count] == 1) {
                id hasValue = [val objectForKey:[keys lastObject]];
                
                if (hasValue && [hasValue intValue]){
                    int max = MAX([hasValue intValue], [value intValue]);
                    [val setObject:[NSNumber numberWithInt:max] forKey:[keys lastObject]];
                }
                else [val setObject:value forKey:[keys lastObject]];
                
            } else {
                
                stringValue = [NSString stringWithFormat:@"\"%@\"", value];
                
                [val setObject:stringValue forKey:[keys lastObject]];
                
            }
            
        }
        
    }
    
    return finalDict;
}

-(NSDictionary*) processWholeXmlFromAgc:(NSDictionary *)agcDict {
    
    NSMutableDictionary *finalDict = [NSKeyedUnarchiver unarchiveObjectWithData:[NSKeyedArchiver archivedDataWithRootObject: [agcToXmlTemplate objectForKey:CONTENT]]];
    
    
    NSMutableDictionary *viewDict = [finalDict objectForKey:ARTBOARD];
    
    return [self processTemplateDict:&viewDict agcDict:agcDict finalDict:finalDict ofType:VIEW];
    
}

/* in caser of whole file translation => extend with header and footer */
-(NSString *) surroundWithHeader:(NSString *) header footer:(NSString *) footer string:(NSString *)str {
    
    
    return [NSString stringWithFormat:@"%@\n%@\n%@", header, str, footer];
    
}

-(void) copyImage:(NSImage *)image toProject:(NSString *)fileName {
    
    NSString *resourcesXmlProj = [NSString stringWithFormat:@"%@%@/%@",[self xmlPath], RESOURCES_PATH, fileName];
    NSString *resourcesXmlRes = [NSString stringWithFormat:@"%@%@",[self xmlPath], RESOURCES_PATH];
    
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
        
        NSImage *image = [[NSImage alloc]initWithContentsOfFile:href];
        
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
        }
        
        
        NSString *str = [self toString:imageDict name:ISIMAGE isLeaf:TRUE];
        
        [[dict objectForKey:HEADER]  setObject:theFileName forKey:ISIMAGE];
        
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
            
        } else if ([[agcToXmlTemplate objectForKey:SUBTAGS] objectForKey:key]){
            BOOL inBetween = [[[agcToXmlTemplate objectForKey:SUBTAGS] objectForKey:key]objectForKey:BETWEEN] == nil;
            
            /* just an ordinary leaf tag; create a one-line with the given attributes */
            NSString *ret = [self toString:attr name:key isLeaf:inBetween];
            [ tmp appendString: [NSString stringWithFormat:@"\n\t%@", ret]];
   
        }
    }
    
    return tmp;
    
    
}

-(bool) generateSceneHeaderUsingString:(NSMutableString **)finalString withInitialArtboard:(NSString*) initialArtboard
                           sceneOffset:(long)offset isInitialSet:(bool) setInitial dictionary:(NSDictionary *)dict {
    
    [*finalString appendString: SCENEHEADERA];
    [*finalString appendString: [[NSUUID UUID] UUIDString]];
    
    [*finalString appendString: SCENEHEADERB];
    if (!setInitial) {
        [*finalString appendString: initialArtboard];
        setInitial = true;
    }
    else
        [*finalString appendString: [[NSUUID UUID] UUIDString]];
    
    [*finalString appendString: SCENEHEADERC];
    [*finalString appendString: [[NSUUID UUID] UUIDString]];
    [*finalString appendString: SCENEHEADERD];
    [*finalString appendString: [[NSUUID UUID] UUIDString]];
    [*finalString appendString: SCENEHEADERE];
    
    [*finalString appendString: [self parseToString:*finalString dict:dict name: ARTBOARD]];
    [*finalString appendString: XMLVIEWF];
    [*finalString appendString:XMLFOOTERA];
    [*finalString appendString: [[NSUUID UUID] UUIDString]];
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
    if ([self outXmlPath])
        [xmlData writeToFile:[self outXmlPath] atomically:YES];
    
}

-(NSString*) getXmlForAgcObject:(NSDictionary*)typeAgcObject{
    
    NSMutableString *xmlGen = [NSMutableString stringWithFormat:@""];
    NSMutableArray *arrayOfScenes = [[NSMutableArray alloc] init];
    NSMutableString *finalString;
    NSDictionary *dict;
    NSMutableString *stringFooter = [NSMutableString stringWithFormat:XMLSCENESF];
    NSString *initialArtboard, *resources, *xmlHeader, *xmlFile;
    BOOL setInitial = false;
    long sceneOffset = XML_SCENE_X;
    int artboardsNo;
    
    // it was given the whole dictionary to process => goto @"content"; type = "view"
    artboardsNo = (int)[[typeAgcObject objectForKey:ARTBOARDS] count];
    
    initialArtboard = [[NSUUID UUID] UUIDString];
    
    while (sceneNo < artboardsNo) {
        finalString = [[NSMutableString alloc] init];
        
        dict = [[self processWholeXmlFromAgc:typeAgcObject] objectForKey: ARTBOARD];
        sceneOffset = sceneOffset + XML_OFFSET_X;
        
        setInitial = [self generateSceneHeaderUsingString:&finalString
                                      withInitialArtboard:initialArtboard
                                              sceneOffset:sceneOffset
                                             isInitialSet:setInitial
                                               dictionary:dict];
        NSLog(@"Nr = %d", [[sceneMapping objectForKey:[NSNumber numberWithInt:sceneNo]]intValue]);
        [arrayOfScenes insertObject:finalString atIndex:[[sceneMapping objectForKey:[NSNumber numberWithInt:sceneNo]]intValue]];
        [xmlGen appendString:finalString];
        ++sceneNo;
        
    }
    
    NSString *tempStr = [NSMutableString stringWithFormat:@""];
    for (int i = 0; i< [arrayOfScenes count] ; i++) {
        NSLog(@"Val = %@", [arrayOfScenes objectAtIndex:i]);
        tempStr = [tempStr stringByAppendingString:[arrayOfScenes objectAtIndex:i]];
    }
    xmlGen = [tempStr mutableCopy];
    NSLog(@"tempStr = %@", tempStr);
    NSLog(@"There are %d artboards and ~ %d properties computed", sceneNo, noOfElements);
    if ([resourcesDict length]) {
        // append resources
        resources = [NSString stringWithFormat:@"%@\n%@\n%@",XMLRESOURCES, resourcesDict, XMLRESOURCESF];
        [stringFooter appendString:resources];
    }
    
    [stringFooter appendFormat:@"\n%@", XMLDOCUMENTF];
    xmlHeader =  [self surroundWithHeader:XMLHEADERA footer:XMLHEADERB string:initialArtboard];
    xmlFile = [self surroundWithHeader:xmlHeader footer:stringFooter string:xmlGen];
    
    [self writeXmlString:xmlFile];
    
    
    return xmlGen;
    
}



- (id)initWithError:(NSError **)error
{
    return self;
}

@end
