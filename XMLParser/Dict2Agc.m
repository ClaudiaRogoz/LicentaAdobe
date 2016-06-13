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


+ (void)processDict:(NSMutableDictionary *)dictionary  error:(NSError **)error usingXdPath:(NSString *) xdPath xmlDirectory:(NSString *) xmlPath{

    Dict2Agc *gen = [[Dict2Agc alloc] init];
    [gen initWithSchemas];
    [gen setXdPath:xdPath];
    [gen setXmlPath:xmlPath];
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
    [self processWholeXmlFromAgc:xmlDict];
    return agcGen;
}


-(void) getDict:(id *)values fromConditions:(NSArray*)goToAgc {
    
    for (id key in goToAgc) {
        id nodeValue;
        if ([*values isKindOfClass:[NSDictionary class]]) {
            nodeValue = [*values objectForKey:key];
            if ([key isEqualToString:VIEW]) {
                id frame = [nodeValue objectForKey:FRAME];
                widthArtboard = [[frame objectForKey:WIDTH] intValue];
                heightArtboard = [[frame objectForKey:HEIGHT] intValue];
            }
        } else if ([*values isKindOfClass:[NSArray class]]){
            //eg. color.$key=backgroundColor
            NSString *typeKey = [key substringFromIndex:[KEY_VALUE length]];
            id type;
            for (type in *values) {
                if ([[type objectForKey:KEY] isEqualToString:typeKey]) {
                    nodeValue = type;
                    break;
                }
            }
        }
        if (nodeValue)
            *values = nodeValue;
    }
}

