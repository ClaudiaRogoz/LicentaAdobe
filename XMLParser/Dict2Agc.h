//
//  Dict2Agc.h
//  XDXCodeTranslator
//
//  Created by crogoz on 08/06/16.
//  Copyright © 2016 crogoz. All rights reserved.
//

#ifndef Dict2Agc_h
#define Dict2Agc_h

#import <Foundation/Foundation.h>

#include "Constants.h"
#include "Helper.h"
#import "XDCreator.h"

@interface Dict2Agc : NSObject
{
    NSMutableDictionary *agcToXmlTemplate;
    NSMutableDictionary *translationDict;
    NSMutableDictionary *transformObjects;
    
    NSMutableDictionary *interactionsDict;
    NSMutableDictionary *idMapping;
    NSMutableArray *sceneList;
    NSString *changeType;

    int sceneNo;
    int childNo;
    
    int startXArtboard;
    int startYArtboard;
    int widthArtboard;
    int heightArtboard;
    
    float imageHeightScalefactor;
    float lastWidth;
    float lastHeight;
    NSString *lastId;
    NSString *homeArtboard;
}

/* where we find all external resources: eg. images */
@property NSString *resourcesPath;
@property NSString *xdPath;
@property NSString *xmlPath;


+ (void)processDict:(NSMutableDictionary *)dictionary  error:(NSError **)error usingXdPath:(NSString *) xdPath xmlDirectory:(NSString *) xmlPath;

@end

#endif /* Dict2Agc_h */
