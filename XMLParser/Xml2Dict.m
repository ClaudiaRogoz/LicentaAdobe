#import "Xml2Dict.h"

NSString *const kXMLReaderTextNodeKey = @"text";

@interface Xml2Dict (Internal)

- (id)initWithError:(NSError **)error;
- (NSDictionary *)objectWithData:(NSData *)data;

@end

@implementation Xml2Dict


+ (NSDictionary *)dictionaryForXMLData:(NSData *)data error:(NSError **)error
{
    Xml2Dict *reader = [[Xml2Dict alloc] initWithError:error];
    NSDictionary *rootDictionary = [reader objectWithData:data];
    NSLog(@"root = %@", rootDictionary);
    return rootDictionary;
}

+ (NSDictionary *)dictionaryForXMLString:(NSString *)string error:(NSError **)error
{
    NSData *data = [string dataUsingEncoding:NSUTF8StringEncoding];
    return [Xml2Dict dictionaryForXMLData:data error:error];
}


- (id)initWithError:(NSError **)error
{
    if (self = [super init])
    {

    }
    return self;
}

- (void)dealloc
{

}

- (NSDictionary *)objectWithData:(NSData *)data
{

    
    dictionaryStack = [[NSMutableArray alloc] init];
    textInProgress = [[NSMutableString alloc] init];

    [dictionaryStack addObject:[NSMutableDictionary dictionary]];
    
    // Parse the XML
    NSXMLParser *parser = [[NSXMLParser alloc] initWithData:data];
    parser.delegate = self;
    BOOL success = [parser parse];
    

    if (success)
    {
        NSDictionary *resultDict = [dictionaryStack objectAtIndex:0];
        return resultDict;
    }
    
    return nil;
}


- (void)parser:(NSXMLParser *)parser didStartElement:(NSString *)elementName namespaceURI:(NSString *)namespaceURI qualifiedName:(NSString *)qName attributes:(NSDictionary *)attributeDict
{

    NSLog(@"[%@]PartentDict = %@", elementName, [dictionaryStack lastObject]);
    id parentDict = [dictionaryStack lastObject];

    id childDict;
    
    if (![elementName isEqualToString:SUBVIEWS]) {
        childDict = [NSMutableDictionary dictionary];
        [childDict addEntriesFromDictionary:attributeDict];
        if ([parentDict isKindOfClass:[NSDictionary class]]) {
            if ([elementName isEqualToString:SCENE]) {
                id existingValue = [parentDict objectForKey:elementName];
                if (existingValue)
                {
                    NSMutableArray *array = nil;
                    if ([existingValue isKindOfClass:[NSMutableArray class]])
                    {
                        array = (NSMutableArray *) existingValue;
                    }
                    else
                    {
                        array = [NSMutableArray array];
                        [array addObject:existingValue];
                        
                        [parentDict setObject:array forKey:elementName];
                    }
                    [array addObject:childDict];
                } else {
                    [parentDict setObject:childDict forKey:elementName];
                
                }
            } else
                [parentDict setObject:childDict forKey:elementName];
        } else {
            id child = [[NSMutableDictionary alloc] init];
            [child setObject:childDict forKey:elementName];
            [parentDict addObject:child];

        }
    } else {
        childDict = [[NSMutableArray alloc] init];
        [parentDict setObject:childDict forKey:elementName];
    }
    
    

    [dictionaryStack addObject:childDict];
}

- (void)parser:(NSXMLParser *)parser didEndElement:(NSString *)elementName namespaceURI:(NSString *)namespaceURI qualifiedName:(NSString *)qName
{
    NSMutableDictionary *dict = [dictionaryStack lastObject];

    if ([textInProgress length] > 0)
    {

        [dict setObject:textInProgress forKey:@"text"];
        
        textInProgress = [[NSMutableString alloc] init];
    }

    [dictionaryStack removeLastObject];
}

- (void)parser:(NSXMLParser *)parser foundCharacters:(NSString *)string
{
    NSString *newString;
    if (string != nil) /* we have a string tag (multiline label)*/ {
        newString = [string stringByReplacingOccurrencesOfString:@"  " withString:@""];
        newString = [newString stringByReplacingOccurrencesOfString:@" " withString:@""];
        newString = [newString stringByReplacingOccurrencesOfString:@"\n" withString:@""];
        
        if ([newString length]) {
            
            [textInProgress appendString:string];
        }
        
    }

}

- (void)parser:(NSXMLParser *)parser parseErrorOccurred:(NSError *)parseError
{


}

@end