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
    /* translation schema between agc and xml
     * it is read from Defs_Dict.json */
    NSMutableDictionary *agcToXmlTemplate;
    
    /* translation between xml_tag_name and agc_element_name
     * it is read from Rules_Dict.json
     **/
    NSMutableDictionary *translationDict;
    
    /* dictionary that maps attributes that need to be changed
     * eg. x, y (absolute <=> relative)
     **/
    NSMutableDictionary *transformObjects;
    
    /* entry = <source_id, destination_id> ; used for processing segues; */
    NSMutableDictionary *interactionsDict;
    
    NSMutableDictionary *idMapping;
    NSMutableArray *sceneList;
    
    /* used for assets whose type is temporary (starts with "$")*/
    NSString *changeType;
    
    /* current scene number */
    int sceneNo;
    
    /* child number within the scene */
    int childNo;
    
    /* offsets & sizes for the scenes */
    int startXArtboard;
    int startYArtboard;
    int widthArtboard;
    int heightArtboard;
    
    float imageHeightScalefactor;
    float lastWidth;
    float lastHeight;
    NSString *lastId;
    
    /* entry scene (id) */
    NSString *homeArtboard;
    
    float imageFind;
}

/* where we find all external resources: eg. images */
@property NSString *resourcesPath;
@property NSString *xdPath;
@property NSString *xmlPath;
@property NSString *homeId;

/* given a dictionary obtained from Dict2Agc module, this function returns the xml representation (storyboard) */
+ (id)processDict:(NSMutableDictionary *)dictionary  error:(NSError **)error usingXdPath:(NSString *) xdPath xmlDirectory:(NSString *) xmlPath homeArtboard:(NSString *)homeArtboard;

@end

#endif /* Dict2Agc_h */
