#ifndef __IXMPPathSegment_h__
#define __IXMPPathSegment_h__ 1

// =================================================================================================
// Copyright 2014 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

// =================================================================================================
/// @file IXMPathSegment.h
/// @brief Definition of IXMPPathSegment interface and related types
///
/// This header defines the interface of the IXMPPathSegment type and its related types.
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
// 02-12-14 HK  5.5-c028 Done refactoring of XMP DOM interfaces and implementations.
// 02-09-14 ADC 5.5-c026 Re-factoring of XMPCommon Framework
// 02-05-14 ADC 5.5-c024 Added a new API to the XMPCore to return pointer to interface
//						 IXMPDOMFactory
//
// =================================================================================================
#endif // AdobePrivate

#include "XMPCore/XMPCoreFwdDeclarations.h"
#include "XMPCore/XMPCore_Defines.h"

#include "XMPCommon/Interfaces/BaseInterfaces/ISharedOwnership.h"

namespace NS_XMPCORE {
using NS_XMPCOMMON::kMaxEnumValue;
using NS_XMPCOMMON::SizeT;
using NS_XMPCOMMON::ISharedOwnership_v1;

/**
 * This enumeration represents the type (property, array index, qualifier or qualifier selector) of path segment.
 */
typedef enum
{
    kXMPPathSegementTypeProperty                    = 0,
    kXMPPathSegmentTypeArrayIndex                   = 1,
    kXMPPathSegmentTypeQualifier                    = 2,
    kXMPPathSegmentTypeQualifierSelector    = 3,

    kMaxValue                                                               = kMaxEnumValue,
} eXMPPathSegmentType;

/**
 * This class represents a path segment.
 */
class XMP_PUBLIC IXMPPathSegment_v1
    : public virtual ISharedOwnership_v1
{
public:
/**
 * This method returns namespace of this path segment.
 */
virtual const char * GetNameSpace() const __NOTHROW__ = 0;
/**
 * This method returns name of this path segment.
 */
virtual const char * GetName() const __NOTHROW__ = 0;
/**
 * This method returns type (property, array index, qualifier or qualifier selector) of this path segment.
 */
virtual eXMPPathSegmentType GetType() const __NOTHROW__ = 0;
/**
 * This method returns index if this segment is of type "array index".
 */
virtual size_t GetIndex() const __NOTHROW__ = 0;
/**
 * This method returns value of this segment if this is of type "qualifier selector".
 */
virtual const char * GetValue() const __NOTHROW__ = 0;

// static factory methods
/**
 * This method creates and returns a segment for XMP property of specified name in specified namespace.
 */
XMP_PRIVATE static spIXMPPathSegment_latest CreatePropertySegment(const char *nameSpace, const char *name);
/**
 * This method creates and returns a segment for XMP array index in specified namespace.
 */
XMP_PRIVATE static spIXMPPathSegment_latest CreateArrayIndexSegment(const char *nameSpace, size_t index);
/**
 * This method creates and returns a segment for XMP qualifier of specified name in specified namespace.
 */
XMP_PRIVATE static spIXMPPathSegment_latest CreateQualifierSegment(const char *nameSpace, const char *name);
/**
 * This method creates and returns a selecter segment for XMP qualifier of specified name,value in specified namespace.
 */
XMP_PRIVATE static spIXMPPathSegment_latest CreateQualifierSelectorSegment(const char *nameSpace, const char *name, const char *value);

protected:
virtual ~IXMPPathSegment_v1() __NOTHROW__ = 0;
};

inline IXMPPathSegment_v1::~IXMPPathSegment_v1() __NOTHROW__
{
}
}

#endif  // __IXMPPathSegment_h__
