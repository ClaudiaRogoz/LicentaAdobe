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
    NSLog(@"xmlPath = %@", xmlPath);
    NSBundle *thisBundle = [NSBundle bundleForClass:[self class]];
    NSString *def = [thisBundle pathForResource:@"Defs" ofType:@"json"];
    NSString *rule = [thisBundle pathForResource:@"Rules" ofType:@"json"];
    NSString *test = [thisBundle pathForResource:TESTMULTTEXT_PATH ofType:@"json"];
    
    XMLGenerator *gen = [[XMLGenerator alloc] initWithError:&error];
    NSData *defData = [NSData dataWithContentsOfFile:def];
    
    NSLog(@"Def = %@", def);
    NSData *ruleData = [NSData dataWithContentsOfFile:rule];
    
    NSLog(@"A =");
    NSMutableDictionary *defDictionary = [NSJSONSerialization JSONObjectWithData:defData options:NSJSONReadingMutableContainers error:&error];
    NSLog(@"B =");
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
    transformObjects[@"size"] = [[NSMutableDictionary alloc] init];
    transformObjects[@"size"][@"x"] = [NSNumber numberWithInt:1];
    transformObjects[@"size"][@"y"] = [NSNumber numberWithInt:1];
    
    transformObjects[@"color"] = [[NSMutableDictionary alloc] init];
    transformObjects[@"color"][@"red"] = [NSNumber numberWithInt:1];
    transformObjects[@"color"][@"green"] = [NSNumber numberWithInt:1];
    transformObjects[@"color"][@"blue"] = [NSNumber numberWithInt:1];
    
    sceneNo = 0;
    
    
}


