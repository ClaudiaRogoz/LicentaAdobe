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
    NSMutableArray *dictionaryStack;
    NSMutableString *textInProgress;
    unsigned long offset;
    NSString *homeArtboard;
}

/* where we find all external resources: eg. images */
@property NSString *resourcesPath;
@property NSString *xdPath;
@property NSString *xmlPath;
@property NSString *xmlContent;

+ (NSDictionary *)dictionaryForXMLData:(NSData *)data  error:(NSError **)error;

@end



#endif /* Xml2Dict_h */
