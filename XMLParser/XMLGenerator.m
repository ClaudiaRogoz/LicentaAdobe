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
    XMLGenerator *gen = [[XMLGenerator alloc] initWithError:&error];
    NSData *defData = [NSData dataWithContentsOfFile:DEF_PATH];
    NSLog(@"Data %@", defData);
    
    NSData *ruleData = [NSData dataWithContentsOfFile:RULES_PATH];
    NSLog(@"D1 = %@", ruleData);
    
    NSMutableDictionary *defDictionary = [NSJSONSerialization JSONObjectWithData:defData options:NSJSONReadingMutableContainers error:&error];
 
    NSDictionary *ruleDictionary = [NSJSONSerialization JSONObjectWithData:ruleData options:NSJSONReadingMutableContainers error:&error];
    [gen setXmlPath:xmlPath];
    [gen initializeWithDefs:defDictionary rules:ruleDictionary];
    
    NSMutableDictionary *agcTemplate = [[NSMutableDictionary alloc] init];
    
    NSData *testData = [NSData dataWithContentsOfFile:TESTIL_PATH];
    agcTemplate =  [NSJSONSerialization JSONObjectWithData:testData options:kNilOptions error:&error];
    NSLog(@"AgcTemplate = %@", agcTemplate);
    NSString *translation = [gen getXmlForAgcObject:agcTemplate];
    NSLog(@"Translation Dictionary = %@", translation);
   
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


-(NSString *) computeValue:(NSString *)initValue forDict:(NSDictionary *)agcDict{
    
    
    if ([initValue isEqualToString:RANDOM]) {
        //generate a random value; needed for id
        return [[NSUUID UUID] UUIDString];
        
    } else {
        //if it depends on an agc tag
        initValue = [initValue substringFromIndex:1];
        NSArray *array = [initValue componentsSeparatedByString:@"."];
        
        id value = agcDict;
        for (id key in array) {
            value = [value objectForKey:key];
           
        }
        
        return value;
    
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
    
    NSLog(@"ABC to merge %@ with %@\nParams = %@", defaultDict, *initDict, paramDict);
    if ([defaultDict count] > 0)
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
            NSLog(@"transform %@ with %@", key, [paramDict objectForKey:key]);
            [*initDict setObject:[paramDict objectForKey:key] forKey:key];
        }
    }
    //TODO? maybe we need to propagate pairs from paramDict <maybe ?!> => then "toString" MUST be rewritten!!!

}

