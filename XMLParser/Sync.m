//
//  Sync.m
//  XMLParser
//
//  Created by crogoz on 20/04/16.
//  Copyright © 2016 crogoz. All rights reserved.
//

#import "Sync.h"

@import AppKit;

@implementation Sync


+ (void) startSync:(NSString *) path {
    NSError *error;
    Sync *sync = [[Sync alloc] initWithError:&error];
    [sync initSync];
    [sync monitorXDFile:path];
    
}

- (id)initWithError:(NSError **)error
{
    return self;
}

- (void) initSync
{
    NSError *error;
    NSBundle *thisBundle = [NSBundle bundleForClass:[self class]];
    NSString *def = [thisBundle pathForResource:AGC_TEMPLATE ofType:JSON];
    NSData *defData = [NSData dataWithContentsOfFile:def];
    
    exportAgc = [[NSMutableDictionary alloc] init];
    offsetXmlFile = [[NSMutableDictionary alloc] init];
    objectOffset = [[NSMutableDictionary alloc] init];
   
    attributes = [NSJSONSerialization JSONObjectWithData:defData options:NSJSONReadingMutableContainers error:&error];
    
    /* TODO read from rules */
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
    
    objectOffset[@"<scene"] = [NSNumber numberWithInt: 1];
    
    
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

-(void) processArtboardPairs:(NSMutableArray *)filesInit enumerator:(NSDirectoryEnumerator *) enumeratorF agcinfo:(NSMutableDictionary *) jsonArtboards {
    int i = 0;
    
    for (NSURL *urlF in enumeratorF) {
        NSError *error;
        NSNumber *isDirectory = nil;
        if (! [urlF getResourceValue:&isDirectory forKey:NSURLIsDirectoryKey error:&error]) {
            // handle error
        }
        else if (! [isDirectory boolValue] &&
                 ![[[urlF path] lastPathComponent] isEqualToString:@".DS_Store"]) {
            
            if ([[NSFileManager defaultManager] contentsEqualAtPath:[urlF path] andPath:[filesInit objectAtIndex:i]])
                continue;
            
            NSLog(@"TODO at %d generate xml code", i);
            
            /* update file */
            NSMutableDictionary *jsonDict = [self serializeFromPath:[filesInit objectAtIndex:i]];
            //TODOTren [self mergeDict:jsonDict withHeaderDict:]
            NSLog(@"JsonDict = %@", jsonDict);
            NSString *xcodeString = [XMLGenerator generateXmlForTag:jsonDict];
            NSLog(@"XcodeStr = %@", xcodeString);
            ++i;
            
        }
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
    
    [self processArtboardPairs:filesInit enumerator:enumeratorF agcinfo:jsonArtboards];
    
}

- (void) monitorXDFile:(NSString*) path
{
    
    const char *pathString = [path cStringUsingEncoding:NSASCIIStringEncoding];
    int fildes = open(pathString, O_RDONLY);
    NSLog(@"Filedes = %d", fildes);
    dispatch_queue_t queue = dispatch_get_global_queue(0, 0);
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
                                              NSString *mainBundle = [self getProjHomePath];
                                              NSString *unzipped_xd = [mainBundle stringByAppendingPathComponent:XD_UNZIP_PATH];
                                              
                                              [self unzipXD:path atPath:unzipped_xd];
                                              
                                              [self findChangesForPath:(NSString *)unzipped_xd];
                                          }
                                      });
    
    dispatch_source_set_cancel_handler(source, ^(void)
                                       {
                                           close(fildes);
                                       });
    dispatch_resume(source);
    
}


@end
