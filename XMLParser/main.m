//
//  main.m
//  XMLParser
//
//  Created by crogoz on 05/03/16.
//  Copyright © 2016 crogoz. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#include <sys/event.h>
#include <sys/time.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#import "XMLReader.h"

int main(int argc, const char * argv[]) {
    
    NSString *file = [NSString stringWithFormat:@"%s", argv[1]];
    NSString *imageDir = [NSString stringWithFormat:@"%s", argv[2]];
    NSString *path = [[NSBundle mainBundle] pathForResource:file ofType:@"storyboard"];
    NSData *parser = [NSData dataWithContentsOfFile:file];
    NSString *string = [[NSString alloc] initWithData:parser encoding:NSUTF8StringEncoding] ;
    NSLog(@"String%@", string);
    // Parse the XML into a dictionary
    NSError *parseError = nil;
    NSDictionary *xmlDictionary = [XMLReader dictionaryForXMLData:parser resources:imageDir outFile:file error:&parseError];
    
    
    
    NSPasteboard *pasteboard = [NSPasteboard generalPasteboard];
    [pasteboard clearContents];
    NSPasteboardItem *clipboardItem = [[NSPasteboardItem alloc] init];
    NSString *hello = [NSString stringWithFormat:@"Hello"];
    [clipboardItem setData:[NSData dataWithContentsOfFile:@"/Users/crogoz/Documents/artboardF.agc"] forType:@"com.adobe.sparkler.design"];
    [pasteboard writeObjects:[NSArray arrayWithObject:clipboardItem]];
    /*NSError *error;
    NSData *jsonData = [NSJSONSerialization dataWithJSONObject:xmlDictionary
                                                       options:NSJSONWritingPrettyPrinted // Pass 0 if you don't care about the readability of the generated string
                                                         error:&error];
    
    if (! jsonData) {
        NSLog(@"Got an error: %@", error);
    } else {
        NSString *jsonString = [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
        
        NSArray *paths = NSSearchPathForDirectoriesInDomains
        (NSDocumentDirectory, NSUserDomainMask, YES);
        NSString *documentsDirectory = [paths objectAtIndex:0];
        NSString *outFile = [NSString stringWithFormat:@"%@/%@_out.agc", documentsDirectory, file];
        NSLog(@"Writing to file %@", outFile);
        [[NSFileManager defaultManager] createFileAtPath:outFile contents:nil attributes:nil];
        [jsonString writeToFile:outFile atomically:YES encoding:NSUTF8StringEncoding error:nil];
        
    }
    
    [XMLReader splitArtboards:xmlDictionary];

    //TDOD change the name of the file beeing watched!! ( parameter ? )
    [XMLReader monitorXDFile:@"/Users/crogoz/Documents/Y/UntitledY.xd"];*/

    return NSApplicationMain(argc, argv);
}
