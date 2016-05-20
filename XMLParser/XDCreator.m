//
//  XDCreator.m
//  XDXCodeTranslator
//
//  Created by crogoz on 19/05/16.
//  Copyright © 2016 crogoz. All rights reserved.
//
#include "XDCreator.h"
#include "Helper.h"

@import AppKit;


@implementation XDCreator

- (NSString *) createTimeStamp {
    
    NSDateFormatter *formatter;
    
    formatter = [[NSDateFormatter alloc] init];
    [formatter setDateFormat:@"yyyy-MM-dd'T'HH:mm:ss'.830+03:00'"];
    
    return [formatter stringFromDate:[NSDate date]];

}

- (NSString *) generateUniqueId {
    return [[NSUUID UUID] UUIDString];

}

- (int) getRangeofString:(NSString *) search inString:(NSString *) init  offset:(int) offset {
    

    NSRange range = [init rangeOfString:search
                                options:0
                                  range:NSMakeRange(offset, [init length]- offset)];
    
    if (range.location == NSNotFound) {
        NSLog(@"[ERROR] %@ not found", search);
        return - 1;
    }
    
    return (int)range.location;

}

- (NSString *) replaceString:(NSString *) repStr inString:(NSString *) metaInfo usingSearchArray:(NSArray *) array lastObject:(BOOL) lastObject {
    
    int range = 0;
    int counter = 0;
    XDCreator *xdc = [[XDCreator alloc] init];
    
    for (id date in array) {
        counter ++;
        range = [xdc getRangeofString:date inString:metaInfo offset:range + 1];
        int offset = (int)[date length];
        
        if (lastObject && counter != [array count])
            continue;
        
        metaInfo = [metaInfo stringByReplacingCharactersInRange:NSMakeRange(range + offset + 1, 1) withString:repStr];
        
    }
    
    return metaInfo;
    
}

- (void) generateMetaInf:(NSString *) documentID instance:(NSString *) instanceID path:(NSString *) path {
   
    NSError *error;
    NSArray *modifyDates = @[CREATEDATE, MODIFYDATE, METADATADATE, WHENDATE, WHENDATE];
    NSArray *uniqIds = @[DOC_ID, ORIG_LID, INSTANCE_ID];
    NSArray *instanceIds = @[INST_ID];
    NSString *timeStamp = [self createTimeStamp];
    NSString *template = [[NSBundle mainBundle] pathForResource:META_TEMPLATE ofType:XML];
    NSString *metaInfo = [NSString stringWithContentsOfFile:template encoding:NSUTF8StringEncoding error:NULL];

    metaInfo = [self replaceString:timeStamp inString:metaInfo usingSearchArray:modifyDates lastObject:false];
    metaInfo = [self replaceString:documentID inString:metaInfo usingSearchArray:uniqIds lastObject:false];
    metaInfo = [self replaceString:instanceID inString:metaInfo usingSearchArray:instanceIds  lastObject:false];
    metaInfo = [self replaceString:instanceID inString:metaInfo usingSearchArray:@[INSTANCE_ID, INSTANCE_ID] lastObject:true];
    
    [metaInfo writeToFile:path atomically:YES encoding:NSUTF8StringEncoding error:&error];

}