-(NSString *) computeValue:(NSString *)initValue forDict:(NSDictionary *)agcDict {
    
    
    if ([initValue isEqualToString:RANDOM]) {
        //generate a random value; needed for id
        return [[NSUUID UUID] UUIDString];
        
    } else {
        //if it depends on an agc tag
        initValue = [initValue substringFromIndex:1];
        NSArray *array = [initValue componentsSeparatedByString:@"."];
        
        id value = agcDict;
        for (id key in array) {
            NSLog(@"key = %@", key);
            
            if ([key isEqualToString:COUNT]) {
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
    NSArray *order = [dict objectForKey:@"toString"];
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
        [tagStr appendFormat:@"</mutableString>"];
        NSLog(@"Tag = %@", tagStr);
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
        
        BOOL toTransform = [value isKindOfClass:[NSString class]] && [value hasPrefix:@"$"];
        if (toTransform) {
          
            [*initDict setObject:[paramDict objectForKey:key] forKey:key];
        }
    }
    
}

-(void) mergeDictionaries:(NSMutableDictionary **)objDict withDict:(NSMutableDictionary *)dictValue
              usingValues:(NSDictionary *)paramsValue {
    
    //NSLog(@"DictValue = %@ %@ %@", dictValue, *objDict, paramsValue);
    NSMutableDictionary *defaultDict = [*objDict objectForKey:DEFAULT];
    
    for (id key in [*objDict allKeys]) {
        id value = [*objDict objectForKey:key];
        //NSLog(@"key = %@ value = %@ Dict = %@", key, value, dictValue);
        if ([value isKindOfClass:[NSString class]] && [value hasPrefix:@"$"]) {
            value = [dictValue objectForKey:[value substringFromIndex:1]];
            
            if (value) {
                //NSLog(@"Changing %@ with %@", key, value);
                if ([[transformObjects objectForKey:@"size"] objectForKey:key]) {
                    /* TODO change the size -> scale */
                    float translatedValue;
                    NSLog(@"Key need to be resized = %@ %f %d", key, [value floatValue], startXArtboard);
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
                    
                    
                    NSLog(@"translation = %f", translatedValue);
                    [*objDict setObject:[NSNumber numberWithFloat:translatedValue] forKey:key];
                    continue;
                } else if ([[transformObjects objectForKey:@"color"] objectForKey:key]) {
                    /* change the color */
                    float color = [value floatValue] / 255;
                    [*objDict setObject:[NSString stringWithFormat:@"%f", color] forKey:key];
                    continue;
                }
                [*objDict setObject:value forKey:key];
                
            } else {
                /* use values specified from agc */
                value = [paramsValue objectForKey:key];
                NSLog(@"Setting key = %@ value = %@ params = %@", key, value, paramsValue);
                if (!value)
                    continue;
                
                if (![value hasPrefix:@"$"]) {
                    //NSLog(@"Here\n");
                    [*objDict setValue:value forKey:key]; /* no need for transformation */
                } else if ([dictValue objectForKey:[[self splitVariable:value] objectAtIndex:0]]) {
                    
                    id tvalue = [[self splitVariable:value] objectAtIndex:0];
                    //NSLog(@"Set for here");
                    
                    if ([[transformObjects objectForKey:@"size"] objectForKey:key]) {
                        /* TODO change size here */
                        //NSLog(@"vhange her ");
                        
                        float initValue = [[dictValue objectForKey:tvalue] floatValue];
                        float translatedValue = initValue;
                        float xScaleFactor = (float)WIDTHXMLARTBOARD/WIDTHXDARTBOARD;
                        float yScaleFactor = (float)HEIGHTXMLARTBOARD/HEIGHTXDARTBOARD;
                        NSLog(@"ScalerFactor = %f %f %f %f", xScaleFactor, yScaleFactor, WIDTHXMLARTBOARD, widthXDArtboard);
                        if ([key isEqualToString:XARTBOARD]) {
                            translatedValue = initValue - startXArtboard;//fabsf(startXArtboard - initValue);
                            translatedValue = translatedValue * xScaleFactor;
                        }
                        else if ([key isEqualToString:YARTBOARD]) {
                            translatedValue = initValue - startYArtboard;//fabsf(startYArtboard - initValue);
                            translatedValue = translatedValue * yScaleFactor;
                        }
                        NSLog(@"Key need to be resized = %@ %f %f offset: %d", key, initValue, translatedValue, startXArtboard);
                        [*objDict setValue:[NSNumber numberWithInt:translatedValue] forKey:key];
                    } else
                        [*objDict setValue:[dictValue objectForKey:tvalue] forKey:key];
                    
                    /* check if width/height needs to be computed (eg. text frame) */
                    if ([tvalue isEqualToString:@"size"] && ![[*objDict objectForKey:@"height"] isEqualToString:@"$rawText"]) { /* then we must compute the width/height of the text frame*/
                        /*FIX ME: assumed that the text font is the NSFont */
                        /* we have the height = text; width = fontSize; */
                        
                        NSLog(@"BUHUHU1 %d %d", textLines, textLen);
                        NSLog(@"Dict -= %@", *objDict);
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
        NSLog(@"Dict irt is!");
        for (id key in [type allKeys]) {
            NSLog(@"Check for %@", key);
            id value = [object mutableCopy];
            id subType = [type objectForKey:key];
            NSArray *gotoTag = [key componentsSeparatedByString:@"."];
            NSLog(@"Obj = %@", value);
            for (id elem in [gotoTag subarrayWithRange:NSMakeRange(0, [gotoTag count] -1)]) {
                NSLog(@"elem = %@", elem);
                value = [value objectForKey:elem];
                NSLog(@"goto %@", value);
            }
            
            if (![value isEqualToString:[gotoTag lastObject]])
            continue;
            
            NSLog(@"Match here %@", subType);
            for (id subKey in subType) {
                id subValue = [object mutableCopy];
                id subSubType = [subType objectForKey:subKey];
                gotoTag = [subKey componentsSeparatedByString:@"."];
                for (id elem in [gotoTag subarrayWithRange:NSMakeRange(0, [gotoTag count] -1)]) {
                    subValue = [subValue objectForKey:elem];
                }
                
                if (![subValue isEqualToString:[gotoTag lastObject]])
                continue;
                else {
                    NSLog(@"Settype = %@", type);
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
    
    //NSLog(@"Mutiple conditions = %@", cond);
    for (id condition in cond) {
        id values = agcParams;
       // NSLog(@"Obj = %@", objDict);
       // NSLog(@"Check for the following condition: %@", condition);
        NSArray *goToAgc = [self splitVariable:condition];
        //NSLog(@"Dependency = %@ %@", goToAgc, values);
        for (id key in goToAgc) {
            
            id nodeValue;
            ///NSLog(@"Check for key = %@ %@ %@", key, condition, values);
            if ([key hasPrefix:@"$"] && [key isEqualToString:SCENENO]) {
                nodeValue = [values objectAtIndex:sceneNo];
                
            } else if ([key hasPrefix:@"$"] && [key isEqualToString:ARTBOARDSCENE]) {
                NSString *artboard = [NSString stringWithFormat:@"artboard%d", sceneNo +1];
                nodeValue = [values objectForKey:artboard];

                /* obtain the startX and startY for the current scene */
                startXArtboard = [[nodeValue objectForKey:XARTBOARD] intValue];
                startYArtboard = [[nodeValue objectForKey:YARTBOARD] intValue];
                NSLog(@"XYWH = %@", nodeValue);
                widthXDArtboard = [[nodeValue objectForKey:WIDTH] intValue];
                heightXDArtboard = [[nodeValue objectForKey:HEIGHT] intValue];
                
                //NSLog(@"STARTXY = %d %d %d %d", startXArtboard, startYArtboard, heightXDArtboard, widthXDArtboard);
            } else if ([key hasPrefix:@"$"] && [key isEqualToString:LINES]){
                nodeValue = [values objectAtIndex:0];
            } else if ([key hasPrefix:@"$"] && [key isEqualToString:LINESDICT]){
                nodeValue = [values objectForKey:[NSNumber numberWithInt:0]];
            } else {
            
                nodeValue = [values objectForKey:key];
                
            }
            
            values = nodeValue;
            //NSLog(@"TempV = %@", values);
        }
        
        NSMutableDictionary *dictValue = values;
        BOOL isEmpty = ([dictValue count] == 0);
        if (isEmpty && !dictValue) {
            //use default values!!!
            //NSLog(@"MERGEDEF: %@ %@ %@", [objDict objectForKey:DEFAULT], objDict, dict);
            [self mergeDefaultValues:[objDict objectForKey:DEFAULT] withDict:&objDict usingDict:dict];
            return objDict;
            
        } else if (isEmpty) {
            //no subview found
            return nil;
        } else {
            NSLog(@"Dict for cond = %@", [dict objectForKey:condition]);
            id subRules = [dict objectForKey:condition];
            
            if ([subRules isKindOfClass:[NSMutableDictionary class]] && [subRules objectForKey:LEN]) {
                
                int counter = (int)[dictValue count];
                NSLog(@"ClaudSet to %d %@", counter, dictValue);
                //textLines = counter;
                //NSLog(@"objectDict = %@", objDict);
                textLines = MAX(counter, [[objDict objectForKey:LEN] intValue]);
                
                [objDict setObject:[NSNumber numberWithInt:textLines] forKey:LEN];
                
                id tmp = dictValue;
                id firstLine;
                if (textLines == counter && [condition isEqualToString:@"$text.paragraphs.$lineListNo.lines"])
                    firstLine = [[[tmp objectAtIndex:0] objectAtIndex:0]objectForKey:@"to"];
                else if (textLines == counter && [condition isEqualToString:@"$text.paragraphs"]) {
                    tmp = [[tmp objectAtIndex:0] objectForKey:@"lines"];
                    firstLine = [[[tmp objectAtIndex:0] objectAtIndex:0]objectForKey:@"to"];
                }
                
                textLen = [firstLine intValue];
            
                continue;
            }
            if ([subRules isKindOfClass:[NSMutableDictionary class]] && [subRules objectForKey:TYPE] &&
                [[subRules objectForKey:TYPE] isEqualToString:STYLE]) {
                
                id styleFont = [dictValue objectForKey:@"style"];
                //NSLog(@"Font Style %@", [dictValue objectForKey:@"style"]);
                
                id translatedStyle;
                
                if ([styleFont isEqualToString:REGULAR])
                    translatedStyle = @"system";
                else if ([styleFont isEqualToString:ITALIC])
                    translatedStyle = @"italicSystem";
                else if ([styleFont isEqualToString:BOLD])
                    translatedStyle = @"boldSystem";
                //NSLog(@"objDict = %@", objDict);
                [[dict objectForKey:condition] setObject:translatedStyle forKey:TYPE];
                //id fontStyle = [dictValue ]
                
                //continue;
            
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
                    NSLog(@"object = %@", object);
                    id type = [translationDict objectForKey:[object objectForKey:@"type"]];
                    NSLog(@"Ttype = %@", type);
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
                    
                    NSLog(@"Ttype = %@", type);
                    if ([type isEqualToString:GROUP]) {
                        NSLog(@"This is a group! %@", object);
                        NSMutableDictionary *viewDict = [newObjDict objectForKey:VIEW];
                        [self processTemplateDict:&viewDict agcDict:object finalDict:finalDict];
                        NSLog(@"parent = %@", viewDict);
                        
                        id sizeFrame = [[viewDict objectForKey:@"rules"] objectForKey:@"rect"];
                        
                        int x = [[sizeFrame objectForKey:@"x"] intValue];
                        int y = [[sizeFrame objectForKey:@"y"] intValue];
                        
                        
                        int prevWidth = widthXDArtboard;
                        int prevHeight = heightXDArtboard;
                        widthXDArtboard = WIDTHXMLARTBOARD;
                        heightXDArtboard = HEIGHTXMLARTBOARD;
                        int prevX = startXArtboard;
                        int prevY = startYArtboard;
                        startXArtboard = x - startXArtboard;
                        startYArtboard = y - startYArtboard;
                        
                        NSMutableArray *viewSubviews = [[NSMutableArray alloc] init];
                        
                        
                        for (id key in [[object objectForKey:GROUP] objectForKey:@"children"]) {
                            id type = [translationDict objectForKey:[key objectForKey:@"type"]];
                            NSLog(@"Ttype = %@", type);
                            
                            if (!type)
                                continue;
                            
                            type = [self getShapeType:type object:object];
                            NSMutableDictionary *typeObjDict = [NSKeyedUnarchiver unarchiveObjectWithData:[NSKeyedArchiver archivedDataWithRootObject: [newObjDict objectForKey:type]]];
                            NSLog(@"%d %d %d ", startXArtboard, startYArtboard, widthXDArtboard);
                            [self processTemplateDict:&typeObjDict agcDict:key finalDict:finalDict];
                            
                            id groupFrame = [[typeObjDict objectForKey:@"rules"] objectForKey:@"rect"];
                            
                            int x = [[groupFrame objectForKey:@"x"] intValue];
                            int y = [[groupFrame objectForKey:@"y"] intValue];
                            int w = [[groupFrame objectForKey:@"width"] intValue];
                            int h = [[groupFrame objectForKey:@"height"] intValue];
                            
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
                                
                            NSLog(@"group = %@", typeObjDict);
                            NSMutableDictionary *subViewDict = [[NSMutableDictionary alloc] init ];
                            [subViewDict setObject:typeObjDict forKey:type];
                            [viewSubviews addObject:subViewDict];
                            
                        }
                        
                        NSLog(@"MaxMin = %d %d %d %d", minx, miny, maxx, maxy);
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

                        NSLog(@"ObjDict = %@", viewSubviews);
                        
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
                        NSLog(@"ObjectView = %@", objDict);
                        //NSMutableDictionary *groupDict = [self processGroup:&viewDict agcDict:[object objectForKey:GROUP]];
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
    
    NSMutableDictionary *rulesInitDict = [*templateDict objectForKey:@"rules"];
    NSMutableDictionary *rulesTempDict = [rulesInitDict mutableCopy];
    
    for (id rule in rulesTempDict) {
        NSLog(@"rule = %@", rule);
        NSArray *keys = [self splitVariable:rule];
        
        
        if ([keys count] == 1) {
            
            //TODO goto "subviews" dictionary
            NSLog(@"TO Process %@", rule);
            NSMutableDictionary *rulesDict = [rulesTempDict objectForKey:rule];
            if ([rulesDict isKindOfClass:[NSArray class]])
                continue;
            
            NSLog(@"Conditions for : %@ are %@", rule, [rulesDict allKeys]);
            
            NSArray *cond;
            if ([rulesDict count] == 0)
                cond = nil;
            else if ([rulesDict objectForKey:ORDER])
                cond = [rulesDict objectForKey:ORDER];
            else
                cond = [rulesDict allKeys];
            
                
            NSLog(@"The condition %@ = %@ %@ %@ %@", rule, cond, rule, [rulesTempDict objectForKey:rule], agcDict);
            NSLog(@"xyw %d %d %d ", startXArtboard, startYArtboard, widthXDArtboard);
            NSMutableDictionary *mergeDict = [self computeObjects:rule condition:cond params:[rulesTempDict objectForKey:rule] agcDict:agcDict];
            NSLog(@"Merge dict = %@ For %@", mergeDict, rule);
            
            if (mergeDict != nil) {
                [rulesInitDict setObject:mergeDict forKey:rule];
                NSLog(@"After merge  =  %@ ", rulesInitDict);
            }
            
        } else {
            
            NSLog(@"TMPL = %@ %@", *templateDict, keys);
            id val = *templateDict;
            for (id key in [keys subarrayWithRange:NSMakeRange(0, [keys count] -1)]) {
                val = [val objectForKey:key];
            }
            NSString *value = [self computeValue:[rulesTempDict objectForKey:rule] forDict:agcDict];
            NSLog(@"Set value = %@ %@\n%@", value, [keys lastObject], val);
           
            
            if ([[value componentsSeparatedByString:@" "] count] == 1) {
                id hasValue = [val objectForKey:[keys lastObject]];
                if (hasValue && [hasValue intValue]){
                    int max = MAX([hasValue intValue], [value intValue]);
                    [val setObject:[NSNumber numberWithInt:max] forKey:[keys lastObject]];
                }
                else [val setObject:value forKey:[keys lastObject]];
            } else {
                NSString *stringValue = [NSString stringWithFormat:@"\"%@\"", value];
                 NSLog(@"A");
                [val setObject:stringValue forKey:[keys lastObject]];
                
            }
            NSLog(@"Val = %@", val);
            
        }
        
    }
    
    return finalDict;
}

-(NSDictionary*) processWholeXmlFromAgc:(NSDictionary *)agcDict {
    
    NSMutableDictionary *finalDict = [NSKeyedUnarchiver unarchiveObjectWithData:[NSKeyedArchiver archivedDataWithRootObject: [agcToXmlTemplate objectForKey:@"content"]]];
    NSLog(@"finalDict = %@ %@", finalDict, agcToXmlTemplate);
    
    
    NSMutableDictionary *viewDict = [finalDict objectForKey:@"view"];
    
    return [self processTemplateDict:&viewDict agcDict:agcDict finalDict:finalDict];
    
}

/* in caser of whole file translation => extend with header and footer */
-(NSString *) surroundWithHeader:(NSString *) header footer:(NSString *) footer string:(NSString *)str {
    
    
    return [NSString stringWithFormat:@"%@\n%@\n%@", header, str, footer];
    
}

-(NSMutableString *) parseToString:(NSMutableString *)str dict:(NSDictionary *)dict name:(NSString *) name{
    
    NSMutableString* tmp = [NSMutableString stringWithFormat:@""];
    NSLog(@"tmp = %@", dict);
    
    /* now we only have to translate the currentDict */
    for (id key in [dict objectForKey:TOSTRING]) {
        id attr = [dict objectForKey:key];
        NSLog(@"At key = %@ with %@", key, attr);
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
            NSLog(@"FileName = %@ %@", theFileName, dict);
            imageDict[NAME] = theFileName;
            // [attr objectForKey:ISIMAGE];
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
            NSLog(@"imageView = %@", imageDict);
            NSString *str = [self toString:imageDict name:ISIMAGE isLeaf:TRUE];
            
            [[dict objectForKey:HEADER]  setObject:theFileName forKey:ISIMAGE];
            /* insert this tag into resourcesDict */
            [resourcesDict appendString:str];
            
            NSLog(@"ResourcesW = %@", resourcesDict);
            
        }
        
        if ([key isEqualToString:RULES]) {
            
            [tmp appendString:[self parseToString:tmp dict:attr name:key]] ;
            
            
        } else if ([key isEqualToString:HEADER]) {
            /* create a new top tag with dict[allKeys] objeectAtIndex[0] */
            [ tmp appendString: [self toString:attr name:name isLeaf:FALSE]];
            
            
        } else if ([key isEqualToString:SUBVIEWS]){
            [tmp appendString:XMLSUBVIEWS];
            for (id subview in attr) {
                NSLog(@"Subviewz = %@", subview);
                NSString *name = [[subview allKeys] objectAtIndex:0];
                NSMutableDictionary *dict = [subview objectForKey:name];
                NSLog(@"name = %@ %@", name, dict);
                NSMutableString *str = [self parseToString:tmp dict:dict name:name];
                NSString* subFooter = [NSString stringWithFormat:@"\n</%@>", name];
                [str appendString:subFooter];
                [tmp appendString: str];
            }
            [tmp appendString:XMLSUBVIEWSF];
            NSLog(@"Key = %@ is Subview\n", key);
            
            
        } else if ([[agcToXmlTemplate objectForKey:SUBTAGS] objectForKey:key]){
            BOOL inBetween = [[[agcToXmlTemplate objectForKey:SUBTAGS] objectForKey:key]objectForKey:BETWEEN] == nil;
            
            /* just an ordinary leaf tag; create a one-line with the given attributes */
            NSLog(@"OneLiner = %@ %@", key, attr);
            NSString *ret = [self toString:attr name:key isLeaf:inBetween];
            [ tmp appendString: [NSString stringWithFormat:@"\n\t%@", ret]];
            
            
        }
    }
    
    return tmp;
    
    
}

-(NSString*) getXmlForAgcObject:(NSDictionary*)typeAgcObject {
    NSString *agcObject = [typeAgcObject objectForKey:@"type"];
    NSMutableString *xmlGen = [NSMutableString stringWithFormat:@""];
    NSMutableString *finalString;
    NSDictionary *dict;
    NSMutableString *stringFooter = [NSMutableString stringWithFormat:@"</scenes>"];
    
    if (!agcObject) {
        // it was given the whole dictionary to process => goto @"content"; type = "view"
        // TODO insert header + footer of the xml file
        
        NSLog(@"typeX = %@ %@", typeAgcObject, agcToXmlTemplate);
        int artboardsNo = (int)[[typeAgcObject objectForKey:@"artboards"] count];
        NSLog(@"No of artboards = %d", artboardsNo);
        
        NSString *initialArtboard = [[NSUUID UUID] UUIDString];
        BOOL setInitial = false;
        
        while (sceneNo < artboardsNo) {
            finalString = [[NSMutableString alloc] init];
            
            dict = [[self processWholeXmlFromAgc:typeAgcObject] objectForKey: @"view"];
            
            NSLog(@"D1ct = %@", dict);
            [finalString appendString: SCENEHEADERA];
            [finalString appendString: [[NSUUID UUID] UUIDString]];
            
            [finalString appendString: SCENEHEADERB];
            if (!setInitial)
                [finalString appendString: initialArtboard];
            else
                [finalString appendString: [[NSUUID UUID] UUIDString]];
            [finalString appendString: SCENEHEADERC];
            [finalString appendString: [[NSUUID UUID] UUIDString]];
            [finalString appendString: SCENEHEADERD];
            [finalString appendString: [[NSUUID UUID] UUIDString]];
            [finalString appendString: SCENEHEADERE];
            
            [finalString appendString: [self parseToString:finalString dict:dict name:@"view"]];
            [finalString appendString:@"</view>"];
            [finalString appendString:XMLFOOTERA];
            [finalString appendString: [[NSUUID UUID] UUIDString]];
            [finalString appendString:XMLFOOTERB];
            [xmlGen appendString:finalString];
            ++sceneNo;
            NSLog(@"Scene = %d", sceneNo);
        }
        
        /* TODO 15 apr */
        NSLog(@"XMLGen = %@", xmlGen);
        
      // NSMutableString *stringFooter = [NSMutableString stringWithFormat:@"%@\n%@",@"</view>", XMLFOOTER];
        if ([resourcesDict length]) {
            //TODO append resources if it exists
            NSString *resources = [NSString stringWithFormat:@"%@\n%@\n%@",XMLRESOURCES, resourcesDict, XMLRESOURCESF];
            [stringFooter appendString:resources];
        }
        NSLog(@"here = %@", stringFooter);
        [stringFooter appendFormat:@"\n%@", XMLDOCUMENTF];
        NSString *xmlHeader =  [self surroundWithHeader:XMLHEADERA footer:XMLHEADERB string:initialArtboard];
        NSString *xmlFile = [self surroundWithHeader:xmlHeader footer:stringFooter string:xmlGen];
        NSLog(@"XML = %@", xmlFile);
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
        NSLog(@"[ERROR] No translation can be achieved at the moment for %@", [agcDict objectForKey:@"type"]);
        return;
    }
    
    NSLog(@"XmlTemplate = %@", xmlTemplate);
    
}

- (id)initWithError:(NSError **)error
{
    return self;
}

@end
