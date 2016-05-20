//
//  Sync.m
//  XMLParser
//
//  Created by crogoz on 20/04/16.
//  Copyright © 2016 crogoz. All rights reserved.
//

#import "Sync.h"
#include <CommonCrypto/CommonDigest.h>

@import AppKit;

const NSString *xmlScene = @"<scene";
const NSString *xmlEndScene = @"</scene";

@implementation Sync


+ (void) startSync:(NSString *) path withXcode:(NSString *) xmlPath {
    NSError *error;
    Sync *sync = [[Sync alloc] initWithError:&error];
    [sync initSync: xmlPath];
    [sync monitorXDFile:path];
}

- (id)initWithError:(NSError **)error
{
    return self;
}

- (void) initSync:(NSString*) xmlFile
{
    NSError *error;
    NSBundle *thisBundle = [NSBundle bundleForClass:[self class]];
    NSString *mainBundle = [self getProjHomePath];
    NSString *hashFile = [NSString stringWithFormat:@"%@/.%@/%@%@%@",mainBundle, PREV_ART_PATH, HASH_PATH, DOT, JSON];
    NSString *offsetFile = [NSString stringWithFormat:@"%@/.%@/%@%@%@",mainBundle, PREV_ART_PATH, OFFSET_PATH, DOT, JSON];
    NSString *def = [thisBundle pathForResource:AGC_TEMPLATE ofType:JSON];
    NSData *defData = [NSData dataWithContentsOfFile:def];
    NSData *hashData = [NSData dataWithContentsOfFile:hashFile];
    NSData *offsetData = [NSData dataWithContentsOfFile:offsetFile];
    arrayOfScenes = [[NSMutableArray alloc] init];
    exportAgc = [[NSMutableDictionary alloc] init];
    
    xmlContent = [NSString stringWithContentsOfFile:xmlFile encoding:NSUTF8StringEncoding error:&error];

    xmlHeader = [[NSString alloc] init];
    xmlFooter = [[NSString alloc] init];
    [self setXmlPath:xmlFile];
        hashArtboards = [NSJSONSerialization JSONObjectWithData:hashData options:NSJSONReadingMutableContainers error:&error];
        offsetArtboards = [NSJSONSerialization JSONObjectWithData:offsetData options:NSJSONReadingMutableContainers error:&error];
        int lastScene = (int)[[offsetArtboards allKeys] count];
        NSString * sceneStr = [NSString stringWithFormat:@"%d", lastScene];
        lastOffset = [[offsetArtboards objectForKey:sceneStr] longValue];
    
    [offsetArtboards removeObjectForKey:sceneStr];
    NSString *firstScene = [NSString stringWithFormat:@"1"];
    unsigned long firstOffset = [[offsetArtboards objectForKey:firstScene] longValue];
    unsigned long xmlSize = [xmlContent length];
    
    xmlHeader = [xmlContent substringWithRange:NSMakeRange(0, firstOffset)];
    xmlFooter = [xmlContent substringWithRange:NSMakeRange(lastOffset, xmlSize - lastOffset)];
    NSLog(@"Header %@\nFooter %@------------------------------------\n", xmlHeader, xmlFooter);
    attributes = [NSJSONSerialization JSONObjectWithData:defData options:NSJSONReadingMutableContainers error:&error];
    
    /* TODO read from rules (inverted rules maybe) */
    exportAgc[@"shape"] = [[NSMutableDictionary alloc] init];
    
    exportAgc[@"shape"][@"path"] = [[NSMutableArray alloc] init ];
    [exportAgc[@"shape"][@"path"] addObject:@"style.fill.type.solid"];
    [exportAgc[@"shape"][@"path"] addObject:@"shape.type.path"];
    
    exportAgc[@"shape"][@"rectangle"] = [[NSMutableArray alloc] init];
    [exportAgc[@"shape"][@"rectangle"] addObject:@"style.fill.type.solid" ];
    [exportAgc[@"shape"][@"rectangle"] addObject:@"shape.type.rect"];
    
    exportAgc[@"shape"][@"imageView"] = @"style.fill.type.pattern";
    exportAgc[@"group"] = [[NSArray alloc] init];
    
    exportAgc[@"text"] = @"textField";
    
    
}

-(NSString *) getProjHomePath {
    
    NSString *mainBundle = [[NSBundle mainBundle] bundlePath];
    for (int i = 0; i< PROJ_PATH; i++) {
        mainBundle = [mainBundle stringByDeletingLastPathComponent];
    }
    return mainBundle;
}

