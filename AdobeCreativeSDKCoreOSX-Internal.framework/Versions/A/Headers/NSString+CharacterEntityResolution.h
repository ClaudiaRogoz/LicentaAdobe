/******************************************************************************
*
* ADOBE CONFIDENTIAL
* ___________________
*
* Copyright 2015 Adobe Systems Incorporated
* All Rights Reserved.
*
* NOTICE:  All information contained herein is, and remains the property of
* Adobe Systems Incorporated and its suppliers, if any. The intellectual and
* technical concepts contained herein are proprietary to Adobe Systems
* Incorporated and its suppliers and are protected by trade secret or
* copyright law. Dissemination of this information or reproduction of this
* material is strictly forbidden unless prior written permission is obtained
* from Adobe Systems Incorporated.
******************************************************************************/

#ifndef AdobeNSStringCharEntityResolutionHeader
#define AdobeNSStringCharEntityResolutionHeader

#import <Foundation/Foundation.h>

@interface NSString (CharacterEntityResolution)

/**
*  Finds and resolves any character entity references contained within the receiver to their respective Unicode characters
*  and returns the result. See http://www.w3.org/TR/html5/syntax.html#named-character-references for details on supported
*  characters.
*
*  @return A string devoid of character entity references.
*/
- (NSString *)stringByResolvingCharacterEntityReferences;

@end

#endif
