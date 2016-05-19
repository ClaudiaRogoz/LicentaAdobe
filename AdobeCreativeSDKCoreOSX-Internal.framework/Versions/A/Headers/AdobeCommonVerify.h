/*************************************************************************
*
* ADOBE CONFIDENTIAL
* ___________________
*
*  Copyright 2014 Adobe Systems Incorporated
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

#ifndef AdobeCommonVerifyHeader
#define AdobeCommonVerifyHeader

/*
*
* This is a collection of macros that is used to verify arguments and state
* to ensure correct usage of our APIs and report incorrect usage to our clients
* who do not use a debug build.
*
* All of these macros throw NSExceptions whenever the desired condition is not met.
*
*
* WARNING
*
* These macros do *not* get stripped out in release builds. So they should be
* used with extreme caution.
*
* They are not meant as a replacement for NSAssert but rather as a complement. We
* use NSAssert to verify state and arguments that are outside the control of our
* clients as well as to perform checks that are expensive and that should not be
* performed in a release build.
*
* Also: These macros must not be used to perform regular error handling (e.g. a failed
* network request or a missing file). Runtime errors must not get thrown.
*
*
* Macros with ... argument
*
* Some of the macros require a format NSString with variable arguments. Since the
* standard C macro __VA_ARGS__ does not eliminate a preceeding comma if there
* are no variable arguments and ##__VA_ARGS__ (which does do that) is a non-
* standard GNU C++ extension we are expecting the format string to be part
* of the list of variable arguments so that
*
*  VerifyArgument(foo == 5, @"Foo must be 5");
*
* works as well as
*
*  VerifyArgument(foo == bar, @"Foo must be %@", bar);
*
*/


/**
* brief Throws a NSInvalidArgumentException exception if condition resolves to NO.
*
* param condition   The condition to verify.
* param format      A human-readable message string (that is, the exception reason) with
*                  conversion specifications for the variable arguments (if any).
*/
#define VerifyArgument(condition, ...)     do {         if (!(condition)){ [NSException raise:NSInvalidArgumentException format:__VA_ARGS__]; }     } while (0)

/**
* brief Throws a NSInvalidArgumentException exception if the given argument is nil.
*
* param argument      The argument.
* param argumentName  The name of the argument.
*/
#define VerifyArgumentNotNil(argument, argumentName)     do {         if ((argument) == nil){ [NSException raise:NSInvalidArgumentException format:@"Argument '%@' must not be nil.", argumentName]; }     } while (0)

/**
* brief Throws a NSInternalInconsistencyException exception if condition resolves to NO.
*
* param condition   The condition to verify.
* param format      A human-readable message string (that is, the exception reason) with
*                  conversion specifications for the variable arguments (if any).
*/
#define VerifyState(condition, ...)     do {         if (!(condition)){ [NSException raise:NSInternalInconsistencyException format:__VA_ARGS__]; }     } while (0)

/**
* brief Throws a NSInternalInconsistencyException exception if the given property is nil.
*
* param property      The property.
* param propertyName  The name of the property.
*/
#define VerifyPropertyNotNil(property, propertyName)     do {         if ((property) == nil){ [NSException raise:NSInternalInconsistencyException format:@"Property '%@' must not be nil.", propertyName]; }     } while (0)

/**
* brief Throws a NSRangeException exception if condition resolves to NO.
*
* param condition   The condition to verify.
* param format      A human-readable message string (that is, the exception reason) with
*                  conversion specifications for the variable arguments (if any).
*/
#define VerifyRange(condition, ...)     do {         if (!(condition)){ [NSException raise:NSRangeException format:__VA_ARGS__]; }     } while (0)

#endif // ifndef creativeSDK_AdobeCommonVerify_h
