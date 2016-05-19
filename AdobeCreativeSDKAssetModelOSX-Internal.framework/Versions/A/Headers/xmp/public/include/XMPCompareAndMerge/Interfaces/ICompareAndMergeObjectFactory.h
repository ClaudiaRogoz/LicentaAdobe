#ifndef __ICompareAndMergeObjectFactory_h__
#define __ICompareAndMergeObjectFactory_h__ 1

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
//  ADC	Amandeep Chawla
//
// mm-dd-yy who Description of changes, most recent first.
//
// 02-25-14 ADC 1.0-m010 Porting XMPCompareAndMerge to Mac Environment.
// 02-18-14 ADC 1.0-m004 Three Way Conflict Identification Feature.
//
// =================================================================================================
#endif  // AdobePrivate

#include "XMPCompareAndMerge/XMPCompareAndMergeFwdDeclarations.h"
#include "XMPCompareAndMerge/XMPCompareAndMerge_Defines.h"

#include "XMPCommon/Interfaces/BaseInterfaces/ITSingleton.h"

namespace NS_XMPCOMPAREANDMERGE {
using namespace NS_XMPCOMMON;

class XMP_PUBLIC ICompareAndMergeObjectFactory_v1
    : public virtual ITSingleton< ICompareAndMergeObjectFactory_v1 >
{
public:
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIThreeWayMerge_latest CreateThreeWayMerge();

protected:
virtual pIThreeWayMerge_latest CreateThreeWayMerge(pIError_base & error) __NOTHROW__ = 0;
virtual ~ICompareAndMergeObjectFactory_v1() __NOTHROW__ = 0;
};

inline ICompareAndMergeObjectFactory_v1::~ICompareAndMergeObjectFactory_v1() __NOTHROW__
{
}
}

#endif  // __ICompareAndMergeObjectFactory_h__
