#ifndef _QEXTICONFONTGLOBAL_H
#define _QEXTICONFONTGLOBAL_H

#include <qextGlobal.h>

/********************************************************************************
   QEXT Compiler specific cmds for export and import code to DLL
********************************************************************************/
#ifdef QEXT_BUILD_SHARED_LIBS // compiled as a dynamic lib.
    #ifdef QEXT_BUILD_ICONFONT_LIB // defined if we are building the lib
        #define QEXT_ICONFONT_API Q_DECL_EXPORT
    #else
        #define QEXT_ICONFONT_API Q_DECL_IMPORT
    #endif
    #define QEXT_ICONFONT_HIDDEN Q_DECL_HIDDEN
#else // compiled as a static lib.
    #define QEXT_ICONFONT_API
    #define QEXT_ICONFONT_HIDDEN
#endif

#endif // _QEXTICONFONTGLOBAL_H
