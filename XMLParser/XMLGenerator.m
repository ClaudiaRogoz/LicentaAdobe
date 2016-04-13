//
//  XMLGenerator.m
//  XMLParser
//
//  Created by crogoz on 07/04/16.
//  Copyright © 2016 crogoz. All rights reserved.
//

#import "XMLGenerator.h"



@implementation XMLGenerator

+ (void)readTemplate
{
    NSError *error;
    XMLGenerator *gen = [[XMLGenerator alloc] initWithError:&error];
    NSData *defData = [NSData dataWithContentsOfFile:DEF_PATH];
    NSData *ruleData = [NSData dataWithContentsOfFile:RULES_PATH];
    
    NSMutableDictionary *defDictionary = [NSJSONSerialization JSONObjectWithData:defData options:NSJSONReadingMutableContainers error:&error];
 
    NSDictionary *ruleDictionary = [NSJSONSerialization JSONObjectWithData:ruleData options:NSJSONReadingMutableContainers error:&error];
    
    [gen initializeWithDefs:defDictionary rules:ruleDictionary];
    
    NSMutableDictionary *agcTemplate = [[NSMutableDictionary alloc] init];
    
    NSData *testData = [NSData dataWithContentsOfFile:TEST_PATH];
    agcTemplate =  [NSJSONSerialization JSONObjectWithData:testData options:kNilOptions error:&error];
    NSLog(@"AgcTemplate = %@", agcTemplate);
    NSString *translation = [gen getXmlForAgcObject:agcTemplate];
    NSLog(@"Translation Dictionary = %@", translation);
   
}


-(void)initializeWithDefs:(NSDictionary*)defDict rules:(NSDictionary*)ruleDict {
    agcToXmlTemplate = [defDict mutableCopy];
    translationDict = [ruleDict mutableCopy];
    resourcesDict = [[NSMutableDictionary alloc] init];
    sceneNo = 0;


}


-(NSString *) computeValue:(NSString *)initValue {
    
    if ([initValue isEqualToString:RANDOM]) {
        //generate a random value; needed for id
        return [[NSUUID UUID] UUIDString];
        
    } /*else {
        //if it depends on an agc tag
        initValue = [initValue substringFromIndex:1];
        NSArray *array = [initValue componentsSeparatedByString:@"."];
        
    
    }*/
    
    return initValue;

}

-(NSArray *) splitVariable:(NSString*) varName {
    
    NSLog(@"Check for %@", varName);
    if ([varName hasPrefix:@"$"]) {
        return [[varName substringFromIndex:1] componentsSeparatedByString:@"."];
    }
    
    return [NSArray arrayWithObjects:varName, nil];

}

// TODO generate toString depending on
-(NSString *) toString:(NSMutableDictionary *)dict name:(NSString*)varName isLeaf:(BOOL)leaf {
    NSArray *order = [dict objectForKey:@"toString"];
    //NSLog(@"Order = %@", order);
    NSMutableString *tagStr = [NSMutableString stringWithFormat:@"<%@", varName];
    
    for (id object in order) {
        [tagStr appendFormat:@" %@=%@", object, [dict objectForKey:object]];
    }
    if (leaf)
        [tagStr appendFormat:@"/>"];
    else
        [tagStr appendFormat:@">"];
    
    return tagStr;
}

-(void) mergeDefaultValues:(NSDictionary*)defaultDict withDict:(NSMutableDictionary **) initDict usingDict:(NSDictionary*) paramDict {
    
    NSLog(@"Trying to merge %@ with %@", defaultDict, *initDict);
    for (id key in [defaultDict allKeys]) {
        NSString *value = [defaultDict objectForKey:key];
        [*initDict setObject:value forKey:key];
    }
    
    
    NSString *dependency = [[paramDict allKeys] objectAtIndex:0];
    paramDict = [paramDict objectForKey:dependency];
    NSLog(@"Trying to merge %@ with %@", paramDict, *initDict);
    for (id key in [*initDict allKeys]) {
        NSString *value = [*initDict objectForKey:key];
        NSLog(@"keyK = %@ %@", key, value);
        BOOL toTransform = [value isKindOfClass:[NSString class]] && [value hasPrefix:@"$"];
        if (toTransform) {
            NSLog(@"transform %@", key);
            [*initDict setObject:[paramDict objectForKey:key] forKey:key];
        }
    }
    //TODO? maybe we need to propagate pairs from paramDict <maybe ?!> => then "toString" MUST be rewritten!!!

}

