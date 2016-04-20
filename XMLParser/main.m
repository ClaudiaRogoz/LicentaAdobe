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
#import "XMLGenerator.h"
#include "Constants.h"

int main(int argc, const char * argv[]) {
    
    
    NSString *tmpPath = [NSString stringWithFormat:@"%s", argv[1]];
    NSString *xmlPath;
    if ([tmpPath hasSuffix:@"/"])
        xmlPath = [NSString stringWithFormat:@"%s%@", argv[1], STORYBOARD];
    else {
        tmpPath = [tmpPath stringByAppendingString:@"/"];
        xmlPath = [NSString stringWithFormat:@"%s/%@", argv[1], STORYBOARD];
    }
    
    NSString *xdPath = @"/Users/crogoz/Documents/Y/UntitledY.xd";//[NSString stringWithFormat:@"%s", argv[3]];
    
    NSData *parser = [NSData dataWithContentsOfFile:xmlPath];
   
    // Parse the XML into a dictionary
    NSError *parseError = nil;
    [XMLReader dictionaryForXMLData:parser resources:tmpPath xdPath:xdPath outFile:xmlPath error:&parseError];
    
    
    /* copy <agc file> to clipboard */
    NSPasteboard *pasteboard = [NSPasteboard generalPasteboard];
    [pasteboard clearContents];
    NSPasteboardItem *clipboardItem = [[NSPasteboardItem alloc] init];
   
    NSArray *paths = NSSearchPathForDirectoriesInDomains
    (NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documentsDirectory = [paths objectAtIndex:0];
    NSString *outFile = [NSString stringWithFormat:@"%@/%@", documentsDirectory, ARTBOARDXML];
    [clipboardItem setData:[NSData dataWithContentsOfFile:outFile] forType:SPARKLERCLIPBOARD];
    [pasteboard writeObjects:[NSArray arrayWithObject:clipboardItem]];
 
    
    [XMLGenerator readTemplateUsingXML:[NSString stringWithFormat:@"%@", tmpPath]];

    return NSApplicationMain(argc, argv);
}