-(void) unzipXD:(NSString *)path atPath:(NSString*) unzipped_xd {
    
    NSError *error;
    
    if ([[NSFileManager defaultManager] fileExistsAtPath:unzipped_xd])
        [[NSFileManager defaultManager] removeItemAtPath:unzipped_xd error:&error];
    
    [[NSFileManager defaultManager] createDirectoryAtPath:unzipped_xd withIntermediateDirectories:NO attributes:nil error:&error];
    
    NSTask *task = [[NSTask alloc] init];
    task.launchPath = UNZIP_PATH;
    task.arguments = @[path];
    task.currentDirectoryPath=unzipped_xd;
    
    [task launch];
    [task waitUntilExit];
    
}

-(id) gotoAttribute:(NSMutableDictionary *) dict rules:(NSString *) rule {

    NSArray *array = [rule componentsSeparatedByString:DOT];
    id tempDict = dict;
    
    for (id key in array) {
        if ([tempDict isKindOfClass:[NSDictionary class]])
            tempDict = [tempDict objectForKey:key];
        else tempDict = [tempDict objectAtIndex:[key intValue]];
    
    }
    return tempDict;

}

-(NSMutableDictionary *) serializeFromPath:(NSString *)filePath {
    
    NSError *error;
    NSString *jsonString = [[NSString alloc] initWithContentsOfFile:filePath encoding:NSUTF8StringEncoding error:NULL];
    
    return [NSJSONSerialization JSONObjectWithData:[jsonString dataUsingEncoding:NSUTF8StringEncoding] options:NSJSONReadingMutableContainers error:&error];
}

-(BOOL) isArtboard:(NSURL *)urlF {
    
    return (![[[urlF path] lastPathComponent] isEqualToString:DS_STORE]);

}
-(NSString *) artboardHeader:(int) i {
    return [NSString stringWithFormat:@"%@%d", ART_SCENE, i+1];

}

-(NSDictionary *) getArtboardNo:(int) i forDict:(NSDictionary *)dict{
    
    return [dict objectForKey:[self artboardHeader:i]];

}

-(void) mergeDict:(NSDictionary **)dict withHeaderDict:(NSDictionary *) header artboardNo:(int) i{

    id tempDict = *dict;
    
    NSMutableDictionary *artboardInfo = [[NSMutableDictionary alloc] init];
    
    [artboardInfo setObject:header forKey:[self artboardHeader:i]];
    [tempDict setObject:artboardInfo forKey:ARTBOARDS];
    
}

-(NSString*) computeSha1:(NSString*)input
{
    const char *cstr = [input cStringUsingEncoding:NSUTF8StringEncoding];
    NSData *data = [NSData dataWithBytes:cstr length:input.length];
    
    uint8_t digest[CC_SHA1_DIGEST_LENGTH];
    
    CC_SHA1(data.bytes, (CC_LONG)data.length, digest);
    
    NSMutableString* output = [NSMutableString stringWithCapacity:CC_SHA1_DIGEST_LENGTH * 2];
    
    for(int i = 0; i < CC_SHA1_DIGEST_LENGTH; i++)
        [output appendFormat:@"%02x", digest[i]];
    
    return output;
    
}

- (void) writeXmlString:(NSString*) xmlString {
    
    NSError *err;
    
    NSData *data = [xmlString dataUsingEncoding:NSUTF8StringEncoding];
    
    NSXMLDocument *doc = [[NSXMLDocument alloc] initWithData:data options:NSXMLDocumentTidyXML error:&err];
    NSData* xmlData = [doc XMLDataWithOptions:NSXMLNodePrettyPrint];
    if ([self xmlPath])
        [xmlData writeToFile:[self xmlPath] atomically:YES];
    

}

- (void) updateXmlFile {
    
    NSString *finalXml = xmlHeader;
   // NSLog(@"Updating... %@", xmlHeader);
    unsigned long offset;
    for (int i= 0; i < [arrayOfScenes count]; i++) {
        offset = [finalXml length];
        //NSLog(@"Length = %lu", offset);
        NSString *iStr = [NSString stringWithFormat:@"%d", i];
        NSString *xmlScene = [arrayOfScenes objectAtIndex:i];
        [shaList setValue:[self computeSha1:xmlScene] forKey:iStr] ;
        [offsetArtboards setObject:[NSNumber numberWithLong:offset]forKey:iStr];
        finalXml = [finalXml stringByAppendingString:xmlScene];
        
        
    }
    lastOffset = [finalXml length];
    finalXml = [finalXml stringByAppendingString:xmlFooter];
    //NSLog(@"finalXml = %@", finalXml);
    [self writeXmlString:finalXml];
    
}

