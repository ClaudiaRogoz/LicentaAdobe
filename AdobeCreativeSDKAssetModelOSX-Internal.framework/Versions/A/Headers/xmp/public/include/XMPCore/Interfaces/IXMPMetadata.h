#ifndef __IXMPMetadata_h__
#define __IXMPMetadata_h__ 1

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
//  ADC	Amandeep Chawla
//
// mm-dd-yy who Description of changes, most recent first.
//
// 02-24-14 HK  5.6-c004 Added new internal XMP DOM interfaces + fixed memory leaks + implemented qualifiers for new XMP DOM.
// 02-24-14 ADC 5.6-c001 XMPCommon Framework and XMPCore new APIs ported to Mac Environment.
// 02-18-14 HK  5.5-c034 Implementing Serialize(), Clone() and all setter/modifier methods of XMP DOM.
// 02-12-14 HK  5.5-c030 Creating client glue code for XMP DOM APIs.
// 02-12-14 HK  5.5-c028 Done refactoring of XMP DOM interfaces and implementations.
// 02-07-14 HK  5.5-c025 Disabling warning:4250 on Windows and enabling lazy loading of Array and structure nodes children.
// 02-03-14 HK  5.5-c023 Submitting first version of XMP DOM interfaces and implementations.
//
// =================================================================================================
#endif  // AdobePrivate

#include "XMPCore/XMPCoreFwdDeclarations.h"
#include "XMPCore/XMPCore_Defines.h"

#include "XMPCore/Interfaces/IXMPStructNode.h"


namespace NS_XMPCORE {
using namespace NS_XMPCOMMON;

/**
 * This class extends XMP structure and represents root node of XMP DOM.
 */
class XMP_PUBLIC IXMPMetadata_v1
    : public virtual IXMPStructNode_v1
{
public:
/**
 *
 */
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spcIUTF8String GetAboutURI() const;
/**
 *
 */
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIUTF8String GetAboutURI();
/**
 *
 */
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED void SetAboutURI(const char *uri);
/**
 * This method serializes this XMP DOM and returns serialized XMP packet string.
 */
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIUTF8String Serialize() const;
/**
 * This method clones this XMP DOM and returns it.
 */
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPMetadata_latest Clone() const;

XMP_PRIVATE static spIXMPMetadata_latest Create(const char *packet, SizeT length);

protected:
virtual pcIUTF8String_latest GetAboutURI(pIError_base &) const __NOTHROW__ = 0;
virtual pIUTF8String_latest GetAboutURI(pIError_base &) __NOTHROW__ = 0;
virtual void SetAboutURI(const char *uri, size_t uriLength, pIError_base &) __NOTHROW__ = 0;
virtual pIUTF8String_latest Serialize(pIError_base &) const __NOTHROW__ = 0;
virtual pIXMPMetadata_latest Clone(pIError_base &) const __NOTHROW__ = 0;
virtual ~IXMPMetadata_v1()  __NOTHROW__;

                #ifndef FRIEND_CLASS_DECLARATION
                        #define FRIEND_CLASS_DECLARATION()
                #endif
FRIEND_CLASS_DECLARATION();
};

inline IXMPMetadata_v1::~IXMPMetadata_v1()  __NOTHROW__
{
}
}

#endif  // __IXMPMetadata_h__
