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
    NSMutableDictionary *header;
    NSMutableArray* artboards;
    BOOL insertedRoot;
    int counterArtboards;
    int counterCh;
    
    
}

@property NSString *resourcesPath;

+ (NSDictionary *)dictionaryForXMLData:(NSData *)data resources:(NSString*)resourcesDir error:(NSError **)errorPointer;
+ (NSDictionary *)dictionaryForXMLString:(NSString *)string error:(NSError **)errorPointer;
+ (NSMutableArray *)splitArtboards:(NSDictionary *)dictionary;
+ (void) writeToFile:(NSDictionary*)dict file:(NSString*) fileName;
+ (void) monitorXDFile:(NSString*) path;
+ (int) compare2Artboards:(NSDictionary*) first dict2:(NSDictionary *) second;

@end
