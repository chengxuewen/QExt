#ifndef _QEXTOPENSSLGLOBAL_H
#define _QEXTOPENSSLGLOBAL_H

#include <qextGlobal.h>
#include <qextOpenSSLConfig.h>

/***********************************************************************************************************************
   QExt Compiler specific cmds for export and import code to DLL
***********************************************************************************************************************/
#ifdef QEXT_BUILD_SHARED // compiled as a dynamic lib.
#   ifdef QEXT_BUILD_OPENSSL_LIB // defined if we are building the lib
#       define QEXT_OPENSSL_API Q_DECL_EXPORT
#   else
#       define QEXT_OPENSSL_API Q_DECL_IMPORT
#   endif
#   define QEXT_OPENSSL_HIDDEN Q_DECL_HIDDEN
#else // compiled as a static lib.
#   define QEXT_OPENSSL_API
#   define QEXT_OPENSSL_HIDDEN
#endif

#endif // _QEXTOPENSSLGLOBAL_H
