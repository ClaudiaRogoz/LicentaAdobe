//
//  XMLReader.m
//  XMLParser
//
//  Created by crogoz on 05/03/16.
//  Copyright © 2016 crogoz. All rights reserved.
//

#include <CommonCrypto/CommonDigest.h>
#import "XMLReader.h"


NSString *const kXMLReaderTextNodeKey = @"text";


@interface XMLReader (Internal)

- (id)initWithError:(NSError **)error;
- (NSDictionary *)objectWithData:(NSData *)data;

@end


@implementation XMLReader

#pragma mark -
#pragma mark Public methods


- (NSString *) appendModifiedString:(NSMutableDictionary *)dict minTagOffset:(NSNumber **)tagOffset
{
    NSMutableString *newString = [[NSMutableString alloc] init];
    
    //maybe extedn to other subTags ?!
    NSArray *order = [NSArray arrayWithObjects:@"rect", @"fontDescription", @"color", nil];
    NSLog(@"Dict = %@", dict);
   // int cnt = 0;
    for (id key in order) {
        
        if (![dict objectForKey:key])
            continue;
        
        NSString *tagKey = [NSString stringWithFormat:@"<%@", key];
        NSRange rangeOfString = [newString rangeOfString:tagKey];
        NSString *value = [dict objectForKey:key];
        
        
        if (rangeOfString.location == NSNotFound)  {
            
            [newString appendString:value];
            
        } else {
            unsigned long start = (unsigned long)rangeOfString.location;
            unsigned long end = [newString length];
            
            newString = [[newString stringByReplacingCharactersInRange:NSMakeRange(start, end - start) withString:value] mutableCopy];
        }
        
    }
    
    return newString;
    
}

/* second = prev dictionary; first = current dictionary */
- (NSMutableDictionary*) compare2Artboards:(NSArray *) first dict2:(NSArray *) second artboard_info:(NSMutableDictionary *)jsonArtboards offsetGroup:(NSMutableDictionary *)offsetGroupDict numberGroup:(NSNumber *) nr
{
    
    //TODO first only for modified objects
    unsigned long counter = MIN([first count], [second count]);
    NSMutableDictionary *xmlExport = [[NSMutableDictionary alloc] init];
    for (int i = 0; i< counter; i++) {
        NSLog(@"Counter = %d", i);
        NSDictionary *prev = [second objectAtIndex:i];
        NSDictionary *newD = [first objectAtIndex:i];
        
        id typeP = [prev objectForKey:@"type"];
        id typeN = [newD objectForKey:@"type"];
        NSLog(@"NameXOXO %@", [newD objectForKey:@"name"]);
        // check if it is the same object (no adding, nor deleting, just modifyingn ops)
        if ([typeN isEqualToString:typeP]) {
            NSLog(@"Same type = %@\n", typeN);
            id solType = [exportAgc objectForKey:typeN];
            
            //if type == Group
            if ([solType isKindOfClass:[NSArray class]]) {
                NSLog(@"Group thing");
                id transform = [newD objectForKey:@"transform"];
                int prevTx = [[offsetGroupDict objectForKey:@"tx"] intValue];
                int prevTy = [[offsetGroupDict objectForKey:@"ty"] intValue];
                int tx = [[transform objectForKey:@"tx"] intValue] + prevTx;
                int ty = [[transform objectForKey:@"ty"] intValue] + prevTy;
                NSMutableDictionary *dict = [@{@"tx" : [NSNumber numberWithInt:tx], @"ty" : [NSNumber numberWithInt:ty]} mutableCopy];
                
                id newDictCh = [[newD objectForKey:@"group"] objectForKey:@"children"];
                id prevDictCh = [[prev objectForKey:@"group"] objectForKey:@"children"];
                
                
                NSLog(@"Group check for %@ \n %@", newDictCh, prevDictCh);
                NSMutableDictionary *newXmlDict  = [self compare2Artboards:newDictCh dict2:prevDictCh artboard_info:jsonArtboards offsetGroup:dict numberGroup:[NSNumber numberWithInt:i + 1]];
                nr = 0;
                NSLog(@"------------------------------------Group check DONE %@ %@", xmlExport, newXmlDict);
                for (id newKey in newXmlDict) {
                    NSMutableDictionary *dict = [newXmlDict objectForKey:newKey];
                    
                    NSMutableDictionary *dictGroup = [xmlExport objectForKey:[NSNumber numberWithInt:i + 1]];
                    if (dictGroup == nil) {
                        [xmlExport setObject:dict forKey:[NSNumber numberWithInt:i + 1]];
                    } else {
                        [dictGroup addEntriesFromDictionary:dict];
                    }
                
                }
                NSLog(@"Value = %@", xmlExport);
                [offsetGroupDict setObject:[NSNumber numberWithInt:prevTx] forKey:@"tx"];
                [offsetGroupDict setObject:[NSNumber numberWithInt:prevTx] forKey:@"ty"];
                
                continue;
                
            }
            
            // only one possibility when type = solType (eg. textfield)
            if ([solType isKindOfClass:[NSString class]]) {
                NSLog(@"We are Here\n");
                NSDictionary *currAttr = [attributes objectForKey:solType];
                
                NSMutableDictionary *trList = [[NSMutableDictionary alloc] init];
                NSLog(@"JsonArtboards = %@", jsonArtboards);
                bool ok = [self checkAreEqual:newD prevDict:prev attr:currAttr outList:&trList equal:true json_info:jsonArtboards];
                
                if (ok == false) {
                    
                    NSNumber *tagNo = [NSNumber numberWithInt:i + 1]; // DON"T FORGET in the nsdictionary counter starts at 1!!!!!
                    if ([nr intValue])
                        xmlExport[tagNo] = trList;
                    else
                        xmlExport[tagNo] = trList;
                }
                continue;
                
            }
            
            //type = NSMutableDictionary eg.shape
            //TODO change each NSMutabelDict into NSMutableDict of NSArray (it's easier)
            for (id key in solType){
                
                id cond = [solType objectForKey:key];
                if ([cond isKindOfClass:[NSArray class]]) {
                    //is kind of array => multiple rules must be achieved
                    NSString *condIsOfType = @"";
                    int isOk = true;
                    for (id rule in cond) {
                        NSArray *array = [rule componentsSeparatedByString:@"."];
                        
                        id value1 = prev;
                        id value2 = newD;
                        NSLog(@"Array = %@", array);
                        for (id key1 in [array subarrayWithRange:NSMakeRange(0, [array count] -1)]) {
                            NSLog(@"Value 1 = %@", value1);
                            if (![value1  objectForKey:key1] || ![value2  objectForKey:key1]) {
                                condIsOfType  = @"NOT";
                                break;
                            }
                            value1 = [value1 objectForKey:key1];
                            value2 = [value2 objectForKey:key1];
                        }
                        
                        bool eqValues = [value1 isEqualToString: value2] && [value1 isEqualToString:[array lastObject]];
                        if ([condIsOfType isEqualToString:@"NOT"] || !eqValues) {
                            isOk = false;
                            break;
                        }
                    }
                    
                    
                    if (isOk){
                        NSLog(@"Chack for keyXXX = %@ %@ %d", key, cond, i);
                        NSDictionary *currAttr = [attributes objectForKey:key];
                        NSLog(@"currAttr = %@ %@ %@", newD, prev, currAttr);
                        NSMutableDictionary *trList = [[NSMutableDictionary alloc] init];
                        bool ok = [self checkAreEqual:newD prevDict:prev attr:currAttr outList:&trList equal:true json_info:jsonArtboards];
                        
                        if (ok == false) {
                            
                            NSNumber *tagNo = [NSNumber numberWithInt:i + 1]; // DON"T FORGET in the nsdictionary counter starts at 1!!!!!
                            NSLog(@"RList = %@ %@", trList, tagNo);
                            if ([nr intValue]) {
                                xmlExport[tagNo] = trList;
                            }
                            else
                                xmlExport[tagNo] = trList;
                            
                            NSLog(@"RList %@", xmlExport);
                            
                        }
                        break;
                    }
                    
                }
                else if ([cond isKindOfClass:[NSString class]]) {
                    NSArray *array = [cond componentsSeparatedByString:@"."];
                    
                    id value1 = prev;
                    id value2 = newD;
                    
                    for (id key1 in [array subarrayWithRange:NSMakeRange(0, [array count] -1)]) {
                        value1 = [value1 objectForKey:key1];
                        value2 = [value2 objectForKey:key1];
                    }
                    
                    NSLog(@"Chack for key = %@", key);
                    if ([value1 isEqualToString: value2] && [value1 isEqualToString:[array lastObject]]){
                        
                        NSDictionary *currAttr = [attributes objectForKey:key];
                        
                        NSMutableDictionary *trList = [[NSMutableDictionary alloc] init];
                        bool ok = [self checkAreEqual:newD prevDict:prev attr:currAttr outList:&trList equal:true json_info:jsonArtboards];
                        
                        if (ok == false) {
                            NSNumber *tagNo = [NSNumber numberWithInt:i + 1]; // DON"T FORGET in the nsdictionary counter starts at 1!!!!!
                            xmlExport[tagNo] = trList;
                            continue;
                        }
                        
                    }
                }
            }
            
        }
        
    }
    
    return xmlExport;
    
}

//transform from XD coordinates to Xcode coordinates
-(bool) checkTransformToAbsoluteValue:(NSNumber **)value variable:(NSString *)var scale_dict:(NSDictionary *) scaleDict other_updates:(NSMutableDictionary **) otherUpdates
{
    if ([var isEqualToString:@"$rect.x"] || [var isEqualToString:@"$rect.y"]) {
        //transform relative coord to absolute coord
        NSArray *arr = [var componentsSeparatedByString:@"."];
        int offsetValue = [[scaleDict objectForKey:[arr lastObject]] intValue];
        
        NSLog(@"Dimension: %d %d", widthXMLArtboard, widthAgcArtboard);
        NSLog(@"Dimension: %d %d", heightXMLArtboard, heightAgcArtboard);
        //scale to xcode artboard
        float xScaleFactor = (float)widthXMLArtboard / widthAgcArtboard;
        float yScaleFactor = (float)heightXMLArtboard / heightAgcArtboard;
        
        float scaledValue = [*value floatValue] - offsetValue;
        if ([var isEqualToString:@"$rect.x"])
            scaledValue = scaledValue * xScaleFactor;
        else
            scaledValue = scaledValue * yScaleFactor;
        
        *value = [NSNumber numberWithFloat: scaledValue];
        
        
        
        
        return true;
    }
    else if ([var isEqualToString:@"$color.red"] || [var isEqualToString:@"$color.green"] || [var isEqualToString:@"$color.blue"]) {
        
        *value = [NSNumber numberWithFloat:[*value floatValue]/255];
        return true;
    } else if ([var isEqualToString:@"$fontDescription.pointSize"]) {
        
        return true;
    }
    
    return false;
    
}