- (void) processTemplate:(id*)template usingArtboards:(NSMutableDictionary *) dict {

    NSError *error;

    if ([*template isKindOfClass:[NSDictionary class]]) {
        for (id key in [*template allKeys]) {
            id value = [*template objectForKey:key];
            if ([value isKindOfClass:[NSString class]]){
                if ([value isEqualToString:TOTRANSFORM]) {
                        [*template setObject:[self generateUniqueId] forKey:key];
                    
                } else if ([value hasPrefix:FILE_SIZE]) {
                    NSString *dirName = [value substringFromIndex:[FILE_SIZE length] + 1];
                    NSString *dirStr = [[[self xdPath] stringByDeletingLastPathComponent] stringByAppendingPathComponent:dirName];
                    NSString *contentsAtPath = [[[NSFileManager defaultManager] contentsOfDirectoryAtPath:dirStr error:&error] lastObject];
                    NSString *fullPath = [dirStr stringByAppendingPathComponent:contentsAtPath];
                    unsigned long long fileSize = [[[NSFileManager defaultManager] attributesOfItemAtPath:fullPath error:nil] fileSize];
                    [*template setObject:[NSNumber numberWithLong:fileSize] forKey:key];
                }
            } else {
                [self processTemplate:&value usingArtboards:dict];
            }
        }
        
    } else if ([*template isKindOfClass:[NSArray class]]) {
        for(id key in *template) {
            id tempKey = key;
            [self processTemplate:&tempKey usingArtboards:dict];
        }
    }
    
}

- (void) generateManifest:(NSString *) documentID path:(NSString *) path dict:(NSMutableDictionary *) dict {
    
    NSError *error;
    NSString *tempName = [[NSBundle mainBundle] pathForResource:MANIFEST ofType:JSON];
    NSData *data = [NSData dataWithContentsOfFile:tempName];
    NSMutableDictionary *template = [NSJSONSerialization JSONObjectWithData:data options:NSJSONReadingMutableContainers error:&error];
    [template setObject:documentID forKey:ID];
    id temp = [template objectForKey:CHILDREN];
    [self processTemplate:&temp usingArtboards:dict];
    NSLog(@"Temp = %@", temp);
    
}

- (void) setMetaData:(NSString *) path manifest:(NSString *) manifest dict:dict{
    

    NSString *document = [self generateUniqueId];
    NSString *instance = [self generateUniqueId];

    [self generateMetaInf:document instance:instance path:path];
    [self generateManifest:document path:manifest dict:dict];
    
    
}

- (NSDictionary *) readResourcesFile {
    NSError *error;
    NSString *resourceValue = [[NSBundle mainBundle] pathForResource:RESOURCESDICT ofType:JSON];
    NSLog(@"Resources = %@", resourceValue);
    NSString *jsonString = [NSString stringWithContentsOfFile:resourceValue encoding:NSUTF8StringEncoding error:&error];
    NSData * jsonData = [jsonString dataUsingEncoding:NSUTF8StringEncoding];

    return [NSJSONSerialization JSONObjectWithData:jsonData options:0 error:&error];
 
}

