#ifndef __IThreeWayResolvedConflict_h__
#define __IThreeWayResolvedConflict_h__ 1

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
// 02-25-14 ADC 1.0-m010 Porting XMPCompareAndMerge to Mac Environment.
// 02-24-14 HK  1.0-m009 Added new internal XMP DOM interfaces + fixed memory leaks + implemented qualifiers for new XMP DOM.
// 02-18-14 ADC 1.0-m004 Three Way Conflict Identification Feature.
//
// =================================================================================================
#endif  // AdobePrivate

#include "XMPCompareAndMerge/XMPCompareAndMergeFwdDeclarations.h"
#include "XMPCompareAndMerge/XMPCompareAndMerge_Defines.h"

#include "XMPCommon/Interfaces/BaseInterfaces/ISharedOwnership.h"
#include "XMPCommon/XMPCommonFwdDeclerations.h"

#include "XMPCore/XMPCoreFwdDeclarations.h"

namespace NS_XMPCOMPAREANDMERGE {
using namespace NS_XMPCOMMON;
using namespace NS_XMPCORE;

class XMP_PUBLIC IThreeWayResolvedConflict_v1
    : public virtual ISharedOwnership_v1
{
public:
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED eResolvedConflictReason GetResolvedConflictReason() const;
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED eResolvedNodeSource GetResolvedNodeSource() const;
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spcIXMPNode_latest GetCommonBaseNode() const;
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spcIXMPNode_latest GetUserVersionNode() const;
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spcIXMPNode_latest GetLatestVersionNode() const;
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spcIXMPNode_latest GetResolvedNode() const;
// VIRTUAL_IF_SOURCE_COMPILED spcITwoWayConflictResolutionStrategy GetStrategyUsed() const = 0;

protected:
virtual UInt32 GetResolvedConflictReason(pIError_base & err) const __NOTHROW__ = 0;
virtual UInt32 GetResolvedNodeSource(pIError_base & err) const __NOTHROW__ = 0;
virtual pcIXMPNode_latest GetCommonBaseNode(pIError_base & err) const __NOTHROW__ = 0;
virtual pcIXMPNode_latest GetUserVersionNode(pIError_base & err) const __NOTHROW__ = 0;
virtual pcIXMPNode_latest GetLatestVersionNode(pIError_base & err) const __NOTHROW__ = 0;
virtual pcIXMPNode_latest GetResolvedNode(pIError_base & err) const __NOTHROW__ = 0;
virtual ~IThreeWayResolvedConflict_v1() __NOTHROW__ = 0;
};

inline IThreeWayResolvedConflict_v1::~IThreeWayResolvedConflict_v1() __NOTHROW__
{
}
}

#endif  // __IThreeWayResolvedConflict_h__
