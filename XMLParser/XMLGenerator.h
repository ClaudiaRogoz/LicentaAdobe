//
//  XMLGenerator.h
//  XMLParser
//
//  Created by crogoz on 07/04/16.
//  Copyright © 2016 crogoz. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface XMLGenerator : NSObject
{

    NSMutableDictionary *agcToXmlTemplate;
    NSMutableDictionary *translationDict;
    NSMutableDictionary *uniqueIds;
    int sceneNo;
}


@property NSString *xmlPath;
@property NSString *agcPath;

- (id)initWithError:(NSError **)error;
+ (NSDictionary*)readTemplate;

@end


