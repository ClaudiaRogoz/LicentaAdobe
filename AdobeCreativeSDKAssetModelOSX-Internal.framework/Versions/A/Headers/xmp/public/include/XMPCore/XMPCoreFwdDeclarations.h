#ifndef __XMPDOMFwdDeclarations_h__
#define __XMPDOMFwdDeclarations_h__ 1

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
// 02-24-14 HK  5.6-c004 Added new internal XMP DOM interfaces + fixed memory leaks + implemented qualifiers for new XMP DOM.
// 02-12-14 HK  5.5-c028 Done refactoring of XMP DOM interfaces and implementations.
// 02-09-14 ADC 5.5-c026 Re-factoring of XMPCommon Framework
//
// =================================================================================================
#endif  // AdobePrivate

#include "XMPCommon/XMPCommonFwdDeclerations.h"
#include "XMPCore/XMPCore_Defines.h"

namespace NS_XMPCORE {
using NS_XMPCOMMON::shared_ptr;

// IXMPNode
class IXMPNode_v1;

typedef IXMPNode_v1                         IXMPNode_base;
typedef IXMPNode_v1 *                       pIXMPNode_base;
typedef const IXMPNode_v1 *                 pcIXMPNode_base;

typedef IXMPNode_v1                         IXMPNode_latest;
typedef IXMPNode_v1 *                       pIXMPNode_latest;
typedef const IXMPNode_v1 *                 pcIXMPNode_latest;

typedef shared_ptr< IXMPNode_latest >       spIXMPNode_latest;
typedef shared_ptr< const IXMPNode_latest > spcIXMPNode_latest;

// IXMPSimpleNode
class IXMPSimpleNode_v1;

typedef IXMPSimpleNode_v1                         IXMPSimpleNode_base;
typedef IXMPSimpleNode_v1 *                       pIXMPSimpleNode_base;
typedef const IXMPSimpleNode_v1 *                 pcIXMPSimpleNode_base;

typedef IXMPSimpleNode_v1                         IXMPSimpleNode_latest;
typedef IXMPSimpleNode_v1 *                       pIXMPSimpleNode_latest;
typedef const IXMPSimpleNode_v1 *                 pcIXMPSimpleNode_latest;

typedef shared_ptr< IXMPSimpleNode_latest >       spIXMPSimpleNode_latest;
typedef shared_ptr< const IXMPSimpleNode_latest > spcIXMPSimpleNode_latest;

// IXMPArrayNode
class IXMPArrayNode_v1;

typedef IXMPArrayNode_v1                         IXMPArrayNode_base;
typedef IXMPArrayNode_v1 *                       pIXMPArrayNode_base;
typedef const IXMPArrayNode_v1 *                 pcIXMPArrayNode_base;

typedef IXMPArrayNode_v1                         IXMPArrayNode_latest;
typedef IXMPArrayNode_v1 *                       pIXMPArrayNode_latest;
typedef const IXMPArrayNode_v1 *                 pcIXMPArrayNode_latest;

typedef shared_ptr< IXMPArrayNode_latest >       spIXMPArrayNode_latest;
typedef shared_ptr< const IXMPArrayNode_latest > spcIXMPArrayNode_latest;

// IXMPStructNode
class IXMPStructNode_v1;

typedef IXMPStructNode_v1                         IXMPStructNode_base;
typedef IXMPStructNode_v1 *                       pIXMPStructNode_base;
typedef const IXMPStructNode_v1 *                 pcIXMPStructNode_base;

typedef IXMPStructNode_v1                         IXMPStructNode_latest;
typedef IXMPStructNode_v1 *                       pIXMPStructNode_latest;
typedef const IXMPStructNode_v1 *                 pcIXMPStructNode_latest;

typedef shared_ptr< IXMPStructNode_latest >       spIXMPStructNode_latest;
typedef shared_ptr< const IXMPStructNode_latest > spcIXMPStructNode_latest;

// IXMPLanguageAlternative
class IXMPLanguageAlternative_v1;

typedef IXMPLanguageAlternative_v1                         IXMPLanguageAlternative_base;
typedef IXMPLanguageAlternative_v1 *                       pIXMPLanguageAlternative_base;
typedef const IXMPLanguageAlternative_v1 *                 pcIXMPLanguageAlternative_base;

typedef IXMPLanguageAlternative_v1                         IXMPLanguageAlternative_latest;
typedef IXMPLanguageAlternative_v1 *                       pIXMPLanguageAlternative_latest;
typedef const IXMPLanguageAlternative_v1 *                 pcIXMPLanguageAlternative_latest;

typedef shared_ptr< IXMPLanguageAlternative_latest >       spIXMPLanguageAlternative_latest;
typedef shared_ptr< const IXMPLanguageAlternative_latest > spcIXMPLanguageAlternative_latest;

// IXMPNodeIterator
class IXMPNodeIterator_v1;

typedef IXMPNodeIterator_v1                   IXMPNodeIterator_base;
typedef IXMPNodeIterator_v1 *                 pIXMPNodeIterator_base;

typedef IXMPNodeIterator_v1                   IXMPNodeIterator_latest;
typedef IXMPNodeIterator_v1 *                 pIXMPNodeIterator_latest;

typedef shared_ptr< IXMPNodeIterator_latest > spIXMPNodeIterator_latest;

// IXMPConstNodeIterator
class IXMPConstNodeIterator_v1;

typedef IXMPConstNodeIterator_v1                   IXMPConstNodeIterator_base;
typedef IXMPConstNodeIterator_v1 *                 pIXMPConstNodeIterator_base;

typedef IXMPConstNodeIterator_v1                   IXMPConstNodeIterator_latest;
typedef IXMPConstNodeIterator_v1 *                 pIXMPConstNodeIterator_latest;

typedef shared_ptr< IXMPConstNodeIterator_latest > spIXMPConstNodeIterator_latest;


// IXMPPath
class IXMPPath_v1;

typedef IXMPPath_v1                         IXMPPath_base;
typedef IXMPPath_v1 *                       pIXMPPath_base;
typedef const IXMPPath_v1 *                 pcIXMPPath_base;

typedef IXMPPath_v1                         IXMPPath_latest;
typedef IXMPPath_v1 *                       pIXMPPath_latest;
typedef const IXMPPath_v1 *                 pcIXMPPath_latest;

typedef shared_ptr< IXMPPath_latest >       spIXMPPath_latest;
typedef shared_ptr< const IXMPPath_latest > spcIXMPPath_latest;

// IXMPPathSegment
class IXMPPathSegment_v1;

typedef IXMPPathSegment_v1                         IXMPPathSegment_base;
typedef IXMPPathSegment_v1 *                       pIXMPPathSegment_base;
typedef const IXMPPathSegment_v1 *                 pcIXMPPathSegment_base;

typedef IXMPPathSegment_v1                         IXMPPathSegment_latest;
typedef IXMPPathSegment_v1 *                       pIXMPPathSegment_latest;
typedef const IXMPPathSegment_v1 *                 pcIXMPPathSegment_latest;

typedef shared_ptr< IXMPPathSegment_latest >       spIXMPPathSegment_latest;
typedef shared_ptr< const IXMPPathSegment_latest > spcIXMPPathSegment_latest;

// IXMPQualifiers
class IXMPQualifiers_v1;

typedef IXMPQualifiers_v1                         IXMPQualifiers_base;
typedef IXMPQualifiers_v1 *                       pIXMPQualifiers_base;
typedef const IXMPQualifiers_v1 *                 pcIXMPQualifiers_base;

typedef IXMPQualifiers_v1                         IXMPQualifiers_latest;
typedef IXMPQualifiers_v1 *                       pIXMPQualifiers_latest;
typedef const IXMPQualifiers_v1 *                 pcIXMPQualifiers_latest;

typedef shared_ptr< IXMPQualifiers_latest >       spIXMPQualifiers_latest;
typedef shared_ptr< const IXMPQualifiers_latest > spcIXMPQualifiers_latest;

// IXMPMetadata
class IXMPMetadata_v1;

typedef IXMPMetadata_v1                         IXMPMetadata_base;
typedef IXMPMetadata_v1 *                       pIXMPMetadata_base;
typedef const IXMPMetadata_v1 *                 pcIXMPMetadata_base;

typedef IXMPMetadata_v1                         IXMPMetadata_latest;
typedef IXMPMetadata_v1 *                       pIXMPMetadata_latest;
typedef const IXMPMetadata_v1 *                 pcIXMPMetadata_latest;

typedef shared_ptr< IXMPMetadata_latest >       spIXMPMetadata_latest;
typedef shared_ptr< const IXMPMetadata_latest > spcIXMPMetadata_latest;

// IXMPDOMFactory
class IXMPDOMFactory_v1;

typedef IXMPDOMFactory_v1                   IXMPDOMFactory_base;
typedef IXMPDOMFactory_v1 *                 pIXMPDOMFactory_base;

typedef IXMPDOMFactory_v1                   IXMPDOMFactory_latest;
typedef IXMPDOMFactory_v1 *                 pIXMPDOMFactory_latest;

typedef shared_ptr< IXMPDOMFactory_latest > spIXMPDOMFactory_latest;
}

#endif  // __XMPDOMFwdDeclarations_h__
