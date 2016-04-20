//
//  XMLGenerator.m
//  XMLParser
//
//  Created by crogoz on 07/04/16.
//  Copyright © 2016 crogoz. All rights reserved.
//

#import "XMLGenerator.h"

#import <Foundation/Foundation.h>
#import <CoreData/CoreData.h>

@import AppKit;
@implementation XMLGenerator

+ (void)readTemplateUsingXML:(NSString *)xmlPath
{
    NSError *error;
    
    NSBundle *thisBundle = [NSBundle bundleForClass:[self class]];
    NSString *def = [thisBundle pathForResource:DEF_PATH ofType:JSON];
    NSString *rule = [thisBundle pathForResource:RULES_PATH ofType:JSON];
    NSString *test = [thisBundle pathForResource:TESTMULTTEXT_PATH ofType:JSON];
    
    XMLGenerator *gen = [[XMLGenerator alloc] initWithError:&error];
    NSData *defData = [NSData dataWithContentsOfFile:def];
    
    
    NSData *ruleData = [NSData dataWithContentsOfFile:rule];
    
    
    NSMutableDictionary *defDictionary = [NSJSONSerialization JSONObjectWithData:defData options:NSJSONReadingMutableContainers error:&error];
    
    NSDictionary *ruleDictionary = [NSJSONSerialization JSONObjectWithData:ruleData options:NSJSONReadingMutableContainers error:&error];
    [gen setXmlPath:xmlPath];
    [gen initializeWithDefs:defDictionary rules:ruleDictionary];
    
    NSMutableDictionary *agcTemplate = [[NSMutableDictionary alloc] init];
    
    NSData *testData = [NSData dataWithContentsOfFile:test ];//TESTPARAGROUP_PATH ];//TESTTEXT_PATH];//
    agcTemplate =  [NSJSONSerialization JSONObjectWithData:testData options:kNilOptions error:&error];

    [gen getXmlForAgcObject:agcTemplate];

    
}


-(void)initializeWithDefs:(NSDictionary*)defDict rules:(NSDictionary*)ruleDict {
    agcToXmlTemplate = [defDict mutableCopy];
    translationDict = [ruleDict mutableCopy];
    resourcesDict = [[NSMutableString alloc] init];
    
    transformObjects = [[NSMutableDictionary alloc] init];
    transformObjects[SIZE] = [[NSMutableDictionary alloc] init];
    transformObjects[SIZE][XARTBOARD] = [NSNumber numberWithInt:1];
    transformObjects[SIZE][YARTBOARD] = [NSNumber numberWithInt:1];
    
    transformObjects[COLOR] = [[NSMutableDictionary alloc] init];
    transformObjects[COLOR][RED] = [NSNumber numberWithInt:1];
    transformObjects[COLOR][GREEN] = [NSNumber numberWithInt:1];
    transformObjects[COLOR][BLUE] = [NSNumber numberWithInt:1];
    
    sceneNo = 0;
    
    
}


