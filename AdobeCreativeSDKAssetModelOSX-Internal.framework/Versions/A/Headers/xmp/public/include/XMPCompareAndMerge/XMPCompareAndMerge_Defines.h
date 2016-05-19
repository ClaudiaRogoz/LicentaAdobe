#ifndef __XMPCompareAndMerge_Defines_h__
#define __XMPCompareAndMerge_Defines_h__ 1

// =================================================================================================
// Copyright 2014 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

// =================================================================================================
// XMP_CompareAndMergeDefines.h - Common Defines for XMP Compare And Merge component
// ================================================================
//
// This header defines common definitions to be used in XMP Compare And Merge component.
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
// 03-11-14 ADC 5.6-m018 Fixing some warnings reported on Windows while compiling with Warning Level 4.
// 02-25-14 ADC 1.0-m010 Porting XMPCompareAndMerge to Mac Environment.
// 01-30-14 ADC 1.0-m001 First version
//
// =================================================================================================
#endif // AdobePrivate

// =================================================================================================
// All Platform Settings
// ===========================
#include "XMPCommon/XMPCommon_Defines.h"

// =================================================================================================
// Macintosh Specific Settings
// ===========================
#if XMP_MacBuild
        #define ENABLE_XMP_COMPARE_AND_MERGE 1
#endif

// =================================================================================================
// IOS Specific Settings
// ===========================
#if XMP_iOSBuild
        #define ENABLE_XMP_COMPARE_AND_MERGE 1
#endif

// =================================================================================================
// Windows Specific Settings
// =========================
#if XMP_WinBuild
        #define ENABLE_XMP_COMPARE_AND_MERGE 1
#endif

// =================================================================================================
// UNIX Specific Settings
// ======================
#if XMP_UNIXBuild
        #define ENABLE_XMP_COMPARE_AND_MERGE 0
#endif

#ifndef ENABLE_XMP_COMPARE_AND_MERGE
        #define ENABLE_XMP_COMPARE_AND_MERGE 0
#endif

#if ENABLE_XMP_COMPARE_AND_MERGE
        #define NS_XMPCOMPAREANDMERGE        AdobeXMPCM
#endif

#endif  // __XMPCompareAndMerge_Defines_h__
