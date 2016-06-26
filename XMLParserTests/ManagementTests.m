//
//  ManagementTests.m
//  XDXCodeTranslator
//
//  Created by crogoz on 26/06/16.
//  Copyright © 2016 crogoz. All rights reserved.
//

#import <XCTest/XCTest.h>
#import "XCode2XD.h"
#import "Dict2Agc.h"
#import "Xml2Dict.h"
#import "Helper.h"

@interface ManagementTests : XCTestCase

@end

@implementation ManagementTests

- (void)setUp {
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

- (BOOL) match:(id) first second:(id) second {
    
        if (second == nil)
            return false;
        if (![second isKindOfClass:[first class]])
            return false;
        else if ([second isKindOfClass:[NSString class]] && ![second isEqualToString:first])
            return false;
        else if ([second isKindOfClass:[NSNumber class]] && second != first)
            return false;
        else if ([second isKindOfClass:[NSDictionary class]]) {
            id firstKeys = [first allKeys];
            for (id key in firstKeys) {
                id firstValue = [first objectForKey:key];
                id secondValue = [second objectForKey:key];
                BOOL ok = [self match:firstValue second:secondValue];
                if (ok == false)
                    return ok;
            }
        } else if ([second isKindOfClass:[NSArray class]]) {
            if ([second count] != [first count])
                return false;
            for (int i = 0; i< (int)[second count]; i++) {
                BOOL ok = [self match:[first objectAtIndex:i] second:[second objectAtIndex:i]];
                if (!ok)
                    return false;
            }
        }
    return true;
}

- (void) writeToFile:(NSDictionary*)xmlDictionary file:(NSString*) file computeSha:(int)sha {
    
    NSError *error;
    NSData *jsonData = [NSJSONSerialization dataWithJSONObject:xmlDictionary
                                                       options:NSJSONWritingPrettyPrinted
                                                         error:&error];
    if (! jsonData) {
        NSLog(@"Got an error: %@", error);
    } else {
        NSString *jsonString = [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
        NSString *mainBundle = [Helper getProjHomePath];
        NSString *outFile = [NSString stringWithFormat:@"%@/.%@", mainBundle, file];
        [[NSFileManager defaultManager] createFileAtPath:outFile contents:nil attributes:nil];
        [jsonString writeToFile:outFile atomically:YES encoding:NSUTF8StringEncoding error:nil];
    }
}


- (void)testSingleView {
    // This is an example of a functional test case.
    // Use XCTAssert and related functions to verify your tests produce the correct results.
    NSError *parseError = nil;
    NSString *mainBundle = [Helper getProjHomePath];
    NSString *importPath = [mainBundle stringByAppendingPathComponent:@"TestSingleView.xml"];
    NSData *parser = [NSData dataWithContentsOfFile:importPath];
    NSDictionary *xmlDictionary = [Xml2Dict dictionaryForXMLData:parser error:&parseError];
    NSString *refPath = [mainBundle stringByAppendingPathComponent:@"RefSingleView.json"];
    NSData *refData = [NSData dataWithContentsOfFile:refPath];
    NSDictionary *refDictionary = [NSJSONSerialization JSONObjectWithData:refData options:NSJSONReadingMutableContainers error:&parseError];
    BOOL isEqual = [self match:xmlDictionary second:refDictionary];
    XCTAssert(isEqual, "Pass");
}


- (void)testMultipleViews {
    // This is an example of a functional test case.
    // Use XCTAssert and related functions to verify your tests produce the correct results.
    NSError *parseError = nil;
    NSString *mainBundle = [Helper getProjHomePath];
    NSString *importPath = [mainBundle stringByAppendingPathComponent:@"TestMultipleViews.xml"];
    NSData *parser = [NSData dataWithContentsOfFile:importPath];
    NSDictionary *xmlDictionary = [Xml2Dict dictionaryForXMLData:parser error:&parseError];
    /*NSData *jsonData = [NSJSONSerialization dataWithJSONObject:xmlDictionary
                                                       options:NSJSONWritingPrettyPrinted
                                                         error:&parseError];
    NSString *jsonString = [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
    NSString *outFile = [NSString stringWithFormat:@"%@/RefMultipleViews.json", mainBundle];
    [jsonString writeToFile:outFile atomically:YES encoding:NSUTF8StringEncoding error:nil];
    */
    NSString *refPath = [mainBundle stringByAppendingPathComponent:@"RefMultipleViews.json"];
    NSData *refData = [NSData dataWithContentsOfFile:refPath];
    NSDictionary *refDictionary = [NSJSONSerialization JSONObjectWithData:refData options:NSJSONReadingMutableContainers error:&parseError];
    BOOL isEqual = [self match:xmlDictionary second:refDictionary];
    XCTAssert(isEqual, "Pass");
}

- (void) testMultipleViewsWithAssets {
    
    NSError *parseError = nil;
    NSString *mainBundle = [Helper getProjHomePath];
    NSString *importPath = [mainBundle stringByAppendingPathComponent:@"TestMultipleAssets.xml"];
    NSData *parser = [NSData dataWithContentsOfFile:importPath];
    NSDictionary *xmlDictionary = [Xml2Dict dictionaryForXMLData:parser error:&parseError];
    NSData *jsonData = [NSJSONSerialization dataWithJSONObject:xmlDictionary
                                                       options:NSJSONWritingPrettyPrinted
                                                         error:&parseError];
    NSString *jsonString = [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
    NSString *outFile = [NSString stringWithFormat:@"%@/RefMultipleAssets.json", mainBundle];
    [jsonString writeToFile:outFile atomically:YES encoding:NSUTF8StringEncoding error:nil];

}

@end