-(void) replacePrevArtboard:(NSMutableDictionary *)newArtboards no:(int)nr {
    NSError *error;
    
    NSString *artboardName = [NSString stringWithFormat:@"%@/%@%d%@%@",PREV_ART_PATH, ARTBOARD_FILE_PREFIX, nr, DOT, AGC];
    NSData *jsonData = [NSJSONSerialization dataWithJSONObject:newArtboards
                                                       options:NSJSONWritingPrettyPrinted
                                                         error:&error];
    
    NSString *jsonString = [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
    [jsonString writeToFile:artboardName atomically:YES encoding:NSUTF8StringEncoding error:nil];
    
}

-(void) processArtboardPairs:(NSMutableArray *)filesInit enumerator:(NSDirectoryEnumerator *) enumeratorF agcinfo:(NSMutableDictionary *) jsonArtboards {
    
    NSString *resource = [filesInit lastObject];
    [filesInit removeLastObject];
    NSMutableDictionary *jsonHeader = [[self serializeFromPath:resource] objectForKey:ARTBOARDS];
    NSError *error;
    NSString *mainBundle = [self getProjHomePath];
    NSStringEncoding encoding;
    int nr = -1;
    
    for (id newArtboards in filesInit) {
        /*compute hash & find hash entry in hashArtboards */
        /*goto artboard (found in hashArtboard) & check contentsAreEqual */
        /*just copy from teh corresponding offset into xml */
        nr ++;
        
        
        NSString *content = [NSString stringWithContentsOfFile:newArtboards usedEncoding:&encoding error:&error];
        NSString *jsonHash = [self computeSha1:content];
        NSLog(@"content");
        if (hashArtboards && [hashArtboards objectForKey:jsonHash]) {
            int prevArtNo = [[hashArtboards objectForKey:jsonHash] intValue];
            long prevArtOffset = [[offsetArtboards objectForKey:[NSNumber numberWithInt:prevArtNo]] longValue];
            long nextArtOffset;
            id nextOffset = [offsetArtboards objectForKey:[NSNumber numberWithInt:prevArtNo + 1]];
            
            if (nextOffset)
                nextArtOffset = [nextOffset longValue];
            else {
                nextArtOffset = lastOffset;
                
            }
            
            NSString *prevArtboard = [NSString stringWithFormat:@"%@/.%@/%@%d%@%@", mainBundle, PREV_ART_PATH, ARTBOARD_FILE_PREFIX, nr, DOT, AGC];
            if ([[NSFileManager defaultManager] contentsEqualAtPath:prevArtboard andPath:newArtboards]) {
                /*copy from prev_artboard to newStoryboard the currentScene */
                //NSLog(@"Just Copy Artboard");
                NSString *substr = [xmlContent substringWithRange:NSMakeRange(prevArtOffset, nextArtOffset - prevArtOffset)];
                [arrayOfScenes insertObject:substr atIndex:nr];
                continue;
            }
        }
        
        NSMutableDictionary *jsonDict = [self serializeFromPath:newArtboards];
        [self mergeDict:&jsonDict withHeaderDict:[self getArtboardNo:nr forDict:jsonHeader] artboardNo:nr];
        
        NSString *xcodeString = [XD2XCode generateXmlForTag:jsonDict];
        //NSLog(@"XcodeStr = %@", xcodeString);
        //TODO
        NSLog(@"NewArtboards = %@", jsonDict);
        [self replacePrevArtboard:jsonDict no:nr];
        [arrayOfScenes insertObject:xcodeString atIndex:nr];
    }
}


- (BOOL) isResourcesPath:(NSString*) path {
    for (int i = 0; i< 2; i++) {
    
        path = [path stringByDeletingLastPathComponent];
    }
    
    return ( [[path lastPathComponent] caseInsensitiveCompare:RESOURCES] == NSOrderedSame);

}

- (void) findChangesForPath:(NSString *)unzipped_xd {
    
    NSString *mainBundle = [self getProjHomePath];
    NSError *error;
    NSURL *directoryURLF = [NSURL fileURLWithPath:[mainBundle stringByAppendingPathComponent:[NSString stringWithFormat:@".%@", PREV_ART_PATH]]];
    NSURL *directoryURLI = [NSURL fileURLWithPath:unzipped_xd];
    NSString *pathToArtboardAgc = [unzipped_xd stringByAppendingPathComponent: GRAPHIC_CONTENT ];
    NSString *jsonString = [[NSString alloc] initWithContentsOfFile:pathToArtboardAgc encoding:NSUTF8StringEncoding error:NULL];
    NSMutableDictionary *jsonArtboards = [NSJSONSerialization JSONObjectWithData:[jsonString dataUsingEncoding:NSUTF8StringEncoding] options:NSJSONReadingMutableContainers error:&error];
    
    jsonArtboards = [jsonArtboards objectForKey:ARTBOARDS];
    
    widthAgcArtboard = [[[jsonArtboards objectForKey:FIRST_ARTBOARD] objectForKey:WIDTH] intValue];
    heightAgcArtboard = [[[jsonArtboards objectForKey:FIRST_ARTBOARD]  objectForKey:HEIGHT] intValue];
    
    NSArray *keys = [NSArray arrayWithObject:NSURLIsDirectoryKey];
    
    NSDirectoryEnumerator *enumeratorI = [[NSFileManager defaultManager]
                                          enumeratorAtURL:directoryURLI
                                          includingPropertiesForKeys:keys
                                          options:0
                                          errorHandler:^(NSURL *url, NSError *error) {
                                              return YES;
                                          }];
    
    NSDirectoryEnumerator *enumeratorF = [[NSFileManager defaultManager]
                                          enumeratorAtURL:directoryURLF
                                          includingPropertiesForKeys:keys
                                          options:0
                                          errorHandler:^(NSURL *url, NSError *error) {
                                              return YES;
                                          }];
    
    NSMutableArray *filesInit = [[NSMutableArray alloc] init];
    NSString *resourcesPath;
    
    for (NSURL *urlI in enumeratorI) {
        
        NSError *error;
        NSNumber *isDirectory = nil;
        if (! [urlI getResourceValue:&isDirectory forKey:NSURLIsDirectoryKey error:&error]) {
            // handle error
        }
        else if (! [isDirectory boolValue]) {
            
            if ([[[[urlI path] componentsSeparatedByString:@"/"] lastObject] isEqualToString:GRAPHIC]) {
                if ([self isResourcesPath:[urlI path]])
                    resourcesPath = [NSString stringWithString:[urlI path]];
                else
                    [filesInit addObject:[urlI path]];
            }
        }
        
    }
    [filesInit addObject:resourcesPath];
    [self processArtboardPairs:filesInit enumerator:enumeratorF agcinfo:jsonArtboards];
    
}

- (void) monitorXDFile:(NSString*) path
{
    
    /* https://developer.apple.com/library/ios/documentation/General/Conceptual/ConcurrencyProgrammingGuide/GCDWorkQueues/GCDWorkQueues.html */
    const char *pathString = [path cStringUsingEncoding:NSASCIIStringEncoding];
    int fildes = open(pathString, O_RDONLY);

    dispatch_queue_t queue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
    
    __block dispatch_source_t source = dispatch_source_create(DISPATCH_SOURCE_TYPE_VNODE, fildes, DISPATCH_VNODE_DELETE | DISPATCH_VNODE_WRITE | DISPATCH_VNODE_EXTEND | DISPATCH_VNODE_ATTRIB | DISPATCH_VNODE_LINK | DISPATCH_VNODE_RENAME | DISPATCH_VNODE_REVOKE,
                                                              queue);
    
    dispatch_source_set_event_handler(source, ^
                                      {
                                          unsigned long flags = dispatch_source_get_data(source);
                                     
                                          if(flags & DISPATCH_VNODE_DELETE)
                                          {
                                              [self monitorXDFile:path];
                                              
                                          }
                                          else {

                                              /* creates an unzip directory of the current XD project (**changes have been made ) */
                                              arrayOfScenes = [[NSMutableArray alloc] init];
                                              NSString *mainBundle = [self getProjHomePath];
                                              NSString *unzipped_xd = [mainBundle stringByAppendingPathComponent:XD_UNZIP_PATH];
                                              
                                              [self unzipXD:path atPath:unzipped_xd];
                                              
                                              [self findChangesForPath:(NSString *)unzipped_xd];
                                              NSLog(@"[Sync DONE]");
                                              [self updateXmlFile];
                                          }
                                      });
    
    dispatch_source_set_cancel_handler(source, ^(void)
                                       {
                                         
                                           close(fildes);
                                       });
    dispatch_resume(source);
    
}


@end
