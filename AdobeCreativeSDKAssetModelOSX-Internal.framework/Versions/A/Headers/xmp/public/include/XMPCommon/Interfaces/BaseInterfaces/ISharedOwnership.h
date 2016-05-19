#ifndef __ISharedOwnership_h__
#define __ISharedOwnership_h__ 1

// =================================================================================================
// Copyright 2014 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

// =================================================================================================
/// @file ISharedOwnership.h
/// @brief Definition of template class TISharedOwnership.
///
/// Any class/interface which inherits from this class needs to provide implementation for
/// AcquireSharedOwnership and ReleaseSharedOwnership pure virtual function. Also the destructor of
/// derived class should be declared as protected so that by mistake also client of this object
/// cannot call delete on this.
///
// =================================================================================================

#if AdobePrivate
// =================================================================================================
// Change history
// ==============
//
// Writers:
//  ADC	Amandeep Chawla
//
// mm/dd/yy who Description of changes, most recent on top.
//
// 02-24-14 ADC 5.6-c001 XMPCommon Framework and XMPCore new APIs ported to Mac Environment.
//
// 02-18-14 ADC 1.0-m004 Three Way Conflict Identification Feature.
// 02-13-14 ADC 5.5-c031 Refactoring XMPCore, implementing few APIs and fixing issues.
// 02-09-14 ADC 1.0-m003 Re-factoring of XMPCommon Framework
// 02-05-14 ADC 1.0-m002 Some changes in the common framework
// 01-30-14 ADC 1.0-m001 First version
//
// =================================================================================================
#endif // AdobePrivate

#include "XMPCommon/XMPCommon_Defines.h"

namespace NS_XMPCOMMON {
class XMP_PUBLIC ISharedOwnership_v1 {
public:
virtual void AcquireSharedOwnership() const __NOTHROW__ = 0;
virtual void ReleaseSharedOwnership() const __NOTHROW__ = 0;
virtual void AcquireSharedOwnershipForRawPointer() const __NOTHROW__
{
}

protected:
virtual void Destroy() __NOTHROW__
{
    delete this;
}

virtual ~ISharedOwnership_v1() __NOTHROW__ = 0;
};

inline ISharedOwnership_v1::~ISharedOwnership_v1() __NOTHROW__
{
}
}

#endif  // __ISharedOwnership_h__
