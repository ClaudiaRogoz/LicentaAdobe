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

#ifndef AdobeCollaborationTypeHeader
#define AdobeCollaborationTypeHeader

#import <Foundation/Foundation.h>

/**
 * The type of collaboration, can be private which is an unshared resource,
 * shared by the current user with others, or a resource that has been shared
 * with this user.
 */

typedef NS_ENUM (NSInteger, AdobeCollaborationType)
{
    /** Private */
    AdobeCollaborationTypePrivate,
    /** Shared by the User */
    AdobeCollaborationTypeSharedByUser,
    /** Shared with the User */
    AdobeCollaborationTypeSharedWithUser
};

#endif
