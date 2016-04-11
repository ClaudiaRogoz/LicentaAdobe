//
//  XMLGenerator.m
//  XMLParser
//
//  Created by crogoz on 07/04/16.
//  Copyright © 2016 crogoz. All rights reserved.
//

#import "XMLGenerator.h"

#define DEF_PATH @"/Users/crogoz/Desktop/XMLParser/XMLParser/Defs.json"
#define RULES_PATH @"/Users/crogoz/Desktop/XMLParser/XMLParser/Rules.json"
#define TEST_PATH @"/Users/crogoz/Desktop/XMLParser/XMLParser/TestGenerator.json"

#define RANDOM @"$rand"
#define SCENE @"$sceneNo"
#define DEFAULT @"default"
#define ARTBOARDSCENE @"$artboardsceneNo"

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

    NSDictionary *translation = [gen getXmlForAgcObject:agcTemplate];
    NSLog(@"Translation Dictionary = %@", translation);
}

-(void)initializeWithDefs:(NSDictionary*)defDict rules:(NSDictionary*)ruleDict {
    agcToXmlTemplate = [defDict mutableCopy];
    translationDict = [ruleDict mutableCopy];
    //uniqueIds = [[NSMutableDictionary alloc] init];
    sceneNo = 0;


}


-(NSString *) computeValue:(NSString *)initValue {
    
    if ([initValue isEqualToString:RANDOM]) {
        //generate a random value; needed for id
        return [[NSUUID UUID] UUIDString];
        
    
    }
    
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
-(NSString *) toString:(NSMutableDictionary *)dict name:(NSString*)varName {
    //NSArray *order = [dict objectForKey:@"toString"];
    
    /*NSMutableString *tagStr = [[NSMutableString alloc] init];
   
    for (id object in order) {
        
    }*/
    
    return @"";
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
    
    NSMutableDictionary *objDict = [[[agcToXmlTemplate objectForKey:@"subviews"] objectForKey:rule] mutableCopy];
    
    
    // now changing based on params
    if (!cond) {
        //just generate the tag; no other transformations are needed
        return objDict;
        
    }
    //get values from agc in order to transfer them into xml
    id values = agcParams;
    NSArray *goToAgc = [self splitVariable:cond];
    
    for (id key in goToAgc) {
        
        id nodeValue;
        NSLog(@"Check for key = %@", key);
        if ([key hasPrefix:@"$"] && [key isEqualToString:SCENE]) {
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
        return nil;
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
        
    }
    
    NSLog(@"ValuesForKey = %@", values);
    return values;

}


-(NSDictionary*) processWholeXmlFromAgc:(NSDictionary *)agcDict {
    
    NSMutableDictionary *finalDict = [NSKeyedUnarchiver unarchiveObjectWithData:[NSKeyedArchiver archivedDataWithRootObject: [agcToXmlTemplate objectForKey:@"content"]]];
    NSLog(@"finalDict = %@ %@", finalDict, agcToXmlTemplate);
   // NSMutableDictionary *subviews = [[agcToXmlTemplate objectForKey:@"subviews"] mutableCopy];
    NSMutableDictionary *rulesTempDict = [[finalDict objectForKey:@"view"] objectForKey:@"rules"];
    NSMutableDictionary *tempDict = [finalDict objectForKey:@"view"] ;
    
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
            
            [self computeObjects:rule condition:cond params:[rulesTempDict objectForKey:rule] agcDict:agcDict];
        
        } else {
            //TODO the modified variable is in the "finalDict"
            
            for (id key in [keys subarrayWithRange:NSMakeRange(0, [keys count] -1)]) {
                tempDict = [tempDict objectForKey:key];
            }
            NSString *value = [self computeValue:[rulesTempDict objectForKey:rule]];
            NSLog(@"Set value = %@ %@\n%@", value, [keys lastObject], tempDict);
            [tempDict setObject:value forKey:[keys lastObject]];
            
        }
    
    }
    
    return finalDict;
}

-(NSDictionary*) getXmlForAgcObject:(NSDictionary*)typeAgcObject {
    NSString *agcObject = [typeAgcObject objectForKey:@"type"];
    if (!agcObject) {
        // it was given the whole dictionary to process => goto @"content"; type = "view"
        // TODO insert header + footer of the xml file
        return [self processWholeXmlFromAgc:typeAgcObject];
        
    }
    // look at subviews
    NSArray *array = [NSArray arrayWithObjects:@"subviews", nil];
   // NSDictionary *xmlDict;
    for (id key in array) {
        NSDictionary *result = [[translationDict objectForKey:key] objectForKey:agcObject];
        if (result)
            return result;
    
    }
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
