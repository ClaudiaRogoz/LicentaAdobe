//
//  XMLReader.h
//  XMLParser
//
//  Created by crogoz on 05/03/16.
//  Copyright © 2016 crogoz. All rights reserved.
//


#import <Foundation/Foundation.h>
@import AppKit;


@interface XMLReader : NSObject
{
    NSMutableArray *dictionaryStack;
    NSMutableArray *inheritanceStack;
    NSMutableArray *toInsertObjects;
    NSMutableString *textInProgress;
    NSMutableDictionary *xml2agcDictionary;
    NSMutableDictionary *defaultValues;
    NSMutableDictionary *invertedDictionary;
    NSMutableDictionary *attributes;
    NSMutableDictionary *exportAgc;
    NSMutableArray *artboards;
    NSMutableDictionary *offsetXmlFile;
    NSMutableDictionary *objectOffset;
    
    int sceneNo;
    NSData *xmlData;
    int xmlOffset;
    
    BOOL insertedRoot;
    int counterArtboards;
    int counterCh;
    
    
}

@property NSString *resourcesPath;

+ (NSDictionary *)dictionaryForXMLData:(NSData *)data resources:(NSString*)resourcesDir outFile:(NSString *)out_file error:(NSError **)errorPointer;
+ (NSDictionary *)dictionaryForXMLString:(NSString *)string error:(NSError **)errorPointer;
+ (NSMutableArray *)splitArtboards:(NSDictionary *)dictionary;
+ (void) writeToFile:(NSDictionary*)dict file:(NSString*) fileName;
+ (void) monitorXDFile:(NSString*) path;
- (NSMutableDictionary*) compare2Artboards:(NSArray *) first dict2:(NSArray *) second;
- (bool) checkAreEqual:(NSDictionary *)prev prevDict:(NSDictionary *)newD attr:(NSDictionary*)currAttr outList:(NSMutableDictionary**)trList equal:(BOOL) eq;
- (void) updateXMLfile:(NSDictionary*)tags tagNo:(NSNumber *)n;

@end
