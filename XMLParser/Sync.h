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

+(NSString*) computeSha1:(NSString*)input;

/* starts synchronization; reads the sha & the offset dictionaries; */
+ (void) startSync:(NSString *) path withXcode:(NSString *) xmlPath offsetList:(NSMutableArray *)offset shaList:(NSMutableDictionary *)shaList;

/*  sync algorithm; monitors a file given as parameter */
- (void) monitorXDFile;

/* gets all the "graphicContent.agc" files within an xd file */
- (void) findChangesForPath:(NSString *)unzipped_xd;

- (BOOL) isResourcesPath:(NSString*) path;

/* checks the scenes; if a scene is modified (its sha is not in the shaList), 
 * we generate the new xml representation  */
- (void) processArtboardPairs:(NSMutableArray *)filesInit agcinfo:(NSMutableDictionary *) jsonArtboards;

/* writes a dictionary to thye corresponding agc file */
- (void) replacePrevArtboard:(NSMutableDictionary *)newArtboards no:(int)nr;

/* creates the whole xml file; computes the sha & the new offsets*/
- (void) updateXmlFile;

/* writes a string to a file */
- (void) writeXmlString:(NSString*) xmlString;

/* creates the artboards dictionary */
- (void) mergeDict:(NSDictionary **)dict withHeaderDict:(NSDictionary *) header artboardNo:(int) i;

/* returns the dictionary that describes a scene */
- (NSDictionary *) getArtboardNo:(int)i forDict:(NSDictionary *)dict;

/* returns an artboard name */
- (NSString *) artboardHeader:(int) i;

/* checks whether the current url represents a scene */
- (BOOL) isArtboard:(NSURL *)urlF;

/* returns a dictionary representation for the json found in "filePath"*/
- (NSMutableDictionary *) serializeFromPath:(NSString *)filePath;

/* given a dictionary "dict" and a string (x1.x2. ... .xn) where x1, x2, ... , xn are keys in "dict"
 * returns the value corresponding to the last key (xn) in the dictionary
 **/
- (id) gotoAttribute:(NSMutableDictionary *) dict rules:(NSString *) rule;

/* calls unzip command for the xd file */
- (void) unzipXD:(NSString *)path atPath:(NSString*) unzipped_xd;

/* returns the main project's directory */
- (NSString *) getProjHomePath;

/* init method */
- (void) initSync:(NSString*) xmlFile shaList:(NSMutableDictionary *) shaList offsetList:(NSMutableArray *)offset;

- (id)initWithError:(NSError **)error;
@end

#endif /* Sync_h */
