#ifndef __IXMPPath_h__
#define __IXMPPath_h__ 1

// =================================================================================================
// Copyright 2014 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

// =================================================================================================
/// @file IXMPath.hpp
/// @brief Definition of IXMPPath interface and related types
///
/// This header defines the interface of the IXMPPath type and its related types.
///
// =================================================================================================

#if AdobePrivate
// =================================================================================================
// Change history
// ==============
//
// Writers:
//  ADC Amandeep Chawla
//	HK	Honey Kansal
//
// mm/dd/yy who Description of changes, most recent on top.
//
// 02-24-14 HK  5.6-c004 Added new internal XMP DOM interfaces + fixed memory leaks + implemented qualifiers for new XMP DOM.
// 02-24-14 ADC 5.6-c001 XMPCommon Framework and XMPCore new APIs ported to Mac Environment.
// 02-18-14 HK  5.5-c034 Implementing Serialize(), Clone() and all setter/modifier methods of XMP DOM.
// 02-12-14 HK  5.5-c028 Done refactoring of XMP DOM interfaces and implementations.
// 02-09-14 ADC 5.5-c026 Re-factoring of XMPCommon Framework
// 01-30-14 ADC 1.0-m001 First version
//
// =================================================================================================
#endif // AdobePrivate

#include "XMPCore/XMPCoreFwdDeclarations.h"
#include "XMPCore/XMPCore_Defines.h"

#include "XMPCommon/Interfaces/BaseInterfaces/ISharedOwnership.h"
#include "XMPCommon/Interfaces/IError.h"
#include "XMPCommon/Interfaces/IUTF8String.h"

namespace NS_XMPCORE {
using namespace NS_XMPCOMMON;
/**
 * This class represents path to a XMP property in DOM.
 */
class XMP_PUBLIC IXMPPath_v1
    : public virtual ISharedOwnership_v1
{
public:
/**
 * This method serializes this path and returns serialized string.
 */
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIUTF8String Serialize(bool) const;
/**
 * This method appends specified path segment to the end of this path.
 */
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED void AppendSegment(spIXMPPathSegment_latest);
/**
 * This method returns the path segment at specified index.
 */
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPPathSegment_latest GetSegment(SizeT) const;
/**
 * This method returns total number of segments present in this pth.
 */
virtual SizeT SegmentCount() const __NOTHROW__ = 0;
/**
 * This method returns true if there are no segments present in this path else false.
 */
virtual bool IsEmpty() const __NOTHROW__ = 0;

// static factory methods
/**
 * This method creates and returns an emtry path with no segments.
 */
XMP_PRIVATE static spIXMPPath_latest CreateEmptyPath();
/**
 * This method creates path by parsing specified serialized path string and returns it.
 */
XMP_PRIVATE static spIXMPPath_latest CreatePathByParsing(const char *);

protected:
virtual pIUTF8String_latest Serialize(bool, pIError_base &) const __NOTHROW__ = 0;
virtual void AppendSegment(pIXMPPathSegment_base, pIError_base &) __NOTHROW__ = 0;
virtual pIXMPPathSegment_latest GetSegment(SizeT, pIError_base &) const __NOTHROW__ = 0;

~IXMPPath_v1() __NOTHROW__ = 0;
                #ifndef FRIEND_CLASS_DECLARATION
                        #define FRIEND_CLASS_DECLARATION()
                #endif
FRIEND_CLASS_DECLARATION();
};

inline IXMPPath_v1::~IXMPPath_v1() __NOTHROW__
{
}
}

#endif  // __IXMPPath_h__
