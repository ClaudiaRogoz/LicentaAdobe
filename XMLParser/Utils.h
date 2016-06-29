//
//  Utils.h
//  XMLParser
//
//  Created by crogoz on 20/04/16.
//  Copyright © 2016 crogoz. All rights reserved.
//
#import <QuartzCore/QuartzCore.h>
#import <Cocoa/Cocoa.h>
#import <Foundation/Foundation.h>
#import <CommonCrypto/CommonDigest.h>
#include <sys/event.h>
#include <sys/time.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#include "Sync.h"
#import "XCode2XD.h"
#import "XD2XCode.h"
#import "Xml2Dict.h"
#import "Dict2Agc.h"

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

void printOptions() {
    
    NSLog(@"\nUsage:\n\t./XDXCodeTranslator [arguments] [file paths ..]\n"
          "\n\n\t./XDXCodeTranslator -i <pathToXCodeProject> <pathToXdFile>\n\t\ttranslates an XCode project into an XD project;"
          "The XD info is put in Clipboard;\n\t\t the XD file will be updated using Cmd+V"
          "\n\n\t./XDXCodeTranslator -e <pathToExportProject>\n\t\ttranslates an XD project into an XCode project;If -nosync parameter is specified, then no synchronization will be made; otherwise, XD->XCode projects will synchronize (whenever the xd file is modified, the modifications will be seen in th XCode project; XCode->XD sync is not available)"
          "The XD info is put into ClipBoard (using Cmd+V).\n\t\t Using this command, the XD is translated into Xcode;"
          "\nArguments:\n"
          "\n\t-h\t\tPrint help message (this message) and exit"
          "\n\t-i\t\tImports an XCode project path given as argument (eg. ~/<XcodeProjectName>/<XcodeProjectName>)\n\t\tpathToXdFile=absolute path to an existing xd file or a new one."
          "\n\t-e\t\tExports an XD project to an XCode project. \n\t\tThe Xcode project is given as an argument."
          "\n\t\t(eg. ~/<XcodeProjectName>/<XcodeProjectName>)"
          "\n eg: <pathToProject> = ~/Desktop/<ImportProj>/<ImportProj>\n");
}


void openExportProject(NSString *outXmlPath) {
    
    NSString *nameXcodeProj = [[outXmlPath lastPathComponent] stringByAppendingPathExtension:XCODEPROJ];
    NSString *pathToXcodeProj = [[outXmlPath stringByDeletingLastPathComponent] stringByAppendingPathComponent:nameXcodeProj];
    NSTask *task = [[NSTask alloc] init];
    task.launchPath = OPEN_PATH;
    task.arguments = @[pathToXcodeProj];
    [task launch];
    [task waitUntilExit];
}

void openXdFile(NSString *outXDPath) {
    NSTask *task = [[NSTask alloc] init];
    task.launchPath = OPEN_PATH;
    task.arguments = @[outXDPath];
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

NSString* resolvePath(NSString *path) {
    
    NSString *expandedPath = [[path stringByExpandingTildeInPath] stringByStandardizingPath];
    const char *cpath = [expandedPath cStringUsingEncoding:NSUTF8StringEncoding];
    char *resolved = NULL;
    char *returnValue = realpath(cpath, resolved);
    if (returnValue == NULL && resolved != NULL) {
        printf("Error with path: %s\n", resolved);
        return nil;
    }
    return [NSString stringWithCString:returnValue encoding:NSUTF8StringEncoding];
}

NSString* sanityCheck(NSString *inXDPath) {
    while ([Helper fileExists:inXDPath]) {
        NSLog(@"[WARNING] The XD project %@ exists. Do you want to override it? [y/n]", inXDPath);
        NSFileHandle *kbd = [NSFileHandle fileHandleWithStandardInput];
        NSData *inputData = [kbd availableData];
        NSString *option = [[[NSString alloc] initWithData:inputData
                                                  encoding:NSUTF8StringEncoding] substringToIndex:1];
        if ([option isEqualToString:@"y"])
            break;
        else {
            NSLog(@"Please provide another xdPath:\n");
            char cstring[40];
            scanf("%s", cstring);
            inXDPath = [NSString stringWithCString:cstring encoding:1];
            if ([inXDPath hasPrefix:@"~"]) {
                inXDPath  = resolvePath(inXDPath);
            }
        }
    }
    return inXDPath;
}

void import(char *path, char *xdPath, bool withSync) {
    
    CFTimeInterval startTime = CACurrentMediaTime();
    NSString *inXmlPath= [NSString stringWithFormat:@"%s", path];
    NSString *inXDPath = [NSString stringWithFormat:@"%s", xdPath];
    NSString *importPath = pathFormat(&inXmlPath, path);
    NSData *parser = [NSData dataWithContentsOfFile:importPath];
    if (!parser) {
        NSLog(@"[ERROR] import path is not valid");
        printOptions();
        return;
    }
    inXDPath = sanityCheck(inXDPath);
    NSLog(@"Output XD File = %@", inXDPath);
    /* Parse the XML into a dictionary */
    NSError *parseError = nil;
    NSDictionary *xmlDictionary = [Xml2Dict dictionaryForXMLData:parser error:&parseError];
    CFTimeInterval elapsedTime = CACurrentMediaTime() ;
    NSLog(@"[XML2Dict DONE] Time elapsed: %f", elapsedTime - startTime);
    
    NSMutableArray *offset = [xmlDictionary objectForKey:SCENE_TAG];
    NSString *homeArtboard = [xmlDictionary objectForKey:HOME_ARTBOARD];
    if (homeArtboard == nil) {
        NSLog(@"[ERROR] No intial View controller! Please set one and try again");
        return;
    }
    NSMutableDictionary*shaList = [Dict2Agc processDict:[xmlDictionary mutableCopy] error:&parseError usingXdPath:inXDPath xmlDirectory:inXmlPath homeArtboard:homeArtboard];
    elapsedTime = CACurrentMediaTime() - elapsedTime;
    NSLog(@"[Import DONE] Time elapsed: %f", elapsedTime);
    openXdFile(inXDPath);
    if (withSync)
        [Sync startSync:inXDPath withXcode:importPath offsetList:offset shaList:shaList];
}

void export(char *xdPath, char *xmlPath) {
    
    CFTimeInterval startTime = CACurrentMediaTime();
    NSString *inXdPath = [NSString stringWithFormat:@"%s", xdPath];
    NSString *outXmlPath= [NSString stringWithFormat:@"%s", xmlPath];
    NSString *exportPath = pathFormat(&outXmlPath, xmlPath);
    BOOL exists = [[NSFileManager defaultManager] fileExistsAtPath:exportPath];
    if (!exists) {
        NSLog(@"[ERROR] export path is not valid");
        printOptions();
        return;
    }
  
    [XD2XCode readTemplateUsingXML:inXdPath writeTo:exportPath];
    CFTimeInterval elapsedTime = CACurrentMediaTime() - startTime;
    NSLog(@"[Export DONE] Time elapsed: %f", elapsedTime);
    /* open export xcode project */
    openExportProject(outXmlPath);
    /* Notify the user to  Drag & Drop resources */
    openDragDropPanel(outXmlPath);
}

void synch(char *XDPath, char *XMLPath) {
}

#endif /* Utils_h */
