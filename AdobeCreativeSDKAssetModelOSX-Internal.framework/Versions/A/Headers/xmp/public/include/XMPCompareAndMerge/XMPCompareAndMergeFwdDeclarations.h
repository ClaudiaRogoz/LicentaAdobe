#ifndef __XMPCompareAndMergeFwdDeclarations_h__
#define __XMPCompareAndMergeFwdDeclarations_h__ 1

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
// 03-03-14 ADC 1.0-m013 Implemented GetMergedMetadata function of ThreeWayMerge.
// 02-19-14 ADC 1.0-m007 Public Header files were referring to couple of private header files.
// 02-18-14 ADC 1.0-m005 Fixes for problems reported by QE during the basic sanity tests
// 02-18-14 ADC 1.0-m004 Three Way Conflict Identification Feature.
//
// =================================================================================================
#endif  // AdobePrivate

#include "XMPCommon/XMPCommonFwdDeclerations.h"
#include "XMPCompareAndMerge/XMPCompareAndMerge_Defines.h"

namespace NS_XMPCOMPAREANDMERGE {
// IThreeWayMerge
using NS_XMPCOMMON::shared_ptr;
using NS_XMPCOMMON::kMaxEnumValue;

class IThreeWayMerge_v1;

typedef IThreeWayMerge_v1                   IThreeWayMerge_base;
typedef IThreeWayMerge_v1 *                 pIThreeWayMerge_base;

typedef IThreeWayMerge_v1                   IThreeWayMerge_latest;
typedef IThreeWayMerge_v1 *                 pIThreeWayMerge_latest;

typedef shared_ptr< IThreeWayMerge_latest > spIThreeWayMerge_latest;

// IThreeWayMergeResult
class IThreeWayMergeResult_v1;

typedef IThreeWayMergeResult_v1                         IThreeWayMergeResult_base;
typedef IThreeWayMergeResult_v1 *                       pIThreeWayMergeResult_base;
typedef const IThreeWayMergeResult_v1 *                 pcIThreeWayMergeResult_base;

typedef IThreeWayMergeResult_v1                         IThreeWayMergeResult_latest;
typedef IThreeWayMergeResult_v1 *                       pIThreeWayMergeResult_latest;
typedef const IThreeWayMergeResult_v1 *                 pcIThreeWayMergeResult_latest;

typedef shared_ptr< IThreeWayMergeResult_latest >       spIThreeWayMergeResult_latest;
typedef shared_ptr< const IThreeWayMergeResult_latest > spcIThreeWayMergeResult_latest;

// IThreeWayUnResolvedConflict
class IThreeWayUnResolvedConflict_v1;

typedef IThreeWayUnResolvedConflict_v1                         IThreeWayUnResolvedConflict_base;
typedef IThreeWayUnResolvedConflict_v1 *                       pIThreeWayUnResolvedConflict_base;
typedef const IThreeWayUnResolvedConflict_v1 *                 pcIThreeWayUnResolvedConflict_base;

typedef IThreeWayUnResolvedConflict_v1                         IThreeWayUnResolvedConflict_latest;
typedef IThreeWayUnResolvedConflict_v1 *                       pIThreeWayUnResolvedConflict_latest;
typedef const IThreeWayUnResolvedConflict_v1 *                 pcIThreeWayUnResolvedConflict_latest;

typedef shared_ptr< IThreeWayUnResolvedConflict_latest >       spIThreeWayUnResolvedConflict_latest;
typedef shared_ptr< const IThreeWayUnResolvedConflict_latest > spcIThreeWayUnResolvedConflict_latest;

typedef std::vector< spIThreeWayUnResolvedConflict_latest >    IThreeWayUnResolvedConflictList_latest;
typedef std::vector< spcIThreeWayUnResolvedConflict_latest >   cIThreeWayUnResolvedConflictList_latest;

typedef shared_ptr< IThreeWayUnResolvedConflictList_latest >   spIThreeWayUnResolvedConflictList_latest;
typedef shared_ptr< cIThreeWayUnResolvedConflictList_latest >  spcIThreeWayUnResolvedConflictList_latest;

// IThreeWayResolvedConflict
class IThreeWayResolvedConflict_v1;

typedef IThreeWayResolvedConflict_v1                         IThreeWayResolvedConflict_base;
typedef IThreeWayResolvedConflict_v1 *                       pIThreeWayResolvedConflict_base;
typedef const IThreeWayResolvedConflict_v1 *                 pcIThreeWayResolvedConflict_base;

typedef IThreeWayResolvedConflict_v1                         IThreeWayResolvedConflict_latest;
typedef IThreeWayResolvedConflict_v1 *                       pIThreeWayResolvedConflict_latest;
typedef const IThreeWayResolvedConflict_v1 *                 pcIThreeWayResolvedConflict_latest;

typedef shared_ptr< IThreeWayResolvedConflict_latest >       spIThreeWayResolvedConflict_latest;
typedef shared_ptr< const IThreeWayResolvedConflict_latest > spcIThreeWayResolvedConflict_latest;

typedef std::vector< spIThreeWayResolvedConflict_latest >    IThreeWayResolvedConflictList_latest;
typedef std::vector< spcIThreeWayResolvedConflict_latest >   cIThreeWayResolvedConflictList_latest;

typedef shared_ptr< IThreeWayResolvedConflictList_latest >   spIThreeWayResolvedConflictList_latest;
typedef shared_ptr< cIThreeWayResolvedConflictList_latest >  spcIThreeWayResolvedConflictList_latest;

// ICompareAndMergeObjectFactory
class ICompareAndMergeObjectFactory_v1;

typedef ICompareAndMergeObjectFactory_v1  ICompareAndMergeObjectFactory_base;
typedef ICompareAndMergeObjectFactory_v1 *pICompareAndMergeObjectFactory_base;

typedef ICompareAndMergeObjectFactory_v1  ICompareAndMergeObjectFactory_latest;
typedef ICompareAndMergeObjectFactory_v1 *pICompareAndMergeObjectFactory_latest;

// IThreeWayConflictResolutionStrategy
class IThreeWayConflictResolutionStrategy_v1;

typedef IThreeWayConflictResolutionStrategy_v1                         IThreeWayConflictResolutionStrategy_base;
typedef IThreeWayConflictResolutionStrategy_v1 *                       pIThreeWayConflictResolutionStrategy_base;
typedef const IThreeWayConflictResolutionStrategy_v1 *                 pcIThreeWayConflictResolutionStrategy_base;

typedef IThreeWayConflictResolutionStrategy_v1                         IThreeWayConflictResolutionStrategy_latest;
typedef IThreeWayConflictResolutionStrategy_v1 *                       pIThreeWayConflictResolutionStrategy_latest;
typedef const IThreeWayConflictResolutionStrategy_v1 *                 pcIThreeWayConflictResolutionStrategy_latest;

typedef shared_ptr< IThreeWayConflictResolutionStrategy_latest >       spIThreeWayConflictResolutionStrategy_latest;
typedef shared_ptr< const IThreeWayConflictResolutionStrategy_latest > spcIThreeWayConflictResolutionStrategy_latest;

typedef enum
{
    kResolvedNodeSourceNone                         = 0,
    kResolvedNodeSourceBaseVersion          = 1,
    kResolvedNodeSourceLatestVersion        = 2,
    kResolvedNodeSourceUserVersion          = 3,
    kResolvedNodeSourceFieldsMerged         = 4,

    kResolvedNodeSourceCustomMerged         = kMaxEnumValue - 2,
    kResolvedNodeSourceStragetyDefined      = kMaxEnumValue - 1,
    kResolvedNodeSourceMaxValue                     = kMaxEnumValue
} eResolvedNodeSource;

typedef enum
{
    kUnResolvedConflictReasonResolved                                               = 0,
    kUnResolvedConflictReasonDifferentValues                                = 1,
    kUnResolvedConflictReasonDifferentTypes                                 = 2,
    kUnResolvedConflictReasonDeletedInLatestEditedInUser    = 3,
    kUnResolvedConflictReasonDeletedInUserEditedInLatest    = 4,
    kUnResolvedConflictReasonDifferentQualifiers                    = 5,
    kUnResolvedConflictReasonDifferentIsURIFlag                             = 6,


    kUnResolvedConflictReasonMaxValue                                               = kMaxEnumValue
} eUnResolvedConflictReason;

typedef enum
{
    kResolvedConflictReasonUnResolved                                                       = 0,
    kResolvedConflictReasonValueSameBetweenBaseAndUser                      = 1,
    kResolvedConflictReasonValueSameBetweenBaseAndLatest            = 2,
    kResolvedConflictReasonInsertionOnlyInUser                                      = 3,
    kResolvedConflictReasonInsertionOnlyInLatest                            = 4,
    kResolvedConflictReasonDeletionOnlyInUser                                       = 5,
    kResolvedConflictReasonDeletionOnlyInLatest                                     = 6,

    kResolvedConflictReasonCustomStrategyApplied                            = kMaxEnumValue - 1,
    kResolvedConflictReasonMaxValue                                                         = kMaxEnumValue
} eResolvedConflictReason;
}

#endif  // __XMPCompareAndMergeFwdDeclarations_h__
