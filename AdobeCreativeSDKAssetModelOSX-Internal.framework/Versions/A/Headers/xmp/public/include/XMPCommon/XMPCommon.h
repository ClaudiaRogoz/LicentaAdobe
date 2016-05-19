#ifndef __XMPCommon_h__
#define __XMPCommon_h__ 1

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
//
// =================================================================================================
#endif  // AdobePrivate

#include "XMPCommon/XMPCommonFwdDeclerations.h"
#include "XMPCommon/XMPCommon_Defines.h"

namespace NS_XMPCOMMON {
pIError_latest InitializeXMPCommonFramework();
pIError_latest TerminateXMPCommonFramework();
}

#endif  // __XMPCommon_h__
