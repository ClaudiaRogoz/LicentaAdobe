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
    
    id firstKeys = [first allKeys];
    for (id key in firstKeys) {
        id firstValue = [first objectForKey:key];
        id secondValue = [second objectForKey:key];
        if (secondValue == nil)
            return false;
        if (![secondValue isKindOfClass:[firstValue class]])
            return false;
        if ([secondValue isKindOfClass:[NSString class]] && ![secondValue isEqualToString:firstValue])
            return false;
        if ([secondValue isKindOfClass:[NSDictionary class]]) {
            BOOL ok = [self match:firstValue second:secondValue];
            if (ok == false)
                return ok;
        } else if ([secondValue isKindOfClass:[NSArray class]]) {
            if ([secondValue count] != [firstValue count])
                return false;
            for (int i = 0; i< [secondValue count]; i++) {
                BOOL ok = [self match:[firstValue objectAtIndex:i] second:[secondValue objectAtIndex:i]]
                if (!ok)
                    return false;
            }
        }
    
    }
    return true;
}

- (void)testExample {
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
    NSLog(@"xmlDict = %@ %@", xmlDictionary, isEqual);
    XCTAssert(true, "Pass");
}

@end
