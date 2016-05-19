#ifndef __ITSingleton_h__
#define __ITSingleton_h__ 1

// =================================================================================================
// Copyright 2014 Adobe Systems Incorporated
// All Rights Reserved.
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
//  ADC Amandeep Chawla
//
// mm-dd-yy who Description of changes, most recent on top
//
// 02-24-14 ADC 5.6-c001 XMPCommon Framework and XMPCore new APIs ported to Mac Environment.
//
// 02-09-14 ADC 1.0-m003 Re-factoring of XMPCommon Framework
// 02-05-14 ADC 1.0-m002 Some changes in the common framework
// 01-30-14 ADC 1.0-m001 First Version of the file
//
// =================================================================================================
#endif // AdobePrivate

#include "XMPCommon/XMPCommon_Defines.h"

namespace NS_XMPCOMMON {
template< typename Ty >
class XMP_PUBLIC ITSingleton {
public:
typedef Ty *pointer;

XMP_PRIVATE static pointer GetInstance();
XMP_PRIVATE static void CreateInstance();
XMP_PRIVATE static void DestroyInstance();

protected:
};
}
#endif  // __ITSingleton_h__