-(NSString *) computeValue:(NSString *)initValue forDict:(NSDictionary *)agcDict {
    
    NSLog(@"IV: %@", initValue);
    if ([initValue isEqualToString:RANDOM]) {
        //generate a random value; needed for id
        return [[NSUUID UUID] UUIDString];
        
    } else if ([initValue hasPrefix:GETMAX]) {
        
        NSRange range = [initValue rangeOfString:GETMAX];
        NSArray *max2 = [[initValue substringFromIndex:range.location + GETMAX.length + 1] componentsSeparatedByString:SPACE];
       
        id first = [self computeValue:[max2 objectAtIndex:0] forDict:agcDict];
        id second = [self computeValue:[max2 objectAtIndex:1] forDict:agcDict];
        int ret = MAX([first intValue], [second intValue]);
        
        return [NSString stringWithFormat:@"%d", ret];
        
        
    
    } else {
        //if it depends on an agc tag
        initValue = [initValue substringFromIndex:1];
        NSArray *array = [initValue componentsSeparatedByString:DOT];
        
        id value = agcDict;
        for (id key in array) {
            
            if ([key isEqualToString:COUNT]) {
                NSLog(@"Counter found %@", agcDict);
                return [ NSString stringWithFormat:@"%d", (int)[value count]];
            }
            if ([key isEqualToString:LINES])
                value = [value objectAtIndex:0];
            else
                value = [value objectForKey:key];
            
            
        }
        
        return value;
        
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

-(void) mergeDictionaries:(NSMutableDictionary **)objDict withDict:(NSMutableDictionary *)dictValue
              usingValues:(NSDictionary *)paramsValue {
    
    
    NSMutableDictionary *defaultDict = [*objDict objectForKey:DEFAULT];
    
    for (id key in [*objDict allKeys]) {
        id value = [*objDict objectForKey:key];
        
        if ([value isKindOfClass:[NSString class]] && [value hasPrefix:TOTRANSFORM]) {
            value = [dictValue objectForKey:[value substringFromIndex:1]];
            
            if (value) {
                
                /*if ([[transformObjects objectForKey:SIZE] objectForKey:key]) {
                     changing the size -> scale 
                    float translatedValue;
                   
                    float xScaleFactor = (float)widthXDArtboard / WIDTHXMLARTBOARD;
                    float yScaleFactor = (float)heightXDArtboard / HEIGHTXMLARTBOARD;
                    if ([key isEqualToString:XARTBOARD]) {
                        translatedValue = [value floatValue] - startXArtboard;
                        translatedValue = translatedValue * xScaleFactor;
                    }
                    else {
                        translatedValue = [value floatValue] - startYArtboard;
                        translatedValue = translatedValue * yScaleFactor;
                    }
                    
                    [*objDict setObject:[NSNumber numberWithFloat:translatedValue] forKey:key];
                    continue;
                    
                } else */if ([[transformObjects objectForKey:COLOR] objectForKey:key]) {
                    /* change the color */
                    float color = [value floatValue] / 255;
                    [*objDict setObject:[NSString stringWithFormat:@"%f", color] forKey:key];
                    continue;
                }
                [*objDict setObject:value forKey:key];
                
            } else {
                /* use values specified from agc */
                value = [paramsValue objectForKey:key];
                
                if (!value)
                    continue;
                
                if (![value hasPrefix:TOTRANSFORM]) {
                    
                    [*objDict setValue:value forKey:key]; /* no need for transformation */
                } else if ([dictValue objectForKey:[[self splitVariable:value] objectAtIndex:0]]) {
                    
                    id tvalue = [[self splitVariable:value] objectAtIndex:0];
                    
                    if ([[transformObjects objectForKey:@"size"] objectForKey:key]) {
                        /* changing size here */
                        
                        
                        float initValue = [[dictValue objectForKey:tvalue] floatValue];
                        float translatedValue = initValue;
                        float xScaleFactor = (float)WIDTHXMLARTBOARD/WIDTHXDARTBOARD;
                        float yScaleFactor = (float)HEIGHTXMLARTBOARD/HEIGHTXDARTBOARD;
                        
                        if ([key isEqualToString:XARTBOARD]) {
                            translatedValue = initValue - startXArtboard;
                            translatedValue = translatedValue * xScaleFactor;
                        }
                        else if ([key isEqualToString:YARTBOARD]) {
                            translatedValue = initValue - startYArtboard;
                            translatedValue = translatedValue * yScaleFactor;
                        }
                       
                        [*objDict setValue:[NSNumber numberWithInt:translatedValue] forKey:key];
                    } else
                        [*objDict setValue:[dictValue objectForKey:tvalue] forKey:key];
                    
                    /* check if width/height needs to be computed (eg. text frame) */
                    if ([tvalue isEqualToString:SIZE] && ![[*objDict objectForKey:HEIGHT] isEqualToString:RAWTEXT]) {
                        
                        /* then we must compute the width/height of the text frame*/
                        /*FIX ME: assumed that the text font is the NSFont */
                        /* we have the height = text; width = fontSize; */
                        
                        [*objDict setValue:[dictValue objectForKey:tvalue] forKey:key];
                        
                        NSString *label = [*objDict objectForKey:HEIGHT];
                        
                        NSString *firstLine = [label substringToIndex:textLen];
                        int fontSize = [[*objDict objectForKey:WIDTH] intValue];
                        
                        
                        NSMutableParagraphStyle *style = [[NSParagraphStyle defaultParagraphStyle] mutableCopy];
                        [style setLineBreakMode:NSLineBreakByWordWrapping];
                        
                        NSDictionary *attributes = @{NSFontAttributeName: [NSFont systemFontOfSize:fontSize],
                                                      NSParagraphStyleAttributeName: style};
                        
                        CGRect lineFrame = [firstLine boundingRectWithSize:CGSizeMake(CGFLOAT_MAX, CGFLOAT_MAX)
                                                                   options:NSStringDrawingUsesLineFragmentOrigin
                                                                attributes:attributes
                                                                   context:nil];
                        
                        float width = lineFrame.size.width  + 0.1 * lineFrame.size.width;
                        CGRect rect = [label boundingRectWithSize:CGSizeMake(width, CGFLOAT_MAX)
                                                                  options:NSStringDrawingUsesLineFragmentOrigin
                                                               attributes:attributes
                                                                  context:nil];
                        
                        [*objDict setValue:[NSNumber numberWithFloat:rect.size.height] forKey:HEIGHT];
                        [*objDict setValue:[NSNumber numberWithFloat:rect.size.width + 0.1 * rect.size.width] forKey:WIDTH];
                        
                    }
                    
                    
                } else {/* use default values */
                    [*objDict setObject:[defaultDict objectForKey:key] forKey:key];
                }
                
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
-(NSMutableDictionary *) computeObjects:(NSString *)rule condition:(NSArray*)cond params:(NSDictionary *)dict agcDict:agcParams{
    
    id objDict;
    if ([rule isEqualToString:SUBVIEWS])
        objDict = [[agcToXmlTemplate objectForKey:SUBVIEWS] mutableCopy];
    else
        objDict = [[[agcToXmlTemplate objectForKey:SUBTAGS] objectForKey:rule] mutableCopy];
    
    // now changing based on params
    if (!cond) {
        //just generate the tag; no other transformations are needed
        return objDict;
        
    }
    //get values from agc in order to transfer them into xml
    
    for (id condition in cond) {
        id values = agcParams;
       
        NSArray *goToAgc = [self splitVariable:condition];
       
        for (id key in goToAgc) {
            
            id nodeValue;
            
            if ([key hasPrefix:TOTRANSFORM] && [key isEqualToString:SCENENO]) {
                nodeValue = [values objectAtIndex:sceneNo];
                
            } else if ([key hasPrefix:TOTRANSFORM] && [key isEqualToString:ARTBOARDSCENE]) {
                NSString *artboard = [NSString stringWithFormat:@"artboard%d", sceneNo +1];
                nodeValue = [values objectForKey:artboard];

                /* obtain the startX and startY for the current scene */
                startXArtboard = [[nodeValue objectForKey:XARTBOARD] intValue];
                startYArtboard = [[nodeValue objectForKey:YARTBOARD] intValue];
                
                widthXDArtboard = [[nodeValue objectForKey:WIDTH] intValue];
                heightXDArtboard = [[nodeValue objectForKey:HEIGHT] intValue];
                
            } else if ([key hasPrefix:TOTRANSFORM] && [key isEqualToString:LINES]){
                nodeValue = [values objectAtIndex:0];
            } else if ([key hasPrefix:TOTRANSFORM] && [key isEqualToString:LINESDICT]){
                nodeValue = [values objectForKey:[NSNumber numberWithInt:0]];
            } else {
            
                nodeValue = [values objectForKey:key];
                
            }
            
            values = nodeValue;
        }
        
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
                
                id translatedStyle;
                
                if ([styleFont isEqualToString:REGULAR])
                    translatedStyle = FONT_SYSTEM;
                else if ([styleFont isEqualToString:ITALIC])
                    translatedStyle = FONT_ITALIC;
                else if ([styleFont isEqualToString:BOLD])
                    translatedStyle = FONT_BOLD;
                
                [[dict objectForKey:condition] setObject:translatedStyle forKey:TYPE];
                
            
            }
            if (![dictValue isKindOfClass:[NSArray class]]) {
                
                [self mergeDictionaries:&objDict withDict:dictValue usingValues:[dict objectForKey:condition]];
                
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
                    
                   
                    
                    NSMutableDictionary *typeObjDict = [NSKeyedUnarchiver unarchiveObjectWithData:[NSKeyedArchiver archivedDataWithRootObject: [newObjDict objectForKey:type]]];
                    
                    int minx = WIDTHXMLARTBOARD;
                    int miny = HEIGHTXMLARTBOARD;
                    int maxx = 0;
                    int maxy = 0;
                    int maxh = 0;
                    int maxw = 0;
                    
                   
                    if ([type isEqualToString:GROUP]) {
                        
                        NSMutableDictionary *viewDict = [newObjDict objectForKey:VIEW];
                        [self processTemplateDict:&viewDict agcDict:object finalDict:finalDict];
                        
                        
                        id sizeFrame = [[viewDict objectForKey:RULES] objectForKey:FRAME];
                        
                        int x = [[sizeFrame objectForKey:XARTBOARD] intValue];
                        int y = [[sizeFrame objectForKey:YARTBOARD] intValue];
                        
                        
                        int prevWidth = widthXDArtboard;
                        int prevHeight = heightXDArtboard;
                        widthXDArtboard = WIDTHXMLARTBOARD;
                        heightXDArtboard = HEIGHTXMLARTBOARD;
                        int prevX = startXArtboard;
                        int prevY = startYArtboard;
                        startXArtboard = x - startXArtboard;
                        startYArtboard = y - startYArtboard;
                        
                        NSMutableArray *viewSubviews = [[NSMutableArray alloc] init];
                        
                        
                        for (id key in [[object objectForKey:GROUP] objectForKey:CHILDREN]) {
                            id type = [translationDict objectForKey:[key objectForKey:TYPE]];
                           
                            
                            if (!type)
                                continue;
                            
                            type = [self getShapeType:type object:object];
                            NSMutableDictionary *typeObjDict = [NSKeyedUnarchiver unarchiveObjectWithData:[NSKeyedArchiver archivedDataWithRootObject: [newObjDict objectForKey:type]]];
                            
                            [self processTemplateDict:&typeObjDict agcDict:key finalDict:finalDict];
                            
                            id groupFrame = [[typeObjDict objectForKey:RULES] objectForKey:FRAME];
                            
                            int x = [[groupFrame objectForKey:XARTBOARD] intValue];
                            int y = [[groupFrame objectForKey:YARTBOARD] intValue];
                            int w = [[groupFrame objectForKey:WIDTH] intValue];
                            int h = [[groupFrame objectForKey:HEIGHT] intValue];
                            
                            if (x <= minx && y <= miny) {
                                minx = x;
                                miny = y;
                            }
                            if (x + w >= maxx && y + h >= maxy) {
                                maxx = x + w;
                                maxy = y + h;
                                maxh = h;
                                maxw = w;
                            }
                                
                            
                            NSMutableDictionary *subViewDict = [[NSMutableDictionary alloc] init ];
                            [subViewDict setObject:typeObjDict forKey:type];
                            [viewSubviews addObject:subViewDict];
                            
                        }
                        
                       
                        widthXDArtboard = prevWidth;
                        heightXDArtboard = prevHeight;
                        startXArtboard = prevX;
                        startYArtboard = prevY;
                        int widthFrame = maxx - minx + maxw;
                        int heightFrame = maxy - miny + maxh;
                        
                        [sizeFrame setObject:[NSNumber numberWithInt:minx] forKey:XARTBOARD];
                        [sizeFrame setObject:[NSNumber numberWithInt:miny] forKey:YARTBOARD];
                        [sizeFrame setObject:[NSNumber numberWithInt:widthFrame] forKey:WIDTH];
                        [sizeFrame setObject:[NSNumber numberWithInt:heightFrame] forKey:HEIGHT];

                        
                        
                        for (id keyObject in viewSubviews) {
                            id name = [[keyObject allKeys] objectAtIndex:0];
                            id frame = [[[keyObject objectForKey:name ] objectForKey:RULES] objectForKey:FRAME];
                            int x = [[frame objectForKey:XARTBOARD] intValue];
                            x = x - minx;
                            int y = [[frame objectForKey:YARTBOARD] intValue];
                            y = y - miny;
                            [frame setObject:[NSNumber numberWithInt:x] forKey:XARTBOARD];
                            [frame setObject:[NSNumber numberWithInt:y] forKey:YARTBOARD];
                        
                        }
                        [[viewDict objectForKey:RULES ] setObject:viewSubviews forKey:SUBVIEWS];
                        NSMutableDictionary *subViewTmp = [[NSMutableDictionary alloc] init ];
                        [subViewTmp setObject:viewDict forKey:VIEW];
                        
                        [objDict addObject:subViewTmp];
                       
                        continue;
                    }
                    
                    
                    [self processTemplateDict:&typeObjDict agcDict:object finalDict:finalDict];
                    
                    NSMutableDictionary *subViewDict = [[NSMutableDictionary alloc] init ];
                    [subViewDict setObject:typeObjDict forKey:type];
                    [objDict addObject:subViewDict];
                }
                
            }
        }
        
        
    }
    return objDict;
    
    
    
}

-(NSDictionary*) processTemplateDict:(NSMutableDictionary **) templateDict agcDict:(NSDictionary *)agcDict finalDict:(NSMutableDictionary *)finalDict{
    
    NSMutableDictionary *rulesInitDict = [*templateDict objectForKey:RULES];
    NSMutableDictionary *rulesTempDict = [rulesInitDict mutableCopy];
    
    for (id rule in rulesTempDict) {
        
        NSArray *keys = [self splitVariable:rule];
        
        
        if ([keys count] == 1) {
            
            //goto "subviews" dictionary
           
            NSMutableDictionary *rulesDict = [rulesTempDict objectForKey:rule];
            
            if ([rulesDict isKindOfClass:[NSArray class]])
                continue;
            
            
            NSArray *cond;
            if ([rulesDict count] == 0)
                cond = nil;
            else if ([rulesDict objectForKey:ORDER])
                cond = [rulesDict objectForKey:ORDER];
            else
                cond = [rulesDict allKeys];
            
            
            NSMutableDictionary *mergeDict = [self computeObjects:rule condition:cond params:[rulesTempDict objectForKey:rule] agcDict:agcDict];
            
            if (mergeDict != nil) {
                
                [rulesInitDict setObject:mergeDict forKey:rule];
               
            }
            
        } else {
            
            
            id val = *templateDict;
            
            for (id key in [keys subarrayWithRange:NSMakeRange(0, [keys count] -1)]) {
                val = [val objectForKey:key];
            }
            
            NSString *value = [self computeValue:[rulesTempDict objectForKey:rule] forDict:agcDict];
           
            
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
        
    }
    
    return finalDict;
}

-(NSDictionary*) processWholeXmlFromAgc:(NSDictionary *)agcDict {
    
    NSMutableDictionary *finalDict = [NSKeyedUnarchiver unarchiveObjectWithData:[NSKeyedArchiver archivedDataWithRootObject: [agcToXmlTemplate objectForKey:@"content"]]];
    
    
    NSMutableDictionary *viewDict = [finalDict objectForKey:ARTBOARD];
    
    return [self processTemplateDict:&viewDict agcDict:agcDict finalDict:finalDict];
    
}

/* in caser of whole file translation => extend with header and footer */
-(NSString *) surroundWithHeader:(NSString *) header footer:(NSString *) footer string:(NSString *)str {
    
    
    return [NSString stringWithFormat:@"%@\n%@\n%@", header, str, footer];
    
}

-(NSMutableString *) parseToString:(NSMutableString *)str dict:(NSDictionary *)dict name:(NSString *) name{
    
    NSMutableString* tmp = [NSMutableString stringWithFormat:@""];
    
    
    /* now we only have to translate the currentDict */
    for (id key in [dict objectForKey:TOSTRING]) {
        
        id attr = [dict objectForKey:key];
        
        if ([attr isKindOfClass:[NSDictionary class]] && [attr objectForKey:ISIMAGE]) {
            /* add image in the resources tag */
            NSString * href = [attr objectForKey:ISIMAGE];
            /* find width and height for image */
            
            
            /* TODO copy the image into the xcode project!!! */
            /* TODO get only the name of the file */
            NSImage *image = [[NSImage alloc]initWithContentsOfFile:href];
            /* create an image Tag using subTags */
            NSMutableDictionary *imageDict = [[[agcToXmlTemplate objectForKey:SUBTAGS] objectForKey:ISIMAGE] mutableCopy];
            NSString *theFileName = [href lastPathComponent];
           
            imageDict[NAME] = theFileName;
            
            imageDict[WIDTH] = [NSString stringWithFormat:@"%f", image.size.width];
            imageDict[HEIGHT] = [NSString stringWithFormat:@"%f", image.size.height];
            
            NSArray *rootarray = [[self xmlPath] componentsSeparatedByString:@"/"];
            rootarray = [rootarray subarrayWithRange:NSMakeRange(0, [rootarray count] -2)];
            
            /* TODO copy to the same file! for now just copy to our try file*/
            
            /* NSString *toCopyPath = [rootarray componentsJoinedByString:@"/"];
             NSLog(@"TOCOPY = %@", toCopyPath);
             */
            NSString *toCopyPath = @"/Users/crogoz/Desktop/Try/ladybug.jpg";
            [[NSFileManager defaultManager] createFileAtPath:toCopyPath contents:nil attributes:nil];
            
            NSBitmapImageRep *imgRep = (NSBitmapImageRep *)[[image representations] objectAtIndex: 0];
            NSData *data = (NSData *)[imgRep representationUsingType: NSPNGFileType properties: [[NSDictionary alloc] init]];
            [data writeToFile: toCopyPath atomically: NO];
           
            NSString *str = [self toString:imageDict name:ISIMAGE isLeaf:TRUE];
            
            [[dict objectForKey:HEADER]  setObject:theFileName forKey:ISIMAGE];
            /* insert this tag into resourcesDict 
             * only if this resource was not prev added */
            if ([resourcesDict rangeOfString:str].location == NSNotFound) {
                [resourcesDict appendString:str];
            }
            
        }
        
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

-(NSString*) getXmlForAgcObject:(NSDictionary*)typeAgcObject {
    NSString *agcObject = [typeAgcObject objectForKey:TYPE];
    NSMutableString *xmlGen = [NSMutableString stringWithFormat:@""];
    NSMutableString *finalString;
    NSDictionary *dict;
    NSMutableString *stringFooter = [NSMutableString stringWithFormat:XMLSCENESF];
    
    if (!agcObject) {
        // it was given the whole dictionary to process => goto @"content"; type = "view"
        
        int artboardsNo = (int)[[typeAgcObject objectForKey:ARTBOARDS] count];
       
        
        NSString *initialArtboard = [[NSUUID UUID] UUIDString];
        BOOL setInitial = false;
        
        while (sceneNo < artboardsNo) {
            finalString = [[NSMutableString alloc] init];
            
            dict = [[self processWholeXmlFromAgc:typeAgcObject] objectForKey: ARTBOARD];
            
            NSLog(@"Dict = %@", dict);
            [finalString appendString: SCENEHEADERA];
            [finalString appendString: [[NSUUID UUID] UUIDString]];
            
            [finalString appendString: SCENEHEADERB];
            if (!setInitial) {
                [finalString appendString: initialArtboard];
                setInitial = true;
            }
            else
                [finalString appendString: [[NSUUID UUID] UUIDString]];
            [finalString appendString: SCENEHEADERC];
            [finalString appendString: [[NSUUID UUID] UUIDString]];
            [finalString appendString: SCENEHEADERD];
            [finalString appendString: [[NSUUID UUID] UUIDString]];
            [finalString appendString: SCENEHEADERE];
            
            [finalString appendString: [self parseToString:finalString dict:dict name: ARTBOARD]];
            [finalString appendString: XMLVIEWF];
            [finalString appendString:XMLFOOTERA];
            [finalString appendString: [[NSUUID UUID] UUIDString]];
            [finalString appendString:XMLFOOTERB];
            [xmlGen appendString:finalString];
            ++sceneNo;
           
        }
        
        if ([resourcesDict length]) {
            // append resources if it exists
            NSString *resources = [NSString stringWithFormat:@"%@\n%@\n%@",XMLRESOURCES, resourcesDict, XMLRESOURCESF];
            [stringFooter appendString:resources];
        }
        
        [stringFooter appendFormat:@"\n%@", XMLDOCUMENTF];
        NSString *xmlHeader =  [self surroundWithHeader:XMLHEADERA footer:XMLHEADERB string:initialArtboard];
        NSString *xmlFile = [self surroundWithHeader:xmlHeader footer:stringFooter string:xmlGen];
        
        NSData *data = [xmlFile dataUsingEncoding:NSUTF8StringEncoding];
        
        NSError *err;
        NSXMLDocument *doc = [[NSXMLDocument alloc] initWithData:data options:NSXMLDocumentTidyXML error:&err];
        NSData* xmlData = [doc XMLDataWithOptions:NSXMLNodePrettyPrint];
        [xmlData writeToFile:@"new.xml" atomically:YES];
        
        return finalString;
        
    }
    
    return nil;
}

-(void) generateXmlForTag:(NSDictionary*)agcDict {
    NSString *xmlTemplate = [self getXmlForAgcObject:agcDict];
    
    if (!xmlTemplate) {
        NSLog(@"[ERROR] No translation can be achieved at the moment for %@", [agcDict objectForKey:TYPE]);
        return;
    }
    
}

- (id)initWithError:(NSError **)error
{
    return self;
}

@end
