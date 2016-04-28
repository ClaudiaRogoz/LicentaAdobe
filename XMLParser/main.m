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
#import "Utils.h"
#include "Sync.h"


int main(int argc, const char * argv[]) {
    
    /* TODO for -i => import <importProj> <XDFile> */
    /* TODO for -e => export <XDFile> <exportProj> */
    if (!strcmp(argv[1], HELP)) {
        NSLog(@"./XMLParser <pathToImportProject> <pathToExportProject>\n"
                "\n eg: <pathToImportProject> = ~/Desktop/<ImportProj>/<ImportProj>"
                "\n eg: <pathToImportProject> = ~/Desktop/<ExportProj>/<ExportProj>");
        return 0;
    }
    
    
    NSString *xdPath = @"/Users/crogoz/SampleSync.xd";
    
    NSString *inXmlPath= [NSString stringWithFormat:@"%s", argv[1]];
    NSString *importPath = pathFormat(&inXmlPath, argv[1]);
    
    
    NSData *parser = [NSData dataWithContentsOfFile:importPath];
    
    NSString *outXmlPath= [NSString stringWithFormat:@"%s", argv[2]];
    NSString *exportPath = pathFormat(&outXmlPath, argv[2]);
    
    // Parse the XML into a dictionary
    NSError *parseError = nil;
    [XMLReader dictionaryForXMLData:parser resources:inXmlPath xdPath:xdPath outFile:importPath error:&parseError];
    
    
    /* copy <agc file> to clipboard */
    NSPasteboard *pasteboard = [NSPasteboard generalPasteboard];
    [pasteboard clearContents];
    NSPasteboardItem *clipboardItem = [[NSPasteboardItem alloc] init];
    NSString *mainBundle = getProjHomePath();
   
    NSString *outFile = [NSString stringWithFormat:@"%@/.%@", mainBundle, ARTBOARDXML];
    [clipboardItem setData:[NSData dataWithContentsOfFile:outFile] forType:SPARKLERCLIPBOARD];
    [pasteboard writeObjects:[NSArray arrayWithObject:clipboardItem]];
    
   
    /* generate storyboard for xcode from xd */
    [XMLGenerator readTemplateUsingXML:[NSString stringWithFormat:@"%@", outXmlPath] writeTo:exportPath];
    
    NSLog(@"-----Start sync");
    [Sync startSync:xdPath];
    
    /* open export xcode project */
    openExportProject(outXmlPath);
    
    /* Notify the user to  Drag & Drop resources */
    openDragDropPanel(outXmlPath);
    
   
    
    return 0;
}
