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
#import "XMLGenerator.h"

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


+ (void) startSync:(NSString *) path;

/**
 *  sync algorithm; monitors a file given as parameter
 *  PARAMS:
 *      path:   the path for the xd file
 **/
- (void) monitorXDFile:(NSString*) path;



@end

#endif /* Sync_h */
