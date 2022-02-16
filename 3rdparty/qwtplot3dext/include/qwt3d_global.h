#pragma once
#ifndef qwt3d_global_h__2009_10_11_14_19_14_begin_guarded_code
#define qwt3d_global_h__2009_10_11_14_19_14_begin_guarded_code

#include <qglobal.h>

#define QWT3D_MAJOR_VERSION 0
#define QWT3D_MINOR_VERSION 3
#define QWT3D_PATCH_VERSION 1


#if defined(_MSC_VER) /* MSVC Compiler */
/* template-class specialization 'identifier' is already instantiated */
#pragma warning(disable: 4660)
/* inherits via dominance */
#pragma warning(disable: 4250)
#endif // _MSC_VER

#ifdef QWTPLOT3DEXT_DLL

#if defined(QWTPLOT3DEXT_MAKEDLL)     // create a DLL library
#define QWT3D_EXPORT Q_DECL_EXPORT
#else                        // use a DLL library
#define QWT3D_EXPORT Q_DECL_IMPORT
#endif

#endif // QWT3D_DLL

#ifndef QWT3D_EXPORT
#define QWT3D_EXPORT
#endif


#endif /* include guard */