-(id) getShapeType:(id)type object:(id)object {
    if ([type isKindOfClass:[NSDictionary class]]) {
        id allKeys = [type allKeys];
        if ([type objectForKey:ORDER]) {
            allKeys = [type objectForKey:ORDER];
        }
        for (id key in allKeys) {
            if ([[type objectForKey:key] isKindOfClass:[NSArray class]]) {
                continue;
            }
            if ([key hasPrefix:TOTRANSFORM]) { /* only default value */
                return [type objectForKey:key];
            }
            id value = [object mutableCopy];
            id subType = [type objectForKey:key];
            NSArray *gotoTag = [key componentsSeparatedByString:DOT];
            if ([gotoTag count] == 1) {
                if ([value objectForKey:key] != nil) {
                    return subType;
                } else
                    continue;
            }
            for (id elem in [gotoTag subarrayWithRange:NSMakeRange(0, [gotoTag count] -1)]) {
                value = [value objectForKey:elem];
            }
            NSLog(@"TypeV = %@ %@", value, subType);
            if ([value isKindOfClass:[NSString class]] && ![value isEqualToString:[gotoTag lastObject]] && !([[gotoTag lastObject] isEqualToString:ISNIL] && [value  isEqualToString: @""]) )
                continue;
            if ([subType isKindOfClass:[NSString class]]) {
                NSLog(@"FInd = %@ %@", [gotoTag lastObject], [value objectForKey:[gotoTag lastObject]]);
                if ([value isKindOfClass:[NSString class]])
                    return subType;
                else if ([value isKindOfClass:[NSDictionary class]] && [value objectForKey:[gotoTag lastObject]])
                    return subType;
                else
                    continue;
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
    float ratio = MAX(xScaleFactor,yScaleFactor);
    if (preserveRatio ) {
        NSLog(@"PRESERVERATIO %f", translatedValue);
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
        
    } else if ([key isEqualToString:HEIGHT]) {
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
            float initValue = [[dictValue objectForKey:tvalue] floatValue];
            float translatedValue = [self changeSize:initValue
                                                 key:key
                                       preserveRatio:false
                                      preserveOffset:false
                                               scale:true];
            [*objDict setValue:[NSNumber numberWithInt:translatedValue] forKey:key];
            
        } else if ([key isEqualToString:HREF]) {
            NSString *name = [dictValue objectForKey:tvalue];
            NSString *directory = [[[self xmlPath] stringByDeletingLastPathComponent] stringByDeletingLastPathComponent];
            NSString *imageName = [Helper findFile:name inPath:directory];
            [*objDict setValue:imageName forKey:key];
            
        } else {
            [*objDict setValue:[dictValue objectForKey:tvalue] forKey:key];
        }
    } else if ([defaultDict objectForKey:key]){/* use default values */
        [*objDict setObject:[Helper deepCopy:[defaultDict objectForKey:key]] forKey:key];
    }
}

- (void) updateSizeColor:(id) value key:(NSString *)key type:(NSString*) type forDict:(NSMutableDictionary **) objDict {
    
    if ([self isOfTypeColor:key]) {
        float color;
        color = [value floatValue] * 255;
        [*objDict setObject:[NSNumber numberWithFloat: color] forKey:key];
        return;
    }
    if ([self isOfTypeScale:key object:type]) {
        BOOL preserveRatio = false;
        if ([type isEqualToString:ISIMAGE]) {
            preserveRatio = true;
        }
        float initValue = [value floatValue];
        float translatedValue = [self changeSize:initValue key:key preserveRatio:false preserveOffset:false scale:preserveRatio];
        [*objDict setObject:[NSNumber numberWithFloat:translatedValue] forKey:key];
        return;
    }
    if ([self isOfTypeSize:key]) {
        float initValue = [value floatValue];
        float translatedValue = [self changeSize:initValue key:key preserveRatio:false preserveOffset:false scale:true];
        [*objDict setObject:[NSNumber numberWithFloat:translatedValue] forKey:key];
        return;
    }
    if ([value intValue]) {
        int intValue = [value intValue];
        [*objDict setObject:[NSNumber numberWithInt:intValue] forKey:key];
        return;
    }
    if ([value floatValue]) {
        int intValue = [value floatValue];
        [*objDict setObject:[NSNumber numberWithFloat:intValue] forKey:key];
        return;
    }
    [*objDict setObject:value forKey:key];

}

-(void) mergeDictionaries:(NSMutableDictionary **)objDict withDict:(NSMutableDictionary *)dictValue
              usingValues:(NSDictionary *)paramsValue type:(NSString *)type {
    
    NSMutableDictionary *defaultDict = [Helper deepCopy:[*objDict objectForKey:DEFAULT]];
    id allKeys = [*objDict allKeys];
    if ([*objDict objectForKey:ORDER])
        allKeys = [*objDict objectForKey:ORDER];
    for (id key in allKeys) {
        id value = [*objDict objectForKey:key];
        if ([value isKindOfClass:[NSString class]] && [value hasPrefix:TOTRANSFORM]) {
            value = [dictValue objectForKey:[value substringFromIndex:1]];
            if (value) {
                [self updateSizeColor:value key:key type:type forDict: objDict];
            } else {
                /* use values specified from agc */
                value = [paramsValue objectForKey:key];
                if (!value)
                    continue;
                [self merge:dictValue withDict:objDict withDefDict:defaultDict forValue:value key:key type:type];
            }
        } else if ([value isKindOfClass:[NSDictionary class]] && ![key isEqualToString:DEFAULT]) {
            id value = [*objDict objectForKey:key];
            [self mergeDictionaries:&value withDict:dictValue usingValues:[Helper deepCopy:[dictValue objectForKey:DEFAULT]] type:key];
        }
    }
}


- (void ) removeProperties:(NSArray *)properties fromDict:(NSMutableDictionary **)typeObjDict {
    
    for (id property in properties) {
        id value = [*typeObjDict objectForKey:RULES];
        NSArray *arr = [Helper getArrayProperties:property];
        for (id key in [arr subarrayWithRange:NSMakeRange(0, [arr count] - 1)]) {
            value = [value objectForKey:key];
        }
        [value removeObjectForKey:[arr lastObject]];
    }
    [*typeObjDict removeObjectForKey:TOREMOVE];
}

-(NSMutableDictionary *) computeObjects:(NSString *)rule condition:(NSArray*)cond params:(NSDictionary *)dict
                                agcDict:agcParams type:(NSString *)type {
    
    id objDict;
    if ([rule isEqualToString:CHILDREN])
        objDict = [NSKeyedUnarchiver unarchiveObjectWithData:[NSKeyedArchiver archivedDataWithRootObject:[agcToXmlTemplate objectForKey:CHILDREN]]];
    else {
        NSArray *arr = [Helper splitVariableForDot:rule];
        id value = [agcToXmlTemplate objectForKey:SUBTAGS];
        for (id component in arr)
            value = [value objectForKey:component];
        objDict = [NSKeyedUnarchiver unarchiveObjectWithData:[NSKeyedArchiver archivedDataWithRootObject:value]];
    }
    if (!cond)
        return objDict;
    /* get values from agc in order to transfer them into xml */
    for (id condition in cond) {
        id values = agcParams;
        NSArray *goToAgc = [Helper splitVariable:condition];
        [self getDict:&values fromConditions:goToAgc];
        NSMutableDictionary *dictValue = values;
        BOOL isEmpty = ([dictValue count] == 0);
        if (isEmpty && !dictValue) {
            return objDict;
        } else if (isEmpty) {
            /* no subview found */
            return nil;
        } else {
            if (![dictValue isKindOfClass:[NSArray class]])
                [self mergeDictionaries:&objDict withDict:dictValue usingValues:[dict objectForKey:condition] type:type];
            else {
                NSMutableDictionary *finalDict = [Helper deepCopy:[agcToXmlTemplate objectForKey:CHILDREN]];
                NSMutableDictionary *newObjDict = [Helper deepCopy:[objDict mutableCopy]];
                objDict = [[NSMutableArray alloc] init];
                for (id object in dictValue) {
                    /* obtain the type of each object; get the corresponding template*/
                    if (![object isKindOfClass:[NSDictionary class]])
                        continue;
                    id name = [[object allKeys] objectAtIndex:0];
                    id type = [translationDict objectForKey:name];
                    if (!type)
                        continue;
                    NSLog(@"Got type = %@", type);
                    type = [self getShapeType:type object:[object objectForKey:name]];
                    if (![type isKindOfClass:[NSString class]])
                        continue;
                    NSLog(@"type is = %@", type);
                    NSMutableDictionary *typeObjDict = [NSKeyedUnarchiver unarchiveObjectWithData:[NSKeyedArchiver archivedDataWithRootObject: [newObjDict objectForKey:type]]];
                    [self processTemplateDict:&typeObjDict agcDict:[object objectForKey:name] finalDict:finalDict ofType:type];
                    [[typeObjDict objectForKey:RULES ]removeObjectForKey:ORDER];
                    [self removeProperties:[typeObjDict objectForKey:TOREMOVE] fromDict:&typeObjDict];
                    typeObjDict = [typeObjDict objectForKey:RULES];
                    NSMutableDictionary *subViewDict = [[NSMutableDictionary alloc] init ];
                    [subViewDict setObject:typeObjDict forKey:changeType];
                    [objDict addObject:typeObjDict];
                    NSLog(@"typeObjdict = %@", typeObjDict);
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
            if ([key isEqualToString:RANDOM])
                return [[NSUUID UUID] UUIDString];
            id value = [Helper splitVariable:key];
            id tempDict = initDict;
            for (id result in value) {
                tempDict = [tempDict objectForKey:result];
            }
            return tempDict;
        } else {
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
    return key;
}

- (id) getDict:(NSMutableDictionary *)dict fromArrayProperties:(NSArray *)arr usingRule:(NSString *)rule initialDict:(NSMutableDictionary *)rulesDict{
    
    id subTag;
    if ([rulesDict objectForKey:arr[0]])         /* only replace the dictionary corresponding to rule */
        subTag = [rulesDict objectForKey:arr[0]];
    else
        subTag = [Helper deepCopy:[[agcToXmlTemplate objectForKey:SUBTAGS] objectForKey:arr[0]]];
    id value = subTag;
    for (id key in [arr subarrayWithRange:NSMakeRange(1, [arr count] - 2)])
        value = [value objectForKey:key];
    [value setObject:dict forKey:[arr lastObject]];
    
    return subTag;
}

- (NSNumber *) getNumber:(id) value {
    if ([value intValue])
        return [NSNumber numberWithInt:[value intValue]];
    
    if ([value floatValue])
        return [NSNumber numberWithFloat:[value floatValue]];
    
    return nil;
}
-(NSDictionary*) processTemplateDict:(NSMutableDictionary **) templateDict agcDict:(NSDictionary *)agcDict
                           finalDict:(NSMutableDictionary *)finalDict ofType:(NSString *) type {
    NSMutableDictionary *rulesInitDict = [*templateDict objectForKey:RULES];
    NSMutableDictionary *rulesTempDict = [rulesInitDict mutableCopy];
    NSArray *cond;
    NSMutableDictionary *mergeDict;
    id rulesByOrder, rulesDict;

    /* if an order is specified => follow it
     * otherwise use the default enumerator */
    if ([rulesTempDict objectForKey:ORDER])
        rulesByOrder = [rulesTempDict objectForKey:ORDER];
    else
        rulesByOrder = rulesTempDict;
    for (id rule in rulesByOrder) {
        /* goto "subviews" dictionary */
        rulesDict = [rulesTempDict objectForKey:rule];
        if ([rulesDict isKindOfClass:[NSString class]]) {
            id value = [self processFormula:rulesDict initDict:agcDict translatedDict:*templateDict];
            if (value) {
                NSArray *arr = [Helper getArrayProperties:rule];
                if ([arr count] == 1) {
                    NSNumber *nr = [self getNumber:value];
                    if (nr)
                        value = nr;
                    [rulesInitDict setObject:value forKey:rule];
                } else {
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
    startXArtboard = sceneNo * OFFSETBOARD;
    id scene = [self processTemplateDict:&viewDict agcDict:dict finalDict:finalDict ofType:VIEW];
    scene = [self convertSceneToJsonFormat:scene];
    [children addObject:scene];
    [*artworkFiles setObject:children forKey:CHILDREN];
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

    NSMutableDictionary *finalDict = [Helper deepCopy: [agcToXmlTemplate objectForKey:CONTENT]];
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
    transformObjects[SCALE][SHAPE] = [NSNumber numberWithInt:1];
    transformObjects[SCALE][ISIMAGE] = [NSNumber numberWithInt:1];
    transformObjects[SCALE][BUTTON_IMAGE] = [NSNumber numberWithInt:1];
    transformObjects[COLOR] = [[NSMutableDictionary alloc] init];
    transformObjects[COLOR][XML_RED] = [NSNumber numberWithInt:1];
    transformObjects[COLOR][XML_GREEN] = [NSNumber numberWithInt:1];
    transformObjects[COLOR][XML_BLUE] = [NSNumber numberWithInt:1];
    sceneNo = 0;
}


@end
