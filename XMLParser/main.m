//
//  main.m
//  XMLParser
//
//  Created by crogoz on 05/03/16.
//  Copyright © 2016 crogoz. All rights reserved.
//


#import "Utils.h"

int main(int argc, const char * argv[]) {
    
    if (!strcmp(argv[1], HELP)) {
        printOptions();
        return 0;
    
    }else if (!strcmp(argv[1], IMPORT)) {
        if (!strcmp(argv[2], NOSYNC))
            import((char*)argv[3], (char*)argv[4], false);
        else
            import((char*)argv[2], (char*)argv[3], true);
    
    }else if (!strcmp(argv[1], EXPORT)) {
            export((char*)argv[2], (char*)argv[3]);
    
    }else if (!strcmp(argv[1], SYNC)) {
        /*sync xdFile xcodeStoryboard */
        synch((char *)argv[2], (char *)argv[3]);
        
    }else {
        NSLog(@"[Error] Wrong options");
        printOptions();
    }
    
    return NSApplicationMain(argc, argv);
}
