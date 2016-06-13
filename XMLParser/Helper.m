//
//  Helper.m
//  XDXCodeTranslator
//
//  Created by crogoz on 19/05/16.
//  Copyright © 2016 crogoz. All rights reserved.
//

#import <Foundation/Foundation.h>
#include "Helper.h"

@implementation Helper


+ (NSString *) getProjHomePath {
    
    NSString *mainBundle = [[NSBundle mainBundle] bundlePath];
    for (int i = 0; i< PROJ_PATH; i++) {
        mainBundle = [mainBundle stringByDeletingLastPathComponent];
    }
    return mainBundle;
}

+ (NSString*) computeSha1:(NSString*)input {
    const char *cstr = [input cStringUsingEncoding:NSUTF8StringEncoding];
    NSData *data = [NSData dataWithBytes:cstr length:input.length];
    
    uint8_t digest[CC_SHA1_DIGEST_LENGTH];
    
    CC_SHA1(data.bytes, (CC_LONG)data.length, digest);
    
    NSMutableString* output = [NSMutableString stringWithCapacity:CC_SHA1_DIGEST_LENGTH * 2];
    
    for(int i = 0; i < CC_SHA1_DIGEST_LENGTH; i++)
        [output appendFormat:@"%02x", digest[i]];
    
    return output;
    
}

+ (id) deepCopy:(id) object {
    
    return [NSKeyedUnarchiver unarchiveObjectWithData:[NSKeyedArchiver archivedDataWithRootObject: object]];
    
}

+ (NSMutableArray *) findAllFiles: (NSString *)name inPath:(NSString *) initPath {
    
    NSMutableArray *allFiles = [[NSMutableArray alloc] init];
    NSFileManager *fileManager = [NSFileManager defaultManager];
    NSString *directory = initPath;;
    
    NSURL *directoryURL = [NSURL fileURLWithPath:directory];
    NSArray *keys = [NSArray arrayWithObject:NSURLIsDirectoryKey];
    
    NSDirectoryEnumerator *enumerator = [fileManager
                                         enumeratorAtURL:directoryURL
                                         includingPropertiesForKeys:keys
                                         options:0
                                         errorHandler:^(NSURL *url, NSError *error) {
                                             // Handle the error.
                                             // Return YES if the enumeration should continue after the error.
                                             return YES;
                                         }];
    
    for (NSURL *url in enumerator) {
        NSError *error;
        NSNumber *isDirectory = nil;
        if (! [url getResourceValue:&isDirectory forKey:NSURLIsDirectoryKey error:&error]) {
            // handle error
        }
        else if (! [isDirectory boolValue]) {
            if ([[[url path] lastPathComponent] isEqualToString:name])
                [allFiles addObject: [url path]];
        }
    }
    
    return allFiles;


}

