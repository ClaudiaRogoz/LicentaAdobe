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

NSString *pathFormat(NSString **path, const char *arg) {
    
    NSString *retPath;
    
    if ([*path hasSuffix:@"/"])
        retPath = [NSString stringWithFormat:@"%s%@", arg, STORYBOARD];
    else {
        *path = [*path stringByAppendingString:@"/"];
        retPath = [NSString stringWithFormat:@"%s/%@", arg, STORYBOARD];
    }
    
    return retPath;
}


void openExportProject(NSString * outXmlPath) {
    
    NSString *nameXcodeProj = [[outXmlPath lastPathComponent] stringByAppendingPathExtension:XCODEPROJ];
    NSString *pathToXcodeProj = [[outXmlPath stringByDeletingLastPathComponent] stringByAppendingPathComponent:nameXcodeProj];
    
    NSTask *task = [[NSTask alloc] init];
    task.launchPath = @"/usr/bin/open";
    task.arguments = @[pathToXcodeProj];
    
    [task launch];
    [task waitUntilExit];


}

void openDragDropPanel(NSString *outXmlPath) {

    NSOpenPanel *panel = [NSOpenPanel openPanel];
    [panel setCanChooseFiles:YES];
    [panel setCanChooseDirectories:YES];
    [panel setAllowsMultipleSelection:YES]; // yes if more than one dir is allowed
    [panel setDirectoryURL:[NSURL fileURLWithPath:[NSString stringWithFormat:@"%@%@", outXmlPath ,RESOURCES]]];
    NSInteger clicked = [panel runModal];
    
    if (clicked == NSFileHandlingPanelOKButton) {
        for (NSURL *url in [panel URLs]) {
            // do something with the url here.
        }
    }

}

int main(int argc, const char * argv[]) {
    
    /* TODO for -i => import <importProj> <XDFile> */
    /* TODO for -e => export <XDFile> <exportProj> */
    if (!strcmp(argv[1], HELP)) {
        NSLog(@"./XMLParser <pathToImportProject> <pathToExportProject>\n"
                "\n eg: <pathToImportProject> = ~/Desktop/<ImportProj>/<ImportProj>"
                "\n eg: <pathToImportProject> = ~/Desktop/<ExportProj>/<ExportProj>");
        return 0;
    }
    
    
    NSString *xdPath = @"/Users/crogoz/Documents/Y/UntitledY.xd";//[NSString stringWithFormat:@"%s", argv[3]];
    
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
    NSString *mainBundle = [[NSBundle mainBundle] bundlePath];
   
    NSString *outFile = [NSString stringWithFormat:@"%@/.%@", mainBundle, ARTBOARDXML];
    [clipboardItem setData:[NSData dataWithContentsOfFile:outFile] forType:SPARKLERCLIPBOARD];
    [pasteboard writeObjects:[NSArray arrayWithObject:clipboardItem]];
    
   
    /* generate storyboard for xcode from xd */
    [XMLGenerator readTemplateUsingXML:[NSString stringWithFormat:@"%@", outXmlPath] writeTo:exportPath];
    
    
    /* open export xcode project */
    openExportProject(outXmlPath);
    
    /* Notify the user to  Drag & Drop resources */
    openDragDropPanel(outXmlPath);
    
    return 0;
}
