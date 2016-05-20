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

- (void) setMetaDataDate:(NSString *) path {
    
    NSError *error;
    NSArray *modifyDates = @[CREATEDATE, MODIFYDATE, METADATADATE, WHENDATE];
    NSString *timeStamp = [self createTimeStamp];
    NSString *template = [[NSBundle mainBundle] pathForResource:[METADATA stringByDeletingPathExtension] ofType:XML];
    
    //read File into Str
    NSString *metaInfo = [NSString stringWithContentsOfFile:template encoding:NSUTF8StringEncoding error:NULL];
    
    //modify timeStamp &
    for (id date in modifyDates) {
        NSRange range = [metaInfo rangeOfString:date];
        if (range.location == NSNotFound) {
            NSLog(@"[ERROR] Word not found");
            return;
        }
        
        for(int i = 0; i< range.length; i++) {
            int offset = (int)[date length];
            [metaInfo stringByReplacingCharactersInRange:NSMakeRange(range.location + offset + 2, 1) withString:timeStamp];
        
        }
    }
    
    [metaInfo writeToFile:path atomically:YES encoding:NSUTF8StringEncoding error:&error];
    
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

    [xdc setMetaDataDate:metaInfoContent];
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