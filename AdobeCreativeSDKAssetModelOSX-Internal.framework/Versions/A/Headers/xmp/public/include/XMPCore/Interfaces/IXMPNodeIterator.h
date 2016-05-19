#ifndef __IXMPNodeIterator_h__
#define __IXMPNodeIterator_h__ 1


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
// 02-13-14 ADC 5.5-c031 Refactoring XMPCore, implementing few APIs and fixing issues.
// 02-12-14 HK  5.5-c030 Creating client glue code for XMP DOM APIs.
// 02-12-14 HK  5.5-c029 Fixing PK failure for XMPCore DOM unit tests.
// 02-12-14 HK  5.5-c028 Done refactoring of XMP DOM interfaces and implementations.
// 02-07-14 HK  5.5-c025 Disabling warning:4250 on Windows and enabling lazy loading of Array and structure nodes children.
// 02-03-14 HK  5.5-c023 Submitting first version of XMP DOM interfaces and implementations.
//
// =================================================================================================
#endif  // AdobePrivate

#include "XMPCore/XMPCoreFwdDeclarations.h"
#include "XMPCore/XMPCore_Defines.h"

#include "XMPCommon/Interfaces/BaseInterfaces/ISharedOwnership.h"

namespace NS_XMPCORE {
using namespace NS_XMPCOMMON;
/**
 * This class represents an iterator over the children of a XMP DOM node.
 */
class XMP_PUBLIC IXMPNodeIterator_v1
    : public virtual ISharedOwnership_v1
{
public:
/**
 * This method returns the node, this iterator is currently pointing to.
 */
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPNode_latest GetValue();
/**
 * This method increases pointer of iterator by one and returns itself. Returns null if end of iterator is reached.
 */
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPNodeIterator_latest Next();

protected:
virtual pIXMPNode_latest GetValue(pIError_base & err) __NOTHROW__ = 0;
virtual pIXMPNodeIterator_latest Next(pIError_base & err) __NOTHROW__ = 0;
virtual ~IXMPNodeIterator_v1() __NOTHROW__ = 0;

                #ifndef FRIEND_CLASS_DECLARATION
                        #define FRIEND_CLASS_DECLARATION()
                #endif
FRIEND_CLASS_DECLARATION();
};

inline IXMPNodeIterator_v1::~IXMPNodeIterator_v1() __NOTHROW__
{
}

/**
 * This class represents an iterator over the children of a XMP DOM node.
 */
class XMP_PUBLIC IXMPConstNodeIterator_v1
    : public virtual ISharedOwnership_v1
{
public:
/**
 * This method returns the node, this iterator is currently pointing to.
 */
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spcIXMPNode_latest GetValue();
/**
 * This method increases pointer of iterator by one and returns itself. Returns null if end of iterator is reached.
 */
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPConstNodeIterator_latest Next();

protected:
virtual pcIXMPNode_latest GetValue(pIError_base & err) __NOTHROW__ = 0;
virtual pIXMPConstNodeIterator_latest Next(pIError_base & err) __NOTHROW__ = 0;
virtual ~IXMPConstNodeIterator_v1() __NOTHROW__ = 0;

                #ifndef FRIEND_CLASS_DECLARATION
                        #define FRIEND_CLASS_DECLARATION()
                #endif
FRIEND_CLASS_DECLARATION();
};

inline IXMPConstNodeIterator_v1::~IXMPConstNodeIterator_v1() __NOTHROW__
{
}
}

#endif  // __IXMPNodeIterator_h__