+ (NSString *) getImagePath:(NSString *) name inDirectory:(NSString *)directory {
    
    /* get file path from the pbxproj file */
    NSError *error;
    NSString *rootPath = [directory stringByDeletingLastPathComponent];
    NSArray *dirFiles = [[NSFileManager defaultManager] contentsOfDirectoryAtPath:rootPath error:nil];
    NSString *xcodeProj = [[dirFiles filteredArrayUsingPredicate:[NSPredicate predicateWithFormat:@"self ENDSWITH '.xcodeproj'"]] firstObject];
    rootPath = [rootPath stringByAppendingPathComponent:xcodeProj];
    dirFiles = [[NSFileManager defaultManager] contentsOfDirectoryAtPath:rootPath error:nil];
    NSString *pbxProj = [[dirFiles filteredArrayUsingPredicate:[NSPredicate predicateWithFormat:@"self ENDSWITH '.pbxproj'"]] firstObject];
    NSString *projPath = [rootPath stringByAppendingPathComponent:pbxProj];
    NSString *str = [NSString stringWithContentsOfFile:projPath encoding:NSUTF8StringEncoding error:&error];
    NSString *searchPath = [NSString stringWithFormat:@"%@%@%@", PBXPROJ_IMAGE_NAME, name, PBXPROJ_IMAGE_PATH];
    NSRange imagePath = [str rangeOfString:searchPath];
    if (imagePath.length == 0) {
        return rootPath;
    }
    unsigned long length = [searchPath length] + imagePath.location;
    NSRange endPath = [str rangeOfString:DELIMITER options:0 range:NSMakeRange(length, [str length] - length)];
    NSString *path = [str substringWithRange:NSMakeRange(length, endPath.location - length)];
    int prev_times = 0;
    /*the path is relative to the pbxproj file => transform to absolute path*/
    imagePath = [path rangeOfString:PREV_PATH];
    while (imagePath.location != NSNotFound) {
        path = [path substringFromIndex:imagePath.location + [PREV_PATH length]];
        prev_times++;
        imagePath = [path rangeOfString:PREV_PATH];
        rootPath = [rootPath stringByDeletingLastPathComponent];
    }
    
    path = [rootPath stringByAppendingPathComponent:path];
    
    return path;
}

+ (NSString *)findFile:(NSString *)name inPath:(NSString *) initPath
{
    NSFileManager *fileManager = [NSFileManager defaultManager];
    NSString *directory = initPath;;
    
    NSURL *directoryURL = [NSURL fileURLWithPath:directory];
    NSArray *keys = [NSArray arrayWithObject:NSURLIsDirectoryKey];
    
    NSDirectoryEnumerator *enumerator = [fileManager
                                         enumeratorAtURL:directoryURL
                                         includingPropertiesForKeys:keys
                                         options:0
                                         errorHandler:^(NSURL *url, NSError *error) {
                                             // Handle the error.
                                             // Return YES if the enumeration should continue after the error.
                                             return YES;
                                         }];
    
    for (NSURL *url in enumerator) {
        NSError *error;
        NSNumber *isDirectory = nil;
        if (! [url getResourceValue:&isDirectory forKey:NSURLIsDirectoryKey error:&error]) {
            // handle error
        }
        else if (! [isDirectory boolValue]) {
            if ([[[url path] lastPathComponent] isEqualToString:name])
                return [url path];
        }
    }
    
    /* get file path from the pbxproj file */
    
    return [self getImagePath:name inDirectory:directory];
}

+ (void) addShaForString:(NSString *)jsonString artboardNo:(int)nr hash:(NSMutableDictionary *) hashArtboards {
    
    NSString *jsonSha = [self computeSha1:jsonString];
    [hashArtboards setObject:[NSNumber numberWithInt:nr] forKey:jsonSha];
    
}

