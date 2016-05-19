#ifndef __IXMPNode_h__
#define __IXMPNode_h__ 1

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
// 02-18-14 ADC 1.0-m004 Three Way Conflict Identification Feature.
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
#include "XMPCommon/XMPCommonFwdDeclerations.h"

namespace NS_XMPCORE {
using namespace NS_XMPCOMMON;
/**
 * This enumeration represents various types of properties type available in XMP like
 * simple, array and structure.
 */
typedef enum
{
    kXMPNodeTypeSimple                              = 0,
    kXMPNodeTypeArray                               = 1,
    kXMPNodeTypeStruct                              = 2,

    kXMPNodeTypeMaxValue                    = NS_XMPCOMMON::kMaxEnumValue
} eXMPNodeType;

/**
 * This class represents XMP DOM node. All kinds of XMP properties (simple, array, structure) extend this class.
 */
class XMP_PUBLIC IXMPNode_v1
    : public virtual ISharedOwnership_v1
{
public:

/**
 * This method returns parent of this node. Returns null if this is root node.
 */
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spcIXMPNode_latest GetParent() const;
/**
 * This method returns parent of this node. Returns null if this is root node.
 */
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPNode_latest GetParent();
/**
 * This method returns name of this node.
 */
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spcIUTF8String GetName() const;
/**
 * This method returns name of this node.
 */
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIUTF8String GetName();
/**
 * This method returns namespace of this node.
 */
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spcIUTF8String GetNameSpace() const;
/**
 * This method returns namespace of this node.
 */
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIUTF8String GetNameSpace();
/**
 * This method returns XMP path of this node.
 */
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spcIXMPPath_latest GetPath() const;
/**
 * This method returns XMP path of this node.
 */
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPPath_latest GetPath();
/**
 * This method returns node present at specified path in the DOM relative to this node.
 */
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spcIXMPNode_latest GetNode(const spcIXMPPath_latest & path) const;
/**
 * This method returns node present at specified path in the DOM relative to this node.
 */
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPNode_latest GetNode(const spcIXMPPath_latest & path);
/**
 * This method returns an iterator to iterate over the children of this node. If this node represents simple
 * property then it returns null.
 */
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPConstNodeIterator_latest Iterator() const;
/**
 * This method returns an iterator to iterate over the children of this node. If this node represents simple
 * property then it returns null.
 */
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPNodeIterator_latest Iterator();
/**
 * This method returns simple property node present at specified path in the DOM relative to this node. If no such
 * node exists then it returns null.
 */
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spcIXMPSimpleNode_latest GetSimpleNode(const spcIXMPPath_latest & path) const;
/**
 * This method returns simple property node present at specified path in the DOM relative to this node. If no such
 * node exists then it returns null.
 */
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPSimpleNode_latest GetSimpleNode(const spcIXMPPath_latest & path);
/**
 * This method returns structure property node present at specified path in the DOM relative to this node. If no such
 * node exists then it returns null.
 */
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spcIXMPStructNode_latest GetStructNode(const spcIXMPPath_latest & path) const;
/**
 * This method returns structure property node present at specified path in the DOM relative to this node. If no such
 * node exists then it returns null.
 */
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPStructNode_latest GetStructNode(const spcIXMPPath_latest & path);
/**
 * This method returns array property node present at specified path in the DOM relative to this node. If no such
 * node exists then it returns null.
 */
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spcIXMPArrayNode_latest GetArrayNode(const spcIXMPPath_latest & path) const;
/**
 * This method returns array property node present at specified path in the DOM relative to this node. If no such
 * node exists then it returns null.
 */
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPArrayNode_latest GetArrayNode(const spcIXMPPath_latest & path);
// spcIXMPLanguageAlternative GetLangAlt( const spcIXMPPath_latest & path ) const;
// spIXMPLanguageAlternative GetLangAlt( const spcIXMPPath_latest & path );
/**
 * This method returns qualifiers present at this node.
 */
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spcIXMPQualifiers_latest GetQualifiers( ) const;
/**
 * This method returns qualifiers present at this node.
 */
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPQualifiers_latest GetQualifiers( );
/**
 * This method removes and returns node present at specified path in the DOM relative to this node.
 */
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPNode_latest Remove(const spcIXMPPath_latest &);
/**
 * This method returns the type of this node which can be simple, array or struture.
 */
virtual eXMPNodeType GetNodeType() const __NOTHROW__ = 0;
/**
 * This method returns true if this node's parent is an array else false.
 */
virtual bool IsArrayItem() const __NOTHROW__ = 0;
/**
 * This method returns true if it has qualifiers else false.
 */
virtual bool HasQualifiers() const __NOTHROW__ = 0;
/**
 * This method returns the number of children this node has. If this is a simple propertu then it returns 0.
 */
virtual size_t Size() const __NOTHROW__ = 0;

template< typename derivedTy, typename baseTy >
XMP_PRIVATE static const shared_ptr< const derivedTy > AdaptNodeTo(const shared_ptr< const baseTy > & basePtr)
{
    return NS_XMPCOMMON::dynamic_pointer_cast< const derivedTy >(basePtr);
}

template< typename derivedTy, typename baseTy >
XMP_PRIVATE static shared_ptr< derivedTy > AdaptNodeTo(const shared_ptr< baseTy > & basePtr)
{
    return NS_XMPCOMMON::dynamic_pointer_cast< derivedTy >(basePtr);
}

protected:
virtual pcIXMPNode_latest GetParent(pIError_base & err) const __NOTHROW__ = 0;
virtual pIXMPNode_latest GetParent(pIError_base & err) __NOTHROW__ = 0;
virtual pcIUTF8String_latest GetName(pIError_base & err) const __NOTHROW__ = 0;
virtual pIUTF8String_latest GetName(pIError_base & err) __NOTHROW__ = 0;
virtual pcIUTF8String_latest GetNameSpace(pIError_base & err) const __NOTHROW__ = 0;
virtual pIUTF8String_latest GetNameSpace(pIError_base & err) __NOTHROW__ = 0;
virtual pIXMPConstNodeIterator_latest Iterator(pIError_base & err) const __NOTHROW__ = 0;
virtual pIXMPNodeIterator_latest Iterator(pIError_base & err) __NOTHROW__ = 0;
virtual pcIXMPPath_latest GetPath(pIError_base & err) const __NOTHROW__ = 0;
virtual pIXMPPath_latest GetPath(pIError_base & err) __NOTHROW__ = 0;
virtual pcIXMPNode_latest GetNode(pcIXMPPath_base, pIError_base & err) const __NOTHROW__ = 0;
virtual pIXMPNode_latest GetNode(pcIXMPPath_base, pIError_base & err) __NOTHROW__ = 0;
virtual pIXMPNode_latest Remove(pcIXMPPath_base, pIError_base & err) __NOTHROW__ = 0;
virtual pcIXMPQualifiers_latest GetQualifiers(pIError_base &) const __NOTHROW__ = 0;
virtual pIXMPQualifiers_latest GetQualifiers(pIError_base &) __NOTHROW__ = 0;

virtual ~IXMPNode_v1() __NOTHROW__ = 0;

                #ifndef FRIEND_CLASS_DECLARATION
                        #define FRIEND_CLASS_DECLARATION()
                #endif
FRIEND_CLASS_DECLARATION();
};

inline IXMPNode_v1::~IXMPNode_v1() __NOTHROW__
{
}
}

#endif  // __IXMPNode_h__
