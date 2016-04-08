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
    agcToXmlTemplate = defDict;
    translationDict = ruleDict;
    uniqueIds = [[NSMutableDictionary alloc] init];


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

-(void) computeObjects:(NSString *)rule condition:(NSString*)cond params:(NSDictionary *)dict {
    NSMutableDictionary *objDict = [[[agcToXmlTemplate objectForKey:@"subviews"] objectForKey:rule] mutableCopy];
    
    
    
    


}


-(NSDictionary*) processWholeXmlFile {
    
    NSMutableDictionary *finalDict = [NSKeyedUnarchiver unarchiveObjectWithData:[NSKeyedArchiver archivedDataWithRootObject: [agcToXmlTemplate objectForKey:@"content"]]];
    NSLog(@"finalDict = %@ %@", finalDict, agcToXmlTemplate);
    NSMutableDictionary *subviews = [[agcToXmlTemplate objectForKey:@"subviews"] mutableCopy];
    NSMutableDictionary *rulesTempDict = [[finalDict objectForKey:@"view"] objectForKey:@"rules"];
    NSMutableDictionary *tempDict = [finalDict objectForKey:@"view"] ;
    
    for (id rule in rulesTempDict) {
        NSLog(@"rule = %@", rule);
        NSArray *keys = [self splitVariable:rule];
        
        
        if ([keys count] == 1) {
            //TODO goto "subviews" dictionary
            NSLog(@"TO Process %@", rule);
            NSMutableDictionary *rulesDict = [rulesTempDict objectForKey:rule];
            NSString* cond = [[rulesDict allKeys] objectAtIndex:0];
            [self computeObjects:rule condition:cond params:[rulesTempDict objectForKey:rule]];
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
                return [self processWholeXmlFile];
        
    }
    // look at subviews
    NSArray *array = [NSArray arrayWithObjects:@"subviews", nil];
    NSDictionary *xmlDict;
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
