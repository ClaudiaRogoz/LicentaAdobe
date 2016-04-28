//
//  Sync.m
//  XMLParser
//
//  Created by crogoz on 20/04/16.
//  Copyright © 2016 crogoz. All rights reserved.
//

#import "Sync.h"

@import AppKit;

@implementation Sync


+ (void) startSync:(NSString *) path {
    NSError *error;
    Sync *sync = [[Sync alloc] initWithError:&error];
    [sync initSync];
    [sync monitorXDFile:path];
    
}

- (id)initWithError:(NSError **)error
{
    return self;
}

- (void) initSync
{
    NSError *error;
    NSBundle *thisBundle = [NSBundle bundleForClass:[self class]];
    NSString *def = [thisBundle pathForResource:AGC_TEMPLATE ofType:JSON];
    NSData *defData = [NSData dataWithContentsOfFile:def];
    
    exportAgc = [[NSMutableDictionary alloc] init];
    offsetXmlFile = [[NSMutableDictionary alloc] init];
    objectOffset = [[NSMutableDictionary alloc] init];
   
    attributes = [NSJSONSerialization JSONObjectWithData:defData options:NSJSONReadingMutableContainers error:&error];
    
    /* TODO read from rules */
    exportAgc[@"shape"] = [[NSMutableDictionary alloc] init];
    
    exportAgc[@"shape"][@"path"] = [[NSMutableArray alloc] init ];
    [exportAgc[@"shape"][@"path"] addObject:@"style.fill.type.solid"];
    [exportAgc[@"shape"][@"path"] addObject:@"shape.type.path"];
    
    exportAgc[@"shape"][@"rectangle"] = [[NSMutableArray alloc] init];
    [exportAgc[@"shape"][@"rectangle"] addObject:@"style.fill.type.solid" ];
    [exportAgc[@"shape"][@"rectangle"] addObject:@"shape.type.rect"];
    
    exportAgc[@"shape"][@"imageView"] = @"style.fill.type.pattern";
    exportAgc[@"group"] = [[NSArray alloc] init];
    
    exportAgc[@"text"] = @"textField";
    
    objectOffset[@"<scene"] = [NSNumber numberWithInt: 1];
    
    
}