+ (void) writeToFile:(NSDictionary*)xmlDictionary file:(NSString*) file computeSha:(int)sha
                hash:(NSMutableDictionary *) hashArtboards {
    
    NSError *error;
    NSData *jsonData = [NSJSONSerialization dataWithJSONObject:xmlDictionary
                                                       options:NSJSONWritingPrettyPrinted
                                                         error:&error];
    
    if (! jsonData) {
        NSLog(@"Got an error: %@", error);
    } else {
        NSString *jsonString = [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
        
        NSString *mainBundle = [self getProjHomePath];
        
        
        NSString *outFile = [NSString stringWithFormat:@"%@/.%@", mainBundle, file];
        
        [[NSFileManager defaultManager] createFileAtPath:outFile contents:nil attributes:nil];
        [jsonString writeToFile:outFile atomically:YES encoding:NSUTF8StringEncoding error:nil];
        if (sha != -1) {
            [self addShaForString:jsonString artboardNo:sha hash:hashArtboards];
        }
    }
}

+ (BOOL) checkPathExists:(NSString *) absolutePath {
    
    return [[NSFileManager defaultManager] fileExistsAtPath:absolutePath];

}

+ (void) createXdFile:(NSString *) xdPath {
    
    NSTask *task = [[NSTask alloc] init];
    task.launchPath = ZIP_PATH;
    task.arguments = @[ZIP_RECURSIVE, ZIP_DIR, xdPath, ZIP_ARTWORK, ZIP_INTERACTIONS, ZIP_META, ZIP_MIME, ZIP_RESOURCES, ZIP_MANIFEST];
    task.currentDirectoryPath=[xdPath stringByDeletingLastPathComponent];
    
    [task launch];
    [task waitUntilExit];

}

+ (NSString *) convertSvgToPng:(NSString *) svgName withFill:(NSString *) hexColor strokeColor:(NSString *) stroke strokeWidth:(int )strokeWidth {

    NSString *pngName = [[svgName stringByDeletingPathExtension] stringByAppendingPathExtension:PNG];
    NSTask *task = [[NSTask alloc] init];
    
    task.launchPath = @"/usr/local/bin/convert";
    NSString *fillColor = [NSString  stringWithFormat:@"#%@", hexColor];
    if (![hexColor isEqualToString:NONE])
        task.arguments = @[CONVERT_DENSITY, CONVERT_VALUE, CONVERT_FILL, fillColor, CONVERT_BKG, CONVERT_NONE, svgName, pngName];
    else
        task.arguments = @[CONVERT_DENSITY, CONVERT_VALUE, CONVERT_FILL, NONE, CONVERT_STROKE, [NSString  stringWithFormat:@"#%@", stroke], CONVERT_WIDTH, [NSString stringWithFormat:@"%d", strokeWidth], CONVERT_BKG, CONVERT_NONE, svgName, pngName];
    [task launch];
    [task waitUntilExit];
    
    NSLog(@"[Task done] Export png at %@ %hhd", pngName, [[NSFileManager defaultManager] fileExistsAtPath:pngName]);
    
    return pngName;

}

+ (NSString *) convertSvgLineToPng:(NSString *) svgName withFill:(NSString *) hexColor{
    
    NSString *pngName = [[svgName stringByDeletingPathExtension] stringByAppendingPathExtension:PNG];
    NSTask *task = [[NSTask alloc] init];
    
    task.launchPath = @"/usr/local/bin/convert";
    task.arguments = @[CONVERT_BKG, CONVERT_NONE, CONVERT_FILL, [NSString  stringWithFormat:@"#%@", hexColor],svgName, pngName];
    
    [task launch];
    [task waitUntilExit];
    
    NSLog(@"[Task done] Export png at %@ %hhd", pngName, [[NSFileManager defaultManager] fileExistsAtPath:pngName]);
    
    return pngName;
    
}

+ (NSArray *)splitVariable:(NSString *)varName delimitator:(NSString *) variable {
    
    if ([varName hasPrefix:TOCHOOSE]) {
        return [[varName substringFromIndex:1] componentsSeparatedByString:TOCHOOSE];
    }
    
    return [NSArray arrayWithObjects:varName, nil];


}

+ (NSArray *)splitVariableForDot:(NSString *)varName {
    return [varName componentsSeparatedByString:DOT];
}

+ (NSArray *) splitVariable:(NSString*) varName {
    
    if ([varName hasPrefix:@"$"]) {
        return [[varName substringFromIndex:1] componentsSeparatedByString:@"."];
    }
    
    return [NSArray arrayWithObjects:varName, nil];
    
}

+ (NSArray *) getArrayProperties:(NSString *) property {
    return [property componentsSeparatedByString:DOT];
}

+ (id) getValueForProperties:(NSArray *) properties inDict:(NSDictionary *)dict {
    id value = dict;
    for (id property in properties) {
        value = [value objectForKey:property];
    }
    return value;
}

+ (void) unzipXD:(NSString *)path atPath:(NSString*) unzipped_xd {
    
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

@end
