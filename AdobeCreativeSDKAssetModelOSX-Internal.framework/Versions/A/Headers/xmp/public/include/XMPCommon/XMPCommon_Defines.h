#ifndef __XMPCommon_Defines_h__
#define __XMPCommon_Defines_h__ 1

// =================================================================================================
// Copyright 2014 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

// =================================================================================================
// XMP_CommonDefines.h - Common Defines across all the XMP Components
// ================================================================
//
// This header defines common definitions to be used across all the XMP Components.
//
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
// 04-11-14 ADC 1.0-m019 [3739647] Find a Strategy to resolve the issues of "multiple definitions" faced
//						 by clients while integrating the new builds containing Compare and Merge.
// 03-03-14 ADC 1.0-m013 Implemented GetMergedMetadata function of ThreeWayMerge.
// 02-25-14 ADC 1.0-m010 Porting XMPCompareAndMerge to Mac Environment.
// 02-24-14 HK  5.6-c004 Added new internal XMP DOM interfaces + fixed memory leaks + implemented qualifiers for new XMP DOM.
// 02-24-14 ADC 5.6-c003 Fixing crash in XMPFilesAPI test.
// 02-24-14 ADC 5.6-c001 XMPCommon Framework and XMPCore new APIs ported to Mac Environment.
//
// 02-18-14 ADC 1.0-m005 Fixes for problems reported by QE during the basic sanity tests
// 02-18-14 ADC 1.0-m004 Three Way Conflict Identification Feature.
// 02-13-14 ADC 5.5-c031 Refactoring XMPCore, implementing few APIs and fixing issues.
// 02-09-14 ADC 1.0-m003 Re-factoring of XMPCommon Framework
// 02-05-14 ADC 1.0-m002 Some changes in the common framework
// 01-30-14 ADC 1.0-m001 First version
//
// =================================================================================================
#endif // AdobePrivate

// =================================================================================================
// All Platform Settings
// ===========================
#include "XMP_Const.h"
#include "XMP_Environment.h"

// =================================================================================================
// Macintosh Specific Settings
// ===========================
#if XMP_MacBuild
        #define ENABLE_XMP_COMMON_CODE                  1
        #define SUPPORT_STD_ATOMIC_IMPLEMENTATION       0
        #define SUPPORT_SHARED_POINTERS_IN_TR1          1
        #define SUPPORT_SHARED_POINTERS_IN_STD          0
        #define SUPPORT_SHARED_POINTERS_WITH_ALLOCATORS 0
#endif

// =================================================================================================
// IOS Specific Settings
// ===========================
#if XMP_iOSBuild
        #define ENABLE_XMP_COMMON_CODE                  1
        #define SUPPORT_STD_ATOMIC_IMPLEMENTATION       0
        #define SUPPORT_SHARED_POINTERS_IN_TR1          1
        #define SUPPORT_SHARED_POINTERS_IN_STD          0
        #define SUPPORT_SHARED_POINTERS_WITH_ALLOCATORS 0
#endif

// =================================================================================================
// Windows Specific Settings
// =========================
#if XMP_WinBuild
        #define ENABLE_XMP_COMMON_CODE                    1
        #define SUPPORT_SHARED_POINTERS_WITH_ALLOCATORS   1
        #if _MSC_VER <= 1600
                #define SUPPORT_STD_ATOMIC_IMPLEMENTATION 0
                #define SUPPORT_SHARED_POINTERS_IN_TR1    1
                #define SUPPORT_SHARED_POINTERS_IN_STD    0
        #else
                #define SUPPORT_STD_ATOMIC_IMPLEMENTATION 1
                #define SUPPORT_SHARED_POINTERS_IN_TR1    0
                #define SUPPORT_SHARED_POINTERS_IN_STD    1
        #endif
#endif

// =================================================================================================
// UNIX Specific Settings
// ======================
#if XMP_UNIXBuild
        #define ENABLE_XMP_COMMON_CODE 0
#endif

#ifndef ENABLE_XMP_COMMON_CODE
        #define ENABLE_XMP_COMMON_CODE 0
#endif

#if ENABLE_XMP_COMMON_CODE
        #define NS_XMPCOMMON           AdobeXMPCommon
        #define __NOTHROW__            throw()

        #define _TRY_(errorReference)                                 \
    errorReference = NULL;                                          \
    try{                                                                           \

        #define _CATCH_(errorReference)                               \
    }catch (pIError_base err){                          \
        errorReference = err;                                   \
    }catch (...){                                                       \
                        \
    }
