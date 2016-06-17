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
#import "XD2XCode.h"

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
    
    /*dictionary containing mappings between artboards and their shas*/
    NSMutableDictionary *hashArtboards;
    
     /*dictionary containing mappings between scenes
      * and their offset (in the xml file )*/
    NSMutableArray *offsetArtboards;
    
    /**
     * json template for agc elements written as a mutableDictionary
     **/
    NSMutableDictionary *attributes;
    NSMutableDictionary *tempHash;
    
    /**
     * rules needed for agc2xml export;
     * using these rules we obtain the type of the agc element
     **/
    NSMutableDictionary *exportAgc;
    NSMutableArray *arrayOfScenes;
    NSString *xmlContent;
    NSString *xmlHeader;
    NSString *xmlFooter;
    
}

@property NSString *xmlPath;
@property NSString *xmlDir;
@property NSString *xdPath;

+ (void) startSync:(NSString *) path withXcode:(NSString *) xmlPath offsetList:(NSMutableArray *)offset shaList:(NSMutableDictionary *)shaList;
/**
 *  sync algorithm; monitors a file given as parameter
 *  PARAMS:
 *      path:   the path for the xd file
 **/
- (void) monitorXDFile:(NSString*)path with:(NSString *)xmlPath;

@end

#endif /* Sync_h */
