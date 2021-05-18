#ifndef QEXTMVVMGLOBAL_H
#define QEXTMVVMGLOBAL_H

#include <qextglobal.h>

/********************************************************************************
   QEXT Compiler specific cmds for export and import code to DLL
********************************************************************************/
#ifdef QEXT_BUILD_SHARED_LIBS // compiled as a dynamic lib.
#   ifdef QEXT_BUILD_MVVM_LIB // defined if we are building the lib
#       define QEXT_MVVM_API Q_DECL_EXPORT
#   else
#       define QEXT_MVVM_API Q_DECL_IMPORT
#   endif
#   define QEXT_MVVM_HIDDEN Q_DECL_HIDDEN
#else // compiled as a static lib.
#   define QEXT_MVVM_API
#   define QEXT_MVVM_HIDDEN
#endif

#endif // QEXTMVVMGLOBAL_H