-(void) mergeDictionaries:(NSMutableDictionary **)objDict withDict:(NSMutableDictionary *)dictValue
              usingValues:(NSDictionary *)paramsValue {
    
    NSLog(@"DictValue = %@ %@ %@", dictValue, *objDict, paramsValue);
    NSMutableDictionary *defaultDict = [*objDict objectForKey:DEFAULT];
    //paramsValue = [paramsValue objectForKey:[[paramsValue allKeys] objectAtIndex:0]];
    
    for (id key in [*objDict allKeys]) {
        id value = [*objDict objectForKey:key];
        NSLog(@"key = %@ value = %@ Dict = %@", key, value, dictValue);
        if ([value isKindOfClass:[NSString class]] && [value hasPrefix:@"$"]) {
            value = [dictValue objectForKey:[value substringFromIndex:1]];
            
            if (value) {
                NSLog(@"Changing %@ with %@", key, value);
                if ([[transformObjects objectForKey:@"size"] objectForKey:key]) {
                    /* TODO change the size -> scale */
                    NSLog(@"Key need to be resized = %@", key);
                } else if ([[transformObjects objectForKey:@"color"] objectForKey:key]) {
                    /* change color */
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
                
                if (![value hasPrefix:@"$"])
                    [*objDict setValue:value forKey:key]; /* no need for transformation */
                else if ([dictValue objectForKey:[[self splitVariable:value] objectAtIndex:0]]) {//[[translationDict objectForKey:value] isEqualToString:key]){ /* used for tx & ty */
                   // NSLog(@"%@ === %@", [translationDict objectForKey:value], key);
                    NSLog(@"%@", [self splitVariable:value]);
                    NSLog(@"there is a translation :D %@", dictValue);
                    id tvalue = [[self splitVariable:value] objectAtIndex:0];
                    [*objDict setValue:[dictValue objectForKey:tvalue] forKey:key];
                } else {/* use default values */
                    [*objDict setObject:[defaultDict objectForKey:key] forKey:key];
                }
                    
            }
        }
        
    }
    
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
    
    NSLog(@"Mutiple conditions = %@", cond);
    for (id condition in cond) {
        id values = agcParams;
        NSLog(@"Obj = %@", objDict);
        NSLog(@"Check for the following condition: %@", condition);
    NSArray *goToAgc = [self splitVariable:condition];
    NSLog(@"Dependency = %@ %@", goToAgc, values);
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
        if (![dictValue isKindOfClass:[NSArray class]]) {
            NSLog(@"2merge = %@ with %@dict= %@ %@", objDict,  dict, dictValue, agcParams);
            
            [self mergeDictionaries:&objDict withDict:dictValue usingValues:[dict objectForKey:condition]];
            //[self mergeDefaultValues:[dict objectForKey:dep] withDict:&objDict usingDict:dictValue];
        }
        else {
            NSMutableDictionary *finalDict = [NSKeyedUnarchiver unarchiveObjectWithData:[NSKeyedArchiver archivedDataWithRootObject: [agcToXmlTemplate objectForKey:SUBVIEWS]]];
            NSMutableDictionary *newObjDict = [NSKeyedUnarchiver unarchiveObjectWithData:[NSKeyedArchiver archivedDataWithRootObject: [objDict mutableCopy]]];
            objDict = [[NSMutableArray alloc] init];
            NSLog(@"objects in subviews are = %@", dictValue);
            for (id object in dictValue) {
                /* obtain the type of each object 
                 * get the corresponding template*/
                id type = [translationDict objectForKey:[object objectForKey:@"type"]];
                if (!type)
                    continue;
                NSLog(@"OBJDict  = %@", objDict);
                NSLog(@"TypeABC = %@", type);
                /*TODO1:00!!*/
                NSLog(@"newObj = %@", [newObjDict objectForKey:type]);
                NSMutableDictionary *typeObjDict = [NSKeyedUnarchiver unarchiveObjectWithData:[NSKeyedArchiver archivedDataWithRootObject: [newObjDict objectForKey:type]]];//[newObjDict objectForKey:type];//[NSKeyedUnarchiver unarchiveObjectWithData:[newObjDict objectForKey:type]];
                //NSLog(@"ParamsZ = %@ %@ %@", typeObjDict, object, finalDict);
                NSLog(@"--------------------------------------------\n");
                [self processTemplateDict:&typeObjDict agcDict:object finalDict:finalDict];
                //[self mergeDefaultValues:object withDict:&typeObjDict usingDict:dict];
                NSLog(@"Merged = %@", typeObjDict);
                NSMutableDictionary *subViewDict = [[NSMutableDictionary alloc] init ];
                [subViewDict setObject:typeObjDict forKey:type];
                [objDict addObject:subViewDict];
            }
            
            NSLog(@"We've found that the Subview contains: %@", objDict);
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
            else
                cond = [rulesDict allKeys];// objectAtIndex:0];
            
            NSLog(@"The condition %@ = %@ %@ %@ %@", rule, cond, rule, [rulesTempDict objectForKey:rule], agcDict);
            NSMutableDictionary *mergeDict = [self computeObjects:rule condition:cond params:[rulesTempDict objectForKey:rule] agcDict:agcDict];
            NSLog(@"Merge dict = %@ For %@", mergeDict, rule);
            
            if (mergeDict != nil) {
                [rulesInitDict setObject:mergeDict forKey:rule];
                NSLog(@"After merge  =  %@ ", rulesInitDict);
            }
            
        } else {
            //TODO the modified variable is in the "finalDict"
            //remove the $x.y.z... rule
            //[rulesInitDict removeObjectForKey:rule];
            NSLog(@"TMPL = %@ %@", *templateDict, keys);
            id val = *templateDict;
            for (id key in [keys subarrayWithRange:NSMakeRange(0, [keys count] -1)]) {
                val = [val objectForKey:key];
            }
            NSString *value = [self computeValue:[rulesTempDict objectForKey:rule] forDict:agcDict];
            NSLog(@"Set value = %@ %@\n%@", value, [keys lastObject], val);
            NSLog(@"Components = %@", [value componentsSeparatedByString:@" "]);
            
            if ([[value componentsSeparatedByString:@" "] count] == 1)
                [val setObject:value forKey:[keys lastObject]];
            else {
                NSString *stringValue = [NSString stringWithFormat:@"\"%@\"", value];
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
            /* find widtth and height for image */
            
           
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
            NSBitmapImageRep *imageRep = [NSBitmapImageRep imageRepWithContentsOfFile:href];
            
            NSData *data = [imageRep representationUsingType:NSPNGFileType properties:nil];
            [data writeToFile:toCopyPath atomically:YES];
            // Save the data
            // NSString *copyImageToXcodeDir = [NSString stringWithFormat:@"%@/%@",xmlPath, theFileName];
            
            NSString *tmp = @"";
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
            
            /* just an ordinary leaf tag; create a one-line with the given attributes */
            NSLog(@"OneLiner = %@ %@", key, attr);
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
        if ([resourcesDict length]) {
            //TODO append resources if it exists
            NSString *resources = [NSString stringWithFormat:@"%@\n%@\n%@",XMLRESOURCES, resourcesDict, XMLRESOURCESF];
            [stringFooter appendString:resources];
        }
        
        [stringFooter appendFormat:@"\n%@", XMLDOCUMENTF];
        
        NSString *xmlFile = [self surroundWithHeader:XMLHEADER footer:stringFooter string:xmlGen];
        NSLog(@"XML = %@", xmlFile);
        NSData *data = [xmlFile dataUsingEncoding:NSUTF8StringEncoding];

        NSError *err;
        NSXMLDocument *doc = [[NSXMLDocument alloc] initWithData:data options:NSXMLDocumentTidyXML error:&err];
        NSData* xmlData = [doc XMLDataWithOptions:NSXMLNodePrettyPrint];
        [xmlData writeToFile:@"new.xml" atomically:YES];
        
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
