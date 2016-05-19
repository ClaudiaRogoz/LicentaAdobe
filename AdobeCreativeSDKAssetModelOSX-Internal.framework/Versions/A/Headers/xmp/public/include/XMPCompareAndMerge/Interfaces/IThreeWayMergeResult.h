#ifndef __IThreeWayMergeResult_h__
#define __IThreeWayMergeResult_h__ 1

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
#include "XMPCore/XMPCoreFwdDeclarations.h"

namespace NS_XMPCOMPAREANDMERGE {
using namespace NS_XMPCOMMON;
using namespace NS_XMPCORE;
using NS_XMPCOMMON::UInt32;

typedef enum
{
    kThreeWayMergeStatusNoConflictFound                             = 0,
    kThreeWayMergeStatusAllConflictsResolved                = 1,
    kThreeWayMergeStatusConflictsPending                    = 2,

    kThreeWayMergeStatusMaxValue                                    = kMaxEnumValue
} eThreeWayMergeStatus;

class XMP_PUBLIC IThreeWayMergeResult_v1
    : public virtual ISharedOwnership_v1
{
public:
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED eThreeWayMergeStatus GetMergedStatus( ) const;
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIThreeWayResolvedConflictList_latest GetResolvedConflicts() const;
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIThreeWayUnResolvedConflictList_latest GetUnResolvedConflicts() const;
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPMetadata_latest GetMergedMetadata() const;

protected:
virtual UInt32 GetMergedStatus(pIError_base & error) const __NOTHROW__ = 0;
virtual SizeT GetCountOfResolvedConflicts(pIError_base & error) const __NOTHROW__ = 0;
virtual SizeT GetCountOfUnResolvedConflicts(pIError_base & error) const __NOTHROW__ = 0;
virtual pIThreeWayUnResolvedConflict_latest GetUnResolvedConflict(SizeT index, pIError_base & error) const __NOTHROW__ = 0;
virtual pIThreeWayResolvedConflict_latest GetResolvedConflict(SizeT index, pIError_base & error) const __NOTHROW__ = 0;
virtual pIXMPMetadata_latest GetMergedMetadata(pIError_base & err) const __NOTHROW__ = 0;
virtual ~IThreeWayMergeResult_v1() __NOTHROW__ = 0;
};

inline IThreeWayMergeResult_v1::~IThreeWayMergeResult_v1() __NOTHROW__
{
}
}

#endif  // __IThreeWayMergeResult_h__
