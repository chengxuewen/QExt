#ifndef _QEXTMVVMGLOBAL_H
#define _QEXTMVVMGLOBAL_H

#include <qextGlobal.h>

/********************************************************************************
   QEXT Compiler specific cmds for export and import code to DLL
********************************************************************************/
#ifdef QEXT_BUILD_SHARED_LIBS // compiled as a dynamic lib.
    #ifdef QEXT_BUILD_MVVM_LIB // defined if we are building the lib
        #define QEXT_MVVM_API Q_DECL_EXPORT
    #else
        #define QEXT_MVVM_API Q_DECL_IMPORT
    #endif
    #define QEXT_MVVM_HIDDEN Q_DECL_HIDDEN
#else // compiled as a static lib.
    #define QEXT_MVVM_API
    #define QEXT_MVVM_HIDDEN
#endif

#ifndef M_PI
#define M_PI 3.14159265358979323846264338327950288 /* pi */
#endif

#endif // _QEXTMVVMGLOBAL_H
