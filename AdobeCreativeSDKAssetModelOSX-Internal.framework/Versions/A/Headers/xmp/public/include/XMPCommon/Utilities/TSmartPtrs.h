#ifndef __TSmartPtrs_h__
#define __TSmartPtrs_h__ 1

// =================================================================================================
// Copyright 2014 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

// =================================================================================================
/// @file TSmartPointers.h
/// @brief Definition of smart pointers to be used by the clients of XMP Toolkit
///
/// This header defines the template versions of smart pointers that can be used within
/// XMP framework.
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
// mm-dd-yy who Description of changes, most recent on top
//
// 02-25-14 ADC 1.0-m011 Changes required for compiling on Visual Studio 2010.
// 02-24-14 ADC 5.6-c001 XMPCommon Framework and XMPCore new APIs ported to Mac Environment.
//
// 02-19-14 ADC 1.0-m007 Public Header files were referring to couple of private header files.
// 02-19-14 ADC 5.5-c007 Public Header files were referring to couple of private header files.
// 02-18-14 ADC 1.0-m004 Three Way Conflict Identification Feature.
// 02-13-14 ADC 5.5-c031 Refactoring XMPCore, implementing few APIs and fixing issues.
//
// =================================================================================================
#endif // AdobePrivate


#include "XMPCommon/XMPCommon_Defines.h"

#if SUPPORT_SHARED_POINTERS_IN_STD
        #include <functional>
        #include <memory>
#elif SUPPORT_SHARED_POINTERS_IN_TR1
        #if XMP_WinBuild
                #include <functional>
                #include <memory>
        #else
                #include <tr1/functional>
                #include <tr1/memory>
        #endif
#else
        #error "location of shared pointer stuff is unknown"
#endif

namespace NS_XMPCOMMON {
#if SUPPORT_SHARED_POINTERS_IN_STD
using std::shared_ptr;
using std::mem_fn;
using std::dynamic_pointer_cast;
using std::static_pointer_cast;
#elif SUPPORT_SHARED_POINTERS_IN_TR1
using std::tr1::shared_ptr;
using std::tr1::mem_fn;
using std::tr1::dynamic_pointer_cast;
using std::tr1::static_pointer_cast;
#endif

template< typename Ty >
shared_ptr< Ty > CreateUncheckedSharedPointer(Ty *ptr)
{
    ptr->AcquireSharedOwnership();
    return shared_ptr< Ty >(ptr, mem_fn(&Ty::ReleaseSharedOwnership) );
}

template< typename OutPtrType, typename InPtrType >
shared_ptr< OutPtrType > CreateSharedPointer(InPtrType *ptr)
{
    static bool dynamicCastSuccess = false;
    OutPtrType *outPtr = NULL;

    if (dynamicCastSuccess)
    {
        outPtr = static_cast< OutPtrType * >(ptr);
    }
    else
    {
        outPtr = dynamic_cast< OutPtrType * >(ptr);

        if (outPtr)
        {
            dynamicCastSuccess = true;
        }
    }

    if (outPtr)
    {
        ptr->AcquireSharedOwnership();
        return shared_ptr< OutPtrType >(outPtr, mem_fn(&OutPtrType::ReleaseSharedOwnership) );
    }
    else
    {
        // TODO:@Aman: throw error
        return shared_ptr< OutPtrType >();
    }
}

template< typename Ty >
shared_ptr< Ty > CreateUncheckedSharedPtrWithDefaultDelete(Ty *ptr)
{
    return shared_ptr< Ty >(ptr);
}
}

#endif  // __TSmartPtrs_h__
