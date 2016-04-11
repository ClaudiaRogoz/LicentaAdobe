//
//  XMLGenerator.h
//  XMLParser
//
//  Created by crogoz on 07/04/16.
//  Copyright © 2016 crogoz. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  Parses AGC code; Generates XML tags for XCODE
 **/

@interface XMLGenerator : NSObject
{
    /* translation schema between agc and xml 
     * it is read from Defs.json */
    NSMutableDictionary *agcToXmlTemplate;
    
    /* translation between xml_tag_name and agc_element_name
     * it is read from Rules.json
     **/
    NSMutableDictionary *translationDict;
    //NSMutableDictionary *uniqueIds;
    
    /* current scene_number == artboard_number */
    int sceneNo;
}

/* agc & xml file paths */
@property NSString *xmlPath;
@property NSString *agcPath;


- (id)initWithError:(NSError **)error;

+ (void)readTemplate;

@end


