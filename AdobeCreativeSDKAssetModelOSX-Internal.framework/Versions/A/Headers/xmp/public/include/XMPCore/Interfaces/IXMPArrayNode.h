#ifndef __IXMPArrayNode_h__
#define __IXMPArrayNode_h__ 1

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

#include "XMPCore/Interfaces/IXMPNode.h"

namespace NS_XMPCORE {
using namespace NS_XMPCOMMON;

/**
 * This enumeration represents different kinds of array forms possible in XMP i.e,
 * unordered, ordered and alternative.
 */
typedef enum
{
    kXMPArrayNodeFormUnordered              = 0,
    kXMPArrayNodeFormOrdered                = 1,
    kXMPArrayNodeFormAlternative    = 2,

    kXMPArrayNodeFormMaxValue               = NS_XMPCOMMON::kMaxEnumValue
} eXMPArrayNodeForm;

/**
 * This class extends XMP node and represents an array in the XMP tree. There are 3 types of
 * XMP arrays: unordered, ordered or alternative
 *
 */
class XMP_PUBLIC IXMPArrayNode_v1
    : public virtual IXMPNode_v1 {
public:

using IXMPNode_v1::GetNode;
/**
 * This method returns the node in this array at specified index.
 */
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spcIXMPNode_latest GetNode(SizeT index) const;
/**
 * This method returns the node in this array at specified index.
 */
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPNode_latest GetNode(SizeT index);
/**
 * This method returns the node of type "simple" in this array at specified index.
 */
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spcIXMPSimpleNode_latest GetSimpleNode(SizeT index) const;
/**
 * This method returns the node of type "simple" in this array at specified index.
 */
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPSimpleNode_latest GetSimpleNode(SizeT index);
/**
 * This method returns the node of type "array" in this array at specified index.
 */
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spcIXMPArrayNode_latest GetArrayNode(SizeT index) const;
/**
 * This method returns the node of type "array" in this array at specified index.
 */
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPArrayNode_latest GetArrayNode(SizeT index);
/**
 * This method returns the node of type "struct" in this array at specified index.
 */
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spcIXMPStructNode_latest GetStructNode(SizeT index) const;
/**
 * This method returns the node of type "struct" in this array at specified index.
 */
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPStructNode_latest GetStructNode(SizeT index);
// spcIXMPLanguageAlternative GetLanguageAlternative( SizeT index ) const;
// spIXMPLanguageAlternative GetLanguageAlternative( SizeT index );

/**
 * This method creates, appends a simple node initialized with specified value at the end of this array
 * and returns it.
 */
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPSimpleNode_latest AppendSimpleNode(const char *value);
/**
 * This method creates, appends an empty array node of specified form type at the end of this array
 * and returns it.
 */
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPArrayNode_latest AppendArrayNode(eXMPArrayNodeForm form);
/**
 * This method creates, appends an empty struct node at the end of this array and returns it.
 */
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPStructNode_latest AppendStructNode();
// spIXMPLanguageAlternative AppendLanguageAlternative();

/**
 * This method creates, sets a simple node initialized with specified value at the specified index of this array
 * and returns it.
 */
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPSimpleNode_latest SetSimpleNode(SizeT index, const char *value);
/**
 * This method creates, sets an empty array of specified form type at the specified index of this array
 * and returns it.
 */
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPArrayNode_latest SetArrayNode(SizeT index, eXMPArrayNodeForm form);
/**
 * This method creates, sets an empty struct node at the specified index of this array
 * and returns it.
 */
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPStructNode_latest SetStructNode(SizeT index);
// spIXMPLanguageAlternative SetLanguageAlternative( SizeT index );

/**
 * This method creates, inserts a simple node initialized with specified value at the specified index of this array
 * and returns it.
 */
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPSimpleNode_latest InsertSimpleNode(SizeT index, const char *value);
/**
 * This method creates, inserts an empty array of specified form type at the specified index of this array
 * and returns it.
 */
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPArrayNode_latest InsertArrayNode(SizeT index, eXMPArrayNodeForm form);
/**
 * This method creates, inserts an empty struct node at the specified index of this array
 * and returns it.
 */
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPStructNode_latest InsertStructNode(SizeT index);
// spIXMPLanguageAlternative InsertLanguageAlternative( SizeT index );

using IXMPNode_v1::Remove;
/**
 * This method removes the node at the specified index of this array
 * and returns it.
 */
XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIXMPNode_latest Remove(SizeT index);
/**
 * This method returns the form type of this array.
 */
virtual eXMPArrayNodeForm GetFormType() const __NOTHROW__ = 0;
/**
 * This method returns true of this array has no elements.
 */
virtual bool IsEmpty() const __NOTHROW__ = 0;
/**
 * This method removes all the elements of this array.
 */
virtual void Clear() __NOTHROW__ = 0;

protected:

virtual pcIXMPNode_latest GetNode(SizeT index, pIError_base & err) const __NOTHROW__ = 0;
virtual pIXMPNode_latest GetNode(SizeT index, pIError_base & err) __NOTHROW__ = 0;

virtual pcIXMPSimpleNode_latest GetSimpleNode(SizeT index, pIError_base & err) const __NOTHROW__ = 0;
virtual pIXMPSimpleNode_latest GetSimpleNode(SizeT index, pIError_base & err) __NOTHROW__ = 0;
virtual pcIXMPArrayNode_latest GetArrayNode(SizeT index, pIError_base & err) const __NOTHROW__ = 0;
virtual pIXMPArrayNode_latest GetArrayNode(SizeT index, pIError_base & err) __NOTHROW__ = 0;
virtual pcIXMPStructNode_latest GetStructNode(SizeT index, pIError_base & err) const __NOTHROW__ = 0;
virtual pIXMPStructNode_latest GetStructNode(SizeT index, pIError_base & err) __NOTHROW__ = 0;
virtual pcIXMPLanguageAlternative_latest GetLanguageAlternative(SizeT index, pIError_base & err) const __NOTHROW__ = 0;
virtual pIXMPLanguageAlternative_latest GetLanguageAlternative(SizeT index, pIError_base & err) __NOTHROW__ = 0;

virtual pIXMPSimpleNode_latest AppendSimpleNode(const char *value, pIError_base & err) __NOTHROW__ = 0;
virtual pIXMPArrayNode_latest AppendArrayNode(eXMPArrayNodeForm form, pIError_base & err) __NOTHROW__ = 0;
virtual pIXMPStructNode_latest AppendStructNode(pIError_base & err) __NOTHROW__ = 0;
virtual pIXMPLanguageAlternative_latest AppendLanguageAlternative(pIError_base & err) __NOTHROW__ = 0;

virtual pIXMPSimpleNode_latest SetSimpleNode(SizeT index, const char *value, pIError_base & err) __NOTHROW__ = 0;
virtual pIXMPArrayNode_latest SetArrayNode(SizeT index, eXMPArrayNodeForm form, pIError_base & err) __NOTHROW__ = 0;
virtual pIXMPStructNode_latest SetStructNode(SizeT index, pIError_base & err) __NOTHROW__ = 0;
virtual pIXMPLanguageAlternative_latest SetLanguageAlternative(SizeT index, pIError_base & err) __NOTHROW__ = 0;

virtual pIXMPSimpleNode_latest InsertSimpleNode(SizeT index, const char *value, pIError_base & err) __NOTHROW__ = 0;
virtual pIXMPArrayNode_latest InsertArrayNode(SizeT index, eXMPArrayNodeForm form, pIError_base & err) __NOTHROW__ = 0;
virtual pIXMPStructNode_latest InsertStructNode(SizeT index, pIError_base & err) __NOTHROW__ = 0;
virtual pIXMPLanguageAlternative_latest InsertLanguageAlternative(SizeT index, pIError_base & err) __NOTHROW__ = 0;

virtual pIXMPNode_latest Remove(SizeT index, pIError_base & err) __NOTHROW__ = 0;

virtual ~IXMPArrayNode_v1() __NOTHROW__ = 0;

                #ifndef FRIEND_CLASS_DECLARATION
                        #define FRIEND_CLASS_DECLARATION()
                #endif
FRIEND_CLASS_DECLARATION();
};

inline IXMPArrayNode_v1::~IXMPArrayNode_v1() __NOTHROW__
{
}
}

#endif  // __IXMPArrayNode_h__
