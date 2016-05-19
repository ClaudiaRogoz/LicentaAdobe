/*************************************************************************
*
* ADOBE CONFIDENTIAL
* ___________________
*
*  Copyright 2013 Adobe Systems Incorporated
*  All Rights Reserved.
*
* NOTICE:  All information contained herein is, and remains
* the property of Adobe Systems Incorporated and its suppliers,
* if any.  The intellectual and technical concepts contained
* herein are proprietary to Adobe Systems Incorporated and its
* suppliers and are protected by trade secret or copyright law.
* Dissemination of this information or reproduction of this material
* is strictly forbidden unless prior written permission is obtained
* from Adobe Systems Incorporated.
**************************************************************************/

#ifndef AdobeiTunesParsersHeader
#define AdobeiTunesParsersHeader

extern NSString *const kAdobeiTunesErrorDomain;

/**
*  A completion block used by subclasses of @ c AdobeiTunesServiceBaseParser
*
*  @param productIDsArray An @c NSArray of productIDs.
*  @param error           An NSError that indicates a failure to parse XML data.
*/
typedef void (^ParserCompletionBlock)(NSArray *productIDsArray, NSError *error);

/** Base XML parser class. */
@interface AdobeiTunesServiceBaseParser : NSObject <NSXMLParserDelegate>

/**
*  Method used to create an @c NSXMLParser initialized with data, set itself as delegate and start parsing the data.
*
*  @param data The XML data to parse.
*/
- (void)parseData:(NSData *)data;

@end


/** XML parser class used to parse the response received from Adobe iTunes server.
* According to https://zerowing.corp.adobe.com/display/bizarch/Adobe+iTunes+Service+Architecture the response has the following format:
* <Response>
* <Products>
* <Product>
* <ProductID>com.adobe.sketch.tier1ccstorage.1mo</ProductID>
* </Product>
* </Products>
* <Error>
* <ErrCode>0</ErrCode>
* <ErrDesc>SUCCESS</ErrDesc>
* </Error>
* </Response>
*/
@interface AdobeiTunesServiceResponseParser : AdobeiTunesServiceBaseParser

/**
*  Designated initializer for @c AdobeiTunesServiceResponseParser
*
*  @param completionBlock A completion block that is called when parsing is finished.
*
*  @return An instance of @c AdobeiTunesServiceResponseParser
*/
- (id)initWithCompletionBlock:(ParserCompletionBlock)completionBlock;

@end


/** XML parser class used to parse the product IDs.
* According to https://zerowing.corp.adobe.com/display/bizarch/Adobe+iTunes+Service+Architecture the response has the following format:
* <Response>
* <Products>
* <Product>
* <Name/>
* <ProductID/>
* <Metadata/>
* </Product>
* ...
* </Products>
* </Response>
*
* TODO: This class is not currently used and may go away once we have a final XML response format from AITS and we know we don't need it anymore.
*/
@interface ProductIDsResponseParser : AdobeiTunesServiceBaseParser

/**
*  Designated initializer for @c ProductIDsResponseParser.
*
*  @param completionBlock A completion block that is called when parsing is finished.
*
*  @return An instance of @c ProductIDsResponseParser.
*/
- (id)initWithCompletionBlock:(ParserCompletionBlock)completionBlock;

@end

#endif