-(NSMutableDictionary *) computeObjects:(NSString *)rule condition:(NSString*)cond params:(NSDictionary *)dict agcDict:agcParams{
    
    NSMutableDictionary *objDict;
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
    id values = agcParams;
    NSArray *goToAgc = [self splitVariable:cond];
    NSLog(@"Dependency = %@ %@", goToAgc, agcParams);
    for (id key in goToAgc) {
        
        id nodeValue;
        NSLog(@"Check for key = %@", key);
        if ([key hasPrefix:@"$"] && [key isEqualToString:SCENENO]) {
            nodeValue = [values objectAtIndex:sceneNo];
        
        } else if ([key hasPrefix:@"$"] && [key isEqualToString:ARTBOARDSCENE]) {
            NSString *artboard = [NSString stringWithFormat:@"artboard%d", sceneNo +1];
            nodeValue = [values objectForKey:artboard];

        } else {
            nodeValue = [values objectForKey:key];
            
        }
        
        values = nodeValue;
        NSLog(@"TempV = %@", values);
    }
    
    NSMutableDictionary *dictValue = values;
    BOOL isEmpty = ([dictValue count] == 0);
    if (isEmpty && !dictValue) {
        //TODO use default values!!!
        NSLog(@"IT is null");
        [self mergeDefaultValues:[objDict objectForKey:DEFAULT] withDict:&objDict usingDict:dict];
        NSLog(@"t0 merge = %@", objDict);
        return objDict;
    } else if (isEmpty) {
        //no subview found
        NSLog(@"it is empty");
        return nil;
    } else {
        //TODO check type 08.03.2016
        // based on type look at rules.json -> gotoSubviews..
        //maybe recursive ?
        //merge "dict" with "values"
        NSLog(@"NOT NULL TODO\n");
        if (![dictValue isKindOfClass:[NSArray class]])
            [self mergeDefaultValues:dictValue withDict:&objDict usingDict:dict];
        else {
            NSMutableDictionary *tree = [[NSMutableDictionary alloc] init];
            for (id object in dictValue) {
                /* obtain the type of each object 
                 * get the corresponding template*/
                id type = [translationDict objectForKey:[object objectForKey:@"type"]];
                NSMutableDictionary *typeObjDict = [objDict objectForKey:type];
                 NSMutableDictionary *finalDict = [NSKeyedUnarchiver unarchiveObjectWithData:[NSKeyedArchiver archivedDataWithRootObject: [agcToXmlTemplate objectForKey:SUBVIEWS]]];
                NSMutableDictionary *tb = [self processTemplateDict:&typeObjDict agcDict:object finalDict:finalDict];
                //[self mergeDefaultValues:object withDict:&typeObjDict usingDict:dict];
                NSLog(@"Merged = %@", tb);
            }
            
        }
        return objDict;
        
    }
    
    NSLog(@"ValuesForKey = %@", values);
    return values;

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
            //NSArray *conds = [rulesDict allKeys];
            NSString* cond;
            if ([rulesDict count] == 0)
                cond = nil;
            else
                cond = [[rulesDict allKeys] objectAtIndex:0];
            
            NSMutableDictionary *mergeDict = [self computeObjects:rule condition:cond params:[rulesTempDict objectForKey:rule] agcDict:agcDict];
            NSLog(@"Merge dict = %@ For %@", mergeDict, rule);
            
            if (mergeDict != nil) {
                [rulesInitDict setObject:mergeDict forKey:rule];
                NSLog(@"After merge  =  %@ ", rulesInitDict);
            }
            
        } else {
            //TODO the modified variable is in the "finalDict"
            //remove the $x.y.z... rule
            [rulesInitDict removeObjectForKey:rule];
            for (id key in [keys subarrayWithRange:NSMakeRange(0, [keys count] -1)]) {
                *templateDict = [*templateDict objectForKey:key];
            }
            NSString *value = [self computeValue:[rulesTempDict objectForKey:rule]];
            NSLog(@"Set value = %@ %@\n%@", value, [keys lastObject], *templateDict);
            [*templateDict setObject:value forKey:[keys lastObject]];
            
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

/* TODO pretty print xml using tab = count nr of subtags etc !! */
-(NSMutableString *) parseToString:(NSMutableString *)str dict:(NSDictionary *)dict name:(NSString *) name{
    
    NSMutableString* tmp = [NSMutableString stringWithFormat:@""];
    /* now we only have to translate the currentDict */
    for (id key in [dict objectForKey:TOSTRING]) {
        id attr = [dict objectForKey:key];
        NSLog(@"At key = %@ with %@", key, str);
        if ([key isEqualToString:RULES]) {
            
            [tmp appendString:[self parseToString:tmp dict:attr name:key]] ;
           
        
        } else if ([key isEqualToString:HEADER]) {
                /* create a new top tag with dict[allKeys] objeectAtIndex[0] */
                [ tmp appendString: [self toString:attr name:name isLeaf:FALSE]];
            
            
        } else if ([key isEqualToString:SUBVIEWS]){
            NSLog(@"Key = %@ is Subview\n", key);
            
            
        } else if ([[agcToXmlTemplate objectForKey:SUBTAGS] objectForKey:key]){
            
            /* just an ordinary leaf tag; create a one-line with the given attributes */
            NSString *ret = [self toString:attr name:key isLeaf:TRUE];
             [ tmp appendString: [NSString stringWithFormat:@"\n\t%@", ret]];
            
        }
    }
    
    return tmp;
    
    
}

-(NSString*) getXmlForAgcObject:(NSDictionary*)typeAgcObject {
    NSString *agcObject = [typeAgcObject objectForKey:@"type"];
    if (!agcObject) {
        // it was given the whole dictionary to process => goto @"content"; type = "view"
        // TODO insert header + footer of the xml file
        NSMutableString *finalString = [[NSMutableString alloc] init];
        NSLog(@"typeX = %@ %@", typeAgcObject, agcToXmlTemplate);
        NSDictionary *dict = [[self processWholeXmlFromAgc:typeAgcObject] objectForKey: @"view"];
        NSLog(@"D1ct = %@", dict);
        NSString *xmlGen = [self parseToString:finalString dict:dict name:@"view"];
        NSMutableString *stringFooter = [NSMutableString stringWithFormat:@"%@\n%@",@"</view>", XMLFOOTER];
        if ([resourcesDict count]) {
            //TODO append resources if it exists
        }
        
        [stringFooter appendFormat:@"\n%@", XMLDOCUMENTFOOTER];
        
        NSString *xmlFile = [self surroundWithHeader:@"" footer:stringFooter string:xmlGen];
        NSLog(@"EQStr = %@", xmlFile);
        return finalString;
        
    }
    // TODO look at subviews
   /* NSArray *array = [NSArray arrayWithObjects:@"subviews", nil];
   // NSDictionary *xmlDict;
    for (id key in array) {
        NSDictionary *result = [[translationDict objectForKey:key] objectForKey:agcObject];
        if (result)
            return @"";
    
    }*/
    return nil;
}

-(void) generateXmlForTag:(NSDictionary*)agcDict
{
    NSDictionary *xmlTemplate = [self getXmlForAgcObject:agcDict];
    
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
