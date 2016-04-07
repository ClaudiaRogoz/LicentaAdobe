//
//  XMLGenerator.m
//  XMLParser
//
//  Created by crogoz on 07/04/16.
//  Copyright © 2016 crogoz. All rights reserved.
//

#import "XMLGenerator.h"

@implementation XMLGenerator

+ (NSDictionary*)readTemplateFromPath:(NSString *)agcPath {
    NSError *error;
    XMLGenerator *gen = [[XMLGenerator alloc] initWithError:&error];
    NSData *jsonData = [NSData dataWithContentsOfFile:agcPath];
    NSDictionary *dictionary = [NSJSONSerialization JSONObjectWithData:jsonData options:kNilOptions error:&error];
    
    return dictionary;
}

- (id)initWithError:(NSError **)error
{
    return self;
}

@end
