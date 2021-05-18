#ifndef QEXTJSONGLOBAL_H
#define QEXTJSONGLOBAL_H

#include <qextglobal.h>

/********************************************************************************
   QEXT Compiler specific cmds for export and import code to DLL
********************************************************************************/
#ifdef QEXT_BUILD_SHARED_LIBS // compiled as a dynamic lib.
#   ifdef QEXT_BUILD_JSON_LIB // defined if we are building the lib
#       define QEXT_JSON_API Q_DECL_EXPORT
#   else
#       define QEXT_JSON_API Q_DECL_IMPORT
#   endif
#   define QEXT_JSON_HIDDEN Q_DECL_HIDDEN
#else // compiled as a static lib.
#   define QEXT_JSON_API
#   define QEXT_JSON_HIDDEN
#endif

#endif // QEXTJSONGLOBAL_H
