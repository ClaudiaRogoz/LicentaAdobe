//
//  Dict2Agc.m
//  XDXCodeTranslator
//
//  Created by crogoz on 08/06/16.
//  Copyright © 2016 crogoz. All rights reserved.
//

#import <Foundation/Foundation.h>

#include "Dict2Agc.h"

@import AppKit;


@implementation Dict2Agc


+ (void)processDict:(NSMutableDictionary *)dictionary  error:(NSError **)error usingXdPath:(NSString *) xdPath {

    Dict2Agc *gen = [[Dict2Agc alloc] init];
    NSLog(@"Dictionary = %@", dictionary);
    [gen initWithSchemas];
    [gen setXdPath:xdPath];
    [gen getXDForXmlObject:dictionary];
  
}

-(void) initWithSchemas {
    
    NSError *error;
    
    NSBundle *thisBundle = [NSBundle bundleForClass:[self class]];
    NSString *def = [thisBundle pathForResource:DEF_DICT_PATH ofType:JSON];
    NSString *rule = [thisBundle pathForResource:RULES_DICT_PATH ofType:JSON];
    NSData *defData = [NSData dataWithContentsOfFile:def];
    
    NSData *ruleData = [NSData dataWithContentsOfFile:rule];
    
    NSMutableDictionary *defDictionary = [NSJSONSerialization JSONObjectWithData:defData options:NSJSONReadingMutableContainers error:&error];
    
    NSDictionary *ruleDictionary = [NSJSONSerialization JSONObjectWithData:ruleData options:NSJSONReadingMutableContainers error:&error];
    
    [self initializeWithDefs:defDictionary rules:ruleDictionary];
    
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
        
        NSString *mainBundle = [Helper getProjHomePath];
        
        NSString *outFile = [NSString stringWithFormat:@"%@/.%@", mainBundle, file];
        
        [[NSFileManager defaultManager] createFileAtPath:outFile contents:nil attributes:nil];
        [jsonString writeToFile:outFile atomically:YES encoding:NSUTF8StringEncoding error:nil];

    }
}

-(NSString *) getXDForXmlObject:(NSMutableDictionary *) xmlDict {

    NSMutableString *agcGen = [NSMutableString stringWithFormat:@""];
    NSDictionary *dict = [self processWholeXmlFromAgc:xmlDict];

    //NSString *finalArtboardName = [NSString stringWithFormat:ARTBOARDXML];
    //[self writeToFile:dict file:finalArtboardName computeSha:-1];
    return agcGen;
}


-(void) getDict:(id *)values fromConditions:(NSArray*)goToAgc {
    
    for (id key in goToAgc) {
        
        id nodeValue;
             nodeValue = [*values objectForKey:key];
            if ([key isEqualToString:VIEW]) {
                id frame = [nodeValue objectForKey:FRAME];
                widthArtboard = [[frame objectForKey:WIDTH] intValue];
                heightArtboard = [[frame objectForKey:HEIGHT] intValue];
            }
        
        *values = nodeValue;
        
    }
    
}

