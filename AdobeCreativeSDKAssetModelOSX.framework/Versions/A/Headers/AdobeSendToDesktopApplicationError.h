/*************************************************************************
 *
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
 * suppliers and are protected by trade secret or copyright law.
 * Dissemination of this information or reproduction of this material
 * is strictly forbidden unless prior written permission is obtained
 * from Adobe Systems Incorporated.
 **************************************************************************/

#ifndef AdobeSendToDesktopErrorHeader
#define AdobeSendToDesktopErrorHeader

#import <Foundation/Foundation.h>

/** The domain for Adobe Send To Desktop Application errors. */
extern NSString *const AdobeSendToDesktopApplicationErrorDomain;

/**
 * Error codes for the AdobeSendToDesktopApplicationErrorDomain domain.
 */
typedef NS_ENUM (NSInteger, AdobeSendToDesktopApplicationErrorCode)
{
    /**
     * Illegal argument.
     */
    AdobeSendToDesktopApplicationIllegalArgument = 1,

    /**
     * Monitor failure.
     *
     * The Creative Cloud monitor tracking the completion of the "send to desktop" copy stopped
     * responding.  This is no indication that the copy failed, but that it could not be confirmed.
     */
    AdobeSendToDesktopApplicationMonitorFailure = 2,
};

#endif