//dictionaries are teh same (same type).. check attributes
//return the diffs through trList dictionary
- (bool) checkAreEqual:(NSDictionary *)prev prevDict:(NSDictionary *)newD attr:(NSDictionary*)currAttr
               outList:(NSMutableDictionary**)trList equal:(BOOL) eq json_info:(NSDictionary *) jsonInfo
{
    if (prev == nil && newD == nil)
        return eq;
    
    //first of all go through each <key, value> pair; see difference -> TODO: eventually use xml2agcDict.. setup needed!!
    //id keys = [prev allKeys];
    NSArray * sortedAllKeys = [prev allKeys];
    sortedAllKeys = [sortedAllKeys sortedArrayUsingComparator:^(id a, id b) {
        return [a compare:b];
    }];
    for (id key in sortedAllKeys) {
        
        //NSLog(@"Checking for %@", key);
        if ([key isEqualToString:@"rawText"])
            tempText = [newD objectForKey:key];
        
        id value = [prev objectForKey:key];
        //NSLog(@"value %@ for %@", value, key);
        //NSLog(@"CurrAttr = %@", currAttr);
        if ([value isKindOfClass:[NSMutableDictionary class]] && [currAttr objectForKey:key]) {
            
            eq = [self checkAreEqual:[prev objectForKey:key] prevDict:[newD objectForKey:key] attr:[currAttr objectForKey:key] outList:trList equal:eq json_info:(NSDictionary *) jsonInfo];
            
        } else if ([value isKindOfClass:[NSMutableArray class]]) {
            id areLines = [[value objectAtIndex:0] objectForKey:@"lines"];
            if (areLines && [*trList objectForKey:@"$fontDescription.pointSize"]) {
                //update width & height for textArea when size changes
                float textSize = [[*trList objectForKey:@"$fontDescription.pointSize"] floatValue];
                NSLog(@"FloatValue = %f", textSize);
                NSFont *font = [NSFont systemFontOfSize:textSize];
                NSLog(@"TempText = %@", tempText);
                CGFloat width = [tempText sizeWithAttributes:@{ NSFontAttributeName:font }].width + EPS; //USING SYSTEM'S Font!!!
                CGFloat height = [tempText sizeWithAttributes:@{ NSFontAttributeName:font }].height;
                
                NSLog(@"Changing Size to %f %f", width , height);
                NSString *widthS = [NSString stringWithFormat:@"$rect.width"];
                NSString *heightS = [NSString stringWithFormat:@"$rect.height"];
                [*trList setObject:[NSString stringWithFormat:@"%f", width] forKey:widthS];
                [*trList setObject:[NSString stringWithFormat:@"%f", height] forKey:heightS];
                
            }
            
            continue;
            
        } else {
            if ([prev objectForKey:key] == nil || [newD objectForKey:key] == nil ) {
                continue;
                
            }
            //NSLog(@"key = %@", key);
            if ([value isKindOfClass:[NSString class]]) {
                //NSLog(@"AKey is here\n");
                if (![[prev objectForKey:key] isEqualToString:[newD objectForKey:key]] &&
                    (![[currAttr objectForKey:key] isEqualToString:@"$rand"] && ![key isEqualToString:@"uid"])) {
                    eq = false;
                    NSNumber *nr = [newD objectForKey:key];
                    NSMutableDictionary * otherUpdates = [[NSMutableDictionary alloc] init];
                    NSLog(@"Bef transform %@ ", nr);
                    
                    [self checkTransformToAbsoluteValue:&nr variable:[currAttr objectForKey:key] scale_dict:jsonInfo other_updates:&otherUpdates];
                    NSLog(@"ZZ transform %@ %@", nr, [currAttr objectForKey:key]);
                    [*trList setObject:nr forKey:[currAttr objectForKey:key]];
                }
                
            } else {
                
                if ([prev objectForKey:key] != [newD objectForKey:key]){
                    NSLog(@"BKey is here %@ %@\n", [prev objectForKey:key] , [newD objectForKey:key]);
                    eq = false;
                    NSNumber *nr = [newD objectForKey:key];
                    NSLog(@"NR = %@ %@ %@ %@", nr, currAttr, key, [currAttr objectForKey:key]);
                    NSMutableDictionary * otherUpdates = [[NSMutableDictionary alloc] init];
                    if ([[currAttr objectForKey:key] isEqualToString:@"$justAValue"]) //drop value;
                        continue;
                    [self checkTransformToAbsoluteValue:&nr variable:[currAttr objectForKey:key] scale_dict:jsonInfo other_updates:&otherUpdates];
                    NSLog(@"To transfom %@ %@", nr, [currAttr objectForKey:key]);
                    [*trList setObject:nr forKey:[currAttr objectForKey:key]];
                    
                }
            }
        }
        
    }
    
    return eq;
}

- (void) updateXMLfile:(NSDictionary *)tags tagNo:(NSNumber *)n offsetScene:(NSNumber **) offset_scene
{
    
    
    
    NSString *pathToTempXml = @"/Users/crogoz/Desktop/XMLParser/myNewFile.xml";
    
    NSFileHandle *outputTempXml = [NSFileHandle fileHandleForWritingAtPath:pathToTempXml];
    if(outputTempXml == nil) {
        [[NSFileManager defaultManager] createFileAtPath:pathToTempXml contents:nil attributes:nil];
        outputTempXml = [NSFileHandle fileHandleForWritingAtPath:pathToTempXml];
    }
    
    NSFileHandle *inputXml = [NSFileHandle fileHandleForReadingAtPath: [self xmlPath]];
    if (inputXml == nil)
        NSLog(@"Failed to open file");
    
    
    if ([tags count] == 0) {
        //just copy from offset_start
        NSLog(@"Here we are\n");
        unsigned long fileSize = [inputXml seekToEndOfFile];
        [inputXml seekToFileOffset:[*offset_scene longValue]];
        
        long sizeToRead = fileSize - [*offset_scene longValue];
        NSData *inputData = [inputXml readDataOfLength:sizeToRead];
        [outputTempXml seekToEndOfFile];
        [outputTempXml writeData:inputData];
        return;
    }
    
    
    NSMutableArray *offset = [offsetXmlFile objectForKey:n];
    long newNextOffset = 0;
    long diffOffset = 0;
    int prevKey = 0;
    unsigned long nextXMlTag = 0;
    // int lastIndex = [[tags objectForKey:[[tags allKeys] lastObject]] intValue];
    NSArray * sortedAllKeys = [tags allKeys];
    sortedAllKeys = [sortedAllKeys sortedArrayUsingComparator:^(id a, id b) {
        return [a compare:b];
    }];
    
    for  (id key in sortedAllKeys) {
        
        // we have the changes that have to be made in the form of a dictioanry
        NSMutableDictionary *toChange = [tags objectForKey:key];
        
        
        //we have the tag that needs changing (for it or some of it's subtags)
        id gotoXml = [offset objectAtIndex:[key intValue] -1];
        if ([key intValue] < [offset count])
            nextXMlTag = [[offset objectAtIndex:[key intValue]] longValue];
        else {
            NSString *sceneEnds = @"</scene>";
            NSData *sceneEnd = [sceneEnds dataUsingEncoding:NSUTF8StringEncoding];
            NSRange range = [xmlData rangeOfData:sceneEnd options:0 range:NSMakeRange([gotoXml intValue], [xmlData length] - [gotoXml intValue])];
            //NSLog (@"FInalScene = %d %lu", [gotoXml intValue], (unsigned long)range.location);
            nextXMlTag = range.location + [sceneEnds length];
            
            
        }
        
        //NSLog(@"Tag is = %@ %lu", gotoXml, nextXMlTag);
        NSMutableDictionary *stringChunks = [[NSMutableDictionary alloc] init];
        NSRange range;
        
        //TODO06.03 changed offset from INT_MAX -1
        //[gotoXml longValue]; // highest subTag --> needed for offset writing
        long minTagOffset = INT_MAX -1;//[gotoXml longValue];
        NSLog(@"keys = %@", [toChange allKeys]);
        for (id key1 in [toChange allKeys]) {
            NSString *tmp = [key1 substringWithRange:NSMakeRange(1, [key1 length] -1)];
            NSArray *subTags = [tmp componentsSeparatedByString:@"."];
            NSString *replacedValue = [toChange objectForKey:key1];
            if ([[toChange objectForKey:key1] isKindOfClass:[NSNumber class]])
                replacedValue= [[toChange objectForKey:key1] stringValue];
            NSLog(@"key1 = %@ where minTagOffset = %ld", key1, minTagOffset);
            
            id key2 = [subTags objectAtIndex:0];
            
            if ([stringChunks objectForKey:key2]) {
                
                NSString *newData = [stringChunks objectForKey:key2];
                NSString *attrString = [NSString stringWithFormat:@" %@=\"", [subTags lastObject]];
                
                unsigned long shiftAttr = [[subTags lastObject] length] + 3;
                NSRange rangeOfString = [newData rangeOfString:attrString];
                if (rangeOfString.location == NSNotFound )
                    NSLog(@"[ERROR] Not found :s");
                NSString *tmpRange = [newData substringFromIndex:rangeOfString.location + shiftAttr];
                NSRange rangeLastString = [tmpRange rangeOfString:@"\""];
                
                if (rangeOfString.location == NSNotFound || rangeLastString.location == NSNotFound)  {
                    
                    NSLog(@"[ERROR] string was not found");
                } else {
                    unsigned long st = (unsigned long)rangeOfString.location + shiftAttr;
                    unsigned long en = (unsigned long)rangeLastString.location;
                    
                    newData = [newData stringByReplacingCharactersInRange:NSMakeRange(st, en) withString:replacedValue];
                    
                    [stringChunks setObject:newData forKey:key2];
                    
                }
                
                continue;
            }
            
            //find subTag's offset
            NSData *find = [[NSString stringWithFormat:@"<%@", key2] dataUsingEncoding:NSUTF8StringEncoding];
            
            range = [xmlData rangeOfData:find options:0 range:NSMakeRange([gotoXml intValue], nextXMlTag - [gotoXml intValue])];
            if (range.location == NSNotFound) {
                //TODO11 create label if iot doesn't exist :D
                NSLog(@"Color can't be here :(");
                continue;
            }
            NSFileHandle *fHandle;
            fHandle = [NSFileHandle fileHandleForReadingAtPath: [self xmlPath]];
            if (fHandle == nil)
                NSLog(@"Failed to open file");
            
            minTagOffset = MIN((unsigned long)range.location, minTagOffset);
            
            unsigned long sizeToRead = nextXMlTag  - (unsigned long)range.location;
            
            [fHandle seekToFileOffset:range.location];
            NSData *databuffer;
            databuffer = [fHandle readDataOfLength: sizeToRead];
            NSString *newData;
            newData = [[NSString alloc] initWithData:databuffer encoding:NSASCIIStringEncoding];
            //TODO string replace with ...
            NSLog(@"DatBuffer = %@", newData);
            NSString *attrString = [NSString stringWithFormat:@" %@=\"", [subTags lastObject]];
            unsigned long shiftAttr = [[subTags lastObject] length] + 3;
            NSRange rangeOfString = [newData rangeOfString:attrString];
            NSString *tmpRange = [newData substringFromIndex:rangeOfString.location + shiftAttr];
            NSRange rangeLastString = [tmpRange rangeOfString:@"\""];
            
            if (rangeOfString.location == NSNotFound || rangeLastString.location == NSNotFound)  {
                
                NSLog(@"[ERROR] string was not found");
            } else {
                unsigned long st = (unsigned long)rangeOfString.location + shiftAttr;
                unsigned long en = (unsigned long)rangeLastString.location;
                newData = [newData stringByReplacingCharactersInRange:NSMakeRange(st, en) withString:replacedValue];
            }
            
            NSLog(@"newData + %@", newData);
            [stringChunks setObject:newData forKey:key2];
            
            [fHandle closeFile];
            
        }
        
        NSNumber *tagOffset = [NSNumber numberWithLong:minTagOffset];
        NSString *cntTag = [self appendModifiedString:stringChunks minTagOffset:&tagOffset];
        
        
        
        
        //TODO update offset & propagate offset
        unsigned long prevOffset = (unsigned long)range.location;
        
        [outputTempXml seekToEndOfFile];
        
        //TODO copy to file + copy intra chunks beteween (key, key +1)
        if (prevKey == 0) {
            //copy all from beginning to the curent offset
            //TODO change for any "n" -> only no 1 artboard works
            [inputXml seekToFileOffset:[*offset_scene longValue]];
            long sizeToRead = minTagOffset - [*offset_scene longValue];
            NSData *inputData = [inputXml readDataOfLength:sizeToRead];
            NSString* newStr = [[NSString alloc] initWithData:inputData encoding:NSUTF8StringEncoding];
            NSString* newStr1 =[[NSString alloc] initWithData:[cntTag dataUsingEncoding:NSUTF8StringEncoding] encoding:NSUTF8StringEncoding];
            NSLog(@"At %@ writing to file %@ %@", n, newStr, newStr1);
            [outputTempXml writeData:inputData];
            [outputTempXml seekToEndOfFile];
            //copy current Tag to outputXMlfile
            [outputTempXml writeData:[cntTag dataUsingEncoding:NSUTF8StringEncoding]];
            long totalSize = [outputTempXml seekToEndOfFile];
            newNextOffset = totalSize;
            
            
        } else if (prevKey == [key intValue] -1) {
            //just copy the string to the file (no other tags are in between)
            long tmpOffset = [*offset_scene longValue] + [gotoXml longValue];
            long latest = [inputXml seekToEndOfFile];
            [inputXml seekToFileOffset:tmpOffset];
            unsigned long sizeToRead = minTagOffset - [gotoXml longValue];
            NSData *inputData = [inputXml readDataOfLength:sizeToRead];
            NSString *dataBuff = [[NSString alloc] initWithData:inputData  encoding:NSUTF8StringEncoding];
            NSLog(@"To insert string betwee = %@ %lu %lu %lu", dataBuff, sizeToRead, tmpOffset, latest);
            [outputTempXml writeData:inputData];
            [outputTempXml seekToEndOfFile];
            [outputTempXml writeData:[cntTag dataUsingEncoding:NSUTF8StringEncoding]];
            long totalSize = [outputTempXml seekToEndOfFile];
            diffOffset = newNextOffset - prevOffset;
            newNextOffset = totalSize;
            
            NSLog(@"NextOffset for %d will be = %lu", [key intValue] + 1, newNextOffset);
            
        } else { //if (prevKey != lastIndex){
            NSLog(@"PrevKey3 = %d", prevKey);
            //copy all tags from the prevKey to this key
            //TODO update each offset in between
            int skippedTagNo = prevKey +1;
            id gotoTag = [offset objectAtIndex:skippedTagNo -1];
            long tmpOffset = [*offset_scene longValue] +[gotoTag longValue];
            [inputXml seekToFileOffset:tmpOffset];
            unsigned long sizeToRead = minTagOffset - [gotoTag longValue];
            NSData *inputData = [inputXml readDataOfLength:sizeToRead];
            
            NSString* newStr1 =[[NSString alloc] initWithData:inputData  encoding:NSUTF8StringEncoding];
            NSLog(@"\n-----------\ndata read = %@", newStr1);
            [outputTempXml writeData:inputData];
            [outputTempXml seekToEndOfFile];
            //copy currentTag to outputXMLfile
            [outputTempXml writeData:[cntTag dataUsingEncoding:NSUTF8StringEncoding]];
            long totalSize = [outputTempXml seekToEndOfFile];
            diffOffset = newNextOffset - [[offset objectAtIndex:prevKey] longValue];
            
            
            int tags = skippedTagNo;
            
            //TODO FIXME
            while (tags <= [key intValue]) {
                
                unsigned long prevTagOffset = [[offset objectAtIndex:tags -1] longValue];
                unsigned long nextOffset = prevTagOffset + diffOffset;
                
                [offset replaceObjectAtIndex:tags -1 withObject:[NSNumber numberWithLong:nextOffset]];
                tags = tags + 1;
                
            }
            newNextOffset = totalSize;
            
        }
        prevKey = [key intValue];
    }
    [outputTempXml closeFile];
    *offset_scene = [NSNumber numberWithLong:nextXMlTag];
}


