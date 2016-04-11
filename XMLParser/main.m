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

int main(int argc, const char * argv[]) {
    
   
    NSString *xmlPath = [NSString stringWithFormat:@"%s", argv[1]];
    NSString *imageDir = [NSString stringWithFormat:@"%s", argv[2]];
    NSString *xdPath = @"/Users/crogoz/Documents/Y/UntitledY.xd";//[NSString stringWithFormat:@"%s", argv[3]];

    NSData *parser = [NSData dataWithContentsOfFile:xmlPath];
    NSString *string = [[NSString alloc] initWithData:parser encoding:NSUTF8StringEncoding] ;
    NSLog(@"String%@", string);
    // Parse the XML into a dictionary
    NSError *parseError = nil;
    [XMLReader dictionaryForXMLData:parser resources:imageDir xdPath:xdPath outFile:xmlPath error:&parseError];
    
    
    /* copy <agc file> to clipboard */
    NSPasteboard *pasteboard = [NSPasteboard generalPasteboard];
    [pasteboard clearContents];
    NSPasteboardItem *clipboardItem = [[NSPasteboardItem alloc] init];
   // NSString *hello = [NSString stringWithFormat:@"Hello"];
    NSArray *paths = NSSearchPathForDirectoriesInDomains
    (NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documentsDirectory = [paths objectAtIndex:0];
    NSString *outFile = [NSString stringWithFormat:@"%@/%@", documentsDirectory, ARTBOARDXML];
    [clipboardItem setData:[NSData dataWithContentsOfFile:outFile] forType:SPARKLERCLIPBOARD];
    [pasteboard writeObjects:[NSArray arrayWithObject:clipboardItem]];
    
   /* NSXMLElement *root = [[NSXMLElement alloc] initWithName:@"Request"];
    [root addAttribute:[NSXMLNode attributeWithName:@"Attribute1" stringValue:@"Value1"]];
    [root addAttribute:[NSXMLNode attributeWithName:@"Attribute2" stringValue:@"Value2"]];
    [root addAttribute:[NSXMLNode attributeWithName:@"Attribute3" stringValue:@"Value3"]];
    NSString *ns = [NSString stringWithFormat:@"%@", root];
    NSLog(@"NS = %@", ns);*/
 
    
    //[XMLGenerator readTemplate];

    return NSApplicationMain(argc, argv);
}
