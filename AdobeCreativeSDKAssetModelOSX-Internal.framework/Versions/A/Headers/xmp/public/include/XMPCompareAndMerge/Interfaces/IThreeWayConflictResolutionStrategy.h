#ifndef __IThreeWayConflictResolutionStrategy_h__
#define __IThreeWayConflictResolutionStrategy_h__ 1

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
// 03-06-14 ADC 1.0-m016 Fixed some issues found while implementing Anywhere History Strategy.
// 03-05-14 ADC 1.0-m014 Implemented a small change in Resolution strategy.
// 03-03-14 ADC 1.0-m013 Implemented GetMergedMetadata function of ThreeWayMerge.
//
// =================================================================================================
#endif  // AdobePrivate

#include "XMPCompareAndMerge/XMPCompareAndMergeFwdDeclarations.h"
#include "XMPCompareAndMerge/XMPCompareAndMerge_Defines.h"

#include "XMPCore/Interfaces/IXMPNode.h"
#include "XMPCore/XMPCoreFwdDeclarations.h"

#include "XMPCommon/Interfaces/BaseInterfaces/ISharedOwnership.h"
#include "XMPCommon/Interfaces/IError.h"
#include "XMPCommon/Interfaces/IUTF8String.h"

namespace NS_XMPCOMPAREANDMERGE {
using namespace NS_XMPCOMMON;
using namespace NS_XMPCORE;
using NS_XMPCOMMON::UInt32;

class XMP_PUBLIC IThreeWayConflictResolutionStrategy_v1
    : public virtual ISharedOwnership_v1
{
public:
virtual bool InterestedInResolvingConflict(const spcIUTF8String & nodePath, eXMPNodeType nodeType, eUnResolvedConflictReason reason, bool alreadyResolved) = 0;

virtual eUnResolvedConflictReason ResolveConflict(eUnResolvedConflictReason reasonsForConflict, const spcIXMPNode_latest & commonBaseNode,
                                                  const spcIXMPNode_latest & latestVersionNode, const spcIXMPNode_latest & userVersionNode, spcIXMPNode_latest & resolvedNode,
                                                  eResolvedConflictReason & reasonForConflictResolution, eResolvedNodeSource & resolvedNodeSource) = 0;

// these functions are wrapper over actual functions client needs to implement, so no implementation required from client side
virtual UInt32 InterestedInResolvingConflict(pcIUTF8String_latest nodePath, UInt32 nodeType,
                                             UInt32 reason, UInt32 alreadyResolved, pIError_base & error);

virtual UInt32 ResolveConflict(UInt32 reasonsForConflict, const pcIXMPNode_latest & commonBaseNode,
                               const pcIXMPNode_latest & latestVersionNode, const pcIXMPNode_latest & userVersionNode, pcIXMPNode_latest & resolvedNode,
                               UInt32 & reasonForConflictResolution, UInt32 & resolvedNodeSource, pIError_base & error);

protected:
virtual ~IThreeWayConflictResolutionStrategy_v1() __NOTHROW__ = 0;
};

inline IThreeWayConflictResolutionStrategy_v1::~IThreeWayConflictResolutionStrategy_v1() __NOTHROW__
{
}

inline UInt32 IThreeWayConflictResolutionStrategy_v1::InterestedInResolvingConflict(pcIUTF8String_latest nodePath, UInt32 nodeType, UInt32 reason,
                                                                                    UInt32 alreadyResolved, pIError_base & error)
{
    _TRY_(error);
    bool returnValue = InterestedInResolvingConflict(CreateSharedPointer< const IUTF8String_latest >(nodePath), static_cast< eXMPNodeType >(nodeType),
                                                     static_cast< eUnResolvedConflictReason >(reason), alreadyResolved != 0 ? true : false);
    return static_cast< UInt32 >(returnValue);

    _CATCH_(error);
    return 0;
}

inline UInt32 IThreeWayConflictResolutionStrategy_v1::ResolveConflict(UInt32 reasonsForConflict, const pcIXMPNode_latest & commonBaseNode,
                                                                      const pcIXMPNode_latest & latestVersionNode, const pcIXMPNode_latest & userVersionNode, pcIXMPNode_latest & resolvedNode,
                                                                      UInt32 & reasonForConflictResolution, UInt32 & resolvedNodeSource, pIError_base & error)
{
    _TRY_(error);
    spcIXMPNode_latest _resolvedNode = CreateSharedPointer< const IXMPNode_latest >(resolvedNode);
    eResolvedConflictReason _reasonForConflictResolution = static_cast< eResolvedConflictReason >(reasonForConflictResolution);
    eResolvedNodeSource _resolvedNodeSource = static_cast< eResolvedNodeSource >(resolvedNodeSource);

    eUnResolvedConflictReason returnValue = ResolveConflict(static_cast< eUnResolvedConflictReason >(reasonsForConflict),
                                                            CreateSharedPointer< const IXMPNode_latest >(commonBaseNode), CreateSharedPointer< const IXMPNode_latest >(latestVersionNode),
                                                            CreateSharedPointer< const IXMPNode_latest >(userVersionNode), _resolvedNode, _reasonForConflictResolution, _resolvedNodeSource);

    if (_resolvedNode && _resolvedNode.get() != resolvedNode)
    {
        _resolvedNode->AcquireSharedOwnership();
        resolvedNode = _resolvedNode.get();
    }


    reasonForConflictResolution = static_cast< UInt32 >(_reasonForConflictResolution);
    resolvedNodeSource = static_cast< UInt32 >(_resolvedNodeSource);
    return static_cast < UInt32 >(returnValue);

    _CATCH_(error);
    return 0;
}
}
#endif  // __IThreeWayConflictResolutionStrategy_h__
