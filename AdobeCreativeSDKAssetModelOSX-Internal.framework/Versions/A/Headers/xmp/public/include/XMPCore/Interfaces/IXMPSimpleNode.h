#ifndef __IXMPSimpleNode_h__
#define __IXMPSimpleNode_h__ 1

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
//  HK	Honey Kansal
//
// mm-dd-yy who Description of changes, most recent first.
//
// 02-24-14 HK  5.6-c004 Added new internal XMP DOM interfaces + fixed memory leaks + implemented qualifiers for new XMP DOM.
// 02-24-14 ADC 5.6-c001 XMPCommon Framework and XMPCore new APIs ported to Mac Environment.
// 02-12-14 HK  5.5-c029 Fixing PK failure for XMPCore DOM unit tests.
// 02-12-14 HK  5.5-c028 Done refactoring of XMP DOM interfaces and implementations.
// 02-07-14 HK  5.5-c025 Disabling warning:4250 on Windows and enabling lazy loading of Array and structure nodes children.
// 02-03-14 HK  5.5-c023 Submitting first version of XMP DOM interfaces and implementations.
//
// =================================================================================================
#endif  // AdobePrivate

#include "XMPCore/Interfaces/IXMPNode.h"

namespace NS_XMPCORE {
/**
 * This class extends XMP node and represents XMP simple property.
 */
class XMP_PUBLIC IXMPSimpleNode_v1
    : public virtual IXMPNode_v1
{
public:

/**
 * This method returns value of this simple property.
 */
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spcIUTF8String GetValue() const;
/**
 * This method returns value of this simple property.
 */
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIUTF8String GetValue();
/**
 * This method assigns specified value to this simple property.
 */
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED void SetValue(const char *value);
/**
 * This method returns true if this property represents an URI.
 */
XMP_PRIVATE virtual bool IsURI() const __NOTHROW__ = 0;
/**
 * This method sets this property as URI if true is passed.
 */
XMP_PRIVATE virtual void SetURI(bool isURI) __NOTHROW__ = 0;

protected:
virtual pcIUTF8String_latest GetValue(pIError_base &) const __NOTHROW__ = 0;
virtual pIUTF8String_latest GetValue(pIError_base &) __NOTHROW__ = 0;
virtual void SetValue(const char *value, pIError_base &) __NOTHROW__ = 0;

virtual ~IXMPSimpleNode_v1() __NOTHROW__ = 0;

                #ifndef FRIEND_CLASS_DECLARATION
                        #define FRIEND_CLASS_DECLARATION()
                #endif
FRIEND_CLASS_DECLARATION();
};

inline IXMPSimpleNode_v1::~IXMPSimpleNode_v1() __NOTHROW__
{
}
}

#endif  // __IXMPSimpleNode_h__
