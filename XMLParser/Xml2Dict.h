//
//  Xml2Dict.h
//  XDXCodeTranslator
//
//  Created by crogoz on 08/06/16.
//  Copyright © 2016 crogoz. All rights reserved.
//

#ifndef Xml2Dict_h
#define Xml2Dict_h

#import <Foundation/Foundation.h>

#include "Constants.h"
#include "Helper.h"

@interface Xml2Dict : NSObject
{
    /* array used for import; dictioanryStack[0] return the corresponding agc Dictionary; 
     * it is used as a stack */
    NSMutableArray *dictionaryStack;
    
    /* used for <string> smth <string> */
    NSMutableString *textInProgress;
    
    /* the id of the entry scene */
    NSString *homeArtboard;
}

/* where we find all external resources: eg. images */
@property NSString *resourcesPath;
@property NSString *xdPath;
@property NSString *xmlPath;
@property NSString *xmlContent;


/* returns the json representation of the storyboard file */
+ (NSDictionary *)dictionaryForXMLData:(NSData *)data  error:(NSError **)error;

/* returns the json representation of the storyboard file */
+ (NSDictionary *)dictionaryForXMLString:(NSString *)string error:(NSError **)error;

/* initializations */
- (NSDictionary *)objectWithData:(NSData *)data;

/* returns the entry scene in the XCode application */
- (NSString*) getHomeArtboard;

/* translates a tag and its attributes */
- (void)parser:(NSXMLParser *)parser didStartElement:(NSString *)elementName namespaceURI:(NSString *)namespaceURI qualifiedName:(NSString *)qName attributes:(NSDictionary *)attributeDict;

/* this method is called when a tag ends */
- (void)parser:(NSXMLParser *)parser didEndElement:(NSString *)elementName namespaceURI:(NSString *)namespaceURI qualifiedName:(NSString *)qName;

/* used for inline text */
- (void)parser:(NSXMLParser *)parser foundCharacters:(NSString *)string;

@end



#endif /* Xml2Dict_h */
