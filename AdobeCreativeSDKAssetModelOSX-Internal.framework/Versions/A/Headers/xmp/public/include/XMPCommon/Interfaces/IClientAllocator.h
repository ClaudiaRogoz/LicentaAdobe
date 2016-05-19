#ifndef __IClientAllocator_h__
#define __IClientAllocator_h__ 1

// =================================================================================================
// Copyright 2014 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

// =================================================================================================
/// @file IClientAllocator.h
/// @brief Definition of IAllocator interface and related types
///
/// This header defines the interface of the IClientAllocator type.
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
// 02-09-14 ADC 1.0-m003 Re-factoring of XMPCommon Framework
// 02-05-14 ADC 1.0-m002 Some changes in the common framework
// 01-30-14 ADC 1.0-m001 First version
//
// =================================================================================================
#endif // AdobePrivate

#include "XMPCommon/Interfaces/BaseInterfaces/ISharedOwnership.h"
#include "XMPCommon/XMPCommon_Defines.h"

namespace NS_XMPCOMMON {
class XMP_PUBLIC IClientAllocator_v1
    : public virtual ISharedOwnership_v1
{
public:
virtual void * Allocate(SizeT size) __NOTHROW__ = 0;
virtual void Deallocate(void *ptr) __NOTHROW__ = 0;

protected:
virtual ~IClientAllocator_v1() __NOTHROW__ = 0;
};

inline IClientAllocator_v1::~IClientAllocator_v1() __NOTHROW__
{
}
}

#endif  // __IClientAllocator_h__
