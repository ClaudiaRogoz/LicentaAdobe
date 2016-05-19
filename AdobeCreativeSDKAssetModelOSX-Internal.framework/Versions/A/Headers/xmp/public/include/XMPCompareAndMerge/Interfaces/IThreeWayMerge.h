#ifndef __IThreeWayMerge_h__
#define __IThreeWayMerge_h__ 1

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
//	HK	Honey Kansal
//
// mm-dd-yy who Description of changes, most recent first.
//
// 03-03-14 ADC 1.0-m013 Implemented GetMergedMetadata function of ThreeWayMerge.
// 02-25-14 ADC 1.0-m010 Porting XMPCompareAndMerge to Mac Environment.
// 02-24-14 HK  1.0-m009 Added new internal XMP DOM interfaces + fixed memory leaks + implemented qualifiers for new XMP DOM.
// 02-18-14 ADC 1.0-m004 Three Way Conflict Identification Feature.
//
// =================================================================================================
#endif  // AdobePrivate

#include "XMPCompareAndMerge/XMPCompareAndMergeFwdDeclarations.h"
#include "XMPCompareAndMerge/XMPCompareAndMerge_Defines.h"

#include "XMPCommon/Interfaces/BaseInterfaces/ISharedOwnership.h"

#include "XMPCore/XMPCoreFwdDeclarations.h"

namespace NS_XMPCOMPAREANDMERGE {
using namespace NS_XMPCOMMON;
using namespace NS_XMPCORE;
using NS_XMPCOMMON::UInt32;

class XMP_PUBLIC IThreeWayMerge_v1
    : public virtual ISharedOwnership_v1
{
public:
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIThreeWayMergeResult_latest Merge(const spcIXMPMetadata_latest & commonBaseMetadata,
                                                                           const spcIXMPMetadata_latest & latestVersionMedata, const spcIXMPMetadata_latest & userVersionMetadata);

XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED bool RegisterConflictResolutionStrategy(const spIThreeWayConflictResolutionStrategy_latest & strategy);

XMP_PRIVATE static spIThreeWayMerge_latest CreateThreeWayMerge( );

protected:
virtual pIThreeWayMergeResult_latest Merge(pcIXMPMetadata_base base, pcIXMPMetadata_base latest, pcIXMPMetadata_base user,
                                           pIError_base & error) __NOTHROW__ = 0;
virtual UInt32 RegisterConflictResolutionStrategy(pIThreeWayConflictResolutionStrategy_base strategy, pIError_base & error) __NOTHROW__ = 0;

virtual ~IThreeWayMerge_v1() __NOTHROW__ = 0;
};

inline IThreeWayMerge_v1::~IThreeWayMerge_v1() __NOTHROW__
{
}
}

#endif  // __IThreeWayMerge_h__
