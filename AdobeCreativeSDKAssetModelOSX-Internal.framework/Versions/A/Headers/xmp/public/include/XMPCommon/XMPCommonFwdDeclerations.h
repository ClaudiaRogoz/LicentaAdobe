#ifndef __XMPCommonFwdDeclerations_h__
#define __XMPCommonFwdDeclerations_h__ 1

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
// 02-13-14 ADC 5.5-c031 Refactoring XMPCore, implementing few APIs and fixing issues.
// 02-09-14 ADC 1.0-m003 Re-factoring of XMPCommon Framework
//
// =================================================================================================
#endif  // AdobePrivate

#include "XMPCommon/Utilities/TSmartPtrs.h"
#include "XMPCommon/XMPCommon_Defines.h"

namespace NS_XMPCOMMON {
using NS_XMPCOMMON::shared_ptr;

// IError
class IError_v1;

typedef IError_v1                   IError_base;
typedef IError_v1 *                 pIError_base;

typedef IError_v1                   IError_latest;
typedef IError_v1 *                 pIError_latest;

typedef shared_ptr< IError_latest > spIError;

// IUTF8String
class IUTF8String_v1;

typedef IUTF8String_v1                         IUTF8String_base;
typedef IUTF8String_v1 *                       pIUTF8String_base;
typedef const IUTF8String_v1 *                 pcIUTF8String_base;

typedef IUTF8String_v1                         IUTF8String_latest;
typedef IUTF8String_v1 *                       pIUTF8String_latest;
typedef const IUTF8String_v1 *                 pcIUTF8String_latest;

typedef shared_ptr< IUTF8String_latest >       spIUTF8String;
typedef shared_ptr< const IUTF8String_latest > spcIUTF8String;

// IClientAllocator
class IClientAllocator_v1;

typedef IClientAllocator_v1                   IClientAllocator_base;
typedef IClientAllocator_v1 *                 pIClientAllocator_base;

typedef IClientAllocator_v1                   IClientAllocator_latest;
typedef IClientAllocator_v1 *                 pIClientAllocator_latest;

typedef shared_ptr< IClientAllocator_latest > spIClientAllocator;

// IAllocatorManager
class IAllocatorManager_v1;

typedef IAllocatorManager_v1                   IAllocatorManager_base;
typedef IAllocatorManager_v1 *                 pIAllocatorManager_base;

typedef IAllocatorManager_v1                   IAllocatorManager_latest;
typedef IAllocatorManager_v1 *                 pIAllocatorManager_latest;

typedef shared_ptr< IAllocatorManager_latest > spIAllocatorManager;

// ISharedMutex
class ISharedMutex_v1;

typedef ISharedMutex_v1                   ISharedMutex_base;
typedef ISharedMutex_v1 *                 pISharedMutex_base;

typedef ISharedMutex_v1                   ISharedMutex_latest;
typedef ISharedMutex_v1 *                 pISharedMutex_latest;

typedef shared_ptr< ISharedMutex_latest > spISharedMutex;
}

#endif  // __XMPCommonFwdDeclerations_h__
