#ifndef _QEXTMVVMGLOBAL_H
#define _QEXTMVVMGLOBAL_H

#include <qextGlobal.h>
#include <qextMemory.h>

/***********************************************************************************************************************
   QExt Compiler specific cmds for export and import code to DLL
***********************************************************************************************************************/
#ifdef QEXT_BUILD_SHARED // compiled as a dynamic lib.
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

#endif // _QEXTMVVMGLOBAL_H
