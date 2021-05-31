#ifndef QEXTCOROUTINEGLOBAL_H
#define QEXTCOROUTINEGLOBAL_H

#include <qextglobal.h>

/********************************************************************************
   QEXT Compiler specific cmds for export and import code to DLL
********************************************************************************/
#ifdef QEXT_BUILD_SHARED_LIBS // compiled as a dynamic lib.
#   ifdef QEXT_BUILD_COROUTINE_LIB // defined if we are building the lib
#       define QEXT_COROUTINE_API Q_DECL_EXPORT
#   else
#       define QEXT_COROUTINE_API Q_DECL_IMPORT
#   endif
#   define QEXT_COROUTINE_HIDDEN Q_DECL_HIDDEN
#else // compiled as a static lib.
#   define QEXT_COROUTINE_API
#   define QEXT_COROUTINE_HIDDEN
#endif

#endif // QEXTCOROUTINEGLOBAL_H
