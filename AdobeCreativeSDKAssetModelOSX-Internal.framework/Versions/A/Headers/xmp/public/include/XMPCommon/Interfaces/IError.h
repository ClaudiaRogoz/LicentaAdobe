#ifndef __IError_h__
#define __IError_h__ 1

// =================================================================================================
// Copyright 2014 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

// =================================================================================================
/// @file IError.h
/// @brief Definition of IError interface and related types
///
/// This header defines the interface of the IError type and its related types.
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
// 01-30-14 ADC 1.0-m001 First version
//
// =================================================================================================
#endif // AdobePrivate

#include "XMPCommon/Interfaces/BaseInterfaces/ISharedOwnership.h"
#include "XMPCommon/XMPCommon_Defines.h"

namespace NS_XMPCOMMON {
#if 0
typedef enum
{
    kNoErrMM                                                                = 0,
    kAllocationFailureErrMM                                 = 1,
    kDeallocationFailureErrMM                               = 2,

    kMaxEnumMM                                                              = kMaxEnumValue
} eMemoryManagementErrorCodes;

typedef enum
{
    kNoErrCE                                                                = 0,

    kMaxEnumCE                                                              = kMaxEnumValue
} eConflictEngineErrorCodes;

typedef enum
{
    kNoErrCRE                                                               = 0,

    kMaxEnumCRE                                                             = kMaxEnumValue
} eConflictResolutionEngineErrorCodes;
#endif // if 0
class XMP_PUBLIC IError_v1
    : public virtual ISharedOwnership_v1
{
public:
// severity of the error
typedef enum
{
    kXMPErrSeve_Warning                                             = 0,
    /// Recovery is not possible, an exception will be thrown aborting the API call.
    kXMPErrSev_OperationFatal                               = 1,
    /// Recovery is not possible, an exception will be thrown, the file is corrupt and possibly unusable.
    kXMPErrSev_FileFatal                                    = 2,
    /// Recovery is not possible, an exception will be thrown, the entire process should be aborted.
    kXMPErrSev_ProcessFatal                                 = 3,

    // Add new severities here
    kMaxEnumSeverity                                                = kMaxEnumValue
} eErrorSeverity;

typedef enum
{
    kGeneralDomain                                                  = 0,
    kMemoryManagementDomain                                 = 1,
    kXMPCoreDomain                                                  = 2,
    kXMPFilesDomain                                                 = 3,
    kConflictEngineDomain                                   = 4,
    kConflictResolutionEngineDomain                 = 5,
    // Add new domains here

    kMaxEnumDomain                                                  = kMaxEnumValue
} eErrorDomain;

typedef enum
{
    kNoErrGen                                                               = 0,
    kBadParamErrGen                                                 = 1,
    kUnknownExceptionErrGen                                 = 2,
    kClientCancelErrGen                                             = 3,
    kInitializationFailureErrGen                    = 4,
    kTerminationFailureErrGen                               = 5,
    kLibraryNotIntializedErrGen                             = 6,
    kInterfaceVersionNotSupportedErrGen             = 7,
    kMemoryAllocationFailureErrGen                  = 8,
    kWarningNotToleratedErrGen                              = 9,

    kMaxEnumGen                                                             = kMaxEnumValue
} eGeneralErrorCodes;

typedef UInt32 eErrorCode;

virtual eErrorCode GetCode() const __NOTHROW__ = 0;
virtual eErrorDomain GetDomain() const __NOTHROW__ = 0;
virtual eErrorSeverity GetSeverity() const __NOTHROW__ = 0;
virtual const char * GetMessage() const __NOTHROW__ = 0;
virtual const char * GetFileName() const __NOTHROW__ = 0;
virtual UInt64 GetLineNumber() const __NOTHROW__ = 0;

protected:
virtual ~IError_v1() __NOTHROW__ = 0;
};

inline IError_v1::~IError_v1() __NOTHROW__
{
}
}

#endif  // __IError_h__
