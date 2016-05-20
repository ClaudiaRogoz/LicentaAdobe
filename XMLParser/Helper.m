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

@end
