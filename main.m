//
//  main.m
//  XMLParser
//
//  Created by crogoz on 05/03/16.
//  Copyright © 2016 crogoz. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "XMLReader.h"

int main(int argc, const char * argv[]) {
    
    NSString *file = [NSString stringWithFormat:@"%s", argv[1]];
    NSString *path = [[NSBundle mainBundle] pathForResource:file ofType:@"xml"];
    NSData *parser = [NSData dataWithContentsOfFile:path];
    
    // Parse the XML into a dictionary
    NSError *parseError = nil;
    NSDictionary *xmlDictionary = [XMLReader dictionaryForXMLData:parser error:&parseError];
    
    NSError *error;
    NSData *jsonData = [NSJSONSerialization dataWithJSONObject:xmlDictionary
                                                       options:NSJSONWritingPrettyPrinted // Pass 0 if you don't care about the readability of the generated string
                                                         error:&error];
    
    if (! jsonData) {
        NSLog(@"Got an error: %@", error);
    } else {
        NSString *jsonString = [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
        jsonString = [jsonString stringByReplacingOccurrencesOfString:@"children1"
                                                           withString:@"children"];
        NSArray *paths = NSSearchPathForDirectoriesInDomains
        (NSDocumentDirectory, NSUserDomainMask, YES);
        NSString *documentsDirectory = [paths objectAtIndex:0];
        NSString *outFile = [NSString stringWithFormat:@"%@/%@_out.agc", documentsDirectory, file];
        NSLog(@"Writing to file %@", outFile);
        [[NSFileManager defaultManager] createFileAtPath:outFile contents:nil attributes:nil];
        [jsonString writeToFile:outFile atomically:YES encoding:NSUTF8StringEncoding error:nil];
        
    }
    

    return NSApplicationMain(argc, argv);
}
