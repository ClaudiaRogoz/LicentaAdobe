//
//  Constants.m
//  XMLParser
//
//  Created by crogoz on 14/04/16.
//  Copyright © 2016 crogoz. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Constants.h"

@implementation Constants

+ (NSDictionary*) hasToBeTransformed {
    static NSDictionary *inst = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        inst = @{
                 @"size": @"",
                 @"color": @"value2",
                 };
    });
    return inst;
}

@end