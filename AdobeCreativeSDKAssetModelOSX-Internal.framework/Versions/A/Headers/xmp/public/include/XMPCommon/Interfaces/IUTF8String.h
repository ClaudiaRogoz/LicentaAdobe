#ifndef __IUTF8String_h__
#define __IUTF8String_h__ 1

// =================================================================================================
// Copyright 2014 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

// =================================================================================================
/// @file IUTF8String.h
/// @brief Definition of IUTFString interface and related types
///
/// This header defines the interface of the IUTF8String type and its related types.
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
// 02-05-14 ADC 1.0-m002 Some changes in the common framework
// 01-30-14 ADC 1.0-m001 First version
//
// =================================================================================================
#endif // AdobePrivate

#include "XMPCommon/Interfaces/BaseInterfaces/ISharedOwnership.h"
#include "XMPCommon/XMPCommonFwdDeclerations.h"
#include "XMPCommon/XMPCommon_Defines.h"

namespace NS_XMPCOMMON {
class XMP_PUBLIC IUTF8String_v1
    : public virtual ISharedOwnership_v1
{
public:
XMP_PRIVATE spIUTF8String append(const char *);
XMP_PRIVATE spIUTF8String append(const char *, SizeT count);
XMP_PRIVATE spIUTF8String append(const spIUTF8String &);
XMP_PRIVATE spIUTF8String assign(const char *);
XMP_PRIVATE spIUTF8String assign(const char *, SizeT count);
XMP_PRIVATE spIUTF8String assign(const spIUTF8String &);

virtual const char * c_str() const = 0;
virtual void clear() = 0;
virtual bool empty() const = 0;
virtual SizeT size() const = 0;

// XMP_PRIVATE static spIUTF8String CreateEmptyString();
// XMP_PRIVATE static spIUTF8String CreateFromCStr( const char * );
// XMP_PRIVATE static spIUTF8String CreateFromUTF8String( const spIUTF8String );

// TODO:@Aman protected:
virtual pIUTF8String_latest assign(const char *buffer, pIError_base & error) __NOTHROW__ = 0;
virtual pIUTF8String_latest assign(const char *buffer, SizeT count, pIError_base & error) __NOTHROW__ = 0;
virtual pIUTF8String_latest assign(pcIUTF8String_base str, pIError_base & error) __NOTHROW__ = 0;
virtual pIUTF8String_latest append(const char *buffer, pIError_base & error) __NOTHROW__ = 0;
virtual pIUTF8String_latest append(const char *buffer, SizeT count, pIError_base & error) __NOTHROW__ = 0;
virtual pIUTF8String_latest append(pcIUTF8String_base, pIError_base & error) __NOTHROW__ = 0;

protected:
virtual ~IUTF8String_v1() __NOTHROW__ = 0;
};

inline IUTF8String_v1::~IUTF8String_v1() __NOTHROW__
{
}
}

#endif  // __IUTF8String_h__