+ (void) writeData:(NSMutableDictionary *) dict toPath:(NSString *) path {
    
    NSError *error;
    NSData *jsonData = [NSJSONSerialization dataWithJSONObject:dict
                                                       options:NSJSONWritingPrettyPrinted
                                                         error:&error];
    
    if (! jsonData) {
        NSLog(@"Got an error: %@", error);
    } else {
        NSString *jsonString = [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
        
        [jsonString writeToFile:path atomically:YES encoding:NSUTF8StringEncoding error:nil];
    }
}

+ (NSString *) createStorage:(NSArray *) list usingXDPath:(NSString *)xdPath {
    
    
    NSMutableString *path = [[NSMutableString alloc] init];
    NSString *xdDir = [xdPath stringByDeletingLastPathComponent];
    NSError *error;
    BOOL success;
    
    [path setString:xdDir];
    for (id dir in list) {
        path = [[path stringByAppendingPathComponent:dir] mutableCopy];
        
        if (dir != [list lastObject]) {
            
            if (![[NSFileManager defaultManager] fileExistsAtPath:path]) {
                NSLog(@"Creating dir .... %@", path);
                success = [[NSFileManager defaultManager] createDirectoryAtPath:path
                                                    withIntermediateDirectories:NO
                                                                     attributes:nil
                                                                          error:&error];
            }
            else success = true;
            
        } else {
            NSLog(@"Creating path .... %@", path);
            success = [[NSFileManager defaultManager] createFileAtPath:path contents:nil attributes:nil];
        }
        
        if (success == false) {
            NSLog(@"[ERROR] cannot create path %@", path);
            return nil;
        }
        
    }
    return path;
    
}

+ (void) createManifest:(NSMutableDictionary *) dict xdPath:(NSString *) xdPath {
    
    NSArray *manifestFile = @[MANIFEST];
    NSArray *metaInfo = @[META_INF, METADATA];
    NSString *manifestContent = [self createStorage:manifestFile usingXDPath:xdPath];
    NSString *metaInfoContent = [self createStorage:metaInfo usingXDPath:xdPath];
    
    XDCreator *xdc = [[XDCreator alloc] init];
    [xdc setXdPath:xdPath];
    [xdc setMetaData:metaInfoContent manifest:manifestContent dict:dict];
}

+ (void) createMimetype:(NSString *) xdPath {
    
    NSArray *resourcesList = @[MIMETYPE];
    NSError *error;

    NSString *graphicContent = [self createStorage:resourcesList usingXDPath:xdPath];
    
    [MIMETYPE_CONTENT writeToFile:graphicContent atomically:YES encoding:NSUTF8StringEncoding error:&error];
    
}

+ (void) createInteractionContent:(NSMutableDictionary *) interactions xdPath:(NSString *) xdPath {
    //TODO
    NSMutableDictionary *version = [@{VERSION : VERSION_INTERACTIONS} mutableCopy];
    NSString *jsonInteractions = [NSString stringWithFormat:@"%@%@%@", INTERACTIONS, DOT, JSON];
    NSArray *resourcesList = @[INTERACTIONS, jsonInteractions];

    NSString *graphicContent = [self createStorage:resourcesList usingXDPath:xdPath];
    
    [self writeData:version toPath:graphicContent];
}

+ (void) createResourcesContent:(NSMutableDictionary *) artboards xdPath:(NSString *) xdPath {
    
    NSLog(@"Artboards = %@", artboards);
    /*version, children = [], resources, meta, artboards = {.. + viewportHeight = viewSource.height}*/
    NSArray *resourcesList = @[RESOURCES, GRAPHICS, GRAPHIC];
    NSDictionary * dict = [[[XDCreator alloc] init] readResourcesFile];
    NSMutableDictionary *resDict = [[NSMutableDictionary alloc] init];
    [resDict setObject:VERSION_AGC forKey:VERSION];
    [resDict setObject:[[NSArray alloc] init] forKey:CHILDREN];
    if ([artboards objectForKey:RESOURCES])
        [resDict setObject:[artboards objectForKey:RESOURCES] forKey:RESOURCES];
    else
         [resDict setObject:dict forKey:RESOURCES];
    
    for (id artboard  in artboards) {
        NSLog(@"Artboard = %@", artboard);
        id value = [artboards objectForKey:artboard];
        [value setObject:[value objectForKey:HEIGHT] forKey:VIEWPORT];
    }
    
    [resDict setObject:artboards forKey:ARTBOARDS];

    NSString *graphicContent = [self createStorage:resourcesList usingXDPath:xdPath];
    
    [self writeData:resDict toPath:graphicContent];
}


/* receives an already split dictionary */
+ (void) createArtworkContent:(NSMutableDictionary *) artboard artboardNo:(int) artNo xdPath:(NSString *) xdPath {
    
    NSString *artWorkNo = [NSString stringWithFormat:@"%@%d", ARTBOARD_FILE_PREFIX, artNo];
    NSArray *resourcesList = @[ARTWORK, artWorkNo, GRAPHICS, GRAPHIC];
    NSDictionary *href = @{HREF : GRAPHIC_CONTENT};
    [artboard removeObjectForKey:VIEWSOURCE];
    [artboard removeObjectForKey:META];
    [artboard setObject:href forKey:ARTBOARDS];
    [artboard setObject:href forKey:RESOURCES];

    NSString *graphicContent = [self createStorage:resourcesList usingXDPath:xdPath];
    
    [self writeData:artboard toPath:graphicContent];
    
}

@end