/* second = prev dictionary; first = current dictionary */
- (NSMutableDictionary*) compare2Artboards:(NSArray *) first dict2:(NSArray *) second artboard_info:(NSMutableDictionary *)jsonArtboards offsetGroup:(NSMutableDictionary *)offsetGroupDict numberGroup:(NSNumber *) nr
{
    
    unsigned long counter = MIN([first count], [second count]);
    NSMutableDictionary *xmlExport = [[NSMutableDictionary alloc] init];
    for (int i = 0; i< counter; i++) {
        
        NSDictionary *prev = [second objectAtIndex:i];
        NSDictionary *newD = [first objectAtIndex:i];
        
        id typeP = [prev objectForKey:TYPE];
        id typeN = [newD objectForKey:TYPE];
        
        // check if it is the same object (no adding, nor deleting, just modifyingn ops)
        if ([typeN isEqualToString:typeP]) {
            
            id solType = [exportAgc objectForKey:typeN];
            
            //if type == Group
            if ([solType isKindOfClass:[NSArray class]]) {
                
                id transform = [newD objectForKey:TRANSFORM];
                int prevTx = [[offsetGroupDict objectForKey:TX] intValue];
                int prevTy = [[offsetGroupDict objectForKey:TY] intValue];
                int tx = [[transform objectForKey:TX] intValue] + prevTx;
                int ty = [[transform objectForKey:TY] intValue] + prevTy;
                NSMutableDictionary *dict = [@{TX : [NSNumber numberWithInt:tx], TY : [NSNumber numberWithInt:ty]} mutableCopy];
                
                id newDictCh = [[newD objectForKey:GROUP] objectForKey:CHILDREN];
                id prevDictCh = [[prev objectForKey:GROUP] objectForKey:CHILDREN];
                
                
                NSMutableDictionary *newXmlDict  = [self compare2Artboards:newDictCh dict2:prevDictCh artboard_info:jsonArtboards offsetGroup:dict numberGroup:[NSNumber numberWithInt:i + 1]];
                nr = 0;
                
                for (id newKey in newXmlDict) {
                    NSMutableDictionary *dict = [newXmlDict objectForKey:newKey];
                    
                    NSMutableDictionary *dictGroup = [xmlExport objectForKey:[NSNumber numberWithInt:i + 1]];
                    if (dictGroup == nil) {
                        [xmlExport setObject:dict forKey:[NSNumber numberWithInt:i + 1]];
                    } else {
                        [dictGroup addEntriesFromDictionary:dict];
                    }
                    
                }
                
                [offsetGroupDict setObject:[NSNumber numberWithInt:prevTx] forKey:TX];
                [offsetGroupDict setObject:[NSNumber numberWithInt:prevTx] forKey:TY];
                
                continue;
                
            }
            
            // only one possibility when type = solType (eg. textfield)
            if ([solType isKindOfClass:[NSString class]]) {
                
                NSDictionary *currAttr = [attributes objectForKey:solType];
                
                NSMutableDictionary *trList = [[NSMutableDictionary alloc] init];
                
                bool ok = [self checkAreEqual:newD prevDict:prev attr:currAttr outList:&trList equal:true json_info:jsonArtboards];
                
                if (ok == false) {
                    
                    NSNumber *tagNo = [NSNumber numberWithInt:i + 1]; // counter starts at 1!!!!!
                    if ([nr intValue])
                        xmlExport[tagNo] = trList;
                    else
                        xmlExport[tagNo] = trList;
                }
                continue;
                
            }
            
            //type = NSMutableDictionary eg.shape
            for (id key in solType){
                
                id cond = [solType objectForKey:key];
                if ([cond isKindOfClass:[NSArray class]]) {
                    
                    //is kind of array => multiple rules must be achieved
                    NSString *condIsOfType = @"";
                    int isOk = true;
                    for (id rule in cond) {
                        NSArray *array = [rule componentsSeparatedByString:DOT];
                        
                        id value1 = prev;
                        id value2 = newD;
                        
                        for (id key1 in [array subarrayWithRange:NSMakeRange(0, [array count] -1)]) {
                            
                            if (![value1  objectForKey:key1] || ![value2  objectForKey:key1]) {
                                condIsOfType  = NOT;
                                break;
                            }
                            value1 = [value1 objectForKey:key1];
                            value2 = [value2 objectForKey:key1];
                        }
                        
                        bool eqValues = [value1 isEqualToString: value2] && [value1 isEqualToString:[array lastObject]];
                        if ([condIsOfType isEqualToString:NOT] || !eqValues) {
                            isOk = false;
                            break;
                        }
                    }
                    
                    
                    if (isOk){
                        
                        NSDictionary *currAttr = [attributes objectForKey:key];
                        
                        NSMutableDictionary *trList = [[NSMutableDictionary alloc] init];
                        
                        bool ok = [self checkAreEqual:newD prevDict:prev attr:currAttr outList:&trList equal:true json_info:jsonArtboards];
                        
                        if (ok == false) {
                            
                            NSNumber *tagNo = [NSNumber numberWithInt:i + 1]; // nsdictionary counter starts at 1!!!!!
                            
                            if ([nr intValue]) {
                                xmlExport[tagNo] = trList;
                            }
                            else
                                xmlExport[tagNo] = trList;
                            
                        }
                        break;
                    }
                    
                }
                else if ([cond isKindOfClass:[NSString class]]) {
                    NSArray *array = [cond componentsSeparatedByString:DOT];
                    
                    id value1 = prev;
                    id value2 = newD;
                    
                    for (id key1 in [array subarrayWithRange:NSMakeRange(0, [array count] -1)]) {
                        value1 = [value1 objectForKey:key1];
                        value2 = [value2 objectForKey:key1];
                    }
                    
                    
                    if ([value1 isEqualToString: value2] && [value1 isEqualToString:[array lastObject]]){
                        
                        NSDictionary *currAttr = [attributes objectForKey:key];
                        
                        NSMutableDictionary *trList = [[NSMutableDictionary alloc] init];
                        bool ok = [self checkAreEqual:newD prevDict:prev attr:currAttr outList:&trList equal:true json_info:jsonArtboards];
                        
                        if (ok == false) {
                            NSNumber *tagNo = [NSNumber numberWithInt:i + 1]; // nsdictionary counter starts at 1!!!!!
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

- (NSString *) appendModifiedString:(NSMutableDictionary *)dict minTagOffset:(NSNumber **)tagOffset
{
    NSMutableString *newString = [[NSMutableString alloc] init];
    
    NSArray *order = [NSArray arrayWithObjects:FRAME, FONT_DESCR, COLOR, nil];
    
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

//transform from XD coordinates to Xcode coordinates
-(bool) checkTransformToAbsoluteValue:(NSNumber **)value variable:(NSString *)var scale_dict:(NSDictionary *) scaleDict other_updates:(NSMutableDictionary **) otherUpdates
{
    if ([var isEqualToString:FRAME_X] || [var isEqualToString:FRAME_Y]) {
        //transform relative coord to absolute coord
        NSArray *arr = [var componentsSeparatedByString:DOT];
        int offsetValue = [[scaleDict objectForKey:[arr lastObject]] intValue];
        
        //scale to xcode artboard
        float xScaleFactor = (float)widthXMLArtboard / widthAgcArtboard;
        float yScaleFactor = (float)heightXMLArtboard / heightAgcArtboard;
        
        float scaledValue = [*value floatValue] - offsetValue;
        if ([var isEqualToString:FRAME_X])
            scaledValue = scaledValue * xScaleFactor;
        else
            scaledValue = scaledValue * yScaleFactor;
        
        *value = [NSNumber numberWithFloat: scaledValue];
        
        return true;
    }
    else if ([var isEqualToString:COLOR_RED] || [var isEqualToString:COLOR_GREEN] || [var isEqualToString:COLOR_BLUE]) {
        
        *value = [NSNumber numberWithFloat:[*value floatValue]/255];
        return true;
        
    } else if ([var isEqualToString:FONT_POINT]) {
        
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
    NSArray * sortedAllKeys = [prev allKeys];
    sortedAllKeys = [sortedAllKeys sortedArrayUsingComparator:^(id a, id b) {
        return [a compare:b];
    }];
    for (id key in sortedAllKeys) {
        
        if ([key isEqualToString:RAWTEXT_VALUE])
            tempText = [newD objectForKey:key];
        
        id value = [prev objectForKey:key];
        
        if ([value isKindOfClass:[NSMutableDictionary class]] && [currAttr objectForKey:key]) {
            
            eq = [self checkAreEqual:[prev objectForKey:key] prevDict:[newD objectForKey:key] attr:[currAttr objectForKey:key] outList:trList equal:eq json_info:(NSDictionary *) jsonInfo];
            
        } else if ([value isKindOfClass:[NSMutableArray class]]) {
            id areLines = [[value objectAtIndex:0] objectForKey:LINE_VALUE];
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

- (void) updateXMLfile:(NSDictionary *)tags
                 tagNo:(NSNumber *)n
           offsetScene:(NSNumber **) offset_scene
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
        
        
        
        
        //update offset & propagate offset
        unsigned long prevOffset = (unsigned long)range.location;
        
        [outputTempXml seekToEndOfFile];
        
        //copy to file + copy intra chunks beteween (key, key +1)
        if (prevKey == 0) {
            //copy all from beginning to the curent offset
            //change for any "n" -> only no 1 artboard works
            [inputXml seekToFileOffset:[*offset_scene longValue]];
            long sizeToRead = minTagOffset - [*offset_scene longValue];
            NSData *inputData = [inputXml readDataOfLength:sizeToRead];
            
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
            
        } else {
            
            //copy all tags from the prevKey to this key
            //update each offset in between
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

-(NSString *) getProjHomePath {
    
    NSString *mainBundle = [[NSBundle mainBundle] bundlePath];
    for (int i = 0; i< PROJ_PATH; i++) {
        mainBundle = [mainBundle stringByDeletingLastPathComponent];
    }
    return mainBundle;
}

-(void) unzipXD:(NSString *)path atPath:(NSString*) unzipped_xd {
    
    NSError *error;
    
    if ([[NSFileManager defaultManager] fileExistsAtPath:unzipped_xd])
        [[NSFileManager defaultManager] removeItemAtPath:unzipped_xd error:&error];
    
    [[NSFileManager defaultManager] createDirectoryAtPath:unzipped_xd withIntermediateDirectories:NO attributes:nil error:&error];
    
    NSTask *task = [[NSTask alloc] init];
    task.launchPath = UNZIP_PATH;
    task.arguments = @[path];
    task.currentDirectoryPath=unzipped_xd;
    
    [task launch];
    [task waitUntilExit];
    
}
-(id) gotoAttribute:(NSMutableDictionary *) dict rules:(NSString *) rule {

    NSArray *array = [rule componentsSeparatedByString:DOT];
    id tempDict = dict;
    
    for (id key in array) {
        if ([tempDict isKindOfClass:[NSDictionary class]])
            tempDict = [tempDict objectForKey:key];
        else tempDict = [tempDict objectAtIndex:[key intValue]];
    
    }
    return tempDict;

}

-(NSMutableDictionary *) serializeFromPath:(NSString *)filePath {
    
    NSError *error;
    NSString *jsonString = [[NSString alloc] initWithContentsOfFile:filePath encoding:NSUTF8StringEncoding error:NULL];
    
    return [NSJSONSerialization JSONObjectWithData:[jsonString dataUsingEncoding:NSUTF8StringEncoding] options:NSJSONReadingMutableContainers error:&error];
}

-(void) processArtboardPairs:(NSMutableArray *)filesInit enumerator:(NSDirectoryEnumerator *) enumeratorF agcinfo:(NSMutableDictionary *) jsonArtboards {
    int i = 0;
    
    for (NSURL *urlF in enumeratorF) {
        NSError *error;
        NSNumber *isDirectory = nil;
        if (! [urlF getResourceValue:&isDirectory forKey:NSURLIsDirectoryKey error:&error]) {
            // handle error
        }
        else if (! [isDirectory boolValue] &&
                 ![[[urlF path] lastPathComponent] isEqualToString:@".DS_Store"]) {
            
            NSMutableDictionary *jsonDict1 = [self serializeFromPath:[urlF path]];
            NSMutableDictionary *jsonDict2 = [self serializeFromPath:[filesInit objectAtIndex:i]];
            
            NSArray *first = [self gotoAttribute:jsonDict1 rules:CHILDREN_SUBVIEWS];
            NSArray *second = [self gotoAttribute:jsonDict2 rules:CHILDREN_SUBVIEWS];
            
            NSString *artboardNoInfo = [NSString stringWithFormat:@"artboard%d", i +1];
            
            NSMutableDictionary * offsetGroupDict = [[NSMutableDictionary alloc] init];
            offsetGroupDict[TX] = [NSNumber numberWithInt: 0];
            offsetGroupDict[TY] = [NSNumber numberWithInt: 0];
            
            NSMutableDictionary* tagExport = [self compare2Artboards:first
                                                               dict2:second
                                                       artboard_info:[jsonArtboards objectForKey:artboardNoInfo]
                                                         offsetGroup:offsetGroupDict
                                                         numberGroup:[NSNumber numberWithInt:0]];
            NSLog(@"To export = %@ %d", tagExport, i);
            
            ++i;
            
        }
    }


}

- (void) findChangesForPath:(NSString *)unzipped_xd {
    
    NSString *mainBundle = [self getProjHomePath];
    NSError *error;
    NSURL *directoryURLF = [NSURL fileURLWithPath:[mainBundle stringByAppendingPathComponent:[NSString stringWithFormat:@".%@", PREV_ART_PATH]]];
    NSURL *directoryURLI = [NSURL fileURLWithPath:unzipped_xd];
    NSString *pathToArtboardAgc = [unzipped_xd stringByAppendingPathComponent: GRAPHIC_CONTENT ];
    NSString *jsonString = [[NSString alloc] initWithContentsOfFile:pathToArtboardAgc encoding:NSUTF8StringEncoding error:NULL];
    NSMutableDictionary *jsonArtboards = [NSJSONSerialization JSONObjectWithData:[jsonString dataUsingEncoding:NSUTF8StringEncoding] options:NSJSONReadingMutableContainers error:&error];
    
    jsonArtboards = [jsonArtboards objectForKey:ARTBOARDS];
    
    widthAgcArtboard = [[[jsonArtboards objectForKey:FIRST_ARTBOARD] objectForKey:WIDTH] intValue];
    heightAgcArtboard = [[[jsonArtboards objectForKey:FIRST_ARTBOARD]  objectForKey:HEIGHT] intValue];
    
    NSArray *keys = [NSArray arrayWithObject:NSURLIsDirectoryKey];
    
    NSDirectoryEnumerator *enumeratorI = [[NSFileManager defaultManager]
                                          enumeratorAtURL:directoryURLI
                                          includingPropertiesForKeys:keys
                                          options:0
                                          errorHandler:^(NSURL *url, NSError *error) {
                                              return YES;
                                          }];
    
    NSDirectoryEnumerator *enumeratorF = [[NSFileManager defaultManager]
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
            
            if ([[[[urlI path] componentsSeparatedByString:@"/"] lastObject] isEqualToString:GRAPHIC]) {
                [filesInit addObject:[urlI path]];
            }
        }
        
    }
    
    [self processArtboardPairs:filesInit enumerator:enumeratorF agcinfo:jsonArtboards];
    
}

- (void) monitorXDFile:(NSString*) path
{
    
    const char *pathString = [path cStringUsingEncoding:NSASCIIStringEncoding];
    int fildes = open(pathString, O_RDONLY);
    NSLog(@"Filedes = %d", fildes);
    dispatch_queue_t queue = dispatch_get_global_queue(0, 0);
    __block dispatch_source_t source = dispatch_source_create(DISPATCH_SOURCE_TYPE_VNODE, fildes, DISPATCH_VNODE_DELETE | DISPATCH_VNODE_WRITE | DISPATCH_VNODE_EXTEND | DISPATCH_VNODE_ATTRIB | DISPATCH_VNODE_LINK | DISPATCH_VNODE_RENAME | DISPATCH_VNODE_REVOKE,
                                                              queue);
    dispatch_source_set_event_handler(source, ^
                                      {
                                          unsigned long flags = dispatch_source_get_data(source);
                                          
                                          if(flags & DISPATCH_VNODE_DELETE)
                                          {
                                              [self monitorXDFile:path];
                                              
                                          }
                                          else {
                                              
                                              
                                              /* creates an unzip directory of the current XD project (**changes have been made ) */
                                              NSString *mainBundle = [self getProjHomePath];
                                              NSString *unzipped_xd = [mainBundle stringByAppendingPathComponent:XD_UNZIP_PATH];
                                              
                                              [self unzipXD:path atPath:unzipped_xd];
                                              
                                              [self findChangesForPath:(NSString *)unzipped_xd];
                                          }
                                      });
    
    dispatch_source_set_cancel_handler(source, ^(void)
                                       {
                                           close(fildes);
                                       });
    dispatch_resume(source);
    
}


@end