// TODO:@Aman set unknown exception caught error, operation fatal

        #define _NO_CATCH_()                                                    \
    }catch (...){                                                       \
        throw;                                                                  \
    }

        #define CALL_EQUIVALENT_VIRTUAL_FUNCTION_NO_ARGS(className, functionName)                     \
    {                                                                                                                                                               \
        pIError_latest error(NULL);                                                                                                  \
        p ## className ## _base ptr = functionName(error);                                                                \
        if (error){                                                                                                                                    \
            throw CreateUncheckedSharedPointer(error); }                                                            \
        return CreateSharedPointer< className ## _latest, className ## _base >(ptr);              \
    }

        #define CALL_EQUIVALENT_VIRTUAL_FUNCTION(className, functionName, ...)                        \
    {                                                                                                                                                               \
        pIError_latest error(NULL);                                                                                                  \
        p ## className ## _base ptr = functionName(__VA_ARGS__, error);                                   \
        if (error){                                                                                                                                    \
            throw CreateUncheckedSharedPointer(error); }                                                            \
        return CreateSharedPointer< className ## _latest, className ## _base >(ptr);              \
    }

        #define CALL_EQUIVALENT_CVIRTUAL_FUNCTION_NO_ARGS(className, functionName)                                    \
    {                                                                                                                                                                                       \
        pIError_latest error(NULL);                                                                                                                          \
        pc ## className ## _base ptr = functionName(error);                                                                                       \
        if (error){                                                                                                                                                            \
            throw CreateUncheckedSharedPointer(error); }                                                                                    \
        return CreateSharedPointer< const className ## _latest, const className ## _base >(ptr);          \
    }

        #define CALL_EQUIVALENT_CVIRTUAL_FUNCTION(className, functionName, ...)                                               \
    {                                                                                                                                                                                       \
        pIError_latest error(NULL);                                                                                                                          \
        pc ## className ## _base ptr = functionName(__VA_ARGS__, error);                                                          \
        if (error){                                                                                                                                                            \
            throw CreateUncheckedSharedPointer(error); }                                                                                    \
        return CreateSharedPointer< const className ## _latest, const className ## _base >(ptr);          \
    }

        #define CALL_EQUIVALENT_VIRTUAL_FUNCTION_RETURNING_ENUM_NO_ARGS(enumType, functionName)               \
    {                                                                                                                                                                                       \
        pIError_latest error(NULL);                                                                                                                          \
        UInt32 value = functionName(error);                                                                                                           \
        if (error){                                                                                                                                                            \
            throw CreateUncheckedSharedPointer(error); }                                                                                    \
        return static_cast< enumType >(value);                                                                                                        \
    }

        #define CALL_EQUIVALENT_VIRTUAL_FUNCTION_RETURNING_ENUM(enumType, functionName, ...)          \
    {                                                                                                                                                                       \
        pIError_latest error(NULL);                                                                                                          \
        UInt32 value = functionName(__VA_ARGS__, error);                                                                      \
        if (error){                                                                                                                                            \
            throw CreateUncheckedSharedPointer(error); }                                                                    \
        return static_cast< enumType >(value);                                                                                        \
    }

        #define CALL_EQUIVALENT_VIRTUAL_FUNCTION_RETURNING_BOOL(functionName, ...)                    \
    {                                                                                                                                                                       \
        pIError_latest error(NULL);                                                                                                          \
        UInt32 value = functionName(__VA_ARGS__, error);                                                                      \
        if (error){                                                                                                                                            \
            throw CreateUncheckedSharedPointer(error); }                                                                    \
        return value != 0 ? true : false;                                                                                                      \
    }


        #define CALL_EQUIVALENT_VIRTUAL_FUNCTION_RETURNING_NOTHING(functionName, ...)         \
    {                                                                                                                                                               \
        pIError_latest error(NULL);                                                                                                  \
        functionName(__VA_ARGS__, error);                                                                                             \
        if (error){                                                                                                                                    \
            throw CreateUncheckedSharedPointer(error); }                                                            \
    }

        #define RETURN_RAW_PTR_FROM_FUNCTION_RETURNING_SHARED_PTR(sharedPtrType, functionName, ...)   \
    sharedPtrType sharedPtr = functionName(__VA_ARGS__);                                                                          \
    if (sharedPtr){sharedPtr->AcquireSharedOwnershipForRawPointer(); }                                                      \
    return sharedPtr.get();

        #define RETURN_RAW_PTR_FROM_SHARED_PTR(sharedPtr)                                                                                             \
    if ( (sharedPtr) ){(sharedPtr)->AcquireSharedOwnershipForRawPointer(); }                                          \
    return sharedPtr.get();

        #ifndef SOURCE_COMPILED
                #define SOURCE_COMPILED            0
        #endif

        #if SOURCE_COMPILED
                #define VIRTUAL_IF_SOURCE_COMPILED virtual
        #else
                #define VIRTUAL_IF_SOURCE_COMPILED
        #endif

namespace NS_XMPCOMMON {
typedef XMP_Int64  Int64;
typedef XMP_Uns64  UInt64;
typedef XMP_Int32  Int32;
typedef XMP_Uns32  UInt32;

        #if !XMP_64
typedef XMP_Uns32  NativeUInt;
typedef XMP_Int32  NativeInt;
        #else
typedef XMP_Uns64  NativeUInt;
typedef XMP_Int64  NativeInt;
        #endif

typedef NativeUInt SizeT;

const SizeT kMaxSize_t = (SizeT) - 1;
// force an enum type to be represented in 32 bits
static const XMP_Int32 kMaxEnumValue = Max_XMP_Int32;
}
#endif  // ENABLE_XMP_COMMON_CODE

#endif  // __XMPCommon_Defines_h__
