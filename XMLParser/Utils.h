//
//  Utils.h
//  XMLParser
//
//  Created by crogoz on 20/04/16.
//  Copyright © 2016 crogoz. All rights reserved.
//
#include "Sync.h"

#ifndef Utils_h
#define Utils_h

#define DEBUG 1

#ifdef DEBUG
#       define DLog(fmt, ...) NSLog((@"%s [Line %d] " fmt), __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__);
#else
#       define DLog(...)
#endif

NSString * getProjHomePath() {
    
    NSString *mainBundle = [[NSBundle mainBundle] bundlePath];
    for (int i = 0; i< PROJ_PATH; i++) {
        mainBundle = [mainBundle stringByDeletingLastPathComponent];
    }
    return mainBundle;
}

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
    task.launchPath = OPEN_PATH;
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
        
    }
    
}

void import(char *path) {
    
    NSString *inXmlPath= [NSString stringWithFormat:@"%s", path];
    NSString *importPath = pathFormat(&inXmlPath, path);
    NSData *parser = [NSData dataWithContentsOfFile:importPath];
    
    // Parse the XML into a dictionary
    NSError *parseError = nil;
    [XMLReader dictionaryForXMLData:parser resources:inXmlPath outFile:importPath error:&parseError];
    
    
    /* copy <agc file> to clipboard */
    NSPasteboard *pasteboard = [NSPasteboard generalPasteboard];
    [pasteboard clearContents];
    NSPasteboardItem *clipboardItem = [[NSPasteboardItem alloc] init];
    NSString *mainBundle = getProjHomePath();
    
    NSString *outFile = [NSString stringWithFormat:@"%@/.%@", mainBundle, ARTBOARDXML];
    [clipboardItem setData:[NSData dataWithContentsOfFile:outFile] forType:SPARKLERCLIPBOARD];
    [pasteboard writeObjects:[NSArray arrayWithObject:clipboardItem]];
    
}

void export(char *path) {
    
    NSString *outXmlPath= [NSString stringWithFormat:@"%s", path];
    NSString *exportPath = pathFormat(&outXmlPath, path);
    
    /* generate storyboard for xcode from xd */
    [XMLGenerator readTemplateUsingXML:[NSString stringWithFormat:@"%@", outXmlPath] writeTo:exportPath];
    /* open export xcode project */
    openExportProject(outXmlPath);
    
    /* Notify the user to  Drag & Drop resources */
    openDragDropPanel(outXmlPath);
}

void synch(char *XDPath, char *XMLPath) {
    NSString * xdPath= [NSString stringWithFormat:@"%s", XDPath];
    NSString * xmlPath= [NSString stringWithFormat:@"%s", XMLPath];
    [Sync startSync:xdPath withXcode:xmlPath];
}

void printOptions() {
    
    NSLog(@"\nUsage:\n\t./XDXCodeTranslator [arguments] [file paths ..]\n"
          "\n\n\t./XDXCodeTranslator -i <pathToXCodeProject>\n\t\ttranslates an XCode project into an XD project;"
          "The XD info is put in Clipboard;\n\t\t the XD file will be updated using Cmd+V"
          "\n\n\t./XDXCodeTranslator -e <pathToExportProject>\n\t\ttranslates an XD project into an XCode project;"
          "The XD info is put into ClipBoard (using Cmd+V).\n\t\t Using this command, the XD is translated into Xcode;"
          "\nArguments:\n"
          "\n\t-h\t\tPrint help message (this message) and exit"
          "\n\t-i\t\tImports an XCode project path given as argument (eg. ~/<XcodeProjectName>/<XcodeProjectName>)"
          "\n\t-e\t\tExports an XD project to an XCode project. \n\t\tThe Xcode project is given as an argument."
          "\n\t\t(eg. ~/<XcodeProjectName>/<XcodeProjectName>)"
          "\n eg: <pathToProject> = ~/Desktop/<ImportProj>/<ImportProj>\n");
}

#endif /* Utils_h */
