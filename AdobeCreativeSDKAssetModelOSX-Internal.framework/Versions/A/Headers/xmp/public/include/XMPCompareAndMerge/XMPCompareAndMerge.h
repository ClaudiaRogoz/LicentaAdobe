#ifndef __XMPCOMPAREANDMERGE_h__
#define __XMPCOMPAREANDMERGE_h__ 1

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
//  ADC	Amandeep Chawla
//
// mm-dd-yy who Description of changes, most recent on top.
//
// 02-25-14 ADC 1.0-m010 Porting XMPCompareAndMerge to Mac Environment.
// 02-18-14 ADC 1.0-m004 Three Way Conflict Identification Feature.
// 01-30-14 ADC 1.0-m001 First version
//
// =================================================================================================
#endif // AdobePrivate

//  ================================================================================================
/// \file XMPCompareAndMerge.h
/// \brief Overall header file for the XMP DiffAndMerge
///
/// This is an overall header file, the only one that C++ clients should include.
///
// TODO:@aman: update the documentation
/// The full client API is in the \c TXMPMeta.hpp, \c TXMPIterator.hpp, \c TXMPUtils.hpp headers.
/// Read these for information, but do not include them directly. The \c TXMP... classes are C++
/// template classes that must be instantiated with a string class such as \c std::string. The
/// string class is used to return text strings for property values, serialized XMP, and so on.
/// Clients must also compile \c XMP.incl_cpp to ensure that all client-side glue code is generated.
/// This should be done by including it in exactly one client source file.
///
/// There are two C preprocessor macros that simplify use of the templates:
///
/// \li \c TXMP_STRING_TYPE - Define this as the string class to use with the template. You will get
/// the template headers included and typedefs (\c SXMPMeta, and so on) to use in your code.
///
/// \li \c TXMP_EXPAND_INLINE - Define this as 1 if you want to have the template functions expanded
/// inline in your code. Leave it undefined, or defined as 0, to use out-of-line instantiations of
/// the template functions. Compiling \c XMP.incl_cpp generates explicit out-of-line
/// instantiations if \c TXMP_EXPAND_INLINE is off.
///
/// The template parameter, class \c tStringObj, must have the following member functions (which
/// match those for \c std::string):
///
/// <pre>
///  tStringObj& assign ( const char * str, size_t len )
///  size_t size() const
///  const char * c_str() const
/// </pre>
///
/// The string class must be suitable for at least UTF-8. This is the encoding used for all general
/// values, and is the default encoding for serialized XMP. The string type must also be suitable
/// for UTF-16 or UTF-32 if those serialization encodings are used. This mainly means tolerating
/// embedded 0 bytes, which \c std::string does.
//  ================================================================================================

#include "XMPCommon/XMPCommonFwdDeclerations.h"
#include "XMPCompareAndMerge/XMPCompareAndMergeFwdDeclarations.h"
#include "XMPCompareAndMerge/XMPCompareAndMerge_Defines.h"
#include "XMP_Version.h"

extern "C" {
NS_XMPCOMMON::pIError_latest XMP_PUBLIC
XMPCM_GetVersionInfo(XMP_VersionInfo *info);

NS_XMPCOMMON::pIError_latest XMP_PUBLIC
XMPCM_Initialize();

NS_XMPCOMMON::pIError_latest XMP_PUBLIC
XMPCM_Terminate();

NS_XMPCOMPAREANDMERGE::pICompareAndMergeObjectFactory_latest XMP_PUBLIC
XMPCM_GetObjectFactoryInstance();
}

// =================================================================================================

#endif  // __XMPCOMPAREANDMERGE_h__