-(id) getShapeType:(id)type object:(id)object {
    
    
    if ([type isKindOfClass:[NSDictionary class]]) {
        
        id allKeys = [type allKeys];
        if ([type objectForKey:ORDER]) {
            allKeys = [type objectForKey:ORDER];
        }
        
        for (id key in [type allKeys]) {
        
            if ([[type objectForKey:key] isKindOfClass:[NSArray class]]) {
                continue;
            }
            
            if ([key hasPrefix:TOTRANSFORM]) {
                //only default value
                return [type objectForKey:key];
            
            }

            id value = [object mutableCopy];
            id subType = [type objectForKey:key];
            NSArray *gotoTag = [key componentsSeparatedByString:DOT];
            //NSLog(@"%@ %@ %@ %@", key, gotoTag, object, [value objectForKey:key]);
            if ([gotoTag count] == 1) {
                if ([value objectForKey:key] != nil) {
                    return subType;
                } else continue;
            }
            
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
- (BOOL) isOfTypeColor:(NSString *) key {
    return [[transformObjects objectForKey:COLOR] objectForKey:key] != nil;
}

-(BOOL) isOfTypeScale:(NSString *)key object:(NSString *) type {
    return [[transformObjects objectForKey:SCALE] objectForKey:key] && [[transformObjects objectForKey:SCALE] objectForKey:type];
}

-(BOOL) isOfTypeSize:(NSString *)key {
    return [[transformObjects objectForKey:SIZE] objectForKey:key] != nil;
}

- (float) changeSize:(float) initValue key:(NSString *)key preserveRatio:(BOOL) preserveRatio preserveOffset: (BOOL) offset scale:(BOOL) scale{
    
    float translatedValue = initValue;
    
    
    float xScaleFactor = ((float)WIDTH_XD_ARTBOARD/WIDTH_XML_ARTBOARD);
    float yScaleFactor = (float)HEIGHT_XD_ARTBOARD/HEIGHT_XML_ARTBOARD;
    float widthScaleFactor = xScaleFactor;
    float heightScalefactor = yScaleFactor;
    
    float ratio = MIN(xScaleFactor,yScaleFactor);
    
    if (preserveRatio ) {
        widthScaleFactor = ratio;
        heightScalefactor = ratio;
    }
    
    if ([key isEqualToString:TX]) {
        translatedValue = translatedValue * xScaleFactor;
        translatedValue = translatedValue + startXArtboard;
        
    } else if ([key isEqualToString:TY]) {
      
        translatedValue = translatedValue * yScaleFactor;
        translatedValue = translatedValue + startYArtboard;

        
        
    } else if ([key isEqualToString:WIDTH]) {
        translatedValue = initValue * widthScaleFactor;
        
    }
    else if ([key isEqualToString:HEIGHT]) {
        translatedValue = initValue * heightScalefactor;
    }
    
    return translatedValue;
}

- (void) merge:(NSMutableDictionary *) dictValue withDict:(NSMutableDictionary **) objDict
   withDefDict:(NSMutableDictionary *)defaultDict forValue:(NSString *) value key:(NSString *) key type:(NSString *) type {
    
    if (![value hasPrefix:TOTRANSFORM]) {
        [*objDict setValue:value forKey:key]; /* no need for transformation */
    } else if ([dictValue objectForKey:[[Helper splitVariable:value] objectAtIndex:0]]) {
        
        id tvalue = [[Helper splitVariable:value] objectAtIndex:0];
        
        if ([self isOfTypeSize:key]) {
            /* changing size here */
            
            float initValue = [[dictValue objectForKey:tvalue] floatValue];
            float translatedValue = [self changeSize:initValue key:key preserveRatio:false preserveOffset:false scale:true];
            
            [*objDict setValue:[NSNumber numberWithInt:translatedValue] forKey:key];
        } else {
            [*objDict setValue:[dictValue objectForKey:tvalue] forKey:key];
            
        }
        
        /*if we have a special operation to perform eg. getSize from path*/
    } else if ([defaultDict objectForKey:key]){/* use default values */
        
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
                NSLog(@"keyH = %@ %hhd", key, [self isOfTypeSize:key]);
                if ([self isOfTypeColor:key]) {
                    /* change the color */
                    float color;
                    
                    color = [value floatValue] * 255;
                    [*objDict setObject:[NSNumber numberWithFloat: color] forKey:key];
                    continue;
                }
                
                if ([self isOfTypeScale:key object:type]) {
                    
                    float initValue = [value floatValue];
                    float translatedValue = [self changeSize:initValue key:key preserveRatio:false preserveOffset:false scale:true];
                    [*objDict setObject:[NSNumber numberWithFloat:translatedValue] forKey:key];
                    continue;
                }
                
               if ([self isOfTypeSize:key]) {
                   
                    float initValue = [value floatValue];
                   
                    float translatedValue = [self changeSize:initValue key:key preserveRatio:false preserveOffset:false scale:true];
                    [*objDict setObject:[NSNumber numberWithFloat:translatedValue] forKey:key];
                    continue;
                    
                }
                if ([value intValue]) {
                    int intValue = [value intValue];
                    [*objDict setObject:[NSNumber numberWithInt:intValue] forKey:key];
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


-(NSMutableDictionary *) computeObjects:(NSString *)rule condition:(NSArray*)cond params:(NSDictionary *)dict
                                agcDict:agcParams type:(NSString *)type {
    
    
    id objDict;
    
    if ([rule isEqualToString:CHILDREN])
        objDict = [NSKeyedUnarchiver unarchiveObjectWithData:[NSKeyedArchiver archivedDataWithRootObject:[agcToXmlTemplate objectForKey:CHILDREN]]];
    else {
        NSArray *arr = [Helper splitVariableForDot:rule];
        id value = [agcToXmlTemplate objectForKey:SUBTAGS];
        for (id component in arr) {
            value = [value objectForKey:component];
        }
        objDict = [NSKeyedUnarchiver unarchiveObjectWithData:[NSKeyedArchiver archivedDataWithRootObject:value]];
    }
    
    // now changing based on params
    if (!cond) {
        //just generate the tag; no other transformations are needed
        return objDict;
    }
    
    //get values from agc in order to transfer them into xml
    for (id condition in cond) {
        id values = agcParams;
        
        NSArray *goToAgc = [Helper splitVariable:condition];
        
        [self getDict:&values fromConditions:goToAgc];
        
        NSMutableDictionary *dictValue = values;
        
        BOOL isEmpty = ([dictValue count] == 0);
        if (isEmpty && !dictValue) {
            //use default values!!!
            //TODO
           // [self mergeDefaultValues:[objDict objectForKey:DEFAULT] withDict:&objDict usingDict:dict];
            return objDict;
            
        } else if (isEmpty) {
            //no subview found
            return nil;
            
        } else {
            
            if (![dictValue isKindOfClass:[NSArray class]]) {
                
                [self mergeDictionaries:&objDict withDict:dictValue usingValues:[dict objectForKey:condition] type:type];
                
            }
            else {
                
                
                NSMutableDictionary *finalDict = [NSKeyedUnarchiver unarchiveObjectWithData:[NSKeyedArchiver archivedDataWithRootObject: [agcToXmlTemplate objectForKey:CHILDREN]]];
                NSMutableDictionary *newObjDict = [NSKeyedUnarchiver unarchiveObjectWithData:[NSKeyedArchiver archivedDataWithRootObject: [objDict mutableCopy]]];

                objDict = [[NSMutableArray alloc] init];
                
                
                for (id object in dictValue) {
                    /* obtain the type of each object
                     * get the corresponding template*/
                    if (![object isKindOfClass:[NSDictionary class]])
                        continue;
                    id name = [[object allKeys] objectAtIndex:0];
                    id type = [translationDict objectForKey:name];
                    
                    if (!type)
                        continue;
                    
                    
                    
                    type = [self getShapeType:type object:[object objectForKey:name]];
                    if (![type isKindOfClass:[NSString class]])
                        continue;
                    
                    NSMutableDictionary *typeObjDict = [NSKeyedUnarchiver unarchiveObjectWithData:[NSKeyedArchiver archivedDataWithRootObject: [newObjDict objectForKey:type]]];
                    
                    [self processTemplateDict:&typeObjDict agcDict:[object objectForKey:name] finalDict:finalDict ofType:type];
                    [[typeObjDict objectForKey:RULES ]removeObjectForKey:ORDER];
                    typeObjDict = [typeObjDict objectForKey:RULES];
                    NSMutableDictionary *subViewDict = [[NSMutableDictionary alloc] init ];
                    [subViewDict setObject:typeObjDict forKey:changeType];
                    [objDict addObject:typeObjDict];
                    
                }
                
           }
        }
    }
    
    return objDict;
}

- (id) replaceValuesInDict:(id) template withValues:(NSMutableDictionary *) values {

    NSMutableDictionary *result = [[NSMutableDictionary alloc] init];
    if ([template isKindOfClass:[NSArray class]]) {
        template = [template objectAtIndex:0];
    }
    
    for (id key in template) {
        id translatedKey = key;
        if ([translationDict objectForKey:key])
            translatedKey = [translationDict objectForKey:key];
        if ([values objectForKey:translatedKey])
                [result setObject:[values objectForKey:translatedKey] forKey:key];
        
        else [result setObject:[template objectForKey:key] forKey:key];
    }
    
    return result;
}

- (id) getLineAttributes:(NSMutableDictionary **) line {

    return [[[*line objectForKey:LINE_VALUE] objectAtIndex:0] objectAtIndex:0];
}

- (id) createParagraphs:(NSString *) text lineNo:(int) nr fontSize:(int) fontSize{
    
    NSMutableArray *paragraphs = [[NSMutableArray alloc] init];
    int len = (int)[text length];
    int charctersLine = len / nr;
    int initialY = fontSize - 1;
    for (int i = 0 ; i < nr; i++) {
        NSMutableDictionary *line = [Helper deepCopy:[[agcToXmlTemplate objectForKey:SUBTAGS]objectForKey:LINE_VALUE]];
        id value = [self getLineAttributes:&line];

        [value setObject:[NSNumber numberWithInt:initialY] forKey:YARTBOARD];
        [value setObject:[NSNumber numberWithInt:charctersLine] forKey:TO];
        initialY += fontSize + 2;
        [paragraphs addObject:line];
    }
    

    return paragraphs;
    
}

- (id) processFormula:(NSString *)key  initDict:(NSDictionary *) initDict translatedDict:(NSMutableDictionary *) translatedDict {
    
    if ([key hasPrefix:TOTRANSFORM]) {
        NSArray *words = [key componentsSeparatedByString:SPACE];
        if ([words count] == 1) {
            //eg $text
            id value = [Helper splitVariable:key];
            return [initDict objectForKey:[value objectAtIndex:0]];
            
        } else {
            //TODO a formula should be applied (eg COPY)
            if ([key hasPrefix:COPY]) {
                id properties = [[key substringFromIndex:[COPY length] + 1] componentsSeparatedByString:SPACE];
                id propertyName = [properties objectAtIndex:0];
                id translationName = [properties objectAtIndex:1];
                
                NSArray *propArr = [Helper getArrayProperties:propertyName];
                NSArray *transArr = [Helper getArrayProperties:translationName];
                id value = [Helper getValueForProperties:propArr inDict:translatedDict];
                id translated = [Helper getValueForProperties:transArr inDict:agcToXmlTemplate];
                
                return [NSArray arrayWithObjects:[self replaceValuesInDict:translated withValues:value], nil];
                
            } else if ([key hasPrefix:PARAGRAPH]) {
                id values = [[key substringFromIndex:[PARAGRAPH length] + 1] componentsSeparatedByString:SPACE];
                id numberOfLines = [values objectAtIndex:0];
                id text = [initDict objectForKey:[values objectAtIndex:1]];
                NSArray *propArr = [Helper getArrayProperties:[values objectAtIndex:2]];
                int fontSize = [[Helper getValueForProperties:propArr inDict:translatedDict] intValue];
                int nr;
                
                if ([numberOfLines intValue]) {
                    nr = [numberOfLines intValue];
                } else {
                    //TODO $PARAGRAPH numberOfLines text
                }
                
                return [self createParagraphs:text lineNo:nr fontSize: fontSize];

            }
        }
    }
    
    return nil;
}

- (id) getDict:(NSMutableDictionary *)dict fromArrayProperties:(NSArray *)arr usingRule:(NSString *)rule initialDict:(NSMutableDictionary *)rulesDict{
    id subTag;
    if ([rulesDict objectForKey:arr[0]]) {
        //only replace the dictionary corresponding to rule
        subTag = [rulesDict objectForKey:arr[0]];
    } else {
        subTag = [Helper deepCopy:[[agcToXmlTemplate objectForKey:SUBTAGS] objectForKey:arr[0]]];
    }
    
    id value = subTag;
    for (id key in [arr subarrayWithRange:NSMakeRange(1, [arr count] - 2)]) {
        value = [value objectForKey:key];
        
    }
    [value setObject:dict forKey:[arr lastObject]];
    
    
    return subTag;
    
}

-(NSDictionary*) processTemplateDict:(NSMutableDictionary **) templateDict agcDict:(NSDictionary *)agcDict
                           finalDict:(NSMutableDictionary *)finalDict ofType:(NSString *) type {
    NSMutableDictionary *rulesInitDict = [*templateDict objectForKey:RULES];
    NSMutableDictionary *rulesTempDict = [rulesInitDict mutableCopy];
    NSArray *keys, *cond;
    NSMutableDictionary *mergeDict;
    id rulesByOrder, rulesDict;

    /* if an order is specified => follow it
     * otherwise use the default enumerator */
    if ([rulesTempDict objectForKey:ORDER])
        rulesByOrder = [rulesTempDict objectForKey:ORDER];
    else rulesByOrder = rulesTempDict;
    
    for (id rule in rulesByOrder) {
        
        keys = [Helper splitVariable:rule];
     
        
        //goto "subviews" dictionary
        rulesDict = [rulesTempDict objectForKey:rule];
        
        if ([rulesDict isKindOfClass:[NSString class]]) {

            id value = [self processFormula:rulesDict initDict:agcDict translatedDict:*templateDict];
            if (value) {
                NSArray *arr = [Helper getArrayProperties:rule];
                if ([arr count] == 1)
                    [rulesInitDict setObject:value forKey:rule];
                else {
                    [rulesInitDict removeObjectForKey:rule];
                    id result = [self getDict:value fromArrayProperties:arr usingRule:rule initialDict:rulesInitDict];
                    [rulesInitDict setObject:result forKey:arr[0]];
                }
            }
            continue;
        }
        
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
            if ([mergeDict isKindOfClass:[NSDictionary class]])
                [mergeDict removeObjectForKey:DEFAULT];
            NSArray *arr = [Helper getArrayProperties:rule];
            if ([arr count] == 1)
                [rulesInitDict setObject:mergeDict forKey:rule];
            else {
                [rulesInitDict removeObjectForKey:rule];
                id result = [self getDict:mergeDict fromArrayProperties:arr usingRule:rule initialDict:rulesInitDict];

                [rulesInitDict setObject:result forKey:arr[0]];
            }
                
        }
            
    }
    changeType = type;
    
    return finalDict;
}

- (id) getStartingXmlDict:(NSDictionary **)xmlDict properties:(NSArray *)arr {
    
    id values = *xmlDict;
    for (id component in arr) {
        values = [values objectForKey:component];
    }
    NSLog(@"values = %@", values);
    return values;
}

- (id) convertSceneToJsonFormat:(NSMutableDictionary *) scene {

    NSMutableDictionary *result = [[scene objectForKey:VIEW] objectForKey:RULES];
    id value = [result objectForKey:STYLE_VALUE];
    [value removeObjectForKey:FONT_VALUE];
    id children = [result objectForKey:CHILDREN];
    NSMutableDictionary *subViews = [NSMutableDictionary dictionary];
    [subViews setObject:children forKey:CHILDREN];
    [subViews setObject:[NSString stringWithFormat:@"%@%d", ART_SCENE, ++sceneNo] forKey:REF];
    [result setObject:subViews forKey:ART_SCENE];
    
    [result removeObjectForKey:CHILDREN];
    return result;

}

- (void) processXmlScenes:(NSMutableDictionary **) artworkFiles  forDict:(NSMutableDictionary *) dict {
    
    NSMutableArray *children = [[NSMutableArray alloc] init];
    NSMutableDictionary *finalDict = [Helper deepCopy: [agcToXmlTemplate objectForKey:CONTENT]];
    NSMutableDictionary *viewDict = [finalDict objectForKey:ARTBOARD];
    startXArtboard = startXArtboard  + sceneNo * OFFSETBOARD;
    id scene = [self processTemplateDict:&viewDict agcDict:dict finalDict:finalDict ofType:VIEW];
    scene = [self convertSceneToJsonFormat:scene];
    [children addObject:scene];
    [*artworkFiles setObject:children forKey:CHILDREN];
    NSLog(@"MultScenes = %@", *artworkFiles);
    [XDCreator createArtworkContent:*artworkFiles artboardNo:sceneNo xdPath:[self xdPath]];

}


- (void) processXmlResources:(int*) offset artboardsDict:(NSMutableDictionary **) artboards{
    NSMutableDictionary *resources = [Helper deepCopy: [agcToXmlTemplate objectForKey:FIRST_ARTBOARD]];
    [resources setObject:[NSNumber numberWithInt:*offset]  forKey:XARTBOARD];
    *offset += OFFSETBOARD;
    NSString *template = [[resources objectForKey:NAME] stringByAppendingFormat:@"%d", sceneNo + 1];
    [resources setObject:template forKey:NAME];
    NSString *name = [NSString stringWithFormat:@"%@%d", ART_SCENE, sceneNo + 1];
    [*artboards setObject:resources forKey:name];
}

- (NSDictionary *) processWholeXmlFromAgc:(NSMutableDictionary *) xmlDict {

    NSMutableDictionary *finalDict = [NSKeyedUnarchiver unarchiveObjectWithData:[NSKeyedArchiver archivedDataWithRootObject: [agcToXmlTemplate objectForKey:CONTENT]]];
    NSArray *arr = [Helper splitVariable:[finalDict objectForKey:DEPENDENCY]];
    xmlDict = [self getStartingXmlDict:&xmlDict properties:arr];
    NSMutableDictionary *artworkFiles = [Helper deepCopy:[agcToXmlTemplate objectForKey:ARTWORK]];
    NSMutableDictionary *resources = [NSMutableDictionary dictionary];
    int offsetX = 0;
    [XDCreator createInteractionContent:nil xdPath:[self xdPath] homeArtboard:nil];
    [XDCreator createMimetype:[self xdPath]];
    
    
    if ([xmlDict isKindOfClass:[NSDictionary class]]) {
        
        [self processXmlResources: &offsetX artboardsDict:&resources];
        [XDCreator createResourcesContent:resources xdPath:[self xdPath]];
        [self processXmlScenes:&artworkFiles forDict:xmlDict];
        
    } else {
        for (id dict in xmlDict) {
            [self processXmlResources: &offsetX artboardsDict:&resources];
            [XDCreator createResourcesContent:resources xdPath:[self xdPath]];
            [self processXmlScenes:&artworkFiles forDict:dict];
        }
    
    }
    
    NSMutableDictionary *artboards = [NSMutableDictionary dictionary];
    [artboards setValue:resources forKey:ARTBOARDS];
    [XDCreator createManifest:artboards xdPath:[self xdPath]];
    [Helper createXdFile:[self xdPath]];
    return nil;
}

-(void)initializeWithDefs:(NSDictionary*)defDict rules:(NSDictionary*)ruleDict {
    agcToXmlTemplate = [defDict mutableCopy];
    translationDict = [ruleDict mutableCopy];
   
    transformObjects = [[NSMutableDictionary alloc] init];
    transformObjects[SIZE] = [[NSMutableDictionary alloc] init];
    transformObjects[SIZE][TX] = [NSNumber numberWithInt:1];
    transformObjects[SIZE][TY] = [NSNumber numberWithInt:1];
    
    transformObjects[SCALE] = [[NSMutableDictionary alloc] init];
    transformObjects[SCALE][WIDTH] = [NSNumber numberWithInt:1];
    transformObjects[SCALE][HEIGHT] = [NSNumber numberWithInt:1];
    transformObjects[SCALE][FRAMED] = [NSNumber numberWithInt:1];
    transformObjects[SCALE][IMAGEVIEW] = [NSNumber numberWithInt:1];
    
    transformObjects[COLOR] = [[NSMutableDictionary alloc] init];
    transformObjects[COLOR][XML_RED] = [NSNumber numberWithInt:1];
    transformObjects[COLOR][XML_GREEN] = [NSNumber numberWithInt:1];
    transformObjects[COLOR][XML_BLUE] = [NSNumber numberWithInt:1];
    
    sceneNo = 0;
    
}


@end
