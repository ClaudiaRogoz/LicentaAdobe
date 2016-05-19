#ifndef __IXMPQualifiers_h__
#define __IXMPQualifiers_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2014 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#if AdobePrivate
// =================================================================================================
// Change history
// ==============
//
// Writers:
//  HK	Honey Kansal
//  ADC Amandeep Chawla
//
// mm-dd-yy who Description of changes, most recent first.
//
// 02-24-14 HK  5.6-c004 Added new internal XMP DOM interfaces + fixed memory leaks + implemented qualifiers for new XMP DOM.
// 02-24-14 ADC 5.6-c001 XMPCommon Framework and XMPCore new APIs ported to Mac Environment.
// 02-12-14 HK  5.5-c028 Done refactoring of XMP DOM interfaces and implementations.
// 02-07-14 HK  5.5-c025 Disabling warning:4250 on Windows and enabling lazy loading of Array and structure nodes children.
// 02-03-14 HK  5.5-c023 Submitting first version of XMP DOM interfaces and implementations.
//
// =================================================================================================
#endif  // AdobePrivate

#include "XMPCore/XMPCoreFwdDeclarations.h"
#include "XMPCore/XMPCore_Defines.h"

#include "XMPCommon/Interfaces/IError.h"
#include "XMPCore/Interfaces/IXMPStructNode.h"

namespace NS_XMPCORE {
using namespace NS_XMPCOMMON;
/**
 * This class extends XMP structure node and represents XMP qualifier.
 */
class XMP_PUBLIC IXMPQualifiers_v1
    : public virtual IXMPStructNode_v1 {
public:
/**
 * This method returns XMP node on which this qualifier is present.
 */
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spcIXMPNode_latest GetHost() const;
/**
 * This method returns XMP node on which this qualifier is present.
 */
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPNode_latest GetHost();

protected:
virtual pcIXMPNode_latest GetHost(pIError_base & err) const __NOTHROW__ = 0;
virtual pIXMPNode_latest GetHost(pIError_base & err) __NOTHROW__ = 0;

virtual ~IXMPQualifiers_v1() __NOTHROW__ = 0;
};

inline IXMPQualifiers_v1::~IXMPQualifiers_v1() __NOTHROW__
{
}
}

#endif  // __IXMPQualifiers_h__
