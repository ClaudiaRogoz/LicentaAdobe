//
//  XMLReader.m
//  XMLParser
//
//  Created by crogoz on 05/03/16.
//  Copyright © 2016 crogoz. All rights reserved.
//

#import "XMLReader.h"

NSString *const kXMLReaderTextNodeKey = @"text";


@interface XMLReader (Internal)

- (id)initWithError:(NSError **)error;
- (NSDictionary *)objectWithData:(NSData *)data;

@end


@implementation XMLReader

#pragma mark -
#pragma mark Public methods

+ (NSDictionary *)dictionaryForXMLData:(NSData *)data error:(NSError **)error
{
    XMLReader *reader = [[XMLReader alloc] initWithError:error];
    NSDictionary *rootDictionary = [reader objectWithData:data];
      return rootDictionary;
}

+ (NSDictionary *)dictionaryForXMLString:(NSString *)string error:(NSError **)error
{
    NSData *data = [string dataUsingEncoding:NSUTF8StringEncoding];
    return [XMLReader dictionaryForXMLData:data error:error];
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

- (NSDictionary *)objectWithData:(NSData *)data
{
    
    dictionaryStack = [[NSMutableArray alloc] init];
    textInProgress = [[NSMutableString alloc] init];
    inheritanceStack = [[NSMutableArray alloc] init];
    attributes = [[NSMutableDictionary alloc] init];
    toInsertObjects = [[NSMutableArray alloc] init];
    
    //TODO eventually read from file (XML ??? )
    insertedRoot = false;
    xml2agcDictionary = [[NSMutableDictionary alloc] init];
    xml2agcDictionary[@"scene"] = @"children1";
    xml2agcDictionary[@"objects"] = @"artboard2";
    xml2agcDictionary[@"viewController"] = @"artboard";
    //xml2agcDictionary[@"imageView"] = @"imageView";
    xml2agcDictionary[@"view"] = @"children";
    xml2agcDictionary[@"textField"] =@"textField";
    xml2agcDictionary[@"label"] =@"textField";
    
    
    xml2agcDictionary[@"children"] = @"list";
    xml2agcDictionary[@"children1"] = @"list";
    xml2agcDictionary[@"paragraphs"] = @"list";
   
    xml2agcDictionary[@"textField."][@"name"] = @"text";
    
    //inverted index for bottom-up inheritance
    xml2agcDictionary[@"rect."] = [[NSMutableDictionary alloc] init];
    xml2agcDictionary[@"rect."][@"x"] = @"textField.transform.tx"; //TODO Dictionary based on type (textField only) -> make dictionary of {textfield: transform.x; label: ....x}
    xml2agcDictionary[@"rect."][@"y"] = @"textField.transform.ty";
    xml2agcDictionary[@"rect."][@"width"] = @"rect.shape.width"; //TODO Dictionary based on type (textField only) -> make dictionary of {textfield: transform.x; label: ....x}
    xml2agcDictionary[@"rect."][@"height"] = @"rect.shape.height";
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
    attributes[@"textField"][@"name"] = @"$text";
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
    attributes[@"textField"][@"text"][@"rawText"] = @"#text"; // # already saved (an attribute from parent ??? TODO eventually for other cases !!!!!) should I use a stack ??
    
    attributes[@"rectangle"] = [[NSMutableDictionary alloc] init]; // TODO name insert!! random ? OR WITH hashtableNames (better)
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
    
    
   /* attributes[@"imageView"] = [[NSMutableDictionary alloc] init];
    attributes[@"imageView"][@"type"] = @"shape";
    attributes[@"imageView"][@"transform"] = attributes[@"rectangle"][@"transform"];
    attributes[@"imageView"][@"style"][@"fill"] = [[NSMutableDictionary alloc] init];
    attributes[@"imageView"][@"style"][@"fill"][@"type"] = @"pattern";
    attributes[@"imageView"][@"style"][@"fill"][@"pattern"] = [[NSMutableDictionary alloc] init];
    attributes[@"imageView"][@"style"][@"fill"][@"pattern"][@"width"] = @"%image.width"; //TODO ???
    attributes[@"imageView"][@"style"][@"fill"][@"pattern"][@"height"] = @"%image.height";
    attributes[@"imageView"][@"style"][@"fill"][@"pattern"][@"href"] = @"";
    */
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
    
    attributes[@"frame"] = [[NSMutableDictionary alloc] init];
    
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
    parser.delegate = self;
    BOOL success = [parser parse];
    
    // Return the stack's root dictionary on success
    if (success)
    {
        NSDictionary *resultDict = [dictionaryStack objectAtIndex:0];
        return resultDict;
    }
    
    return nil;
}

#pragma mark -
#pragma mark NSXMLParserDelegate methods

- (void)parser:(NSXMLParser *)parser didStartElement:(NSString *)elementName namespaceURI:(NSString *)namespaceURI qualifiedName:(NSString *)qName attributes:(NSDictionary *)attributeDict
{
    // Get the dictionary for the current level in the stack
    NSMutableDictionary *parentDict = [dictionaryStack lastObject];
    
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
            //TODO save frame for label/textfield
            NSArray *keys =[NSArray arrayWithObjects:@"x", @"y", @"width", @"height", nil];
            
            for (id attr in keys){
               
                if ([attributeDict[attr] intValue])
                    attributes[@"frame"][attr] = [NSNumber numberWithFloat:[attributeDict[attr] floatValue]];
                 attributes[@"frame"][attr] = attributeDict[attr];
            }
            
        }
        
        // when there is a tag with the key backgroundColor; add new rectangel with the spec colors
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
               
                    NSArray *strings = [[xml2agcDictionary[@"rect."] objectForKey:key1] componentsSeparatedByString:@"."];
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
          
            NSArray *strings = [[xml2agcDictionary[entry] objectForKey:key] componentsSeparatedByString:@"."];
            
            id value = nil;
            if ([[parentDict objectForKey:@"type"] isEqualToString:@"text"])
                value = parentDict;
            
            //check if inverted index corresponds to current value
            if ([[strings objectAtIndex:0] isEqualToString:[entry substringToIndex:[entry length] - 1]])
                 continue;
            
            for (id key in [strings subarrayWithRange:NSMakeRange(1, [strings count] - 2)]){
                value = [value objectForKey: key];
               
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
            [value setObject:tempValue forKey:[strings lastObject]];
            
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
    
    
    //TODO transform to list!!!
    if ([xml2agcDictionary objectForKey:elementName] && [[xml2agcDictionary objectForKey:elementName] isEqual:@"list"] ){
        
        
    }else {
      
        
        NSMutableDictionary *correctAttr = [NSKeyedUnarchiver unarchiveObjectWithData:[NSKeyedArchiver archivedDataWithRootObject: attributes[elementName]]];
;
        
       
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
                    
                    if ([tempValue intValue])
                        tempValue = [NSNumber numberWithInt:[tempValue intValue]];
                    
                    attributes[tempSaved] = tempValue;
                    correctAttr[key] = tempValue;
                    
                }
            }
        }
        
        [childDict addEntriesFromDictionary:correctAttr];
    }
    
    if ([xml2agcDictionary objectForKey:[inheritanceStack lastObject]] &&
        [[xml2agcDictionary objectForKey:[inheritanceStack lastObject]] isEqual: @"list"]){
        elementName = [[NSString alloc] initWithFormat:@"%d",counterCh++];
        id lastObject =  [NSKeyedUnarchiver unarchiveObjectWithData:[NSKeyedArchiver archivedDataWithRootObject: [dictionaryStack lastObject]]];
        
        
        if ([[inheritanceStack lastObject] isEqualToString: @"children1"])
            [childDict setObject:@"artboard" forKey:@"type"];
        
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
    
   
    
    //TODO replace all $"smth" values with default ones --> see how ?
    
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
        NSInteger length = tempReplace.length;
       
        NSArray *strings = [[xml2agcDictionary objectForKey:@"length."] componentsSeparatedByString:@"."];
        
        id value = parentDict;
        for (id key in [strings subarrayWithRange:NSMakeRange(1, [strings count] - 2)]){
            if ([value isKindOfClass:[NSMutableDictionary class]])
                value = [value objectForKey: key];
            else
                value = value[0][key][0][0]; // For lines only
            
        }
      
        [value setObject:[NSNumber numberWithInt:textValue.length] forKey:[strings lastObject]];
        
        
    }

    //default Values
    id def = [defaultValues objectForKey:elementName];
    for(id key in def){
        
        NSArray *strings = [key componentsSeparatedByString:@"."];
        NSString *firstTag = [[NSString alloc] initWithFormat:@"%@.", strings[0]];
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
        NSInteger counter = [dictionaryStack count];
        id prevParent = [dictionaryStack objectAtIndex:2]; // TODO hardcodare doar ptr un artboard!!!!
        
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
