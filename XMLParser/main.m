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


int main(int argc, const char * argv[]) {
    
    /* TODO for -i => import <importProj> <XDFile> */
    /* TODO for -e => export <XDFile> <exportProj> */
    if (!strcmp(argv[1], HELP)) {
        printOptions();
        return 0;
    
    }else if (!strcmp(argv[1], IMPORT)) {
        import((char*)argv[2]);
    
    }else if (!strcmp(argv[1], EXPORT)) {
        export((char*)argv[2]);
    
    }else if (!strcmp(argv[1], SYNC)) {
        synch((char *)argv[2]);
        
    }else {
        NSLog(@"Wrong options");
        printOptions();
    }
    
    return NSApplicationMain(argc, argv);
}
