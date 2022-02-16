#ifndef QWT3D_GLOBAL_H
#define QWT3D_GLOBAL_H

#include <qglobal.h>

#define QWT3D_MAJOR_VERSION 0
#define QWT3D_MINOR_VERSION 2
#define QWT3D_PATCH_VERSION 6



#if defined(_MSC_VER) /* MSVC Compiler */
/* template-class specialization 'identifier' is already instantiated */
#pragma warning(disable: 4660)
/* inherits via dominance */
#pragma warning(disable: 4250)
#endif // _MSC_VER

#ifdef QWT3D_DLL

#if defined(QWT3D_MAKEDLL)     // create a DLL library
#define QWT3D_EXPORT Q_DECL_EXPORT
#else                        // use a DLL library
#define QWT3D_EXPORT Q_DECL_IMPORT
#endif

#endif // QWT3D_DLL

#ifndef QWT3D_EXPORT
#define QWT3D_EXPORT
#endif



#endif
