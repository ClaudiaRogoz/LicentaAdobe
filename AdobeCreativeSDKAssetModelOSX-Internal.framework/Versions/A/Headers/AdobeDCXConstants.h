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

// Reviewed by rhorns on October 8, 2013

#ifndef AdobeDCXConstantsHeader
#define AdobeDCXConstantsHeader

#import <Foundation/Foundation.h>

/** name Asset States
* States for the composite and its components
*/
/**@{*/

/** Component/composite hasn't been modified locally since the last pull. */
extern NSString *const AdobeDCXAssetStateUnmodified;
/** Component/composite has been modified locally since the last pull. */
extern NSString *const AdobeDCXAssetStateModified;
/** User has deleted the component/composite locally. */
extern NSString *const AdobeDCXAssetStatePendingDelete;
/** Component/document has been deleted locally and needs to be deleted on the server on next push.
* Notice that this value is for DCX-internal use only.
* A client should never set the state of a component/composite to this value.
*/
extern NSString *const AdobeDCXAssetStateCommittedDelete;

/**@}*/

#endif
