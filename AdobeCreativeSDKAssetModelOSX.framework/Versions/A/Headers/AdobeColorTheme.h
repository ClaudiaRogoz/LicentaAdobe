/*************************************************************************
 * ADOBE CONFIDENTIAL
 * ___________________
 *
 *  Copyright 2015 Adobe Systems Incorporated
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Adobe Systems Incorporated and its suppliers,
 * if any.  The intellectual and technical concepts contained
 * herein are proprietary to Adobe Systems Incorporated and its
 * suppliers and are protected by all applicable intellectual property
 * laws, including trade secret and copyright laws.
 * Dissemination of this information or reproduction of this material
 * is strictly forbidden unless prior written permission is obtained
 * from Adobe Systems Incorporated.
 **************************************************************************/

#ifndef AdobeColorThemeHeader
#define AdobeColorThemeHeader

/** Color Theme Rule */
typedef NS_ENUM (NSUInteger, AdobeColorThemeRule)
{
    /** Unknown */
    AdobeColorThemeRuleUnknown,
    /** Not set */
    AdobeColorThemeRuleNotSet,
    /** Analogous */
    AdobeColorThemeRuleAnalogous,
    /** Complimentary */
    AdobeColorThemeRuleComplimentary,
    /** Monochromatic */
    AdobeColorThemeRuleMonochromatic,
    /** Triad */
    AdobeColorThemeRuleTriad,
    /** Custom */
    AdobeColorThemeRuleCustom,
    /** Shades of a single color */
    AdobeColorThemeShades
};

/** Describes the "mood" of a particular color theme. */
typedef NS_ENUM (NSUInteger, AdobeColorThemeMood)
{
    /** Unknown */
    AdobeColorThemeMoodUnknown,
    /** Not set */
    AdobeColorThemeMoodNotSet,
    /** Colorful */
    AdobeColorThemeMoodColorful,
    /** Bright */
    AdobeColorThemeMoodBright,
    /** Muted */
    AdobeColorThemeMoodMuted,
    /** Dark */
    AdobeColorThemeMoodDark,
    /** Custom */
    AdobeColorThemeMoodCustom,
};

/**
 * A ColorTheme represents a collection of related ColorItems.
 */
@interface AdobeColorTheme : NSObject

/**
 * The creator of the theme.
 *
 * Note: may be a nil value
 */
@property (nonatomic, copy) NSString *author;

/**
 * Access an array of UIColors representing the theme
 */
@property (nonatomic, strong, readonly) NSArray *colors;

/**
 * The color mood that best describes the color theme.
 *
 * Set to AdobeColorThemeMoodUnknown by default
 */
@property (nonatomic, assign) AdobeColorThemeMood mood;

/**
 * The name or title of the color theme.
 */
@property (nonatomic, copy) NSString *name;

/**
 * The color harmony rule used to create the theme.
 *
 * Set to AdobeColorRuleUnknown by default.
 */
@property (nonatomic, assign) AdobeColorThemeRule rule;

/**
 * Descriptive tags.
 */
@property (nonatomic, strong) NSArray *tags;

/**
 * Initializes with an array of DCX swatches. Each swatch is expected to be an NSDictionary.
 *
 * For example, the following two lines are equivalent:
 * @code
 *
 * [[AdobeColorTheme alloc] initWithDCXSwatches@[@{@"value": @{@"r": @"0.5", @"g": @"1.0", @"b": @"0.25"}}]];
 * [[AdobeColorTheme alloc] initWithUIColors:@[[UIColor colorWithRed:0.5 green:1.0 blue:0.25 alpha:1.0]]];
 * @endcode
 *
 * We currently support only the RGB color model.
 *
 * @param dict Dictionary of DCX Swatches used to initialize the ColorTheme.
 */
- (instancetype)initWithDCXSwatches:(NSArray *)dict;

/**
 * Initializes the color theme with an array of UIColor objects.
 *
 * @param array Array of UIColors used to initialize the ColorTheme.
 */
- (instancetype)initWithUIColors:(NSArray *)array;

@end

#endif
