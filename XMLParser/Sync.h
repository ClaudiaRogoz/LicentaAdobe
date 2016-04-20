//
//  Sync.h
//  XMLParser
//
//  Created by crogoz on 20/04/16.
//  Copyright © 2016 crogoz. All rights reserved.
//

#ifndef Sync_h
#define Sync_h

#import <Foundation/Foundation.h>
#import "Constants.h"

@interface Sync : NSObject
{
    /**
     *  temp variable used for textField/label;
     * we have to propagate the text name for lower tags
     * TODO: integrate in attributes
     **/
    NSString *tempText;
    
    /* width/height of xcode artboards and xd artboards */
    int widthXMLArtboard;
    int heightXMLArtboard;
    int widthAgcArtboard;
    int heightAgcArtboard;
    
    /**
     * json template for agc elements written as a mutableDictionary
     **/
    NSMutableDictionary *attributes;
    
    NSData *xmlData;
    
    /**
     * rules needed for agc2xml export;
     * using these rules we obtain the type of the agc element
     **/
    NSMutableDictionary *exportAgc;
    
    /**
     * offsets of tags in the xml file; needed for sync
     **/
    NSMutableDictionary *offsetXmlFile;
    
    /**
     *  which objects to monitor;
     *  used for sync
     **/
    NSMutableDictionary *objectOffset;
    
}

@property NSString *xmlPath;



/**
 *  sync algorithm; monitors a file given as parameter
 *  PARAMS:
 *      path:   the path for the xd file
 **/
- (void) monitorXDFile:(NSString*) path;

/**
 *  compares 2 Artboards;
 *  returns $diff (as a dictionary) between the old dictioanry and the new dictionary
 *  PARAMS:
 *      first: old dictionary
 *      second: new dictionary
 *      jsonArtboards: template dictioanry
 *      offsetGroupDict:   offset dictionary
 **/
- (NSMutableDictionary*) compare2Artboards:(NSArray *) first dict2:(NSArray *) second artboard_info:(NSMutableDictionary *)jsonArtboards offsetGroup:(NSMutableDictionary *)offsetGroupDict numberGroup:(NSNumber *) nr;

/**
 *  checks whether 2 dictionaries are equal; the difference is given as a
 * dictionary in `trList` variable
 **/
- (bool) checkAreEqual:(NSDictionary *)prev prevDict:(NSDictionary *)newD attr:(NSDictionary*)currAttr outList:(NSMutableDictionary**)trList equal:(BOOL) eq json_info:(NSDictionary *) jsonInfo;


/**
 *  updates the XML file with the modified values
 *  used for sync
 *  PARAMS:
 *      tags: dictionary with variables and their equivalent values
 *      tagNo: the number of the current scene
 *      offset_scene: the updated offsets after the modifications
 **/
- (void) updateXMLfile:(NSDictionary *)tags tagNo:(NSNumber *)n offsetScene:(NSNumber **) offset_scene;

/**
 *  merges an xml tag with it's subtags;
 *  used for sync
 **/
- (NSString *) appendModifiedString:(NSMutableDictionary *)dict minTagOffset:(NSNumber **)tagOffset;


@end

#endif /* Sync_h */