- (void) monitorXDFile:(NSString*) path
{
    NSLog(@"Offset: %@", offsetXmlFile);
    const char *pathString = [path cStringUsingEncoding:NSASCIIStringEncoding];
    int fildes = open(pathString, O_RDONLY);
    //int counter = 0;
    dispatch_queue_t queue = dispatch_get_global_queue(0, 0);
    __block dispatch_source_t source = dispatch_source_create(DISPATCH_SOURCE_TYPE_VNODE,fildes, DISPATCH_VNODE_DELETE | DISPATCH_VNODE_WRITE | DISPATCH_VNODE_EXTEND | DISPATCH_VNODE_ATTRIB | DISPATCH_VNODE_LINK | DISPATCH_VNODE_RENAME | DISPATCH_VNODE_REVOKE,
                                                              queue);
    dispatch_source_set_event_handler(source, ^
                                      {
                                          unsigned long flags = dispatch_source_get_data(source);
                                          //Do some stuff
                                          
                                          if(flags & DISPATCH_VNODE_DELETE)
                                          {
                                              [self monitorXDFile:path];
                                              
                                          }
                                          else {
                                              
                                              NSLog(@"File has changed!\n");
                                              NSError *error;
                                              NSString *pathToTempXml = @"/Users/crogoz/Desktop/XMLParser/myNewFile.xml";
                                              [[NSFileManager defaultManager] removeItemAtPath:pathToTempXml error:&error];
                                              
                                              //NSString *zipPath = [[NSBundle mainBundle] pathForResource:path ofType:@"xd"];
                                              
                                              //TODO change unzip directory -> maybe temp directory ?
                                              //NSString *destinationPath = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, //NSUserDomainMask, YES) objectAtIndex:0];
                                              NSArray *paths = NSSearchPathForDirectoriesInDomains
                                              (NSDocumentDirectory, NSUserDomainMask, YES);
                                              NSString *documentsDirectory = [paths objectAtIndex:0];
                                              
                                              NSTask *task = [[NSTask alloc] init];
                                              task.launchPath = @"/usr/bin/unzip";
                                              task.arguments = @[path];
                                              task.currentDirectoryPath=documentsDirectory;
                                              
                                              [task launch];
                                              [task waitUntilExit];
                                              
                                              NSFileManager *fileManager = [[ NSFileManager alloc] init];
                                              
                                              NSString *pathFinal = @"/Users/crogoz/Documents/temp-artwork";
                                              NSURL *directoryURLF = [NSURL fileURLWithPath:pathFinal];
                                              
                                              NSString *pathInit = @"/Users/crogoz/Documents/artwork";
                                              NSURL *directoryURLI = [NSURL fileURLWithPath:pathInit];
                                              
                                              NSString *pathToArtboardAgc = @"/Users/crogoz/Documents/resources/graphics/graphicContent.agc";
                                              NSString *jsonString = [[NSString alloc] initWithContentsOfFile:pathToArtboardAgc encoding:NSUTF8StringEncoding error:NULL];
                                              
                                              NSMutableDictionary *jsonArtboards = [NSJSONSerialization JSONObjectWithData:[jsonString dataUsingEncoding:NSUTF8StringEncoding] options:NSJSONReadingMutableContainers error:&error];
                                              jsonArtboards = [jsonArtboards objectForKey:@"artboards"];
                                              
                                              widthAgcArtboard = [[[jsonArtboards objectForKey:@"artboard1"] objectForKey:@"width"] intValue];
                                              heightAgcArtboard = [[[jsonArtboards objectForKey:@"artboard1"]  objectForKey:@"height"] intValue];
                                              
                                              NSArray *keys = [NSArray arrayWithObject:NSURLIsDirectoryKey];
                                              
                                              
                                              
                                              NSDirectoryEnumerator *enumeratorI = [fileManager
                                                                                    enumeratorAtURL:directoryURLI
                                                                                    includingPropertiesForKeys:keys
                                                                                    options:0
                                                                                    errorHandler:^(NSURL *url, NSError *error) {
                                                                                        return YES;
                                                                                    }];
                                              
                                              NSDirectoryEnumerator *enumeratorF = [fileManager
                                                                                    enumeratorAtURL:directoryURLF
                                                                                    includingPropertiesForKeys:keys
                                                                                    options:0
                                                                                    errorHandler:^(NSURL *url, NSError *error) {
                                                                                        return YES;
                                                                                    }];
                                              
                                              NSMutableArray *filesInit = [[NSMutableArray alloc] init];
                                              
                                              for (NSURL *urlI in enumeratorI) {
                                                  
                                                  NSError *error;
                                                  NSNumber *isDirectory = nil;
                                                  if (! [urlI getResourceValue:&isDirectory forKey:NSURLIsDirectoryKey error:&error]) {
                                                      // handle error
                                                  }
                                                  else if (! [isDirectory boolValue]) {
                                                      
                                                      if ([[[[urlI path] componentsSeparatedByString:@"/"] lastObject] isEqualToString:@"graphicContent.agc"]) {
                                                          NSLog(@"URL = %@", [urlI path]);
                                                          [filesInit addObject:[urlI path]];
                                                          
                                                      }
                                                  }
                                                  
                                              }
                                              NSLog(@"Files = %@", filesInit);
                                              
                                              int i = 0;
                                              NSNumber *offset_scene = [NSNumber numberWithInt:0];
                                              
                                              
                                              for (NSURL *urlF in enumeratorF) {
                                                  NSError *error;
                                                  NSNumber *isDirectory = nil;
                                                  if (! [urlF getResourceValue:&isDirectory forKey:NSURLIsDirectoryKey error:&error]) {
                                                      // handle error
                                                  }
                                                  else if (! [isDirectory boolValue] &&
                                                           ![[urlF path] isEqualToString:@"/Users/crogoz/Documents/temp-artwork/.DS_Store"]) {
                                                      //[filesInit addObject:[urlF path]];
                                                      //TODO dictionaries to compare
                                                      NSLog(@"Files = %@ %@", filesInit, urlF);
                                                      NSLog(@"Check %@ with %@", [urlF path], [filesInit objectAtIndex:i]);
                                                      
                                                      NSString *filePath = [urlF path];
                                                      NSString *jsonString = [[NSString alloc] initWithContentsOfFile:filePath encoding:NSUTF8StringEncoding error:NULL];
                                                      
                                                      NSError *jsonError;
                                                      
                                                      NSMutableDictionary *jsonDict1 = [NSJSONSerialization JSONObjectWithData:[jsonString dataUsingEncoding:NSUTF8StringEncoding] options:NSJSONReadingMutableContainers error:&jsonError];
                                                      
                                                      filePath = [filesInit objectAtIndex:i];
                                                      jsonString = [[NSString alloc] initWithContentsOfFile:filePath encoding:NSUTF8StringEncoding error:NULL];
                                                      
                                                      NSMutableDictionary *jsonDict2 = [NSJSONSerialization JSONObjectWithData:[jsonString dataUsingEncoding:NSUTF8StringEncoding] options:NSJSONReadingMutableContainers error:&jsonError];
                                                      
                                                      NSMutableSet *keysInA = [NSMutableSet setWithArray:[jsonDict1 allKeys]];
                                                      NSSet *keysInB = [NSSet setWithArray:[jsonDict2 allKeys]];
                                                      [keysInA minusSet:keysInB];
                                                      
                                                      
                                                      
                                                      //TODO eventual in xml2agc
                                                      NSArray *first = [[[[jsonDict1 objectForKey:@"children"] objectAtIndex:0] objectForKey:@"artboard"] objectForKey:@"children"];
                                                      NSArray *second = [[[[jsonDict2 objectForKey:@"children"] objectAtIndex:0] objectForKey:@"artboard"] objectForKey:@"children"];
                                                      
                                                      
                                                      NSString *artboardNoInfo = [NSString stringWithFormat:@"artboard%d", i +1];
                                                      
                                                      NSMutableDictionary * offsetGroupDict = [[NSMutableDictionary alloc] init];
                                                      offsetGroupDict[@"tx"] = [NSNumber numberWithInt: 0];
                                                      offsetGroupDict[@"ty"] = [NSNumber numberWithInt: 0];
                                                      NSMutableDictionary* tagExport = [self compare2Artboards:first dict2:second artboard_info:[jsonArtboards objectForKey:artboardNoInfo] offsetGroup:offsetGroupDict numberGroup:[NSNumber numberWithInt:0]];
                                                      NSLog(@"To export = %@ %d", tagExport, i);
                                                      
                                                      //TODO export to XML file: For now: Use myXMLFileScenes.xml !!!
                                                      
                                                      [self updateXMLfile:tagExport tagNo:[NSNumber numberWithInt:++i] offsetScene:&offset_scene];
                                                      
                                                      NSLog(@"Update %d is done", i);
                                                      //TODO: only for same objects-> different attributes
                                                      //TODO: objects are added
                                                      //TODO objects are deleted & added
                                                      
                                                  }
                                                  
                                              }
                                              //add footer for xml file
                                              [self updateXMLfile:[[NSMutableDictionary alloc] init] tagNo:0 offsetScene:&offset_scene];
                                              
                                              //NSLog(@"Offsets are = %@", )
                                              NSLog(@"Offset: %@", offsetXmlFile);
                                          }
                                      });
    
    dispatch_source_set_cancel_handler(source, ^(void)
                                       {
                                           close(fildes);
                                       });
    dispatch_resume(source);
    
}

+ (NSDictionary *)dictionaryForXMLData:(NSData *)data resources:(NSString*)resourcesDir xdPath:(NSString*)xdPath outFile:(NSString *)out_file error:(NSError **)error
{
    XMLReader *reader = [[XMLReader alloc] initWithError:error];
    [reader setResourcesPath:resourcesDir];
    [reader setXdPath:xdPath];
    [reader setXmlPath:out_file];
    
    NSMutableDictionary *rootDictionary = [[reader objectWithData:data] mutableCopy];
    
    NSString *finalArtboardName = [NSString stringWithFormat:ARTBOARDXML];
    [reader writeToFile:rootDictionary file:finalArtboardName];
    
    [reader splitArtboards:rootDictionary];
    
    
    [reader monitorXDFile:xdPath];
    
    
    return rootDictionary;
}

- (void) writeToFile:(NSDictionary*)xmlDictionary file:(NSString*) file {
    
    NSError *error;
    NSData *jsonData = [NSJSONSerialization dataWithJSONObject:xmlDictionary
                                                       options:NSJSONWritingPrettyPrinted // Pass 0 if you don't care about the readability of the generated string
                                                         error:&error];
    
    if (! jsonData) {
        NSLog(@"Got an error: %@", error);
    } else {
        NSString *jsonString = [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
        
        NSArray *paths = NSSearchPathForDirectoriesInDomains
        (NSDocumentDirectory, NSUserDomainMask, YES);
        NSString *documentsDirectory = [paths objectAtIndex:0];
        NSString *outFile = [NSString stringWithFormat:@"%@/%@", documentsDirectory, file];
        NSLog(@"Writing to file %@", outFile);
        [[NSFileManager defaultManager] createFileAtPath:outFile contents:nil attributes:nil];
        [jsonString writeToFile:outFile atomically:YES encoding:NSUTF8StringEncoding error:nil];
        
    }
}

- (NSMutableArray *)splitArtboards:(NSDictionary *)dictionary {
    NSMutableArray *rootArray = [[NSMutableArray alloc] init];
    
    NSMutableDictionary *artboardsD = [dictionary objectForKey:@"artboards"];
    int nr = 1;
    for (id key in [artboardsD allKeys]) {
        NSMutableDictionary *tempArray = [NSKeyedUnarchiver unarchiveObjectWithData:[NSKeyedArchiver archivedDataWithRootObject: dictionary]];
        id artboardNo = [artboardsD objectForKey:key];
        [tempArray  setValue:[[NSMutableDictionary alloc] init] forKey:@"artboards"];
        [[tempArray objectForKey:@"artboards"]  setValue:artboardNo forKey:key];
        
        id children =  [[dictionary objectForKey:@"children"] objectAtIndex:(nr -1)];
        
        [tempArray setObject:[[NSMutableArray alloc] init] forKey:@"children"];
        [[tempArray objectForKey:@"children"] addObject:children];
        
        NSString *artboardName = [NSString stringWithFormat:@"artboard-artboard%d.agc", nr];
        [self writeToFile:tempArray file:artboardName];
        nr++;
    }
    
    
    
    return rootArray;
    
}

#pragma mark -
#pragma mark Parsing


- (id)initWithError:(NSError **)error
{
    return self;
}

- (void)dealloc
{
    
}

- (NSMutableDictionary *)objectWithData:(NSData *)data
{
    
    dictionaryStack = [[NSMutableArray alloc] init];
    textInProgress = [[NSMutableString alloc] init];
    inheritanceStack = [[NSMutableArray alloc] init];
    attributes = [[NSMutableDictionary alloc] init];
    toInsertObjects = [[NSMutableArray alloc] init];
    //artboards = [[NSMutableArray alloc] init];
    exportAgc = [[NSMutableDictionary alloc] init];
    offsetXmlFile = [[NSMutableDictionary alloc] init];
    objectOffset = [[NSMutableDictionary alloc] init];
    //exportScaleStack = [[NSMutableArray alloc] init];
    
    sceneNo = 0;
    
    xmlData = [data mutableCopy];
    xmlOffset = 0;
    
    counterArtboards = 1;
    //TODO eventually read from file (XML ??? )
    insertedRoot = false;
    
    xml2agcDictionary = [[NSMutableDictionary alloc] init];
    xml2agcDictionary[@"scenes"] = @"children";
    xml2agcDictionary[@"scene"] = @"artboard2";
    xml2agcDictionary[@"viewController"] = @"artboard";
    xml2agcDictionary[@"imageView"] = @"imageView";
    xml2agcDictionary[@"view"] = @"children";
    xml2agcDictionary[@"textField"] =@"textField";
    xml2agcDictionary[@"label"] = @"textField";
    xml2agcDictionary[@"switch"] = @"Button";
    
    xml2agcDictionary[@"children"] = @"list";
    xml2agcDictionary[@"children1"] = @"list";
    xml2agcDictionary[@"paragraphs"] = @"list";
    
    //for type = "shape"
    exportAgc[@"shape"] = [[NSMutableDictionary alloc] init];
    
    // an agc is of type shape if <=> style fill == solid
    
    //Rules needed to be achieved
    exportAgc[@"shape"][@"path"] = [[NSMutableArray alloc] init ];
    [exportAgc[@"shape"][@"path"] addObject:@"style.fill.type.solid"];
    [exportAgc[@"shape"][@"path"] addObject:@"shape.type.path"];
    
    exportAgc[@"shape"][@"rectangle"] = [[NSMutableArray alloc] init];
    [exportAgc[@"shape"][@"rectangle"] addObject:@"style.fill.type.solid" ];
    [exportAgc[@"shape"][@"rectangle"] addObject:@"shape.type.rect"];
    
    
    //an agc is of type imageView if <=> style fill == pattern
    exportAgc[@"shape"][@"imageView"] = @"style.fill.type.pattern";
    exportAgc[@"group"] = [[NSArray alloc] init];
    
    //for type = "text"
    exportAgc[@"text"] = @"textField";
    
    xml2agcDictionary[@"textField."][@"name"] = @"text";
    
    
    //inverted index for bottom-up inheritance
    xml2agcDictionary[@"imageView."] = @"style.fill.pattern.href";
    xml2agcDictionary[@"rect."] = [[NSMutableDictionary alloc] init];
    xml2agcDictionary[@"rect."][@"x"] = @"textField.transform.tx"; //TODO Dictionary based on type (textField only) -> make dictionary of {textfield: transform.x; label: ....x}
    xml2agcDictionary[@"rect."][@"y"] = @"textField.transform.ty";
    
    //TODO1 eventually transfer to xml2agcDictionary [@"rect."] !!!
    xml2agcDictionary[@"switch."] = [[NSMutableDictionary alloc] init];
    xml2agcDictionary[@"switch."][@"rect"] = [[NSMutableDictionary alloc] init];
    xml2agcDictionary[@"switch."][@"rect"][@"x"] = @"switch.transform.tx";
    xml2agcDictionary[@"switch."][@"rect"][@"y"] = @"switch.transform.ty";
    
    
    xml2agcDictionary[@"switch."][@"color"] = [[NSMutableDictionary alloc] init];
    xml2agcDictionary[@"switch."][@"color"][@"onTintColor"] = [[NSMutableDictionary alloc] init];
    
    xml2agcDictionary[@"rect."][@"width"] = [[NSMutableDictionary alloc] init];
    xml2agcDictionary[@"rect."][@"width"][@"rect"] = @"rect.shape.width"; //TODO Dictionary based on type (textField only) -> make dictionary of {textfield: transform.x; label: ....x}
    xml2agcDictionary[@"rect."][@"width"][@"text"] = @"textField.shape.width";
    xml2agcDictionary[@"rect."][@"width"][@"shape"] = @"imageView.style.fill.pattern.width";
    
    xml2agcDictionary[@"rect."][@"height"] = [[NSMutableDictionary alloc] init];
    xml2agcDictionary[@"rect."][@"height"][@"text"]= @"textField.shape.height";
    xml2agcDictionary[@"rect."][@"height"][@"rect"]= @"rect.shape.height";
    xml2agcDictionary[@"rect."][@"height"][@"shape"] = @"imageView.style.fill.pattern.height";
    
    xml2agcDictionary[@"color."] = [[NSMutableDictionary alloc] init];
    xml2agcDictionary[@"color."][@"red"] = @"textField.style.fill.color.value.r";
    xml2agcDictionary[@"color."][@"green"] = @"textField.style.fill.color.value.g";
    xml2agcDictionary[@"color."][@"blue"] = @"textField.style.fill.color.value.b";
    xml2agcDictionary[@"color."][@"alpha"] = @"textField.style.fill.color.alpha";
    xml2agcDictionary[@"fontDescription."] = [[NSMutableDictionary alloc] init];
    xml2agcDictionary[@"fontDescription."][@"pointSize"] = @"textField.style.font.size";
    xml2agcDictionary[@"length."] = @"textField.text.paragraphs.lines.to";
    //mapping between attr from parent tag -> attr to siblings tag (top -> down ) eg name and rawtext from textField
    // used for didEndElement
    xml2agcDictionary[@"#textField"] = [[NSMutableDictionary alloc] init];
    xml2agcDictionary[@"#textField"][@"textField.text.rawText"] = @"#text";
    
    //default values template!!!
    defaultValues = [[NSMutableDictionary alloc] init];
    defaultValues[@"textField"] = [[NSMutableDictionary alloc] init];
    defaultValues[@"textField"][@"textField.style.fill.color.value.r"] = [NSNumber numberWithInt:0];
    defaultValues[@"textField"][@"textField.style.fill.color.value.g"] = [NSNumber numberWithInt:0];
    defaultValues[@"textField"][@"textField.style.fill.color.value.b"] = [NSNumber numberWithInt:0];
    defaultValues[@"textField"][@"textField.style.fill.color.alpha"] = [NSNumber numberWithInt:1];
    
    // custom templates for agc representation
    attributes = [[NSMutableDictionary alloc] init];
    attributes[@"artboard"] = [[NSMutableDictionary alloc] init]; //TODO style -> background color from color tag (inherits view)
    attributes[@"artboard"][@"ref"] = @"artboard1";
    
    attributes[@"textField"] = [[NSMutableDictionary alloc] init];
    attributes[@"textField"][@"type"] = @"text";
    attributes[@"textField"][@"name"] = @"$text"; //TODO update with ID!!!
    attributes[@"textField"][@"transform"] = [[NSMutableDictionary alloc] init];
    attributes[@"textField"][@"transform"][@"a"] = [NSNumber numberWithInt:1];
    attributes[@"textField"][@"transform"][@"b"] = [NSNumber numberWithInt:0];
    attributes[@"textField"][@"transform"][@"c"] = [NSNumber numberWithInt:0];
    attributes[@"textField"][@"transform"][@"d"] = [NSNumber numberWithInt:1];
    attributes[@"textField"][@"transform"][@"tx"] = @"$rect.x"; // TODO transform based of outer shape(rectangle) -> look for attributes -> textAlignment in testField -> center/ left/right
    attributes[@"textField"][@"transform"][@"ty"] = @"$rect.y";
    attributes[@"textField"][@"style"] = [[NSMutableDictionary alloc] init];
    attributes[@"textField"][@"style"][@"fill"] = [[NSMutableDictionary alloc] init];
    attributes[@"textField"][@"style"][@"fill"][@"type"] = @"solid"; // ?? fontDescription pointsize ???
    attributes[@"textField"][@"style"][@"fill"][@"color"] = [[NSMutableDictionary alloc] init];
    attributes[@"textField"][@"style"][@"fill"][@"color"][@"mode"] = @"RGB";
    attributes[@"textField"][@"style"][@"fill"][@"color"][@"value"] = [[NSMutableDictionary alloc] init];
    attributes[@"textField"][@"style"][@"fill"][@"color"][@"value"][@"r"] = @"$color.red";
    attributes[@"textField"][@"style"][@"fill"][@"color"][@"value"][@"g"] = @"$color.green";
    attributes[@"textField"][@"style"][@"fill"][@"color"][@"value"][@"b"] = @"$color.blue";
    attributes[@"textField"][@"style"][@"fill"][@"color"][@"alpha"] = @"$color.alpha";
    attributes[@"textField"][@"style"][@"font"] = [[NSMutableDictionary alloc] init];
    attributes[@"textField"][@"style"][@"font"][@"postscriptName"] = @"HelveticaNeue"; //TODO hardcodare => default properties
    attributes[@"textField"][@"style"][@"font"][@"family"] = @"Helvetica Neue";
    attributes[@"textField"][@"style"][@"font"][@"style"] = @"Regular";
    attributes[@"textField"][@"style"][@"font"][@"size"] = @"$fontDescription.pointSize";
    attributes[@"textField"][@"text"] = [[NSMutableDictionary alloc] init];
    attributes[@"textField"][@"text"][@"rawText"] = @"#text";
    
    attributes[@"rectangle"] = [[NSMutableDictionary alloc] init];
    attributes[@"rectangle"][@"type"] = @"shape";
    attributes[@"rectangle"][@"transform"] = [[NSMutableDictionary alloc] init];
    attributes[@"rectangle"][@"transform"][@"a"] = [NSNumber numberWithInt:1];
    attributes[@"rectangle"][@"transform"][@"b"] = [NSNumber numberWithInt:0];
    attributes[@"rectangle"][@"transform"][@"c"] = [NSNumber numberWithInt:0];
    attributes[@"rectangle"][@"transform"][@"d"] = [NSNumber numberWithInt:1];
    attributes[@"rectangle"][@"transform"][@"tx"] = @"$rect.x";
    attributes[@"rectangle"][@"transform"][@"ty"] = @"$rect.y";
    attributes[@"rectangle"][@"style"] = [[NSMutableDictionary alloc] init];
    attributes[@"rectangle"][@"style"][@"fill"] = [[NSMutableDictionary alloc] init];
    attributes[@"rectangle"][@"style"][@"fill"][@"type"] = @"solid"; // ?? fontDescription pointsize ???
    attributes[@"rectangle"][@"style"][@"fill"][@"color"] = [[NSMutableDictionary alloc] init];
    attributes[@"rectangle"][@"style"][@"fill"][@"color"][@"mode"] = @"RGB";
    attributes[@"rectangle"][@"style"][@"fill"][@"color"][@"value"] = [[NSMutableDictionary alloc] init];
    attributes[@"rectangle"][@"style"][@"fill"][@"color"][@"value"][@"r"] = @"$color.red";
    attributes[@"rectangle"][@"style"][@"fill"][@"color"][@"value"][@"g"] = @"$color.green";
    attributes[@"rectangle"][@"style"][@"fill"][@"color"][@"value"][@"b"] = @"$color.blue";
    attributes[@"rectangle"][@"shape"] = [[NSMutableDictionary alloc] init];
    attributes[@"rectangle"][@"shape"][@"type"] = @"rect";
    attributes[@"rectangle"][@"shape"][@"x"] = [NSNumber numberWithInt:0];
    attributes[@"rectangle"][@"shape"][@"y"] = [NSNumber numberWithInt:0];
    attributes[@"rectangle"][@"shape"][@"width"] = @"$rect.width";
    attributes[@"rectangle"][@"shape"][@"height"] = @"$rect.height";
    
    attributes[@"path"] = [[NSMutableDictionary alloc] init];
    attributes[@"path"][@"type"] = @"shape";
    attributes[@"path"][@"transform"] = [[NSMutableDictionary alloc] init];
    attributes[@"path"][@"transform"][@"a"] = [NSNumber numberWithInt:1];
    attributes[@"path"][@"transform"][@"b"] = [NSNumber numberWithInt:0];
    attributes[@"path"][@"transform"][@"c"] = [NSNumber numberWithInt:0];
    attributes[@"path"][@"transform"][@"d"] = [NSNumber numberWithInt:1];
    attributes[@"path"][@"transform"][@"tx"] = @"$rect.x";
    attributes[@"path"][@"transform"][@"ty"] = @"$rect.y";
    attributes[@"path"][@"style"] = [[NSMutableDictionary alloc] init];
    attributes[@"path"][@"style"][@"fill"] = [[NSMutableDictionary alloc] init];
    attributes[@"path"][@"style"][@"fill"][@"type"] = @"solid"; // ?? fontDescription pointsize ???
    attributes[@"path"][@"style"][@"fill"][@"color"] = [[NSMutableDictionary alloc] init];
    attributes[@"path"][@"style"][@"fill"][@"color"][@"mode"] = @"RGB";
    attributes[@"path"][@"style"][@"fill"][@"color"][@"value"] = [[NSMutableDictionary alloc] init];
    attributes[@"path"][@"style"][@"fill"][@"color"][@"value"][@"r"] = @"$color.red";
    attributes[@"path"][@"style"][@"fill"][@"color"][@"value"][@"g"] = @"$color.green";
    attributes[@"path"][@"style"][@"fill"][@"color"][@"value"][@"b"] = @"$color.blue";
    attributes[@"path"][@"shape"] = [[NSMutableDictionary alloc] init];
    attributes[@"path"][@"shape"][@"type"] = @"path";
    attributes[@"path"][@"shape"][@"path"] = @"";
    attributes[@"path"][@"style"][@"stroke"] = [[NSMutableDictionary alloc] init];
    attributes[@"path"][@"style"][@"stroke"][@"color"] = [[NSMutableDictionary alloc] init];
    attributes[@"path"][@"style"][@"stroke"][@"color"][@"mode"] = @"RGB";
    attributes[@"path"][@"style"][@"stroke"][@"color"][@"value"] = [[NSMutableDictionary alloc] init];
    attributes[@"path"][@"style"][@"stroke"][@"color"][@"value"][@"r"] = @"$color.red";
    attributes[@"path"][@"style"][@"stroke"][@"color"][@"value"][@"g"] = @"$color.green";
    attributes[@"path"][@"style"][@"stroke"][@"color"][@"value"][@"b"] = @"$color.blue";
    attributes[@"path"][@"style"][@"stroke"][@"type"] = @"solid";
    attributes[@"path"][@"style"][@"stroke"][@"width"] = @"$justAValue";
    attributes[@"path"][@"visualBounds"] = [[NSMutableDictionary alloc] init];
    attributes[@"path"][@"visualBounds"][@"x"] = @"$rect.x";
    attributes[@"path"][@"visualBounds"][@"y"] = @"$rect.y";
    attributes[@"path"][@"visualBounds"][@"width"] = @"$rect.width";
    attributes[@"path"][@"visualBounds"][@"height"] = @"$rect.height";
    
    attributes[@"imageView"] = [[NSMutableDictionary alloc] init];
    attributes[@"imageView"][@"type"] = @"shape";
    attributes[@"imageView"][@"transform"] = [NSKeyedUnarchiver unarchiveObjectWithData:[NSKeyedArchiver archivedDataWithRootObject: attributes[@"rectangle"][@"transform"]]];
    attributes[@"imageView"][@"style"] = [[NSMutableDictionary alloc] init];
    attributes[@"imageView"][@"style"][@"fill"] = [[NSMutableDictionary alloc] init];
    attributes[@"imageView"][@"style"][@"fill"][@"type"] = @"pattern";
    attributes[@"imageView"][@"style"][@"fill"][@"pattern"] = [[NSMutableDictionary alloc] init];
    attributes[@"imageView"][@"style"][@"fill"][@"pattern"][@"width"] = @"$justAValue";
    attributes[@"imageView"][@"style"][@"fill"][@"pattern"][@"height"] = @"$justAValue";
    attributes[@"imageView"][@"style"][@"fill"][@"pattern"][@"href"] = @"$image"; // TODO add resourcesPath
    attributes[@"imageView"][@"style"][@"fill"][@"pattern"][@"meta"] = [[NSMutableDictionary alloc] init];
    attributes[@"imageView"][@"style"][@"fill"][@"pattern"][@"meta"][@"ux"] = [[NSMutableDictionary alloc] init];
    attributes[@"imageView"][@"style"][@"fill"][@"pattern"][@"meta"][@"ux"][@"uid"] = @"$rand";
    
    attributes[@"imageView"][@"shape"] = [[NSMutableDictionary alloc] init];
    attributes[@"imageView"][@"shape"][@"type"] = @"rect";
    attributes[@"imageView"][@"shape"][@"x"] = [NSNumber numberWithInt:0];
    attributes[@"imageView"][@"shape"][@"y"] = [NSNumber numberWithInt:0];
    attributes[@"imageView"][@"shape"][@"width"] = @"$rect.width";
    attributes[@"imageView"][@"shape"][@"height"] = @"$rect.height";
    
    attributes[@"textField"][@"text"][@"frame"] = [[NSMutableDictionary alloc] init];
    attributes[@"textField"][@"text"][@"frame"][@"type"] = @"positioned";
    attributes[@"textField"][@"text"][@"paragraphs"] = [[NSMutableArray alloc] init];
    
    attributes[@"backgroundColor"] = [[NSMutableDictionary alloc] init];
    attributes[@"backgroundColor"][@"style"] = [[NSMutableDictionary alloc] init];
    attributes[@"backgroundColor"][@"style"][@"fill"] = [[NSMutableDictionary alloc] init];
    attributes[@"backgroundColor"][@"style"][@"fill"][@"type"] = @"solid"; // ?? fontDescription pointsize ???
    attributes[@"backgroundColor"][@"style"][@"fill"][@"color"] = [[NSMutableDictionary alloc] init];
    attributes[@"backgroundColor"][@"style"][@"fill"][@"color"][@"mode"] = @"RGB";
    attributes[@"backgroundColor"][@"style"][@"fill"][@"color"][@"value"] = [[NSMutableDictionary alloc] init];
    attributes[@"backgroundColor"][@"style"][@"fill"][@"color"][@"value"][@"r"] = @"$color.red";
    attributes[@"backgroundColor"][@"style"][@"fill"][@"color"][@"value"][@"g"] = @"$color.green";
    attributes[@"backgroundColor"][@"style"][@"fill"][@"color"][@"value"][@"b"] = @"$color.blue";
    
    attributes[@"meta"] = [[NSMutableDictionary alloc] init];
    attributes[@"meta"][@"ux"] = [[NSMutableDictionary alloc] init];
    attributes[@"meta"][@"ux"][@"groupItems"] =  [NSNumber numberWithBool:false];
    
    attributes[@"viewSource"] = [[NSMutableDictionary alloc] init];
    attributes[@"viewSource"][@"x"] = [NSNumber numberWithInt:0];
    attributes[@"viewSource"][@"y"] = [NSNumber numberWithInt:0];
    attributes[@"viewSource"][@"width"] = 0;
    attributes[@"viewSource"][@"height"] = [NSNumber numberWithInt:667]; //TODO change for any Artboard type -> for now Iphone 6
    
    attributes[@"resources"] = [[NSMutableDictionary alloc] init];
    attributes[@"resources"][@"gradients"] = [[NSMutableDictionary alloc] init];
    attributes[@"resources"][@"clipPaths"] = [[NSMutableDictionary alloc] init];
    
    attributes[@"frame"] = [[NSMutableDictionary alloc] init];
    
    objectOffset[@"<imageView"] = [NSNumber numberWithInt: 1];
    objectOffset[@"<label"] = [NSNumber numberWithInt: 1];
    objectOffset[@"<textField"] = [NSNumber numberWithInt: 1];
    objectOffset[@"<switch"] = [NSNumber numberWithInt: 1];
    
    NSMutableDictionary *lines = [[NSMutableDictionary alloc] init];
    NSMutableArray *line = [[NSMutableArray alloc] init];
    NSMutableDictionary *dict = [[NSMutableDictionary alloc] init];
    dict[@"x"] = [NSNumber numberWithInt:0];
    dict[@"y"] = [NSNumber numberWithInt:0];
    dict[@"from"] = [NSNumber numberWithInt:0];
    dict[@"to"] = [NSNumber numberWithInt:11];
    NSMutableArray *temp = [[NSMutableArray alloc]init];
    [temp addObject:dict];
    [line addObject:temp];
    [lines setObject:line forKey:@"lines"];
    
    attributes[@"textField"][@"text"][@"paragraphs"] = [[NSMutableArray alloc] init];
    [attributes[@"textField"][@"text"][@"paragraphs"] addObject: lines];
    
    
    [dictionaryStack addObject:[NSMutableDictionary dictionary]];
    
    // Parse the XML
    NSXMLParser *parser = [[NSXMLParser alloc] initWithData:data];
    //parser.delegate = self;
    [parser setDelegate:self];
    BOOL success = [parser parse];
    
    // Return the stack's root dictionary on success
    if (success)
    {
        
        id type = [dictionaryStack objectAtIndex:0];
        [type  setObject:[[NSMutableDictionary alloc] init] forKey:@"artboards"];
        //TODO5.03 added here these 3 -> check if export still works
        [type  setObject:[attributes objectForKey:@"viewSource"] forKey:@"viewSource"];
        [type  setObject:[attributes objectForKey:@"meta"] forKey:@"meta"];
        [type  setObject:[attributes objectForKey:@"resources"] forKey:@"resources"];
        id sources = [type objectForKey:@"viewSource"];
        //id viewSource =
        type = [type objectForKey:@"artboards"];
        NSLog(@"Success = %d", counterArtboards);
        int width = 375;
        int height = 667;
        //int offsetX = 400;
        int x = 0;
        
        for (int i = 1; i< counterArtboards; i++){
            NSMutableString *artboardNo = [NSMutableString stringWithFormat:@"artboard%d", i];
            NSMutableString *iphoneNo = [NSMutableString stringWithFormat:@"iPhone 6 – %d", i];
            [type  setObject:[[NSMutableDictionary alloc] init] forKey:artboardNo];
            [[type objectForKey:artboardNo] setObject:[NSNumber numberWithInt: width] forKey:@"width"];
            [[type objectForKey:artboardNo] setObject:[NSNumber numberWithInt: height] forKey:@"height"];
            [[type objectForKey:artboardNo] setObject:[NSNumber numberWithInt: x] forKey:@"x"];
            [[type objectForKey:artboardNo] setObject:[NSNumber numberWithInt: 0] forKey:@"y"];
            [[type objectForKey:artboardNo] setObject:iphoneNo forKey:@"name"];
            x = x + OFFSETBOARD;
        }
        
        //TODO add viewSource
        
        [sources setObject:[NSNumber numberWithInt:x] forKey:@"width"];
        NSMutableDictionary *resultDict = [dictionaryStack objectAtIndex:0];
        return resultDict;
    }
    
    return nil;
}

// functions that scales & updates x based on artboards and import
- (void) scaleAttrDict:(NSMutableDictionary **) attrScaleDict attribute:(NSString *)elementName{
    //don't bother for tags != <rect>
    if (![elementName isEqualToString:@"rect"])
        return;
    
    if ([[inheritanceStack lastObject] isEqualToString:@"children"]) {
        // axiom: all artboards must have the same size in a single app
        widthXMLArtboard = [[*attrScaleDict objectForKey:@"width"] intValue];
        heightXMLArtboard = [[*attrScaleDict objectForKey:@"height"] intValue];
        return;
        
    }
    int x = [[*attrScaleDict objectForKey:@"x"] intValue];
    int y = [[*attrScaleDict objectForKey:@"y"]intValue];
    int width = [[*attrScaleDict objectForKey:@"width"] intValue];
    int height = [[*attrScaleDict objectForKey:@"height"]intValue];
    
    float xScaleFactor = (float)WIDTHIPH6/widthXMLArtboard;
    float yScaleFactor = (float)HEIGHTIPH6/heightXMLArtboard;
    NSLog(@"x = %d ;y  = %d ;width = %d; height = %d", x, y, width, height);
    NSArray *arrayWithSize = [NSArray arrayWithObjects:@"x", @"width", @"y", @"height", nil];
    for (id value in arrayWithSize) {
        float scaledValue = [[*attrScaleDict objectForKey:value] floatValue];
        if ([value isEqualToString:@"x"] ) {
            NSLog(@"Scena este = %d %d", sceneNo, (sceneNo -1) * OFFSETBOARD);
            scaledValue = scaledValue * xScaleFactor+ (sceneNo -1) * OFFSETBOARD;
        }
        else if ([value isEqualToString:@"width"])
            scaledValue = scaledValue * xScaleFactor;
        else
            scaledValue = scaledValue * yScaleFactor;
    
        NSLog(@"Update %@ with %f", value, scaledValue);
        [*attrScaleDict setValue:[NSNumber numberWithFloat:scaledValue] forKey:value];
    }
}

#pragma mark -
#pragma mark NSXMLParserDelegate methods

- (void)parser:(NSXMLParser *)parser didStartElement:(NSString *)elementName namespaceURI:(NSString *)namespaceURI qualifiedName:(NSString *)qName attributes:(NSMutableDictionary *)attributeDict
{
    attributeDict = [attributeDict mutableCopy];
    NSString *tagName = [NSString stringWithFormat:@"<%@", elementName];
    
    //updates width/height/x/y
    if (objectOffset[tagName] != nil){
        
        NSData *find = [tagName dataUsingEncoding:NSUTF8StringEncoding];
        unsigned long start = xmlOffset + 1;
        unsigned long end = [xmlData length];
        
        NSRange range = [xmlData rangeOfData:find options:0 range:NSMakeRange(start, end -start)];
        //NSLog(@"For = %@ %d %d", elementName, range.location, range.length);
        NSMutableArray *arr = [offsetXmlFile objectForKey:[NSNumber numberWithInt:sceneNo]];
        [arr addObject:[NSNumber numberWithLong: range.location]];
        xmlOffset = (unsigned long)range.location;
        //NSLog(@"Start = %d %d", xmlOffset, start);
        
    }
    
    if ([elementName isEqualToString:@"scene"]) {
        sceneNo++;
        [offsetXmlFile setObject: [[NSMutableArray alloc] init] forKey:[NSNumber numberWithInt:sceneNo]];
        
    }
    
    [self scaleAttrDict:&attributeDict attribute:elementName];
    
    // Get the dictionary for the current level in the stack
    NSMutableDictionary *parentDict = [dictionaryStack lastObject];
    //NSString *nameInit = elementName;
    
    if ([elementName isEqualToString:@"switch"]){
        
        NSString *buttonPath = [[NSBundle mainBundle] pathForResource:xml2agcDictionary[elementName] ofType:@"agc"];
        NSError * error=nil;;
        
        NSString *jsonString = [NSString stringWithContentsOfFile:buttonPath encoding:NSUTF8StringEncoding error:&error];
        NSData * jsonData = [jsonString dataUsingEncoding:NSUTF8StringEncoding];
        NSMutableDictionary * parsedData = [NSJSONSerialization JSONObjectWithData:jsonData options:NSJSONReadingMutableContainers error:&error];
        
        //NSLog(@"Button parent = %@", parentDict);
        [parentDict[@"children"] addObject:parsedData];
        [inheritanceStack addObject:@"switch"];
        
        return;
    }
    
    // Create the child dictionary for the new element, and initilaize it with the attributes
    NSMutableDictionary *childDict = [NSMutableDictionary dictionary];
    
    
    NSMutableDictionary* tempDict = [[NSMutableDictionary alloc] init];
    tempDict[@"href"] = @"/resources/graphics/graphicContent.agc";
    
    if (![xml2agcDictionary objectForKey:elementName]) {
        
        //check whether the attr are needed
        NSString *entry = [NSString stringWithFormat:@"%@.", elementName];
        if (![xml2agcDictionary objectForKey:entry])
            return;
        
        if ([elementName isEqualToString: @"rect"]) {
            //save frame for label/textfield
            NSArray *keys =[NSArray arrayWithObjects:@"x", @"y", @"width", @"height", nil];
            NSLog(@"My parent is %@", inheritanceStack);
            
            if ([[inheritanceStack lastObject] isEqualToString:@"children"]) {
                // axiom: all artboards must have the same size in a single app
                widthXMLArtboard = [[attributeDict objectForKey:@"width"] intValue];
                heightXMLArtboard = [[attributeDict objectForKey:@"height"] intValue];
                
            }
            
            for (id attr in keys){
                
                if ([attributeDict[attr] intValue] || [attributeDict[attr] floatValue])
                    attributes[@"frame"][attr] = [NSNumber numberWithFloat:[attributeDict[attr] floatValue]];
                
                attributes[@"frame"][attr] = attributeDict[attr];
                
            }
            
        }
        
        if ([elementName isEqualToString:@"color"] && [[inheritanceStack lastObject] isEqualToString:@"switch"]) {
            int red = [[attributeDict objectForKey:@"red"] floatValue] * 255;
            int green = [[attributeDict objectForKey:@"green"] floatValue] * 255;
            int blue = [[attributeDict objectForKey:@"blue"] floatValue] * 255;
            NSLog(@"Set color to %d %d %d", red, green, blue);
            NSLog(@"Switch parent = %@", [dictionaryStack lastObject]);
            return;
        }
        
        // when there is a tag with the key backgroundColor; add new rectangle with the spec colors
        if ([elementName isEqualToString: @"color"] && [[attributeDict objectForKey:@"key"] isEqualToString:@"backgroundColor"] && [[inheritanceStack lastObject] intValue]) {
            
            NSMutableDictionary *shapeAttr = [NSKeyedUnarchiver unarchiveObjectWithData:[NSKeyedArchiver archivedDataWithRootObject: attributes[@"rectangle"]]];
            
            NSString *str = [NSString stringWithFormat:@"%@.", elementName];
            
            
            for (id key1 in [xml2agcDictionary objectForKey:str]){
                NSArray *strings = [[xml2agcDictionary[str] objectForKey:key1] componentsSeparatedByString:@"."];
                
                id value = shapeAttr;
                for (id key in [strings subarrayWithRange:NSMakeRange(1, [strings count] - 2)]) {
                    value = [value objectForKey:key];
                    
                }
                
                id tempValue = [attributeDict objectForKey:key1];
                
                if ([tempValue intValue])
                    tempValue = [NSNumber numberWithInt:[tempValue intValue]];
                else if ([tempValue floatValue])
                    tempValue = [NSNumber numberWithFloat:[tempValue floatValue]];
                else if ([tempValue isEqualToString:@"0.0"] || [tempValue isEqualToString:@"0"])
                    tempValue = [NSNumber numberWithInt:0];
                float x = [tempValue floatValue];
                int y = x * 255;
                [value setObject:[NSNumber numberWithInt:y] forKey:[strings lastObject]];
                
            }
            
            id size = [attributes objectForKey:@"frame"];
            
            for (id key1 in xml2agcDictionary[@"rect."]){
                
                NSArray *strings;
                if ([[xml2agcDictionary[@"rect."] objectForKey:key1] isKindOfClass:[NSMutableDictionary class]]) {
                    
                    strings = [[[xml2agcDictionary[@"rect."] objectForKey:key1] objectForKey:@"rect" ]componentsSeparatedByString:@"."];
                    
                }
                else
                    strings = [[xml2agcDictionary[@"rect."] objectForKey:key1] componentsSeparatedByString:@"."];
                
                
                id value = shapeAttr;
                for (id key in [strings subarrayWithRange:NSMakeRange(1, [strings count] - 2)]) {
                    value = [value objectForKey:key];
                    
                }
                
                id tempValue = [size objectForKey:key1];
                
                if ([tempValue intValue])
                    tempValue = [NSNumber numberWithInt:[tempValue intValue]];
                else if ([tempValue floatValue])
                    tempValue = [NSNumber numberWithFloat:[tempValue floatValue]];
                else if ([tempValue isEqualToString:@"0.0"] || [tempValue isEqualToString:@"0"])
                    tempValue = [NSNumber numberWithInt:0];
                    
                [value setObject:tempValue forKey:[strings lastObject]];
                
            }
            
            
            [toInsertObjects addObject: shapeAttr];
            
            return;
            
        } else if ([elementName isEqualToString: @"color"] && [[attributeDict objectForKey:@"key"] isEqualToString:@"backgroundColor"] &&
                   [[attributeDict objectForKey:@"colorSpace" ] isEqualToString:@"calibratedRGB"]){
            
            NSString *entry = [NSString stringWithFormat:@"%@.", elementName];
            
            NSMutableDictionary *shapeAttr = [NSKeyedUnarchiver unarchiveObjectWithData:[NSKeyedArchiver archivedDataWithRootObject: attributes[@"backgroundColor"]]];
            
            for (id key in xml2agcDictionary[entry]){
                id value = shapeAttr;
                NSArray *strings = [[xml2agcDictionary[entry] objectForKey:key] componentsSeparatedByString:@"."];
                
                for (id key1 in [strings subarrayWithRange:NSMakeRange(1, [strings count] - 2)]) {
                    value = [value objectForKey:key1];
                    
                }
                
                float tempValue = [[attributeDict objectForKey:key] floatValue];
                int rgb = tempValue * 255;
                
                [value setObject:[NSNumber numberWithInt:rgb] forKey:[strings lastObject]];
                
            }
            
            [toInsertObjects addObject:shapeAttr];
            
            return;
        }
        
        bool ok = false;
        for (id key in xml2agcDictionary[entry]){
            
            NSArray *strings;
            
            if ([[xml2agcDictionary[entry] objectForKey:key] isKindOfClass:[NSMutableDictionary class]]) {
                
                NSString *parent = [parentDict objectForKey:@"type"];
                
                if (parent)
                    strings = [[[xml2agcDictionary[entry] objectForKey:key] objectForKey: parent] componentsSeparatedByString:@"."];
                else {
                    ok = true;
                    return;
                    
                }
            }
            else {
                strings = [[xml2agcDictionary[entry] objectForKey:key] componentsSeparatedByString:@"."];
            }
            
            id value = parentDict;
            
            for (id key1 in [strings subarrayWithRange:NSMakeRange(1, [strings count] - 2)]){
                value = [value objectForKey: key1];
                
            }
            
            if (![attributeDict objectForKey:key])
                continue;
            
            
            id tempValue = [attributeDict objectForKey:key];
            
            if ([tempValue intValue])
                tempValue = [NSNumber numberWithInt:[tempValue intValue]];
            else if ([tempValue floatValue])
                tempValue = [NSNumber numberWithFloat:[tempValue floatValue]];
            
            if ([attributeDict objectForKey:key] && [elementName isEqualToString:@"color"]){
                //transform to RGB values!!!!
                float x = [tempValue floatValue];
                int y = x * 255;
                tempValue = [NSNumber numberWithInt: y];
                
            } else if ([attributeDict objectForKey:key] && [elementName isEqualToString:@"fontDescription"] && [[inheritanceStack lastObject] intValue]){
                
                NSString *text = attributes[@"#text"];
                float width = [[[attributes objectForKey:@"frame"] objectForKey:@"width"] floatValue];
                float height = [[[attributes objectForKey:@"frame"] objectForKey:@"height"] floatValue];
                float x = [[[attributes objectForKey:@"frame"] objectForKey:@"x"] floatValue];
                float y = [[[attributes objectForKey:@"frame"] objectForKey:@"y"] floatValue];
                CGSize frameSize = CGSizeMake(width, height);
                int textSize = [tempValue intValue];
                NSFont *font = [NSFont systemFontOfSize:textSize];
                
                CGRect idealFrame = [text boundingRectWithSize:frameSize
                                                       options:NSStringDrawingUsesLineFragmentOrigin
                                                    attributes:@{ NSFontAttributeName:font }
                                                       context:nil];
                
                float x_pos =(width - idealFrame.size.width) /2;
                float y_pos =(height - idealFrame.size.height) /2;
                
                x_pos = x_pos + x;
                y_pos = y_pos + y + textSize;
                
                id tempDict = parentDict;
                
                tempDict = [tempDict objectForKey:@"transform"];
                
                [tempDict setObject:[NSNumber numberWithFloat:x_pos] forKey:@"tx"];
                [tempDict setObject:[NSNumber numberWithFloat:y_pos] forKey:@"ty"];
                
                [value setObject:tempValue forKey:[strings lastObject]];
                return;
            }
            if (!ok){
                if([ [value objectForKey:[strings lastObject]] isKindOfClass:[NSString class] ] &&
                   [[ [value objectForKey:[strings lastObject]] substringToIndex:1] isEqualToString:@"$"])
                    [value setObject:tempValue forKey:[strings lastObject]];
                else if ([value objectForKey:@"href"]) {
                    //if it is an image -> update width & height
                    
                    id value = parentDict;
                    value = [value objectForKey:@"shape"];
                    
                    float weight = [[attributeDict objectForKey:@"width"] floatValue];
                    float height = [[attributeDict objectForKey:@"height"] floatValue];
                    
                    [value setObject:[NSNumber numberWithFloat:weight] forKey:@"width"];
                    [value setObject:[NSNumber numberWithFloat:height]  forKey:@"height"];
                }
            }
        }
        
        return;
    }
    else if (!insertedRoot){
        [parentDict setObject: @"1.5.0" forKey:@"version"];
        [parentDict setObject: tempDict  forKey:@"resources"];
        [parentDict setObject: tempDict  forKey:@"artboards"];
        
        insertedRoot = true;
    }
    
    
    elementName = [xml2agcDictionary objectForKey:elementName];
    //NSLog(@"ElementName = %@ for %@", elementName, nameInit);
    NSMutableDictionary *correctAttr = [NSKeyedUnarchiver unarchiveObjectWithData:[NSKeyedArchiver archivedDataWithRootObject: attributes[elementName]]];
    ;
    //First level attributes
    for (id key in attributes[elementName]){
        
        id value = [attributes[elementName] objectForKey:key];
        
        if ([value isKindOfClass:[NSString class]]){
            if ([[value substringToIndex:1] isEqualToString:@"$"]){
                
                NSInteger i = [value length] -1;
                value = [value substringWithRange:NSMakeRange(1, i)];
                
                NSString *tempSaved = [NSString stringWithFormat:@"#%@", value];
                id tempValue = nil;
                if ([value isEqualToString:@"text"] && attributeDict[value])
                    tempValue = attributeDict[value];
                
                else if (!attributeDict[value])
                    tempValue = attributeDict[@"placeholder"];
                
                if ([tempValue intValue] )
                    tempValue = [NSNumber numberWithInt:[tempValue intValue]];
                else if ([tempValue floatValue]){
                    tempValue = [NSNumber numberWithFloat:[tempValue floatValue]];
                }
                attributes[tempSaved] = tempValue;
                correctAttr[key] = tempValue;
                
            }
            //TODO transfrom for lower levels; propagate attributes
        } else if ([elementName isEqualToString:@"imageView"] && [key isEqualToString:@"style"]){
            
            NSString *imageName = [NSString stringWithFormat:@"%@/%@",
                                   [self resourcesPath], [attributeDict objectForKey:@"image"]];
            NSArray *strings = [[xml2agcDictionary objectForKey:@"imageView."] componentsSeparatedByString:@"."];
            
            id value = correctAttr;
            for (id key in [strings subarrayWithRange:NSMakeRange(0, [strings count] -1)]){
                value = [value objectForKey:key];
                
            }
            
            //generate random values for uid ...
            int num = arc4random() % 1000000;
            [value setObject:imageName forKey:[strings lastObject]];
            
            NSImage *image = [[NSImage alloc]initWithContentsOfFile:imageName];
            
            if (image == nil) {
                NSLog(@"[ERROR]Image is nil");
            }
            
            [value setObject:[NSNumber numberWithInt:image.size.width] forKey:@"width"];
            [value setObject:[NSNumber numberWithInt:image.size.height] forKey:@"height"];
            
            value = [[value objectForKey:@"meta"] objectForKey:@"ux"];
            
            [value setObject: [NSString stringWithFormat:@"%d", num] forKey:@"uid"];
        }
    }
    
    [childDict addEntriesFromDictionary:correctAttr];
    
    if ([xml2agcDictionary objectForKey:[inheritanceStack lastObject]] &&
        [[xml2agcDictionary objectForKey:[inheritanceStack lastObject]] isEqual: @"list"]){
        elementName = [[NSString alloc] initWithFormat:@"%d",counterCh++];
        id lastObject =  [NSKeyedUnarchiver unarchiveObjectWithData:[NSKeyedArchiver archivedDataWithRootObject: [dictionaryStack lastObject]]];
        
        if ([[inheritanceStack lastObject] isEqualToString: @"children"] && ![childDict objectForKey:@"type"]){
            [childDict setObject:@"artboard" forKey:@"type"];
        }
        
        NSMutableArray *array = nil;
        if (![lastObject isKindOfClass:[NSMutableArray class]] && [lastObject count] == 0 ){
            array = [NSMutableArray array];
            [array addObject:childDict];
            
            [parentDict setObject:array forKey:[inheritanceStack lastObject]];
        }
        else {
            
            array = (NSMutableArray *) [lastObject objectForKey:[inheritanceStack lastObject]];
            
            [array addObject: childDict];
            [parentDict setObject:array forKey:[inheritanceStack lastObject]];
            
        }
        
    }else   [parentDict setObject:childDict forKey:elementName];
    
    
    [inheritanceStack addObject:elementName];
    
    [dictionaryStack addObject:childDict];
}

- (void)parser:(NSXMLParser *)parser didEndElement:(NSString *)elementName namespaceURI:(NSString *)namespaceURI qualifiedName:(NSString *)qName
{
    
    
    if ([elementName isEqualToString:@"switch"]) {
        [inheritanceStack removeObject:@"switch"];
        return;
        
    }
    
    if ([xml2agcDictionary[elementName] isEqualToString:@"artboard"]) {
        //TODO!!! new file -> compute header
        NSString *artboardNo = [NSString stringWithFormat:@"artboard%d", counterArtboards++] ;
        [[dictionaryStack lastObject] setObject:artboardNo forKey:@"ref"];
        //[artboards addObject:artboardNo];
    }
    
    //TODO2 remove function after TODO1 (this < didStartElement ?)
    if ([elementName isEqualToString:@"rect"] && [[inheritanceStack lastObject] isEqualToString:@"switch"]){
        
        //TODO1 insert in xml2agcDict
        id value = [[[dictionaryStack lastObject] objectForKey:@"children"] lastObject];
        
        
        NSArray *strings = [@"switch.transform.tx" componentsSeparatedByString:@"."];
        
        for (id key in [strings subarrayWithRange:NSMakeRange(1, [strings count] -2)]) {
            value = [value objectForKey:key];
        }
        
        id frame = [attributes objectForKey:@"frame"];
        [value setObject:[frame objectForKey:@"x"] forKey:[strings lastObject]];
        //TODO1 change here!!!
        strings = [@"switch.transform.ty" componentsSeparatedByString:@"."];
        frame = [attributes objectForKey:@"frame"];
        
        [value setObject:[frame objectForKey:@"y"] forKey:[strings lastObject]];
        
        return;
        
    }
    
    //replace all $"smth" values with default ones
    
    NSString *tempReplace = [NSString stringWithFormat:@"#%@", elementName];
    
    if ([elementName isEqualToString:@"label"]){
        tempReplace = [NSString stringWithFormat:@"#%@", xml2agcDictionary[elementName]];
    }
    
    NSMutableDictionary *parentDict = [dictionaryStack lastObject];
    NSString *textValue = nil;
    for (id key in xml2agcDictionary[tempReplace]){
        
        
        NSArray *strings = [key componentsSeparatedByString:@"."];
        
        
        id value = parentDict;
        
        for (id key1 in [strings subarrayWithRange:NSMakeRange(1, [strings count] - 2)]){
            
            value = [value objectForKey:key1];
            
        }
        textValue = [attributes objectForKey:[xml2agcDictionary[tempReplace] objectForKey:key]];
        [value setObject:[attributes objectForKey:[xml2agcDictionary[tempReplace] objectForKey:key]] forKey:[strings lastObject]];
    }
    
    
    id agcElement = [xml2agcDictionary objectForKey:elementName];
    if ([[xml2agcDictionary objectForKey:agcElement] isEqualToString:@"list"]){
        
        NSInteger counter = [dictionaryStack count];
        id prevParent = dictionaryStack[counter - 2];
        [prevParent addEntriesFromDictionary:parentDict];
    }
    
    if ([elementName isEqualToString:@"textField"] || [elementName isEqualToString:@"label"]){
       // NSInteger length = tempReplace.length;
        
        NSArray *strings = [[xml2agcDictionary objectForKey:@"length."] componentsSeparatedByString:@"."];
        
        id value = parentDict;
        for (id key in [strings subarrayWithRange:NSMakeRange(1, [strings count] - 2)]){
            if ([value isKindOfClass:[NSMutableDictionary class]])
                value = [value objectForKey: key];
            else
                value = value[0][key][0][0]; // For lines only
            
        }
        
        [value setObject:[NSNumber numberWithLong:textValue.length] forKey:[strings lastObject]];
        
    }
    
    //default Values
    id name = elementName;
    if ([elementName isEqualToString:@"label"])
        name =xml2agcDictionary[elementName];
    
    id def = [defaultValues objectForKey:name];
    for(id key in def){
        
        NSArray *strings = [key componentsSeparatedByString:@"."];
        //NSString *firstTag = [[NSString alloc] initWithFormat:@"%@.", strings[0]];
        id value = parentDict;
        
        for (id key1 in [strings subarrayWithRange:NSMakeRange(1, [strings count] - 2)]){
            value = [value objectForKey:key1];
        }
        
        id tempValue = [value objectForKey:[strings lastObject]];
        
        if (![tempValue isKindOfClass:[NSNumber class]] && [tempValue isKindOfClass:[NSString class]] && [[tempValue substringToIndex:1] isEqualToString:@"$"]){
            
            [value setObject:[def objectForKey:key] forKey:[strings lastObject]];
        }
        
    }
    
    if ([toInsertObjects count] && [elementName isEqualToString:@"view"]) {
        NSLog(@"For button %@ at %@", toInsertObjects, [dictionaryStack objectAtIndex:2]);
        id prevParent = [dictionaryStack objectAtIndex:2];
        
        [prevParent addEntriesFromDictionary:[toInsertObjects objectAtIndex:0]];
        [toInsertObjects removeLastObject];
        
    }
    
    //insert Objects from toInsertObjects
    if ([elementName isEqualToString:@"textField"] || [elementName isEqualToString:@"label"] ) {
        for (id key in toInsertObjects){
            NSInteger counter = [dictionaryStack count];
            id prevParent = dictionaryStack[counter - 2];
            
            [[prevParent objectForKey:@"children" ] insertObject:key atIndex:0];
            
        }
        
        [toInsertObjects removeLastObject];
        
    }
    
    
    // Set the text property
    if ([textInProgress length] > 0)
    {
        // Reset the texts
        textInProgress = [[NSMutableString alloc] init];
    }
    
    if ([xml2agcDictionary objectForKey:elementName]){
        // Pop the current dict
        [dictionaryStack removeLastObject];
        
        [inheritanceStack removeLastObject];
        
    }
    
}

- (void)parser:(NSXMLParser *)parser foundCharacters:(NSString *)string
{
    
    // Build the text value
    [textInProgress appendString:string];
}

- (void)parser:(NSXMLParser *)parser parseErrorOccurred:(NSError *)parseError
{
    // Set the error pointer to the parser's error object
    
}

@end
